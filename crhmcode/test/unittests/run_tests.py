#! /bin/python

import sys, os
import glob
import subprocess

import csv
import numpy as np
import pandas as pd


MODULE_SRC_BASE_PATH = '../../src/modules'
MODULE_SRC_PATHS = [MODULE_SRC_BASE_PATH,os.path.join(MODULE_SRC_BASE_PATH,'waterquality')]

BORLAND_OUTPUT_FILENAME = 'CRHM_output.txt'
CRHMCODE_OUTPUT_FILENAME = 'CRHM_output.txt'


def run_borland(project_filename, output_filename=BORLAND_OUTPUT_FILENAME):

    print("BL:",project_filename)
    print("BL:",os.path.abspath(project_filename) )

    if os.path.exists(output_filename):
        os.remove(output_filename)

    if sys.platform == 'linux' or sys.platform == 'darwin':
        process = subprocess.Popen([
            'wine',
            "./CRHM.exe",
            project_filename
        ], stdout=subprocess.PIPE,stderr=subprocess.PIPE,
        # cwd="/Users/richardlawford/PhD/models/hype/demos/demo",
            shell=False
        )
    else:
        process = subprocess.Popen([
            "./CRHM.exe",
            project_filename
        ], stdout=subprocess.PIPE,stderr=subprocess.PIPE,
        # cwd="/Users/richardlawford/PhD/models/hype/demos/demo",
            shell=False
        )

    output, error = process.communicate()
    return pd.read_csv(output_filename,header=[0,1],sep='\t',
                            index_col=0,parse_dates=True, encoding='iso-8859-1')



def run_crhmcode(project_filename, output_filename=CRHMCODE_OUTPUT_FILENAME):
    if os.path.exists(output_filename):
        os.remove(output_filename)

    process = subprocess.Popen([
            "./crhm",
            project_filename
        ], stdout=subprocess.PIPE,stderr=subprocess.PIPE,
            shell=False
        )
    output, error = process.communicate()
    return pd.read_csv(output_filename,header=[0,1],sep='\t',
                            index_col=0,parse_dates=True,encoding='iso-8859-1')


CUTOFF = 1e-3
ALLOWED_ERROR_FRACTION = 0.1

def compare_results(df_borland, df_crhmcode):
    global CUTOFF, ALLOWED_ERROR_FRACTION

    if len(df_borland.columns) != len(df_crhmcode.columns):
        return "Number of output columns does not match"
    if not df_borland.index.equals(df_crhmcode.index):
        return "Timestamp indices does not match"
    for col_borland, col_crhmcode in zip(df_borland.columns[1:],df_crhmcode.columns[1:]):
        dt_borland = df_borland[col_borland]
        dt_crhmcode = df_crhmcode[col_crhmcode]
        dt_absmean = np.abs(dt_borland+dt_crhmcode)/2
        msk_above_cutoff = dt_absmean > CUTOFF
        aa = dt_borland[msk_above_cutoff]
        bb = dt_crhmcode[msk_above_cutoff]
        print(len(aa),len(bb))
        print(dt_borland[msk_above_cutoff])
        print(dt_crhmcode[msk_above_cutoff])
        dt_failure = (aa.to_numpy()-bb.to_numpy()) > ALLOWED_ERROR_FRACTION * dt_absmean[msk_above_cutoff]
        if np.count_nonzero(dt_failure) > 0:
            idx = np.argwhere(dt_failure)[0]
            return f"{col_borland} / {col_crhmcode} failed to match at {df_borland.index[idx]}: values are {dt_borland[idx]} and {dt_crhmcode[idx]}"
    return None



def run_test_success(prj_file):
    prj_time = os.path.getmtime(prj_file)
    tmpl_time = os.path.getmtime('template.prj')
    if tmpl_time > prj_time:
        print(
            "WARNING: template is more recent than output project",
            file=sys.stderr
        )

    output_crhmcode = run_crhmcode(prj_file)
    output_borland = run_borland(
            os.path.abspath(prj_file),
            os.path.join(os.path.dirname(prj_file),BORLAND_OUTPUT_FILENAME))

    cmp_rslt = compare_results(output_borland, output_crhmcode)
    if cmp_rslt is None:
        print("SUCCESS")
        return True
    else:
        print("FAILURE: "+cmp_rslt)

        output_crhmcode.to_csv('crhmcode.csv')
        output_borland.to_csv('borland.csv')
        return False



if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage information:")
        print("Run tests for a single module")
        print(f"\tpython {sys.argv[0]} <MODULE_FILENAME>")
        print("\t<MODULE_FILENAME> is the filename of the module without any extension.")
        print("Example:")
        print(f"\tpython {sys.argv[0]} ClassNeedle")
        print()
        print("Run tests for all modules")
        print(f"\tpython {sys.argv[0]} all")
        exit(0)

    module_names = [sys.argv[1]]
    if module_names[0] == 'all':
        module_names = []
        for module_src_path in MODULE_SRC_PATHS:
            module_names += [os.path.basename(x)[:-4] 
                    for x in glob.glob(os.path.join(module_src_path,'Class*.cpp'))]

#    prj_file = 'ClassNeedle_0.prj'

    blocklist = set()
    with open('blocklist.csv',mode='r') as f:
        reader = csv.reader(f)
        for row in reader:
            if len(row) > 1:
                blocklist.add( (row[0],row[1]) )

    allowlist = set()
    with open('allowlist.csv',mode='r') as f:
        reader = csv.reader(f)
        for row in reader:
            if len(row) > 1:
                allowlist.add( (row[0],row[1]) )


    print(blocklist)

    for module_name in module_names:
        for proj_filepath in glob.glob(os.path.join(module_name,'*.prj' )):                
            filename = os.path.basename(proj_filepath)

            if filename == 'unit.prj':
                var_id = '-1'
            else:
                var_id = filename[8:-4]

            print((module_name,var_id))
            if (module_name,var_id) in blocklist:
                continue
            if (module_name,var_id) not in allowlist:
                continue

            success = run_test_success(proj_filepath)
            if not success:
                exit(1)

    exit(0)