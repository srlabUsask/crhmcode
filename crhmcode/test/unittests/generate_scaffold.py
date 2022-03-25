#! /bin/python

import sys, os
import glob
import re
from datetime import datetime, timedelta

import numpy as np
from numpy.random import default_rng

import pandas as pd


MODULE_SRC_BASE_PATH = '../../src/modules'
MODULE_SRC_PATHS = [MODULE_SRC_BASE_PATH,os.path.join(MODULE_SRC_BASE_PATH,'waterquality')]
NEWMODULES_CPP_PATH = os.path.join(MODULE_SRC_BASE_PATH,'newmodules','NewModules.cpp')

TEMPLATE_FILENAME = 'template.prj'

#BASE_FILENAME_VARIATION = '{module_name}_{variation_id}'
#BASE_FILENAME_NOVARIATION = '{module_name}'

BASE_FILENAME_VARIATION = '{module_name}/unit_var{variation_id}'
BASE_FILENAME_NOVARIATION = '{module_name}/unit'


def get_module_internal_name(module_name:str):
    with open(NEWMODULES_CPP_PATH,'r') as f:
        lns = f.readlines()
    for ln in lns:
# NB: Fix for capitalization error in file naming (PRL)        
        if module_name in ['ClassIntcp','ClassGlobal','ClassBasin']:
            module_name = module_name[0]+module_name[1:].lower()

        if module_name in ln:
            re_t = re.compile(r'AddModule\(new (\S+)\("(\S+)",\s+"([^"]+)"')
            rslt = re_t.search(ln)
            if rslt is not None:
                return rslt.group(2),rslt.group(3)

    print(f"Could not find 'AddModule' for {module_name} in {NEWMODULES_CPP_PATH}")
    return None,None



def get_variation_info(src_code_in:str):
    variation_matcher = re.compile(r"\W*variation_set\W*=\W*(.+);")
    src_code_as_lines = src_code_in.split('\n')
    variations = {'default':[]}
    curr_variations = ['default']
    for line in src_code_as_lines:
        rslt = variation_matcher.match(line)
        if rslt is not None:
            curr_variations = [x.strip() for x in rslt.group(1).split('+')]
            if len(curr_variations) == 0:
                curr_variations = None
            for vv in curr_variations:
                if vv not in variations:
                    variations[vv] = []            
        else:
            if curr_variations is not None:
                for vv in curr_variations:
                    if ( 'declvar(' in line or
                            'declgetvar(' in line or
                            'declputvar(' in line or
                            'declstatvar(' in line or
                            'declreadobs(' in line or
                            'declparam(' in line
                    ):
                        variations[vv].append(line)

    print(variations)
    return variations


def get_obs_vars(src_code_in:str):
    obsvars_matcher = re.compile(r'declreadobs\("(\S+)"\s*,[^,]+,\s*"([^"]+)"\s*,\s*"([^"]+)"') #"(\S+)"')
    return obsvars_matcher.findall(src_code_in)


def get_io_vars(src_code_in:str):
    invars_matcher = re.compile(r'declgetvar\("\*"\s*,\s*"(\S+)"\s*,\s*"(\S+)"')
    outvars_matcher = re.compile(r'declvar\("(\S+)"')
#  declputvar("*", "Sd", "(mm)", &Sd);
    inoutvars_matcher = re.compile(r'declputvar\("\*"\s*,\s*"(\S+)"\s*,\s*"(\S+)"')
    # The additional information for statvars is not used, should match with outvars
    statvars_matcher = re.compile(r'declstatvar\("(\S+)"') #\s*,[^,]+,\s*"([^"]+)"\s*,\s*"([^"]+)"\s*')

    invars_matched = invars_matcher.findall(src_code_in)
    outvars_matched = outvars_matcher.findall(src_code_in)
    inoutvars_matched = inoutvars_matcher.findall(src_code_in)
    statvars_matched = statvars_matcher.findall(src_code_in)

    return (  invars_matched, #zip(invars_names, invars_units) ,
            outvars_matched+statvars_matched,
            inoutvars_matched )


def get_params(src_code_in:str):
    matcher = re.compile(r'declparam\("(\S+)"\s*,([^,]+),\s*"([^"]+)"\s*,\s*"([^"]+)"\s*,\s*"([^"]+)"\s*,\s*"([^"]+)"\s*,\s*"([^"]+)"')
    rslt = matcher.findall(src_code_in)

    return rslt


def reformat_params(params_list, module_name:str):
    list_out = []
    for param in params_list:
        param_name, param_dim, dflt_val_str = param[:3]
        list_out.append(f'{module_name} {param_name}')

