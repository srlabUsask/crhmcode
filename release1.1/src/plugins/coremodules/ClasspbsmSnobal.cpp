#include "ClasspbsmSnobal.h"
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
ClasspbsmSnobal * ClasspbsmSnobal :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClasspbsmSnobal::klone(string name) const@@@ClasspbsmSnobal.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClasspbsmSnobal::klone(string name) const@@@ClasspbsmSnobal.cpp>");
    return new ClasspbsmSnobal (name);
InstrumentLogger::instance()->log_instrument_log("</ClasspbsmSnobal::klone(string name) const@@@ClasspbsmSnobal.cpp>");
}
void ClasspbsmSnobal :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClasspbsmSnobal::decl(void)@@@ClasspbsmSnobal.cpp>");
    Description = "'Special \"pbsm\" module compatible with \"snobal\".' \
                 'original version using hru_u,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u,' \
                 'using hru_u and a regression to use daily windspeed,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u and a regression to use daily windspeed.'";
    variation_set = VARIATION_0 + VARIATION_2;
    declgetvar ("*", "hru_u", "(m/s)", & hru_u);
    variation_set = VARIATION_1 + VARIATION_3;
    declgetvar ("*", "hru_Uadjust", "(m/s)", & hru_Uadjust);
    variation_set = VARIATION_2 + VARIATION_3;
    declparam ("u_D", TDim :: NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed correction", "()", & u_D);
    declparam ("Drift_offset", TDim :: NHRU, "[0.0]", "-100.0", "100.0", "Daily windspeed drift offset correction", "()", & Drift_offset);
    declparam ("Drift_slope", TDim :: NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed drift slope correction", "()", & Drift_slope);
    declparam ("Subl_offset", TDim :: NHRU, "[0.0]", "-100.0", "100.0", "Daily windspeed sublimation offset correction", "()", & Subl_offset);
    declparam ("Subl_slope", TDim :: NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed sublimation slope correction", "()", & Subl_slope);
    variation_set = VARIATION_ORG;
    declvar ("hru_subl", TDim :: NHRU, "interval sublimation", "(mm/int)", & Subl);
    declvar ("hru_drift", TDim :: NHRU, "interval composite transport", "(mm/int)", & Drift);
    decldiag ("DriftH", TDim :: NHRU, "interval transport", "(mm/int)", & DriftH);
    decldiag ("SublH", TDim :: NHRU, "interval sublimation", "(mm/int)", & SublH);
    declvar ("Drift_out", TDim :: NHRU, "interval transport out", "(mm/int)", & Drift_out);
    declvar ("Drift_in", TDim :: NHRU, "interval transport in", "(mm/int)", & Drift_in);
    declvar ("BasinSnowLoss", TDim :: BASIN, "transport out of basin", "(mm/int)", & BasinSnowLoss);
    declstatdiag ("cumSubl", TDim :: NHRU, "cumulative sublimation", "(mm)", & cumSubl);
    declstatdiag ("cumDrift", TDim :: NHRU, "cumulative transport from HRU", "(mm)", & cumDrift);
    declstatdiag ("cumBasinSnowLoss", TDim :: BASIN, "cumulative transport out of basin", "(mm)", & cumBasinSnowLoss);
    declstatdiag ("cumBasinSnowGain", TDim :: BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", & cumBasinSnowGain);
    declstatdiag ("cumDriftIn", TDim :: NHRU, "cumulative transport to HRU", "(mm)", & cumDriftIn);
    decllocal ("hru_basin", TDim :: NHRU, "conversion factor", "()", & hru_basin);
    decldiag ("DrySnow", TDim :: NHRU, "DrySnow", "()", & DrySnow);
    declstatdiag ("SnowAge", TDim :: NHRU, "SnowAge", "()", & SnowAge);
    decldiag ("Prob", TDim :: NHRU, "Probability", "()", & Prob);
    decldiag ("snowdepth", TDim :: NHRU, "depth of snow using Gray/Pomeroy", "(m)", & snowdepth);
    declparam ("fetch", TDim :: NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", & fetch);
    declparam ("Ht", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", & Ht);
    declparam ("distrib", TDim :: NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - can sum to 1", "()", & distrib);
    decldiagparam ("N_S", TDim :: NHRU, "[320]", "1", "500", "vegetation number density", "(1/m^2)", & N_S);
    decldiagparam ("A_S", TDim :: NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", & A_S);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    decldiagparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evaporatation, 1 -> inhibit", "()", & inhibit_evap);
    declparam ("inhibit_bs", TDim :: NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", & inhibit_bs);
    decldiagparam ("inhibit_subl", TDim :: NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", & inhibit_subl);
    declputvar ("*", "SWE", "(kg/m^2)", & SWE);
    declputvar ("*", "z_s", "(m)", & z_s);
    declputvar ("*", "rho", "(kg/m^3)", & rho);
    declgetvar ("*", "hru_t", "(°C)", & hru_t);
    declgetvar ("*", "hru_ea", "(kPa)", & hru_ea);
    declgetvar ("*", "net_snow", "(mm/int)", & net_snow);
InstrumentLogger::instance()->log_instrument_log("</ClasspbsmSnobal::decl(void)@@@ClasspbsmSnobal.cpp>");
}
void ClasspbsmSnobal :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClasspbsmSnobal::init(void)@@@ClasspbsmSnobal.cpp>");
    nhru = getdim (TDim :: NHRU);
    cumBasinSnowLoss [0] = 0.0;
    cumBasinSnowGain [0] = 0.0;
    for (hh = 0; hh < nhru; ++ hh) {
        SWE [hh] = 0.0;
        cumDrift [hh] = 0.0;
        cumDriftIn [hh] = 0.0;
        cumSubl [hh] = 0.0;
        SnowAge [hh] = 0.0;
        DrySnow [hh] = 0;
        snowdepth [hh] = 0.0;
        if ((hh > 0) && (Ht [hh] < Ht [hh - 1]) && distrib [hh - 1] > 0)
        {
            CRHMException TExcept (string ("'" + Name + " (pbsmSnobal)' vegetation heights not in ascending order.").c_str (), TExcept :: WARNING);
            LogError (TExcept);
        }

    }
    for (hh = 0; hh < nhru; ++ hh)
        hru_basin [hh] = hru_area [hh] / basin_area [0];
InstrumentLogger::instance()->log_instrument_log("</ClasspbsmSnobal::init(void)@@@ClasspbsmSnobal.cpp>");
}
void ClasspbsmSnobal :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClasspbsmSnobal::run(void)@@@ClasspbsmSnobal.cpp>");
    double Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
    double SumDrift, total, SWE_Max, transport;
    for (hh = 0; chkStruct (); ++ hh) {
        if (variation == VARIATION_ORG || variation == VARIATION_2)
        {
            hru_u_ = hru_u [hh];
        }

        else
        {
            hru_u_ = hru_Uadjust [hh];
        }

        if (variation == VARIATION_2 || variation == VARIATION_3)
        {
            hru_u_ = u_D [hh] * hru_u_;
        }

        Drift_out [hh] = 0.0;
        Drift_in [hh] = 0.0;
        Drift [hh] = 0.0;
        Subl [hh] = 0.0;
        Prob [hh] = 0.0;
        if (SWE [hh] > 0.0 && ! inhibit_bs [hh])
        {
            E_StubHt = Ht [hh] - z_s [hh];
            if (E_StubHt < 0.0001)
            {
                E_StubHt = 0.0001;
            }

            Ustar = 0.02264 * pow (hru_u_, 1.295f);
            if (E_StubHt > 0.01)
            {
                Znod = (sqr (Ustar) / 163.3f) + 0.5 * N_S [hh] * E_StubHt * A_S [hh];
                Lambda = N_S [hh] * A_S [hh] * E_StubHt;
                Ustn = Ustar * sqrt ((PBSM_constants :: Beta * Lambda) / (1.0 + PBSM_constants :: Beta * Lambda));
                Uten_Prob = (log (10.0 / Znod)) / PBSM_constants :: KARMAN * sqrt (Ustar - Ustn);
            }

            else
            {
                Uten_Prob = hru_u_;
            }

            bool newsnow = net_snow [hh];
            ProbabilityThresholdNew (SWE [hh], hru_t [hh], Uten_Prob, Prob [hh], Ut, newsnow, SnowAge [hh], DrySnow [hh]);
            if (Prob [hh] > 0.001)
            {
                Ut = Ut * 0.8;
                double RH = hru_ea [hh] / Common :: estar (hru_t [hh]);
                Pbsm (E_StubHt, Ut, DriftH [hh], SublH [hh], hru_t [hh], hru_u_, RH, fetch [hh], N_S [hh], A_S [hh]);
                if (variation == VARIATION_2 || variation == VARIATION_3)
                {
                    DriftH [hh] = Drift_offset [hh] + DriftH [hh] * Drift_slope [hh];
                    SublH [hh] = Subl_offset [hh] + SublH [hh] * Subl_slope [hh];
                }

                Drift_out [hh] = DriftH [hh] * Prob [hh] / fetch [hh];
                if (! inhibit_subl [hh])
                {
                    Subl [hh] = SublH [hh] * Prob [hh];
                }

                if (Drift_out [hh] + Subl [hh] > SWE [hh])
                {
                    if (Drift_out [hh] >= SWE [hh])
                    {
                        Drift_out [hh] = SWE [hh];
                        Subl [hh] = 0.0;
                    }

                    else
                    {
                        Subl [hh] = SWE [hh] - Drift_out [hh];
                    }

                }

                cumDrift [hh] += Drift_out [hh];
                cumSubl [hh] += Subl [hh];
            }

        }

    }
    if (distrib [0] > 0.0)
    {
        double Drft = Drift_out [0] * distrib [0];
        SWE [0] += Drft;
        cumDriftIn [0] += Drft;
        cumBasinSnowGain [0] += Drft * hru_basin [0];
    }

    BasinSnowLoss [0] = 0.0;
    long LastN = 0;
    if (! inhibit_bs [0] && nhru == 1)
    {
        BasinSnowLoss [0] = Drift_out [0];
        cumBasinSnowLoss [0] += BasinSnowLoss [0];
    }

    for (long nn = LastN; chkStruct (nn); ++ nn) {
        if (distrib [nn] >= 0.0 && nn + 1 < nhru)
        {
            continue;
        }

        SumDrift = 0.0;
        for (long hhh = LastN; chkStruct (hhh, nn); ++ hhh)
            SumDrift += Drift_out [hhh] * hru_basin [hhh];
        if (SumDrift > 0.0)
        {
            for (long hh = LastN + 1; chkStruct (hh, nn + 1); ++ hh) {
                if (Ht [hh] > z_s [hh])
                {
                    SWE_Max = SWE [hh] + rho [hh] * (Ht [hh] - z_s [hh]);
                }

                else
                {
                    SWE_Max = SWE [hh];
                }

                if (SWE_Max <= 0.0)
                {
                    SWE_Max = Ht [hh];
                }

                if (hh == nn)
                {
                    if (distrib [nn] > 0)
                    {
                        double In = SumDrift / hru_basin [hh];
                        if (SWE_Max > SWE [hh] + In)
                        {
                            Drift_in [hh] = In;
                            cumDriftIn [hh] += Drift_in [hh];
                            transport = 0.0;
                        }

                        else
                        if (SWE_Max > SWE [hh])
                        {
                            Drift_in [hh] = SWE_Max - SWE [hh];
                            cumDriftIn [hh] += Drift_in [hh];
                            transport -= (In - (SWE_Max - SWE [hh])) * hru_basin [hh];
                        }

                        else
                        {
                            transport = SumDrift;
                        }

                    }

                    else
                    if (distrib [nn] < 0)
                    {
                        Drift_in [hh] = SumDrift / hru_basin [hh];
                        cumDriftIn [hh] += Drift_in [hh];
                        transport = 0.0;
                    }

                    else
                    {
                        transport = SumDrift;
                    }

                    BasinSnowLoss [0] += (transport + Drift_out [hh] * hru_basin [hh]);
                    cumBasinSnowLoss [0] += (transport + Drift_out [hh] * hru_basin [hh]);
                }

                else
                if (SWE_Max > SWE [hh] && distrib [hh] > 0.0)
                {
                    total = 0.0;
                    for (long jj = hh; chkStruct (jj, nn + 1); jj ++)
                        total += fabs (distrib [jj]);
                    transport = SumDrift * fabs (distrib [hh]) / total / hru_basin [hh];
                    if (SWE_Max > SWE [hh] + transport)
                    {
                        Drift_in [hh] += transport;
                    }

                    else
                    if (SWE_Max > SWE [hh])
                    {
                        transport = SWE_Max - SWE [hh];
                        Drift_in [hh] += transport;
                    }

                    else
                    {
                        transport = 0.0;
                    }

                    SumDrift -= transport * hru_basin [hh];
                    cumDriftIn [hh] += transport;
                }

            }
            LastN = nn + 1;
        }

    }
    for (hh = 0; chkStruct (); ++ hh) {
        Drift [hh] = Drift_in [hh] - Drift_out [hh];
        if (SWE [hh] > 0.0)
        {
            const_cast < long * > (inhibit_evap) [hh] = 1;
            snowdepth [hh] = Common :: DepthofSnow (SWE [hh]);
        }

        else
        {
            const_cast < long * > (inhibit_evap) [hh] = 0;
            snowdepth [hh] = 0.0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClasspbsmSnobal::run(void)@@@ClasspbsmSnobal.cpp>");
}
void ClasspbsmSnobal :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClasspbsmSnobal::finish(bool good)@@@ClasspbsmSnobal.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (pbsmSnobal)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumDrift [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsmSnobal)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumDriftIn [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsmSnobal)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSubl [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
    LogMessage ("'pbsmSnobal' cumBasinSnowLoss (mm): ", cumBasinSnowLoss [0]);
    LogMessage ("'pbsmSnobal' cumBasinSnowGain (mm): ", cumBasinSnowGain [0]);
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClasspbsmSnobal::finish(bool good)@@@ClasspbsmSnobal.cpp>");
}