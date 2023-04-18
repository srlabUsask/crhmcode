/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
#include "ClassGrow_crops_annually.h"


ClassGrow_crops_annually* ClassGrow_crops_annually::klone(string name) const {
    return new ClassGrow_crops_annually(name);
}

void ClassGrow_crops_annually::decl(void) {

    Description = "'Misc modules.' \
                 'nothing,' \
                 'Hype fertilizer.'\
                 'Grow_crops.'\
                 'Both.'";

    // Hype parameters not affected fertdown1, fertdowd2, mandown1, mandown2, part, resfast and resdown

    variation_set = VARIATION_1 + VARIATION_3;

    declvar("Fert_N_amount_up", TDim::NHRU, "current hru N fertilizer amount", "(kg/km^2)", &Fert_N_amount_up);

    declvar("Fert_P_amount_up", TDim::NHRU, "current hru P fertilizer amount", "(kg/km^2)", &Fert_P_amount_up);

    declvar("Man_N_amount_up", TDim::NHRU, "current hru N manure amount", "(kg/km^2)", &Man_N_amount_up);

    declvar("Man_P_amount_up", TDim::NHRU, "current hru P manure amount", "(kg/km^2)", &Man_P_amount_up);

    declvar("Res_N_amount_up", TDim::NHRU, "current hru N residue amount", "(kg/km^2)", &Res_N_amount_up);

    declvar("Res_P_amount_up", TDim::NHRU, "current hru P residue amount", "(kg/km^2)", &Res_P_amount_up);

    declvar("Fert_N_amount_down", TDim::NHRU, "current hru N fertilizer amount", "(kg/km^2)", &Fert_N_amount_down);

    declvar("Fert_P_amount_down", TDim::NHRU, "current hru P fertilizer amount", "(kg/km^2)", &Fert_P_amount_down);

    declvar("Man_N_amount_down", TDim::NHRU, "current hru N manure amount", "(kg/km^2)", &Man_N_amount_down);

    declvar("Man_P_amount_down", TDim::NHRU, "current hru P manure amount", "(kg/km^2)", &Man_P_amount_down);

    declvar("Res_N_amount_down", TDim::NHRU, "current hru N residue amount", "(kg/km^2)", &Res_N_amount_down);

    declvar("Res_P_amount_down", TDim::NHRU, "current hru P residue amount", "(kg/km^2)", &Res_P_amount_down);

    declvar("Fertperiod", TDim::NHRU, "current period for spreading fertilizer and manure amount", "()", &Fertperiod);

    declvar("Litterperiod", TDim::NHRU, "current period for residue amount", "()", &Litterperiod);

    //declvar("Fertday", TDim::NHRU, "day to apply fertilizer", "()", &Fertday);

    //declvar("Manday", TDim::NHRU, "day to apply manure", "()", &Manday);

    //declvar("Resdayno", TDim::NHRU, "day to apply residue", "()", &Resdayno);

    declvar("LockOut", TDim::NHRU, "prevents changes of fertilizer and manure amounts on multi day periods", "()", &LockOut);

    //declvar("SecondDown_fert", TDim::NHRU, "second down", "()", &SecondDown_fert);

    //declvar("SecondDown_man", TDim::NHRU, "second down", "()", &SecondDown_man);

    ObsCnt_N_up = declreadobs("Fert_N_up", TDim::NHRU, "annual N fertilizer dates and amount", "(kg/km^2)", &Fert_N_up, HRU_OBS_Q, true);

    ObsCnt_P_up = declreadobs("Fert_P_up", TDim::NHRU, "annual P fertilizer dates and amount", "(kg/km^2)", &Fert_P_up, HRU_OBS_Q, true);

    ObsCntMan_N_up = declreadobs("Man_N_up", TDim::NHRU, "annual N Manure dates and amount", "(kg/km^2)", &Man_N_up, HRU_OBS_Q, true);

    ObsCntMan_P_up = declreadobs("Man_P_up", TDim::NHRU, "annual P Manure dates and amount", "(kg/km^2)", &Man_P_up, HRU_OBS_Q, true);

    ObsCntRes_N_up = declreadobs("Res_N_up", TDim::NHRU, "annual N Residues dates and amount", "(kg/km^2)", &Res_N_up, HRU_OBS_Q, true);

    ObsCntRes_P_up = declreadobs("Res_P_up", TDim::NHRU, "annual P Residues dates and amount", "(kg/km^2)", &Res_P_up, HRU_OBS_Q, true);

    ObsCnt_N_down = declreadobs("Fert_N_down", TDim::NHRU, "annual N fertilizer dates and amount", "(kg/km^2)", &Fert_N_down, HRU_OBS_Q, true);

    ObsCnt_P_down = declreadobs("Fert_P_down", TDim::NHRU, "annual P fertilizer dates and amount", "(kg/km^2)", &Fert_P_down, HRU_OBS_Q, true);

    ObsCntMan_N_down = declreadobs("Man_N_down", TDim::NHRU, "annual N Manure dates and amount", "(kg/km^2)", &Man_N_down, HRU_OBS_Q, true);

    ObsCntMan_P_down = declreadobs("Man_P_down", TDim::NHRU, "annual P Manure dates and amount", "(kg/km^2)", &Man_P_down, HRU_OBS_Q, true);

    ObsCntRes_N_down = declreadobs("Res_N_down", TDim::NHRU, "annual N Residues dates and amount", "(kg/km^2)", &Res_N_down, HRU_OBS_Q, true);

    ObsCntRes_P_down = declreadobs("Res_P_down", TDim::NHRU, "annual P Residues dates and amount", "(kg/km^2)", &Res_P_down, HRU_OBS_Q, true);

    ObsCnt_fertperiod = declreadobs("Fert_period", TDim::NHRU, "spreading period for feritilzer and manure", "(d)", &Fert_period, HRU_OBS_Q, true);


    declparam("Ag_YearStart", TDim::NHRU, "[0]", "0", "10", " suggestions for northern hemisphere - 0, southern hemisphere - 183", "()", &Ag_YearStart);

    declputparam("*", "fertNamount_up", "(kg/km^2)", &fertNamount_up);

    declputparam("*", "fertNamount_down", "(kg/km^2)", &fertNamount_down);

    declputparam("*", "fertPamount_up", "(kg/km^2)", &fertPamount_up);

    declputparam("*", "fertPamount_down", "(kg/km^2)", &fertPamount_down);

    declputparam("*", "manNamount_up", "(kg/km^2)", &manNamount_up);

    declputparam("*", "manNamount_down", "(kg/km^2)", &manNamount_down);

    declputparam("*", "manPamount_up", "(kg/km^2)", &manPamount_up);

    declputparam("*", "manPamount_down", "(kg/km^2)", &manPamount_down);

    declputparam("*", "resNamount_up", "(kg/km^2)", &resNamount_up);

    declputparam("*", "resNamount_down", "(kg/km^2)", &resNamount_down);

    declputparam("*", "resPamount_up", "(kg/km^2)", &resPamount_up);

    declputparam("*", "resPamount_down", "(kg/km^2)", &resPamount_down);

    declputparam("*", "fertday_up", "()", &fertday_up);

    declputparam("*", "fertday_down", "()", &fertday_down);

    declputparam("*", "manday_up", "()", &manday_up);

    declputparam("*", "manday_down", "()", &manday_down);

    declputparam("*", "resday_up", "()", &resday_up);

    declputparam("*", "resday_down", "()", &resday_down);

    declputparam("*", "fertperiod", "()", &fertperiod);

    declputparam("*", "litterperiod", "()", &litterperiod);

    variation_set = VARIATION_2 + VARIATION_3;

    declparam("Htmax", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "maximum vegetation height", "(m)", &Htmax);

    declparam("Init_Crop_Ht_1", TDim::NHRU, "[0.1]", "0.001", "100.0", "initial crop height (1)", "(m)", &Init_Crop_Ht_1);

    declparam("Crop_Grow_Rate_1", TDim::NHRU, "[0.8]", "0.0", "1.0", "crop growth rate (1)", "(m/d)", &Crop_Grow_Rate_1);

    declparam("JCrop_Start_1", TDim::NHRU, "[250]", "0", "366", "start Julian day (1); JCrop_Start_1 = 0 if no crop", "()", &JCrop_Start_1);

    declparam("JCrop_Harvest_1", TDim::NHRU, "[228]", "0", "366", "harvest Julian day (1); JCrop_Harvest_1 = 0 if no crop", "()", &JCrop_Harvest_1);

    declparam("Crop_Htmax_1", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "maximum vegetation height (1)", "(m)", &Crop_Htmax_1);

    declparam("Init_Crop_Ht_2", TDim::NHRU, "[0.1]", "0.001", "100.0", "initial crop height (2)", "(m)", &Init_Crop_Ht_2);

    declparam("Crop_Grow_Rate_2", TDim::NHRU, "[0.8]", "0.0", "1.0", "crop growth rate (2)", "(m/d)", &Crop_Grow_Rate_2);

    declparam("JCrop_Start_2", TDim::NHRU, "[250]", "0", "366", "start Julian day (2); JCrop_Start_2 = 0 if no crop", "()", &JCrop_Start_2);

    declparam("JCrop_Harvest_2", TDim::NHRU, "[228]", "0", "366", "harvest Julian day (2); JCrop_Harvest_2 = 0 if no crop", "()", &JCrop_Harvest_2);

    declparam("Crop_Htmax_2", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "maximum vegetation height (2)", "(m)", &Crop_Htmax_2);

    declputparam("*", "Ht", "(m)", &Ht);

    variation_set = VARIATION_ORG;

    declparam("disable_manfertres", TDim::NHRU, "[0]", "0", "1", "Disable manure,fertilization,residuals (false=0, true=1)", "()", &disable_manfertres);

}

