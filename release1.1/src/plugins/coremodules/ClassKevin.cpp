#include "ClassKevin.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM.h"
#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include "../../core/InstrumentLogger.h"

using namespace CRHM;
ClassKevin * ClassKevin :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassKevin::klone(string name) const@@@ClassKevin.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassKevin::klone(string name) const@@@ClassKevin.cpp>");
    return new ClassKevin (name);
InstrumentLogger::instance()->log_instrument_log("</ClassKevin::klone(string name) const@@@ClassKevin.cpp>");
}
void ClassKevin :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassKevin::decl(void)@@@ClassKevin.cpp>");
    Description = "'Melt model loosely based on thesis (K. Shook).'";
    declvar ("winter", TDim :: NHRU, "winter = 1 - true", "()", & winter);
    declvar ("SnowStat", TDim :: NHRU, "EARLY/MATURE/HOLD 0/1/2", "()", & SnowStat);
    declvar ("sca", TDim :: NHRU, "snow covered area", "()", & sca);
    declvar ("snowmelt", TDim :: NHRU, "snow melt", "(mm/int)", & snowmelt);
    declvar ("netLong", TDim :: NHRU, "net long-wave", "(mm/int)", & netLong);
    declvar ("netShort", TDim :: NHRU, "net long-wave", "(mm/int)", & netShort);
    declvar ("snowmeltD", TDim :: NHRU, "daily snow melt", "(mm/d)", & snowmeltD);
    declvar ("cumsnowmelt", TDim :: NHRU, "cumulative snow melt", "(mm)", & cumsnowmelt);
    decldiag ("albedo", TDim :: NHRU, "areal albedo()", "()", & albedo);
    decldiagparam ("Asnow1", TDim :: NHRU, "0.8", "0", "1", "early snow albedo", "()", & Asnow1);
    decldiagparam ("Asnow2", TDim :: NHRU, "0.6", "0", "1", "mature snow albedo", "()", & Asnow2);
    decldiagparam ("Asoil", TDim :: NHRU, "0.2", "0.1", "1", "soil albedo", "()", & Asoil);
    declparam ("cv", TDim :: NHRU, "0.33", "0.2", "0.7", "coefficient of variation", "()", & cv);
    declparam ("tfactor", TDim :: NHRU, "0.1", "0.0", "10.0", "degree interval melt factor", "(mm/d*ºC)", & tfactor);
    declparam ("nfactor", TDim :: NHRU, "0.0", "0.0", "10.0", "net radiation factor (typical value 3.0 (mm/MJ*m^2*d))", "(mm/MJ*m^2*d)", & nfactor);
    declparam ("meltthresh", TDim :: NHRU, "1.0", "0.0", "10.0", "melt threshold to become mature pack", "(mm/d)", & meltthresh);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("hru_lat", TDim :: NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(°)", & hru_lat);
    declputvar ("*", "SWE", "(mm)", & SWE);
    declreadobs ("hru_Qn", TDim :: NHRU, "net radiation", "(W/m^2)", & hru_Qn, 0, true);
    declgetvar ("*", "hru_t", "(°C)", & hru_t);
    declgetvar ("*", "hru_tmean", "(°C)", & hru_tmean);
    declgetvar ("*", "hru_eamean", "(kPa)", & hru_eamean);
    declgetvar ("*", "hru_SunAct", "(h)", & hru_SunAct);
    declgetvar ("*", "SunMax", "(h)", & SunMax);
    declgetvar ("*", "Qdro", "(W/m^2)", & Qdro);
    declgetvar ("*", "Qdfo", "(W/m^2)", & Qdfo);
InstrumentLogger::instance()->log_instrument_log("</ClassKevin::decl(void)@@@ClassKevin.cpp>");
}
void ClassKevin :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassKevin::init(void)@@@ClassKevin.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh)
        if (nfactor [hh] != 0.0 && hru_Qn == NULL)
        {
            CRHMException TExcept ("Kevin: nfactor > 0.0 with observation 'hru_Qn' not defined!", TExcept :: TERMINATE);
            LogError (TExcept);
        }

    SWEpeak = new double [nhru];
    SWElast = new double [nhru];
    for (hh = 0; hh < nhru; ++ hh) {
        snowmelt [hh] = 0.0;
        cumsnowmelt [hh] = 0.0;
        netLong [hh] = 0.0;
        netShort [hh] = 0.0;
        if (SWE [0] > 50.0)
        {
            for (long hh = 0; hh < nhru; ++ hh) {
                winter [hh] = 1;
                albedo [hh] = Asnow1 [hh];
                sca [hh] = 1.0;
            }
        }

        else
        {
            winter [hh] = 0;
            albedo [hh] = Asoil [hh];
            sca [hh] = 0.0;
        }

        SnowStat [hh] = EARLY;
        SWEpeak [hh] = SWE [hh];
        SWElast [hh] = SWE [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassKevin::init(void)@@@ClassKevin.cpp>");
}
void ClassKevin :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassKevin::run(void)@@@ClassKevin.cpp>");
    double melt, netlong, shortw, net;
    long nstep = getstep () % Global :: Freq;
    long jday = julian ("now");
    double hemisphere = (hru_lat [0] < 0.0);
    if ((! hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE [0] > 5.0 && nstep == 1)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            winter [hh] = 1;
            albedo [hh] = Asnow1 [hh];
            sca [hh] = 1.0;
        }
    }

    for (hh = 0; chkStruct (); ++ hh) {
        snowmelt [hh] = 0.0;
        if (nstep == 1)
        {
            snowmeltD [hh] = 0.0;
        }

        if (SWE [hh] <= 0.0)
        {
            albedo [hh] = Asoil [hh];
            sca [hh] = 0.0;
            SnowStat [hh] = EARLY;
            continue;
        }

        if ((tfactor [hh] > 0.0) || (nfactor [hh] > 0.0))
        {
            melt = 0.0;
            if (hru_t [hh] > 0.0)
            {
                melt += hru_t [hh] * tfactor [hh] / Global :: Freq;
            }

            if (hru_Qn)
            {
                if (hru_Qn [hh] > 0.0)
                {
                    melt += hru_Qn [hh] * nfactor [hh] * WtoMJ_D / Global :: Freq;
                }

            }

        }

        else
        {
            netlong = - 0.85 + 0.97 * CRHM_constants :: SB * pow (hru_tmean [hh] + 273.0f, 4.0f) * (- 0.39f + 0.093f * sqrt (hru_eamean [hh])) * (0.26f + 0.81f * (hru_SunAct [hh] / SunMax [hh]));
            netLong [hh] = netlong;
            if (hru_SunAct [hh] > 0.0)
            {
                shortw = (0.024f + 0.974f * pow (hru_SunAct [hh] / SunMax [hh], 1.35f)) * Qdro [hh] * WtoMJ_D + (2.68f + 2.2f * (hru_SunAct [hh] / SunMax [hh]) - 3.85f * sqr (hru_SunAct [hh] / SunMax [hh])) * Qdfo [hh] * WtoMJ_D;
            }

            else
            {
                shortw = (0.024f * Qdro [hh] + 2.68f * Qdfo [hh]) * WtoMJ_D;
            }

            netShort [hh] = shortw;
            if (SnowStat [hh] == MATURE)
            {
                net = (shortw * (1.0f - Asnow2 [hh]) + netlong) / Global :: Freq;
            }

            else
            {
                net = (shortw * (1.0f - Asnow1 [hh]) + netlong) / Global :: Freq;
            }

            if (net > 0.0)
            {
                melt = net / 0.3336f;
            }

            else
            {
                melt = 0.0;
            }

        }

        switch (SnowStat [hh]) {
        case EARLY:
            if (melt > 0.0)
            {
                if (melt > SWE [hh])
                {
                    melt = SWE [hh];
                    SWE [hh] = 0.0;
                    snowmelt [hh] = melt;
                    sca [hh] = 0.0;
                    albedo [hh] = Asoil [hh];
                }

                else
                {
                    SWE [hh] -= melt;
                    snowmelt [hh] = melt;
                    sca [hh] = 1.0;
                    albedo [hh] = Asnow1 [hh];
                }

            }

            break;
        case MATURE:
            if (SWE [hh] > SWElast [hh])
            {
                if (melt > 0.0)
                {
                    SWE [hh] -= melt;
                    snowmelt [hh] = melt;
                }

                if (SWE [hh] > SWEpeak [hh])
                {
                    SWEpeak [hh] = SWE [hh];
                    LogMessage (hh, " add to SWE peak ", SWEpeak [hh], TExtra :: DT);
                }

                else
                if (SWE [hh] > SWElast [hh])
                {
                    SnowStat [hh] = HOLD;
                }

                SWElast [hh] = SWE [hh];
                sca [hh] = 1.0;
                albedo [hh] = Asnow1 [hh];
                break;
            }

            if (melt > 0.0)
            {
                sca [hh] = Common :: SWE_prob (SWEpeak [hh], SWEpeak [hh] - SWElast [hh], cv [hh]);
                if (sca [hh] >= 0.01)
                {
                    snowmelt [hh] = melt * sca [hh];
                    if (snowmelt [hh] > SWE [hh])
                    {
                        snowmelt [hh] = SWE [hh];
                    }

                    SWE [hh] -= snowmelt [hh];
                    SWElast [hh] = SWE [hh];
                    albedo [hh] = Asnow2 [hh] * sca [hh] + Asoil [hh] * (1.0 - sca [hh]);
                }

                else
                {
                    snowmelt [hh] = SWE [hh];
                    SWE [hh] = 0.0;
                    winter [hh] = 0;
                    SnowStat [hh] = EARLY;
                    sca [hh] = 0.0;
                    albedo [hh] = Asoil [hh];
                    LogMessage (hh, " going to 'EARLY' SWE ", SWE [hh], TExtra :: DT);
                }

            }

            break;
        case HOLD:
            sca [hh] = 1.0;
            albedo [hh] = Asnow1 [hh];
            if (melt > 0.0)
            {
                if (melt > SWE [hh])
                {
                    melt = SWE [hh];
                }

                SWE [hh] -= melt;
                snowmelt [hh] += melt;
            }

            if (SWElast [hh] >= SWE [hh] || SWE [hh] >= SWEpeak [hh])
            {
                SnowStat [hh] = MATURE;
                SWElast [hh] = SWE [hh];
            }

            break;
        }
        snowmeltD [hh] += snowmelt [hh];
        cumsnowmelt [hh] += snowmelt [hh];
        if (nstep == 0)
        if (snowmeltD [hh] >= meltthresh [hh] && SnowStat [hh] == EARLY && SWE [hh] > 5)
        {
            SnowStat [hh] = MATURE;
            SWEpeak [hh] = SWE [hh];
            LogMessage (hh, "'Kevin' SWE peak ", SWEpeak [hh], TExtra :: DT);
            LogDebug (" ");
            SWElast [hh] = SWE [hh];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassKevin::run(void)@@@ClassKevin.cpp>");
}
void ClassKevin :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassKevin::finish(bool good)@@@ClassKevin.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (Kevin)' cumsnowmelt (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumsnowmelt [hh], hru_area [hh], basin_area [0]);
    }
    LogDebug (" ");
    delete [] SWEpeak;
    SWEpeak = NULL;
    delete [] SWElast;
    SWElast = NULL;
InstrumentLogger::instance()->log_instrument_log("</ClassKevin::finish(bool good)@@@ClassKevin.cpp>");
}