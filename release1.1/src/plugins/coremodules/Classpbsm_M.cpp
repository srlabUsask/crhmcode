#include "Classpbsm_M.h"
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
Classpbsm_M * Classpbsm_M :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm_M::klone(string name) const@@@Classpbsm_M.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::klone(string name) const@@@Classpbsm_M.cpp>");
    return new Classpbsm_M (name);
InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::klone(string name) const@@@Classpbsm_M.cpp>");
}
void Classpbsm_M :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm_M::decl(void)@@@Classpbsm_M.cpp>");
    Description = "'Calculates snow transport and sublimation (Pomeroy and Li, 1999). This module has enhanced transport distribution features.'";
    declstatvar ("SWE", TDim :: NHRU, "snow water equivalent", "(mm)", & SWE);
    declvar ("Subl", TDim :: NHRU, "interval sublimation", "(mm/int)", & Subl);
    declvar ("Drift", TDim :: NHRU, "interval transport", "(mm/int)", & Drift);
    declvar ("BasinSnowLoss", TDim :: BASIN, "transport out of basin", "(mm/int)", & BasinSnowLoss);
    declstatvar ("cumSubl", TDim :: NHRU, "cumulative sublimation", "(mm)", & cumSubl);
    declstatvar ("cumDrift", TDim :: NHRU, "cumulative transport from HRU", "(mm)", & cumDrift);
    declstatvar ("cumBasinSnowLoss", TDim :: BASIN, "cumulative transport out of basin", "(mm)", & cumBasinSnowLoss);
    declstatvar ("cumBasinSnowGain", TDim :: BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", & cumBasinSnowGain);
    decllocal ("cumDriftIn", TDim :: NHRU, "cumulative transport to HRU", "(mm)", & cumDriftIn);
    decllocal ("DrySnow", TDim :: NHRU, "DrySnow", "()", & DrySnow);
    decllocal ("SnowAge", TDim :: NHRU, "SnowAge", "()", & SnowAge);
    decllocal ("this_distrib", TDim :: NHRU, "current step distribution", "()", & this_distrib);
    declstatvar ("cumSno", TDim :: NHRU, "cumulative snow", "(mm)", & cumSno);
    declvar ("Prob", TDim :: NHRU, "Probability", "()", & Prob);
    declstatvar ("snowdepth", TDim :: NHRU, "depth of snow using Gray/Pomeroy", "(m)", & snowdepth);
    declvar ("Q_leeslope", TDim :: NHRU, "leeslope transport from HRU", "(mm)", & Q_leeslope);
    declvar ("Q_valley", TDim :: NHRU, "valley transport from HRU", "(mm)", & Q_valley);
    declvar ("Results", TDim :: NDEFN, "calulated distributions", "()", & Results, & Results_lay, nhru);
    declparam ("fetch", TDim :: NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", & fetch);
    declparam ("Ht", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", & Ht);
    declparam ("distrib", TDim :: NDEFN, "[0.0, 1.0, 1.0, 1.0]", "0.0", "99.0", "distribution array", "()", & distrib, & distrib_hru, nhru);
    decldiagparam ("N_S", TDim :: NHRU, "[320]", "0.1", "500", "vegetation number density", "(1/m^2)", & N_S);
    decldiagparam ("A_S", TDim :: NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", & A_S);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("hru_GSL", TDim :: NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(°)", & hru_GSL);
    decldiagparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", & inhibit_evap);
    declparam ("inhibit_bs", TDim :: NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", & inhibit_bs);
    decldiagparam ("inhibit_subl", TDim :: NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", & inhibit_subl);
    declparam ("eq_prof", TDim :: NHRU, "[0]", "0", "1", "0: use vegetation height, 1: use equilibrium profile depth as SWE_Max", "()", & eq_prof);
    declparam ("Zwind", TDim :: NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", & Zwind);
    decldiagparam ("Beta_M", TDim :: NHRU, "[170.0]", "32.0", "170.0", "ratio of element to surface drag for vegetation; 170 for stalks, 320 for shrubs", "()", & Beta_M);
    declparam ("hru_Ht", TDim :: NHRU, "[0.0]", "0.0", "1000.0", "HRU feature height(m)", "(m)", & hru_Ht);
    declgetvar ("*", "hru_t", "(°C)", & hru_t);
    declgetvar ("*", "hru_rh", "(%)", & hru_rh);
    declgetvar ("*", "hru_u", "(m/s)", & hru_u);
    declgetvar ("*", "hru_newsnow", "()", & hru_newsnow);
    declgetvar ("*", "net_snow", "(mm/int)", & net_snow);
InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::decl(void)@@@Classpbsm_M.cpp>");
}
void Classpbsm_M :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm_M::init(void)@@@Classpbsm_M.cpp>");
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
        if ((hh > 0) && (Ht [hh] < Ht [hh - 1]) && distrib [hh - 1] > 0)
        {
            CRHMException TExcept ("PBSM - vegetation heights not in ascending order", TExcept :: WARNING);
            LogError (TExcept);
        }

    }
    hru_basin = new double [nhru];
    for (hh = 0; hh < nhru; ++ hh)
        hru_basin [hh] = hru_area [hh] / basin_area [0];
InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::init(void)@@@Classpbsm_M.cpp>");
}
void Classpbsm_M :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm_M::run(void)@@@Classpbsm_M.cpp>");
    double Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
    double DriftH, SublH, CurrentDrift, SWE_Max, transport;
    double VB_distrib = 0.0;
    for (hh = 0; chkStruct (); ++ hh) {
        if (net_snow [hh] > 0.0)
        {
            SWE [hh] = SWE [hh] + net_snow [hh];
            cumSno [hh] = cumSno [hh] + net_snow [hh];
        }

        Drift [hh] = 0.0;
        Subl [hh] = 0.0;
        Prob [hh] = 0.0;
        Q_leeslope [hh] = 0.0;
        Q_valley [hh] = 0.0;
        if (SWE [hh] > 0.0 && ! inhibit_bs [hh])
        {
            E_StubHt = Ht [hh] - Common :: DepthofSnow (SWE [hh]);
            if (E_StubHt < 0.0001)
            {
                E_StubHt = 0.0001;
            }

            double d = 2.0 / 3.0 * E_StubHt;
            double Z = 0.123 * E_StubHt;
            double Wind = hru_u [hh] * log ((10.0 - d) / Z) / log ((Zwind [hh] - d) / Z);
            Ustar = 0.02264 * pow (Wind, 1.295f);
            if (E_StubHt > 0.01)
            {
                Znod = (sqr (Ustar) / 163.3f) + 0.5 * N_S [hh] * E_StubHt * A_S [hh];
                Lambda = N_S [hh] * A_S [hh] * E_StubHt;
                Ustn = Ustar * sqrt ((Beta_M [hh] * Lambda) / (1.0 + Beta_M [hh] * Lambda));
                Uten_Prob = (log (10.0 / Znod)) / PBSM_constants :: KARMAN * sqrt (Ustar - Ustn);
            }

            else
            {
                Uten_Prob = Wind;
            }

            ProbabilityThresholdNew (SWE [hh], hru_t [hh], Uten_Prob, Prob [hh], Ut, hru_newsnow [hh], SnowAge [hh], DrySnow [hh]);
            if (Prob [hh] > 0.001)
            {
                Ut = Ut * 0.8;
                Pbsm (E_StubHt, Ut, DriftH, SublH, hru_t [hh], Wind, hru_rh [hh], fetch [hh], N_S [hh], A_S [hh], hru_GSL [hh], hru_Ht [hh], Beta_M [hh], Q_leeslope [hh], Q_valley [hh]);
                Drift [hh] = DriftH * Prob [hh] / fetch [hh];
                if (! inhibit_subl [hh])
                {
                    Subl [hh] = SublH * Prob [hh];
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
    for (long hh = 0; chkStruct (hh); ++ hh) {
        if (distrib_hru [hh] [0] > 0.0)
        {
            double Drft = Drift [hh] * distrib_hru [hh] [0];
            SWE [hh] += Drft;
            cumDriftIn [hh] += Drft;
            cumBasinSnowGain [0] += Drft * hru_basin [hh];
        }

    }
    BasinSnowLoss [0] = 0.0;
    long LastN = 0;
    for (long nn = LastN; chkStruct (nn); ++ nn) {
        if (distrib [nn] >= 0.0 && nn + 1 < nhru)
        {
            continue;
        }

        for (long cc = LastN; chkStruct (cc, hh - 1); ++ cc) {
            CurrentDrift = Drift [cc] * hru_basin [cc];
            if (CurrentDrift > 0.0)
            {
                for (long hh = LastN + 1; chkStruct (hh, nn + 1); ++ hh) {
                    if (! eq_prof [hh])
                    {
                        SWE_Max = SWEfromDepth (Ht [hh]);
                    }

                    else
                    {
                        double tanEqSlope = (0.1818 * 100 * tan (hru_GSL [cc] * DEGtoRAD) + 0.4309 * 100 * tan (hru_GSL [hh] * DEGtoRAD) - 7.2887) / 100;
                        double EqProfDepth = hru_Ht [hh] / 2 * (1 - (tan (hru_GSL [hh] * DEGtoRAD) - tanEqSlope) / (tan (hru_GSL [hh] * DEGtoRAD) * (1 + tan (hru_GSL [hh] * DEGtoRAD) * tanEqSlope)));
                        SWE_Max = SWEfromDepth (EqProfDepth);
                    }

                    if (hh == nn)
                    {
                        if (fabs (distrib_hru [cc] [hh]) + distrib_hru [nhru - 1] [hh] > 0.0)
                        {
                            BasinSnowLoss [0] = CurrentDrift * distrib_hru [nhru - 1] [hh] / (fabs (distrib_hru [cc] [hh]) + distrib_hru [nhru - 1] [hh]);
                        }

                        else
                        {
                            BasinSnowLoss [0] = 0;
                        }

                        CurrentDrift -= BasinSnowLoss [0];
                        SWE [hh] += CurrentDrift / hru_basin [hh];
                        cumDriftIn [hh] += CurrentDrift / hru_basin [hh];
                        if (SWE [hh] > SWE_Max)
                        {
                            if (SWE [hh] - SWE_Max >= Drift [hh])
                            {
                                SWE [hh] -= Drift [hh];
                                BasinSnowLoss [0] += Drift [hh];
                            }

                            else
                            {
                                BasinSnowLoss [0] += SWE [hh] - SWE_Max;
                                SWE [hh] = SWE_Max;
                            }

                            BasinSnowLoss [0] *= hru_basin [hh];
                            cumBasinSnowLoss [0] += BasinSnowLoss [0];
                        }

                    }

                    else
                    if (SWE_Max > SWE [hh] && distrib_hru [cc] [hh] > 0.0)
                    {
                        double sum = distrib_hru [nhru - 1] [cc];
                        for (long jj = hh; chkStruct (jj, nn + 1); jj ++) {
                            Results_lay [cc] [jj] = 0.0;
                            if (distrib_hru [cc] [jj] != 88 && distrib_hru [cc] [jj] != 99)
                            {
                                sum += fabs (distrib_hru [cc] [jj]);
                            }

                        }
                        if (distrib_hru [cc] [hh] == 88 && Q_leeslope [hh] >= 0.0)
                        {
                            if (Q_leeslope [hh] > 0.0)
                            {
                                this_distrib [hh] = (1 - sum) * Q_leeslope [hh] / (Q_leeslope [hh] + Q_valley [hh]);
                            }

                            else
                            {
                                this_distrib [hh] = 0.0;
                            }

                            Results_lay [cc] [hh] = this_distrib [hh];
                            for (long kk = hh + 1; chkStruct (kk, nn + 1); kk ++) {
                                if (distrib_hru [cc] [kk] == 99 && Q_valley [hh] >= 0.0)
                                {
                                    if (Q_valley [hh] > 0.0)
                                    {
                                        VB_distrib = (1 - sum) * Q_valley [hh] / (Q_leeslope [hh] + Q_valley [hh]);
                                    }

                                    else
                                    {
                                        VB_distrib = 0.0;
                                    }

                                }

                            }
                        }

                        else
                        if (distrib_hru [cc] [hh] == 99)
                        {
                            this_distrib [hh] = VB_distrib;
                            Results_lay [cc] [hh] = this_distrib [hh];
                        }

                        else
                        {
                            this_distrib [hh] = distrib_hru [cc] [hh];
                        }

                        transport = CurrentDrift * fabs (this_distrib [hh]) / hru_basin [hh] / 1;
                        if (SWE_Max > SWE [hh] + transport)
                        {
                            SWE [hh] += transport;
                        }

                        else
                        {
                            transport = SWE_Max - SWE [hh];
                            SWE [hh] = SWE_Max;
                        }

                        CurrentDrift -= transport * hru_basin [hh];
                        cumDriftIn [hh] += transport;
                    }

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
InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::run(void)@@@Classpbsm_M.cpp>");
}
void Classpbsm_M :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm_M::finish(bool good)@@@Classpbsm_M.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (pbsm_M)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSno [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm_M)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumDrift [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm_M)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumDriftIn [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm_M)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSubl [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm_M)' cumCover   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSno [hh] + cumDriftIn [hh] - cumDrift [hh] - cumSubl [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (pbsm_M)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str (), SWE [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
    LogMessage ("'pbsm_M' cumulative basin snow loss (mm): ", cumBasinSnowLoss [0]);
    LogMessage ("'pbsm_M' cumulative basin snow gain (mm): ", cumBasinSnowGain [0]);
    LogDebug (" ");
    delete [] hru_basin;
    hru_basin = NULL;
InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::finish(bool good)@@@Classpbsm_M.cpp>");
}
void Classpbsm_M :: Sum (double TQsalt, double TQsusp, double SBsum, double SBsalt, double & DriftH, double & SublH)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm_M::Sum(double TQsalt, double TQsusp, double SBsum, double SBsalt, double & DriftH, double & SublH)@@@Classpbsm_M.cpp>");
    if ((SBsum + SBsalt) >= 0.0)
    {
        SublH = 0.0;
    }

    else
    {
        SublH = (SBsum + SBsalt) * (- 1E+3);
    }

    DriftH = (TQsalt + TQsusp);
    SublH = SublH * Global :: Interval * 3600 * 24 / 1000.0;
    DriftH = DriftH * Global :: Interval * 3600 * 24;
InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::Sum(double TQsalt, double TQsusp, double SBsum, double SBsalt, double & DriftH, double & SublH)@@@Classpbsm_M.cpp>");
}
void Classpbsm_M :: Pbsm (double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch, long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley)
{
InstrumentLogger::instance()->log_instrument_log("<Classpbsm_M::Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch, long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley)@@@Classpbsm_M.cpp>");
    double A, Alpha, B, Bd, Bound, C, Diff, DmDt, Es, H, Htran, Hsalt, Inc, Lamb, Lambda, Lb, Mpm, Mpr, Nh, Nsalt, Nz, Nuss, Omega, TQsalt, TQsum, Qz, RauTerm, Temp, Reyn, SBsalt, Sbz, SBsum, SigmaZ, Sigma2, SvDens, Usthr, Ustar, UstarZ, Uz, Vs, Vsalt, Sigma, Vsusp, Z, Zr, Zstb, tX, tH;
    Zstb = 0.005 * N_S * A_S * E_StubHt * 100.0;
    Lambda = N_S * A_S * E_StubHt;
    Sigma = (M_PI * A_S) / (4.0 * E_StubHt);
    TQsalt = 0.0;
    TQsum = 0.0;
    SBsalt = 0.0;
    SBsum = 0.0;
    DriftH = 0.0;
    SublH = 0.0;
    Temp = t + 273.0;
    if ((Temp < 0.0) || (u < 1.0) || (rh < 0.01))
    {

InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch, long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley)@@@Classpbsm_M.cpp>");
        return;
    }

    if (rh >= 1.0)
    {
        rh = rh / 100.0;
    }

    Lamb = 0.000076843 * Temp + 0.003130762;
    Diff = 2.06e-5f * pow (Temp / 273.0f, 1.75f);
    B = PBSM_constants :: LATH * PBSM_constants :: M / (PBSM_constants :: R * Temp) - 1.0;
    Es = 611.15f * exp (22.452f * (Temp - 273.0f) / Temp);
    SvDens = (Es * PBSM_constants :: M) / (PBSM_constants :: R * Temp);
    Sigma2 = rh - 1.0;
    if (u > Uthr)
    {
        Usthr = 0.03697f * Uthr;
        Ustar = 0.02264f * pow (u, 1.295f);
        if (E_StubHt > 0.0001)
        {
            RauTerm = 1.0 / ((1.0 - Sigma * Lambda) * (1.0 + Beta_M * Lambda));
        }

        else
        {
            RauTerm = 1.0;
        }

        Hsalt = PBSM_constants :: C2 / (2.0f * PBSM_constants :: g) * sqr (Ustar);
        Nsalt = 2.0 * PBSM_constants :: rho / (PBSM_constants :: C2 * PBSM_constants :: C3 * Ustar) * (RauTerm - sqr (Usthr) / sqr (Ustar));
        if (Nsalt <= 0.0)
        {
            Sum (TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);

InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch, long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley)@@@Classpbsm_M.cpp>");
            return;
        }

        TQsalt = PBSM_constants :: C1 * PBSM_constants :: rho * Usthr / (PBSM_constants :: g * PBSM_constants :: C3 * Ustar) * (sqr (Ustar) * RauTerm - sqr (Usthr));
        Mpr = 100E-6;
        Htran = 0.9 * M_PI * sqr (Mpr) * PBSM_constants :: Qstar;
        Alpha = 5.0;
        SigmaZ = Sigma2 * (1.019 + 0.027 * log (Hsalt));
        if (SigmaZ > - 0.01)
        {
            SigmaZ = - 0.01;
        }

        Vsalt = 0.6325 * Ustar + 2.3 * Usthr;
        Reyn = (2.0 * Mpr * Vsalt) / 1.88E-5;
        Nuss = 1.79 + 0.606 * sqrt (Reyn);
        A = Lamb * Temp * Nuss;
        C = 1.0 / (Diff * SvDens * Nuss);
        DmDt = ((2.0 * M_PI * Mpr * SigmaZ) - (Htran * B / A)) / ((PBSM_constants :: LATH * B / A) + C);
        Mpm = 4.0 / 3.0 * M_PI * PBSM_constants :: DICE * Mpr * sqr (Mpr) * (1.0 + 3.0 / Alpha + 2.0 / sqr (Alpha));
        Vs = DmDt / Mpm;
        SBsalt = Vs * Nsalt * Hsalt;
        Zr = 0.05628 * Ustar;
        Alpha = 15.0;
        Inc = 0.0001;
        TQsum = 0;
        SBsum = 0;
        Z = Zr + Inc;
        while (Z <= 0.15) {
            Nz = 0.8 * exp (- 1.55 * (pow (0.05628f * Ustar, - 0.544f) - pow (Z, - 0.544f)));
            if (Nz <= Nsalt)
            {
                goto Ten;
            }

            Z = Z + Inc;
        }
        Ten: Lb = Z + Inc;
        Z = Lb;
        Inc = 0.001;
        Bd = 1.0;
        Bound = PBSM_constants :: ZD + (PBSM_constants :: KARMAN2 * (Fetch - PBSM_constants :: XD) * pow (log (Bd * 162.926f / sqr (Ustar)) * log (PBSM_constants :: ZD * 162.926f / sqr (Ustar)), - 0.5f));
        while (fabs (Bound - Bd) > 0.001) {
            Bd = Bound;
            Bound = PBSM_constants :: ZD + (PBSM_constants :: KARMAN2 * (Fetch - PBSM_constants :: XD) * pow (log (Bd * 162.926f / sqr (Ustar)) * log (PBSM_constants :: ZD * 162.926f / sqr (Ustar)), - 0.5f));
        }
        Qdist_leeslope = 0;
        Qdist_valley = 0;
        Twenty: H = Z + Inc;
        while (H <= Bound) {
            Nh = 0.8 * exp (- 1.55f * (pow (0.05628f * Ustar, - 0.544f) - pow (H, - 0.544f)));
            Nz = Nh;
            UstarZ = Ustar * pow (1.2f / (1.2f + Nz), 0.5f);
            Uz = (UstarZ / PBSM_constants :: KARMAN) * log (H / ((0.00613f * sqr (Ustar)) + Zstb));
            if (Uz > 0)
            {
                if (height <= 0)
                {
                    tX = 0;
                }

                else
                {
                    tX = height / (Uz * tan (GSL * DEGtoRAD));
                }

                Mpr = 4.6e-5 * pow (H, - 0.258f);
                if (H >= 5.0)
                {
                    Mpr = 30E-6f;
                }

                Htran = 0.9 * M_PI * sqr (Mpr) * PBSM_constants :: Qstar;
                Alpha = 4.08 + 12.6 * H;
                if (H >= 1.5)
                {
                    Alpha = 25.0;
                }

                SigmaZ = Sigma2 * (1.019 + 0.027 * log (H));
                if (SigmaZ > - 0.01)
                {
                    SigmaZ = - 0.01;
                }

                Omega = 1.1e7f * pow (Mpr, 1.8f);
                tH = (height + H) / Omega;
                Vsusp = Omega + 0.0106f * pow (Uz, 1.36f);
                Reyn = (2.0f * Mpr * Vsusp) / 1.88e-5f;
                Nuss = 1.79f + 0.606f * sqrt (Reyn);
                A = Lamb * Temp * Nuss;
                C = 1.0 / (Diff * SvDens * Nuss);
                DmDt = ((2.0f * M_PI * Mpr * SigmaZ) - (Htran * B / A)) / ((PBSM_constants :: LATH * B / A) + C);
                Mpm = 1.333f * M_PI * PBSM_constants :: DICE * sqr (Mpr) * Mpr * (1.0f + 3.0f / Alpha + 2.0f / sqr (Alpha));
                Vs = DmDt / Mpm;
                Sbz = Vs * Nz * Inc;
                SBsum = SBsum + Sbz;
                Qz = Nz * Uz * Inc;
                if (tH < tX)
                {
                    Qdist_leeslope += Qz;
                }

                else
                {
                    Qdist_valley += Qz;
                }

                if (H >= 5.0)
                {
                    Qz = 0.0;
                }

                TQsum = TQsum + Qz;
                if (Nz >= 1e-5)
                {
                    if (((H - Inc) >= 0.5) && (H < 0.6))
                    {
                        Inc = 0.1;
                        Z = 0.5;
                        goto Twenty;
                    }

                }

                else
                {
                    Sum (TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);

InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch, long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley)@@@Classpbsm_M.cpp>");
                    return;
                }

            }

            else
            {
                TQsalt = 0.0;
                TQsum = 0.0;
                SBsalt = 0.0;
                SBsum = 0.0;
                Sum (TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);

InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch, long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley)@@@Classpbsm_M.cpp>");
                return;
            }

            H = H + Inc;
        }
    }

    Sum (TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
InstrumentLogger::instance()->log_instrument_log("</Classpbsm_M::Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch, long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley)@@@Classpbsm_M.cpp>");
}