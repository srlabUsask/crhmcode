#include "Classwinter_meltflag.h"
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
Classwinter_meltflag * Classwinter_meltflag :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classwinter_meltflag::klone(string name) const@@@Classwinter_meltflag.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classwinter_meltflag::klone(string name) const@@@Classwinter_meltflag.cpp>");
    return new Classwinter_meltflag (name);
InstrumentLogger::instance()->log_instrument_log("</Classwinter_meltflag::klone(string name) const@@@Classwinter_meltflag.cpp>");
}
void Classwinter_meltflag :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classwinter_meltflag::decl(void)@@@Classwinter_meltflag.cpp>");
    Description = "'Estimates the snow albedo during the winter and the melt period. Use with \"ebsm\".'";
    declvar ("meltflag", TDim :: NHRU, "meltflag = 1 - melt true", "()", & meltflag);
    declvar ("winter", TDim :: NHRU, "winter = 1 - true", "()", & winter);
    declparam ("hru_lat", TDim :: NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(" + string (DEGREE) + ")", & hru_lat);
    declgetvar ("*", "hru_tmax", "(" + string (DEGREE_CELSIUS) + ")", & hru_tmax);
    declgetvar ("*", "hru_tmin", "(" + string (DEGREE_CELSIUS) + ")", & hru_tmin);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "QdroD", "(MJ/m^2*d)", & QdroD);
    declgetvar ("*", "Albedo", "()", & Albedo);
InstrumentLogger::instance()->log_instrument_log("</Classwinter_meltflag::decl(void)@@@Classwinter_meltflag.cpp>");
}
void Classwinter_meltflag :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classwinter_meltflag::init(void)@@@Classwinter_meltflag.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        if (SWE [hh] > 5.0)
        {
            winter [hh] = 1;
        }

        else
        {
            winter [hh] = 0;
        }

        meltflag [hh] = 0;
    }
InstrumentLogger::instance()->log_instrument_log("</Classwinter_meltflag::init(void)@@@Classwinter_meltflag.cpp>");
}
void Classwinter_meltflag :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classwinter_meltflag::run(void)@@@Classwinter_meltflag.cpp>");
    long nstep, jday;
    nstep = getstep () % Global :: Freq;
    if (nstep == 0 || Global :: Freq == 1)
    {
        jday = julian ("now");
        for (hh = 0; chkStruct (); ++ hh) {
            double hemisphere = (hru_lat [hh] < 0.0);
            if ((! hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE [hh] > 5.0)
            {
                winter [hh] = 1;
            }

            continue;
        }
        for (hh = 0; chkStruct (); ++ hh) {
            meltflag [hh] = 0;
            if (SWE [hh] <= 0.0)
            {
                winter [hh] = 0;
                meltflag [hh] = 0;
            }

            else
            {
                double Qnc = - 0.371 + 5.22 * QdroD [hh] * (1 - Albedo [hh]);
                if (hru_tmax [hh] < - 6.0 && Qnc < 1.0)
                {
                    winter [hh] = 1;
                }

                if (winter [hh] == 1)
                {
                    double MT = - 0.064 * jday + 6.69;
                    if (hru_tmin [hh] > - 4.0 || Qnc > 1.0 && hru_tmax [hh] > 0.0 || hru_tmax [hh] > MT && Qnc > - 0.5)
                    {
                        meltflag [hh] = 1;
                    }

                }

                else
                {
                    meltflag [hh] = 1;
                }

            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</Classwinter_meltflag::run(void)@@@Classwinter_meltflag.cpp>");
}