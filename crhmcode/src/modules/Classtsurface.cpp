#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "Classtsurface.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
Classtsurface * Classtsurface :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classtsurface::klone(string name) const@@@Classtsurface.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classtsurface::klone(string name) const@@@Classtsurface.cpp>");
    return new Classtsurface (name);
InstrumentLogger::instance()->log_instrument_log("</Classtsurface::klone(string name) const@@@Classtsurface.cpp>");
}
void Classtsurface :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classtsurface::decl(void)@@@Classtsurface.cpp>");
    Description = "'Module to calculate ground surface temperature ' \
    'use hru_t for surface temperature during snowcover period; use Radiative-Conductive-Convective approach to estimate surface temperature(Williams et al, 2015) during snow free periods.' \
    'use hru_t for surface temperature during snowcover period; use parameter n_factor to estimate surface temperature from the air temperature during snow free periods (Woo, 2012, p. 57).' \
    'use previous daily mean snowpack temperature with thermal conductivity and energy of snowpack (***Snobal*** case) to estimate surface temperature during snowcover period; use Radiative-Conductive-Convective approach to estimate surface temperature(Williams et al, 2015) during snow free periods.' \
    'use previous daily mean hru_t with thermal conductivity and energy of snowpack (***ebsm*** case) to estimate surface temperature during snowcover period; use Radiative-Conductive-Convective approach to estimate surface temperature(Williams et al, 2015) during snow free periods.' \
    'use previous daily mean snowpack temperature with thermal conductivity and energy of snowpack (***Snobal*** case) to estimate surface temperature during snowcover period; use parameter n_factor to estimate surface temperature from the air temperature during snow free periods (Woo, 2012, p. 57).' \
    'use previous daily mean hru_t with thermal conductivity and energy of snowpack (***ebsm*** case) to estimate surface temperature during snowcover period; use parameter n_factor to estimate surface temperature from the air temperature during snow free periods (Woo, 2012, p. 57). '";
    declvar ("hru_tsf", TDim :: NHRU, "surface/skin temperature", "(" + string (DEGREE_CELSIUS) + ")", & hru_tsf);
    declvar ("hru_tsf_D", TDim :: NHRU, "mean daily surface/skin temperature", "(" + string (DEGREE_CELSIUS) + ")", & hru_tsf_D);
    decldiag ("hru_tsf_acc", TDim :: NHRU, "mean daily surface/skin temperature", "(" + string (DEGREE_CELSIUS) + ")", & hru_tsf_acc);
    declgetvar ("*", "SWE", "(m)", & SWE);
    declgetvar ("*", "hru_t", "(" + string (DEGREE_CELSIUS) + ")", & hru_t);
    variation_set = VARIATION_2 + VARIATION_4;
    decllocal ("hru_T_s_D", TDim :: NHRU, "mean daily surface/skin temperature", "(" + string (DEGREE_CELSIUS) + ")", & hru_T_s_D);
    decllocal ("hru_T_s_acc", TDim :: NHRU, "sum interval air temperature from previous day", "(" + string (DEGREE_CELSIUS) + ")", & hru_T_s_acc);
    declgetvar ("*", "z_s", "(m)", & z_s);
    declgetvar ("*", "rho", "(kg/m^3)", & rho);
    declgetvar ("*", "T_s", "(" + string (DEGREE_CELSIUS) + ")", & T_s);
    declgetvar ("*", "G", "(W/m^2)", & G);
    variation_set = VARIATION_3 + VARIATION_5;
    decllocal ("hru_t_D", TDim :: NHRU, "mean daily snowpack temperature from previous day", "(" + string (DEGREE_CELSIUS) + ")", & hru_t_D);
    decllocal ("hru_t_acc", TDim :: NHRU, "sum interval air temperature from previous day", "(" + string (DEGREE_CELSIUS) + ")", & hru_t_acc);
    declgetvar ("*", "hru_tmin", "(" + string (DEGREE_CELSIUS) + ")", & tmin);
    declgetvar ("*", "snowdepth", "(m)", & snowdepth);
    variation_set = VARIATION_0 + VARIATION_2 + VARIATION_3;
    decllocal ("Zdt_last", TDim :: NHRU, "Last value of thaw depth", "(m)", & Zdt_last);
    declparam ("W_a", TDim :: NHRU, "[0.77]", "0.0", "1.5", "empirical constant for air temperature", "()", & W_a);
    declparam ("W_b", TDim :: NHRU, "[0.02]", "0.0", "0.1", "empirical constant for net radiation at ground surface", "()", & W_b);
    declparam ("W_c", TDim :: NHRU, "[7.0]", "0.0", "10.0", "empirical constant for frost table", "()", & W_c);
    declparam ("W_d", TDim :: NHRU, "[0.03]", "0.0", "0.1", "empirical constant for frost table", "()", & W_d);
    declgetvar ("*", "netD", "(MJ/m^2*d)", & netD);
    declputvar ("*", "Zdt", "(m)", & Zdt);
    variation_set = VARIATION_1 + VARIATION_4 + VARIATION_5;
    declparam ("n_factor_a", TDim :: NHRU, "[1.0]", "0", "1.2", "a constant in n_factor = n_factor_a - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", & n_factor_a);
    declparam ("n_factor_b", TDim :: NHRU, "[0.0]", "0.0", "1.0", "a constant in n_factor = n_factor_b - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", & n_factor_b);
    declparam ("n_factor_c", TDim :: NHRU, "[0.0]", "0.0", "0.1", "a constant in n_factor = n_factor_c - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", & n_factor_c);
    decllocal ("n_factor_T", TDim :: NHRU, "Days after the start of thaw", "()", & n_factor_T);
    decllocal ("n_factor", TDim :: NHRU, "Calculated value of n_factor from parameters", "()", & n_factor);
    variation_set = VARIATION_2 + VARIATION_3 + VARIATION_4 + VARIATION_5;
    declvar ("SWE_tc", TDim :: NHRU, "SWE thermal conductivity", "(W/(m*K)", & SWE_tc);
    declvar ("SWE_density", TDim :: NHRU, "SWE density", "( kg/m^3)", & SWE_density);
    variation_set = VARIATION_ORG;
