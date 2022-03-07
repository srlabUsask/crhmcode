#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "ClassXG.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
ClassXG * ClassXG :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::klone(string name) const@@@ClassXG.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassXG::klone(string name) const@@@ClassXG.cpp>");
    return new ClassXG (name);
InstrumentLogger::instance()->log_instrument_log("</ClassXG::klone(string name) const@@@ClassXG.cpp>");
}
void ClassXG :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::decl(void)@@@ClassXG.cpp>");
    Description = "'A Simple Thaw-Freeze Algorithm (Changwei, 2013).' \
                 'using variable surface temperature hru_tsf (" + string (DEGREE_CELSIUS) + "),' \
                 'using variable air temperature hru_t (" + string (DEGREE_CELSIUS) + ") and uses parameter n_factor (Woo (2012, p. 57) to estimate surface temperature from the air temperature during snow free periods.'";
    ko = 0.21;
    km = 2.50;
    ka = 0.025;
    ki = 2.24;
    kw = 0.57;
    variation_set = VARIATION_ORG;
    declstatvar ("Zd_front", TDim :: NDEFN, "depth of freezing/thawing fronts", "(m)", & Zd_front, & Zd_front_array, Global :: nlay);
    declstatvar ("Zdf", TDim :: NHRU, "active freezing front", "(m)", & Zdf);
    declstatvar ("Zdt", TDim :: NHRU, "active thawing front", "(m)", & Zdt);
    declstatvar ("Th_low_lay", TDim :: NHRU, "lowest thawed layer", "()", & Th_low_lay);
    declstatvar ("Fz_low_lay", TDim :: NHRU, "lowest frozen layer", "()", & Fz_low_lay);
    declstatvar ("nfront", TDim :: NHRU, "number of freezing/thawing fronts", "()", & nfront);
    declstatvar ("Bfr", TDim :: NHRU, "freeze degree days", "(" + string (DEGREE_CELSIUS) + "*d)", & Bfr);
    declstatvar ("Bth", TDim :: NHRU, "thaw degree days", "(" + string (DEGREE_CELSIUS) + "*d)", & Bth);
    declvar ("pf", TDim :: NDEFN, "freezing ratios", "()", & pf, & pf_lay, Global :: nlay);
    declvar ("pt", TDim :: NDEFN, "thawing ratios", "()", & pt, & pt_lay, Global :: nlay);
    declstatvar ("ttc", TDim :: NDEFN, "thawing thermal conductivity", "(W/(m*K)", & ttc, & ttc_lay, Global :: nlay);
    declstatvar ("ftc", TDim :: NDEFN, "freezing thermal conductivity", "(W/(m*K)", & ftc, & ftc_lay, Global :: nlay);
    declstatvar ("ttc_contents", TDim :: NDEFN, "thawing 0/1 thaw/freeze", "()", & ttc_contents, & ttc_contents_lay, Global :: nlay);
    declstatvar ("ftc_contents", TDim :: NDEFN, "freezing 0/1 freeze/thaw", "()", & ftc_contents, & ftc_contents_lay, Global :: nlay);
    declvar ("tc_composite", TDim :: NDEFN, "freeze/thaw composite ftc/ttc value", "(W/(m*K)", & tc_composite, & tc_composite_lay, Global :: nlay);
    declvar ("tc_composite2", TDim :: NDEFN, "freeze/thaw composite2 ftc/ttc value", "(W/(m*K)", & tc_composite2, & tc_composite2_lay, Global :: nlay);
    declvar ("layer_h2o", TDim :: NDEFN, "water content", "(kg/m^3)", & layer_h2o, & h2o_lay, Global :: nlay);
    decllocal ("B", TDim :: NHRU, "freeze degree days", "()", & B);
    decllocal ("TrigAcc", TDim :: NHRU, "freeze degree days", "()", & TrigAcc);
    decllocal ("TrigState", TDim :: NHRU, "1/0/-1 thaw/standby/freeze", "()", & TrigState);
    decldiag ("XG_moist_d", TDim :: NHRU, "soil moisture depth", "()", & XG_moist_d);
    decldiag ("XG_rechr_d", TDim :: NHRU, "XG calculated soil recharge depth", "()", & XG_rechr_d);
    decllocal ("check_XG_moist", TDim :: NHRU, "sum of XG soil_moist should equal SoilX soil_moist", "()", & check_XG_moist);
    decllocal ("t_trend", TDim :: NHRU, "temperature long term trend", "(" + string (DEGREE_CELSIUS) + ")", & t_trend);
    decllocal ("check_t", TDim :: NHRU, "check temperature source", "(" + string (DEGREE_CELSIUS) + ")", & check_t);
    declstatvar ("XG_max", TDim :: NDEFN, "layer maximum soil moisture content", "(mm)", & XG_max, & XG_max_lay, Global :: nlay);
    declstatvar ("XG_moist", TDim :: NDEFN, "layer soil moisture content", "(mm)", & XG_moist, & XG_moist_lay, Global :: nlay);
    declvar ("theta", TDim :: NDEFN, "XG theta calulated from soil moistures and defaults", "(m^3/m^3)", & theta, & theta_lay, Global :: nlay);
    declstatvar ("rechr_fract", TDim :: NDEFN, "fraction of layer moisture assigned to soilX soil_rechr.", "()", & rechr_fract, & rechr_fract_lay, Global :: nlay);
    declstatvar ("moist_fract", TDim :: NDEFN, "fraction of layer moisture assigned to soilX soil_moist.", "()", & moist_fract, & moist_fract_lay, Global :: nlay);
    declstatvar ("default_fract", TDim :: NDEFN, "below defined soil_moist profile - use default ", "()", & default_fract, & default_fract_lay, Global :: nlay);
    decldiagparam ("Trigthrhld", TDim :: NHRU, "[100.0]", "50.0", "1000.0", "Trigger reference level in degree days", "(" + string (DEGREE_CELSIUS) + "*d)", & Trigthrhld);
    declparam ("N_Soil_layers", TDim :: NHRU, "[2]", "1", "20", "number of soil layers. Must be less than or equal nlay. Define Parameters for layers used. All others are ignored", "()", & N_Soil_layers);
    declparam ("calc_coductivity", TDim :: NHRU, "[0]", "0", "1", "0 - linear method, 1 - use Johansen 1975", "()", & calc_coductivity);
    declparam ("depths", TDim :: NDEFN, "[0.5]", "0.0", "10.0", "depths(thickness) of soil layers", "(m)", & depths, & depths_lay, Global :: nlay);
    declparam ("por", TDim :: NDEFN, "[0.5]", "0.0", "1.0", "porosity", "(m^3/m^3)", & por, & por_lay, Global :: nlay);
    declparam ("theta_default", TDim :: NDEFN, "[0.5]", "0.0", "1.0", "default degree of saturation when not defined by soil module profile from module 'soilX')", "(m^3/m^3)", & theta_default, & theta_default_lay, Global :: nlay);
    declparam ("theta_min", TDim :: NHRU, "[0.001]", "0.0001", "0.1", "minimum value of theta to prevent divide by zero errors)", "(m^3/m^3)", & theta_min);
    declparam ("soil_solid_km", TDim :: NDEFN, "[2.5]", "0.03", "4", "dry soil thermal conductivity", "(W/(m*K)", & soil_solid_km, & soil_solid_km_lay, Global :: nlay);
    declparam ("soil_solid_km_ki", TDim :: NDEFN, "[2.5]", "0.03", "4", "saturated frozen soil thermal conductivity", "(W/(m*K)", & soil_solid_km_ki, & soil_solid_km_ki_lay, Global :: nlay);
    declparam ("soil_solid_km_kw", TDim :: NDEFN, "[2.5]", "0.03", "4", "saturated unfrozen soil thermal conductivity.", "(W/(m*K)", & soil_solid_km_kw, & soil_solid_km_kw_lay, Global :: nlay);
    declparam ("SWE_k", TDim :: NHRU, "[0.35]", "0.1", "1.0", "thermal conductivity of blowing snow.", "(W/(m*K)", & SWE_k);
    declparam ("Zdf_init", TDim :: NHRU, "[0]", "0.0", "3", "initial depth of freezing front. Maximum value limited by freezing algorithm.", "(m)", & Zdf_init);
    declparam ("Zdt_init", TDim :: NHRU, "[0]", "0.0", "3", "initial depth of thawing front. Maximum value limited by thawing algorithm.", "(m)", & Zdt_init);
    declparam ("Zpf_init", TDim :: NHRU, "[2]", "0.0", "30", "initial depth of permafrost front. Maximum value limited by thawing algorithm. If zero set to 2m", "(m)", & Zpf_init);
    declparam ("freeze_kw_ki_update", TDim :: NHRU, "[0]", "0", "1", "Change thermal conductivities kw to ki behind freezing front.", "()", & freeze_kw_ki_update);
    declparam ("thaw_ki_kw_update", TDim :: NHRU, "[0]", "0", "1", "Change thermal conductivities ki to kw behind thawing front.", "()", & thaw_ki_kw_update);
    declparam ("k_update", TDim :: NHRU, "[0]", "0", "2", "Change thermal conductivities ki to kw 0 - never, 1 _ after processing layer, 2 - continuously through layer.", "()", & k_update);
    declgetparam ("*", "soil_moist_max", "(mm)", & soil_moist_max);
    declgetparam ("*", "soil_rechr_max", "(mm)", & soil_rechr_max);
    declgetvar ("*", "soil_moist", "(mm)", & soil_moist);
    declgetvar ("*", "soil_rechr", "(mm)", & soil_rechr);
    variation_set = VARIATION_0;
    declgetvar ("*", "hru_tsf", "(" + string (DEGREE_CELSIUS) + ")", & hru_tsf);
    variation_set = VARIATION_1;
    declparam ("n_factor_a", TDim :: NHRU, "[0.5]", "0", "1.2", "n_factor = n_factor_a - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", & n_factor_a);
    declparam ("n_factor_b", TDim :: NHRU, "[0.54]", "0.0", "1.0", "n_factor = n_factor_b - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", & n_factor_b);
    declparam ("n_factor_c", TDim :: NHRU, "[0.05]", "0.0", "0.1", "n_factor = n_factor_c - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", & n_factor_c);
    decllocal ("n_factor_T", TDim :: NHRU, "Days after the start of thaw", "()", & n_factor_T);
    decllocal ("n_factor", TDim :: NHRU, "calculated value of n_factor from parameters. Woo (2012), p. 57", "()", & n_factor);
    declgetvar ("*", "hru_t", "(" + string (DEGREE_CELSIUS) + ")", & hru_t);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    variation_set = VARIATION_ORG;
