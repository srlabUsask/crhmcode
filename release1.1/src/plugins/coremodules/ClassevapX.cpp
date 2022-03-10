#include "ClassevapX.h"
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
ClassevapX * ClassevapX :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::klone(string name) const@@@ClassevapX.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapX::klone(string name) const@@@ClassevapX.cpp>");
    return new ClassevapX (name);
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::klone(string name) const@@@ClassevapX.cpp>");
}
void ClassevapX :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::decl(void)@@@ClassevapX.cpp>");
    Description = "'Calculates interval evaporation. Parameter \"evap_type\" selects Granger/Priestley-Taylor/Penman-Monteith.'";
    declvar ("hru_actet", TDim :: NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", & hru_actet);
    declstatdiag ("hru_cum_actet", TDim :: NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", & hru_cum_actet);
    declvar ("hru_evap", TDim :: NHRU, "interval evaporation", "(mm/int)", & evap);
    declvar ("hru_evapD", TDim :: NHRU, "daily sum of interval evaporation", "(mm/d)", & evap_D);
    declstatdiag ("hru_cum_evap", TDim :: NHRU, "cumulative interval evaporation", "(mm)", & cum_evap);
    decllocal ("Granger_D", TDim :: NHRU, "daily Granger evaporation", "(mm/d)", & Granger_D);
    decldiag ("rc", TDim :: NHRU, "stomatal resistance (used by Penman-Monteith and Dalton)", "(s/m)", & rc);
    decllocal ("Pa", TDim :: NHRU, "Atmospheric pressure", "(kPa)", & Pa);
    declparam ("Ht", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", & Ht);
    declparam ("evap_type", TDim :: NHRU, "0", "0", "2", "Evaporation method for this HRU, 0 = Granger, 1 = Priestley-Taylor, 2 = Penman-Monteith.", "()", & evap_type);
    declparam ("hru_elev", TDim :: NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", & hru_elev);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", & inhibit_evap);
    decldiagparam ("F_Qg", TDim :: NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", & F_Qg);
    declparam ("Zwind", TDim :: NHRU, "[10]", "0.01", "100.0", "wind measurement height (used by Penman-Monteith).", "(m)", & Zwind);
    declparam ("rcs", TDim :: NHRU, "[25]", "25.0", "5000.0", "stomatal resistance (used by Penman-Monteith).", "(s/m)", & rcs);
    declparam ("Htmax", TDim :: NHRU, "[0.1]", "0.1", "100.0", "maximum vegetation height (used by Penman-Monteith).", "(m)", & Htmax);
    declparam ("LAImax", TDim :: NHRU, "[3.0]", "0.0", "20.0", "maximum leaf area index (used by Penman-Monteith).", "(m^2/m^2)", & LAImax);
    declparam ("LAImin", TDim :: NHRU, "[0.0]", "0.0", "20.0", "minimum leaf area index (used by Penman-Monteith).", "(m^2/m^2)", & LAImin);
    declparam ("s", TDim :: NHRU, "[1]", "0", "1", "seasonal growth index (used by Penman-Monteith).", "()", & s);
    declparam ("PM_method", TDim :: NHRU, "[0]", "0", "2", "Penman-Monteith method (used by Penman-Monteith), 0 = RC min, 1 = LAI, 2 = bulk.", "()", & PM_method);
    declparam ("soil_type", TDim :: NHRU, "[2]", " 1", "12", "HRU soil type (used by Penman-Monteith) [1->11]: sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay.", "()", & soil_type);
    declparam ("soil_Depth", TDim :: NHRU, "[1.0]", "0.0", "10.0", "depth of soil column (used by Penman-Monteith).", "(m)", & soil_Depth);
    declgetvar ("*", "soil_moist", "(mm)", & soil_moist);
    declgetvar ("*", "Rn", "(mm/m^2*int)", & Rn);
    declgetvar ("*", "RnD", "(mm/m^2*d)", & RnD);
    declgetvar ("*", "RnD_POS", "(mm/m^2*d)", & RnD_POS);
    declgetvar ("*", "hru_t", "(°C)", & hru_t);
    declgetvar ("*", "hru_u", "(m/s)", & hru_u);
    declgetvar ("*", "hru_ea", "(kPa)", & hru_ea);
    declgetvar ("*", "hru_tmean", "(°C)", & hru_tmean);
    declgetvar ("*", "hru_umean", "(m/s)", & hru_umean);
    declgetvar ("*", "hru_eamean", "kPa", & hru_eamean);
    declreadobs ("Qsi", TDim :: NHRU, "incident short-wave", "(W/m^2)", & Qsi, HRU_OBS_Q, false);
    declreadobs ("RnObs", TDim :: NHRU, "all-wave", "(W/m^2)", & RnObs, HRU_OBS_Q, true);
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::decl(void)@@@ClassevapX.cpp>");
}
void ClassevapX :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::init(void)@@@ClassevapX.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        Pa [hh] = 101.3f * pow ((293.0f - 0.0065f * hru_elev [hh]) / 293.0f, 5.26f);
        cum_evap [hh] = 0.0;
        hru_cum_actet [hh] = 0.0;
        Granger_D [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::init(void)@@@ClassevapX.cpp>");
}
void ClassevapX :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::run(void)@@@ClassevapX.cpp>");
    const double Cp = 1.005;
    double Q, Z0, d, U, ra, f1, f2, f3, f4, Soil_Moist, p, rcstar, LAI, D, G;
    long nstep = getstep () % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
        evap [hh] = 0.0;
        hru_actet [hh] = 0.0;
        if (inhibit_evap [hh])
        {
            evap_D [hh] = 0.0;
            Granger_D [hh] = 0.0;
            continue;
        }

        if (nstep == 1 || Global :: Freq == 1)
        {
            evap_D [hh] = 0.0;
            Granger_D [hh] = 0.0;
            if (evap_type [hh] == 0)
            {
                Q = RnD [hh] * (1.0 - F_Qg [hh]);
                if (Q > 0.0)
                {
                    double Eal = fdaily (hru_umean [hh], Ht [hh]) * (Common :: estar (hru_tmean [hh]) - hru_eamean [hh]);
                    if (Eal > 0.0)
                    {
                        D = Eal / (Eal + Q);
                        if (D > 1.0)
                        {
                            D = 1.0;
                        }

                    }

                    else
                    {
                        D = 0.0;
                    }

                    G = 1.0 / (0.793 + 0.2 * exp (4.902 * D)) + 0.006 * D;
                    Granger_D [hh] = (delta (hru_tmean [hh]) * G * Q + gamma (Pa [hh], hru_tmean [hh]) * G * Eal) / (delta (hru_tmean [hh]) * G + gamma (Pa [hh], hru_tmean [hh]));
                }

            }

        }

        Q = Rn [hh] * (1.0 - F_Qg [hh]);
        switch (evap_type [hh]) {
        case 0:
            if (Q > 0.0 && Granger_D [hh] > 0.0 && RnD_POS [hh] > 0.0)
            {
                evap [hh] = Q / RnD_POS [hh] / (1.0 - F_Qg [hh]) * Granger_D [hh];
            }

            break;
        case 1:
            if (Q > 0.0)
            {
                evap [hh] = 1.26 * delta (hru_t [hh]) * Q / (delta (hru_t [hh]) + gamma (Pa [hh], hru_t [hh]));
            }

            break;
        case 2:
            if (soil_moist [hh] > 0.0)
            {
                Z0 = Ht [hh] / 7.6;
                d = Ht [hh] * 0.67;
                U = hru_u [hh];
                ra = sqr (log ((Zwind [hh] - d) / Z0)) / (sqr (CRHM_constants :: kappa) * U);
                rcstar = rcs [hh];
                if (PM_method [hh] == 1)
                {
                    LAI = Ht [hh] / Htmax [hh] * (LAImin [hh] + s [hh] * (LAImax [hh] - LAImin [hh]));
                    rcstar = rcs [hh] * LAImax [hh] / LAI;
                }

                f1 = 1.0;
                if (Qsi [hh] > 0.0)
                {
                    f1 = max < double > (1.0, 500.0 / (Qsi [hh]) - 1.5);
                }

                f2 = max < double > (1.0, 2.0 * (Common :: estar (hru_t [hh]) - hru_ea [hh]));
                Soil_Moist = (soil_moist [hh] / soil_Depth [hh] + SetSoilproperties [soil_type [hh]] [1]) / SetSoilproperties [soil_type [hh]] [3];
                p = soilproperties [soil_type [hh]] [AIRENT] * pow (soilproperties [soil_type [hh]] [PORE] / Soil_Moist, soilproperties [soil_type [hh]] [PORESZ]);
                f3 = max < double > (1.0, p / 40.0);
                f4 = 1.0;
                if (hru_t [hh] < 5.0 || hru_t [hh] > 40.0)
                {
                    f4 = 5000 / 50;
                }

                if (RnObs && RnObs [hh] <= 0)
                {
                    rc [hh] = 5000.0;
                }

                else
                if (Qsi [hh] <= 0)
                {
                    rc [hh] = 5000.0;
                }

                else
                {
                    rc [hh] = rcstar * f1 * f2 * f3 * f4;
                    if (rc [hh] > 5000.0)
                    {
                        rc [hh] = 5000.0;
                    }

                }

                double ratio_rs_ra = rc [hh] / ra;
                evap [hh] = (delta (hru_t [hh]) * Q * Global :: Freq + (RHOa (hru_t [hh], hru_ea [hh], Pa [hh]) * Cp / (lambda (hru_t [hh]) * 1e3) * (Common :: estar (hru_t [hh]) - hru_ea [hh]) / (ra / 86400))) / (delta (hru_t [hh]) + gamma (Pa [hh], hru_t [hh]) * (1.0 + ratio_rs_ra)) / Global :: Freq;
            }

            break;
        }
        cum_evap [hh] += evap [hh];
        evap_D [hh] += evap [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::run(void)@@@ClassevapX.cpp>");
}
void ClassevapX :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::finish(bool good)@@@ClassevapX.cpp>");
    double Allcum_evap = 0.0;
    double Allcum_actet = 0.0;
    string Evap_names [] = {"Granger", "Priestley-Taylor", "Penman-Monteith", "Dalton Bulk transfer"};
    for (hh = 0; chkStruct (); ++ hh) {
        string s = "**** " + Evap_names [evap_type [hh]] + " ****";
        LogMessageA (hh, string ("'" + Name + " (evapX)' hru_cum_evap (mm) (mm*hru) (mm*hru/basin): ").c_str (), evap [hh], hru_area [hh], basin_area [0], s.c_str ());
        LogMessageA (hh, string ("'" + Name + " (evapX)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str (), hru_cum_actet [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
        Allcum_evap += cum_evap [hh] * hru_area [hh];
        Allcum_actet += hru_cum_actet [hh] * hru_area [hh];
    }
    LogMessage (string ("'" + Name + " (evapX)' Allcum_evap  (mm*basin): ").c_str (), Allcum_evap / basin_area [0]);
    LogMessage (string ("'" + Name + " (evapX)' Allcum_actet (mm*basin): ").c_str (), Allcum_actet / basin_area [0]);
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::finish(bool good)@@@ClassevapX.cpp>");
}
double ClassevapX :: gamma (double Pa, double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::gamma(double Pa, double t)@@@ClassevapX.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapX::gamma(double Pa, double t)@@@ClassevapX.cpp>");
    return (0.00163 * Pa / lambda (t));
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::gamma(double Pa, double t)@@@ClassevapX.cpp>");
}
double ClassevapX :: lambda (double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::lambda(double t)@@@ClassevapX.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapX::lambda(double t)@@@ClassevapX.cpp>");
    return (2.501 - 0.002361 * t);
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::lambda(double t)@@@ClassevapX.cpp>");
}
double ClassevapX :: delta (double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::delta(double t)@@@ClassevapX.cpp>");
    if (t > 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassevapX::delta(double t)@@@ClassevapX.cpp>");
        return (2504.0 * exp (17.27 * t / (t + 237.3)) / sqr (t + 237.3));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassevapX::delta(double t)@@@ClassevapX.cpp>");
        return (3549.0 * exp (21.88 * t / (t + 265.5)) / sqr (t + 265.5));
    }

InstrumentLogger::instance()->log_instrument_log("</ClassevapX::delta(double t)@@@ClassevapX.cpp>");
}
double ClassevapX :: fdaily (double u, double Ht)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::fdaily(double u, double Ht)@@@ClassevapX.cpp>");
    double Z0 = Ht * 100.0 / 7.6;
    double a = 8.19 + 0.22 * Z0;
    double b = 1.16 + 0.08 * Z0;

InstrumentLogger::instance()->log_instrument_log("</ClassevapX::fdaily(double u, double Ht)@@@ClassevapX.cpp>");
    return a + b * u;
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::fdaily(double u, double Ht)@@@ClassevapX.cpp>");
}
double ClassevapX :: RHOa (double t, double ea, double Pa)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapX::RHOa(double t, double ea, double Pa)@@@ClassevapX.cpp>");
    const double R0 = 2870;

InstrumentLogger::instance()->log_instrument_log("</ClassevapX::RHOa(double t, double ea, double Pa)@@@ClassevapX.cpp>");
    return (1E4 * Pa / (R0 * (273.15 + t)) * (1.0 - 0.379 * (ea / Pa)));
InstrumentLogger::instance()->log_instrument_log("</ClassevapX::RHOa(double t, double ea, double Pa)@@@ClassevapX.cpp>");
}