InstrumentLogger::instance()->log_instrument_log("</Classtsurface::decl(void)@@@Classtsurface.cpp>");
}
void Classtsurface :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classtsurface::init(void)@@@Classtsurface.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; chkStruct (); ++ hh) {
        hru_tsf_D [hh] = 0.0;
        hru_tsf_acc [hh] = 0.0;
        if (variation == VARIATION_3 || variation == VARIATION_5)
        {
            hru_t_D [hh] = 0.0;
            hru_t_acc [hh] = 0.0;
        }

        if (variation == VARIATION_2 || variation == VARIATION_4)
        {
            hru_T_s_D [hh] = 0.0;
            hru_T_s_acc [hh] = 0.0;
        }

        if (variation == VARIATION_2 || variation == VARIATION_3 || variation == VARIATION_4 || variation == VARIATION_5)
        {
            SWE_tc [hh] = 0.0;
            SWE_density [hh] = 0.0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Classtsurface::init(void)@@@Classtsurface.cpp>");
}
void Classtsurface :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classtsurface::run(void)@@@Classtsurface.cpp>");
    long nstep = getstep () % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
        if (SWE [hh] <= 0.0)
        {
            if (variation == VARIATION_ORG || variation == VARIATION_2 || variation == VARIATION_3)
            {
                if (Zdt [hh] > Zdt_last [hh])
                {
                    Zdt_last [hh] = Zdt [hh];
                }

                double Qn = netD [hh] * 1E6 / 86400;
                hru_tsf [hh] = (W_a [hh] * hru_t [hh] + W_b [hh] * Qn) * atan (W_c [hh] * (Zdt_last [hh] + W_d [hh])) * 2.0 / M_PI;
            }

            else
            if (variation == VARIATION_1 || variation == VARIATION_4 || variation == VARIATION_5)
            {
                n_factor_T [hh] += 1.0 / Global :: Freq;
                n_factor [hh] = n_factor_a [hh] - n_factor_b [hh] * exp (- n_factor_c [hh] * n_factor_T [hh]);
                if (n_factor [hh] >= 0.0)
                {
                    hru_tsf [hh] = hru_t [hh] * n_factor [hh];
                }

                else
                {
                    hru_tsf [hh] = 0.0;
                }

            }

        }

        else
        {
            if (variation == VARIATION_1)
            {
                n_factor_T [hh] = 0.0;
            }

            if (variation == VARIATION_2 || variation == VARIATION_4)
            {
                SWE_density [hh] = rho [hh];
                if (SWE_density [hh] < 156)
                {
                    SWE_tc [hh] = 0.023 - 1.01 * SWE_density [hh] / 1000.0 + 0.234 * sqr (SWE_density [hh] / 1000.0);
                }

                else
                {
                    SWE_tc [hh] = 0.138 - 1.01 * SWE_density [hh] / 1000.0 + 3.233 * sqr (SWE_density [hh] / 1000.0);
                }

                hru_tsf [hh] = hru_T_s_D [hh] - G [hh] * 0.5 * z_s [hh] / SWE_tc [hh];
            }

            if (variation == VARIATION_3 || variation == VARIATION_5)
            {
                if (snowdepth [hh] > 0.0)
                {
                    SWE_density [hh] = SWE [hh] / snowdepth [hh];
                }

                else
                {
                    SWE_density [hh] = 0.0;
                }

                if (SWE_density [hh] < 156)
                {
                    SWE_tc [hh] = 0.023 - 1.01 * SWE_density [hh] / 1000.0 + 0.234 * sqr (SWE_density [hh] / 1000.0);
                }

                else
                {
                    SWE_tc [hh] = 0.138 - 1.01 * SWE_density [hh] / 1000.0 + 3.233 * sqr (SWE_density [hh] / 1000.0);
                }

                double t_minus = tmin [hh];
                if (tmin [hh] >= 0.0)
                {
                    t_minus = 0.0;
                }

                double umin = SWE [hh] * (2.115 + 0.00779 * t_minus) * t_minus / 1000.0;
                hru_tsf [hh] = hru_t_D [hh] - (umin * 1E6 / 86400) * snowdepth [hh] / SWE_tc [hh];
            }

            if (hru_t [hh] > 0.0)
            {
                hru_tsf [hh] = 0.0;
            }

            else
            {
                hru_tsf [hh] = hru_t [hh];
            }

        }

        if (nstep == 0)
        {
            hru_tsf_D [hh] = hru_tsf_acc [hh] / Global :: Freq;
            hru_tsf_acc [hh] = 0.0;
            if (variation == VARIATION_3 || variation == VARIATION_5)
            {
                hru_t_D [hh] = hru_t_acc [hh] / Global :: Freq;
                hru_t_acc [hh] = 0.0;
            }

            if (variation == VARIATION_2 || variation == VARIATION_4)
            {
                hru_T_s_D [hh] = hru_T_s_acc [hh] / Global :: Freq;
                hru_T_s_acc [hh] = 0.0;
            }

        }

        hru_tsf_acc [hh] += hru_tsf [hh];
        if (variation == VARIATION_3 || variation == VARIATION_5)
        {
            hru_t_acc [hh] += hru_t [hh];
        }

        if (variation == VARIATION_2 || variation == VARIATION_4)
        {
            hru_T_s_acc [hh] += T_s [hh];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Classtsurface::run(void)@@@Classtsurface.cpp>");
}