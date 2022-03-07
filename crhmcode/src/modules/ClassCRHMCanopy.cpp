#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "ClassCRHMCanopy.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
ClassCRHMCanopy * ClassCRHMCanopy :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::klone(string name) const@@@ClassCRHMCanopy.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::klone(string name) const@@@ClassCRHMCanopy.cpp>");
    return new ClassCRHMCanopy (name);
InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::klone(string name) const@@@ClassCRHMCanopy.cpp>");
}
void ClassCRHMCanopy :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::decl(void)@@@ClassCRHMCanopy.cpp>");
    Description = "'Prototype all season canopy module. Calculates short, long and all-wave radiation components at the snow surface.' \
                 'Inputs are observations Qsi (W/m^2) and Qli (W/m^2), ' \
                 'Inputs are observation Qsi (W/m^2) and variable QliVt_Var (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and observation Qli (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and variable QliVt_Var (W/m^2), '\
                 'Inputs are variable QsiA_Var (W/m^2)(horizontal) from Annandale and variable QliVt_Var (W/m^2), '";
    variation_set = VARIATION_0 + VARIATION_1;
    declreadobs ("Qsi", TDim :: NHRU, "incident short-wave", "(W/m^2)", & Qsi, HRU_OBS_Q);
    variation_set = VARIATION_0 + VARIATION_2;
    declreadobs ("Qli", TDim :: NHRU, "incident long-wave", "(W/m^2)", & Qli, HRU_OBS_Q);
    variation_set = VARIATION_1 + VARIATION_3 + VARIATION_4;
    declgetvar ("*", "QliVt_Var", "(W/m^2)", & QliVt_Var);
    variation_set = VARIATION_2 + VARIATION_3;
    declgetvar ("*", "QsiS_Var", "(W/m^2)", & QsiS_Var);
    variation_set = VARIATION_4;
    declgetvar ("*", "QsiA_Var", "(W/m^2)", & QsiA_Var);
    variation_set = VARIATION_ORG;
    declgetvar ("*", "hru_t", "(" + string (DEGREE_CELSIUS) + ")", & hru_t);
    declgetvar ("*", "hru_u", "(m/s)", & hru_u);
    declgetvar ("*", "hru_rh", "()", & hru_rh);
    declgetvar ("*", "hru_ea", "(kPa)", & hru_ea);
    declgetvar ("*", "hru_snow", "(mm/int)", & hru_snow);
    declgetvar ("*", "hru_rain", "(mm/int)", & hru_rain);
    declgetvar ("*", "hru_evap", "(mm/int)", & hru_evap);
    declgetvar ("*", "SolAng", "(r)", & SolAng);
    declgetvar ("*", "Albedo", "(r)", & Albedo);
    declputvar ("*", "SWE", "(mm)", & SWE);
    declobs ("Ts", TDim :: NHRU, "snow surface temperature", "(" + string (DEGREE_CELSIUS) + ")", & Ts);
    declobs ("Qnsn", TDim :: NHRU, "net all-wave at snow surface", "(W/m^2)", & Qnsn);
    declvar ("Qnsn_Var", TDim :: NHRU, "net all-wave at snow surface", "(W/m^2*int)", & Qnsn_Var);
    declobs ("Qsisn", TDim :: NHRU, "incident short-wave at surface", "(W/m^2)", & Qsisn);
    declobs ("Qlisn", TDim :: NHRU, "incident long-wave at surface", "(W/m^2)", & Qlisn);
    declobs ("Qlosn", TDim :: NHRU, "reflected long-wave at surface", "(W/m^2)", & Qlosn);
    decldiag ("k", TDim :: NHRU, "extinction coefficient", "()", & k);
    decldiag ("Tauc", TDim :: NHRU, "short-wave transmissivity", "(W/m^2)", & Tauc);
    decllocal ("Pa", TDim :: NHRU, "Average surface pressure", "(kPa)", & Pa);
    declvar ("ra", TDim :: NHRU, "", "(s/m)", & ra);
    declvar ("drip_cpy", TDim :: NHRU, "canopy drip", "(mm/int)", & drip_Cpy);
    declvar ("direct_rain", TDim :: NHRU, "direct rainfall through canopy", "(mm/int)", & direct_rain);
    declvar ("net_rain", TDim :: NHRU, " direct_rain + drip", "(mm/int)", & net_rain);
    declstatdiag ("cum_net_rain", TDim :: NHRU, " direct_rain + drip", "(mm)", & cum_net_rain);
    declvar ("Subl_Cpy", TDim :: NHRU, "canopy snow sublimation", "(mm/int)", & Subl_Cpy);
    declstatdiag ("cum_Subl_Cpy", TDim :: NHRU, "canopy snow sublimation", "(mm)", & cum_Subl_Cpy);
    decldiag ("Pevap", TDim :: NHRU, "used when ground is snow covered to calculate canopy evaporation (Priestley-Taylor)", "(mm)", & Pevap);
    declstatvar ("rain_load", TDim :: NHRU, "canopy rain load", "(mm)", & rain_load);
    declstatvar ("Snow_load", TDim :: NHRU, "canopy snow load (timetep start)", "(mm)", & Snow_load);
    declvar ("direct_snow", TDim :: NHRU, "snow 'direct' Thru", "(mm/int)", & direct_snow);
    declvar ("SUnload", TDim :: NHRU, "unloaded canopy snow", "(mm)", & SUnload);
    declvar ("SUnload_H2O", TDim :: NHRU, "unloaded canopy snow as water", "(mm)", & SUnload_H2O);
    declstatdiag ("cum_SUnload_H2O", TDim :: NHRU, "Cumulative unloaded canopy snow as water", "(mm)", & cum_SUnload_H2O);
    declstatdiag ("cum_SUnload", TDim :: NHRU, "Cumulative unloaded canopy snow as snow", "(mm)", & cum_SUnload);
    declvar ("net_snow", TDim :: NHRU, "hru_snow minus interception", "(mm/int)", & net_snow);
    declstatdiag ("cum_net_snow", TDim :: NHRU, "Cumulative Canopy unload ", "(mm)", & cum_net_snow);
    declvar ("net_p", TDim :: NHRU, "total precipitation after interception", "(mm/int)", & net_p);
    decldiag ("u_FHt", TDim :: NHRU, "wind speed at forest top (z = FHt)", "(m/s)", & u_FHt);
    decldiag ("Cc", TDim :: NHRU, "Canopy coverage", "()", & Cc);
    declvar ("intcp_evap", TDim :: NHRU, "HRU Evaporation from interception", "(mm/int)", & intcp_evap);
    declstatdiag ("cum_intcp_evap", TDim :: NHRU, "HRU Evaporation from interception", "(mm)", & cum_intcp_evap);
    declvar ("Qsisn_Var", TDim :: NHRU, "incident short-wave at surface", "(W/m^2*int)", & Qsisn_Var);
    declvar ("Qlisn_Var", TDim :: NHRU, "incident long-wave at surface", "(W/m^2*int)", & Qlisn_Var);
    declparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", & inhibit_evap);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("hru_elev", TDim :: NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", & hru_elev);
    declparam ("Ht", TDim :: NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "forest/vegetation height", "(m)", & Ht);
    declparam ("Zref", TDim :: NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", & Zref);
    declparam ("Zwind", TDim :: NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", & Zwind);
    declparam ("Z0snow", TDim :: NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", & Z0snow);
    declparam ("LAI", TDim :: NHRU, "[2.2]", "0.1", "20.0", "leaf-area-index", "()", & LAI);
    declparam ("Sbar", TDim :: NHRU, "[6.6]", "0.0", "100.0", "maximum canopy snow interception load", "(kg/m^2)", & Sbar);
    declparam ("Zvent", TDim :: NHRU, "[0.75]", "0.0", "1.0", "ventilation wind speed height (z/Ht)", "()", & Zvent);
    declparam ("unload_t", TDim :: NHRU, "[1.0]", "-10.0", "20.0", "if ice-bulb temp >= t : canopy snow is unloaded as snow", "(" + string (DEGREE_CELSIUS) + ")", & unload_t);
    declparam ("unload_t_water", TDim :: NHRU, "[4.0]", "-10.0", "20.0", "if ice-bulb temp >= t: canopy snow is unloaded as water", "(" + string (DEGREE_CELSIUS) + ")", & unload_t_water);
    decldiagparam ("Alpha_c", TDim :: NHRU, "[0.1]", "0.05", "0.2", "canopy albedo", "()", & Alpha_c);
    decldiagparam ("B_canopy", TDim :: NHRU, "[0.038]", "0.0", "0.2", "canopy enhancement parameter. Suggestions are Colorado - 0.023 and Alberta - 0.038", "()", & B_canopy);
InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::decl(void)@@@ClassCRHMCanopy.cpp>");
}
void ClassCRHMCanopy :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::init(void)@@@ClassCRHMCanopy.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        Pa [hh] = 101.3f * pow ((293.0f - 0.0065f * hru_elev [hh]) / 293.0f, 5.26f);
        rain_load [hh] = 0.0;
        Snow_load [hh] = 0.0;
        cum_net_snow [hh] = 0.0;
        cum_net_rain [hh] = 0.0;
        cum_Subl_Cpy [hh] = 0.0;
        cum_intcp_evap [hh] = 0.0;
        cum_SUnload_H2O [hh] = 0.0;
        if (Ht [hh] > Zwind [hh])
        {
            CRHMException TExcept (string ("'" + Name + " (Canopy)' Vegetation height greater than wind reference height, i.e. (Ht > Zwind)!").c_str (), TExcept :: WARNING);
            LogError (TExcept);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::init(void)@@@ClassCRHMCanopy.cpp>");
}
void ClassCRHMCanopy :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::run(void)@@@ClassCRHMCanopy.cpp>");
    double Kstar_H;
    for (hh = 0; chkStruct (); ++ hh) {
        switch (variation) {
        case VARIATION_ORG:
            Qsi_ = Qsi [hh];
            Qli_ = Qli [hh];
            break;
        case VARIATION_1:
            Qsi_ = Qsi [hh];
            Qli_ = QliVt_Var [hh];
            break;
        case VARIATION_2:
            Qsi_ = QsiS_Var [hh];
            Qli_ = Qli [hh];
            break;
        case VARIATION_3:
            Qsi_ = QsiS_Var [hh];
            Qli_ = QliVt_Var [hh];
            break;
        case VARIATION_4:
            Qsi_ = QsiA_Var [hh];
            Qli_ = QliVt_Var [hh];
            break;
        }
        net_rain [hh] = 0.0;
        direct_rain [hh] = 0.0;
        drip_Cpy [hh] = 0.0;
        intcp_evap [hh] = 0.0;
        net_snow [hh] = 0.0;
        direct_snow [hh] = 0.0;
        SUnload [hh] = 0.0;
        SUnload_H2O [hh] = 0.0;
        Subl_Cpy [hh] = 0.0;
        double T1 = hru_t [hh] + CRHM_constants :: Tm;
        double Exposure = Ht [hh] - Common :: DepthofSnow (SWE [hh]);
        if (Exposure < 0.0)
        {
            Exposure = 0.0;
        }

        double LAI_ = LAI [hh] * Exposure / Ht [hh];
        double Vf = 0.45 - 0.29 * log (LAI [hh]);
        double Vf_ = Vf + (1.0 - Vf) * sin ((Ht [hh] - Exposure) / Ht [hh] * M_PI_2);
        if (SolAng [hh] > 0.001)
        {
            k [hh] = 1.081 * SolAng [hh] * cos (SolAng [hh]) / sin (SolAng [hh]);
            Tauc [hh] = exp (- k [hh] * LAI_);
        }

        else
        {
            k [hh] = 0.0;
            Tauc [hh] = 0.0;
        }

        Kstar_H = Qsi_ * (1.0 - Alpha_c [hh] - Tauc [hh] * (1.0 - Albedo [hh]));
        Qlisn [hh] = Qli_ * Vf_ + (1.0f - Vf_) * CRHM_constants :: emiss_c * CRHM_constants :: sbc * pow (T1, 4.0f) + B_canopy [hh] * Kstar_H;
        Qlisn_Var [hh] = Qlisn [hh];
        Qsisn [hh] = Qsi_ * Tauc [hh];
        Qsisn_Var [hh] = Qsisn [hh];
        double rho = Pa [hh] * 1000 / (CRHM_constants :: Rgas * T1);
        double U1 = hru_u [hh];
        ra [hh] = (log (Zref [hh] / Z0snow [hh]) * log (Zwind [hh] / Z0snow [hh])) / sqr (CRHM_constants :: kappa) / U1;
        double deltaX = 0.622 * CRHM_constants :: Ls * Common :: Qs (Pa [hh], T1) / (CRHM_constants :: Rgas * sqr (T1));
        double q = (hru_rh [hh] / 100) * Common :: Qs (Pa [hh], T1);
        Ts [hh] = T1 + (CRHM_constants :: emiss * (Qli_ - CRHM_constants :: sbc * pow (T1, 4.0f)) + CRHM_constants :: Ls * (q - Common :: Qs (Pa [hh], T1)) * rho / ra [hh]) / (4 * CRHM_constants :: emiss * CRHM_constants :: sbc * pow (T1, 3.0f) + (CRHM_constants :: Cp + CRHM_constants :: Ls * deltaX) * rho / ra [hh]);
        Ts [hh] -= CRHM_constants :: Tm;
        if (Ts [hh] > 0.0 || SWE [hh] <= 0.0)
        {
            Ts [hh] = 0.0;
        }

        Qlosn [hh] = CRHM_constants :: emiss * CRHM_constants :: sbc * pow (Ts [hh] + CRHM_constants :: Tm, 4.0f);
        Qnsn [hh] = Qlisn [hh] - Qlosn [hh] + Qsisn [hh] * (1.0 - Albedo [hh]);
        Qnsn_Var [hh] = Qnsn [hh];
        if (Snow_load [hh] > 0.0 || hru_snow [hh] > 0.0)
        {
            double RhoS = 67.92 + 51.25 * exp (hru_t [hh] / 2.59);
            double LStar = Sbar [hh] * (0.27 + 46.0 / RhoS) * LAI [hh];
            if (Snow_load [hh] > LStar)
            {
                direct_snow [hh] = Snow_load [hh] - LStar;
                Snow_load [hh] = LStar;
            }

            if (Ht [hh] - 2.0 / 3.0 * Zwind [hh] > 1.0)
            {
                u_FHt [hh] = hru_u [hh] * log ((Ht [hh] - 2.0 / 3.0 * Zwind [hh]) / 0.123 * Zwind [hh]) / log ((Zwind [hh] - 2.0 / 3.0 * Zwind [hh]) / 0.123 * Zwind [hh]);
            }

            else
            {
                u_FHt [hh] = 0.0;
            }

            double I1 = 0.0;
            if (hru_snow [hh] > 0.0 && LStar > 0.0)
            {
                if (fabs (hru_snow [hh] / LStar) < 50.0)
                {
                    if (u_FHt [hh] <= 1.0)
                    {
                        I1 = (LStar - Snow_load [hh]) * (1.0 - exp (- Cc [hh] * hru_snow [hh] / LStar));
                    }

                    else
                    {
                        I1 = (LStar - Snow_load [hh]) * (1.0 - exp (- hru_snow [hh] / LStar));
                    }

                    if (I1 <= 0)
                    {
                        I1 = 0;
                    }

                    Snow_load [hh] += I1;
                }

                direct_snow [hh] += (hru_snow [hh] - I1);
            }

            const double gamma = 1.15;
            double xi2 = 1 - Zvent [hh];
            double windExt2 = (gamma * LAI [hh] * xi2);
            double uVent = u_FHt [hh] * exp (- 1 * windExt2);
            const double AlbedoIce = 0.8;
            const double Radius = 5.0e-4;
            const double KinVisc = 1.88e-5;
            const double ks = 0.0114;
            const double Fract = 0.37;
            const double ci = 2.102e-3;
            const double Hs = 2.838e6;
            double Alpha, A1, B1, C1, J, D, Lamb, Mpm, Nu, Nr, SStar, Sigma2;
            double Es = 611.15f * exp (22.452f * hru_t [hh] / (hru_t [hh] + 273.0f));
            double SvDens = Es * PBSM_constants :: M / (PBSM_constants :: R * (hru_t [hh] + 273.0f));
            Lamb = 6.3e-4 * (hru_t [hh] + 273.0) + 0.0673;
            Nr = 2.0 * Radius * uVent / KinVisc;
            Nu = 1.79 + 0.606 * sqrt ((double) Nr);
            SStar = M_PI * sqr (Radius) * (1.0f - AlbedoIce) * Qsi_;
            A1 = Lamb * (hru_t [hh] + 273) * Nu;
            B1 = Hs * PBSM_constants :: M / (PBSM_constants :: R * (hru_t [hh] + 273.0f)) - 1.0;
            J = B1 / A1;
            Sigma2 = hru_rh [hh] / 100 - 1;
            D = 2.06e-5 * pow ((hru_t [hh] + 273.0f) / 273.0f, - 1.75f);
            C1 = 1.0 / (D * SvDens * Nu);
            Alpha = 5.0;
            Mpm = 4.0 / 3.0 * M_PI * PBSM_constants :: DICE * Radius * Radius * Radius * (1.0 + 3.0 / Alpha + 2.0 / sqr (Alpha));
            double Vs = (2.0 * M_PI * Radius * Sigma2 - SStar * J) / (Hs * J + C1) / Mpm;
            double Ce;
            if ((Snow_load [hh] / LStar) <= 0.0)
            {
                Ce = 0.07;
            }

            else
            {
                Ce = ks * pow ((Snow_load [hh] / LStar), - Fract);
            }

            double Vi = Vs * Ce;
            Subl_Cpy [hh] = - Snow_load [hh] * Vi * Global :: Interval * 24 * 3600;
            if (Subl_Cpy [hh] > Snow_load [hh])
            {
                Subl_Cpy [hh] = Snow_load [hh];
                Snow_load [hh] = 0.0;
            }

            else
            {
                Snow_load [hh] -= Subl_Cpy [hh];
                if (Snow_load [hh] < 0.0)
                {
                    Snow_load [hh] = 0.0;
                }

            }

            double IceBulbT = hru_t [hh] - (Vi * Hs / 1e6 / ci);
            double Six_Hour_Divisor = Global :: Freq / 4.0;
            const double c = 0.678 / (24 * 7 * 24 / Global :: Freq);
            if (IceBulbT >= unload_t_water [hh])
            {
                drip_Cpy [hh] = Snow_load [hh] / Six_Hour_Divisor;
                SUnload_H2O [hh] = drip_Cpy [hh];
                Snow_load [hh] -= SUnload_H2O [hh];
                cum_SUnload_H2O [hh] += SUnload_H2O [hh];
            }

            else
            if (IceBulbT >= unload_t [hh])
            {
                SUnload [hh] = Snow_load [hh] / Six_Hour_Divisor;
                Snow_load [hh] -= SUnload [hh];
                cum_SUnload [hh] += SUnload [hh];
            }

            else
            if (IceBulbT < unload_t [hh])
            {
                SUnload [hh] = Snow_load [hh] * c;
                if (SUnload [hh] > Snow_load [hh])
                {
                    SUnload [hh] = Snow_load [hh];
                    Snow_load [hh] = 0.0;
                }

                else
                {
                    Snow_load [hh] -= SUnload [hh];
                }

                cum_SUnload [hh] += SUnload [hh];
            }

            net_snow [hh] = direct_snow [hh] + SUnload [hh];
        }

        Cc [hh] = 0.29 * log (LAI [hh]) + 0.55;
        if (Cc [hh] <= 0.0)
        {
            Cc [hh] = 0.0;
        }

        double smax = Cc [hh] * LAI [hh] * 0.2;
        if (hru_rain [hh] > 0.0)
        {
            direct_rain [hh] = hru_rain [hh] * (1 - Cc [hh]);
            if (rain_load [hh] + hru_rain [hh] * Cc [hh] > smax)
            {
                drip_Cpy [hh] += (rain_load [hh] + hru_rain [hh] * Cc [hh] - smax);
                rain_load [hh] = smax;
            }

            else
            {
                rain_load [hh] += hru_rain [hh] * Cc [hh];
            }

        }

        if (rain_load [hh] > 0.0)
        {
            if (inhibit_evap [hh] == 0)
            {
                if (rain_load [hh] >= hru_evap [hh] * Cc [hh])
                {
                    intcp_evap [hh] = hru_evap [hh] * Cc [hh];
                    rain_load [hh] -= hru_evap [hh] * Cc [hh];
                }

                else
                {
                    intcp_evap [hh] = rain_load [hh];
                    rain_load [hh] = 0.0;
                }

            }

            else
            {
                double Q = Qsi_ * 86400 / Global :: Freq / 1e6 / lambda (hru_t [hh]);
                if (Qsi_ > 0.0)
                {
                    Pevap [hh] = 1.26 * delta (hru_t [hh]) * Q / (delta (hru_t [hh]) + gamma (Pa [hh], hru_t [hh]));
                }

                else
                {
                    Pevap [hh] = 0.0;
                }

                if (rain_load [hh] >= Pevap [hh] * Cc [hh])
                {
                    intcp_evap [hh] = Pevap [hh] * Cc [hh];
                    rain_load [hh] -= Pevap [hh] * Cc [hh];
                }

                else
                {
                    intcp_evap [hh] = rain_load [hh];
                    rain_load [hh] = 0.0;
                }

            }

        }

        net_rain [hh] = direct_rain [hh] + drip_Cpy [hh];
        net_p [hh] = net_rain [hh] + net_snow [hh];
        cum_net_rain [hh] += net_rain [hh];
        cum_net_snow [hh] += net_snow [hh];
        cum_intcp_evap [hh] += intcp_evap [hh];
        cum_Subl_Cpy [hh] += Subl_Cpy [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::run(void)@@@ClassCRHMCanopy.cpp>");
}
void ClassCRHMCanopy :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::finish(bool good)@@@ClassCRHMCanopy.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (canopy)'  cum_net_snow    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_net_snow [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (canopy)'  cum_net_rain    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_net_rain [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (canopy)'  cum_Subl_Cpy    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_Subl_Cpy [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (canopy)'  cum_intcp_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_intcp_evap [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (canopy)'  cum_SUnload_H2O (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_SUnload_H2O [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::finish(bool good)@@@ClassCRHMCanopy.cpp>");
}
double ClassCRHMCanopy :: delta (double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::delta(double t)@@@ClassCRHMCanopy.cpp>");
    if (t > 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::delta(double t)@@@ClassCRHMCanopy.cpp>");
        return (2504.0 * exp (17.27 * t / (t + 237.3)) / sqr (t + 237.3));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::delta(double t)@@@ClassCRHMCanopy.cpp>");
        return (3549.0 * exp (21.88 * t / (t + 265.5)) / sqr (t + 265.5));
    }

InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::delta(double t)@@@ClassCRHMCanopy.cpp>");
}
double ClassCRHMCanopy :: lambda (double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::lambda(double t)@@@ClassCRHMCanopy.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::lambda(double t)@@@ClassCRHMCanopy.cpp>");
    return (2.501 - 0.002361 * t);
InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::lambda(double t)@@@ClassCRHMCanopy.cpp>");
}
double ClassCRHMCanopy :: gamma (double Pa, double t)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::gamma(double Pa, double t)@@@ClassCRHMCanopy.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::gamma(double Pa, double t)@@@ClassCRHMCanopy.cpp>");
    return (0.00163 * Pa / lambda (t));
InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::gamma(double Pa, double t)@@@ClassCRHMCanopy.cpp>");
}
double ClassCRHMCanopy :: RHOa (double t, double ea, double Pa)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCRHMCanopy::RHOa(double t, double ea, double Pa)@@@ClassCRHMCanopy.cpp>");
    const double R = 2870;

InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::RHOa(double t, double ea, double Pa)@@@ClassCRHMCanopy.cpp>");
    return (1E4 * Pa / (R * (273.15 + t)) * (1.0 - 0.379 * (ea / Pa)));
InstrumentLogger::instance()->log_instrument_log("</ClassCRHMCanopy::RHOa(double t, double ea, double Pa)@@@ClassCRHMCanopy.cpp>");
}