InstrumentLogger::instance()->log_instrument_log("</ClassXG::decl(void)@@@ClassXG.cpp>");
}
void ClassXG :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::init(void)@@@ClassXG.cpp>");
    nhru = getdim (TDim :: NHRU);
    nlay = getdim (TDim :: NLAY);
    front_size = nlay;
    if (front_size < 4)
    {
        CRHMException TExcept ("number of layers (nlay) should 4 or greater to give 1 or more fronts.", TExcept :: TERMINATE);
        LogError (TExcept);
    }

    for (hh = 0; hh < nhru; ++ hh) {
        if (N_Soil_layers [hh] > nlay)
        {
            CRHMException TExcept ("nlay cannot be less than N_Soil_layers.", TExcept :: TERMINATE);
            LogError (TExcept);
        }

        nfront [hh] = 0;
        Fz_low_lay [hh] = 1;
        Th_low_lay [hh] = 1;
        t_trend [hh] = 0.0;
        if (Zpf_init [hh] <= 0.0)
        {
            const_cast < double * > (Zpf_init) [hh] = 2.0;
        }

        for (long ll = 0; ll < nlay; ++ ll)
            Zd_front_array [ll] [hh] = 0.0;
        double rechrmax = soil_rechr_max [hh];
        double soilmax = soil_moist_max [hh];
        double profile_depth = 0.0;
        XG_rechr_d [hh] = 0.0;
        XG_moist_d [hh] = 0.0;
        for (long ll = 0; ll < N_Soil_layers [hh]; ++ ll) {
            tc_composite_lay [ll] [hh] = 0;
            tc_composite2_lay [ll] [hh] = 0;
            profile_depth += depths_lay [ll] [hh];
            XG_max_lay [ll] [hh] = por_lay [ll] [hh] * depths_lay [ll] [hh] * 1000.0;
            theta_lay [ll] [hh] = theta_default_lay [ll] [hh];
            if (rechrmax > 0.0)
            {
                if (rechrmax > XG_max_lay [ll] [hh])
                {
                    XG_rechr_d [hh] += depths_lay [ll] [hh];
                    rechr_fract_lay [ll] [hh] = 1.0;
                    rechrmax -= XG_max_lay [ll] [hh];
                }

                else
                {
                    double amount = rechrmax / XG_max_lay [ll] [hh];
                    rechr_fract_lay [ll] [hh] = rechrmax / XG_max_lay [ll] [hh];
                    XG_rechr_d [hh] += depths_lay [ll] [hh] * amount;
                    double left = 1.0 - amount;
                    if (soilmax >= XG_max_lay [ll] [hh] * left)
                    {
                        moist_fract_lay [ll] [hh] = left;
                        soilmax -= XG_max_lay [ll] [hh] * left;
                        XG_moist_d [hh] += depths_lay [ll] [hh];
                    }

                    else
                    {
                        moist_fract_lay [ll] [hh] = (soilmax - rechrmax) / XG_max_lay [ll] [hh];
                        double used = rechr_fract_lay [ll] [hh] + moist_fract_lay [ll] [hh];
                        default_fract_lay [ll] [hh] = 1.0 - used;
                        XG_moist_d [hh] += (XG_rechr_d [hh] + depths_lay [ll] [hh] * used);
                        soilmax = 0.0;
                    }

                    rechrmax = 0.0;
                }

            }

            else
            if (soilmax > 0.0)
            {
                if (soilmax >= XG_max_lay [ll] [hh])
                {
                    XG_moist_d [hh] += depths_lay [ll] [hh];
                    moist_fract_lay [ll] [hh] = 1.0;
                    soilmax -= XG_max_lay [ll] [hh];
                }

                else
                {
                    double amount = soilmax / XG_max_lay [ll] [hh];
                    XG_moist_d [hh] += depths_lay [ll] [hh] * amount;
                    moist_fract_lay [ll] [hh] = amount;
                    double left = 1.0 - amount;
                    if (left)
                    {
                        default_fract_lay [ll] [hh] = left;
                    }

                    soilmax = 0.0;
                }

            }

            else
            {
                default_fract_lay [ll] [hh] = 1;
            }

        }
        Th_low_lay [hh] = 1;
        Fz_low_lay [hh] = 1;
        check_XG_moist [hh] = 0.0;
        for (long ll = 0; ll < N_Soil_layers [hh]; ++ ll) {
            if (soil_moist_max [hh] > 0.0)
            {
                XG_moist_lay [ll] [hh] = rechr_fract_lay [ll] [hh] * XG_max_lay [ll] [hh] * soil_rechr [hh] / soil_rechr_max [hh] + moist_fract_lay [ll] [hh] * XG_max_lay [ll] [hh] * (soil_moist [hh] - soil_rechr [hh]) / (soil_moist_max [hh] - soil_rechr_max [hh]);
            }

            else
            {
                XG_moist_lay [ll] [hh] = 0.0;
            }

            check_XG_moist [hh] += XG_moist_lay [ll] [hh];
            XG_moist_lay [ll] [hh] += default_fract_lay [ll] [hh] * XG_max_lay [ll] [hh] * theta_default_lay [ll] [hh];
            theta_lay [ll] [hh] = XG_moist_lay [ll] [hh] / XG_max_lay [ll] [hh];
            if (theta_lay [ll] [hh] <= theta_min [hh])
            {
                theta_lay [ll] [hh] = theta_min [hh];
            }

            h2o_lay [ll] [hh] = theta_lay [ll] [hh] * por_lay [ll] [hh] * 1000;
            if (k_update [hh])
            {
                if (ftc_contents_lay [ll] [hh] == 1)
                {
                    ftc_lay [ll] [hh] = get_ttc_lay (ll);
                }

                else
                {
                    ftc_lay [ll] [hh] = get_ftc_lay (ll);
                }

                if (ttc_contents_lay [ll] [hh] == 1)
                {
                    ttc_lay [ll] [hh] = get_ftc_lay (ll);
                }

                else
                {
                    ttc_lay [ll] [hh] = get_ttc_lay (ll);
                }

            }

            else
            {
                ftc_lay [ll] [hh] = get_ftc_lay (ll);
                ttc_lay [ll] [hh] = get_ttc_lay (ll);
                ftc_contents_lay [ll] [hh] = 0;
                ttc_contents_lay [ll] [hh] = 0;
            }

        }
        for (long ll = 1; ll < N_Soil_layers [hh]; ++ ll) {
            pf_lay [ll] [hh] = sqrt (ftc_lay [ll - 1] [hh] * h2o_lay [ll] [hh] / (ftc_lay [ll] [hh] * h2o_lay [ll - 1] [hh]));
            pt_lay [ll] [hh] = sqrt (ttc_lay [ll - 1] [hh] * h2o_lay [ll] [hh] / (ttc_lay [ll] [hh] * h2o_lay [ll - 1] [hh]));
        }
        if (rechrmax != 0.0 || soilmax != 0.0)
        {
            string S = string ("'") + Name + " (XG)' too few layers (nlay) to handle soil_max in hru = " + to_string (hh + 1).c_str ();
            CRHMException TExcept (S.c_str (), TExcept :: TERMINATE);
            LogError (TExcept);
        }

        if (profile_depth + 0.00001 < Zpf_init [hh])
        {
            string S = string ("'") + Name + " (XG)' sum of soil layer depths is less than the depth of the initial permafrost in hru = " + to_string (hh + 1).c_str ();
            CRHMException TExcept (S.c_str (), TExcept :: WARNING);
            LogError (TExcept);
        }

        bool EndofProfile = false;
        for (long ll = 0; ll < nlay; ++ ll) {
            if (ll + 1 > N_Soil_layers [hh])
            {
                EndofProfile = true;
            }

            if (depths_lay [ll] [hh] == 0.0 && ! EndofProfile)
            {
                CRHMException TExcept ("Fewer soil layers defined than specified in N_Soil_layers.", TExcept :: TERMINATE);
                LogError (TExcept);
            }

        }
        TrigAcc [hh] = 0.0;
        TrigState [hh] = 0;
        B [hh] = 0.0;
        Zdf [hh] = 0.0;
        Zdt [hh] = 0.0;
        Bfr [hh] = 0.0;
        Bth [hh] = 0.0;
        if (variation == VARIATION_1)
        {
            n_factor [hh] = 0.0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassXG::init(void)@@@ClassXG.cpp>");
}
void ClassXG :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::run(void)@@@ClassXG.cpp>");
    double L = 335000;
    long nstep = getstep ();
    for (hh = 0; chkStruct (); ++ hh) {
        if (nstep == 1)
        {
            const_cast < double * > (depths_lay [N_Soil_layers [hh] - 1]) [hh] = 100.0;
            if (Zdf_init [hh] > 0.0 && Bfr [hh] <= 0.0)
            {
                find_freeze_D (Zdf_init [hh]);
            }

            if (Zdt_init [hh] && Zdt_init [hh] < Zpf_init [hh] && Bth [hh] <= 0.0)
            {
                find_thaw_D (Zdt_init [hh]);
            }

        }

        if (nstep % Global :: Freq == 1 || Global :: Freq == 1)
        {
            B [hh] = 0.0;
        }

        if (variation == VARIATION_ORG)
        {
            B [hh] += hru_tsf [hh] / Global :: Freq;
        }

        else
        {
            B [hh] += hru_t [hh] / Global :: Freq;
        }

        TrigAcc [hh] += B [hh];
        t_trend [hh] -= t_trend [hh] / 192;
        t_trend [hh] += B [hh] / 192;
        if (getstep () % Global :: Freq == 0 || Global :: Freq == 1)
        {
            if (TrigAcc [hh] > Trigthrhld [hh])
            {
                TrigAcc [hh] = Trigthrhld [hh];
            }

            else
            if (TrigAcc [hh] < - Trigthrhld [hh])
            {
                TrigAcc [hh] = - Trigthrhld [hh];
            }

            if (TrigAcc [hh] >= Trigthrhld [hh] / 2.0 && TrigState [hh] == 0 && (Zdf [hh] > 0.0 || nfront [hh]))
            {
                TrigState [hh] = 1;
                Zd_front_array [1] [hh] = - Zdf [hh];
                t_trend [hh] = 0.0;
            }

            if (TrigAcc [hh] <= - Trigthrhld [hh] / 2.0 && TrigState [hh] == 0)
            {
                TrigState [hh] = - 1;
                Zd_front_array [1] [hh] = Zdt [hh];
                t_trend [hh] = 0.0;
            }

            if (TrigState [hh] == - 1 && TrigAcc [hh] >= Trigthrhld [hh] / 2.0 && t_trend [hh] > 0.0)
            {
                TrigState [hh] = 0;
                if (Zdt [hh] > 0.0 && Zdf [hh] > 0.0)
                {
                    if (Zdt [hh] > Zdf [hh])
                    {
                        push_front (Zdt [hh]);
                        Zdt [hh] = 0.0;
                        Bth [hh] = 0.0;
                        Zd_front_array [0] [hh] = 0.0;
                        Zd_front_array [1] [hh] = - Zdf [hh];
                    }

                }

            }

            if (TrigState [hh] == 1 && TrigAcc [hh] <= - Trigthrhld [hh] / 2.0 && t_trend [hh] < 0.0)
            {
                TrigState [hh] = 0;
                if (variation == VARIATION_1)
                {
                    n_factor [hh] = 0.0;
                }

                if (Zdf [hh] > 0.0 && Zdt [hh] > 0.0)
                {
                    if (Zdf [hh] > Zdt [hh])
                    {
                        push_front (- Zdf [hh]);
                        Zdf [hh] = 0.0;
                        Bfr [hh] = 0.0;
                        Zd_front_array [0] [hh] = 0.0;
                        Zd_front_array [1] [hh] = Zdt [hh];
                    }

                }

            }

            Th_low_lay [hh] = 1;
            Fz_low_lay [hh] = 1;
            check_XG_moist [hh] = 0.0;
            for (long ll = 0; ll < N_Soil_layers [hh]; ++ ll) {
                if (soil_moist_max [hh] > 0.0)
                {
                    XG_moist_lay [ll] [hh] = rechr_fract_lay [ll] [hh] * XG_max_lay [ll] [hh] * soil_rechr [hh] / soil_rechr_max [hh] + moist_fract_lay [ll] [hh] * XG_max_lay [ll] [hh] * (soil_moist [hh] - soil_rechr [hh]) / (soil_moist_max [hh] - soil_rechr_max [hh]);
                }

                else
                {
                    XG_moist_lay [ll] [hh] = 0.0;
                }

                check_XG_moist [hh] += XG_moist_lay [ll] [hh];
                XG_moist_lay [ll] [hh] += default_fract_lay [ll] [hh] * XG_max_lay [ll] [hh] * theta_default_lay [ll] [hh];
                theta_lay [ll] [hh] = XG_moist_lay [ll] [hh] / XG_max_lay [ll] [hh];
                if (theta_lay [ll] [hh] <= theta_min [hh])
                {
                    theta_lay [ll] [hh] = theta_min [hh];
                }

                h2o_lay [ll] [hh] = theta_lay [ll] [hh] * por_lay [ll] [hh] * 1000;
                if (k_update [hh])
                {
                    if (ftc_contents_lay [ll] [hh] == 1)
                    {
                        ftc_lay [ll] [hh] = get_ttc_lay (ll);
                    }

                    else
                    {
                        ftc_lay [ll] [hh] = get_ftc_lay (ll);
                    }

                    if (ttc_contents_lay [ll] [hh] == 1)
                    {
                        ttc_lay [ll] [hh] = get_ftc_lay (ll);
                    }

                    else
                    {
                        ttc_lay [ll] [hh] = get_ttc_lay (ll);
                    }

                }

                else
                {
                    ftc_lay [ll] [hh] = get_ftc_lay (ll);
                    ttc_lay [ll] [hh] = get_ttc_lay (ll);
                    ftc_contents_lay [ll] [hh] = 0;
                    ttc_contents_lay [ll] [hh] = 0;
                }

            }
            for (long ll = 1; ll < N_Soil_layers [hh]; ++ ll) {
                pf_lay [ll] [hh] = sqrt (ftc_lay [ll - 1] [hh] * h2o_lay [ll] [hh] / (ftc_lay [ll] [hh] * h2o_lay [ll - 1] [hh]));
                pt_lay [ll] [hh] = sqrt (ttc_lay [ll - 1] [hh] * h2o_lay [ll] [hh] / (ttc_lay [ll] [hh] * h2o_lay [ll - 1] [hh]));
            }
            if (TrigState [hh] < 0.0)
            {
                Bfr [hh] -= B [hh];
                if (Bfr [hh] > 0.0)
                {
                    freeze ();
                    if (Zdt [hh] > 0.0 && Zdf [hh] >= Zdt [hh])
                    {
                        if (nfront [hh] > 0)
                        {
                            double Last = last_front ();
                            if (Last < 0.0)
                            {
                                Zdf [hh] = pop_front ();
                                find_freeze_D (Zdf [hh]);
                                double Last = last_front ();
                                if (Last > 0.0)
                                {
                                    Zdt [hh] = pop_front ();
                                    find_thaw_D (Zdf [hh]);
                                    Zd_front_array [1] [hh] = Zdt [hh];
                                }

                                else
                                if (Last < 0.0)
                                {
                                    string D = StandardConverterUtility :: GetDateTimeInString (Global :: DTnow) + " **never two frozen fronts together, check for thaw front (20447)";
                                    string SS = D + "hh " + to_string (hh) + "Last: " + FloatToStrF (Last, TFloatFormat :: ffFixed, 10, 4);
                                    SS = SS + " Zdt[hh]: " + FloatToStrF (Zdt [hh], TFloatFormat :: ffFixed, 10, 4) + " Zdf[hh]: " + FloatToStrF (Zdt [hh], TFloatFormat :: ffFixed, 10, 4);
                                    CRHMException TExcept (SS.c_str (), TExcept :: WARNING);
                                    LogError (TExcept);
                                }

                                else
                                {
                                    Zdt [hh] = 0.0;
                                    Bth [hh] = 0.0;
                                    Zd_front_array [1] [hh] = 0.0;
                                }

                            }

                            else
                            if (Last < 0.0)
                            {
                                string D = StandardConverterUtility :: GetDateTimeInString (Global :: DTnow) + " **never two thaw fronts together (20462)";
                                string SS = D + "hh " + to_string (hh) + "Last: " + FloatToStrF (Last, TFloatFormat :: ffFixed, 10, 4);
                                SS = SS + " Zdt[hh]: " + FloatToStrF (Zdt [hh], TFloatFormat :: ffFixed, 10, 4) + " Zdf[hh]: " + FloatToStrF (Zdt [hh], TFloatFormat :: ffFixed, 10, 4);
                                CRHMException TExcept (SS.c_str (), TExcept :: WARNING);
                                LogError (TExcept);
                            }

                            else
                            {
                                Zdt [hh] = 0.0;
                                Bth [hh] = 0.0;
                                Zd_front_array [1] [hh] = 0.0;
                            }

                        }

                        else
                        {
                            Zdt [hh] = 0.0;
                            Bth [hh] = 0.0;
                            Zd_front_array [1] [hh] = 0.0;
                        }

                    }

                }

                Zd_front_array [0] [hh] = - Zdf [hh];
            }

            else
            if (TrigState [hh] > 0.0)
            {
                if (variation == VARIATION_1)
                {
                    if (SWE [hh] > 0.0)
                    {
                        n_factor_T [hh] = 0.0;
                    }

                    else
                    {
                        ++ n_factor_T [hh];
                    }

                    n_factor [hh] = n_factor_a [hh] - n_factor_b [hh] * exp (- n_factor_c [hh] * n_factor_T [hh]);
                    if (n_factor [hh] >= 0.0)
                    {
                        B [hh] = B [hh] * n_factor [hh];
                    }

                }

                Bth [hh] += B [hh];
                if (Bth [hh] <= 0.0)
                {
                    Bfr [hh] = Bth [hh];
                    Zdt [hh] = 0.0;
                    Bth [hh] = 0.0;
                }

                else
                {
                    thaw ();
                    if (Zdf [hh] > 0.0 && Zdt [hh] >= Zdf [hh])
                    {
                        if (nfront [hh] > 0)
                        {
                            double Last = last_front ();
                            if (Last > 0.0)
                            {
                                Zdt [hh] = pop_front ();
                                find_thaw_D (Zdt [hh]);
                                Last = last_front ();
                                if (Last < 0.0)
                                {
                                    Zdf [hh] = pop_front ();
                                    find_freeze_D (Zdf [hh]);
                                    Zd_front_array [1] [hh] = - Zdf [hh];
                                }

                                else
                                if (Last > 0.0)
                                {
                                    string D = StandardConverterUtility :: GetDateTimeInString (Global :: DTnow) + " **check for freeze front, never two thaw fronts together (20522)";
                                    string SS = D + "hh " + to_string (hh) + "Last: " + FloatToStrF (Last, TFloatFormat :: ffFixed, 10, 4);
                                    SS = SS + " Zdt[hh]: " + FloatToStrF (Zdt [hh], TFloatFormat :: ffFixed, 10, 4) + " Zdf[hh]: " + FloatToStrF (Zdt [hh], TFloatFormat :: ffFixed, 10, 4);
                                    CRHMException TExcept (SS.c_str (), TExcept :: WARNING);
                                    LogError (TExcept);
                                }

                                else
                                {
                                    Zdf [hh] = 0.0;
                                    Bfr [hh] = 0.0;
                                    Zd_front_array [1] [hh] = 0.0;
                                }

                            }

                            else
                            if (Last < 0.0)
                            {
                                string D = StandardConverterUtility :: GetDateTimeInString (Global :: DTnow) + " never two thaw fronts together (20537)";
                                string SS = D + "hh " + to_string (hh) + "Last: " + FloatToStrF (Last, TFloatFormat :: ffFixed, 10, 4);
                                SS = SS + " Zdt[hh]: " + FloatToStrF (Zdt [hh], TFloatFormat :: ffFixed, 10, 4) + " Zdf[hh]: " + FloatToStrF (Zdt [hh], TFloatFormat :: ffFixed, 10, 4);
                                CRHMException TExcept (SS.c_str (), TExcept :: WARNING);
                                LogError (TExcept);
                            }

                            else
                            {
                                Zdf [hh] = 0.0;
                                Bfr [hh] = 0.0;
                                Zd_front_array [1] [hh] = 0.0;
                            }

                        }

                        else
                        {
                            Zdf [hh] = 0.0;
                            Bfr [hh] = 0.0;
                            Zdt [hh] = 0.0;
                            Bth [hh] = 0.0;
                            TrigState [hh] = 0;
                            Zd_front_array [1] [hh] = 0.0;
                        }

                    }

                }

                Zd_front_array [0] [hh] = Zdt [hh];
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassXG::run(void)@@@ClassXG.cpp>");
}
void ClassXG :: freeze (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::freeze(void)@@@ClassXG.cpp>");
    long lay = 1;
    double Za;
    double L = 335000;
    Zdf [hh] = 0.0;
    double ftc;
    if (k_update [hh] == 2)
    {
        ftc = Interpolated_ftc_lay (Zdf [hh], lay);
    }

    else
    {
        ftc = ftc_lay [lay - 1] [hh];
    }

    Za = sqrt (2ll * 86400ll * ftc * Bfr [hh] / (h2o_lay [lay - 1] [hh] * L));
    while (Za > depths_lay [lay - 1] [hh] && lay < N_Soil_layers [hh]) {
        Zdf [hh] += depths_lay [lay - 1] [hh];
        Za = (Za - depths_lay [lay - 1] [hh]) / pf_lay [lay] [hh];
        ++ lay;
        if (k_update [hh] > 0 && freeze_kw_ki_update [hh] && lay > Fz_low_lay [hh])
        {
            ftc_lay [Fz_low_lay [hh] - 1] [hh] = get_ttc_lay (Fz_low_lay [hh] - 1);
            ftc_contents_lay [Fz_low_lay [hh] - 1] [hh] = 1;
            pf_lay [Fz_low_lay [hh]] [hh] = sqrt (ftc_lay [Fz_low_lay [hh] - 1] [hh] * h2o_lay [Fz_low_lay [hh]] [hh] / (ftc_lay [Fz_low_lay [hh]] [hh] * h2o_lay [Fz_low_lay [hh] - 1] [hh]));
            Fz_low_lay [hh] = lay;
            tc_composite_lay [lay - 1] [hh] = ftc_lay [lay - 1] [hh];
        }

    }
    Zdf [hh] += Za;
    if (Zdf [hh] > Zpf_init [hh])
    {
        Zdf [hh] = Zpf_init [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassXG::freeze(void)@@@ClassXG.cpp>");
}
void ClassXG :: thaw (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::thaw(void)@@@ClassXG.cpp>");
    long lay = 1;
    double Za;
    double L = 335000;
    Zdt [hh] = 0.0;
    double ttc;
    if (k_update [hh] == 2)
    {
        ttc = Interpolated_ttc_lay (Zdf [hh], lay);
    }

    else
    {
        ttc = ttc_lay [lay - 1] [hh];
    }

    Za = sqrt (2ll * 86400ll * ttc * Bth [hh] / (h2o_lay [lay - 1] [hh] * L));
    while (Za > depths_lay [lay - 1] [hh] && lay < N_Soil_layers [hh]) {
        Zdt [hh] += depths_lay [lay - 1] [hh];
        Za = (Za - depths_lay [lay - 1] [hh]) / pt_lay [lay] [hh];
        ++ lay;
        if (k_update [hh] > 0 && thaw_ki_kw_update [hh] && lay > Th_low_lay [hh])
        {
            ttc_lay [Th_low_lay [hh] - 1] [hh] = get_ftc_lay (Th_low_lay [hh] - 1);
            ttc_contents_lay [Th_low_lay [hh] - 1] [hh] = 1;
            pt_lay [Th_low_lay [hh]] [hh] = sqrt (ttc_lay [Th_low_lay [hh] - 1] [hh] * h2o_lay [Th_low_lay [hh]] [hh] / (ttc_lay [Th_low_lay [hh]] [hh] * h2o_lay [Th_low_lay [hh] - 1] [hh]));
            Th_low_lay [hh] = lay;
            tc_composite_lay [lay - 1] [hh] = ttc_lay [lay - 1] [hh];
        }

    }
    Zdt [hh] += Za;
    if (Zdt [hh] > Zpf_init [hh])
    {
        Zdt [hh] = Zpf_init [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassXG::thaw(void)@@@ClassXG.cpp>");
}
double ClassXG :: Interpolated_ttc_lay (double Za, long lay)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::Interpolated_ttc_lay(double Za, long lay)@@@ClassXG.cpp>");
    if (! thaw_ki_kw_update [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::Interpolated_ttc_lay(double Za, long lay)@@@ClassXG.cpp>");
        return (ttc_lay [lay - 1] [hh]);
    }

    double split = (Za - Zdt [hh]) / depths_lay [lay - 1] [hh];
    if (split >= 1.0)
    {
        split = 1.0;
    }

    double combination = ttc_lay [lay - 1] [hh] - split * (ttc_lay [lay - 1] [hh] - ftc_lay [lay - 1] [hh]);
    tc_composite2_lay [lay - 1] [hh] = combination;

InstrumentLogger::instance()->log_instrument_log("</ClassXG::Interpolated_ttc_lay(double Za, long lay)@@@ClassXG.cpp>");
    return (combination);
InstrumentLogger::instance()->log_instrument_log("</ClassXG::Interpolated_ttc_lay(double Za, long lay)@@@ClassXG.cpp>");
}
double ClassXG :: Interpolated_ftc_lay (double Za, long lay)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::Interpolated_ftc_lay(double Za, long lay)@@@ClassXG.cpp>");
    if (! freeze_kw_ki_update [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::Interpolated_ftc_lay(double Za, long lay)@@@ClassXG.cpp>");
        return (ftc_lay [lay - 1] [hh]);
    }

    double split = (Za - Zdf [hh]) / depths_lay [lay - 1] [hh];
    if (split >= 1.0)
    {
        split = 1.0;
    }

    double combination = ftc_lay [lay - 1] [hh] + split * (ttc_lay [lay - 1] [hh] - ftc_lay [lay - 1] [hh]);
    tc_composite2_lay [lay - 1] [hh] = combination;

InstrumentLogger::instance()->log_instrument_log("</ClassXG::Interpolated_ftc_lay(double Za, long lay)@@@ClassXG.cpp>");
    return (combination);
InstrumentLogger::instance()->log_instrument_log("</ClassXG::Interpolated_ftc_lay(double Za, long lay)@@@ClassXG.cpp>");
}
void ClassXG :: find_thaw_D (double dt)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::find_thaw_D(double dt)@@@ClassXG.cpp>");
    if (dt == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::find_thaw_D(double dt)@@@ClassXG.cpp>");
        return;
    }

    for (long B = 1; B < 50000; ++ B) {
        Bth [hh] = B;
        thaw ();
        if (Zdt [hh] > dt || Zdt [hh] >= Zpf_init [hh])
        {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::find_thaw_D(double dt)@@@ClassXG.cpp>");
            return;
        }

    }
    string S = string ("'") + Name + " (XG)' Zdt too large in hru = " + to_string (hh + 1).c_str ();
    CRHMException TExcept (S.c_str (), TExcept :: TERMINATE);
    LogError (TExcept);
    throw TExcept;
InstrumentLogger::instance()->log_instrument_log("</ClassXG::find_thaw_D(double dt)@@@ClassXG.cpp>");
}
void ClassXG :: find_freeze_D (double df)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::find_freeze_D(double df)@@@ClassXG.cpp>");
    if (df == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::find_freeze_D(double df)@@@ClassXG.cpp>");
        return;
    }

    for (long B = 1; B < 50000; ++ B) {
        Bfr [hh] = B;
        freeze ();
        if (Zdf [hh] > df || Zdf [hh] >= Zpf_init [hh])
        {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::find_freeze_D(double df)@@@ClassXG.cpp>");
            return;
        }

    }
    string S = string ("'") + Name + " (XG)' Zdf too large in hru = " + to_string (hh + 1).c_str ();
    CRHMException TExcept (S.c_str (), TExcept :: TERMINATE);
    LogError (TExcept);
    throw TExcept;
InstrumentLogger::instance()->log_instrument_log("</ClassXG::find_freeze_D(double df)@@@ClassXG.cpp>");
}
void ClassXG :: push_front (double D)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::push_front(double D)@@@ClassXG.cpp>");
    if (nfront [hh] >= front_size - 3)
    {
        string S = string ("'") + Name + " (XG)' too many fronts in hru = " + to_string (hh + 1).c_str ();
        CRHMException TExcept (S.c_str (), TExcept :: TERMINATE);
        LogError (TExcept);
        throw TExcept;
    }

    for (long ii = nfront [hh] + 1; 2 <= ii; -- ii)
        Zd_front_array [ii + 1] [hh] = Zd_front_array [ii] [hh];
    ++ nfront [hh];
    Zd_front_array [2] [hh] = D;
InstrumentLogger::instance()->log_instrument_log("</ClassXG::push_front(double D)@@@ClassXG.cpp>");
}
double ClassXG :: pop_front (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::pop_front(void)@@@ClassXG.cpp>");
    double D = fabs (Zd_front_array [2] [hh]);
    for (long ii = 2; ii < nfront [hh] + 1; ++ ii)
        Zd_front_array [ii] [hh] = Zd_front_array [ii + 1] [hh];
    Zd_front_array [nfront [hh] + 1] [hh] = 0.0;
    -- nfront [hh];

InstrumentLogger::instance()->log_instrument_log("</ClassXG::pop_front(void)@@@ClassXG.cpp>");
    return D;
InstrumentLogger::instance()->log_instrument_log("</ClassXG::pop_front(void)@@@ClassXG.cpp>");
}
double ClassXG :: last_front (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::last_front(void)@@@ClassXG.cpp>");
    if (! nfront [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::last_front(void)@@@ClassXG.cpp>");
        return 0.0;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::last_front(void)@@@ClassXG.cpp>");
        return (Zd_front_array [2] [hh]);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassXG::last_front(void)@@@ClassXG.cpp>");
}
void ClassXG :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::finish(bool good)@@@ClassXG.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (XG)'  Zdt     (mm): ").c_str (), Zdt [hh]);
        LogMessageA (hh, string ("'" + Name + " (XG)'  Zdf     (mm): ").c_str (), Zdf [hh]);
        LogMessageA (hh, string ("'" + Name + " (XG)'  nfront  ()  : ").c_str (), nfront [hh]);
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassXG::finish(bool good)@@@ClassXG.cpp>");
}
double ClassXG :: get_ftc_lay (long lay)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::get_ftc_lay(long lay)@@@ClassXG.cpp>");
    if (calc_coductivity [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::get_ftc_lay(long lay)@@@ClassXG.cpp>");
        return (soil_solid_km_ki_lay [lay] [hh] - soil_solid_km_lay [lay] [hh]) * sqr (h2o_lay [lay] [hh] / (1000.0 * por_lay [lay] [hh])) + soil_solid_km_lay [lay] [hh];
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::get_ftc_lay(long lay)@@@ClassXG.cpp>");
        return (1.0 - por_lay [lay] [hh]) * soil_solid_km_lay [lay] [hh] + h2o_lay [lay] [hh] / 1000.0 * kw + (por_lay [lay] [hh] - h2o_lay [lay] [hh] / 1000.0) * ka;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassXG::get_ftc_lay(long lay)@@@ClassXG.cpp>");
}
double ClassXG :: get_ttc_lay (long lay)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXG::get_ttc_lay(long lay)@@@ClassXG.cpp>");
    if (calc_coductivity [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::get_ttc_lay(long lay)@@@ClassXG.cpp>");
        return soil_solid_km_lay [lay] [hh] * pow (soil_solid_km_ki_lay [lay] [hh] / soil_solid_km_lay [lay] [hh], h2o_lay [lay] [hh] / (1000.0 * por_lay [lay] [hh]));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassXG::get_ttc_lay(long lay)@@@ClassXG.cpp>");
        return (1.0 - por_lay [lay] [hh]) * soil_solid_km_lay [lay] [hh] + h2o_lay [lay] [hh] / 1000.0 * ki + (por_lay [lay] [hh] - h2o_lay [lay] [hh] / 1000.0) * ka;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassXG::get_ttc_lay(long lay)@@@ClassXG.cpp>");
}