# NB: fixups due to errors in the original code. This should be corrected in the relevant files. (PRL)
        dflt_val_str = dflt_val_str.strip()
        dflt_val_str = dflt_val_str.replace('!','')
        if dflt_val_str[-1] == ']' and dflt_val_str[0] != '[':
            dflt_val_str = '['+dflt_val_str
        if dflt_val_str == '[NOTUSED]':  # From Classqdrift
            dflt_val_str = '[0]'

        default_vals = eval(dflt_val_str)
        if isinstance(default_vals,list):
            default_vals = default_vals[0]
            
        list_out.append(f'{default_vals}')
        print(param_dim)
        if 'NLAY' in param_dim:
            list_out.append(f'{default_vals}')

    return list_out


# NB: CRHM requires MSDOS style newlines
def write_obs_file(filename:str, obsvars, module_name:str,
                    start_date:datetime, end_date:datetime):                    

    idx = pd.date_range(start_date, end_date, freq='1H')

    rng = default_rng()
    var_vals = {obsvar[0]:np.round(rng.random(len(idx)),3) for obsvar in obsvars}
#    var_vals = {obsvar[0]:[0]*len(idx) for obsvar in obsvars}

    df = pd.DataFrame(var_vals, index=idx)
    df['year'] = df.index.year
    df['month'] = df.index.month
    df['day'] = df.index.day
    df['hour'] = df.index.hour+1
    df['minute'] = df.index.minute

    with open(filename,'w', newline='\r\n') as f:
        f.write(f'unit tests for {module_name}\n')
        for obsvar in obsvars:
            f.write(f'{obsvar[0]} 1 {obsvar[2]}\n')
        f.write('############################################\n')
    df.to_csv(filename,mode='a',sep='\t', line_terminator='\r\n',
                columns=['year','month','day','hour','minute']+
                        list(var_vals.keys()),
                index=None, header=None)


def write_proj_file(filename:str,
                    invars, outvars, inoutvars, params,
                    obs_filename:str,
                    module_name:str, module_iname:str, 
                    variation_id, module_date:str,
                    start_date:datetime, end_date:datetime):
    with open(TEMPLATE_FILENAME,'r') as f:
        prj_in = f.read()

    allinvars = invars+inoutvars
    fixed_vars = False
    if fixed_vars:
        macro_decl_block = '\n'.join([
            f'\'declvar, {x[0]}, NHRU, "no description", {x[1]}\''
            for x in allinvars])
        macro_cmd_block = '\n'.join([f"'  {x[0]} = 0'" for x in invars])
        new_obs = []
    else:
        macro_decl_block = '\n'.join([
            f'\'declreadobs, obs_{x[0]}, NHRU, "no description", {x[1]}\''
            for x in allinvars]) + '\n'
        macro_decl_block += '\n'.join([
            f'\'declvar, {x[0]}, NHRU, "no description", {x[1]}\''
            for x in allinvars])
        macro_cmd_block = '\n'.join([f"'  {x[0]} = obs_{x[0]}'"
                                                for x in allinvars])
        new_obs = [('obs_'+x[0],'none',x[1]) for x in allinvars]

        if variation_id is None or variation_id=='0' or variation_id==0:
            module_block = f'{module_iname} CRHM {module_date}'
        else:
            module_block = f'{module_iname}#{variation_id} CRHM {module_date}'

##################
        params_block = '\n'.join(reformat_params(params, module_iname))

##################
        frmt_output = lambda x: x[0] if isinstance(x,tuple) else x
        outputs_block = '\n'.join( [f'{module_iname} {frmt_output(x)} 1' 
                                    for x in outvars])
        if len(inoutvars) > 0:                                    
            outputs_block += '\n' + '\n'.join( [f'Driver {frmt_output(x)} 1' 
                                    for x in inoutvars])                                    

    prj_out = prj_in.format(**{
            'DESCRIPTION':f'Unit tests for {module_name}',
            'MACRO_DECL_BLOCK':macro_decl_block,
            'MACRO_CMD_BLOCK':macro_cmd_block,
            'OBS_BLOCK':obs_filename,  #f'unittest_{module_name}.obs',
            'S_YR':start_date.year,'S_MO':start_date.month,'S_DY':start_date.day,
            'E_YR':end_date.year,'E_MO':end_date.month,'E_DY':end_date.day,
            'MODULE_BLOCK':module_block,
            'PARAMS_BLOCK':params_block,
            'OUTPUTS_BLOCK':outputs_block
            })


    with open(filename, 'w') as f:
        f.write(prj_out)

    return new_obs



