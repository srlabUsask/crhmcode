/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassCanSnobalBase.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

void ClassCanSnobalBase::init(void) {

    input_rec1 = new INPUT_REC[nhru]; // input data for start of data timestep [nhru]
    input_rec2 = new INPUT_REC[nhru]; // input data for start of data timestep [nhru]
    time_step = new long[nhru];	     // length current timestep (sec)
    current_time = new long[nhru];    // start time of current time step (sec)

    computed = new int* [nhru];		// array of flags for each timestep;
    input_deltas = new INPUT_REC * [nhru]; // deltas for climate-input parameters for each timestep
    precip_info = new PRECIP_REC * [nhru]; // array of precip info adjusted for each timestep
    tstep_info = new TSTEP_REC * [nhru]; 	// array of info for each timestep:

    for (long ii = 0; ii < nhru; ++ii) {
        computed[ii] = new int[4];           // [nhru] [4]
        input_deltas[ii] = new INPUT_REC[4]; // [nhru] [4]
        precip_info[ii] = new PRECIP_REC[4]; // [nhru] [4]
        tstep_info[ii] = new TSTEP_REC[4];   // [nhru] [4]
    }

    for (hh = 0; chkStruct(); ++hh) {
        P_a[hh] = 101.3f * pow((293.0f - 0.0065f * hru_elev[hh]) / 293.0f, 5.26f) * 1000.0f;  // Pa

        T_s_veg[hh] = 0.0; // temperatures inside CanSnobal model are K

        rho_veg[hh] = 218.0; // change 10/18/16
        h2o_sat_veg[hh] = 0.0;


        snow_h2o_veg[hh] = 0.0;
        liq_h2o_veg[hh] = 0.0;
        m_s_veg[hh] = snow_h2o_veg[hh] + liq_h2o_veg[hh];

        cc_s_veg[hh] = 0.0;

        liq_h2o_veg[hh] = 0.0;
        delmelt_veg[hh] = 0.0;
        deldrip_veg[hh] = 0.0;
        T_sf[hh] = 0.0;
        T_rain_veg[hh] = 0.0;

        isothermal[hh] = 0;
        vegsnowcover[hh] = 0;
        stop_no_snow[hh] = 0;
        if (hh < nhru)
        {
            current_time[hh] = 0;
        }


        melt_direct_cum[hh] = 0.0;
        E_s_cum[hh] = 0.0;

        m_precip_cum[hh] = 0.0;
        m_rain_cum[hh] = 0.0;
        m_snow_cum[hh] = 0.0;
        cmlmelt_veg[hh] = 0.0;

        Ql_veg[hh] = 0.0;
        qsub_veg[hh] = 0.0;
        Qh_veg[hh] = 0.0;
        Qp[hh] = 0.0;
        Qn_veg[hh] = 0.0;
        delta_Q_veg[hh] = 0.0;

        if (hh < nhru)
        {
            tstep_info[hh][DATA_TSTEP].level = DATA_TSTEP;
            tstep_info[hh][DATA_TSTEP].time_step = 24 * 3600 / Global::Freq;
            tstep_info[hh][DATA_TSTEP].intervals = 0;
            tstep_info[hh][DATA_TSTEP].threshold = DEFAULT_NORMAL_THRESHOLD;

            tstep_info[hh][NORMAL_TSTEP].level = NORMAL_TSTEP;
            tstep_info[hh][NORMAL_TSTEP].time_step = 24 * 3600 / Global::Freq;
            tstep_info[hh][NORMAL_TSTEP].intervals = 1;
            tstep_info[hh][NORMAL_TSTEP].threshold = DEFAULT_NORMAL_THRESHOLD; // 60

            tstep_info[hh][MEDIUM_TSTEP].level = MEDIUM_TSTEP;
            tstep_info[hh][MEDIUM_TSTEP].time_step = 24 * 3600 / Global::Freq / 4;
            tstep_info[hh][MEDIUM_TSTEP].intervals = 4;
            tstep_info[hh][MEDIUM_TSTEP].threshold = DEFAULT_MEDIUM_THRESHOLD; // 10

            tstep_info[hh][SMALL_TSTEP].level = SMALL_TSTEP;
            tstep_info[hh][SMALL_TSTEP].time_step = 24 * 3600 / Global::Freq / 60;
            tstep_info[hh][SMALL_TSTEP].intervals = 15;
            tstep_info[hh][SMALL_TSTEP].threshold = DEFAULT_SMALL_THRESHOLD;  // 1
        }

    }
}

