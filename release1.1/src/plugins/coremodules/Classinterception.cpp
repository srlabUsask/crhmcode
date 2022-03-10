#include "Classinterception.h"
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
Classinterception * Classinterception :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classinterception::klone(string name) const@@@Classinterception.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classinterception::klone(string name) const@@@Classinterception.cpp>");
    return new Classinterception (name);
InstrumentLogger::instance()->log_instrument_log("</Classinterception::klone(string name) const@@@Classinterception.cpp>");
}
void Classinterception :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classinterception::decl(void)@@@Classinterception.cpp>");
    Description = "'Calculates canopy sublimation and unloading.'";
    declvar ("SI_Lo", TDim :: NHRU, "Canopy load", "(kg/m^2)", & SI_Lo);
    declvar ("net_snow", TDim :: NHRU, "Canopy unload ", "(kg/m^2)", & net_snow);
    decldiag ("Cum_net_snow", TDim :: NHRU, "Cumulative Canopy unload ", "(kg/m^2)", & Cum_net_snow);
    declvar ("SI_Subl", TDim :: NHRU, "Canopy sublimation", "(kg/m^2*int)", & SI_Subl);
    decldiag ("Cum_Subl", TDim :: NHRU, "Cumulative Canopy sublimation", "(kg/m^2)", & Cum_Subl);
    declvar ("net_rain", TDim :: NHRU, "hru_rain minus interception", "(mm/int)", & net_rain);
    decldiag ("v", TDim :: NHRU, "ventilation velocity", "(m/s)", & v);
    declparam ("Sbar", TDim :: NHRU, "[6.6]", "0.0", "100.0", "Maximum snow load", "(kg/m^2)", & Sbar);
    declparam ("LAI", TDim :: NHRU, "[2.2]", "0.0", "10.0", "Leaf are index", "(m^2/m^2)", & LAI);
    decldiagparam ("k", TDim :: NHRU, "[0.0113]", "0.0", "1.0", "Snow shape coefficient", "()", & k);
    declparam ("Ht", TDim :: NHRU, "[20]", "0.0", "100.0", "Canopy height", "(m)", & Ht);
    decldiagparam ("WidthJ", TDim :: NHRU, "[75]", "0.0", "100.0", "Canopy ", "(m)", & WidthJ);
    decldiagparam ("velW", TDim :: NHRU, "[0.75]", "0.0", "1.0", "Canopy wind coefficient", "(m)", & velw);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declreadobs ("Qsi", TDim :: NHRU, "incident short-wave", "(W/m^2)", & Qsi, HRU_OBS_Q);
    declgetvar ("*", "hru_t", "(°C)", & hru_t);
    declgetvar ("*", "hru_snow", "(mm/int)", & hru_snow);
    declgetvar ("*", "hru_rain", "(mm/int)", & hru_rain);
    declgetvar ("*", "hru_rh", "()", & hru_rh);
    declgetvar ("*", "hru_u", "(m/s)", & hru_u);
