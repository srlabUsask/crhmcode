#include "ClassSnobalBase.h"
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
void ClassSnobalBase :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::init(void)@@@ClassSnobalBase.cpp>");
    input_rec1 = new INPUT_REC [nhru];
    input_rec2 = new INPUT_REC [nhru];
    time_step = new long [nhru];
    current_time = new long [nhru];
    computed = new int * [nhru];
    input_deltas = new INPUT_REC * [nhru];
    precip_info = new PRECIP_REC * [nhru];
    tstep_info = new TSTEP_REC * [nhru];
    for (long ii = 0; ii < nhru; ++ ii) {
        computed [ii] = new int [4];
        input_deltas [ii] = new INPUT_REC [4];
        precip_info [ii] = new PRECIP_REC [4];
        tstep_info [ii] = new TSTEP_REC [4];
    }
    for (hh = 0; chkStruct (); ++ hh) {
        P_a [hh] = 101.3f * pow ((293.0f - 0.0065f * hru_elev [hh]) / 293.0f, 5.26f) * 1000.0f;
        T_s [hh] = - 75.0;
        T_s_0 [hh] = - 75.0;
        T_s_l [hh] = - 75.0;
        rho [hh] = 218.0;
        h2o_sat [hh] = 0.0;
        z_s [hh] = 0.0;
        z_s_0 [hh] = 0.0;
        z_s_l [hh] = 0.0;
        m_s [hh] = 0.0;
        m_s_0 [hh] = 0.0;
        m_s_l [hh] = 0.0;
        cc_s [hh] = 0.0;
        cc_s_0 [hh] = 0.0;
        cc_s_l [hh] = 0.0;
        h2o [hh] = 0.0;
        h2o_max [hh] = 0.0;
        h2o_total [hh] = 0.0;
        melt [hh] = 0.0;
        z_snow [hh] = 0.0;
        ro_predict [hh] = 0.0;
        T_snow [hh] = 0.0;
        T_rain [hh] = 0.0;
        layer_count [hh] = 0;
        isothermal [hh] = 0;
        snowcover [hh] = 0;
        stop_no_snow [hh] = 0;
        if (hh < nhru)
        {
            current_time [hh] = 0;
        }

        melt_direct_cum [hh] = 0.0;
        E_s_cum [hh] = 0.0;
        m_precip_cum [hh] = 0.0;
        m_rain_cum [hh] = 0.0;
        m_snow_cum [hh] = 0.0;
        m_drift_cum [hh] = 0.0;
        m_subl_cum [hh] = 0.0;
        cumsnowmelt [hh] = 0.0;
        L_v_E [hh] = 0.0;
        E [hh] = 0.0;
        H [hh] = 0.0;
        G [hh] = 0.0;
        M [hh] = 0.0;
        R_n [hh] = 0.0;
        delta_Q [hh] = 0.0;
        delta_Q_0 [hh] = 0.0;
        if (hh < nhru)
        {
            tstep_info [hh] [DATA_TSTEP].level = DATA_TSTEP;
            tstep_info [hh] [DATA_TSTEP].time_step = 24 * 3600 / Global :: Freq;
            tstep_info [hh] [DATA_TSTEP].intervals = 0;
            tstep_info [hh] [DATA_TSTEP].threshold = DEFAULT_NORMAL_THRESHOLD;
            tstep_info [hh] [NORMAL_TSTEP].level = NORMAL_TSTEP;
            tstep_info [hh] [NORMAL_TSTEP].time_step = 24 * 3600 / Global :: Freq;
            tstep_info [hh] [NORMAL_TSTEP].intervals = 1;
            tstep_info [hh] [NORMAL_TSTEP].threshold = DEFAULT_NORMAL_THRESHOLD;
            tstep_info [hh] [MEDIUM_TSTEP].level = MEDIUM_TSTEP;
            tstep_info [hh] [MEDIUM_TSTEP].time_step = 24 * 3600 / Global :: Freq / 4;
            tstep_info [hh] [MEDIUM_TSTEP].intervals = 4;
            tstep_info [hh] [MEDIUM_TSTEP].threshold = DEFAULT_MEDIUM_THRESHOLD;
            tstep_info [hh] [SMALL_TSTEP].level = SMALL_TSTEP;
            tstep_info [hh] [SMALL_TSTEP].time_step = 24 * 3600 / Global :: Freq / 60;
            tstep_info [hh] [SMALL_TSTEP].intervals = 15;
            tstep_info [hh] [SMALL_TSTEP].threshold = DEFAULT_SMALL_THRESHOLD;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::init(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::finish(bool good)@@@ClassSnobalBase.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (Snobal)' m_precip_cum    (mm) (mm*hru) (mm*hru/basin): ").c_str (), m_precip_cum [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Snobal)' m_rain_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str (), m_rain_cum [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Snobal)' m_snow_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str (), m_snow_cum [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Snobal)' m_drift_cum     (mm) (mm*hru) (mm*hru/basin): ").c_str (), m_drift_cum [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Snobal)' m_subl_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str (), - m_subl_cum [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Snobal)' SWE             (mm) (mm*hru) (mm*hru/basin): ").c_str (), m_s [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
        LogMessageA (hh, string ("'" + Name + " (Snobal)' E_s_cum         (mm) (mm*hru) (mm*hru/basin): ").c_str (), E_s_cum [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Snobal)' cumsnowmelt     (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumsnowmelt [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Snobal)' melt_direct_cum (mm) (mm*hru) (mm*hru/basin): ").c_str (), melt_direct_cum [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
    delete [] input_rec1;
    delete [] input_rec2;
    delete [] time_step;
    delete [] current_time;
    for (long ii = 0; ii < nhru; ++ ii) {
        delete [] computed [ii];
        delete [] input_deltas [ii];
        delete [] precip_info [ii];
        delete [] tstep_info [ii];
    }
    delete [] computed;
    delete [] input_deltas;
    delete [] precip_info;
    delete [] tstep_info;
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::finish(bool good)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: init_snow (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::init_snow(void)@@@ClassSnobalBase.cpp>");
    double rho_dry;
    m_s [hh] = rho [hh] * z_s [hh];
    _calc_layers ();
    if (layer_count [hh] == 0)
    {
        if (m_s [hh] > 0.0)
        {
            h2o_total [hh] += m_s [hh];
            melt_direct_int [hh] += m_s [hh];
        }

        rho [hh] = 0.0;
        m_s [hh] = cc_s [hh] = 0.0;
        m_s_0 [hh] = cc_s_0 [hh] = 0.0;
        m_s_l [hh] = cc_s_l [hh] = 0.0;
        T_s [hh] = T_s_0 [hh] = T_s_l [hh] = MIN_SNOW_TEMP + FREEZE;
        h2o_vol [hh] = h2o [hh] = h2o_max [hh] = h2o_sat [hh] = 0.0;
    }

    else
    {
        _layer_mass ();
        cc_s_0 [hh] = _cold_content (T_s_0 [hh], m_s_0 [hh]);
        if (layer_count [hh] == 2)
        {
            cc_s_l [hh] = _cold_content (T_s_l [hh], m_s_l [hh]);
        }

        else
        {
            T_s_l [hh] = MIN_SNOW_TEMP + FREEZE;
            cc_s_l [hh] = 0.0;
        }

        h2o_vol [hh] = h2o_sat [hh] * max_h2o_vol [hh];
        rho_dry = DRY_SNO_RHO (rho [hh], h2o_vol [hh]);
        h2o_max [hh] = H2O_LEFT (z_s [hh], rho_dry, max_h2o_vol [hh]);
        h2o [hh] = h2o_sat [hh] * h2o_max [hh];
        stop_no_snow [hh] = 0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::init_snow(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _calc_layers (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_calc_layers(void)@@@ClassSnobalBase.cpp>");
    if (m_s [hh] <= tstep_info [hh] [SMALL_TSTEP].threshold)
    {
        layer_count [hh] = 0;
        z_s [hh] = z_s_0 [hh] = z_s_l [hh] = 0.0;
    }

    else
    if (z_s [hh] < max_z_s_0 [hh])
    {
        layer_count [hh] = 1;
        z_s_0 [hh] = z_s [hh];
        z_s_l [hh] = 0.0;
    }

    else
    {
        layer_count [hh] = 2;
        z_s_0 [hh] = max_z_s_0 [hh];
        z_s_l [hh] = z_s [hh] - z_s_0 [hh];
        if (z_s_l [hh] * rho [hh] < tstep_info [hh] [SMALL_TSTEP].threshold)
        {
            layer_count [hh] = 1;
            z_s_0 [hh] = z_s [hh];
            z_s_l [hh] = 0.0;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_calc_layers(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _layer_mass (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_layer_mass(void)@@@ClassSnobalBase.cpp>");
    if (layer_count [hh] == 0)
    {
        m_s_0 [hh] = 0.0;
        m_s_l [hh] = 0.0;
    }

    else
    {
        m_s_0 [hh] = rho [hh] * z_s_0 [hh];
        if (layer_count [hh] == 2)
        {
            m_s_l [hh] = rho [hh] * z_s_l [hh];
        }

        else
        {
            m_s_l [hh] = 0.0;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_layer_mass(void)@@@ClassSnobalBase.cpp>");
}
double ClassSnobalBase :: _cold_content (double temp, double mass)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_cold_content(double temp, double mass)@@@ClassSnobalBase.cpp>");
    if (temp < FREEZE)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_cold_content(double temp, double mass)@@@ClassSnobalBase.cpp>");
        return heat_stor (CP_ICE (temp), mass, (temp - FREEZE));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_cold_content(double temp, double mass)@@@ClassSnobalBase.cpp>");
        return 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_cold_content(double temp, double mass)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: do_data_tstep (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::do_data_tstep(void)@@@ClassSnobalBase.cpp>");
    int level;
    S_n [hh] = input_rec1 [hh].S_n;
    I_lw [hh] = input_rec1 [hh].I_lw;
    T_a [hh] = input_rec1 [hh].T_a;
    e_a [hh] = input_rec1 [hh].e_a;
    u [hh] = input_rec1 [hh].u;
    T_g [hh] = input_rec1 [hh].T_g;
    F_g [hh] = input_rec1 [hh].F_g;
    input_deltas [hh] [DATA_TSTEP].S_n = input_rec2 [hh].S_n - input_rec1 [hh].S_n;
    input_deltas [hh] [DATA_TSTEP].I_lw = input_rec2 [hh].I_lw - input_rec1 [hh].I_lw;
    input_deltas [hh] [DATA_TSTEP].T_a = input_rec2 [hh].T_a - input_rec1 [hh].T_a;
    input_deltas [hh] [DATA_TSTEP].e_a = input_rec2 [hh].e_a - input_rec1 [hh].e_a;
    input_deltas [hh] [DATA_TSTEP].u = input_rec2 [hh].u - input_rec1 [hh].u;
    input_deltas [hh] [DATA_TSTEP].T_g = input_rec2 [hh].T_g - input_rec1 [hh].T_g;
    input_deltas [hh] [DATA_TSTEP].F_g = input_rec2 [hh].F_g - input_rec1 [hh].F_g;
    precip_info [hh] -> m_drift = m_drift [hh];
    precip_info [hh] -> m_subl = m_subl [hh];
    if (precip_now [hh])
    {
        precip_info [hh] -> m_pp = m_precip [hh];
        precip_info [hh] -> m_snow = m_snow [hh];
        precip_info [hh] -> m_rain = m_rain [hh];
        if (precip_info [hh] -> m_snow > 0.0)
        {
            precip_info [hh] -> z_snow = z_snow [hh];
        }

        else
        {
            precip_info [hh] -> z_snow = 0.0;
        }

        if ((precip_info [hh] -> m_snow > 0.0) && (precip_info [hh] -> m_rain > 0.0))
        {
            T_snow [hh] = FREEZE;
            h2o_sat_snow [hh] = 1.0;
            T_rain [hh] = T_pp [hh];
        }

        else
        if (precip_info [hh] -> m_snow > 0.0)
        {
            if (T_pp [hh] < FREEZE)
            {
                T_snow [hh] = T_pp [hh];
                h2o_sat_snow [hh] = 0.0;
            }

            else
            {
                T_snow [hh] = FREEZE;
                h2o_sat_snow [hh] = 1.0;
            }

        }

        else
        if (precip_info [hh] -> m_rain > 0.0)
        {
            T_rain [hh] = T_pp [hh];
        }

    }

    else
    {
        precip_info [hh] -> m_pp = 0.0;
        precip_info [hh] -> m_snow = 0.0;
        precip_info [hh] -> m_rain = 0.0;
        precip_info [hh] -> z_snow = 0.0;
    }

    for (level = NORMAL_TSTEP; level <= SMALL_TSTEP; ++ level)
        computed [hh] [level] = 0;
    _divide_tstep (tstep_info [hh]);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::do_data_tstep(void)@@@ClassSnobalBase.cpp>");
}
int ClassSnobalBase :: _divide_tstep (TSTEP_REC * tstep)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_divide_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
    TSTEP_REC * next_lvl_tstep;
    INPUT_REC * curr_lvl_deltas;
    INPUT_REC * next_lvl_deltas;
    PRECIP_REC * curr_lvl_precip;
    PRECIP_REC * next_lvl_precip;
    int next_level;
    next_level = tstep -> level + 1;
    next_lvl_tstep = & tstep_info [hh] [next_level];
    curr_lvl_deltas = & input_deltas [hh] [tstep -> level];
    next_lvl_deltas = & input_deltas [hh] [next_level];
    curr_lvl_precip = & precip_info [hh] [tstep -> level];
    next_lvl_precip = & precip_info [hh] [next_level];
    if (! computed [hh] [next_level])
    {
        next_lvl_deltas -> S_n = curr_lvl_deltas -> S_n / next_lvl_tstep -> intervals;
        next_lvl_deltas -> I_lw = curr_lvl_deltas -> I_lw / next_lvl_tstep -> intervals;
        next_lvl_deltas -> T_a = curr_lvl_deltas -> T_a / next_lvl_tstep -> intervals;
        next_lvl_deltas -> e_a = curr_lvl_deltas -> e_a / next_lvl_tstep -> intervals;
        next_lvl_deltas -> u = curr_lvl_deltas -> u / next_lvl_tstep -> intervals;
        next_lvl_deltas -> T_g = curr_lvl_deltas -> T_g / next_lvl_tstep -> intervals;
        next_lvl_deltas -> F_g = curr_lvl_deltas -> F_g / next_lvl_tstep -> intervals;
        next_lvl_precip -> m_pp = curr_lvl_precip -> m_pp / next_lvl_tstep -> intervals;
        next_lvl_precip -> m_rain = curr_lvl_precip -> m_rain / next_lvl_tstep -> intervals;
        next_lvl_precip -> m_snow = curr_lvl_precip -> m_snow / next_lvl_tstep -> intervals;
        next_lvl_precip -> m_drift = curr_lvl_precip -> m_drift / next_lvl_tstep -> intervals;
        next_lvl_precip -> m_subl = curr_lvl_precip -> m_subl / next_lvl_tstep -> intervals;
        next_lvl_precip -> z_snow = curr_lvl_precip -> z_snow / next_lvl_tstep -> intervals;
        computed [hh] [next_level] = 1;
    }

    for (int ii = 0; (ii < next_lvl_tstep -> intervals) && ! stop_no_snow [hh]; ++ ii) {
        if ((next_level < SMALL_TSTEP) && _below_thold (next_lvl_tstep -> threshold))
        {
            if (! _divide_tstep (next_lvl_tstep))
            {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_divide_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
                return 0;
            }

        }

        else
        {
            if (! _do_tstep (next_lvl_tstep))
            {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_divide_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
                return 0;
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_divide_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
    return 1;
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_divide_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
}
int ClassSnobalBase :: _below_thold (double threshold)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_below_thold(double threshold)@@@ClassSnobalBase.cpp>");
    if (layer_count [hh] == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_below_thold(double threshold)@@@ClassSnobalBase.cpp>");
        return 0;
    }

    if (layer_count [hh] == 1)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_below_thold(double threshold)@@@ClassSnobalBase.cpp>");
        return (m_s [hh] < threshold);
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_below_thold(double threshold)@@@ClassSnobalBase.cpp>");
        return ((m_s_0 [hh] < threshold) || (m_s_l [hh] < threshold));
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_below_thold(double threshold)@@@ClassSnobalBase.cpp>");
}
int ClassSnobalBase :: _do_tstep (TSTEP_REC * tstep)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_do_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
    time_step [hh] = tstep -> time_step;
    m_precip [hh] = precip_info [hh] [tstep -> level].m_pp;
    m_rain [hh] = precip_info [hh] [tstep -> level].m_rain;
    m_snow [hh] = precip_info [hh] [tstep -> level].m_snow;
    m_drift [hh] = precip_info [hh] [tstep -> level].m_drift;
    m_subl [hh] = precip_info [hh] [tstep -> level].m_subl;
    z_snow [hh] = precip_info [hh] [tstep -> level].z_snow;
    h2o_total [hh] = 0.0;
    melt [hh] = 0.0;
    snowcover [hh] = (layer_count [hh] > 0);
    if (! _e_bal ())
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_do_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
        return 0;
    }

    _mass_bal ();
    current_time [hh] += time_step [hh];
    snowmelt_int [hh] += ro_predict [hh];
    E_s_int [hh] += E_s [hh];
    E_int [hh] += E [hh];
    E_s_0_int [hh] += E_s_0 [hh];
    E_s_l_int [hh] += E_s_l [hh];
    S_n [hh] += input_deltas [hh] [tstep -> level].S_n;
    I_lw [hh] += input_deltas [hh] [tstep -> level].I_lw;
    T_a [hh] += input_deltas [hh] [tstep -> level].T_a;
    e_a [hh] += input_deltas [hh] [tstep -> level].e_a;
    u [hh] += input_deltas [hh] [tstep -> level].u;
    T_g [hh] += input_deltas [hh] [tstep -> level].T_g;
    F_g [hh] += input_deltas [hh] [tstep -> level].F_g;

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_do_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
    return 1;
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_do_tstep(TSTEP_REC * tstep)@@@ClassSnobalBase.cpp>");
}
int ClassSnobalBase :: _e_bal (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_e_bal(void)@@@ClassSnobalBase.cpp>");
    if (snowcover [hh])
    {
        _net_rad ();
        if (! _h_le ())
        {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_e_bal(void)@@@ClassSnobalBase.cpp>");
            return 0;
        }

        if (layer_count [hh] == 1)
        {
            if (T_g_or_G_flux [hh])
            {
                G [hh] = F_g [hh];
            }

            else
            {
                G [hh] = g_soil (rho [hh], T_s_0 [hh], T_g [hh], z_s_0 [hh], z_g [hh], P_a [hh]);
            }

            G_0 [hh] = G [hh];
        }

        else
        {
            if (T_g_or_G_flux [hh])
            {
                G [hh] = F_g [hh];
            }

            else
            {
                G [hh] = g_soil (rho [hh], T_s_l [hh], T_g [hh], z_s_l [hh], z_g [hh], P_a [hh]);
            }

            G_0 [hh] = g_snow (rho [hh], rho [hh], T_s_0 [hh], T_s_l [hh], z_s_0 [hh], z_s_l [hh], P_a [hh]);
        }

        _advec ();
        delta_Q_0 [hh] = R_n [hh] + H [hh] + L_v_E [hh] + G_0 [hh] + M [hh];
        if (layer_count [hh] == 1)
        {
            delta_Q [hh] = delta_Q_0 [hh];
        }

        else
        {
            delta_Q [hh] = delta_Q_0 [hh] + G [hh] - G_0 [hh];
        }

    }

    else
    {
        R_n [hh] = 0.0;
        H [hh] = L_v_E [hh] = E [hh] = 0.0;
        G [hh] = G_0 [hh] = 0.0;
        M [hh] = 0.0;
        delta_Q [hh] = delta_Q_0 [hh] = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_e_bal(void)@@@ClassSnobalBase.cpp>");
    return 1;
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_e_bal(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _net_rad (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_net_rad(void)@@@ClassSnobalBase.cpp>");
    R_n [hh] = S_n [hh] + (I_lw [hh] - SNOW_EMISSIVITY * STEF_BOLTZ * pow (T_s_0 [hh], 4.0f));
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_net_rad(void)@@@ClassSnobalBase.cpp>");
}
int ClassSnobalBase :: _h_le (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_h_le(void)@@@ClassSnobalBase.cpp>");
    double e_s, e_a_fix;
    double sat_vp;
    double rel_z_T;
    double rel_z_u;
    e_s = sati (T_s_0 [hh]);
    sat_vp = sati (T_a [hh]);
    if (e_a [hh] > sat_vp)
    {
        e_a_fix = sat_vp;
    }

    else
    {
        e_a_fix = e_a [hh];
    }

    if (! relative_hts [hh])
    {
        rel_z_T = z_T [hh];
        rel_z_u = z_u [hh];
    }

    else
    {
        rel_z_T = z_T [hh] - z_s [hh];
        if (rel_z_T < 1.0)
        {
            rel_z_T = 1.0;
        }

        rel_z_u = z_u [hh] - z_s [hh];
        if (rel_z_u < 1.0)
        {
            rel_z_u = 1.0;
        }

    }

    if (hle1 (P_a [hh], T_a [hh], T_s_0 [hh], rel_z_T, e_a_fix, e_s, rel_z_T, u [hh], rel_z_u, z_0 [hh], H [hh], L_v_E [hh], E [hh]))
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_h_le(void)@@@ClassSnobalBase.cpp>");
        return 1;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_h_le(void)@@@ClassSnobalBase.cpp>");
    return 1;
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_h_le(void)@@@ClassSnobalBase.cpp>");
}
double ClassSnobalBase :: g_soil (double rho, double tsno, double tg, double ds, double dg, double pa)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::g_soil(double rho, double tsno, double tg, double ds, double dg, double pa)@@@ClassSnobalBase.cpp>");
    double k_g;
    double kcs;
    double k_s;
    double g;
    if (tsno > FREEZE)
    {
        tsno = FREEZE;
    }

    k_g = efcon (KT_sand [hh], tg, pa);
    kcs = KTS (rho);
    k_s = efcon (kcs, tsno, pa);
    g = ssxfr (k_s, k_g, tsno, tg, ds, dg);

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::g_soil(double rho, double tsno, double tg, double ds, double dg, double pa)@@@ClassSnobalBase.cpp>");
    return (g);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::g_soil(double rho, double tsno, double tg, double ds, double dg, double pa)@@@ClassSnobalBase.cpp>");
}
double ClassSnobalBase :: g_snow (double rho1, double rho2, double ts1, double ts2, double ds1, double ds2, double pa)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::g_snow(double rho1, double rho2, double ts1, double ts2, double ds1, double ds2, double pa)@@@ClassSnobalBase.cpp>");
    double kcs1;
    double kcs2;
    double k_s1;
    double k_s2;
    double g;
    if (ts1 == ts2)
    {
        g = 0.0;
    }

    else
    {
        kcs1 = KTS (rho1);
        kcs2 = KTS (rho2);
        k_s1 = efcon (kcs1, ts1, pa);
        k_s2 = efcon (kcs2, ts2, pa);
        g = ssxfr (k_s1, k_s2, ts1, ts2, ds1, ds2);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::g_snow(double rho1, double rho2, double ts1, double ts2, double ds1, double ds2, double pa)@@@ClassSnobalBase.cpp>");
    return (g);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::g_snow(double rho1, double rho2, double ts1, double ts2, double ds1, double ds2, double pa)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _advec (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_advec(void)@@@ClassSnobalBase.cpp>");
    if (precip_now)
    {
        M [hh] = (heat_stor (CP_WATER (T_rain [hh]), m_rain [hh], (T_rain [hh] - T_s_0 [hh])) + heat_stor (CP_ICE (T_snow [hh]), m_snow [hh], (T_snow [hh] - T_s_0 [hh]))) / time_step [hh];
    }

    else
    {
        M [hh] = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_advec(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _mass_bal (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_mass_bal(void)@@@ClassSnobalBase.cpp>");
    _time_compact ();
    _precip ();
    _snowmelt ();
    _evap_cond ();
    _h2o_compact ();
    _runoff ();
    if (snowcover [hh])
    {
        if (layer_count [hh] == 1)
        {
            T_s_0 [hh] = new_tsno (m_s_0 [hh], T_s_0 [hh], cc_s_0 [hh]);
            T_s [hh] = T_s_0 [hh];
        }

        else
        if (layer_count [hh] == 2)
        {
            if (isothermal [hh])
            {
                T_s [hh] = T_s_l [hh] = T_s_0 [hh] = FREEZE;
            }

            else
            {
                T_s_0 [hh] = new_tsno (m_s_0 [hh], T_s_0 [hh], cc_s_0 [hh]);
                T_s_l [hh] = new_tsno (m_s_l [hh], T_s_l [hh], cc_s_l [hh]);
                T_s [hh] = new_tsno (m_s [hh], T_s [hh], cc_s [hh]);
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_mass_bal(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _time_compact (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_time_compact(void)@@@ClassSnobalBase.cpp>");
    const double A = 350;
    const double B = 86400;
    double time;
    if (! snowcover [hh] || rho [hh] > A || m_s [hh] <= 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_time_compact(void)@@@ClassSnobalBase.cpp>");
        return;
    }

    if (rho [hh] > 349)
    {
        rho [hh] = 349;
    }

    time = B / (A / rho [hh] - 1);
    rho [hh] = A / (1 + B / (time + time_step [hh]));
    _new_density ();
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_time_compact(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _precip (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_precip(void)@@@ClassSnobalBase.cpp>");
    double h2o_vol_snow;
    if (precip_now [hh])
    {
        if (snowcover [hh])
        {
            _adj_snow (z_snow [hh], m_precip [hh]);
            h2o_vol_snow = h2o_sat_snow [hh] * max_h2o_vol [hh];
            h2o [hh] += H2O_LEFT (z_snow [hh], rho_snow [hh], h2o_vol_snow);
        }

        else
        {
            if (m_snow [hh] > 0.0)
            {
                z_s [hh] = z_snow [hh];
                rho [hh] = rho_snow [hh];
                T_s [hh] = T_snow [hh];
                T_s_0 [hh] = T_snow [hh];
                T_s_l [hh] = T_snow [hh];
                h2o_sat [hh] = h2o_sat_snow [hh];
                init_snow ();
            }

        }

        h2o_total [hh] += m_rain [hh];
    }

    else
    {
        h2o_total [hh] += h2o [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_precip(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _drift (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_drift(void)@@@ClassSnobalBase.cpp>");
    if (m_drift [hh] - m_subl [hh] == 0.0 || layer_count [hh] == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_drift(void)@@@ClassSnobalBase.cpp>");
        return;
    }

    else
    if (m_drift [hh] - m_subl [hh] > 0.0)
    {
        _adj_snow ((m_drift [hh] - m_subl [hh]) / rho [hh], m_drift [hh] - m_subl [hh]);
    }

    else
    {
        _adj_snow ((m_drift [hh] - m_subl [hh]) / rho [hh], m_drift [hh] - m_subl [hh]);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_drift(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _snowmelt (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_snowmelt(void)@@@ClassSnobalBase.cpp>");
    double Q_0;
    double Q_l;
    double Q_freeze;
    double Q_left;
    double h2o_refrozen;
    if (! snowcover [hh])
    {
        melt [hh] = 0.0;

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_snowmelt(void)@@@ClassSnobalBase.cpp>");
        return;
    }

    Q_0 = (delta_Q_0 [hh] * time_step [hh]) + cc_s_0 [hh];
    if (Q_0 > 0.0)
    {
        melt [hh] = MELT (Q_0);
        cc_s_0 [hh] = 0.0;
    }

    else
    if (Q_0 == 0.0)
    {
        melt [hh] = 0.0;
        cc_s_0 [hh] = 0.0;
    }

    else
    {
        melt [hh] = 0.0;
        cc_s_0 [hh] = Q_0;
        if (m_s [hh] < 2.0)
        {
            cc_s_0 [hh] = 0.0;
        }

    }

    if (layer_count [hh] == 2)
    {
        Q_l = ((G [hh] - G_0 [hh]) * time_step [hh]) + cc_s_l [hh];
        if (Q_l > 0.0)
        {
            melt [hh] += MELT (Q_l);
            cc_s_l [hh] = 0.0;
        }

        else
        if (Q_l == 0.0)
        {
            cc_s_l [hh] = 0.0;
        }

        else
        {
            cc_s_l [hh] = Q_l;
        }

    }

    else
    {
        Q_l = 0.0;
    }

    h2o_total [hh] += melt [hh];
    h2o_refrozen = 0.0;
    if (cc_s_0 [hh] < 0.0)
    {
        if (h2o_total [hh] > 0.0)
        {
            Q_freeze = h2o_total [hh] * (z_s_0 [hh] / z_s [hh]) * LH_FUS (FREEZE);
            Q_left = Q_0 + Q_freeze;
            if (Q_left <= 0.0)
            {
                h2o_refrozen = h2o_total [hh] * (z_s_0 [hh] / z_s [hh]);
                cc_s_0 [hh] = Q_left;
            }

            else
            {
                h2o_refrozen = (h2o_total [hh] * (z_s_0 [hh] / z_s [hh])) - MELT (Q_left);
                cc_s_0 [hh] = 0.0;
            }

        }

    }

    if ((layer_count [hh] == 2) && (cc_s_l [hh] < 0.0))
    {
        if (h2o_total [hh] > 0.0)
        {
            Q_freeze = h2o_total [hh] * (z_s_l [hh] / z_s [hh]) * LH_FUS (FREEZE);
            Q_left = Q_l + Q_freeze;
            if (Q_left <= 0.0)
            {
                h2o_refrozen += h2o_total [hh] * (z_s_l [hh] / z_s [hh]);
                cc_s_l [hh] = Q_left;
            }

            else
            {
                h2o_refrozen += ((h2o_total [hh] * (z_s_l [hh] / z_s [hh])) - MELT (Q_left));
                cc_s_l [hh] = 0.0;
            }

        }

    }

    if (fabs (h2o_total [hh] - h2o_refrozen) <= 1e-8)
    {
        h2o_total [hh] = 0.0;
    }

    else
    {
        h2o_total [hh] -= h2o_refrozen;
    }

    if ((layer_count [hh] == 2) && (cc_s_0 [hh] == 0.0) && (cc_s_l [hh] == 0.0))
    {
        isothermal [hh] = 1;
    }

    else
    if ((layer_count [hh] == 1) && (cc_s_0 [hh] == 0.0))
    {
        isothermal [hh] = 1;
    }

    else
    {
        isothermal [hh] = 0;
    }

    if (melt [hh] > 0.0)
    {
        if (rho [hh] <= 0.0)
        {
            rho [hh] = 750;
        }

        _adj_snow (- (melt [hh] / rho [hh]), 0.0);
    }

    if (layer_count [hh] == 2)
    {
        cc_s [hh] = cc_s_0 [hh] + cc_s_l [hh];
    }

    else
    {
        cc_s [hh] = cc_s_0 [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_snowmelt(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _new_density (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_new_density(void)@@@ClassSnobalBase.cpp>");
    z_s [hh] = m_s [hh] / rho [hh];
    _adj_layers ();
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_new_density(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _adj_snow (double delta_z_s, double delta_m_s)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_adj_snow(double delta_z_s, double delta_m_s)@@@ClassSnobalBase.cpp>");
    const double MAX_SNOW_DENSITY = 750;
    z_s [hh] += delta_z_s;
    m_s [hh] += delta_m_s;
    if (z_s [hh] > 0.0)
    {
        rho [hh] = m_s [hh] / z_s [hh];
    }

    else
    {
        z_s [hh] = 0.0;
        m_s [hh] = 0.0;
    }

    if (rho [hh] > MAX_SNOW_DENSITY)
    {
        rho [hh] = MAX_SNOW_DENSITY;
        z_s [hh] = m_s [hh] / rho [hh];
        _adj_layers ();
    }

    else
    {
        if (delta_z_s != 0.0)
        {
            _adj_layers ();
        }

        else
        {
            _layer_mass ();
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_adj_snow(double delta_z_s, double delta_m_s)@@@ClassSnobalBase.cpp>");
}
#define VAP_SUB (2.501 / 2.835)

void ClassSnobalBase :: _evap_cond (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_evap_cond(void)@@@ClassSnobalBase.cpp>");
    double E_l;
    double e_g;
    double e_s_l;
    double k;
    double prev_h2o_tot;
    double q_delta;
    double q_g;
    double q_s_l;
    double rho_air;
    double T_bar;
    if (! snowcover [hh])
    {
        E_s [hh] = 0.0;

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_evap_cond(void)@@@ClassSnobalBase.cpp>");
        return;
    }

    E_s_0 [hh] = E [hh] * time_step [hh];
    prev_h2o_tot = h2o_total [hh];
    if (h2o_total [hh] > 0.0)
    {
        h2o_total [hh] += (E_s_0 [hh] * VAP_SUB);
        if (h2o_total [hh] <= 0.0)
        {
            h2o_total [hh] = 0.0;
        }

    }

    if (layer_count [hh] == 0)
    {
        E_s_l [hh] = 0.0;
    }

    else
    {
        if (layer_count [hh] == 2)
        {
            e_s_l = sati (T_s_l [hh]);
            T_bar = (T_g [hh] + T_s_l [hh]) / 2.0;
        }

        else
        {
            e_s_l = sati (T_s_0 [hh]);
            T_bar = (T_g [hh] + T_s_0 [hh]) / 2.0;
        }

        q_s_l = SPEC_HUM (e_s_l, P_a [hh]);
        e_g = sati (T_g [hh]);
        q_g = SPEC_HUM (e_g, P_a [hh]);
        q_delta = q_g - q_s_l;
        rho_air = GAS_DEN (P_a [hh], MOL_AIR, T_bar);
        k = DIFFUS (P_a [hh], T_bar);
        E_l = EVAP (rho_air, k, q_delta, z_g [hh]);
        E_s_l [hh] = E_l * time_step [hh];
        if (h2o_total [hh] > 0.0)
        {
            h2o_total [hh] += (E_s_l [hh] * VAP_SUB);
            if (h2o_total [hh] <= 0.0)
            {
                h2o_total [hh] = 0.0;
            }

        }

    }

    E_s [hh] = E_s_0 [hh] + E_s_l [hh];
    if (layer_count [hh] > 0)
    {
        _adj_snow (((E_s [hh] + (prev_h2o_tot - h2o_total [hh])) / rho [hh]) / 2.0, E_s [hh]);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_evap_cond(void)@@@ClassSnobalBase.cpp>");
}
#define MAX_DENSITY 550
#define BB 0.4

void ClassSnobalBase :: _h2o_compact (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_h2o_compact(void)@@@ClassSnobalBase.cpp>");
    double Alocal;
    double h2o_added;
    if ((! snowcover [hh]) || (rho [hh] > MAX_DENSITY))
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_h2o_compact(void)@@@ClassSnobalBase.cpp>");
        return;
    }

    Alocal = MAX_DENSITY - rho [hh];
    if (m_s [hh])
    {
        if (precip_now [hh])
        {
            h2o_added = (melt [hh] + m_rain [hh]) / m_s [hh];
        }

        else
        {
            h2o_added = melt [hh] / m_s [hh];
        }

        if (h2o_added > 0.000001)
        {
            rho [hh] += Alocal / (1 + BB / h2o_added);
            _new_density ();
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_h2o_compact(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _adj_layers (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_adj_layers(void)@@@ClassSnobalBase.cpp>");
    int prev_layer_count;
    prev_layer_count = layer_count [hh];
    _calc_layers ();
    if (layer_count [hh] == 0)
    {
        rho [hh] = 218.0;
        if (m_s [hh] > 0.0)
        {
            snowmelt_int [hh] += m_s [hh];
            melt_direct_int [hh] += m_s [hh];
        }

        m_s [hh] = cc_s [hh] = 0.0;
        m_s_0 [hh] = cc_s_0 [hh] = 0.0;
        T_s [hh] = T_s_0 [hh] = MIN_SNOW_TEMP + FREEZE;
        if (prev_layer_count == 2)
        {
            m_s_l [hh] = cc_s_l [hh] = 0.0;
            T_s_l [hh] = MIN_SNOW_TEMP + FREEZE;
        }

        h2o_vol [hh] = h2o [hh] = h2o_max [hh] = h2o_sat [hh] = 0.0;
    }

    else
    {
        _layer_mass ();
        if ((prev_layer_count == 1) && (layer_count [hh] == 2))
        {
            T_s_l [hh] = T_s [hh];
            cc_s_l [hh] = _cold_content (T_s_l [hh], m_s_l [hh]);
        }

        else
        if ((prev_layer_count == 2) && (layer_count [hh] == 1))
        {
            T_s_l [hh] = MIN_SNOW_TEMP + FREEZE;
            cc_s_l [hh] = 0.0;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_adj_layers(void)@@@ClassSnobalBase.cpp>");
}
void ClassSnobalBase :: _runoff (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::_runoff(void)@@@ClassSnobalBase.cpp>");
    double m_s_dry;
    double rho_dry;
    if ((! snowcover [hh]) || (layer_count [hh] == 0))
    {
        ro_predict [hh] = h2o_total [hh];

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_runoff(void)@@@ClassSnobalBase.cpp>");
        return;
    }

    m_s_dry = m_s [hh] - h2o_total [hh];
    rho_dry = m_s_dry / z_s [hh];
    h2o_max [hh] = H2O_LEFT (z_s [hh], rho_dry, max_h2o_vol [hh]);
    if (h2o_total [hh] > h2o_max [hh])
    {
        ro_predict [hh] = h2o_total [hh] - h2o_max [hh];
        h2o [hh] = h2o_max [hh];
        h2o_sat [hh] = 1.0;
        h2o_vol [hh] = max_h2o_vol [hh];
        _adj_snow (0.0, - ro_predict [hh]);
    }

    else
    {
        ro_predict [hh] = 0.0;
        h2o [hh] = h2o_total [hh];
        h2o_sat [hh] = h2o [hh] / h2o_max [hh];
        h2o_vol [hh] = h2o_sat [hh] * max_h2o_vol [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::_runoff(void)@@@ClassSnobalBase.cpp>");
}
double satw (double tk)
{
InstrumentLogger::instance()->log_instrument_log("<satw(double tk)@@@ClassSnobalBase.cpp>");
    double x;
    double l10;
    if (tk <= 0.)
    {
        CRHMException TExcept ("satw temperature <= 0.0", TExcept :: TERMINATE);
        LogError (TExcept);
    }

    errno = 0;
    l10 = log (1.e1);
    x = - 7.90298 * (BOIL / tk - 1.0f) + 5.02808f * log (BOIL / tk) / l10 - 1.3816e-7 * (pow (1.0e1, 1.1344e1f * (1.0 - tk / BOIL)) - 1.0f) + 8.1328e-3 * (pow (1.0e1, - 3.49149f * (BOIL / tk - 1.0f)) - 1.0f) + log (SEA_LEVEL) / l10;
    x = pow (1.0e1f, x);
    if (errno)
    {
        CRHMException TExcept ("satw: bad return from log or pow", TExcept :: TERMINATE);
        LogError (TExcept);
    }

InstrumentLogger::instance()->log_instrument_log("</satw(double tk)@@@ClassSnobalBase.cpp>");
    return (x);
InstrumentLogger::instance()->log_instrument_log("</satw(double tk)@@@ClassSnobalBase.cpp>");
}
static double psi (double zeta, int code)
{
InstrumentLogger::instance()->log_instrument_log("<psi(double zeta, int code)@@@ClassSnobalBase.cpp>");
    double x;
    double result {};
    if (zeta > 0)
    {
        if (zeta > 1)
        {
            zeta = 1;
        }

        result = - BETA_S * zeta;
    }

    else
    if (zeta < 0)
    {
        x = sqrt (sqrt (1.0 - BETA_U * zeta));
        switch (code) {
        case SM:
            result = 2.0 * log ((1.0 + x) / 2.0) + log ((1.0 + x * x) / 2.0) - 2.0 * atan (x) + M_PI_2;
            break;
        case SH:
        case SV:
            result = 2.0 * log ((1.0 + x * x) / 2.0);
            break;
        default:
            CRHMException TExcept ("psi-function code not of these: SM, SH, SV", TExcept :: TERMINATE);
            LogError (TExcept);
        }
    }

    else
    {
        result = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</psi(double zeta, int code)@@@ClassSnobalBase.cpp>");
    return (result);
InstrumentLogger::instance()->log_instrument_log("</psi(double zeta, int code)@@@ClassSnobalBase.cpp>");
}
double ClassSnobalBase :: sati (double tk)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::sati(double tk)@@@ClassSnobalBase.cpp>");
    double l10;
    double x;
    if (tk <= 0.0)
    {
        CRHMException TExcept ("sati temperature <= 0.0", TExcept :: TERMINATE);
        LogError (TExcept);
    }

    if (tk > FREEZE)
    {
        x = satw (tk);

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::sati(double tk)@@@ClassSnobalBase.cpp>");
        return (x);
    }

    errno = 0;
    l10 = log (1.e1);
    x = pow (1.e1, - 9.09718 * ((FREEZE / tk) - 1.0) - 3.56654 * log (FREEZE / tk) / l10 + 8.76793e-1 * (1.0 - (tk / FREEZE)) + log (6.1071) / l10);
    if (errno)
    {
        CRHMException TExcept ("sati: bad return from log or pow", TExcept :: TERMINATE);
        LogError (TExcept);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::sati(double tk)@@@ClassSnobalBase.cpp>");
    return (x * 1.e2);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::sati(double tk)@@@ClassSnobalBase.cpp>");
}
double ClassSnobalBase :: ssxfr (double k1, double k2, double t1, double t2, double d1, double d2)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::ssxfr(double k1, double k2, double t1, double t2, double d1, double d2)@@@ClassSnobalBase.cpp>");
    double xfr;
    xfr = 2.0 * (k1 * k2 * (t2 - t1)) / ((k2 * d1) + (k1 * d2));

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::ssxfr(double k1, double k2, double t1, double t2, double d1, double d2)@@@ClassSnobalBase.cpp>");
    return (xfr);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::ssxfr(double k1, double k2, double t1, double t2, double d1, double d2)@@@ClassSnobalBase.cpp>");
}
double ClassSnobalBase :: heat_stor (double cp, double spm, double tdif)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::heat_stor(double cp, double spm, double tdif)@@@ClassSnobalBase.cpp>");
    double stor;
    stor = cp * spm * tdif;

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::heat_stor(double cp, double spm, double tdif)@@@ClassSnobalBase.cpp>");
    return (stor);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::heat_stor(double cp, double spm, double tdif)@@@ClassSnobalBase.cpp>");
}
double ClassSnobalBase :: new_tsno (double spm, double t0, double ccon)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::new_tsno(double spm, double t0, double ccon)@@@ClassSnobalBase.cpp>");
    double tsno;
    double cp;
    double tdif;
    cp = CP_ICE (t0);
    tdif = ccon / (spm * cp);
    tsno = tdif + FREEZE;
    if (tsno < MIN_SNOW_TEMP + FREEZE)
    {
        tsno = MIN_SNOW_TEMP + FREEZE;
    }

    else
    {
        if (tsno > CRHM_constants :: Tm)
        {
            tsno = CRHM_constants :: Tm;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::new_tsno(double spm, double t0, double ccon)@@@ClassSnobalBase.cpp>");
    return (tsno);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::new_tsno(double spm, double t0, double ccon)@@@ClassSnobalBase.cpp>");
}
double ClassSnobalBase :: efcon (double k, double t, double p)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::efcon(double k, double t, double p)@@@ClassSnobalBase.cpp>");
    double etc;
    double de;
    double lh;
    double e;
    double q;
    de = DIFFUS (p, t);
    if (t > FREEZE)
    {
        lh = LH_VAP (t);
    }

    else
    if (t == FREEZE)
    {
        lh = (LH_VAP (t) + LH_SUB (t)) / 2.0;
    }

    else
    {
        lh = LH_SUB (t);
    }

    e = sati (t);
    q = MIX_RATIO (e, p);
    etc = k + (lh * de * q);

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::efcon(double k, double t, double p)@@@ClassSnobalBase.cpp>");
    return (etc);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::efcon(double k, double t, double p)@@@ClassSnobalBase.cpp>");
}
int ClassSnobalBase :: hle1 (double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu, double z0, double & CRHM_h, double & CRHM_le, double & CRHM_e)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSnobalBase::hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu, double z0, double & CRHM_h, double & CRHM_le, double & CRHM_e)@@@ClassSnobalBase.cpp>");
    double h = 0;
    double e = 0;
    double ah = AH;
    double av = AV;
    double cp = CP_AIR;
    double d0;
    double dens;
    double diff;
    double factor;
    double g = GRAVITY;
    double k = VON_KARMAN;
    double last;
    double lo;
    double ltsh;
    double ltsm;
    double ltsv;
    double qa;
    double qs;
    double ustar;
    double xlh = 0;
    int ier = 0;
    int iter = 0;
    static TDateTime LastDTnow;
    if (z0 <= 0 || zq <= z0 || zu <= z0 || za <= z0)
    {
        string D = StandardConverterUtility :: GetDateTimeInString (Global :: DTnow) + "hle1: height not positive ";
        string SS = D + "hru " + to_string (hh + 1);
        SS = SS + "  ta: " + FloatToStrF (ta - CRHM_constants :: Tm, TFloatFormat :: ffFixed, 10, 4) + ", z0: " + FloatToStrF (z0, TFloatFormat :: ffFixed, 10, 4) + ", zq: " + FloatToStrF (zq, TFloatFormat :: ffFixed, 10, 4) + ", zu: " + FloatToStrF (zu, TFloatFormat :: ffFixed, 10, 4) + ", za: " + FloatToStrF (za, TFloatFormat :: ffFixed, 10, 4);
        CRHMException TExcept (SS.c_str (), TExcept :: WARNING);
        LogError (TExcept);
        ier = - 2;

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu, double z0, double & CRHM_h, double & CRHM_le, double & CRHM_e)@@@ClassSnobalBase.cpp>");
        return (ier);
    }

    if (ta <= 0 || ts <= 0)
    {
        CRHMException TExcept ("temps not K", TExcept :: TERMINATE);
        LogError (TExcept);
        ier = - 2;

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu, double z0, double & CRHM_h, double & CRHM_le, double & CRHM_e)@@@ClassSnobalBase.cpp>");
        return (ier);
    }

    if (ea <= 0 || es <= 0 || press <= 0 || ea >= press || es >= press)
    {
        string D = StandardConverterUtility :: GetDateTimeInString (Global :: DTnow);
        string SS = D + "hh " + to_string (hh) + " 'hle1' " + ". H: " + FloatToStrF (h, TFloatFormat :: ffFixed, 10, 4) + " le: " + FloatToStrF (xlh * e, TFloatFormat :: ffFixed, 10, 4);
        SS = SS + " ta: " + FloatToStrF (ta - CRHM_constants :: Tm, TFloatFormat :: ffFixed, 10, 4) + ", ts: " + FloatToStrF (ts - CRHM_constants :: Tm, TFloatFormat :: ffFixed, 10, 4) + ", ea: " + FloatToStrF (ea, TFloatFormat :: ffFixed, 10, 4) + ", es: " + FloatToStrF (es, TFloatFormat :: ffFixed, 10, 4) + ", u:  " + FloatToStrF (u, TFloatFormat :: ffFixed, 10, 4) + ", m_s:  " + FloatToStrF (m_s [hh], TFloatFormat :: ffFixed, 10, 4);
        CRHM_le = 0.0;
        CRHM_h = 0.0;
        CRHM_e = 0.0;
        CRHMException TExcept2 (SS.c_str (), TExcept :: WARNING);
        LogError (TExcept2);
        CRHMException TExcept ("hle1: pressures must be positive", TExcept :: WARNING);
        LogError (TExcept);
        ier = - 2;

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu, double z0, double & CRHM_h, double & CRHM_le, double & CRHM_e)@@@ClassSnobalBase.cpp>");
        return (ier);
    }

    if ((es - 25.0) > sati (ts) || (ea - 25.0) > satw (ta))
    {
        CRHMException TExcept ("hle1: vapor pressures can't exceed saturation", TExcept :: TERMINATE);
        LogError (TExcept);
        ier = - 2;

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu, double z0, double & CRHM_h, double & CRHM_le, double & CRHM_e)@@@ClassSnobalBase.cpp>");
        return (ier);
    }

    if (es > sati (ts))
    {
        es = sati (ts);
    }

    if (ea > satw (ta))
    {
        ea = satw (ta);
    }

    if (u < 0.5)
    {
        u = 0.5;
    }

    else
    if (u > 15)
    {
        u = 15;
    }

    d0 = 2.0 * PAESCHKE * z0 / 3.0;
    ltsm = log ((zu - d0) / z0);
    ltsh = log ((za - d0) / z0);
    ltsv = log ((zq - d0) / z0);
    qa = SPEC_HUM (ea, press);
    qs = SPEC_HUM (es, press);
    ta += DALR * za;
    dens = GAS_DEN (press, MOL_AIR, VIR_TEMP (sqrt (ta * ts), sqrt (ea * es), press));
    ustar = k * u / ltsm;
    factor = k * ustar * dens;
    e = (qa - qs) * factor * av / ltsv;
    h = (ta - ts) * factor * cp * ah / ltsh;
    if (ta != ts)
    {
        lo = HUGE_VAL;
        do {
            last = lo;
            lo = ustar * ustar * ustar * dens / (k * g * (h / (ta * cp) + 0.61 * e));
            ustar = k * u / (ltsm - psi (zu / lo, SM));
            factor = k * ustar * dens;
            e = (qa - qs) * factor * av / (ltsv - psi (zq / lo, SV));
            h = (ta - ts) * factor * ah * cp / (ltsh - psi (za / lo, SH));
            diff = last - lo;
        }
        while (fabs (diff) > THRESH && fabs (diff / lo) > THRESH && ++ iter < ITMAX);
    }

    xlh = LH_VAP (ts);
    if (ts <= FREEZE)
    {
        xlh += LH_FUS (ts);
    }

    CRHM_le = xlh * e;
    CRHM_h = h;
    CRHM_e = e;
    if (iter >= ITMAX)
    {
        CRHM_le = 0.0;
        CRHM_h = 0.0;
        CRHM_e = 0.0;
        string Flag = "iters" + to_string (iter);
        LastDTnow = Global :: DTnow;
        string D = StandardConverterUtility :: GetDateTimeInString (Global :: DTnow);
        string SS = D + "hh " + to_string (hh) + " 'hle1' " + Flag + ". H: " + FloatToStrF (h, TFloatFormat :: ffFixed, 10, 4) + " le: " + FloatToStrF (xlh * e, TFloatFormat :: ffFixed, 10, 4);
        SS = SS + " ta: " + FloatToStrF (ta - CRHM_constants :: Tm, TFloatFormat :: ffFixed, 10, 4) + ", ts: " + FloatToStrF (ts - CRHM_constants :: Tm, TFloatFormat :: ffFixed, 10, 4) + ", ea: " + FloatToStrF (ea, TFloatFormat :: ffFixed, 10, 4) + ", es: " + FloatToStrF (es, TFloatFormat :: ffFixed, 10, 4) + ", u:  " + FloatToStrF (u, TFloatFormat :: ffFixed, 10, 4) + ", m_s:  " + FloatToStrF (m_s [hh], TFloatFormat :: ffFixed, 10, 4);
        CRHMException TExcept2 (SS.c_str (), TExcept :: WARNING);
        LogError (TExcept2);
        ier = - 1;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu, double z0, double & CRHM_h, double & CRHM_le, double & CRHM_e)@@@ClassSnobalBase.cpp>");
    return (ier);
InstrumentLogger::instance()->log_instrument_log("</ClassSnobalBase::hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu, double z0, double & CRHM_h, double & CRHM_le, double & CRHM_e)@@@ClassSnobalBase.cpp>");
}