void ClassCanSnobalBase::finish(bool good) { // only required for local storage and final output

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (CanSnobal)' m_precip_cum    (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_precip_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (CanSnobal)' m_rain_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_rain_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (CanSnobal)' m_snow_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_snow_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (CanSnobal)' SWE             (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_s_veg[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
        LogMessageA(hh, string("'" + Name + " (CanSnobal)' E_s_cum         (mm) (mm*hru) (mm*hru/basin): ").c_str(), E_s_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (CanSnobal)' cmlmelt_veg     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cmlmelt_veg[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (CanSnobal)' melt_direct_cum (mm) (mm*hru) (mm*hru/basin): ").c_str(), melt_direct_cum[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
    }

    delete[] input_rec1;   // [nhru]
    delete[] input_rec2;   // [nhru]
    delete[] time_step;    // [nhru]
    delete[] current_time; // [nhru]

    for (long ii = 0; ii < nhru; ++ii) {
        delete[] computed[ii];         // [nhru] [4]
        delete[] input_deltas[ii];     // [nhru] [4]
        delete[] precip_info[ii];      // [nhru] [4]
        delete[] tstep_info[ii];       // [nhru] [4]
    }

    delete[] computed;
    delete[] input_deltas;
    delete[] precip_info;
    delete[] tstep_info;
}

// Initialize canopy snowpack on this timestep, i.e., no snow load on timestep start
void ClassCanSnobalBase::init_snow_veg(void)
{
    
    liq_h2o_veg[hh] += m_rain[hh];
    snow_h2o_veg[hh] += m_snow[hh];
    m_s_veg[hh] = liq_h2o_veg[hh] + snow_h2o_veg[hh];

    T_s_veg[hh] = T_sf[hh]; // init canopy snow temperature at precip temp

    cc_s_veg[hh] = _cold_content_veg(T_s_veg[hh], m_s_veg[hh]);

    stop_no_snow[hh] = 0;
    vegsnowcover[hh] = 1;
}

/*
** NAME
**      _cold_content_veg -- calculates cold content for a layer
**
**      double
**	_cold_content_veg(
**	    double  temp,		|* temperature of layer *|
**	    double  mass)		|* specific mass of layer *|
**
** DESCRIPTION
**      This routine calculates the cold content for a layer (i.e., the
**	energy required to bring its temperature to freezing) from the
**	layer's temperature and specific mass.
**
** RETURN VALUE
**	The layer's cold content.
*/

double ClassCanSnobalBase::_cold_content_veg(
    double	temp,		// temperature of layer
    double	mass)		// specific mass of layer
{
    if (temp < FREEZE)
        return heat_stor(CP_ICE(temp), mass, (temp - FREEZE));
    else
        return 0.0;
}

/*
** NAME
**      int do_data_tstep_veg(void) -- run model for 1 data timestep between 2 input records
**
** DESCRIPTION
**	This routine performs the model's calculations for 1 data timestep
**	between 2 input-data records which are in 'input_rec1' and
**	'input_rec2'.
**
**	If there's precipitation during the data timestep, the flag
**	'precip_now_veg' used be true.  Furthermore, the routine requires
**	that the following precipitation variables have been initialized:
**
**		m_pp
**		percent_snow
**		rho_snow
**		T_pp
**
**	This routine divides the data timestep into the appropriate number
**	of normal run timesteps.  The input values for each normal timestep
**	are computed from the two input records by linear interpolation.
**
** RETURN VALUE
**
**	true	The model's calculations were completed.
**
**	false	An error occured, and a message explaining the error has
**		been stored with the 'usrerr' routine.
**
** GLOBAL VARIABLES READ
**	e_a
**	I_lw
**	in_rec
**	m_pp_data
**	m_rain_data
**	m_snow_data
**	more_pr_recs
**	precip_data
**	S_n
**	T_a
**	tstep_info
**	u
**	z_snow_data
**
** GLOBAL VARIABLES MODIFIED
**	precip_now_veg
*/

void ClassCanSnobalBase::do_data_tstep_veg(void) {

    int level; // loop index

  //  Copy values from first input record into global variables.

    S_n[hh] = input_rec1[hh].S_n;
    I_lw[hh] = input_rec1[hh].I_lw;
    T_a[hh] = input_rec1[hh].T_a;
    e_a[hh] = input_rec1[hh].e_a;
    u[hh] = input_rec1[hh].u;

    // Compute deltas for the climate input parameters over the CRHM data timestep.

    input_deltas[hh][DATA_TSTEP].S_n = input_rec2[hh].S_n - input_rec1[hh].S_n;
    input_deltas[hh][DATA_TSTEP].I_lw = input_rec2[hh].I_lw - input_rec1[hh].I_lw;
    input_deltas[hh][DATA_TSTEP].T_a = input_rec2[hh].T_a - input_rec1[hh].T_a;
    input_deltas[hh][DATA_TSTEP].e_a = input_rec2[hh].e_a - input_rec1[hh].e_a;
    input_deltas[hh][DATA_TSTEP].u = input_rec2[hh].u - input_rec1[hh].u;
    input_deltas[hh][DATA_TSTEP].F_g = input_rec2[hh].F_g - input_rec1[hh].F_g;

    // If there is precipitation, then compute the amount of rain & snow in it.

    if (precip_now_veg[hh]) {
        precip_info[hh]->m_pp = m_precip[hh];
        precip_info[hh]->m_snow = m_snow[hh];
        precip_info[hh]->m_rain = m_rain[hh];

        // Mixed snow and rain

        if ((precip_info[hh]->m_snow > 0.0) && (precip_info[hh]->m_rain > 0.0)) {
            T_sf[hh] = FREEZE;
            h2o_sat_veg_snow[hh] = 1.0;
            T_rain_veg[hh] = T_pp[hh]; // TODO try changing to harder ice bulb temp
        }

        // Snow only

        else if (precip_info[hh]->m_snow > 0.0) {
            if (T_pp[hh] < FREEZE) {	/* Cold snow */
                T_sf[hh] = T_pp[hh];
                h2o_sat_veg_snow[hh] = 0.0;
            }
            else {				/* Warm snow */
                T_sf[hh] = FREEZE;
                h2o_sat_veg_snow[hh] = 1.0;
            }
        }

        // Rain only

        else if (precip_info[hh]->m_rain > 0.0) {
            T_rain_veg[hh] = T_pp[hh];
        }
    }
    else {
        precip_info[hh]->m_pp = 0.0;
        precip_info[hh]->m_snow = 0.0;
        precip_info[hh]->m_rain = 0.0;
        precip_info[hh]->z_snow = 0.0;
    }

    //  Clear the 'computed' flag at the other timestep levels.

    for (level = NORMAL_TSTEP; level <= SMALL_TSTEP; ++level)
        computed[hh][level] = 0;

    // Divide the data timestep into normal run timesteps.

    _divide_tstep_veg(tstep_info[hh]);
}

/*
** NAME
**      int _divide_tstep_veg( -- divide a timestep into smaller timesteps
**
**	int
**	_divide_tstep_veg(
**	    TSTEP_REC *tstep;	|* record of timestep to be divided *|
**
** DESCRIPTION
**	This routine divides a timestep into smaller timesteps.  For
**	each of these smaller timestep, the routine either run the
**	model for that timestep, or further subdivides that timestep
**	into even smaller timesteps.
**
** RETURN VALUE
**
**	true	The timestep was successfully divided into smaller timesteps.
**
**	false	An error occured while running the model during one of the
**		smaller timesteps.  An message explaining the error has
**		been stored with the 'usrerr' routine.
**
** GLOBAL VARIABLES READ
**	precip_now_veg
**	tstep_info
**
** GLOBAL VARIABLES MODIFIED
*/

int ClassCanSnobalBase::_divide_tstep_veg(TSTEP_REC* tstep) {  // record of timestep to be divided

    TSTEP_REC* next_lvl_tstep;	// info of next level of timestep
    INPUT_REC* curr_lvl_deltas;	// -> input-deltas of current level
    INPUT_REC* next_lvl_deltas;	// -> input-deltas of next level
    PRECIP_REC* curr_lvl_precip;	// -> precip data of current level
    PRECIP_REC* next_lvl_precip;	// -> precip data of next level
    int next_level;
    // Fetch the record for the timestep at the next level.

    next_level = tstep->level + 1;
    next_lvl_tstep = &tstep_info[hh][next_level];

    curr_lvl_deltas = &input_deltas[hh][tstep->level];
    next_lvl_deltas = &input_deltas[hh][next_level];

    curr_lvl_precip = &precip_info[hh][tstep->level];
    next_lvl_precip = &precip_info[hh][next_level];

    //  If this is the first time this new level has been used during
    //  the current data timestep, then calculate its input deltas and precipitation values.

    if (!computed[hh][next_level]) {
        next_lvl_deltas->S_n = curr_lvl_deltas->S_n / next_lvl_tstep->intervals;
        next_lvl_deltas->I_lw = curr_lvl_deltas->I_lw / next_lvl_tstep->intervals;
        next_lvl_deltas->T_a = curr_lvl_deltas->T_a / next_lvl_tstep->intervals;
        next_lvl_deltas->e_a = curr_lvl_deltas->e_a / next_lvl_tstep->intervals;
        next_lvl_deltas->u = curr_lvl_deltas->u / next_lvl_tstep->intervals;

        next_lvl_precip->m_pp = curr_lvl_precip->m_pp / next_lvl_tstep->intervals;
        next_lvl_precip->m_rain = curr_lvl_precip->m_rain / next_lvl_tstep->intervals;
        next_lvl_precip->m_snow = curr_lvl_precip->m_snow / next_lvl_tstep->intervals;
        next_lvl_precip->z_snow = curr_lvl_precip->z_snow / next_lvl_tstep->intervals;

        computed[hh][next_level] = 1;
    }

    // For each the new smaller timestep, either subdivide them if below their mass threshold, or run the model for them.

    for (int ii = 0; (ii < next_lvl_tstep->intervals) && !stop_no_snow[hh]; ++ii) { // execute every interval

        if ((next_level < SMALL_TSTEP) && _below_thold_veg(next_lvl_tstep->threshold)) {
            if (!_divide_tstep_veg(next_lvl_tstep)) // call self (this routine)
                return 0; // cannot get here unless _hl_e is coded to return error!
        }
        else {
            if (!_do_tstep_veg(next_lvl_tstep)) // execute code
                return 0; // cannot get here unless _hl_e is coded to return error!
        }
    } // for

    return 1;
} // _divide_tstep_veg

/*
** NAME
**      _below_thold_veg -- is a layer's mass below a threshold ?
**
**      int
**	_below_thold_veg(
**	    double  threshold)	|* current timestep's threshold for a
**				   layer's mass *|
**
** DESCRIPTION
**      This routine determines if any individual layer's mass is below
**	a given threshold for the current timestep.
**
** RETURN VALUE
**      	1	A layer's mass is less than the threshold.
**
**		0	All layers' masses are greater than the threshold.
**
** GLOBAL VARIABLES READ
**	m_s_veg
**	m_s_veg
**
** GLOBAL VARIABLES MODIFIED
*/

int ClassCanSnobalBase::_below_thold_veg(double	threshold) { // current timestep's threshold for a layer's mass

    if (vegsnowcover[hh] == 0)
        return 0;
    else
        return (m_s_veg[hh] < threshold);
}

/*
** NAME
**      _do_tstep_veg -- do model calculations for 1 timestep
**
**      int
**	_do_tstep_veg(
**	    TSTEP_REC *tstep;  |* timestep's record *|
**
** DESCRIPTION
**      This routine performs the model's calculations for a single timestep.
**      It requires that these climate variables have been initialized:
**
**      	S_n
**      	I_lw
**      	T_a
**      	e_a
**      	u
**
**	The routine also requires the precipitation data have been adjusted
**	for the timestep, and have been stored in the array:
**
**		precip_info
**
** RETURN VALUE
**
**	true	The model's calculations were completed.
**
**	false	An error occured, and a message explaining the error has
**		been stored with the 'usrerr' routine.
**
** GLOBAL VARIABLES READ
**	delta_Q_veg
**	delsub_veg
**	G
**	Qh_veg
**	Ql_veg
**	Qp
**	delmelt_veg
**	precip_now_veg
**	Qn_veg
**	deldrip_veg
**
** GLOBAL VARIABLES MODIFIED
**	current_time
**	curr_time_hrs
**	delta_Q_bar
**	e_a
**	G_bar
**	H_bar
**	liq_h2o_veg
**	I_lw
**	L_v_E_bar
**	M_bar
**	m_precip
**	m_rain

**	m_snow
**	R_n_bar
**	S_n
**	vegsnowcover
**	T_a
**	u
**	time_step
**	z_snow_veg
*/

int ClassCanSnobalBase::_do_tstep_veg(TSTEP_REC* tstep)  // timestep's record
{
    time_step[hh] = tstep->time_step;

    m_precip[hh] = precip_info[hh][tstep->level].m_pp;
    m_rain[hh] = precip_info[hh][tstep->level].m_rain;
    m_snow[hh] = precip_info[hh][tstep->level].m_snow;

    liq_h2o_veg[hh] = 0.0;
    delmelt_veg[hh] = 0.0;

    // Is there a vegsnowcover?

    vegsnowcover[hh] = (m_s_veg[hh] > 0.0);

    // Calculate energy transfer terms

    if (!_e_bal_veg())
        return 0;

    // Adjust mass and calculate runoff

    _mass_bal();

    //  Update the averages for the energy terms and the totals for mass changes since the last output.

    // increment time
    current_time[hh] += time_step[hh];

    //  update interval values

    delmelt_veg_int[hh] += deldrip_veg[hh];
    delsub_veg_int[hh] += delsub_veg[hh];
    delunld_int[hh] += delunld[hh];

    //  Update the model's input parameters

    S_n[hh] += input_deltas[hh][tstep->level].S_n;
    I_lw[hh] += input_deltas[hh][tstep->level].I_lw;
    T_a[hh] += input_deltas[hh][tstep->level].T_a;
    e_a[hh] += input_deltas[hh][tstep->level].e_a;
    u[hh] += input_deltas[hh][tstep->level].u;

    return 1;
}

/*
** NAME
**      int _e_bal_veg(void) -- calculates point energy budget for 2-layer vegsnowcover
**
** DESCRIPTION
**      Calculates point energy budget for 2-layer vegsnowcover.
**
** RETURN VALUE
**
**	true	The calculations were completed.
**
**	false	An error occured, and a message explaining the error has
**		been stored with the 'usrerr' routine.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

int ClassCanSnobalBase::_e_bal_veg(void) {

    if (vegsnowcover[hh] || liq_h2o_veg[hh] > 0.0) {

        // calculate energy xfer terms

        // calculate net radiation

        _net_rad_veg();

        // calculate Qh_veg & Ql_veg  (and qsub_veg as well)

        if (!_h_le_veg())
            return 0;

        // calculate advection

        _advec_veg();

        // veg snowpack energy budget

        delta_Q_veg[hh] = Qn_veg[hh] + Qh_veg[hh] + Ql_veg[hh] + Qp[hh];

    }
    else {
        Qn_veg[hh] = 0.0;

        Qh_veg[hh] = Ql_veg[hh] = qsub_veg[hh] = 0.0;

        Qp[hh] = 0.0;

        delta_Q_veg[hh] = 0.0;
    }

    return 1;
}

/*
** NAME
**      void _net_rad_veg(void) -- calculates net allwave radiation
**
** DESCRIPTION
**      Calculates net allwave radiation from the net solar radiation
**	incoming thermal/longwave radiation, and the snow surface
**	temperature.
**
** GLOBAL VARIABLES READ
**	I_lw
**	S_n
**	T_s_veg
**
** GLOBAL VARIABLES MODIFIED
**	Qn_veg
*/

void ClassCanSnobalBase::_net_rad_veg(void)
{
    //	Qn_veg[hh] = S_n[hh] + (SNOW_EMISSIVITY * (I_lw[hh] - STEF_BOLTZ * pow(T_s_veg[hh], 4.0f)));
    Qn_veg[hh] = S_n[hh] + (I_lw[hh] - 2.0 * SNOW_EMISSIVITY * STEF_BOLTZ * pow(T_s_veg[hh], 4.0f)) * Cc[hh]; // after CLASS to multiply net LW by canopy coverage (i.e, 1 - sky view) and handle top and bottom of canopy snowpack so multiply outgoing LW by 2, since I_lw[hh] includes incoming atm and surface LW wrt canopy.
}

/*
** NAME
**      int _h_le_veg(void) -- calculates turbulent transfer at a point
**
** DESCRIPTION
**      Calculates point turbulent transfer (Qh_veg and Ql_veg) for a 2-layer
**	vegsnowcover. Ql_veg is determined as sublimation if the vegetation snowpack temperature is <= FREEZE and vaporization otherwise.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

int ClassCanSnobalBase::_h_le_veg(void) {

    double e_s, e_a_fix;
    double sat_vp;
    double rel_z_T; // relative z_T (temperature measurement height) above snow surface
    double rel_z_u; // relative z_u (windspeed measurement height) above snow surface

// calculate saturation vapor pressure

    e_s = sati(T_s_veg[hh]);

    //*** error check for bad vapor pressures ***

    sat_vp = sati(T_a[hh]);
    if (e_a[hh] > sat_vp)
        e_a_fix = sat_vp;
    //		const_cast<double*> (e_a)[hh] = sat_vp;
    else
        e_a_fix = e_a[hh];

    // determine relative measurement heights
    if (!relative_hts[hh]) {
        rel_z_T = z_T[hh];
        rel_z_u = z_u[hh];
    }
    else {
        rel_z_T = z_T[hh] - z_veg_s[hh];
        if (rel_z_T < 1.0)
            rel_z_T = 1.0;
        rel_z_u = z_u[hh] - z_veg_s[hh];
        if (rel_z_u < 1.0)
            rel_z_u = 1.0;
    }

    // calculate Qh_veg & Ql_veg

    if (hle1(P_a[hh], T_a[hh], T_s_veg[hh], rel_z_T, e_a_fix, e_s, rel_z_T, u[hh], rel_z_u, z_0_veg[hh], Qh_veg[hh], Ql_veg[hh], qsub_veg[hh]))
        return 1; // !!!!!TB

    return 1;
}

/*
** NAME
**      void _advec_veg(void) -- calculates advected energy at a point
**
** DESCRIPTION
**      This routine calculates the advected energy for a 2-layer vegsnowcover
**	if there's precipitation for the current timestep.
**
** GLOBAL VARIABLES READ
**	m_rain
**	m_snow
**	precip_now_veg
**	T_rain_veg
**	T_s_veg
**	T_sf
**	time_step
**
** GLOBAL VARIABLES MODIFIED
**	Qp
*/

void ClassCanSnobalBase::_advec_veg(void) {

    if (precip_now_veg[hh]) {
        Qp[hh] = (heat_stor(CP_WATER(T_rain_veg[hh]), m_rain[hh], (T_rain_veg[hh] - T_s_veg[hh])) +
            heat_stor(CP_ICE(T_sf[hh]), m_snow[hh], (T_sf[hh] - T_s_veg[hh]))) / time_step[hh];
    }
    else
        Qp[hh] = 0.0;
}

/*
** NAME
**      void _mass_bal(void) -- calculates point mass budget of 2-layer vegsnowcover
**
** DESCRIPTION
**      Calculates the point mass budget for 2-layer energy budget snowmelt
**	model.  It then solves for new snow temperatures.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

void ClassCanSnobalBase::_mass_bal(void) {

    // adjust mass and calc. runoff

    // age snow by compacting snow due to time passing
    // _time_compact(); rm for now, likely needs to be adjusted for canopy snow

    // process precipitation event
    _precip_veg();

    // calculate melt or freezing and adjust cold content

    _snowmelt();

    // calculate sublimation/evaporation and adjust canopy snowpack

    _subl_evap();

    // calculate mass unloading of snow due to wind, sublimation, melting

    _mass_unld();

    // calculate runoff, and adjust vegsnowcover */

    _runoff_veg();

    // adjust layer temps if there was a vegsnowcover at start of the
    //   timestep and there's still snow on the ground

    if(snow_h2o_veg[hh] > 0.0){
        vegsnowcover[hh] = 1;
    } else {
        vegsnowcover[hh] = 0;
    }

    if (vegsnowcover[hh]) {
        T_s_veg[hh] = new_tsno_veg(m_s_veg[hh], T_s_veg[hh], cc_s_veg[hh]);
    }


}

/*
** NAME
**      void _precip_veg(void) -- process a precipitation event
**
** DESCRIPTION
**      This routine processes a precipitation event, i.e., the current
**	precip record, if there's one for the current timestep.  It
**	determines if the precip is rain or snow which increases the
**	vegsnowcover.
**
** GLOBAL VARIABLES READ
**	h2o_sat_veg_snow
**	m_rain
**	m_precip
**	max_h2o_vol_veg
**	precip_now_veg
**	rho_snow
**	vegsnowcover
**	T_sf
**	z_snow_veg
**
** GLOBAL VARIABLES MODIFIED
**	liq_h2o_veg
**	h2o_sat_veg
**	liq_h2o_veg
**	rho_veg
**	T_s_veg
**	T_s_veg
**	z_veg_s[hh]
*/

void ClassCanSnobalBase::_precip_veg(void)
{

    if (precip_now_veg[hh]) {
        if (vegsnowcover[hh] || liq_h2o_veg[hh] > 0.0) {

            // Adjust vegsnowcover's load by new snow/rain.
            liq_h2o_veg[hh] += m_rain[hh];
            snow_h2o_veg[hh] += m_snow[hh];
            m_s_veg[hh] = liq_h2o_veg[hh] + snow_h2o_veg[hh];
        }
        else { // no vegsnowcover

    // Use snowfall, if any, to setup a new vegsnowcover.

            if (m_precip[hh] > 0.0) {
                init_snow_veg();
            }
        }

    } 

}

/*
** NAME
**      void _snowmelt(void) -- calculates melt or re-freezing at a point
**
** DESCRIPTION
**      Calculates melting or re-freezing for point 2-layer energy balance
**      snowmelt model.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

void ClassCanSnobalBase::_snowmelt(void) {

    double  Q_0;            // energy available for surface melt
    double  Q_freeze;       // energy used for re-freezing
    double  Q_left;         // energy left after re_freezing
    double  h2o_refrozen;   // amount of liquid H2O that was refrozen

// If no snow in the canopy at start of timestep, then just exit.

    if (!vegsnowcover[hh]) {
        delmelt_veg[hh] = 0.0;
        return;
    }

    // calculate melt or freezing, and adjust cold content

    // calculate surface melt

    // energy for surface melt
    Q_0 = (delta_Q_veg[hh] * time_step[hh]) + cc_s_veg[hh];

    if (Q_0 > 0.0) {
        delmelt_veg[hh] = MELT(Q_0); // liquid water will only freeze on next timestep
        if(snow_h2o_veg[hh] - delmelt_veg[hh] < 0.0){
            delmelt_veg[hh] = snow_h2o_veg[hh]; // cannot melt more than the amount of snow in the canopy
        }
        cc_s_veg[hh] = 0.0; // all energy is used to melt snow
    }
    else if (Q_0 == 0.0) {
        delmelt_veg[hh] = 0.0;
        cc_s_veg[hh] = 0.0;
    }
    else {
        delmelt_veg[hh] = 0.0;
        cc_s_veg[hh] = Q_0;

        // if (m_s_veg[hh] < 2.0) // addition TB 06/03/10, TODO mod for canopy snow
        //     cc_s_veg[hh] = 0.0;
    }

    liq_h2o_veg[hh] += delmelt_veg[hh];
    snow_h2o_veg[hh] -= delmelt_veg[hh];

    // adjust layers for re-freezing

    // adjust surface layer

    h2o_refrozen = 0.0;

    if (cc_s_veg[hh] < 0.0) { // cannot enter here if snow is melting on current timestep since cc_s_veg == 0
        // if liquid h2o present, calc refreezing and adj cc_s_veg, assumes liquid is at freezing point
        if (liq_h2o_veg[hh] > 0.0) {
            Q_freeze = liq_h2o_veg[hh] * LH_FUS(FREEZE);
            Q_left = Q_0 + Q_freeze;

            // cold content is negative considering updated Q_0, thus enough energy to freeze all liquid water
            if (Q_left <= 0.0) {
                h2o_refrozen = liq_h2o_veg[hh];
                cc_s_veg[hh] = Q_left;
            }
            else {
                h2o_refrozen = liq_h2o_veg[hh] - MELT(Q_left);
                cc_s_veg[hh] = 0.0;
            }
        }
    }

    // Note:  because of rounding errors, h2o_refrozen may not
    //   be exactly the same as liq_h2o_veg.  Check for this case, and if so, then just zero out liq_h2o_veg.

    if (fabs(liq_h2o_veg[hh] - h2o_refrozen) <= 1e-8) {
        liq_h2o_veg[hh] = 0.0;
    }
    else {
        liq_h2o_veg[hh] -= h2o_refrozen;
        snow_h2o_veg[hh] += h2o_refrozen;

    }

    // determine if vegsnowcover is isothermal

    if ((vegsnowcover[hh] == 1) && (cc_s_veg[hh] == 0.0))
        isothermal[hh] = 1;
    else
        isothermal[hh] = 0;

    m_s_veg[hh] = liq_h2o_veg[hh] + snow_h2o_veg[hh];
}

/*
** NAME
**      void _mass_unld(void) -- adjust the canopy snowpack's snow storage due to mass unloading of snow
**
** DESCRIPTION
**      This is the updated mass snow unloading parameterisations from
**  Cebulski & Pomeroy 2025 to unload based on wind, snowmelt, and sublimation
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

void ClassCanSnobalBase::_mass_unld(void)
{
    delunld[hh] = 0.0; // need to clear this val otherwise accumulates due to += below

    // check maximum canopy snow load spill what is overflowing
    if (snow_h2o_veg[hh] > Lmax[hh])
    {
        delunld[hh] = snow_h2o_veg[hh] - Lmax[hh];
    }

    // melt induced mass unloading of solid snow based on ratio relative to canopy snowmelt similar method
    // to Andreadis et al., (2009) based on Storck's measurements
    delunld_melt[hh] = delmelt_veg[hh] * melt_drip_ratio[hh];

    // mass unloading due to sublimation first suggested in JM's thesis
    const double subl_unld_ratio = 0.0; // TODO move to par file

    if(qsub_veg[hh] < 0.0){
        delunld_subl[hh] = -qsub_veg[hh] * subl_unld_ratio; // if sublimation rate is negative wrt the canopy then apply sublimation based unloading (switch the sign of qsub_veg too as this is how it was parameterized)
    } else {
        delunld_subl[hh] = 0.0; // no sublimation based unloading if deposition of water vapour occurs towards the canopy
    }


    // mechanical wind induced unloading
    const double a_u = 1.740917e-06; // Cebulski & Pomeroy coef from exponential function of unloading as function of wind speed and canopy snow load measurements at Fortress mountain when air temp < -6 C.
    const double b_u = 3.326246e-01; // TODO move to par file

    double fu = 0.0;
    double u_mid = 0.0;

    switch (CanopyWindSwitch[hh])
    {
    case 0:
    { // original using Cionco wind model for dense canopies
        // wind speed for wind induced unloading at 1/2 canopy height
        if ((Ht[hh] - (2.0 / 3.0) * z_u[hh]) > 0.0)
        {
            double u_ht = u[hh] * log((Ht[hh] - (2.0 / 3.0) * z_u[hh]) / 0.123 * z_u[hh]) / log((z_u[hh] - 2.0 / 3.0 * z_u[hh]) / 0.123 * z_u[hh]);
            double A = 2.4338 + 3.45753 * exp(-u_ht);                /* Modified Cionco wind model */
            u_mid = u_ht * exp(A * ((Ht[hh] / 2) / (Ht[hh]) - 1.0)); /* calculates canopy windspd  */
        }
        else
        {
            u_mid = 0.0;
        }
        break;
    } // case 0

    case 1:
    {                           // Canopy wind profile developed at Fortress sparse canopy
        double d0 = 0.5791121;  // displacement height observed at sparse forest around Fortress Forest Tower
        double z0m = 0.4995565; // roughness length observed at above site

        // wind speed for wind induced unloading at 1/2 canopy height
        if ((Ht[hh] / 2 - d0) > z0m)
        {
            double Ustar = u[hh] * PBSM_constants::KARMAN / (log((z_u[hh] - d0) / z0m));
            u_mid = Ustar / PBSM_constants::KARMAN * log((Ht[hh] / 2 - d0) / z0m);
        }
        else
        {
            u_mid = 0.0;
        }

        break;
    } // case 1
    } // end of switch CanopyWind

    if (u_mid >= 0.0)
    {
        fu = u_mid * a_u * exp(b_u * u_mid); // unloading rate due to wind (s-1)
    }
    else
    {
        fu = 0.0; // less than wind induced unloading threshold so set equal to 0.
    }

    // ablation via temperature, wind, and duration based unloading
    // delunld[hh] = m_s_veg[hh] * (fT + fu + ft) * dt; // ODE solution: calculate solid snow unloading over the time interval

    // analytical solution which is more exact over longer time intervals, following from Cebulski & Pomeroy derivation of the HP98 unloading parameterisation
    delunld_wind[hh] = snow_h2o_veg[hh] * (1 - exp(-fu * time_step[hh])); // analytical solution for ODE equation 30 in Cebulski & Pomeroy 2025 Wires WATER Review
    delunld[hh] += delunld_wind[hh];
    delunld[hh] += delunld_melt[hh];
    delunld[hh] += delunld_subl[hh];

    if (delunld[hh] > snow_h2o_veg[hh])
    {
        delunld[hh] = snow_h2o_veg[hh];
        snow_h2o_veg[hh] = 0.0;
    }
    else
    {
        snow_h2o_veg[hh] -= delunld[hh];
    }

    m_s_veg[hh] = liq_h2o_veg[hh] + snow_h2o_veg[hh]; 

}

