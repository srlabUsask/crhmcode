#include "ClassGrow_crops_annually.h"
#include "../../core/InstrumentLogger.h"

ClassGrow_crops_annually * ClassGrow_crops_annually :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassGrow_crops_annually::klone(string name) const@@@ClassGrow_crops_annually.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::klone(string name) const@@@ClassGrow_crops_annually.cpp>");
    return new ClassGrow_crops_annually (name);
InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::klone(string name) const@@@ClassGrow_crops_annually.cpp>");
}
void ClassGrow_crops_annually :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGrow_crops_annually::decl(void)@@@ClassGrow_crops_annually.cpp>");
    Description = "'Misc modules.' \
                 'nothing,' \
                 'Hype fertilizer.'\
                 'Grow_crops.'\
                 'Both.'";
    variation_set = VARIATION_1 + VARIATION_3;
    declvar ("Fert_N_amount_up", TDim :: NHRU, "current hru N fertilizer amount", "(kg/km^2)", & Fert_N_amount_up);
    declvar ("Fert_P_amount_up", TDim :: NHRU, "current hru P fertilizer amount", "(kg/km^2)", & Fert_P_amount_up);
    declvar ("Man_N_amount_up", TDim :: NHRU, "current hru N manure amount", "(kg/km^2)", & Man_N_amount_up);
    declvar ("Man_P_amount_up", TDim :: NHRU, "current hru P manure amount", "(kg/km^2)", & Man_P_amount_up);
    declvar ("Res_N_amount_up", TDim :: NHRU, "current hru N residue amount", "(kg/km^2)", & Res_N_amount_up);
    declvar ("Res_P_amount_up", TDim :: NHRU, "current hru P residue amount", "(kg/km^2)", & Res_P_amount_up);
    declvar ("Fert_N_amount_down", TDim :: NHRU, "current hru N fertilizer amount", "(kg/km^2)", & Fert_N_amount_down);
    declvar ("Fert_P_amount_down", TDim :: NHRU, "current hru P fertilizer amount", "(kg/km^2)", & Fert_P_amount_down);
    declvar ("Man_N_amount_down", TDim :: NHRU, "current hru N manure amount", "(kg/km^2)", & Man_N_amount_down);
    declvar ("Man_P_amount_down", TDim :: NHRU, "current hru P manure amount", "(kg/km^2)", & Man_P_amount_down);
    declvar ("Res_N_amount_down", TDim :: NHRU, "current hru N residue amount", "(kg/km^2)", & Res_N_amount_down);
    declvar ("Res_P_amount_down", TDim :: NHRU, "current hru P residue amount", "(kg/km^2)", & Res_P_amount_down);
    declvar ("Fertperiod", TDim :: NHRU, "current period for spreading fertilizer and manure amount", "()", & Fertperiod);
    declvar ("Litterperiod", TDim :: NHRU, "current period for residue amount", "()", & Litterperiod);
    declvar ("LockOut", TDim :: NHRU, "prevents changes of fertilizer and manure amounts on multi day periods", "()", & LockOut);
    ObsCnt_N_up = declreadobs ("Fert_N_up", TDim :: NHRU, "annual N fertilizer dates and amount", "(kg/km^2)", & Fert_N_up, HRU_OBS_Q, true);
    ObsCnt_P_up = declreadobs ("Fert_P_up", TDim :: NHRU, "annual P fertilizer dates and amount", "(kg/km^2)", & Fert_P_up, HRU_OBS_Q, true);
    ObsCntMan_N_up = declreadobs ("Man_N_up", TDim :: NHRU, "annual N Manure dates and amount", "(kg/km^2)", & Man_N_up, HRU_OBS_Q, true);
    ObsCntMan_P_up = declreadobs ("Man_P_up", TDim :: NHRU, "annual P Manure dates and amount", "(kg/km^2)", & Man_P_up, HRU_OBS_Q, true);
    ObsCntRes_N_up = declreadobs ("Res_N_up", TDim :: NHRU, "annual N Residues dates and amount", "(kg/km^2)", & Res_N_up, HRU_OBS_Q, true);
    ObsCntRes_P_up = declreadobs ("Res_P_up", TDim :: NHRU, "annual P Residues dates and amount", "(kg/km^2)", & Res_P_up, HRU_OBS_Q, true);
    ObsCnt_N_down = declreadobs ("Fert_N_down", TDim :: NHRU, "annual N fertilizer dates and amount", "(kg/km^2)", & Fert_N_down, HRU_OBS_Q, true);
    ObsCnt_P_down = declreadobs ("Fert_P_down", TDim :: NHRU, "annual P fertilizer dates and amount", "(kg/km^2)", & Fert_P_down, HRU_OBS_Q, true);
    ObsCntMan_N_down = declreadobs ("Man_N_down", TDim :: NHRU, "annual N Manure dates and amount", "(kg/km^2)", & Man_N_down, HRU_OBS_Q, true);
    ObsCntMan_P_down = declreadobs ("Man_P_down", TDim :: NHRU, "annual P Manure dates and amount", "(kg/km^2)", & Man_P_down, HRU_OBS_Q, true);
    ObsCntRes_N_down = declreadobs ("Res_N_down", TDim :: NHRU, "annual N Residues dates and amount", "(kg/km^2)", & Res_N_down, HRU_OBS_Q, true);
    ObsCntRes_P_down = declreadobs ("Res_P_down", TDim :: NHRU, "annual P Residues dates and amount", "(kg/km^2)", & Res_P_down, HRU_OBS_Q, true);
    ObsCnt_fertperiod = declreadobs ("Fert_period", TDim :: NHRU, "spreading period for feritilzer and manure", "(d)", & Fert_period, HRU_OBS_Q, true);
    declparam ("Ag_YearStart", TDim :: NHRU, "[0]", "0", "10", " suggestions for northern hemisphere - 0, southern hemisphere - 183", "()", & Ag_YearStart);
    declputparam ("*", "fertNamount_up", "(kg/km^2)", & fertNamount_up);
    declputparam ("*", "fertNamount_down", "(kg/km^2)", & fertNamount_down);
    declputparam ("*", "fertPamount_up", "(kg/km^2)", & fertPamount_up);
    declputparam ("*", "fertPamount_down", "(kg/km^2)", & fertPamount_down);
    declputparam ("*", "manNamount_up", "(kg/km^2)", & manNamount_up);
    declputparam ("*", "manNamount_down", "(kg/km^2)", & manNamount_down);
    declputparam ("*", "manPamount_up", "(kg/km^2)", & manPamount_up);
    declputparam ("*", "manPamount_down", "(kg/km^2)", & manPamount_down);
    declputparam ("*", "resNamount_up", "(kg/km^2)", & resNamount_up);
    declputparam ("*", "resNamount_down", "(kg/km^2)", & resNamount_down);
    declputparam ("*", "resPamount_up", "(kg/km^2)", & resPamount_up);
    declputparam ("*", "resPamount_down", "(kg/km^2)", & resPamount_down);
    declputparam ("*", "fertday_up", "()", & fertday_up);
    declputparam ("*", "fertday_down", "()", & fertday_down);
    declputparam ("*", "manday_up", "()", & manday_up);
    declputparam ("*", "manday_down", "()", & manday_down);
    declputparam ("*", "resday_up", "()", & resday_up);
    declputparam ("*", "resday_down", "()", & resday_down);
    declputparam ("*", "fertperiod", "()", & fertperiod);
    declputparam ("*", "litterperiod", "()", & litterperiod);
    variation_set = VARIATION_2 + VARIATION_3;
    declparam ("Htmax", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "maximum vegetation height", "(m)", & Htmax);
    declparam ("Init_Crop_Ht_1", TDim :: NHRU, "[0.1]", "0.001", "100.0", "initial crop height (1)", "(m)", & Init_Crop_Ht_1);
    declparam ("Crop_Grow_Rate_1", TDim :: NHRU, "[0.8]", "0.0", "1.0", "crop growth rate (1)", "(m/d)", & Crop_Grow_Rate_1);
    declparam ("JCrop_Start_1", TDim :: NHRU, "[250]", "0", "366", "start Julian day (1); JCrop_Start_1 = 0 if no crop", "()", & JCrop_Start_1);
    declparam ("JCrop_Harvest_1", TDim :: NHRU, "[228]", "0", "366", "harvest Julian day (1); JCrop_Harvest_1 = 0 if no crop", "()", & JCrop_Harvest_1);
    declparam ("Crop_Htmax_1", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "maximum vegetation height (1)", "(m)", & Crop_Htmax_1);
    declparam ("Init_Crop_Ht_2", TDim :: NHRU, "[0.1]", "0.001", "100.0", "initial crop height (2)", "(m)", & Init_Crop_Ht_2);
    declparam ("Crop_Grow_Rate_2", TDim :: NHRU, "[0.8]", "0.0", "1.0", "crop growth rate (2)", "(m/d)", & Crop_Grow_Rate_2);
    declparam ("JCrop_Start_2", TDim :: NHRU, "[250]", "0", "366", "start Julian day (2); JCrop_Start_2 = 0 if no crop", "()", & JCrop_Start_2);
    declparam ("JCrop_Harvest_2", TDim :: NHRU, "[228]", "0", "366", "harvest Julian day (2); JCrop_Harvest_2 = 0 if no crop", "()", & JCrop_Harvest_2);
    declparam ("Crop_Htmax_2", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "maximum vegetation height (2)", "(m)", & Crop_Htmax_2);
    declputparam ("*", "Ht", "(m)", & Ht);
    variation_set = VARIATION_ORG;
InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::decl(void)@@@ClassGrow_crops_annually.cpp>");
}
void ClassGrow_crops_annually :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGrow_crops_annually::init(void)@@@ClassGrow_crops_annually.cpp>");
    nhru = getdim (TDim :: NHRU);
    if (variation == VARIATION_1 || variation == VARIATION_3)
    {
        if (ObsCnt_N_up > - 1)
        {
            CRHMException TExcept ("Handling N fertilizer from (Fert_N_up) observation.", TExcept :: WARNING);
            LogError (TExcept);
        }

        if (ObsCnt_P_up > - 1)
        {
            CRHMException TExcept ("Handling P fertilizer from (Fert_P_up) observation.", TExcept :: WARNING);
            LogError (TExcept);
        }

        if (ObsCntMan_N_up > - 1)
        {
            CRHMException TExcept ("Handling N manure from (Man_N_up) observation.", TExcept :: WARNING);
            LogError (TExcept);
        }

        if (ObsCntMan_P_up > - 1)
        {
            CRHMException TExcept ("Handling P manure from (Man_P_up) observation.", TExcept :: WARNING);
            LogError (TExcept);
        }

        if (ObsCntRes_N_up > - 1)
        {
            CRHMException TExcept ("Handling N residues from (Res_N_up) observation.", TExcept :: WARNING);
            LogError (TExcept);
        }

        if (ObsCntRes_P_up > - 1)
        {
            CRHMException TExcept ("Handling P residues from (Res_P_up) observation.", TExcept :: WARNING);
            LogError (TExcept);
        }

        if (ObsCnt_fertperiod > - 1)
        {
            CRHMException TExcept ("Handling fertilizer and manure period (Fert_period) observation.", TExcept :: WARNING);
            LogError (TExcept);
        }

        for (hh = 0; hh < nhru; ++ hh) {
            Fert_N_amount_up [hh] = 0.0;
            Fert_P_amount_up [hh] = 0.0;
            Man_N_amount_up [hh] = 0.0;
            Man_P_amount_up [hh] = 0.0;
            Fert_N_amount_down [hh] = 0.0;
            Fert_P_amount_down [hh] = 0.0;
            Man_N_amount_down [hh] = 0.0;
            Man_P_amount_down [hh] = 0.0;
            Res_N_amount_up [hh] = 0.0;
            Res_P_amount_up [hh] = 0.0;
            Fertperiod [hh] = 1;
            Litterperiod [hh] = 1;
            LockOut [hh] = 0;
        }
    }

    if (variation == VARIATION_2 || variation == VARIATION_3)
    {
        if (! Good_Dates (JCrop_Start_1))
        {
            CRHMException TExcept ("JCrop_Start_1 dates out of range!", TExcept :: TERMINATE);
            LogError (TExcept);
        }

        if (! Good_Dates (JCrop_Harvest_1))
        {
            CRHMException TExcept ("JCrop_Harvest_1 dates out of range!", TExcept :: TERMINATE);
            LogError (TExcept);
        }

        if (! Good_Dates (JCrop_Start_2))
        {
            CRHMException TExcept ("JCrop_Start_2 dates out of range!", TExcept :: TERMINATE);
            LogError (TExcept);
        }

        if (! Good_Dates (JCrop_Harvest_2))
        {
            CRHMException TExcept ("JCrop_Harvest_2 dates out of range!", TExcept :: TERMINATE);
            LogError (TExcept);
        }

        for (hh = 0; hh < nhru; ++ hh)
            const_cast < double * > (Ht) [hh] = Init_Crop_Ht_1 [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::init(void)@@@ClassGrow_crops_annually.cpp>");
}
void ClassGrow_crops_annually :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGrow_crops_annually::run(void)@@@ClassGrow_crops_annually.cpp>");
    long step = getstep ();
    long nstep = step % Global :: Freq;
    long today = julian ("now");
    bool Good_N, Good_P;
    if (step == 1)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            if (variation == VARIATION_1 || variation == VARIATION_3)
            {
                if (ObsCnt_N_up >= hh)
                {
                    declputparam ("*", "fertNamount_up", "(kg/km^2)", & fertNamount_up);
                    const_cast < double * > (fertNamount_up) [hh] = 0.0;
                }

                if (ObsCnt_P_up >= hh)
                {
                    declputparam ("*", "fertPamount_up", "(kg/km^2)", & fertPamount_up);
                    const_cast < double * > (fertPamount_up) [hh] = 0.0;
                }

                if (ObsCntMan_N_up >= hh)
                {
                    declputparam ("*", "manNamount_up", "(kg/km^2)", & manNamount_up);
                    const_cast < double * > (manNamount_up) [hh] = 0.0;
                }

                if (ObsCntMan_P_up >= hh)
                {
                    declputparam ("*", "manPamount_up", "(kg/km^2)", & manPamount_up);
                    const_cast < double * > (manPamount_up) [hh] = 0.0;
                }

                if (ObsCntRes_N_up >= hh)
                {
                    declputparam ("*", "resNamount_up", "(kg/km^2)", & resNamount_up);
                    const_cast < double * > (resNamount_up) [hh] = 0.0;
                }

                if (ObsCntRes_P_up >= hh)
                {
                    declputparam ("*", "resPamount_up", "(kg/km^2)", & resPamount_up);
                    const_cast < double * > (resPamount_up) [hh] = 0.0;
                }

                if (ObsCnt_N_up >= hh || ObsCnt_P_up >= hh)
                {
                    declputparam ("*", "fertday_up", "(d)", & fertday_up);
                    const_cast < double * > (fertday_up) [hh] = 0;
                }

                if (ObsCntMan_N_up >= hh || ObsCntMan_P_up >= hh)
                {
                    declputparam ("*", "manday_up", "(d)", & manday_up);
                    const_cast < double * > (manday_up) [hh] = 0;
                }

                if (ObsCnt_N_down >= hh)
                {
                    declputparam ("*", "fertNamount_down", "(kg/km^2)", & fertNamount_down);
                    const_cast < double * > (fertNamount_down) [hh] = 0.0;
                }

                if (ObsCnt_P_down >= hh)
                {
                    declputparam ("*", "fertPamount_down", "(kg/km^2)", & fertPamount_down);
                    const_cast < double * > (fertPamount_down) [hh] = 0.0;
                }

                if (ObsCntMan_N_down >= hh)
                {
                    declputparam ("*", "manNamount_down", "(kg/km^2)", & manNamount_down);
                    const_cast < double * > (manNamount_down) [hh] = 0.0;
                }

                if (ObsCntMan_P_down >= hh)
                {
                    declputparam ("*", "manPamount_down", "(kg/km^2)", & manPamount_down);
                    const_cast < double * > (manPamount_down) [hh] = 0.0;
                }

                if (ObsCntRes_N_down >= hh)
                {
                    declputparam ("*", "resNamount_down", "(kg/km^2)", & resNamount_down);
                    const_cast < double * > (resNamount_down) [hh] = 0.0;
                }

                if (ObsCntRes_P_down >= hh)
                {
                    declputparam ("*", "resPamount_down", "(kg/km^2)", & resPamount_down);
                    const_cast < double * > (resPamount_down) [hh] = 0.0;
                }

                if (ObsCnt_N_down >= hh || ObsCnt_P_down >= hh)
                {
                    declputparam ("*", "fertday_down", "(d)", & fertday_down);
                    const_cast < double * > (fertday_down) [hh] = 0;
                }

                if (ObsCntMan_N_down >= hh || ObsCntMan_P_down >= hh)
                {
                    declputparam ("*", "manday_down", "(d)", & manday_down);
                    const_cast < double * > (manday_down) [hh] = 0;
                }

                if (ObsCnt_fertperiod >= hh)
                {
                    declputparam ("*", "fertperiod", "(d)", & fertperiod);
                    const_cast < long * > (fertperiod) [hh] = 0;
                }

                declputparam ("*", "litterperiod", "(d)", & litterperiod);
            }

        }
    }

    if (nstep == 1)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            if (variation == VARIATION_1 || variation == VARIATION_3)
            {
                if (Ag_YearStart [hh] == today)
                {
                    fertday_up [hh] = 0;
                    fertday_down [hh] = 0;
                    manday_up [hh] = 0;
                    manday_down [hh] = 0;
                    resday_up [hh] = 0;
                    resday_down [hh] = 0;
                }

                -- LockOut [hh];
                if (LockOut [hh] <= 0)
                {
                    if (ObsCnt_fertperiod > 0)
                    {
                        if (! (Fert_period [hh] >= fLimit || ! Fert_period [hh]))
                        {
                            fertperiod [hh] = 1;
                            if (Fert_period [hh] > 1 && Fert_period [hh] < 366)
                            {
                                fertperiod [hh] = Fert_period [hh];
                            }

                            Fertperiod [hh] = Fert_period [hh];
                        }

                    }

                    else
                    {
                        Fertperiod [hh] = fertperiod [hh];
                    }

                    Good_N = true, Good_P = true;
                    if (ObsCnt_N_up >= hh || ObsCnt_P_up >= hh)
                    {
                        if (ObsCnt_N_up < 0 || Fert_N_up [hh] >= fLimit || ! Fert_N_up [hh] || Fert_N_up [hh] <= 0.0)
                        {
                            Fert_N_amount_up [hh] = 0.0;
                            fertNamount_up [hh] = 0.0;
                            Good_N = false;
                        }

                        if (ObsCnt_P_up < 0 || Fert_P_up [hh] >= fLimit || ! Fert_P_up [hh] || Fert_P_up [hh] <= 0.0)
                        {
                            Fert_P_amount_up [hh] = 0.0;
                            fertPamount_up [hh] = 0.0;
                            Good_P = false;
                        }

                        if (Good_N || Good_P)
                        {
                            LockOut [hh] = fertperiod [hh];
                            if (Good_N && Fert_N_up [hh] > 0.0)
                            {
                                fertNamount_up [hh] = Fert_N_up [hh] / Global :: Freq;
                                Fert_N_amount_up [hh] = fertNamount_up [hh];
                            }

                            if (Good_P && Fert_P_up [hh] > 0.0)
                            {
                                fertPamount_up [hh] = Fert_P_up [hh] / Global :: Freq;
                                Fert_P_amount_up [hh] = fertPamount_up [hh];
                            }

                            fertday_up [hh] = today;
                        }

                        else
                        {
                            fertday_up [hh] = 0;
                        }

                    }

                    Good_N = true, Good_P = true;
                    if (ObsCnt_N_down >= hh || ObsCnt_P_down >= hh)
                    {
                        if (ObsCnt_N_down < 0 || Fert_N_down [hh] >= fLimit || ! Fert_N_down [hh] || Fert_N_down [hh] <= 0.0)
                        {
                            Fert_N_amount_down [hh] = 0.0;
                            fertNamount_down [hh] = 0.0;
                            Good_N = false;
                        }

                        if (ObsCnt_P_down < 0 || Fert_P_down [hh] >= fLimit || ! Fert_P_down [hh] || Fert_P_down [hh] <= 0.0)
                        {
                            Fert_P_amount_down [hh] = 0.0;
                            fertPamount_down [hh] = 0.0;
                            Good_P = false;
                        }

                        if (Good_N || Good_P)
                        {
                            LockOut [hh] = fertperiod [hh];
                            if (Good_N && Fert_N_down [hh] > 0.0)
                            {
                                fertNamount_down [hh] = Fert_N_down [hh] / Global :: Freq;
                                Fert_N_amount_down [hh] = fertNamount_down [hh];
                            }

                            if (Good_P && Fert_P_down [hh] > 0.0)
                            {
                                fertPamount_down [hh] = Fert_P_down [hh] / Global :: Freq;
                                Fert_P_amount_down [hh] = fertPamount_down [hh];
                            }

                            fertday_down [hh] = today;
                        }

                        else
                        {
                            fertday_down [hh] = 0;
                        }

                    }

                    Good_N = true, Good_P = true;
                    if (ObsCntMan_N_up >= hh || ObsCntMan_P_up >= hh)
                    {
                        if (ObsCntMan_N_up < 0 || Man_N_up [hh] >= fLimit || ! Man_N_up [hh] || Man_N_up [hh] <= 0.0)
                        {
                            Man_N_amount_up [hh] = 0.0;
                            manNamount_up [hh] = 0.0;
                            Good_N = false;
                        }

                        if (ObsCntMan_P_up < 0 || Man_P_up [hh] >= fLimit || ! Man_P_up [hh] || Man_P_up [hh] <= 0.0)
                        {
                            Man_P_amount_up [hh] = 0.0;
                            manPamount_up [hh] = 0.0;
                            Good_P = false;
                        }

                        if (Good_N || Good_P)
                        {
                            LockOut [hh] = fertperiod [hh];
                            if (Good_N && Man_N_up [hh] > 0.0)
                            {
                                manNamount_up [hh] = Man_N_up [hh] / Global :: Freq;
                                Man_N_amount_up [hh] = manNamount_up [hh];
                            }

                            if (Good_P && Man_P_up [hh] > 0.0)
                            {
                                manPamount_up [hh] = Man_P_up [hh] / Global :: Freq;
                                Man_P_amount_up [hh] = manPamount_up [hh];
                            }

                            manday_up [hh] = today;
                        }

                        else
                        {
                            manday_up [hh] = 0;
                        }

                    }

                    Good_N = true, Good_P = true;
                    if (ObsCntMan_N_down >= hh || ObsCntMan_P_down >= hh)
                    {
                        if (ObsCntMan_N_down < 0 || Man_N_down [hh] >= fLimit || ! Man_N_down [hh] || Man_N_down [hh] <= 0.0)
                        {
                            Man_N_amount_down [hh] = 0.0;
                            manNamount_down [hh] = 0.0;
                            Good_N = false;
                        }

                        if (ObsCntMan_P_down < 0 || Man_P_down [hh] >= fLimit || ! Man_P_down [hh] || Man_P_down [hh] <= 0.0)
                        {
                            Man_P_amount_down [hh] = 0.0;
                            manPamount_down [hh] = 0.0;
                            Good_P = false;
                        }

                        if (Good_N || Good_P)
                        {
                            LockOut [hh] = fertperiod [hh];
                            if (Good_N && Man_N_down [hh] > 0.0)
                            {
                                manNamount_down [hh] = Man_N_down [hh] / Global :: Freq;
                                Man_N_amount_down [hh] = manNamount_down [hh];
                            }

                            if (Good_P && Man_P_down [hh] > 0.0)
                            {
                                manPamount_down [hh] = Man_P_down [hh] / Global :: Freq;
                                Man_P_amount_down [hh] = manPamount_down [hh];
                            }

                            manday_down [hh] = today;
                        }

                        else
                        {
                            manday_down [hh] = 0;
                        }

                    }

                    Good_N = true, Good_P = true;
                    if (ObsCntRes_N_up >= hh && ObsCntRes_P_up >= hh)
                    {
                        if (ObsCntRes_N_up < 0 || Res_N_up [hh] >= fLimit || ! Res_N_up [hh] || Res_N_up [hh] <= 0.0)
                        {
                            Res_N_amount_up [hh] = 0.0;
                            resNamount_up [hh] = 0.0;
                            Good_N = false;
                        }

                        if (ObsCntRes_P_up < 0 || Res_P_up [hh] >= fLimit || ! Res_P_up [hh] || Res_P_up [hh] <= 0.0)
                        {
                            Res_P_amount_up [hh] = 0.0;
                            resPamount_up [hh] = 0.0;
                            Good_P = false;
                        }

                        if (Good_N || Good_P)
                        {
                            LockOut [hh] = fertperiod [hh];
                            if (Good_N && Man_N_up [hh])
                            {
                                resNamount_up [hh] = Res_N_up [hh] / Global :: Freq;
                                Res_N_amount_up [hh] = Res_N_up [hh];
                            }

                            if (Good_P && Man_P_up [hh])
                            {
                                resPamount_up [hh] = Res_P_up [hh] / Global :: Freq;
                                Res_P_amount_up [hh] = Res_P_up [hh];
                            }

                            resday_up [hh] = today;
                        }

                        else
                        {
                            resday_up [hh] = 0;
                        }

                    }

                    Good_N = true, Good_P = true;
                    if (ObsCntRes_N_down >= hh && ObsCntRes_P_down >= hh)
                    {
                        if (ObsCntRes_N_down < 0 || Res_N_down [hh] >= fLimit || ! Res_N_down [hh] || Res_N_down [hh] <= 0.0)
                        {
                            Res_N_amount_down [hh] = 0.0;
                            resNamount_down [hh] = 0.0;
                            Good_N = false;
                        }

                        if (ObsCntRes_P_down < 0 || Res_P_down [hh] >= fLimit || ! Res_P_down [hh] || Res_P_down [hh] <= 0.0)
                        {
                            Res_P_amount_down [hh] = 0.0;
                            resPamount_down [hh] = 0.0;
                            Good_P = false;
                        }

                        if (Good_N || Good_P)
                        {
                            LockOut [hh] = fertperiod [hh];
                            if (Good_N && Man_N_down [hh])
                            {
                                resNamount_down [hh] = Res_N_down [hh] / Global :: Freq;
                                Res_N_amount_down [hh] = Res_N_down [hh];
                            }

                            if (Good_P && Man_P_down [hh])
                            {
                                resPamount_down [hh] = Res_P_down [hh] / Global :: Freq;
                                Res_P_amount_down [hh] = Res_P_up [hh];
                            }

                            resday_down [hh] = today;
                        }

                        else
                        {
                            resday_down [hh] = 0;
                        }

                    }

                }

            }

            if (variation == VARIATION_2 || variation == VARIATION_3)
            {
                if (today == JCrop_Start_1 [hh])
                {
                    const_cast < double * > (Ht) [hh] = Init_Crop_Ht_1 [hh];
                }

                if (JCrop_Start_1 [hh] != 0 && today >= JCrop_Start_1 [hh] && today <= JCrop_Harvest_1 [hh])
                {
                    const_cast < double * > (Htmax) [hh] = Crop_Htmax_1 [hh];
                }

                if (Ht [hh] < Crop_Htmax_1 [hh])
                {
                    const_cast < double * > (Ht) [hh] = Ht [hh] + Crop_Grow_Rate_1 [hh];
                }

                else
                {
                    const_cast < double * > (Ht) [hh] = Htmax [hh];
                }

                if (today == JCrop_Harvest_1 [hh])
                {
                    const_cast < double * > (Ht) [hh] = Init_Crop_Ht_1 [hh];
                }

                if (today == JCrop_Start_2 [hh])
                {
                    const_cast < double * > (Ht) [hh] = Init_Crop_Ht_2 [hh];
                }

                if (Ht [hh] < Crop_Htmax_2 [hh])
                {
                    const_cast < double * > (Ht) [hh] = Ht [hh] + Crop_Grow_Rate_2 [hh];
                }

                else
                {
                    const_cast < double * > (Ht) [hh] = Htmax [hh];
                }

                if (today == JCrop_Harvest_2 [hh])
                {
                    const_cast < double * > (Ht) [hh] = Init_Crop_Ht_2 [hh];
                }

            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::run(void)@@@ClassGrow_crops_annually.cpp>");
}
void ClassGrow_crops_annually :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGrow_crops_annually::finish(bool good)@@@ClassGrow_crops_annually.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogDebug (" ");
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::finish(bool good)@@@ClassGrow_crops_annually.cpp>");
}
bool ClassGrow_crops_annually :: Good_Dates (const double * dates)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGrow_crops_annually::Good_Dates(const double * dates)@@@ClassGrow_crops_annually.cpp>");
    for (hh = 0; hh < nhru; ++ hh) {
        if (dates [hh] > 366 || dates [hh] < 0)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::Good_Dates(const double * dates)@@@ClassGrow_crops_annually.cpp>");
            return false;
        }

        ;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::Good_Dates(const double * dates)@@@ClassGrow_crops_annually.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</ClassGrow_crops_annually::Good_Dates(const double * dates)@@@ClassGrow_crops_annually.cpp>");
}