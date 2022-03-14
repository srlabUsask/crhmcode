#include "Classnetall.h"
#include <algorithm>
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM/ClassCRHM.h"
#include "../newmodules/SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include "../../core/InstrumentLogger.h"

using namespace CRHM;
Classnetall * Classnetall :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classnetall::klone(string name) const@@@Classnetall.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classnetall::klone(string name) const@@@Classnetall.cpp>");
    return new Classnetall (name);
InstrumentLogger::instance()->log_instrument_log("</Classnetall::klone(string name) const@@@Classnetall.cpp>");
}
void Classnetall :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classnetall::decl(void)@@@Classnetall.cpp>");
    Description = "'Models net all-wave radiation (Rn, RnD and RnD_POS) from sunshine hours, temperature and humidity using Brunt.'";
    declvar ("net", TDim :: NHRU, "all-wave net", "(MJ/m^2*int)", & net);
    decldiag ("Rn", TDim :: NHRU, "all-wave net", "(mm/m^2*int)", & Rn);
    declvar ("netD", TDim :: NHRU, "all-wave net", "(MJ/m^2*d)", & netD);
    declvar ("RnD", TDim :: NHRU, "all-wave net", "(mm/m^2*d)", & RnD);
    decldiag ("RnD_POS", TDim :: NHRU, "Sum of Positive all-wave net", "(mm/m^2*d)", & RnD_POS);
    declstatdiag ("cum_net", TDim :: NHRU, "cumulative all-wave net", "(MJ/m^2)", & cum_net);
    declgetvar ("*", "hru_t", "(" + string (DEGREE_CELSIUS) + ")", & hru_t);
    declgetvar ("*", "hru_ea", "(kPa)", & hru_ea);
    declgetvar ("*", "hru_SunAct", "(h)", & hru_SunAct);
    declgetvar ("*", "Tday", "(" + string (DEGREE_CELSIUS) + ")", & NotUsed, & tday_intvls);
    declgetvar ("*", "EAday", "(kPa)", & NotUsed, & eaday_intvls);
    declgetvar ("*", "SunMax", "(h)", & SunMax);
    declgetvar ("*", "Qdro", "(W/m^2)", & Qdro);
    declgetvar ("*", "Qdfo", "(W/m^2)", & Qdfo);
    declgetvar ("*", "Albedo", "()", & Albedo);
    declgetvar ("*", "pQdro", "(MJ/m^2*int)", & pQdro, & pQdro_FREQ);
    declgetvar ("*", "pQdfo", "(MJ/m^2*int)", & pQdfo, & pQdfo_FREQ);
InstrumentLogger::instance()->log_instrument_log("</Classnetall::decl(void)@@@Classnetall.cpp>");
}
void Classnetall :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classnetall::init(void)@@@Classnetall.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh)
        cum_net [hh] = 0.0;
InstrumentLogger::instance()->log_instrument_log("</Classnetall::init(void)@@@Classnetall.cpp>");
}
void Classnetall :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classnetall::run(void)@@@Classnetall.cpp>");
    double netlong, shortw;
    long nstep = getstep () % Global :: Freq;
    if (nstep == 1 || Global :: Freq == 1)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            netD [hh] = 0.0;
            RnD [hh] = 0.0;
            RnD_POS [hh] = 0.0;
            for (int ff = 0; ff < Global :: Freq; ++ ff) {
                if (SunMax [hh] > 0.0)
                {
                    netlong = - 0.85 + 0.97 * CRHM_constants :: SB * pow (tday_intvls [ff] [hh] + 273.0f, 4) * (- 0.39f + 0.093f * sqrt (eaday_intvls [ff] [hh])) * (0.26f + 0.81f * (hru_SunAct [hh] / SunMax [hh]));
                }

                else
                {
                    netlong = - 0.85;
                }

                if (hru_SunAct [hh] > 0.0 && SunMax [hh] > 0.0)
                {
                    shortw = (0.024f + 0.974f * pow (hru_SunAct [hh] / SunMax [hh], 1.35f)) * pQdro_FREQ [ff] [hh] + (2.68f + 2.2f * (hru_SunAct [hh] / SunMax [hh]) - 3.85f * sqr (hru_SunAct [hh] / SunMax [hh])) * pQdfo_FREQ [ff] [hh];
                }

                else
                {
                    shortw = (0.024f * pQdro_FREQ [ff] [hh] + 2.68f * pQdfo_FREQ [ff] [hh]);
                }

                double Net = (shortw * (1.0f - Albedo [hh]) + netlong / Global :: Freq);
                netD [hh] += Net;
                Net = Net / (2.501f - 0.002361f * tday_intvls [ff] [hh]);
                RnD [hh] += Net;
                if (Net > 0.0)
                {
                    RnD_POS [hh] += Net;
                }

            }
        }
    }

    for (hh = 0; chkStruct (); ++ hh) {
        if (SunMax [hh] > 0.0)
        {
            netlong = - 0.85f + 0.97 * CRHM_constants :: SB * pow (hru_t [hh] + 273.0f, 4.0f) * (- 0.39f + 0.093f * sqrt (hru_ea [hh])) * (0.26f + 0.81f * (hru_SunAct [hh] / SunMax [hh]));
        }

        else
        {
            netlong = - 0.85;
        }

        if (hru_SunAct [hh] > 0.0 && SunMax [hh] > 0.0)
        {
            shortw = (0.024f + 0.974f * pow (hru_SunAct [hh] / SunMax [hh], 1.35f)) * Qdro [hh] * WtoMJ_D + (2.68f + 2.2f * (hru_SunAct [hh] / SunMax [hh]) - 3.85f * sqr (hru_SunAct [hh] / SunMax [hh])) * Qdfo [hh] * WtoMJ_D;
        }

        else
        {
            shortw = (0.024f * Qdro [hh] + 2.68f * Qdfo [hh]) * WtoMJ_D;
        }

        net [hh] = (shortw * (1.0f - Albedo [hh]) + netlong) / Global :: Freq;
        Rn [hh] = net [hh] / (2.501f - 0.002361f * hru_t [hh]);
        cum_net [hh] += net [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</Classnetall::run(void)@@@Classnetall.cpp>");
}