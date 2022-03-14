#include "ClassevapD_Resist.h"
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
ClassevapD_Resist * ClassevapD_Resist :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::klone(string name) const@@@ClassevapD_Resist.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::klone(string name) const@@@ClassevapD_Resist.cpp>");
    return new ClassevapD_Resist (name);
InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::klone(string name) const@@@ClassevapD_Resist.cpp>");
}
void ClassevapD_Resist :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::decl(void)@@@ClassevapD_Resist.cpp>");
    Description = "'Evaluation daily evaporation model using Penman-Monteith and Dalton Bulk transfer.'";
    declvar ("hru_actet", TDim :: NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", & hru_actet);
    declstatdiag ("hru_cum_actet", TDim :: NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", & hru_cum_actet);
    declvar ("hru_evapD", TDim :: NHRU, "daily evaporation", "(mm/d)", & evapD);
    declstatdiag ("hru_cum_evap", TDim :: NHRU, "cumulative interval evaporation", "(mm)", & cum_evap);
    decldiag ("rc", TDim :: NHRU, "stomatal resistance (Penman-Monteith)", "(s/m)", & rc);
    decllocal ("Pa", TDim :: NHRU, "Atmospheric pressure", "(kPa)", & Pa);
    declparam ("Ht", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", & Ht);
    decldiagparam ("Zwind", TDim :: NHRU, "[10.0]", "0.0", "100.0", "Wind instrument height", "(m)", & Zwind);
    declparam ("evap_type", TDim :: NHRU, "0", "0", "1", "Evaporation method for this HRU, 0 = Penman-Monteith, 1 = Dalton bulk transfer", "()", & evap_type);
    declparam ("hru_elev", TDim :: NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", & hru_elev);
    declparam ("basin_area", TDim :: BASIN, "1", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", & inhibit_evap);
    decldiagparam ("F_Qg", TDim :: NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", & F_Qg);
    declparam ("rcs", TDim :: NHRU, "[25]", "25.0", "5000.0", "stomatal resistance (Penman-Monteith/Dalton bulk transfer)", "(s/m)", & rcs);
    declparam ("Htmax", TDim :: NHRU, "[0.1]", "0.1", "100.0", "maximum vegetation height (Penman-Monteith)", "(m)", & Htmax);
    declparam ("LAImax", TDim :: NHRU, "[3.0]", "0.0", "20.0", "maximum leaf area index (Penman-Monteith)", "(m^2/m^2)", & LAImax);
    declparam ("LAImin", TDim :: NHRU, "[0.0]", "0.0", "20.0", "minimum leaf area index (Penman-Monteith)", "(m^2/m^2)", & LAImin);
    declparam ("s", TDim :: NHRU, "[1]", "0", "1", "seasonal growth index (Penman-Monteith)", "()", & s);
    declparam ("PM_method", TDim :: NHRU, "[0]", "0", "2", "Penman-Monteith method, 0 = RC min, 1 = LAI, 2 = bulk", "()", & PM_method);
    declparam ("soil_type", TDim :: NHRU, "[2]", " 1", "12", "HRU soil type (1->11): sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay", "()", & soil_type);
    declparam ("soil_Depth", TDim :: NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", & soil_Depth);
    declgetvar ("*", "RnD", "(mm/m^2*d)", & RnD);
    declgetvar ("*", "hru_tmean", "(" + string (DEGREE_CELSIUS) + ")", & hru_tmean);
    declgetvar ("*", "hru_umean", "(m/s)", & hru_umean);
    declgetvar ("*", "hru_eamean", "(kPa)", & hru_eamean);
    declgetvar ("*", "soil_moist", "(mm)", & soil_moist);
    declreadobs ("Qsi", TDim :: NHRU, "incident short-wave", "(W/m^2)", & Qsi, HRU_OBS_Q, false);
    declobsfunc ("Qsi", "Qsi_mean", & Qsi_mean, TFun :: AVG, NULL, false);
    declreadobs ("Ts", TDim :: NHRU, "surface temperature", "(" + string (DEGREE_CELSIUS) + ")", & Ts, HRU_OBS_misc, true);
    declobsfunc ("Ts", "Tsmean", & Tsmean, TFun :: AVG, NULL, true);
InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::decl(void)@@@ClassevapD_Resist.cpp>");
}
void ClassevapD_Resist :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::init(void)@@@ClassevapD_Resist.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        if (evap_type [hh] == 1 && Ts == NULL)
        {
            CRHMException TExcept ("'evapD' Ts observation not available for Dalton bulk transport method!.", TExcept :: TERMINATE);
            LogError (TExcept);
        }

        Pa [hh] = 101.3f * pow ((293.0f - 0.0065f * hru_elev [hh]) / 293.0f, 5.26f);
        evapD [hh] = 0.0;
        cum_evap [hh] = 0.0;
        hru_cum_actet [hh] = 0.0;
        if (Ht [hh] > Zwind [hh] / 0.67 && evap_type [hh] != 0)
        {
            CRHMException TExcept ("Vegetation height greater than wind reference height, i.e. (Ht > Zwind/0.67)!", TExcept :: WARNING);
            LogError (TExcept);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::init(void)@@@ClassevapD_Resist.cpp>");
}
void ClassevapD_Resist :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::run(void)@@@ClassevapD_Resist.cpp>");
    double Q, rcstar, Z0, d, U, f1, f2, f3, f4, p, ra, ratio_rs_ra;
    const double Cp = 1.005;
    long nstep = getstep () % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
        if (inhibit_evap [hh] && nstep == 1)
        {
            evapD [hh] = 0.0;
            hru_actet [hh] = 0.0;
            continue;
        }

        if (nstep == 1 || Global :: Freq == 1)
        {
            hru_actet [hh] = 0.0;
            Q = RnD [hh] * (1.0 - F_Qg [hh]);
            double Soil_Moist = (soil_moist [hh] / soil_Depth [hh] + SetSoilproperties [soil_type [hh]] [1]) / SetSoilproperties [soil_type [hh]] [3];
            switch (evap_type [hh]) {
            case 0:
                Z0 = Ht [hh] / 7.6;
                d = Ht [hh] * 0.67;
                U = max < double > (0.1, hru_umean [hh]);
                ra = sqr (log ((Zwind [hh] - d) / Z0)) / (sqr (CRHM_constants :: kappa) * U);
                rcstar = rcs [hh];
                if (PM_method [hh] == 1)
                {
                    double LAI = Ht [hh] / Htmax [hh] * (LAImin [hh] + s [hh] * (LAImax [hh] - LAImin [hh]));
                    rcstar = rcs [hh] * LAImax [hh] / LAI;
                }

                f1 = max < double > (1.0, 500.0 / (Qsi_mean [hh]) - 1.5);
                f2 = max < double > (1.0, 2.0 * (estar (hru_tmean [hh]) - hru_eamean [hh]));
                if (f2 < 0.0)
                {
                    f2 = 0.0;
                }

                p = soilproperties [soil_type [hh]] [AIRENT] * pow (1.0 / Soil_Moist, soilproperties [soil_type [hh]] [PORESZ]);
                f3 = max < double > (1.0, p / 40.0);
                f4 = 1.0;
                if (hru_tmean [hh] < 0.0 || hru_tmean [hh] > 40.0)
                {
                    f4 = 5000 / rcs [hh];
                }

                rc [hh] = rcstar * f1 * f2 * f3 * f4;
                if (rc [hh] > 5000.0)
                {
                    rc [hh] = 5000.0;
                }

                ratio_rs_ra = rc [hh] / ra;
                evapD [hh] = (delta (hru_tmean [hh]) * Q + (RHOa (hru_tmean [hh], hru_eamean [hh], Pa [hh]) * Cp / (lambda (hru_tmean [hh]) * 1e3) * (Common :: estar (hru_tmean [hh]) - hru_eamean [hh]) / (ra / 86400))) / (delta (hru_tmean [hh]) + gamma (Pa [hh], hru_tmean [hh]) * (1.0 + ratio_rs_ra));
                break;
            case 1:
                Z0 = Ht [hh] / 7.6;
                d = Ht [hh] * 0.67;
                U = max < double > (0.1, hru_umean [hh]);
                ra = sqr (log ((Zwind [hh] - d) / Z0)) / (sqr (CRHM_constants :: kappa) * U);
                rcstar = rcs [hh];
                f1 = 1.0;
                if (Qsi_mean [hh] > 0.0)
                {
                    f1 = max < double > (1.0, 500.0 / (Qsi_mean [hh]) - 1.5);
                }

                f2 = max < double > (1.0, 2.0 * (estar (hru_tmean [hh]) - hru_eamean [hh]));
                if (f2 < 0.0)
                {
                    f2 = 0.0;
                }

                p = soilproperties [soil_type [hh]] [AIRENT] * pow (1.0 / Soil_Moist, soilproperties [soil_type [hh]] [PORESZ]);
                f3 = max < double > (1.0, p / 40.0);
                f4 = 1.0;
                if (hru_tmean [hh] < 5.0 || hru_tmean [hh] > 40.0)
                {
                    f4 = 5000 / rcs [hh];
                }

                rc [hh] = rcstar * f1 * f2 * f3 * f4;
                if (rc [hh] > 5000.0)
                {
                    rc [hh] = 5000.0;
                }

                double qs = 0.622 * Common :: estar (Tsmean [hh]) / (Pa [hh] - Common :: estar (Tsmean [hh]) * 0.378);
                double q = 0.622 * hru_eamean [hh] / (Pa [hh] - hru_eamean [hh] * 0.378);
                evapD [hh] = RHOa (hru_tmean [hh], hru_eamean [hh], Pa [hh]) * (qs - q) / ((ra + rc [hh]) / 86400);
                break;
            }
            cum_evap [hh] += evapD [hh];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::run(void)@@@ClassevapD_Resist.cpp>");
}
void ClassevapD_Resist :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::finish(bool good)@@@ClassevapD_Resist.cpp>");
    string Evap_names [] = {"Granger", "Priestley-Taylor", "Penman-Monteith", "Dalton Bulk transfer"};
    for (hh = 0; chkStruct (); ++ hh) {
        string s = "**** " + Evap_names [evap_type [hh] + 2] + " ****";
        LogMessageA (hh, string ("'" + Name + " (evapD_Resist)' hru_cum_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_evap [hh], hru_area [hh], basin_area [0], s.c_str ());
        LogMessageA (hh, string ("'" + Name + " (evapD_Resist)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str (), hru_cum_actet [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::finish(bool good)@@@ClassevapD_Resist.cpp>");
}
double ClassevapD_Resist :: gamma (double Pa, double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::gamma(double Pa, double t)@@@ClassevapD_Resist.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::gamma(double Pa, double t)@@@ClassevapD_Resist.cpp>");
    return (0.00163 * Pa / lambda (t));
InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::gamma(double Pa, double t)@@@ClassevapD_Resist.cpp>");
}
double ClassevapD_Resist :: lambda (double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::lambda(double t)@@@ClassevapD_Resist.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::lambda(double t)@@@ClassevapD_Resist.cpp>");
    return (2.501 - 0.002361 * t);
InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::lambda(double t)@@@ClassevapD_Resist.cpp>");
}
double ClassevapD_Resist :: delta (double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::delta(double t)@@@ClassevapD_Resist.cpp>");
    if (t > 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::delta(double t)@@@ClassevapD_Resist.cpp>");
        return (2504.0 * exp (17.27 * t / (t + 237.3)) / sqr (t + 237.3));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::delta(double t)@@@ClassevapD_Resist.cpp>");
        return (3549.0 * exp (21.88 * t / (t + 265.5)) / sqr (t + 265.5));
    }

InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::delta(double t)@@@ClassevapD_Resist.cpp>");
}
double ClassevapD_Resist :: RHOa (double t, double ea, double Pa)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD_Resist::RHOa(double t, double ea, double Pa)@@@ClassevapD_Resist.cpp>");
    const double R0 = 2870;

InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::RHOa(double t, double ea, double Pa)@@@ClassevapD_Resist.cpp>");
    return (1E4 * Pa / (R0 * (273.15 + t)) * (1.0 - 0.379 * (ea / Pa)));
InstrumentLogger::instance()->log_instrument_log("</ClassevapD_Resist::RHOa(double t, double ea, double Pa)@@@ClassevapD_Resist.cpp>");
}