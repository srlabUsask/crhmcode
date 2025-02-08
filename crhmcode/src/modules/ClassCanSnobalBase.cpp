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

        T_s_veg[hh] = -75.0; // temperatures inside CanSnobal model are K
        T_s_veg_0[hh] = -75.0;

        rho_veg[hh] = 218.0; // change 10/18/16
        h2o_sat_veg[hh] = 0.0;

        z_veg_s[hh] = 0.0;
        z_s_veg_0[hh] = 0.0;

        m_s_veg[hh] = 0.0;
        m_s_veg_0[hh] = 0.0;

        cc_s_veg[hh] = 0.0;
        cc_s_0_veg[hh] = 0.0;

        h2o_veg[hh] = 0.0;
        h2o_max_veg[hh] = 0.0;
        h2o_total_veg[hh] = 0.0;
        delmelt_veg[hh] = 0.0;
        z_snow_veg[hh] = 0.0;
        deldrip_veg[hh] = 0.0;
        T_snow_veg[hh] = 0.0;
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
        m_subl_cum[hh] = 0.0;
        cmlmelt_veg[hh] = 0.0;

        Ql_veg[hh] = 0.0;
        qsub_veg[hh] = 0.0;
        Qh_veg[hh] = 0.0;
        Qp[hh] = 0.0;
        Qn_veg[hh] = 0.0;
        delta_Q_veg[hh] = 0.0;
        delta_Q_0_veg[hh] = 0.0;

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
        LogMessageA(hh, string("'" + Name + " (CanSnobal)' m_subl_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), -m_subl_cum[hh], hru_area[hh], basin_area[0]);
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

void ClassCanSnobalBase::init_snow(void)
{
    double	rho_dry;	// snow density without H2O

    m_s_veg[hh] = rho_veg[hh] * z_veg_s[hh];

        // Compute specific mass for each layer.

        _layer_mass();

        cc_s_0_veg[hh] = _cold_content(T_s_veg_0[hh], m_s_veg_0[hh]);

        // Compute liquid water content as volume ratio, and snow density without water.

        h2o_vol_veg[hh] = h2o_sat_veg[hh] * max_h2o_vol_veg[hh];
        rho_dry = DRY_SNO_RHO(rho_veg[hh], h2o_vol_veg[hh]);

        // Determine maximum liquid water content (as specific mass) and the actual liquid water content (as specific mass).

        h2o_max_veg[hh] = H2O_LEFT(z_veg_s[hh], rho_dry, max_h2o_vol_veg[hh]);

        h2o_veg[hh] = h2o_sat_veg[hh] * h2o_max_veg[hh];
        stop_no_snow[hh] = 0; //????

}

/*
** NAME
**      void _layer_mass(void) -- calculate the specific mass for each snow layer
**
** DESCRIPTION
**      This routine computes the specific mass for each snow layer in
**	the vegsnowcover.  A layer's mass is based its depth and the
**	average vegsnowcover density.
**
** GLOBAL VARIABLES READ
**	rho_veg
**	z_s_veg_0
**
** GLOBAL VARIABLES MODIFIED
**	m_s_veg_0
*/

void ClassCanSnobalBase::_layer_mass(void)
{
    m_s_veg_0[hh] = rho_veg[hh] * z_s_veg_0[hh];
}

/*
** NAME
**      _cold_content -- calculates cold content for a layer
**
**      double
**	_cold_content(
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

double ClassCanSnobalBase::_cold_content(
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
**      int do_data_tstep(void) -- run model for 1 data timestep between 2 input records
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
**	precip_now
*/

void ClassCanSnobalBase::do_data_tstep(void) {

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

    precip_info[hh]->m_subl = m_subl[hh];

    if (precip_now_veg[hh]) {
        precip_info[hh]->m_pp = m_precip[hh];
        precip_info[hh]->m_snow = m_snow[hh];
        precip_info[hh]->m_rain = m_rain[hh];

        if (precip_info[hh]->m_snow > 0.0)
            precip_info[hh]->z_snow = z_snow_veg[hh];
        else
            precip_info[hh]->z_snow = 0.0;

        // Mixed snow and rain

        if ((precip_info[hh]->m_snow > 0.0) && (precip_info[hh]->m_rain > 0.0)) {
            T_snow_veg[hh] = FREEZE;
            h2o_sat_veg_snow[hh] = 1.0;
            T_rain_veg[hh] = T_pp[hh];
        }

        // Snow only

        else if (precip_info[hh]->m_snow > 0.0) {
            if (T_pp[hh] < FREEZE) {	/* Cold snow */
                T_snow_veg[hh] = T_pp[hh];
                h2o_sat_veg_snow[hh] = 0.0;
            }
            else {				/* Warm snow */
                T_snow_veg[hh] = FREEZE;
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

    _divide_tstep(tstep_info[hh]);
}

/*
** NAME
**      int _divide_tstep( -- divide a timestep into smaller timesteps
**
**	int
**	_divide_tstep(
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
**	precip_now
**	tstep_info
**
** GLOBAL VARIABLES MODIFIED
*/

int ClassCanSnobalBase::_divide_tstep(TSTEP_REC* tstep) {  // record of timestep to be divided

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
        next_lvl_precip->m_subl = curr_lvl_precip->m_subl / next_lvl_tstep->intervals;
        next_lvl_precip->z_snow = curr_lvl_precip->z_snow / next_lvl_tstep->intervals;

        computed[hh][next_level] = 1;
    }

    // For each the new smaller timestep, either subdivide them if below their mass threshold, or run the model for them.

    for (int ii = 0; (ii < next_lvl_tstep->intervals) && !stop_no_snow[hh]; ++ii) { // execute every interval

        if ((next_level < SMALL_TSTEP) && _below_thold(next_lvl_tstep->threshold)) {
            if (!_divide_tstep(next_lvl_tstep)) // call self (this routine)
                return 0; // cannot get here unless _hl_e is coded to return error!
        }
        else {
            if (!_do_tstep(next_lvl_tstep)) // execute code
                return 0; // cannot get here unless _hl_e is coded to return error!
        }
    } // for

    return 1;
} // _divide_tstep

/*
** NAME
**      _below_thold -- is a layer's mass below a threshold ?
**
**      int
**	_below_thold(
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
**	m_s_veg_0
**
** GLOBAL VARIABLES MODIFIED
*/

int ClassCanSnobalBase::_below_thold(double	threshold) { // current timestep's threshold for a layer's mass

    if (vegsnowcover[hh] == 0)
        return 0;
    else
        return (m_s_veg[hh] < threshold);
}

/*
** NAME
**      _do_tstep -- do model calculations for 1 timestep
**
**      int
**	_do_tstep(
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
**	delta_Q_0_veg
**	delsub_veg
**	G
**	Qh_veg
**	Ql_veg
**	Qp
**	delmelt_veg
**	precip_now
**	Qn_veg
**	deldrip_veg
**
** GLOBAL VARIABLES MODIFIED
**	current_time
**	curr_time_hrs
**	delta_Q_0_bar
**	delta_Q_bar
**	e_a
**	G_bar
**	H_bar
**	h2o_total_veg
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

int ClassCanSnobalBase::_do_tstep(TSTEP_REC* tstep)  // timestep's record
{
    time_step[hh] = tstep->time_step;

    m_precip[hh] = precip_info[hh][tstep->level].m_pp;
    m_rain[hh] = precip_info[hh][tstep->level].m_rain;
    m_snow[hh] = precip_info[hh][tstep->level].m_snow;
    m_subl[hh] = precip_info[hh][tstep->level].m_subl;
    z_snow_veg[hh] = precip_info[hh][tstep->level].z_snow;

    h2o_total_veg[hh] = 0.0;
    delmelt_veg[hh] = 0.0;

    // Is there a vegsnowcover?

    vegsnowcover[hh] = (m_s_veg[hh] > 0.0);

    // Calculate energy transfer terms

    if (!_e_bal())
        return 0;

    // Adjust mass and calculate runoff

    _mass_bal();

    //  Update the averages for the energy terms and the totals for mass changes since the last output.

    // increment time
    current_time[hh] += time_step[hh];

    //  update interval values

    delmelt_veg_int2[hh] += deldrip_veg[hh];
    delsub_veg_int[hh] += delsub_veg[hh];
    delsub_veg_0_int[hh] += qsub_veg[hh];
    delsub_veg_0_int2[hh] += delsub_veg_0[hh];

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
**      int _e_bal(void) -- calculates point energy budget for 2-layer vegsnowcover
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

int ClassCanSnobalBase::_e_bal(void) {

    if (vegsnowcover[hh]) {

        // calculate energy xfer terms

        // calculate net radiation

        _net_rad();

        // calculate Qh_veg & Ql_veg  (and qsub_veg as well)

        if (!_h_le())
            return 0;

        // calculate advection

        _advec();

        // sum qsub_veg.B. terms

        // surface energy budget

        delta_Q_0_veg[hh] = Qn_veg[hh] + Qh_veg[hh] + Ql_veg[hh] + Qp[hh];

        // total snowpack energy budget

        delta_Q_veg[hh] = delta_Q_0_veg[hh];

    }
    else {
        Qn_veg[hh] = 0.0;

        Qh_veg[hh] = Ql_veg[hh] = qsub_veg[hh] = 0.0;

        Qp[hh] = 0.0;

        delta_Q_veg[hh] = delta_Q_0_veg[hh] = 0.0;
    }

    return 1;
}

/*
** NAME
**      void _net_rad(void) -- calculates net allwave radiation
**
** DESCRIPTION
**      Calculates net allwave radiation from the net solar radiation
**	incoming thermal/longwave radiation, and the snow surface
**	temperature.
**
** GLOBAL VARIABLES READ
**	I_lw
**	S_n
**	T_s_veg_0
**
** GLOBAL VARIABLES MODIFIED
**	Qn_veg
*/

void ClassCanSnobalBase::_net_rad(void)
{
    //	Qn_veg[hh] = S_n[hh] + (SNOW_EMISSIVITY * (I_lw[hh] - STEF_BOLTZ * pow(T_s_veg_0[hh], 4.0f)));
    Qn_veg[hh] = S_n[hh] + (I_lw[hh] - SNOW_EMISSIVITY * STEF_BOLTZ * pow(T_s_veg_0[hh], 4.0f)); // correction 07/17/14
}

/*
** NAME
**      int _h_le(void) -- calculates turbulent transfer at a point
**
** DESCRIPTION
**      Calculates point turbulent transfer (Qh_veg and Ql_veg) for a 2-layer
**	vegsnowcover.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

int ClassCanSnobalBase::_h_le(void) {

    double e_s, e_a_fix;
    double sat_vp;
    double rel_z_T; // relative z_T (temperature measurement height) above snow surface
    double rel_z_u; // relative z_u (windspeed measurement height) above snow surface

// calculate saturation vapor pressure

    e_s = sati(T_s_veg_0[hh]);

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

    if (hle1(P_a[hh], T_a[hh], T_s_veg_0[hh], rel_z_T, e_a_fix, e_s, rel_z_T, u[hh], rel_z_u, z_0_veg[hh], Qh_veg[hh], Ql_veg[hh], qsub_veg[hh]))
        return 1; // !!!!!TB

    return 1;
}

double ClassCanSnobalBase::g_soil(
    double	rho_veg,	// snow layer's density (kg/m^3)
    double	tsno,	// snow layer's temperature (K)
    double	tg,	// soil temperature (K)
    double	ds,	// snow layer's thickness (m)
    double	dg,	// dpeth of soil temperature measurement (m)
    double	pa)	// air pressure (Pa)
{
    double	k_g;
    double	kcs;
    double	k_s;
    double	g;

    // check tsno
    if (tsno > FREEZE) {
        // warn("g_soil: tsno = %8.2f; set to %8.2f\n", tsno, FREEZE);
        tsno = FREEZE;
    }

    // set effective soil conductivity
    k_g = efcon(KT_sand[hh], tg, pa);   // 10/26/10

// calculate G
// set snow conductivity
    kcs = KTS(rho_veg);
    k_s = efcon(kcs, tsno, pa);

    g = ssxfr(k_s, k_g, tsno, tg, ds, dg);

    return (g);
}

double ClassCanSnobalBase::g_snow(
    double	rho1,	/* upper snow layer's density (kg/m^3)	*/
    double	rho2,	/* lower  "     "        "    (kg/m^3)	*/
    double	ts1,	/* upper snow layer's temperature (K)	*/
    double	ts2,	/* lower  "     "         "       (K)	*/
    double	ds1,	/* upper snow layer's thickness (m)	*/
    double	ds2,	/* lower  "     "         "     (m)	*/
    double	pa)	/* air pressure (Pa)			*/
{
    double	kcs1;
    double	kcs2;
    double	k_s1;
    double	k_s2;
    double	g;


    //	calculate G
    if (ts1 == ts2)
        g = 0.0;
    else {
        //	set snow conductivity
        kcs1 = KTS(rho1);
        kcs2 = KTS(rho2);
        k_s1 = efcon(kcs1, ts1, pa);
        k_s2 = efcon(kcs2, ts2, pa);

        //	calculate g
        g = ssxfr(k_s1, k_s2, ts1, ts2, ds1, ds2);
    }

    return (g);
}

/*
** NAME
**      void _advec(void) -- calculates advected energy at a point
**
** DESCRIPTION
**      This routine calculates the advected energy for a 2-layer vegsnowcover
**	if there's precipitation for the current timestep.
**
** GLOBAL VARIABLES READ
**	m_rain
**	m_snow
**	precip_now
**	T_rain_veg
**	T_s_veg_0
**	T_snow_veg
**	time_step
**
** GLOBAL VARIABLES MODIFIED
**	Qp
*/

void ClassCanSnobalBase::_advec(void) {

    if (precip_now_veg) {
        Qp[hh] = (heat_stor(CP_WATER(T_rain_veg[hh]), m_rain[hh], (T_rain_veg[hh] - T_s_veg_0[hh])) +
            heat_stor(CP_ICE(T_snow_veg[hh]), m_snow[hh], (T_snow_veg[hh] - T_s_veg_0[hh]))) / time_step[hh];
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
    _time_compact();

    // process precipitation event
    _precip();

    // calculate melt or freezing and adjust cold content

    _snowmelt();

    // calculate evaporation and adjust snowpack

    _evap_cond();

    // compact snow due to H2O generated (melt & rain)
    _h2o_compact();

    // calculate runoff, and adjust vegsnowcover */

    _runoff();

    // adjust layer temps if there was a vegsnowcover at start of the
    //   timestep and there's still snow on the ground

    if (vegsnowcover[hh]) {
        T_s_veg_0[hh] = new_tsno(m_s_veg_0[hh], T_s_veg_0[hh], cc_s_0_veg[hh]);
        T_s_veg[hh] = T_s_veg_0[hh];
    }
}

/*
** NAME
**      void _time_compact(void) -- compact vegsnowcover by gravity over time
**
** DESCRIPTION
**	This routine "ages" the vegsnowcover by accounting for the compaction
**	or densification by gravity as time passes.  The vegsnowcover's
**	density is increased using the following "half-saturation" function:
**
**		rho_veg(time) = A / (1 + B/time)
**
**	A = "saturation-level" or asymtope which is the maximum density
**	    due to compaction by gravity (approximately 350 kg/m^2)
**	B = the point for half of the saturation level is reached (10 days)
**
**			^
**			|
**		 A: 350 + = = = = = = = = = = = = = = = = = =
**		  	|			*   *
**			|		   *
**	rho_veg		|	       *
**	(kg/m^2)	|	    *
**			|	  *
**	       A/2: 175 + . . . *
**      		|     * .
**      		|   *   .
**      		|  * 	.
**      		| * 	.
**      		|*	.
**      	      0 +-------+----------------------------->
**      		0	B: 10 days		time
**
**
** GLOBAL VARIABLES READ
**	time_step
**
** GLOBAL VARIABLES MODIFIED
**	rho_veg
**	(and those variables modified by "_new_density")
**
*/

//  Time when half "saturation", i.e., maximum density is reached * (seconds).
// *  (864000 = 10 days * 24 hours/day * 60 mins/hr * 60 secs/min)

void ClassCanSnobalBase::_time_compact(void)
{
    const double A = 350; // Maximum density due to compaction by gravity (kg/m^2).
    const double B = 86400;

    double	time;	/* point on time axis corresponding to current density */
  // If the snow is already at or above the maximum density due compaction by gravity, then just leave.

    if (!vegsnowcover[hh] || rho_veg[hh] > A || m_s_veg[hh] <= 0.0)
        return;

    // Given the current density, determine where on the time axis we are (i.e., solve the function above for "time").

    if (rho_veg[hh] > 349)
        rho_veg[hh] = 349;

    time = B / (A / rho_veg[hh] - 1);

    // Move along the time axis by the time step, and calculate the density at this new time.

    rho_veg[hh] = A / (1 + B / (time + time_step[hh]));

    // Adjust the vegsnowcover for this new density.

    _new_density();
}

/*
** NAME
**      void _precip(void) -- process a precipitation event
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
**	T_snow_veg
**	z_snow_veg
**
** GLOBAL VARIABLES MODIFIED
**	h2o_veg
**	h2o_sat_veg
**	h2o_total_veg
**	rho_veg
**	T_s_veg
**	T_s_veg_0
**	z_veg_s[hh]
**	(and those variables modified by "_adj_snow" and "_init_snow")
*/

void ClassCanSnobalBase::_precip(void)
{
    double	h2o_vol_veg_snow;	// liquid water content of new snowfall as volume ratio

    if (precip_now_veg[hh]) {
        if (vegsnowcover[hh]) {

            // Adjust vegsnowcover's depth and mass by snowfall's depth and the total precipitation mass.

            _adj_snow(z_snow_veg[hh], m_precip[hh]);


            // Determine the additional liquid water that's in the snowfall,
            //   and then add its mass to liquid water in the whole vegsnowcover.

            h2o_vol_veg_snow = h2o_sat_veg_snow[hh] * max_h2o_vol_veg[hh];
            h2o_veg[hh] += H2O_LEFT(z_snow_veg[hh], rho_snow[hh], h2o_vol_veg_snow);
        }
        else { // no vegsnowcover

    // Use snowfall, if any, to setup a new vegsnowcover.

            if (m_snow[hh] > 0.0) {
                z_veg_s[hh] = z_snow_veg[hh];
                rho_veg[hh] = rho_snow[hh];
                T_s_veg[hh] = T_snow_veg[hh];
                T_s_veg_0[hh] = T_snow_veg[hh];
                h2o_sat_veg[hh] = h2o_sat_veg_snow[hh];

                init_snow();
            }
        }

        // Add rainfall and water in the vegsnowcover to total liquid water. ???? !!!!

        h2o_total_veg[hh] += m_rain[hh];
        //    deldrip_veg[hh] += m_rain[hh];
    } // current precip

  // Add water in the vegsnowcover to total liquid water.
    else // no precip
        h2o_total_veg[hh] += h2o_veg[hh];
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
**	(and those variables modified by "_adj_snow")
*/

void ClassCanSnobalBase::_snowmelt(void) {

    double  Q_0;            // energy available for surface melt
    double  Q_l;	       // energy available for lower layer melt
    double  Q_freeze;       // energy used for re-freezing
    double  Q_left;         // energy left after re_freezing
    double  h2o_refrozen;   // amount of liquid H2O that was refrozen

// If no snow on ground at start of timestep, then just exit.

    if (!vegsnowcover[hh]) {
        delmelt_veg[hh] = 0.0;
        return;
    }

    // calculate melt or freezing, and adjust cold content

    // calculate surface melt

    // energy for surface melt
    Q_0 = (delta_Q_0_veg[hh] * time_step[hh]) + cc_s_0_veg[hh];

    if (Q_0 > 0.0) {
        delmelt_veg[hh] = MELT(Q_0);
        cc_s_0_veg[hh] = 0.0;
    }
    else if (Q_0 == 0.0) {
        delmelt_veg[hh] = 0.0;
        cc_s_0_veg[hh] = 0.0;
    }
    else {
        delmelt_veg[hh] = 0.0;
        cc_s_0_veg[hh] = Q_0;

        if (m_s_veg[hh] < 2.0) // addition TB 06/03/10
            cc_s_0_veg[hh] = 0.0;
    }


    // calculate lower layer melt

    h2o_total_veg[hh] += delmelt_veg[hh];

    // adjust layers for re-freezing

    // adjust surface layer

    h2o_refrozen = 0.0;

    if (cc_s_0_veg[hh] < 0.0) {
        // if liquid h2o present, calc refreezing and adj cc_s_0_veg
        if (h2o_total_veg[hh] > 0.0) {
            Q_freeze = h2o_total_veg[hh] * (z_s_veg_0[hh] / z_veg_s[hh]) * LH_FUS(FREEZE);
            Q_left = Q_0 + Q_freeze;

            if (Q_left <= 0.0) {
                h2o_refrozen = h2o_total_veg[hh] * (z_s_veg_0[hh] / z_veg_s[hh]);
                cc_s_0_veg[hh] = Q_left;
            }
            else {
                h2o_refrozen = (h2o_total_veg[hh] * (z_s_veg_0[hh] / z_veg_s[hh])) - MELT(Q_left);
                cc_s_0_veg[hh] = 0.0;
            }
        }
    }

    // Note:  because of rounding errors, h2o_refrozen may not
    //   be exactly the same as h2o_total_veg.  Check for this case, and if so, then just zero out h2o_total_veg.

    if (fabs(h2o_total_veg[hh] - h2o_refrozen) <= 1e-8) {
        h2o_total_veg[hh] = 0.0;
    }
    else {
        h2o_total_veg[hh] -= h2o_refrozen;
    }

    // determine if vegsnowcover is isothermal

    if ((vegsnowcover[hh] == 1) && (cc_s_0_veg[hh] == 0.0))
        isothermal[hh] = 1;
    else
        isothermal[hh] = 0;

    // adjust depth and density for melt

    if (delmelt_veg[hh] > 0.0) { // !!!
        if (rho_veg[hh] <= 0.0)
            rho_veg[hh] = 750; // Maximum snow density (kg/m^3)

        _adj_snow(-(delmelt_veg[hh] / rho_veg[hh]), 0.0);
    }

    cc_s_veg[hh] = cc_s_0_veg[hh];
}

/*
** NAME
**      void _new_density(void) -- adjust the vegsnowcover's depth and layers for new density
**
** DESCRIPTION
**      This routine adjusts the vegsnowcover's depth for a new density.  The
**	layers are also adjusted accordingly.
**
** GLOBAL VARIABLES READ
**	m_s_veg
**	rho_veg
**
** GLOBAL VARIABLES MODIFIED
**	z_veg_s
**
**	(and those variables modified by "_adj_layers")
*/

void ClassCanSnobalBase::_new_density(void) {

    z_veg_s[hh] = m_s_veg[hh] / rho_veg[hh];

}

/*
** NAME
**      _adj_snow -- adjust the vegsnowcover with changes in depth and/or mass
**
**      void
**	_adj_snow(
**	    double delta_z_s,	|* change in vegsnowcover's depth *|
**	    double delta_m_s)	|* change is vegsnowcover's mass *|
**
** DESCRIPTION
**      This routine adjusts the vegsnowcover for a change in its depth or
**	its mass or both.  The vegsnowcover's density is updated.  If there
**	is a change in the vegsnowcover's depth, the # of layers is recomputed.
**	If there's just a change in the vegsnowcover's mass with no change in
**	its depth, then just the specific masses for the layers are updated.
**
**	The routine ensures that the vegsnowcover's density does NOT exceed
**	a maximum density (currently 750 kg/m^3).  If the adjustments to
**	the vegsnowcover, for some reason, lead to an excessive density, the
**	density is clipped at the maximum, and the depth re-adjusted
**	accordingly.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**	m_s_veg
**	rho_veg
**	z_veg_s
**
**	(and those variables modified by "_adj_layers" and "_layer_mass")
*/

void ClassCanSnobalBase::_adj_snow(
    double	delta_z_s,	// change in vegsnowcover's depth
    double	delta_m_s)	// change is vegsnowcover's mass
{

    const double MAX_SNOW_DENSITY = 750; // Maximum snow density (kg/m^3)

  // Update depth, mass, and then recompute density.
    z_veg_s[hh] += delta_z_s;
    m_s_veg[hh] += delta_m_s;

    if (z_veg_s[hh] > 0.0)
        rho_veg[hh] = m_s_veg[hh] / z_veg_s[hh];
    else {
        z_veg_s[hh] = 0.0;
        m_s_veg[hh] = 0.0;
    }

    // Clip density at maxium density if necessary.
    if (rho_veg[hh] > MAX_SNOW_DENSITY) {
        rho_veg[hh] = MAX_SNOW_DENSITY;
        z_veg_s[hh] = m_s_veg[hh] / rho_veg[hh];
    }
    // If a change in depth, adjust the layers' depths and masses.
    else {
        if (delta_z_s != 0.0)
            _layer_mass();
    }
}

/*
** NAME
**      void _evap_cond(void) -- calculates evaporation/condensation at a point
**
** DESCRIPTION
**      Calculates mass lost or gained by evaporation/condensation
**      at a point for 2-layer energy balance snowmelt model snobal.c;
**      Also adjusts the liq h2o, mass and depth of the snow layer;
**      Assumes that liq h2o is favored in evap as the ratio of
**      vaporization to sublimation (0.882); Half the ice lost as evap
**      is assumed to be lost depth; the rest reduces the density;
**
** GLOBAL VARIABLES READ
**	qsub_veg
**	P_a
**	rho_veg
**	T_s_veg_0
**	time_step
**	z_g
**
** GLOBAL VARIABLES MODIFIED
**	delsub_veg h2o_total_veg
**
**	(and those variables modified by "_adj_snow")
*/

#define VAP_SUB (2.501 / 2.835) // ratio vaporization to sublimatin

void ClassCanSnobalBase::_evap_cond(void) {

    //        double  delsub_veg_0;          // mass of evaporation to air (kg/m^2)
    double  e_g;            // soil vapor press
    double  k;              // soil diffusion coef
    double  prev_h2o_tot;   // previous value of h2o_total_veg variable
    double  q_delta;        // difference between snow & soil spec hum's
    double  q_g;            // soil spec hum
    double  rho_air;        // air density
    double  T_bar;          // snow-soil mean temp

// calculate evaporation or condensation

// If no snow on ground at start of timestep, then just exit.

    if (!vegsnowcover[hh]) {
        delsub_veg[hh] = 0.0;
        return;
    }

    // Total mass change due to evap/cond at surface during timestep

    delsub_veg_0[hh] = qsub_veg[hh] * time_step[hh];

    //  Adjust total h2o for evaporative losses

    prev_h2o_tot = h2o_total_veg[hh];

    if (h2o_total_veg[hh] > 0.0) {
        h2o_total_veg[hh] += (delsub_veg_0[hh] * VAP_SUB);
        if (h2o_total_veg[hh] <= 0.0)
            h2o_total_veg[hh] = 0.0;
    }

    delsub_veg[hh] = delsub_veg_0[hh];

    //      adj mass and depth for evap/cond

    if (vegsnowcover[hh] > 0)
        _adj_snow(((delsub_veg[hh] + (prev_h2o_tot - h2o_total_veg[hh])) / rho_veg[hh]) / 2.0, delsub_veg[hh]);
}

/*
** NAME
**      void _h2o_compact(void) -- compact vegsnowcover due to liquid H2O that was added
**
** DESCRIPTION
**	This routine compacts or densifies the vegsnowcover based on the
**	amount of liquid H2O that was added to the vegsnowcover from melting
**	and rain.  The vegsnowcover's density is increased using the
**	following "half-saturation" function:
**
**		delta_rho(h2o_added) = A / (1 + B/h2o_added)
**
**	A = "saturation-level" or asymtope which is the difference between
**	    the maximum density due to compaction by liquid H2O
**	    (approximately 550 kg/m^2) and the current density
**	B = the point for half of the saturation level is reached (5 %)
**	    (h2o_added = ratio of mass of liquid h2o added by melting and
**		         rain to the mass of the vegsnowcover)
**
**			^
**			|
**		      A + = = = = = = = = = = = = = = = = = =
**	(550 - current  |			*   *
**	       density)	|		   *
**			|	       *
**	delta_rho	|	    *
**	(kg/m^2)	|	  *
**	            A/2 + . . . *
**      		|     * .
**      		|   *   .
**      		|  * 	.
**      		| * 	.
**      		|*	.
**      	      0 +-------+-----------------------------+	  h2o_added
**      		0	B: 5 %			     1.0
**
**
** GLOBAL VARIABLES READ
**	m_rain
**	m_s_veg
**	delmelt_veg
**
** GLOBAL VARIABLES MODIFIED
**	rho_veg
**
**	(and those variables modified by "_new_density")
*/

#define	MAX_DENSITY  550
/*
 *  Maximum density due to compaction by liquid H2O added (kg/m^2).
 */

#define	BB	0.4 // changed from 0.05

 // ratio where half the difference between maximum density and
 //   current density is reached (ratio from 0.0 to 1.0).

void ClassCanSnobalBase::_h2o_compact(void)
{

    double Alocal;         // difference between maximum & currentdensities

    double	h2o_added;	// ratio of mass of liquid H2O added from melting and rain to mass of vegsnowcover

  // If the snow is already at or above the maximum density due compaction by liquid H2O, then just leave.

    if ((!vegsnowcover[hh]) || (rho_veg[hh] > MAX_DENSITY))
        return;

    Alocal = MAX_DENSITY - rho_veg[hh];

    if (m_s_veg[hh]) {  // !!! fudge
        if (precip_now_veg[hh])
            h2o_added = (delmelt_veg[hh] + m_rain[hh]) / m_s_veg[hh];
        else
            h2o_added = delmelt_veg[hh] / m_s_veg[hh];

        if (h2o_added > 0.000001) {
            rho_veg[hh] += Alocal / (1 + BB / h2o_added);
            _new_density(); // Adjust the vegsnowcover for this new density.
        }
    }
}

/*
** NAME
**      void _runoff(void) -- calculates runoff from vegsnowcover
**
** DESCRIPTION
**      Calculates runoff for point energy budget 2-layer snowmelt model
**
** GLOBAL VARIABLES READ
**	h2o_total_veg
**	vegsnowcover
**	max_h2o_vol_veg
**	z_veg_s
**
** GLOBAL VARIABLES MODIFIED
**	h2o_veg
**	h2o_max_veg
**	h2o_sat_veg
**	h2o_vol_veg
**	rho_veg
**	deldrip_veg
*/

void ClassCanSnobalBase::_runoff(void) {

    double	m_s_dry;	/* vegsnowcover's mass without liquid H2O */
    double	rho_dry;	/* snow density without liquid H2O */

// calculate runoff

// If no snow on ground at start of timestep or no layers currently, then all water (e.g., rain) is runoff.

    if ((!vegsnowcover[hh])) {
        deldrip_veg[hh] = h2o_total_veg[hh];
        return;
    }

    //  Determine the snow density without any water, and the maximum liquid water the snow can hold.

    m_s_dry = m_s_veg[hh] - h2o_total_veg[hh];
    rho_dry = m_s_dry / z_veg_s[hh];
    h2o_max_veg[hh] = H2O_LEFT(z_veg_s[hh], rho_dry, max_h2o_vol_veg[hh]);

    // Determine runoff, and water left in the snow

    if (h2o_total_veg[hh] > h2o_max_veg[hh]) {
        deldrip_veg[hh] = h2o_total_veg[hh] - h2o_max_veg[hh];
        h2o_veg[hh] = h2o_max_veg[hh];
        h2o_sat_veg[hh] = 1.0;
        h2o_vol_veg[hh] = max_h2o_vol_veg[hh];

        //  Update the vegsnowcover's mass for the loss of runoff.

        _adj_snow(0.0, -deldrip_veg[hh]);
    }
    else {
        deldrip_veg[hh] = 0.0;
        h2o_veg[hh] = h2o_total_veg[hh];
        h2o_sat_veg[hh] = h2o_veg[hh] / h2o_max_veg[hh];
        h2o_vol_veg[hh] = h2o_sat_veg[hh] * max_h2o_vol_veg[hh];
    }
}

// psi-functions
//	code =	SM	momentum
//		SH	sensible heat flux
//		SV	latent heat flux

static double
psi(double zeta,		// z/lo
    int	code)		// which psi function? (see above)
{
    double	x;		// height function variable
    double	result{};

    if (zeta > 0) // stable
    {
        if (zeta > 1)
        {
            zeta = 1;
        }
        result = -BETA_S * zeta;
    }
    else if (zeta < 0) // unstable
    {
        x = sqrt(sqrt(1.0 - BETA_U * zeta));

        switch (code)
        {
            case SM:
                result = 2.0 * log((1.0 + x) / 2.0) + log((1.0 + x * x) / 2.0) -
                    2.0 * atan(x) + M_PI_2;
                break;

            case SH:
            case SV:
                result = 2.0 * log((1.0 + x * x) / 2.0);
                break;

            default: // shouldn't reach
                CRHMException TExcept("psi-function code not of these: SM, SH, SV", TExcept::TERMINATE);
                LogError(TExcept);
        }
    }
    else //Zeta == 1, neutral
    {
        result = 0.0;
    }

    return (result);
}



double ClassCanSnobalBase::sati(double  tk) { //* air temperature (K)

    double  l10;
    double  x;

    if (tk <= 0.0) {
        CRHMException TExcept("sati temperature <= 0.0", TExcept::TERMINATE);
        LogError(TExcept);
        //            tk = FREEZE + 0.01;
    }

    if (tk > FREEZE) {
        x = satw(tk);
        return(x);
    }

    errno = 0;
    l10 = log(1.e1);

    x = pow(1.e1, -9.09718 * ((FREEZE / tk) - 1.0) - 3.56654 * log(FREEZE / tk) / l10 +
        8.76793e-1 * (1.0 - (tk / FREEZE)) + log(6.1071) / l10);

    if (errno) {
        CRHMException TExcept("sati: bad return from log or pow", TExcept::TERMINATE);
        LogError(TExcept);
    }

    return(x * 1.e2);
}
/* ----------------------------------------------------------------------- */

double ClassCanSnobalBase::ssxfr(
    double	k1,	/* layer 1's thermal conductivity (J / (m K sec))  */
    double	k2,	/* layer 2's    "         "                        */
    double	t1,	/* layer 1's average layer temperature (K)	   */
    double	t2,	/* layer 2's    "      "        "         	   */
    double	d1,     /* layer 1's thickness (m)			   */
    double	d2)     /* layer 2's    "       "			   */
{
    double	xfr;

    xfr = 2.0 * (k1 * k2 * (t2 - t1)) / ((k2 * d1) + (k1 * d2));

    return (xfr);
}
/* ----------------------------------------------------------------------- */

double ClassCanSnobalBase::heat_stor(
    double	cp,	/* specific heat of layer (J/kg K) */
    double	spm,	/* layer specific mass (kg/m^2)    */
    double	tdif)	/* temperature change (K)          */
{
    double	stor;

    stor = cp * spm * tdif;

    return (stor);
}
/* ----------------------------------------------------------------------- */

double ClassCanSnobalBase::new_tsno(
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
        if (tsno > CRHM_constants::Tm)
            tsno = CRHM_constants::Tm;
    }

    return (tsno);
}
/* ----------------------------------------------------------------------- */

double ClassCanSnobalBase::efcon(
    double	k,	/* layer thermal conductivity (J/(m K sec)) */
    double	t,	/* layer temperature (K)		    */
    double	p)	/* air pressure (Pa)  			    */
{
    double	etc;
    double	de;
    double	lh;
    double	e;
    double	q;

    // calculate effective layer diffusion(see Anderson, 1976, pg. 32)
    de = DIFFUS(p, t);

    // set latent heat from layer temp.
    if (t > FREEZE)
        lh = LH_VAP(t);
    else if (t == FREEZE)
        lh = (LH_VAP(t) + LH_SUB(t)) / 2.0;
    else
        lh = LH_SUB(t);

    // set mixing ratio from layer temp.
    e = sati(t);
    q = MIX_RATIO(e, p);

    //	calculate effective layer conductivity
    etc = k + (lh * de * q);

    return (etc);
}

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
        SS = SS + "  ta: " + FloatToStrF(ta - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
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
        SS = SS + " ta: " + FloatToStrF(ta - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
            ", ts: " + FloatToStrF(ts - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
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

    if (u < 0.5)
        u = 0.5;
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

            lo = ustar * ustar * ustar * dens / (k * g * (h / (ta * cp) + 0.61 * e));

            // friction velocity, eq. 4.34'

            ustar = k * u / (ltsm - psi(zu / lo, SM));

            // evaporative flux, eq. 4.33'

            factor = k * ustar * dens;
            e = (qa - qs) * factor * av / (ltsv - psi(zq / lo, SV));

            // sensible heat flux, eq. 4.35' with sign reversed

            h = (ta - ts) * factor * ah * cp / (ltsh - psi(za / lo, SH));

            diff = last - lo;

        } while (fabs(diff) > THRESH && fabs(diff / lo) > THRESH && ++iter < ITMAX);
    }

    xlh = LH_VAP(ts);
    if (ts <= FREEZE)
        xlh += LH_FUS(ts);

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
        SS = SS + " ta: " + FloatToStrF(ta - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
            ", ts: " + FloatToStrF(ts - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
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
