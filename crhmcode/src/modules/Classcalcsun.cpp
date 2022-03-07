#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "Classcalcsun.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
Classcalcsun * Classcalcsun :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classcalcsun::klone(string name) const@@@Classcalcsun.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classcalcsun::klone(string name) const@@@Classcalcsun.cpp>");
    return new Classcalcsun (name);
InstrumentLogger::instance()->log_instrument_log("</Classcalcsun::klone(string name) const@@@Classcalcsun.cpp>");
}
void Classcalcsun :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classcalcsun::decl(void)@@@Classcalcsun.cpp>");
    Description = "'Calculates sunshine hours to replace field data', \
                 'Use actual sunshine hours or estimate from Qsi(W/m^2) when sunshine hours not available', \
                 'Use input Qsi (W/m^2) to estimate sunshine hours,' \
                 'Use input daily short-wave radiation observation(QsiD_Obs (W/m^2)), ' \
                 'Use input daily short-wave radiation variable (QsiD_Var (W/m^2)).'";
    variation_set = VARIATION_0;
    declreadobs ("SunAct", TDim :: NHRU, "sunshine hours", "(h)", & SunAct, HRU_OBS_Q, true);
    variation_set = VARIATION_0 + VARIATION_1;
    declreadobs ("Qsi", TDim :: NHRU, "incident short-wave", "(W/m^2)", & Qsi, HRU_OBS_Q, true);
    declobsfunc ("Qsi", "Qsitot", & Qsitot, TFun :: DTOT, NULL, true);
    variation_set = VARIATION_2;
    declreadobs ("QsiD_Obs", TDim :: NHRU, "daily short-wave", "(W/m^2)", & QsiD_Obs, HRU_OBS_Q);
    variation_set = VARIATION_3;
    declgetvar ("*", "QsiD_Var", "(W/m^2)", & QsiD_Var);
    variation_set = VARIATION_ORG;
    declgetvar ("*", "QdflatD", "(MJ/m^2*d)", & QdflatD);
    declgetvar ("*", "QdfoD", "(MJ/m^2*d)", & QdfoD);
    declgetvar ("*", "SunMax", "(h)", & SunMax);
    declvar ("hru_SunAct", TDim :: NHRU, "Actual Sunshine", "(h)", & hru_SunAct);
InstrumentLogger::instance()->log_instrument_log("</Classcalcsun::decl(void)@@@Classcalcsun.cpp>");
}
void Classcalcsun :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classcalcsun::init(void)@@@Classcalcsun.cpp>");
    nhru = getdim (TDim :: NHRU);
    switch (variation) {
    case VARIATION_ORG:
        if (SunAct == NULL)
        {
            CRHMException TExcept (string ("'" + Name + " (calcsun)' sunshine hours observation missing. Using Qsi instead.").c_str (), TExcept :: WARNING);
            LogError (TExcept);
            if (Qsi == NULL || Qsitot == NULL)
            {
                CRHMException TExcept (string ("'" + Name + " (calcsun)' Qsi interval observation missing.").c_str (), TExcept :: TERMINATE);
                LogError (TExcept);
            }

        }

        break;
    case VARIATION_1:
        if (Qsi == NULL || Qsitot == NULL)
        {
            CRHMException TExcept (string ("'" + Name + " (calcsun)' Qsi interval observation missing.").c_str (), TExcept :: TERMINATE);
            LogError (TExcept);
        }

        break;
    case VARIATION_2:
        if (QsiD_Obs == NULL)
        {
            CRHMException TExcept (string ("'" + Name + " (calcsun)' QsiD_Obs daily observation missing.").c_str (), TExcept :: TERMINATE);
            LogError (TExcept);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Classcalcsun::init(void)@@@Classcalcsun.cpp>");
}
void Classcalcsun :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classcalcsun::run(void)@@@Classcalcsun.cpp>");
    double Temp = - 9999;
    double Ratio;
    long nstep = getstep () % Global :: Freq;
    if (nstep == 1 || Global :: Freq == 1)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            switch (variation) {
            case VARIATION_ORG:
                if (SunAct)
                {
                    hru_SunAct [hh] = SunAct [hh];
                    Temp = - 9999;
                    break;
                }

            case VARIATION_1:
                Temp = Qsitot [hh] * WtoMJ_D / Global :: Freq - QdfoD [hh];
                break;
            case VARIATION_2:
                Temp = QsiD_Obs [hh] * WtoMJ_D - QdfoD [hh];
                break;
            case VARIATION_3:
                Temp = QsiD_Var [hh] * WtoMJ_D - QdfoD [hh];
                break;
            default:
                CRHMException TExcept (string ("'" + Name + " (variation)' 'variation not defined.").c_str (), TExcept :: TERMINATE);
                LogError (TExcept);
            }
            if (Temp != - 9999)
            {
                if (Temp <= 0.0 || QdflatD [hh] - QdfoD [hh] <= 0.0)
                {
                    Ratio = 0.0;
                }

                else
                {
                    Ratio = Temp / (QdflatD [hh] - QdfoD [hh]);
                    if (Ratio > 1.0)
                    {
                        Ratio = 1.0;
                    }

                }

                hru_SunAct [hh] = Ratio * SunMax [hh];
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</Classcalcsun::run(void)@@@Classcalcsun.cpp>");
}