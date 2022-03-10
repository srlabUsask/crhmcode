#include "ClassevapD.h"
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
ClassevapD * ClassevapD :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::klone(string name) const@@@ClassevapD.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapD::klone(string name) const@@@ClassevapD.cpp>");
    return new ClassevapD (name);
InstrumentLogger::instance()->log_instrument_log("</ClassevapD::klone(string name) const@@@ClassevapD.cpp>");
}
void ClassevapD :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::decl(void)@@@ClassevapD.cpp>");
    Description = "'Calculates daily evaporation. Parameter \"evap_type\" selects Granger/Priestley-Taylor.'";
    declvar ("hru_actet", TDim :: NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", & hru_actet);
    declstatdiag ("hru_cum_actet", TDim :: NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", & hru_cum_actet);
    declvar ("hru_evapD", TDim :: NHRU, "daily evaporation", "(mm/d)", & evapD);
    declstatdiag ("hru_cum_evap", TDim :: NHRU, "cumulative interval evaporation", "(mm)", & cum_evap);
    declvar ("evap_G", TDim :: NHRU, "relative evaporation", "()", & G);
    declvar ("evap_D", TDim :: NHRU, "drying power", "()", & D);
    decllocal ("Pa", TDim :: NHRU, "Atmospheric pressure", "(kPa)", & Pa);
    declparam ("evap_type", TDim :: NHRU, "0", "0", "1", "Evaporation method for this HRU, 0 = Granger, 1 = Priestley-Taylor", "()", & evap_type);
    declparam ("Ht", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", & Ht);
    declparam ("hru_elev", TDim :: NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", & hru_elev);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", & inhibit_evap);
    decldiagparam ("F_Qg", TDim :: NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", & F_Qg);
    declgetvar ("*", "RnD", "(mm/m^2*d)", & RnD);
    declgetvar ("*", "hru_tmean", "(°C)", & hru_tmean);
    declgetvar ("*", "hru_umean", "(m/s)", & hru_umean);
    declgetvar ("*", "hru_eamean", "(kPa)", & hru_eamean);
InstrumentLogger::instance()->log_instrument_log("</ClassevapD::decl(void)@@@ClassevapD.cpp>");
}
void ClassevapD :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::init(void)@@@ClassevapD.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        Pa [hh] = 101.3f * pow ((293.0f - 0.0065f * hru_elev [hh]) / 293.0f, 5.26f);
        evapD [hh] = 0.0;
        cum_evap [hh] = 0.0;
        hru_cum_actet [hh] = 0.0;
        D [hh] = 0.0;
        G [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassevapD::init(void)@@@ClassevapD.cpp>");
}
void ClassevapD :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::run(void)@@@ClassevapD.cpp>");
    double Q;
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
            switch (evap_type [hh]) {
            case 0:
                if (Q > 0.0)
                {
                    double Eal = fdaily (hru_umean [hh], Ht [hh]) * (Common :: estar (hru_tmean [hh]) - hru_eamean [hh]);
                    if (Eal > 0.0)
                    {
                        D [hh] = Eal / (Eal + Q);
                        if (D [hh] > 1.0)
                        {
                            D [hh] = 1.0;
                        }

                    }

                    else
                    {
                        D [hh] = 0.0;
                    }

                    G [hh] = 1.0 / (0.793 + 0.2 * exp (4.902 * D [hh])) + 0.006 * D [hh];
                    evapD [hh] = (delta (hru_tmean [hh]) * G [hh] * Q + gamma (Pa [hh], hru_tmean [hh]) * G [hh] * Eal) / (delta (hru_tmean [hh]) * G [hh] + gamma (Pa [hh], hru_tmean [hh]));
                }

                else
                {
                    evapD [hh] = 0.0;
                }

                break;
            case 1:
                if (Q > 0.0)
                {
                    evapD [hh] = 1.26 * delta (hru_tmean [hh]) * Q / (delta (hru_tmean [hh]) + gamma (Pa [hh], hru_tmean [hh]));
                }

                else
                {
                    evapD [hh] = 0.0;
                }

                break;
            }
            cum_evap [hh] += evapD [hh];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassevapD::run(void)@@@ClassevapD.cpp>");
}
void ClassevapD :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::finish(bool good)@@@ClassevapD.cpp>");
    string Evap_names [] = {"Granger", "Priestley-Taylor", "Penman-Monteith", "Dalton Bulk transfer"};
    for (hh = 0; chkStruct (); ++ hh) {
        string s = "**** " + Evap_names [evap_type [hh]] + " ****";
        LogMessageA (hh, string ("'" + Name + " (evapD)' hru_cum_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_evap [hh], hru_area [hh], basin_area [0], s.c_str ());
        LogMessageA (hh, string ("'" + Name + " (evapD)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str (), hru_cum_actet [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
InstrumentLogger::instance()->log_instrument_log("</ClassevapD::finish(bool good)@@@ClassevapD.cpp>");
}
double ClassevapD :: gamma (double Pa, double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::gamma(double Pa, double t)@@@ClassevapD.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapD::gamma(double Pa, double t)@@@ClassevapD.cpp>");
    return (0.00163 * Pa / lambda (t));
InstrumentLogger::instance()->log_instrument_log("</ClassevapD::gamma(double Pa, double t)@@@ClassevapD.cpp>");
}
double ClassevapD :: lambda (double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::lambda(double t)@@@ClassevapD.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassevapD::lambda(double t)@@@ClassevapD.cpp>");
    return (2.501 - 0.002361 * t);
InstrumentLogger::instance()->log_instrument_log("</ClassevapD::lambda(double t)@@@ClassevapD.cpp>");
}
double ClassevapD :: delta (double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::delta(double t)@@@ClassevapD.cpp>");
    if (t > 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassevapD::delta(double t)@@@ClassevapD.cpp>");
        return (2504.0 * exp (17.27 * t / (t + 237.3)) / sqr (t + 237.3));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassevapD::delta(double t)@@@ClassevapD.cpp>");
        return (3549.0 * exp (21.88 * t / (t + 265.5)) / sqr (t + 265.5));
    }

InstrumentLogger::instance()->log_instrument_log("</ClassevapD::delta(double t)@@@ClassevapD.cpp>");
}
double ClassevapD :: fdaily (double u, double Ht)
{
InstrumentLogger::instance()->log_instrument_log("<ClassevapD::fdaily(double u, double Ht)@@@ClassevapD.cpp>");
    double Z0 = Ht * 100.0 / 7.6;
    double a = 8.19 + 0.22 * Z0;
    double b = 1.16 + 0.08 * Z0;

InstrumentLogger::instance()->log_instrument_log("</ClassevapD::fdaily(double u, double Ht)@@@ClassevapD.cpp>");
    return a + b * u;
InstrumentLogger::instance()->log_instrument_log("</ClassevapD::fdaily(double u, double Ht)@@@ClassevapD.cpp>");
}