/*
** NAME
**      void _subl_evap(void) -- calculates evaporation/condensation at a point
**
** DESCRIPTION
**      Calculates mass lost or gained by sublimation/evaporation/condensation
**      at a point for the canopy snowpack. Preferentially adjusts snow in the
**      canopy first, if no snow liquid in the canopy is adjusted.
**
** GLOBAL VARIABLES READ
**	qsub_veg
**	time_step
**
** GLOBAL VARIABLES MODIFIED
**	delsub_veg snow_h2o_veg liq_h2o_veg
**
*/

void ClassCanSnobalBase::_subl_evap(void) {

    if (!vegsnowcover[hh] && !(liq_h2o_veg[hh] > 0.0)) { // no h2o in the canopy
        delsub_veg[hh] = 0.0;
        return;
    }

    // Compute total mass change due to sublimation/evaporation over the time step
    delsub_veg[hh] = qsub_veg[hh] * time_step[hh];

    // Apply mass changes based on the presence of snow or liquid water
    if (vegsnowcover[hh]) {
        // Snow is present in the canopy; modify snow water equivalent
        snow_h2o_veg[hh] += delsub_veg[hh];
        if (snow_h2o_veg[hh] < 0.0) {
            snow_h2o_veg[hh] = 0.0;
        }
    } else {
        // Only liquid water is present; modify liquid water content
        liq_h2o_veg[hh] += delsub_veg[hh];
        if (liq_h2o_veg[hh] < 0.0) {
            liq_h2o_veg[hh] = 0.0;
        }
    }
    m_s_veg[hh] = liq_h2o_veg[hh] + snow_h2o_veg[hh]; 
}

