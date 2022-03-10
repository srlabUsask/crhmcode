#include "Classpbsm.h"
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
Classpbsm * Classpbsm :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm::klone(string name) const@@@Classpbsm.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classpbsm::klone(string name) const@@@Classpbsm.cpp>");
    return new Classpbsm (name);
InstrumentLogger::instance()->log_instrument_log("</Classpbsm::klone(string name) const@@@Classpbsm.cpp>");
}
void Classpbsm :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm::decl(void)@@@Classpbsm.cpp>");
    Description = "'calculates snow transport and sublimation (Pomeroy and Li, 1999).' \
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
    declparam ("Drift_offset", TDim :: NHRU, "[0.0]", "0.0", "100.0", "Daily windspeed drift offset correction", "()", & Drift_offset);
    declparam ("Drift_slope", TDim :: NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed drift slope correction", "()", & Drift_slope);
    declparam ("Subl_offset", TDim :: NHRU, "[0.0]", "0.0", "100.0", "Daily windspeed sublimation offset correction", "()", & Subl_offset);
    declparam ("Subl_slope", TDim :: NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed sublimation slope correction", "()", & Subl_slope);
    variation_set = VARIATION_ORG;
    declstatvar ("SWE", TDim :: NHRU, "snow water equivalent", "(mm)", & SWE);
    declvar ("Subl", TDim :: NHRU, "interval sublimation", "(mm/int)", & Subl);
    declvar ("Drift", TDim :: NHRU, "interval transport", "(mm/int)", & Drift);
    decldiag ("DriftH", TDim :: NHRU, "interval transport", "(mm/int)", & DriftH);
    decldiag ("SublH", TDim :: NHRU, "interval sublimation", "(mm/int)", & SublH);
    decldiag ("BasinSnowLoss", TDim :: BASIN, "transport out of basin", "(mm/int)", & BasinSnowLoss);
    declstatdiag ("cumSubl", TDim :: NHRU, "cumulative sublimation", "(mm)", & cumSubl);
    declstatdiag ("cumDrift", TDim :: NHRU, "cumulative transport from HRU", "(mm)", & cumDrift);
    declstatdiag ("cumBasinSnowLoss", TDim :: BASIN, "cumulative transport out of basin", "(mm)", & cumBasinSnowLoss);
    declstatdiag ("cumBasinSnowGain", TDim :: BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", & cumBasinSnowGain);
    declstatdiag ("cumDriftIn", TDim :: NHRU, "cumulative transport to HRU", "(mm)", & cumDriftIn);
    decllocal ("hru_basin", TDim :: NHRU, "conversion factor", "()", & hru_basin);
    decldiag ("DrySnow", TDim :: NHRU, "DrySnow", "()", & DrySnow);
    declstatdiag ("SnowAge", TDim :: NHRU, "SnowAge", "()", & SnowAge);
    declstatdiag ("cumSno", TDim :: NHRU, "cumulative snow", "(mm)", & cumSno);
    declvar ("Prob", TDim :: NHRU, "Probability", "()", & Prob);
    declvar ("snowdepth", TDim :: NHRU, "depth of snow using Gray/Pomeroy", "(m)", & snowdepth);
    declvar ("rain_on_snow", TDim :: NHRU, "mass of rain falling on snowcover", "(mm/int)", & rain_on_snow);
    declvar ("cumrain_on_snow", TDim :: NHRU, "cumulative rain on snow", "(mm)", & cumrain_on_snow);
    decllocal ("SWE_Init", TDim :: NHRU, "initial SWE", "(mm)", & SWE_Init);
    declparam ("fetch", TDim :: NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", & fetch);
    declparam ("Ht", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", & Ht);
    declparam ("distrib", TDim :: NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - can sum to 1", "()", & distrib);
    decldiagparam ("N_S", TDim :: NHRU, "[320]", "1", "500", "vegetation number density", "(1/m^2)", & N_S);
    decldiagparam ("A_S", TDim :: NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", & A_S);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    decldiagparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evaporatation(System use only), 1 -> inhibit", "()", & inhibit_evap);
    decldiagparam ("inhibit_bs", TDim :: NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", & inhibit_bs);
    decldiagparam ("inhibit_subl", TDim :: NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", & inhibit_subl);
    declgetvar ("*", "hru_t", "(°C)", & hru_t);
    declgetvar ("*", "hru_rh", "(%)", & hru_rh);
    declgetvar ("*", "hru_newsnow", "()", & hru_newsnow);
    declgetvar ("*", "net_snow", "(mm/int)", & net_snow);
    declgetvar ("*", "net_rain", "(mm/int)", & net_rain);
InstrumentLogger::instance()->log_instrument_log("</Classpbsm::decl(void)@@@Classpbsm.cpp>");
}
void Classpbsm :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm::init(void)@@@Classpbsm.cpp>");
    nhru = getdim (TDim :: NHRU);
    cumBasinSnowLoss [0] = 0.0;
    cumBasinSnowGain [0] = 0.0;
    for (hh = 0; hh < nhru; ++ hh) {
        SWE [hh] = 0.0;
        cumDrift [hh] = 0.0;
        cumDriftIn [hh] = 0.0;
        cumSubl [hh] = 0.0;
        cumSno [hh] = 0.0;
        SnowAge [hh] = 0.0;
        DrySnow [hh] = 0;
        snowdepth [hh] = 0.0;
        rain_on_snow [hh] = 0.0;
        cumrain_on_snow [hh] = 0.0;
        ;
        if ((hh > 0) && (Ht [hh] < Ht [hh - 1]) && distrib [hh - 1] > 0)
        {
            CRHMException TExcept (string ("'" + Name + " (pbsm)' vegetation heights not in ascending order.").c_str (), TExcept :: WARNING);
            LogError (TExcept);
        }

    }
    for (hh = 0; hh < nhru; ++ hh)
        hru_basin [hh] = hru_area [hh] / basin_area [0];
InstrumentLogger::instance()->log_instrument_log("</Classpbsm::init(void)@@@Classpbsm.cpp>");
}
void Classpbsm :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm::run(void)@@@Classpbsm.cpp>");
    double Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
    double SumDrift, total, SWE_Max;
    double transport = 0.0;
    long step = getstep ();
    if (step == 1)
    {
        for (hh = 0; chkStruct (); ++ hh)
            SWE_Init [hh] = SWE [hh];
    }

    for (hh = 0; chkStruct (); ++ hh) {
        if (net_snow [hh] > 0.0)
        {
            SWE [hh] = SWE [hh] + net_snow [hh];
            cumSno [hh] = cumSno [hh] + net_snow [hh];
        }

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

        Drift [hh] = 0.0;
        Subl [hh] = 0.0;
        DriftH [hh] = 0.0;
        SublH [hh] = 0.0;
        Prob [hh] = 0.0;
        if (SWE [hh] > 0.0 && net_rain [hh] > 0.0)
        {
            rain_on_snow [hh] = net_rain [hh];
            cumrain_on_snow [hh] += net_rain [hh];
        }

        if (SWE [hh] > 0.0 && ! inhibit_bs [hh])
        {
            E_StubHt = Ht [hh] - Common :: DepthofSnow (SWE [hh]);
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
                Uten_Prob = (log (10.0 / Znod)) / PBSM_constants :: KARMAN * min < double > (0.0, Ustar - Ustn);
            }

            else
            {
                Uten_Prob = hru_u_;
            }

            ProbabilityThresholdNew (SWE [hh], hru_t [hh], Uten_Prob, Prob [hh], Ut, hru_newsnow [hh], SnowAge [hh], DrySnow [hh]);
            if (Prob [hh] > 0.001)
            {
                Ut = Ut * 0.8;
                Pbsm (E_StubHt, Ut, DriftH [hh], SublH [hh], hru_t [hh], hru_u_, hru_rh [hh], fetch [hh], N_S [hh], A_S [hh]);
                if (variation == VARIATION_2 || variation == VARIATION_3)
                {
                    DriftH [hh] = Drift_offset [hh] + DriftH [hh] * Drift_slope [hh];
                    SublH [hh] = Subl_offset [hh] + SublH [hh] * Subl_slope [hh];
                }

                Drift [hh] = DriftH [hh] * Prob [hh] / fetch [hh];
                if (! inhibit_subl [hh])
                {
                    Subl [hh] = SublH [hh] * Prob [hh];
                }

                if (Drift [hh] + Subl [hh] > SWE [hh])
                {
                    Subl [hh] = SWE [hh] * Subl [hh] / (Subl [hh] + Drift [hh]);
                    Drift [hh] = SWE [hh] - Subl [hh];
                }

                cumDrift [hh] = cumDrift [hh] + Drift [hh];
                cumSubl [hh] = cumSubl [hh] + Subl [hh];
                SWE [hh] = SWE [hh] - Subl [hh] - Drift [hh];
            }

        }

    }
    if (distrib [0] > 0.0)
    {
        double Drft = Drift [0] * distrib [0];
        SWE [0] += Drft;
        cumDriftIn [0] += Drft;
        cumBasinSnowGain [0] += Drft * hru_basin [0];
    }

    BasinSnowLoss [0] = 0.0;
    long LastN = 0;
    if (! inhibit_bs [0] && nhru == 1)
    {
        BasinSnowLoss [0] = Drift [0];
        cumBasinSnowLoss [0] += BasinSnowLoss [0];
    }

    for (long nn = LastN; chkStruct (nn); ++ nn) {
        if (distrib [nn] >= 0.0 && nn + 1 < nhru)
        {
            continue;
        }

        SumDrift = 0.0;
        for (long hhh = LastN; chkStruct (hhh, nn); ++ hhh)
            SumDrift += Drift [hhh] * hru_basin [hhh];
        if (SumDrift > 0.0)
        {
            for (long hh = LastN + 1; chkStruct (hh, nn + 1); ++ hh) {
                SWE_Max = SWEfromDepth (Ht [hh]);
                if (hh == nn)
                {
                    if (distrib [nn] > 0)
                    {
                        double In = SumDrift / hru_basin [hh];
                        if (SWE_Max > SWE [hh] + In)
                        {
                            SWE [hh] += In;
                            cumDriftIn [hh] += In;
                            transport = 0.0;
                        }

                        else
                        if (SWE_Max > SWE [hh])
                        {
                            cumDriftIn [hh] += (SWE_Max - SWE [hh]);
                            transport -= (In - (SWE_Max - SWE [hh])) * hru_basin [hh];
                            SWE [hh] += SWE_Max - SWE [hh];
                        }

                        else
                        {
                            transport = SumDrift;
                        }

                    }

                    else
                    if (distrib [nn] < 0)
                    {
                        SWE [hh] += SumDrift / hru_basin [hh];
                        cumDriftIn [hh] += SumDrift / hru_basin [hh];
                        transport = 0.0;
                    }

                    else
                    {
                        transport = SumDrift;
                    }

                    BasinSnowLoss [0] += (transport + Drift [hh] * hru_basin [hh]);
                    cumBasinSnowLoss [0] += (transport + Drift [hh] * hru_basin [hh]);
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
                        SWE [hh] += transport;
                    }

                    else
                    {
                        transport = SWE_Max - SWE [hh];
                        SWE [hh] = SWE_Max;
                    }

                    SumDrift -= transport * hru_basin [hh];
                    cumDriftIn [hh] += transport;
                }

            }
        }

        LastN = nn + 1;
    }
    for (hh = 0; chkStruct (); ++ hh) {
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
InstrumentLogger::instance()->log_instrument_log("</Classpbsm::run(void)@@@Classpbsm.cpp>");
}
void Classpbsm :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm::finish(bool good)@@@Classpbsm.cpp>");
    if (! good)
    {

InstrumentLogger::instance()->log_instrument_log("</Classpbsm::finish(bool good)@@@Classpbsm.cpp>");
        return;
    }

    double AllcumSubl = 0.0;
    double AllcumCover = cumBasinSnowGain [0] - cumBasinSnowLoss [0];
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (pbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSno [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumDrift [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumDriftIn [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSubl [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm)' cumCover   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSno [hh] + cumDriftIn [hh] - cumDrift [hh] - cumSubl [hh], hru_area [hh], basin_area [0], "*** SWE just before melt");
        LogMessageA (hh, string ("'" + Name + " (pbsm)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str (), SWE [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm)' SWE_change (mm) (mm*hru) (mm*hru/basin): ").c_str (), SWE [hh] - SWE_Init [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
        AllcumSubl += cumSubl [hh] * hru_area [hh];
        AllcumCover += (cumSno [hh] + cumDriftIn [hh] - cumDrift [hh] - cumSubl [hh]) * hru_area [hh];
    }
    LogMessage (string ("'" + Name + " (pbsm)' AllcumSubl  (mm*basin): ").c_str (), AllcumSubl, "*** cumulative sum of all HRUs cumSubl");
    LogMessage (string ("'" + Name + " (pbsm)' AllcumCover (mm*basin): ").c_str (), AllcumCover, "*** SWE just before melt cumulative sum of all HRUs cumCover");
    LogDebug (" ");
    LogMessage ("'pbsm' cumBasinSnowLoss (mm): ", cumBasinSnowLoss [0]);
    LogMessage ("'pbsm' cumBasinSnowGain (mm): ", cumBasinSnowGain [0]);
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</Classpbsm::finish(bool good)@@@Classpbsm.cpp>");
}