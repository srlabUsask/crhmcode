#include "Classalbedoobs2.h"
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
Classalbedoobs2 * Classalbedoobs2 :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs2::klone(string name) const@@@Classalbedoobs2.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs2::klone(string name) const@@@Classalbedoobs2.cpp>");
    return new Classalbedoobs2 (name);
InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs2::klone(string name) const@@@Classalbedoobs2.cpp>");
}
void Classalbedoobs2 :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs2::decl(void)@@@Classalbedoobs2.cpp>");
    Description = "'Every interval sets the variable Albedo to the value of the observation Albedo_obs with enhancements.'";
    declstatvar ("Albedo", TDim :: NHRU, "Albedo()", "()", & Albedo);
    declvar ("meltflag", TDim :: NHRU, "meltflag = 1 - melt true", "()", & meltflag);
    declvar ("winter", TDim :: NHRU, "winter = 1 - true", "()", & winter);
    declvar ("net_snowD", TDim :: NHRU, "daily snow fall", "(mm/d)", & net_snowD);
    declvar ("newsnowcnt", TDim :: NHRU, "snow age count", "()", & newsnowcnt);
    decldiagparam ("Albedo_bare", TDim :: NHRU, "[0.17]", "0.0", "1.0", "albedo for bare ground", "()", & Albedo_bare);
    decldiagparam ("Albedo_snow", TDim :: NHRU, "[0.85]", "0.0", "1.0", "albedo for fresh snow covered ground", "()", & Albedo_snow);
    declparam ("hru_lat", TDim :: NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(" + string (DEGREE) + ")", & hru_lat);
    declreadobs ("Albedo_obs", TDim :: NHRU, "albedo observation", "()", & Albedo_obs, HRU_OBS_Q, true);
    declgetvar ("*", "hru_tmax", "(" + string (DEGREE_CELSIUS) + ")", & hru_tmax);
    declgetvar ("*", "hru_tmin", "(" + string (DEGREE_CELSIUS) + ")", & hru_tmin);
    declgetvar ("*", "hru_newsnow", "()", & hru_newsnow);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "QdroD", "(MJ/m^2*d)", & QdroD);
    declgetvar ("*", "net_snow", "(mm/int)", & net_snow);
InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs2::decl(void)@@@Classalbedoobs2.cpp>");
}
void Classalbedoobs2 :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs2::init(void)@@@Classalbedoobs2.cpp>");
    nhru = getdim (TDim :: NHRU);
    if (Albedo_obs == NULL)
    {
        CRHMException TExcept ("\"albedo_obs\". No observation albedo data!  Using calculated albedo instead.", TExcept :: WARNING);
        LogError (TExcept);
    }

    else
    {
        CRHMException TExcept ("\"albedo_obs\". Using observation albedo data!.", TExcept :: WARNING);
        LogError (TExcept);
    }

    for (hh = 0; hh < nhru; ++ hh) {
        if (SWE [hh] > 5.0)
        {
            Albedo [hh] = Albedo_snow [hh];
            winter [hh] = 1;
        }

        else
        {
            Albedo [hh] = Albedo_bare [hh];
            winter [hh] = 0;
        }

        net_snowD [hh] = 0.0;
        meltflag [hh] = 0;
        newsnowcnt [hh] = 0;
    }
InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs2::init(void)@@@Classalbedoobs2.cpp>");
}
void Classalbedoobs2 :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs2::run(void)@@@Classalbedoobs2.cpp>");
    long nstep, jday;
    nstep = getstep () % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
        if (nstep == 1 || Global :: Freq == 1)
        {
            net_snowD [hh] = net_snow [hh];
        }

        else
        {
            net_snowD [hh] += net_snow [hh];
        }

    }
    if (nstep == 0 || Global :: Freq == 1)
    {
        jday = julian ("now");
        for (hh = 0; chkStruct (); ++ hh) {
            double hemisphere = (hru_lat [hh] < 0.0);
            if ((! hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE [hh] > 5.0)
            {
                winter [hh] = 1;
                Albedo [hh] = Albedo_snow [hh];
            }

        }
        for (hh = 0; chkStruct (); ++ hh) {
            meltflag [hh] = 0;
            if (hru_newsnow [hh] > 0)
            {
                newsnowcnt [hh] = 0;
            }

            else
            {
                newsnowcnt [hh] = newsnowcnt [hh] + 1;
            }

            if (SWE [hh] <= 0.0)
            {
                Albedo [hh] = Albedo_bare [hh];
                winter [hh] = 0;
                meltflag [hh] = 0;
            }

            else
            {
                double Qnc = - 0.371 + 5.22 * QdroD [hh] * (1 - Albedo [hh]);
                double MT = - 0.064 * jday + 6.69;
                if (hru_tmax [hh] < - 6.0 && Qnc < 1.0)
                {
                    winter [hh] = 1;
                    if (hru_tmin [hh] > - 4.0 || Qnc > 1.0 && hru_tmax [hh] > 0.0 || hru_tmax [hh] > MT && Qnc > - 0.5)
                    {
                        meltflag [hh] = 1;
                    }

                }

                if (Albedo_obs)
                {
                    Albedo [hh] = Albedo_obs [hh];
                }

                else
                {
                    albedo (jday, Qnc);
                }

                if (! winter [hh])
                {
                    if (Albedo [hh] < Albedo_bare [hh])
                    {
                        Albedo [hh] = Albedo_bare [hh];
                    }

                    meltflag [hh] = 1;
                }

            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs2::run(void)@@@Classalbedoobs2.cpp>");
}
void Classalbedoobs2 :: albedo (long jday, double Qnc)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs2::albedo(long jday, double Qnc)@@@Classalbedoobs2.cpp>");
    double DR = 0.071;
    if (SWE [hh] > 60.0 && Albedo [hh] > 0.65)
    {
        DR = 0.015;
    }

    if (SWE [hh] > 60.0 && Albedo [hh] < 0.65)
    {
        DR = 0.001;
    }

    if (net_snowD [hh] > 0.25)
    {
        Albedo [hh] = Albedo [hh] + net_snowD [hh] * 0.1 * 2.0;
        if (Albedo [hh] > Albedo_snow [hh])
        {
            Albedo [hh] = Albedo_snow [hh];
        }

    }

    if (winter [hh] == 1)
    {
        if (newsnowcnt [hh] < 3)
        {
            Albedo [hh] = Albedo [hh] - 0.05;
        }

        else
        {
            double MT = - 0.064 * jday + 6.69;
            if (hru_tmin [hh] > - 4.0 || Qnc > 1.0 && hru_tmax [hh] > 0.0 || hru_tmax [hh] > MT && Qnc > - 0.5)
            {
                Albedo [hh] = Albedo [hh] - DR;
            }

            else
            if (Albedo [hh] > 0.65)
            {
                Albedo [hh] = Albedo [hh] - 0.006;
            }

        }

    }

    else
    {
        Albedo [hh] = Albedo [hh] - 0.02;
    }

InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs2::albedo(long jday, double Qnc)@@@Classalbedoobs2.cpp>");
}