#define	BB	0.4 // changed from 0.05

/*
** NAME
**      void _runoff_veg(void) -- calculates runoff from vegsnowcover
**
** DESCRIPTION
**      Calculates runoff for point energy budget 2-layer snowmelt model
**
** GLOBAL VARIABLES READ
**	liq_h2o_veg
**	vegsnowcover
**	max_h2o_vol_veg
**	z_veg_s
**
** GLOBAL VARIABLES MODIFIED
**	liq_h2o_veg
**	max_liq_veg
**	h2o_sat_veg
**	h2o_vol_veg
**	rho_veg
**	deldrip_veg
*/

void ClassCanSnobalBase::_runoff_veg(void) {

    // Determine runoff, and water left in the snow

    if (liq_h2o_veg[hh] > max_liq_veg[hh]) {

        deldrip_veg[hh] = liq_h2o_veg[hh] - max_liq_veg[hh];
        liq_h2o_veg[hh] = max_liq_veg[hh];

        //  Update the vegsnowcover's mass for the loss of runoff.

        liq_h2o_veg[hh] -= deldrip_veg[hh];

    } else {
        deldrip_veg[hh] = 0.0;
    }
    m_s_veg[hh] = liq_h2o_veg[hh] + snow_h2o_veg[hh]; 
}