void ClassGrow_crops_annually::init(void) {

    nhru = getdim(TDim::NHRU);

    if (variation == VARIATION_1 || variation == VARIATION_3) {
        if (ObsCnt_N_up > -1) {
            CRHMException TExcept("Handling N fertilizer from (Fert_N_up) observation.", TExcept::WARNING);
            LogError(TExcept);
        }

        if (ObsCnt_P_up > -1) {
            CRHMException TExcept("Handling P fertilizer from (Fert_P_up) observation.", TExcept::WARNING);
            LogError(TExcept);
        }

        if (ObsCntMan_N_up > -1) {
            CRHMException TExcept("Handling N manure from (Man_N_up) observation.", TExcept::WARNING);
            LogError(TExcept);
        }

        if (ObsCntMan_P_up > -1) {
            CRHMException TExcept("Handling P manure from (Man_P_up) observation.", TExcept::WARNING);
            LogError(TExcept);
        }

        if (ObsCntRes_N_up > -1) {
            CRHMException TExcept("Handling N residues from (Res_N_up) observation.", TExcept::WARNING);
            LogError(TExcept);
        }

        if (ObsCntRes_P_up > -1) {
            CRHMException TExcept("Handling P residues from (Res_P_up) observation.", TExcept::WARNING);
            LogError(TExcept);
        }

        if (ObsCnt_fertperiod > -1) {
            CRHMException TExcept("Handling fertilizer and manure period (Fert_period) observation.", TExcept::WARNING);
            LogError(TExcept);
        }

        for (hh = 0; hh < nhru; ++hh) {
            Fert_N_amount_up[hh] = 0.0;
            Fert_P_amount_up[hh] = 0.0;
            Man_N_amount_up[hh] = 0.0;
            Man_P_amount_up[hh] = 0.0;
            Fert_N_amount_down[hh] = 0.0;
            Fert_P_amount_down[hh] = 0.0;
            Man_N_amount_down[hh] = 0.0;
            Man_P_amount_down[hh] = 0.0;
            Res_N_amount_up[hh] = 0.0;
            Res_P_amount_up[hh] = 0.0;
            //Fertday[hh] = 0;
            //Manday[hh] = 0;
            //Resdayno[hh] = 0;
            Fertperiod[hh] = 1;
            Litterperiod[hh] = 1;
            LockOut[hh] = 0;
            //SecondDown_fert[hh] = 0;
            //SecondDown_man[hh] = 0;
        }
    } // VARIATION_1

    if (variation == VARIATION_2 || variation == VARIATION_3) {

        if (!Good_Dates(JCrop_Start_1)) {
            CRHMException TExcept("JCrop_Start_1 dates out of range!", TExcept::TERMINATE);
            LogError(TExcept);
        }

        if (!Good_Dates(JCrop_Harvest_1)) {
            CRHMException TExcept("JCrop_Harvest_1 dates out of range!", TExcept::TERMINATE);
            LogError(TExcept);
        }

        if (!Good_Dates(JCrop_Start_2)) {
            CRHMException TExcept("JCrop_Start_2 dates out of range!", TExcept::TERMINATE);
            LogError(TExcept);
        }

        if (!Good_Dates(JCrop_Harvest_2)) {
            CRHMException TExcept("JCrop_Harvest_2 dates out of range!", TExcept::TERMINATE);
            LogError(TExcept);
        }
        for (hh = 0; hh < nhru; ++hh)
            const_cast<double*> (Ht)[hh] = Init_Crop_Ht_1[hh];
    } // VARIATION_2
}