InstrumentLogger::instance()->log_instrument_log("</Classinterception::decl(void)@@@Classinterception.cpp>");
}
void Classinterception :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classinterception::init(void)@@@Classinterception.cpp>");
    nobs = getdim (TDim :: NOBS);
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        SI_Lo [hh] = 0.0;
        net_snow [hh] = 0.0;
        net_rain [hh] = 0.0;
        SI_Subl [hh] = 0.0;
        Cum_Subl [hh] = 0.0;
        Cum_net_snow [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</Classinterception::init(void)@@@Classinterception.cpp>");
}
void Classinterception :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classinterception::run(void)@@@Classinterception.cpp>");
    const double Radius = 0.0005;
    const double R = 8313.0;
    const double M = 18.01;
    const double RhoI = 900.0;
    const double Fract = 0.4;
    const double Hs = 2838000.0;
    const double Cc = 0.82;
    const double Viscosity = 1.88E-5;
    const double Albedo = 0.8;
    double RhoSat, RhoT, Nr, Nu, Sstar, A, B, J, D, Vs, Ce;
    double I1, Unld, Istar, Cp, RhoS;
    for (hh = 0; chkStruct (); ++ hh) {
        net_rain [hh] = hru_rain [hh];
        RhoS = 67.92 + 51.25 * exp (hru_t [hh] / 2.59);
        Istar = Sbar [hh] * (0.27 + 46.0 / RhoS) * LAI [hh];
        net_snow [hh] = 0.0;
        if (SI_Lo [hh] > Istar)
        {
            net_snow [hh] = SI_Lo [hh] - Istar;
            Cum_net_snow [hh] += net_snow [hh];
            SI_Lo [hh] = Istar;
        }

        if (hru_snow [hh] > 0.0)
        {
            Cp = Cc / (1.0 - (Cc * hru_u [hh] * Ht [hh]) / (velw [hh] * WidthJ [hh]));
            if (Cp <= 0.0 || Cp > 1.0)
            {
                Cp = 1.0;
            }

            I1 = (Istar - SI_Lo [hh]) * (1 - exp (- Cp * hru_snow [hh] / Istar));
            SI_Lo [hh] = SI_Lo [hh] + I1;
            net_snow [hh] += hru_snow [hh] - I1;
            Cum_net_snow [hh] += hru_snow [hh] - I1;
        }

        else
        if (SI_Lo [hh] <= 0.0)
        {
            SI_Lo [hh] = 0.0;
            continue;
        }

        RhoSat = 1.324 * exp (22.452 * hru_t [hh] / (hru_t [hh] + 273.0)) / (hru_t [hh] + 273.0);
        RhoT = 0.00063 * (hru_t [hh] + 273.0) + 0.0673;
        double n = 2.43 * Cc + 2.97 * (1.0 - Cc);
        double mx = 3.46 * Cc + 3.2 * (1.0 - Cc);
        double Is_CioncoA = n + mx * exp (- Ht [hh]);
        double For_vent = velw [hh] * Ht [hh];
        double Is_CioncoB = For_vent / Ht [hh] - 1.0;
        double Is_CioncoAB = Is_CioncoA * Is_CioncoB;
        v [hh] = hru_u [hh] * exp (Is_CioncoAB);
        Nr = 2 * Radius * v [hh] / Viscosity;
        Nu = 1.79 + 0.606 * sqrt (Nr);
        Sstar = M_PI * sqr (Radius) * (1.0 - Albedo) * Qsi [hh];
        A = RhoT * (hru_t [hh] + 273) * Nu;
        B = Hs * M / (R * (hru_t [hh] + 273.0)) - 1.0;
        J = B / A;
        D = 2.06E-5f * pow ((hru_t [hh] + 273.0f) / 273.0f, 1.75f);
        Vs = (2.0 * M_PI * Radius * (1.0 - hru_rh [hh]) + Sstar * J) / (Hs * J + (1.0f / (D * RhoSat * Nu)));
        Vs = Vs / (4.0f / 3.0f * M_PI * pow (Radius, 3.0f) * RhoI);
        Ce = k [hh] * pow (SI_Lo [hh] / Istar, - Fract);
        SI_Subl [hh] = - SI_Lo [hh] * Vs * Ce * 3600.0f * 24.0f / Global :: Freq / 1000.0f;
        Cum_Subl [hh] += SI_Subl [hh];
        if (SI_Lo [hh] > SI_Subl [hh])
        {
            SI_Lo [hh] = SI_Lo [hh] - SI_Subl [hh];
        }

        else
        {
            SI_Subl [hh] = SI_Lo [hh];
            SI_Lo [hh] = 0.0;
            continue;
        }

        if (hru_snow [hh] > 0.0)
        {
            if (I1 > SI_Subl [hh])
            {
                Unld = (I1 - SI_Subl [hh]) * 0.322;
                SI_Lo [hh] = SI_Lo [hh] - Unld;
                net_snow [hh] += Unld;
                Cum_net_snow [hh] += Unld;
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</Classinterception::run(void)@@@Classinterception.cpp>");
}
void Classinterception :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<Classinterception::finish(bool good)@@@Classinterception.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (interception)' Cumulative Canopy Unload      (mm) (mm*hru) (mm*hru/basin): ").c_str (), Cum_net_snow [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (interception)' Cumulative Canopy sublimation (mm) (mm*hru) (mm*hru/basin): ").c_str (), Cum_Subl [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
InstrumentLogger::instance()->log_instrument_log("</Classinterception::finish(bool good)@@@Classinterception.cpp>");
}