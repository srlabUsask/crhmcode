#include "ClassGreencrack.h"
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
ClassGreencrack * ClassGreencrack :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::klone(string name) const@@@ClassGreencrack.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::klone(string name) const@@@ClassGreencrack.cpp>");
    return new ClassGreencrack (name);
InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::klone(string name) const@@@ClassGreencrack.cpp>");
}
void ClassGreencrack :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::decl(void)@@@ClassGreencrack.cpp>");
    Description = "'Handles summer using Green Ampt and frozen soil infiltration using Granger et al. 1984; Gray et al., 1986.'";
    declvar ("infil", TDim :: NHRU, "Potential amount of water infiltrating the soil on each HRU", "(mm/int)", & infil);
    declstatdiag ("cuminfil", TDim :: NHRU, "cumulative potential infiltration on each HRU", "(mm)", & cuminfil);
    declvar ("snowinfil", TDim :: NHRU, "infiltration", "(mm/int)", & snowinfil);
    declstatdiag ("cumsnowinfil", TDim :: NHRU, "cumulative infiltration", "(mm)", & cumsnowinfil);
    declvar ("runoff", TDim :: NHRU, "rainfall runoff", "(mm/int)", & runoff);
    declstatdiag ("cumrunoff", TDim :: NHRU, "cumulative rainfall runoff", "(mm)", & cumrunoff);
    declvar ("meltrunoff", TDim :: NHRU, "melt runoff", "(mm/int)", & meltrunoff);
    declstatdiag ("cummeltrunoff", TDim :: NHRU, "cumulative melt runoff", "(mm)", & cummeltrunoff);
    declvar ("crackstat", TDim :: NHRU, "infiltration status", "()", & crackstat);
    declstatvar ("RainOnSnow", TDim :: NHRU, "cumulative rain on snow", "(mm)", & RainOnSnow);
    declstatvar ("crackon", TDim :: NHRU, "crack cycle enabled", "()", & crackon);
    decllocal ("RainOnSnowA", TDim :: NHRU, "accumulated rain on snow", "(mm)", & RainOnSnowA);
    decllocal ("k", TDim :: NHRU, "(mm/h)", "()", & k);
    decllocal ("F0", TDim :: NHRU, "last HRU cumulative infiltration", "(mm)", & F0);
    decllocal ("f0", TDim :: NHRU, "", "(mm/h)", & f0);
    decllocal ("F1", TDim :: NHRU, "HRU cumulative infiltration", "(mm)", & F1);
    decllocal ("f1", TDim :: NHRU, "", "(mm/h)", & f1);
    decllocal ("dthbot", TDim :: NHRU, "", "()", & dthbot);
    decllocal ("psidthbot", TDim :: NHRU, "", "(mm)", & psidthbot);
    decllocal ("timer", TDim :: NHRU, "", "(d)", & timer);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("fallstat", TDim :: NHRU, "[50.0]", "-1.0", "100.0", "fall status 0.0 - unlimited/ 100.0 - restricted/ other - limited", "(%)", & fallstat);
    decldiagparam ("Major", TDim :: NHRU, "[5]", "1", "100", "threshold for major melt", "(mm/d)", & Major);
    declparam ("soil_type", TDim :: NHRU, "[4]", "0", "12", "water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement"
        " 0 - 12", "()", & soil_type);
    declparam ("soil_moist_max", TDim :: NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."
        "Soil profile is surface to bottom of rooting zone", "(mm)", & soil_moist_max);
    declparam ("soil_moist_init", TDim :: NHRU, "[187.0]", "0.0", "2500.0", "Initial value of available water in soil profile", "(mm)", & soil_moist_init);
    decldiagparam ("PriorInfiltration", TDim :: NHRU, "[0]", "0", "1", "allow limited melt to infiltrate prior to major melt", "()", & PriorInfiltration);
    decldiagparam ("infDays", TDim :: NHRU, "[6]", "0", "20", " maximum number of days of snowmelt infiltration to frozen soil ", "(d)", & infDays);
    declgetvar ("*", "hru_tmax", "(" + string (DEGREE_CELSIUS) + ")", & hru_tmax);
    declgetvar ("*", "snowmeltD", "(mm/d)", & snowmelt);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "net_rain", "(mm/int)", & net_rain);
    declputvar ("*", "soil_moist", "(mm)", & soil_moist);
InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::decl(void)@@@ClassGreencrack.cpp>");
}
void ClassGreencrack :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::init(void)@@@ClassGreencrack.cpp>");
    nhru = getdim (TDim :: NHRU);
    try {
        Xinfil = new double * [3];
        for (int jj = 0; jj < 3; ++ jj)
            Xinfil [jj] = new double [nhru];
    }
    catch (std :: bad_alloc) {
        CRHMException Except ("Could not allocate in module CRACK.", TExcept :: TERMINATE);
        LogError (Except);
        throw Except;
    }
    for (hh = 0; hh < nhru; ++ hh) {
        infil [hh] = 0.0;
        cuminfil [hh] = 0.0;
        snowinfil [hh] = 0.0;
        cumsnowinfil [hh] = 0.0;
        runoff [hh] = 0.0;
        cumrunoff [hh] = 0.0;
        meltrunoff [hh] = 0.0;
        cummeltrunoff [hh] = 0.0;
        RainOnSnow [hh] = 0.0;
        RainOnSnowA [hh] = 0.0;
        crackstat [hh] = 0;
        crackon [hh] = false;
        timer [hh] = 0;
        Xinfil [0] [hh] = 0.0;
        Xinfil [1] [hh] = 0.0;
        Xinfil [2] [hh] = 0.0;
        F1 [hh] = soil_moist_max [hh];
        k [hh] = soilproperties [soil_type [hh]] [KSAT];
        if (soil_moist_max [hh] > 0.0)
        {
            dthbot [hh] = (1.0 - soil_moist_init [hh] / soil_moist_max [hh]);
        }

        else
        {
            dthbot [hh] = 1.0;
            continue;
        }

        psidthbot [hh] = soilproperties [soil_type [hh]] [PSI] * dthbot [hh];
        f1 [hh] = calcf1 (F1 [hh], psidthbot [hh]) * Global :: Interval * 24.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::init(void)@@@ClassGreencrack.cpp>");
}
void ClassGreencrack :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::run(void)@@@ClassGreencrack.cpp>");
    long nstep;
    nstep = getstep () % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
        if (crackon [hh])
        {
            RainOnSnowA [hh] += net_rain [hh];
        }

        infil [hh] = 0.0;
        snowinfil [hh] = 0.0;
        runoff [hh] = 0.0;
        meltrunoff [hh] = 0.0;
    }
    if (nstep == 0)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            if (SWE [hh] > 25.0 && ! crackon [hh])
            {
                crackstat [hh] = 0;
                crackon [hh] = true;
                timer [hh] = 0;
                Xinfil [0] [hh] = 0.0;
                Xinfil [1] [hh] = 0.0;
                Xinfil [2] [hh] = 0.0;
            }

            if (crackon [hh] && snowmelt [hh] > 0.0)
            {
                if (timer [hh] > 0 && crackstat [hh] > 0)
                {
                    if (fallstat [hh] > 0.0 && hru_tmax [0] < - 10.0)
                    {
                        crackstat [hh] = 10;
                    }

                }

                if (fallstat [hh] <= 0.0)
                {
                    snowinfil [hh] = snowmelt [hh];
                    crackstat [hh] = 1;
                }

                else
                if (fallstat [hh] < 100.0)
                {
                    if (snowmelt [hh] >= Major [hh] || crackstat [hh] >= 1)
                    {
                        if (SWE [hh] > Xinfil [2] [hh] && snowmelt [hh] >= Major [hh])
                        {
                            infil_index (fallstat [hh] / 100.0, SWE [hh], Xinfil [0] [hh], Xinfil [1] [hh], infDays [hh]);
                            Xinfil [2] [hh] = SWE [hh];
                        }

                        if (snowmelt [hh] >= Major [hh])
                        {
                            if (crackstat [hh] <= 0)
                            {
                                crackstat [hh] = 1;
                            }

                            else
                            {
                                crackstat [hh] = crackstat [hh] + 1;
                            }

                            timer [hh] = 1;
                            snowinfil [hh] = snowmelt [hh] * Xinfil [0] [hh];
                            if (snowinfil [hh] > Xinfil [1] [hh])
                            {
                                snowinfil [hh] = Xinfil [1] [hh];
                            }

                        }

                        else
                        {
                            snowinfil [hh] = snowmelt [hh] * Xinfil [0] [hh];
                        }

                        if (crackstat [hh] > infDays [hh])
                        {
                            snowinfil [hh] = 0;
                        }

                    }

                    else
                    if (PriorInfiltration [hh])
                    {
                        snowinfil [hh] = snowmelt [hh];
                    }

                }

                else
                if (fallstat [hh] >= 100.0)
                {
                    snowinfil [hh] = 0.0;
                    crackstat [hh] = 1;
                }

                meltrunoff [hh] = snowmelt [hh] - snowinfil [hh];
                if (snowinfil [hh] > 0.0)
                {
                    snowinfil [hh] += RainOnSnowA [hh];
                }

                else
                {
                    meltrunoff [hh] += RainOnSnowA [hh];
                }

                cumsnowinfil [hh] += snowinfil [hh];
                cummeltrunoff [hh] += meltrunoff [hh];
                RainOnSnow [hh] += RainOnSnowA [hh];
                RainOnSnowA [hh] = 0.0;
            }

            else
            if (snowmelt [hh] > 0.0)
            {
                snowinfil [hh] = snowmelt [hh];
                cumsnowinfil [hh] += snowinfil [hh];
            }

            if (crackstat [hh] > 0 && SWE [hh] <= 0.0)
            {
                crackon [hh] = false;
                crackstat [hh] = 0;
            }

        }
    }

    for (hh = 0; chkStruct (); ++ hh) {
        if (! crackon [hh] && net_rain [hh] > 0.0)
        {
            garain = net_rain [hh];
            intensity = net_rain [hh] * Global :: Freq / 24.0;
            if (garain > 0.0)
            {
                if (soil_type [hh] == 12)
                {
                    runoff [hh] = garain;
                }

                else
                if (soil_type [hh] == 0 || soil_moist [hh] <= 0.0)
                {
                    infil [hh] = garain;
                    cuminfil [hh] += infil [hh];
                }

                else
                {
                    F1 [hh] = soil_moist [hh];
                    dthbot [hh] = (1.0 - soil_moist [hh] / soil_moist_max [hh]);
                    psidthbot [hh] = soilproperties [soil_type [hh]] [PSI] * dthbot [hh];
                    if (soil_type [hh] > 0)
                    {
                        f1 [hh] = calcf1 (F1 [hh], psidthbot [hh]) * Global :: Interval * 24.0;
                    }

                    infiltrate ();
                    infil [hh] = F1 [hh] - F0 [hh];
                    cuminfil [hh] += infil [hh];
                    if (pond > 0.0)
                    {
                        runoff [hh] = pond;
                    }

                }

            }

            cumrunoff [hh] += runoff [hh];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::run(void)@@@ClassGreencrack.cpp>");
}
void ClassGreencrack :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::finish(bool good)@@@ClassGreencrack.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (Greencrack)' cumsnowinfil  (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumsnowinfil [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Greencrack)' cummeltrunoff (mm) (mm*hru) (mm*hru/basin): ").c_str (), cummeltrunoff [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Greencrack)' cuminfil      (mm) (mm*hru) (mm*hru/basin): ").c_str (), cuminfil [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Greencrack)' cumrunoff     (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumrunoff [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Greencrack)' RainOnSnow    (mm) (mm*hru) (mm*hru/basin): ").c_str (), RainOnSnow [hh], hru_area [hh], basin_area [0], "information only - amount of rain handled as snow");
        LogDebug (" ");
    }
    if (Xinfil != NULL)
    {
        for (int ii = 0; ii < 3; ii ++)
            delete [] Xinfil [ii];
        delete [] Xinfil;
        Xinfil = NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::finish(bool good)@@@ClassGreencrack.cpp>");
}
void ClassGreencrack :: infiltrate (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::infiltrate(void)@@@ClassGreencrack.cpp>");
    F0 [hh] = F1 [hh];
    f0 [hh] = f1 [hh];
    if (soil_type [hh] == 0)
    {
        pond += garain;

InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::infiltrate(void)@@@ClassGreencrack.cpp>");
        return;
    }

    pond = 0.0;
    f0 [hh] = calcf1 (F0 [hh], psidthbot [hh]);
    if (intensity > f0 [hh])
    {
        ponding ();

InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::infiltrate(void)@@@ClassGreencrack.cpp>");
        return;
    }

    F1 [hh] = F0 [hh] + garain;
    f1 [hh] = calcf1 (F1 [hh], psidthbot [hh]);
    if (intensity > f1 [hh])
    {
        startponding ();
    }

InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::infiltrate(void)@@@ClassGreencrack.cpp>");
}
void ClassGreencrack :: ponding (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::ponding(void)@@@ClassGreencrack.cpp>");
    F1 [hh] = F0 [hh] + garain;
    howmuch (F0 [hh], Global :: Interval * 24.0);
    pond = F0 [hh] + garain - F1 [hh];
InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::ponding(void)@@@ClassGreencrack.cpp>");
}
void ClassGreencrack :: startponding (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::startponding(void)@@@ClassGreencrack.cpp>");
    double Fp = k [hh] * psidthbot [hh] / (intensity - k [hh]);
    double dt = (Fp - F0 [hh]) / intensity;
    howmuch (F0 [hh], Global :: Interval * 24.0 - dt);
    pond = F0 [hh] + garain - F1 [hh];
InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::startponding(void)@@@ClassGreencrack.cpp>");
}
void ClassGreencrack :: howmuch (double F0, double dt)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::howmuch(double F0, double dt)@@@ClassGreencrack.cpp>");
    double LastF1;
    do {
        LastF1 = F1 [hh];
        F1 [hh] = F0 + k [hh] * dt + psidthbot [hh] * log ((F1 [hh] + psidthbot [hh]) / (F0 + psidthbot [hh]));
    }
    while (fabs (LastF1 - F1 [hh]) > 0.01);
InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::howmuch(double F0, double dt)@@@ClassGreencrack.cpp>");
}
double ClassGreencrack :: calcf1 (double F, double psidth)
{
InstrumentLogger::instance()->log_instrument_log("<ClassGreencrack::calcf1(double F, double psidth)@@@ClassGreencrack.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::calcf1(double F, double psidth)@@@ClassGreencrack.cpp>");
    return k [hh] * (psidth / F + 1.0);
InstrumentLogger::instance()->log_instrument_log("</ClassGreencrack::calcf1(double F, double psidth)@@@ClassGreencrack.cpp>");
}