void ClassGrow_crops_annually::run(void) {

    long step = getstep();
    long nstep = step % Global::Freq;
    long today = julian("now");
    bool Good_N, Good_P;

    if (step == 1) { // first step of run. Main saves all parameters after INIT entries are executed. Parameters are restored at end of RUN.
        for (hh = 0; chkStruct(); ++hh) {
            if (variation == VARIATION_1 || variation == VARIATION_3) {
                if (ObsCnt_N_up >= hh) { // file open
                    declputparam("*", "fertNamount_up", "(kg/km^2)", &fertNamount_up);
                    const_cast<double*> (fertNamount_up)[hh] = 0.0; // set by module
                }
                if (ObsCnt_P_up >= hh) { // file open
                    declputparam("*", "fertPamount_up", "(kg/km^2)", &fertPamount_up);
                    const_cast<double*> (fertPamount_up)[hh] = 0.0; // set by module
                }
                if (ObsCntMan_N_up >= hh) { // file open
                    declputparam("*", "manNamount_up", "(kg/km^2)", &manNamount_up);
                    const_cast<double*> (manNamount_up)[hh] = 0.0; // set by module
                }
                if (ObsCntMan_P_up >= hh) { // file open
                    declputparam("*", "manPamount_up", "(kg/km^2)", &manPamount_up);
                    const_cast<double*> (manPamount_up)[hh] = 0.0; // not used
                }
                if (ObsCntRes_N_up >= hh) { // file open
                    declputparam("*", "resNamount_up", "(kg/km^2)", &resNamount_up);
                    const_cast<double*> (resNamount_up)[hh] = 0.0;  // set by this module
                }
                if (ObsCntRes_P_up >= hh) { // file open
                    declputparam("*", "resPamount_up", "(kg/km^2)", &resPamount_up);
                    const_cast<double*> (resPamount_up)[hh] = 0.0;  // set by this module
                }
                if (ObsCnt_N_up >= hh || ObsCnt_P_up >= hh) { // file open
                    declputparam("*", "fertday_up", "(d)", &fertday_up);
                    const_cast<double*> (fertday_up)[hh] = 0; // set by this module
                }
                if (ObsCntMan_N_up >= hh || ObsCntMan_P_up >= hh) { // file open
                    declputparam("*", "manday_up", "(d)", &manday_up);
                    const_cast<double*> (manday_up)[hh] = 0; // set by this module
                }
                if (ObsCnt_N_down >= hh) { // file open
                    declputparam("*", "fertNamount_down", "(kg/km^2)", &fertNamount_down);
                    const_cast<double*> (fertNamount_down)[hh] = 0.0; // set by module
                }
                if (ObsCnt_P_down >= hh) { // file open
                    declputparam("*", "fertPamount_down", "(kg/km^2)", &fertPamount_down);
                    const_cast<double*> (fertPamount_down)[hh] = 0.0; // set by module
                }
                if (ObsCntMan_N_down >= hh) { // file open
                    declputparam("*", "manNamount_down", "(kg/km^2)", &manNamount_down);
                    const_cast<double*> (manNamount_down)[hh] = 0.0; // set by module
                }
                if (ObsCntMan_P_down >= hh) { // file open
                    declputparam("*", "manPamount_down", "(kg/km^2)", &manPamount_down);
                    const_cast<double*> (manPamount_down)[hh] = 0.0; // not used
                }
                if (ObsCntRes_N_down >= hh) { // file open
                    declputparam("*", "resNamount_down", "(kg/km^2)", &resNamount_down);
                    const_cast<double*> (resNamount_down)[hh] = 0.0;  // set by this module
                }
                if (ObsCntRes_P_down >= hh) { // file open
                    declputparam("*", "resPamount_down", "(kg/km^2)", &resPamount_down);
                    const_cast<double*> (resPamount_down)[hh] = 0.0;  // set by this module
                }
                if (ObsCnt_N_down >= hh || ObsCnt_P_down >= hh) { // file open
                    declputparam("*", "fertday_down", "(d)", &fertday_down);
                    const_cast<double*> (fertday_down)[hh] = 0; // set by this module
                }
                if (ObsCntMan_N_down >= hh || ObsCntMan_P_down >= hh) { // file open
                    declputparam("*", "manday_down", "(d)", &manday_down);
                    const_cast<double*> (manday_down)[hh] = 0; // set by this module
                }
                if (ObsCnt_fertperiod >= hh) { // file open
                    declputparam("*", "fertperiod", "(d)", &fertperiod);
                    const_cast<long*> (fertperiod)[hh] = 0; // set by this module
                }
                //        if(ObsCnt_litterperiod >= hh){ // file open  check ????
                declputparam("*", "litterperiod", "(d)", &litterperiod);
                //          const_cast<double *> (litterperiod)[hh] = 0; // set by module
                //        }
            } // VARIATION_1 or VARIATION_3
        } // for hh
    } // first step of run

    if (nstep == 1) { // beginning of every day
        for (hh = 0; chkStruct(); ++hh) {
            if (variation == VARIATION_1 || variation == VARIATION_3) {
                if (disable_manfertres[hh])
                    continue;

                if (Ag_YearStart[hh] == today) {
                    //SecondDown_fert[hh] = 0;
                    //SecondDown_man[hh] = 0;
                    fertday_up[hh] = 0;
                    fertday_down[hh] = 0;
                    manday_up[hh] = 0;
                    manday_down[hh] = 0;
                    resday_up[hh] = 0;
                    resday_down[hh] = 0;
                }
                --LockOut[hh];
                if (LockOut[hh] <= 0) {
                    if (ObsCnt_fertperiod > 0) { // file open
                        if (!(Fert_period[hh] >= fLimit || !Fert_period[hh])) {
                            fertperiod[hh] = 1;
                            if (Fert_period[hh] > 1 && Fert_period[hh] < 366) {
                                fertperiod[hh] = Fert_period[hh];
                            }
                            Fertperiod[hh] = Fert_period[hh];
                        }
                    } // file open
                    else
                        Fertperiod[hh] = fertperiod[hh];

                    Good_N = true, Good_P = true;
                    if (ObsCnt_N_up >= hh || ObsCnt_P_up >= hh) { // either file open
                        if (ObsCnt_N_up < 0 || Fert_N_up[hh] >= fLimit || !Fert_N_up[hh] || Fert_N_up[hh] <= 0.0) {
                            Fert_N_amount_up[hh] = 0.0; // set to all zeros
                            //Fert_N_amount_down[hh] = 0.0; // set to all zeros
                            fertNamount_up[hh] = 0.0; // set to all zeros
                            //fertNamount_down[hh] = 0.0; // set to all zeros
                            Good_N = false;
                        }
                        if (ObsCnt_P_up < 0 || Fert_P_up[hh] >= fLimit || !Fert_P_up[hh] || Fert_P_up[hh] <= 0.0) {
                            Fert_P_amount_up[hh] = 0.0; // set to all zeros
                            //Fert_P_amount_down[hh] = 0.0; // set to all zeros
                            fertPamount_up[hh] = 0.0; // set to all zeros
                            //fertPamount_down[hh] = 0.0; // set to all zeros
                            Good_P = false;
                        }
                        if (Good_N || Good_P) {
                            LockOut[hh] = fertperiod[hh];
                            //if(!SecondDown_fert[hh]){
                            if (Good_N && Fert_N_up[hh] > 0.0) {
                                fertNamount_up[hh] = Fert_N_up[hh] / Global::Freq; // set to interval values given
                                Fert_N_amount_up[hh] = fertNamount_up[hh];
                            }
                            if (Good_P && Fert_P_up[hh] > 0.0) {
                                fertPamount_up[hh] = Fert_P_up[hh] / Global::Freq; // set to interval values given
                                Fert_P_amount_up[hh] = fertPamount_up[hh];
                            }
                            fertday_up[hh] = today;
                            //Fertday[hh] = today;
                            //SecondDown_fert[hh] = 1;
                          //}
                          //else{
                          //  fertNamount_up[hh] = 0.0;
                          //  fertPamount_up[hh] = 0.0;
                          //  Fert_N_amount_up[hh] = 0.0; // set to all zeros
                          //  Fert_P_amount_up[hh] = 0.0; // set to all zeros
                          //  if(Good_N && Fert_N_up[hh] > 0.0){
                          //    fertNamount_down[hh] = Fert_N_up[hh]/Global::Freq; // set to interval values given
                          //    Fert_N_amount_down[hh] = fertNamount_down[hh];
                          //  }
                          //  if(Good_P && Fert_P_up[hh] > 0.0){
                          //    fertPamount_down[hh] = Fert_P_up[hh]/Global::Freq; // set to interval values given
                          //    Fert_P_amount_down[hh] = fertPamount_down[hh];
                          //  }
                          //  fertday_up[hh] = 0;
                          //  fertday_down[hh] = today;
                          //  Fertday[hh] = today;
                          //  SecondDown_fert[hh] = 0;
                          //}
                        } // fertN or P > 0.0
                        else {
                            fertday_up[hh] = 0;
                            //fertday_down[hh] = 0;
                            //Fertday[hh] = 0;
                        }
                    } // file open

                    Good_N = true, Good_P = true;
                    if (ObsCnt_N_down >= hh || ObsCnt_P_down >= hh) { // either file open
                        if (ObsCnt_N_down < 0 || Fert_N_down[hh] >= fLimit || !Fert_N_down[hh] || Fert_N_down[hh] <= 0.0) {
                            Fert_N_amount_down[hh] = 0.0; // set to all zeros
                            fertNamount_down[hh] = 0.0; // set to all zeros
                            Good_N = false;
                        }
                        if (ObsCnt_P_down < 0 || Fert_P_down[hh] >= fLimit || !Fert_P_down[hh] || Fert_P_down[hh] <= 0.0) {
                            Fert_P_amount_down[hh] = 0.0; // set to all zeros
                            fertPamount_down[hh] = 0.0; // set to all zeros
                            Good_P = false;
                        }
                        if (Good_N || Good_P) {
                            LockOut[hh] = fertperiod[hh];
                            if (Good_N && Fert_N_down[hh] > 0.0) {
                                fertNamount_down[hh] = Fert_N_down[hh] / Global::Freq; // set to interval values given
                                Fert_N_amount_down[hh] = fertNamount_down[hh];
                            }
                            if (Good_P && Fert_P_down[hh] > 0.0) {
                                fertPamount_down[hh] = Fert_P_down[hh] / Global::Freq; // set to interval values given
                                Fert_P_amount_down[hh] = fertPamount_down[hh];
                            }
                            fertday_down[hh] = today;
                            //Fertday[hh] = today;
                        }
                        else {
                            fertday_down[hh] = 0;
                            //[hh] = 0;
                        }
                    } // file open

                    Good_N = true, Good_P = true;
                    if (ObsCntMan_N_up >= hh || ObsCntMan_P_up >= hh) { // file open
                        if (ObsCntMan_N_up < 0 || Man_N_up[hh] >= fLimit || !Man_N_up[hh] || Man_N_up[hh] <= 0.0) {
                            Man_N_amount_up[hh] = 0.0; // set to all zeros
                            //Man_N_amount_down[hh] = 0.0; // set to all zeros
                            manNamount_up[hh] = 0.0; // set to all zeros
                            //manNamount_down[hh] = 0.0; // set to all zeros
                            Good_N = false;
                        }
                        if (ObsCntMan_P_up < 0 || Man_P_up[hh] >= fLimit || !Man_P_up[hh] || Man_P_up[hh] <= 0.0) {
                            Man_P_amount_up[hh] = 0.0; // set to all zeros
                            //Man_P_amount_down[hh] = 0.0; // set to all zeros
                            manPamount_up[hh] = 0.0; // set to all zeros
                            //manPamount_down[hh] = 0.0; // set to all zeros
                            Good_P = false;
                        }
                        if (Good_N || Good_P) {
                            LockOut[hh] = fertperiod[hh];
                            //if(!SecondDown_man[hh]){
                            if (Good_N && Man_N_up[hh] > 0.0) {
                                manNamount_up[hh] = Man_N_up[hh] / Global::Freq; // set to interval values given
                                Man_N_amount_up[hh] = manNamount_up[hh];
                            }
                            if (Good_P && Man_P_up[hh] > 0.0) {
                                manPamount_up[hh] = Man_P_up[hh] / Global::Freq; // set to interval values given
                                Man_P_amount_up[hh] = manPamount_up[hh];
                            }
                            manday_up[hh] = today;
                            //Manday[hh] = today;
                        //    SecondDown_man[hh] = 1;
                        //  }
                        //  else{
                        //    manNamount_up[hh] = 0.0; // set to all zeros
                        //    manPamount_up[hh] = 0.0; // set to all zeros
                        //    Man_N_amount_up[hh] = 0.0; // set to all zeros
                        //    Man_P_amount_up[hh] = 0.0; // set to all zeros
                        //    if(Good_N && Man_N_up[hh]){
                        //      manNamount_down[hh] = Man_N_up[hh]/Global::Freq; // set to interval values given
                        //      Man_N_amount_down[hh] = manNamount_down[hh];
                        //    }
                        //    if(Good_P && Man_P_up[hh]){
                        //      manPamount_down[hh] = Man_P_up[hh]/Global::Freq; // set to interval values given
                        //      Man_P_amount_down[hh] = manPamount_down[hh];
                        //    }
                        //    manday_up[hh] = 0;
                        //    manday_down[hh] = today;
                        //    Manday[hh] = today;
                        //    SecondDown_man[hh] = 0;
                        // }
                        } // manNamount_up > 0.0
                        else {
                            manday_up[hh] = 0;
                            //manday_down[hh] = 0;
                            //Manday[hh] = 0;
                        }
                    } // read amount from open file

                    Good_N = true, Good_P = true;
                    if (ObsCntMan_N_down >= hh || ObsCntMan_P_down >= hh) { // file open
                        if (ObsCntMan_N_down < 0 || Man_N_down[hh] >= fLimit || !Man_N_down[hh] || Man_N_down[hh] <= 0.0) {
                            Man_N_amount_down[hh] = 0.0; // set to all zeros
                            manNamount_down[hh] = 0.0; // set to all zeros
                            Good_N = false;
                        }
                        if (ObsCntMan_P_down < 0 || Man_P_down[hh] >= fLimit || !Man_P_down[hh] || Man_P_down[hh] <= 0.0) {
                            Man_P_amount_down[hh] = 0.0; // set to all zeros
                            manPamount_down[hh] = 0.0; // set to all zeros
                            Good_P = false;
                        }
                        if (Good_N || Good_P) {
                            LockOut[hh] = fertperiod[hh];
                            if (Good_N && Man_N_down[hh] > 0.0) {
                                manNamount_down[hh] = Man_N_down[hh] / Global::Freq; // set to interval values given
                                Man_N_amount_down[hh] = manNamount_down[hh];
                            }
                            if (Good_P && Man_P_down[hh] > 0.0) {
                                manPamount_down[hh] = Man_P_down[hh] / Global::Freq; // set to interval values given
                                Man_P_amount_down[hh] = manPamount_down[hh];
                            }
                            manday_down[hh] = today;
                            //Manday[hh] = today;
                        } // manNamount_down > 0.0
                        else {
                            manday_down[hh] = 0;
                            //Manday[hh] = 0;
                        }
                    } // read amount from open file


                    Good_N = true, Good_P = true;
                    if (ObsCntRes_N_up >= hh && ObsCntRes_P_up >= hh) { // file open
                        if (ObsCntRes_N_up < 0 || Res_N_up[hh] >= fLimit || !Res_N_up[hh] || Res_N_up[hh] <= 0.0) {
                            Res_N_amount_up[hh] = 0.0; // set to all zeros
                            resNamount_up[hh] = 0.0;
                            Good_N = false;
                        }
                        if (ObsCntRes_P_up < 0 || Res_P_up[hh] >= fLimit || !Res_P_up[hh] || Res_P_up[hh] <= 0.0) {
                            Res_P_amount_up[hh] = 0.0; // set to all zeros
                            resPamount_up[hh] = 0.0;
                            Good_P = false;
                        }
                        if (Good_N || Good_P) {
                            LockOut[hh] = fertperiod[hh];
                            if (Good_N && Man_N_up[hh]) {
                                resNamount_up[hh] = Res_N_up[hh] / Global::Freq; // set to interval values given
                                Res_N_amount_up[hh] = Res_N_up[hh]; // set to interval values given
                            }
                            if (Good_P && Man_P_up[hh]) {
                                resPamount_up[hh] = Res_P_up[hh] / Global::Freq; // set to interval values given
                                Res_P_amount_up[hh] = Res_P_up[hh]; // set to interval values given
                            }
                            resday_up[hh] = today;
                            //Resdayno[hh] = today;
                        } // resNamount1 > 0.0
                        else {
                            resday_up[hh] = 0;
                            //Resdayno[hh] = 0;
                        }
                    } // file open

                    Good_N = true, Good_P = true;
                    if (ObsCntRes_N_down >= hh && ObsCntRes_P_down >= hh) { // file open
                        if (ObsCntRes_N_down < 0 || Res_N_down[hh] >= fLimit || !Res_N_down[hh] || Res_N_down[hh] <= 0.0) {
                            Res_N_amount_down[hh] = 0.0; // set to all zeros
                            resNamount_down[hh] = 0.0;
                            Good_N = false;
                        }
                        if (ObsCntRes_P_down < 0 || Res_P_down[hh] >= fLimit || !Res_P_down[hh] || Res_P_down[hh] <= 0.0) {
                            Res_P_amount_down[hh] = 0.0; // set to all zeros
                            resPamount_down[hh] = 0.0;
                            Good_P = false;
                        }
                        if (Good_N || Good_P) {
                            LockOut[hh] = fertperiod[hh];
                            if (Good_N && Man_N_down[hh]) {
                                resNamount_down[hh] = Res_N_down[hh] / Global::Freq; // set to interval values given
                                Res_N_amount_down[hh] = Res_N_down[hh]; // set to interval values given
                            }
                            if (Good_P && Man_P_down[hh]) {
                                resPamount_down[hh] = Res_P_down[hh] / Global::Freq; // set to interval values given
                                Res_P_amount_down[hh] = Res_P_up[hh]; // set to interval values given
                            }
                            resday_down[hh] = today;
                            //Resdayno[hh] = today;
                        } // resNamount1 > 0.0
                        else {
                            resday_down[hh] = 0;
                            //Resdayno[hh] = 0;
                        }
                    } // file open

                } // lockout
            } // VARIATION_1 or VARIATION_3

            if (variation == VARIATION_2 || variation == VARIATION_3) {
                if (today == JCrop_Start_1[hh])
                    const_cast<double*> (Ht)[hh] = Init_Crop_Ht_1[hh];

                if (JCrop_Start_1[hh] != 0 && today >= JCrop_Start_1[hh] && today <= JCrop_Harvest_1[hh])
                    const_cast<double*> (Htmax)[hh] = Crop_Htmax_1[hh];

                if (Ht[hh] < Crop_Htmax_1[hh])
                    const_cast<double*> (Ht)[hh] = Ht[hh] + Crop_Grow_Rate_1[hh];
                else
                    const_cast<double*> (Ht)[hh] = Htmax[hh];

                if (today == JCrop_Harvest_1[hh])
                    const_cast<double*> (Ht)[hh] = Init_Crop_Ht_1[hh];

                if (today == JCrop_Start_2[hh])
                    const_cast<double*> (Ht)[hh] = Init_Crop_Ht_2[hh];

                if (Ht[hh] < Crop_Htmax_2[hh])
                    const_cast<double*> (Ht)[hh] = Ht[hh] + Crop_Grow_Rate_2[hh];
                else
                    const_cast<double*> (Ht)[hh] = Htmax[hh];

                if (today == JCrop_Harvest_2[hh])
                    const_cast<double*> (Ht)[hh] = Init_Crop_Ht_2[hh];
            } // VARIATION_2 or VARIATION_3
        } // for hh
    } // start of day
}

void ClassGrow_crops_annually::finish(bool good) {

    for (hh = 0; chkStruct(); ++hh) {
        //    LogMessageA(hh, string("'" + Name + " (Grow_crops_annually)'  cumnetrain  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
    }
    LogDebug(" ");
}

bool ClassGrow_crops_annually::Good_Dates(const double* dates) {

    for (hh = 0; hh < nhru; ++hh) {
        if (dates[hh] > 366 || dates[hh] < 0) {
            return false; // error
        };
    }
    return true;
}