def get_filename_for(moodule_name):
    for module_src_path in MODULE_SRC_PATHS:
        module_filename_in = os.path.join(module_src_path, f'{module_name}.cpp')
        if os.path.exists(module_filename_in):
            return module_filename_in
    return None

def rebuild_scaffolding(module_name:str,
                start_date:datetime, end_date:datetime):

    module_filename_in = get_filename_for(module_name)
    if module_filename_in is None:
        print("Unable to find input source file: "+module_filename_in)
        return

    with open(module_filename_in) as f:
        src_code_in = f.read()

    module_iname, module_date = get_module_internal_name(module_name)
    if module_iname is None:
        return

# Check if the module has variations
    if 'variation_set' in src_code_in:

    # Get the configuration for each variation
        variations = get_variation_info(src_code_in)
        org_info = variations['VARIATION_ORG']
        dflt_info = variations['default']
        src_code_in = ''.join(org_info) + ''.join(dflt_info)  
        obsvars_org = get_obs_vars(src_code_in)
        invars_org, outvars_org, inoutvars_org = get_io_vars(src_code_in)
        params_org = get_params(src_code_in)

        for variation_name, variation_info in variations.items():
            if variation_name == 'VARIATION_ORG' or variation_name == 'default':
                continue
            variation_id = variation_name[10:]

            src_code_in = ''.join(variation_info)   
            obsvars = get_obs_vars(src_code_in)
            invars, outvars, inoutvars = get_io_vars(src_code_in)
            params = get_params(src_code_in)

            obsvars += obsvars_org
            invars += invars_org
            outvars += outvars_org
            inoutvars += inoutvars_org
            params += params_org

            base_filename = BASE_FILENAME_VARIATION.format(
                module_name=module_name,
                variation_id=variation_id )
#            )f'{module_name}_{variation_name[10:]}'
            obs_filename = base_filename+'.obs'

            try:
                os.makedirs(os.path.dirname(obs_filename))
            except FileExistsError:
                pass

            extra_obs = write_proj_file(base_filename+'.prj',
                    invars, outvars, inoutvars,
                    params, 
                    obs_filename,
                    module_name, module_iname, 
                    variation_id, module_date,
                    start_date=start_date, end_date=end_date)

            write_obs_file(obs_filename, obsvars+extra_obs,
                                module_name,
                                start_date, end_date)

    else:
        obsvars = get_obs_vars(src_code_in)
        invars, outvars, inoutvars = get_io_vars(src_code_in)
        params = get_params(src_code_in)

        base_filename = BASE_FILENAME_NOVARIATION.format(
            module_name=module_name
        )
        obs_filename = f'{base_filename}.obs'
        try:
            os.makedirs(os.path.dirname(obs_filename))
        except FileExistsError:
            pass

        extra_obs = write_proj_file(f'{base_filename}.prj',
                    invars, outvars, inoutvars,
                    params,
                    obs_filename,
                    module_name, module_iname, 
                    None, module_date,
                    start_date=start_date, end_date=end_date)

        write_obs_file(obs_filename, obsvars+extra_obs,
                                module_name,
                                start_date, end_date)




if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage information:")
        print("Build/rebuild scaffolding for a single module")
        print(f"\tpython {sys.argv[0]} <MODULE_FILENAME>")
        print("\t<MODULE_FILENAME> is the filename of the module without any extension.")
        print("Example:")
        print(f"\tpython {sys.argv[0]} ClassNeedle")
        print()
        print("Build/rebuild scaffolding for all modules")
        print(f"\tpython {sys.argv[0]} all")
        exit(0)

    start_date = datetime(2001,1,1)
    end_date = datetime(2001,1,2)

    module_name = sys.argv[1]

    if module_name == 'all':
        for module_src_path in MODULE_SRC_PATHS:
            for filename in glob.glob(os.path.join(module_src_path,'Class*.cpp')):
                module_name = os.path.basename(filename)[:-4]
    #            print(module_name)

                # These are for support of other modules
                if module_name in ['ClassSnobalBase']:
                    continue

                if module_name in ['ClassPSPnew','Classpbsm_M','Classbrushintcp']:
                    print(f"{module_name} is not included in CRHM executable")
                    continue

                rebuild_scaffolding(module_name, start_date, end_date)
    else:
        rebuild_scaffolding(module_name, start_date, end_date)


# re.compile(r"\W*variation_set\W*=\W*(\S+);").match(ttt).group(1)

#     declparam("z_g", TDim::NHRU, "[0.01]", "0.1", "1.0", "depth of soil temp meas", "(m)", &z_g);