/* ----------------------------------------------------------------------- */

double ClassCanSnobalBase::new_tsno_veg(
    double	spm,	/* layer's specific mass (kg/m^2) 	 */
    double	t0,	/* layer's last temperature (K) 	 */
    double	ccon)	/* layer's adjusted cold content (J/m^2) */
{
    double	tsno;
    double	cp;
    double	tdif;

    cp = CP_ICE(t0); 

    tdif = ccon / (spm * cp);
    tsno = tdif + FREEZE;

    if (tsno < MIN_SNOW_TEMP + FREEZE)
        tsno = MIN_SNOW_TEMP + FREEZE;
    else {
        if (tsno > FREEZE)
            tsno = FREEZE;
    }

    return (tsno);
}
/* ----------------------------------------------------------------------- */

int ClassCanSnobalBase::hle1(
    double	press,	// aiFr pressure (Pa)
    double	ta,	// air temperature (K) at height za
    double	ts,	// surface temperature (K)
    double	za,	// height of air temp measurement (m)
    double	ea,	// vapor pressure (Pa) at height zq
    double	es,	// vapor pressure (Pa) at surface
    double	zq,	// height of spec hum measurement (m)
    double	u,	// wind speed (m/s) at height zu
    double	zu,	// height of wind speed measurement (m)
    double	z0,	// roughness length (m)

// output variables

double& CRHM_h,	// sens heat flux (+ to surf) (W/m^2)
double& CRHM_le,	// latent heat flux (+ to surf) (W/m^2)
double& CRHM_e)	// mass flux (+ to surf) (kg/m^2/s)
{
    double h = 0;	// sens heat flux (+ to surf) (W/m^2)
    double e = 0;	// mass flux (+ to surf) (kg/m^2/s)

    double	ah = AH;
    double	av = AV;
    double	cp = CP_AIR;
    double	d0;	// displacement height (eq. 5.3)
    double	dens;	// air density
    double	diff;	// difference between guesses
    double	factor;
    double	g = GRAVITY;
    double	k = VON_KARMAN;
    double	last;	// last guess at lo
    double	lo;	// Obukhov stability length (eq. 4.25)
    double	ltsh;	// log ((za-d0)/z0)
    double	ltsm;	// log ((zu-d0)/z0)
    double	ltsv;	// log ((zq-d0)/z0)
    double	qa;	// specific humidity at height zq
    double	qs;	// specific humidity at surface
    double  	ustar;	// friction velocity (eq. 4.34')
    double xlh = 0;	// latent heat of vap/subl
    int	ier = 0;	// return error code
    int	iter = 0;	// iteration counter

    static TDateTime LastDTnow;

    // check for bad input

    // heights must be positive
    if (z0 <= 0 || zq <= z0 || zu <= z0 || za <= z0) {
        string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow) + "hle1: height not positive ";
        string SS = D + "hru " + to_string(hh + 1);
        SS = SS + "  ta: " + FloatToStrF(ta - FREEZE, TFloatFormat::ffFixed, 10, 4) +
            ", z0: " + FloatToStrF(z0, TFloatFormat::ffFixed, 10, 4) +
            ", zq: " + FloatToStrF(zq, TFloatFormat::ffFixed, 10, 4) +
            ", zu: " + FloatToStrF(zu, TFloatFormat::ffFixed, 10, 4) +
            ", za: " + FloatToStrF(za, TFloatFormat::ffFixed, 10, 4);

        CRHMException TExcept(SS.c_str(), TExcept::WARNING);
        LogError(TExcept);
        ier = -2;
        return (ier);
    }

    // temperatures are Kelvin
    if (ta <= 0 || ts <= 0) {
        CRHMException TExcept("temps not K", TExcept::TERMINATE);
        LogError(TExcept);
        ier = -2;
        return (ier);
    }

    // pressures must be positive
    if (ea <= 0 || es <= 0 || press <= 0 || ea >= press || es >= press) {

        string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow);
        string SS = D + "hh " + to_string(hh) + " 'hle1' " + ". Qh_veg: " + FloatToStrF(h, TFloatFormat::ffFixed, 10, 4) + " le: " + FloatToStrF(xlh * e, TFloatFormat::ffFixed, 10, 4);
        SS = SS + " ta: " + FloatToStrF(ta - FREEZE, TFloatFormat::ffFixed, 10, 4) +
            ", ts: " + FloatToStrF(ts - FREEZE, TFloatFormat::ffFixed, 10, 4) +
            ", ea: " + FloatToStrF(ea, TFloatFormat::ffFixed, 10, 4) +
            ", es: " + FloatToStrF(es, TFloatFormat::ffFixed, 10, 4) +
            ", u:  " + FloatToStrF(u, TFloatFormat::ffFixed, 10, 4) +
            ", m_s_veg:  " + FloatToStrF(m_s_veg[hh], TFloatFormat::ffFixed, 10, 4);

        CRHM_le = 0.0; // addition TB 09/23/14
        CRHM_h = 0.0;
        CRHM_e = 0.0;

        CRHMException TExcept2(SS.c_str(), TExcept::WARNING);
        LogError(TExcept2);

        //Manishankar made this change to keep the program running.
        //CRHMException TExcept("hle1: pressures must be positive", TERMINATE);
        CRHMException TExcept("hle1: pressures must be positive", TExcept::WARNING);
        LogError(TExcept);

        ier = -2;
        return (ier);
    }

    // vapor pressures can't exceed saturation if way off stop
    if ((es - 25.0) > sati(ts) || (ea - 25.0) > satw(ta)) {
        CRHMException TExcept("hle1: vapor pressures can't exceed saturation", TExcept::TERMINATE);
        LogError(TExcept);
        ier = -2;
        return (ier);
    }
    // else fix them up
    if (es > sati(ts)) {
        es = sati(ts);
    }
    if (ea > satw(ta)) {
        ea = satw(ta);
    }

    // if (u < 0.5) // rm by AC
    //     u = 0.5;
    else if (u > 15)
        u = 15;
    // displacement plane height, eq. 5.3 & 5.4

    d0 = 2.0 * PAESCHKE * z0 / 3.0;

    // constant log expressions

    ltsm = log((zu - d0) / z0);
    ltsh = log((za - d0) / z0);
    ltsv = log((zq - d0) / z0);

    // convert vapor pressures to specific humidities

    qa = SPEC_HUM(ea, press);
    qs = SPEC_HUM(es, press);

    // convert temperature to potential temperature

    ta += DALR * za;

    // air density at press, virtual temp of geometric mean of air and surface

    dens = GAS_DEN(press, MOL_AIR, VIR_TEMP(sqrt(ta * ts), sqrt(ea * es), press));

    // starting value, assume neutral stability, so psi-functions are all zero

    ustar = k * u / ltsm;
    factor = k * ustar * dens;
    e = (qa - qs) * factor * av / ltsv;
    h = (ta - ts) * factor * cp * ah / ltsh;

    // if not neutral stability, iterate on Obukhov stability length to find solution

    if (ta != ts) {
        lo = HUGE_VAL;

        do {
            last = lo;

            // Eq 4.25, but no minus sign as we define positive Qh_veg as toward surface

            // There was an error in the old version of this line that omitted the cubic power of ustar. Now, this error has been fixed.

            // lo = ustar * ustar * ustar * dens / (k * g * (h / (ta * cp) + 0.61 * e));

            lo = ustar * ustar * ustar * ta * dens * cp / (k * g * h); // changed based on U of S CE836 notes
            // friction velocity, eq. 4.34'

            ustar = k * u / (ltsm - psi(zu / lo, SM));

            // evaporative flux, eq. 4.33'

            factor = k * ustar * dens;
            e = (qa - qs) * factor * av / (ltsv - psi(zq / lo, SV));

            // sensible heat flux, eq. 4.35' with sign reversed

            h = (ta - ts) * factor * ah * cp / (ltsh - psi(za / lo, SH));

            diff = last - lo;

            // if(!(fabs(diff) > THRESH && fabs(diff / lo) > THRESH)){
            //     std::cout << "diff = " << diff << std::endl;
            // }
        if (++iter >= ITMAX) break;
        } while (fabs(diff) > THRESH || (fabs(lo) > 1e-6 && fabs(diff / lo) > THRESH));
    }

    xlh = LH_VAP(ts);
    if (ts <= FREEZE)
        xlh = LH_SUB(ts); // changed from += LH_FUS for clarity

    // latent heat flux (- away from surf)

    CRHM_le = xlh * e;
    CRHM_h = h;
    CRHM_e = e;


    if (iter >= ITMAX) {
        CRHM_le = 0.0; // addition TB 06/03/10
        CRHM_h = 0.0;
        CRHM_e = 0.0;

        string Flag = "iters" + to_string(iter);
        LastDTnow = Global::DTnow;

        string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow);
        string SS = D + "hh " + to_string(hh) + " 'hle1' " + Flag + ". Qh_veg: " + FloatToStrF(h, TFloatFormat::ffFixed, 10, 4) + " le: " + FloatToStrF(xlh * e, TFloatFormat::ffFixed, 10, 4);
        SS = SS + " ta: " + FloatToStrF(ta - FREEZE, TFloatFormat::ffFixed, 10, 4) +
            ", ts: " + FloatToStrF(ts - FREEZE, TFloatFormat::ffFixed, 10, 4) +
            ", ea: " + FloatToStrF(ea, TFloatFormat::ffFixed, 10, 4) +
            ", es: " + FloatToStrF(es, TFloatFormat::ffFixed, 10, 4) +
            ", u:  " + FloatToStrF(u, TFloatFormat::ffFixed, 10, 4) +
            ", m_s_veg:  " + FloatToStrF(m_s_veg[hh], TFloatFormat::ffFixed, 10, 4);
        CRHMException TExcept2(SS.c_str(), TExcept::WARNING);
        LogError(TExcept2);

        ier = -1;
    }

    //  ier_array[ArrayCnt[hh]][hh] = ier;
    //  e_array[ArrayCnt[hh]][hh] = e;
    //  h_array[ArrayCnt[hh]][hh] = h;
    //  Length_array[ArrayCnt[hh]][hh] = lo;
    //  Ustar_array[ArrayCnt[hh]++][hh] = ustar;

    return (ier);
}
