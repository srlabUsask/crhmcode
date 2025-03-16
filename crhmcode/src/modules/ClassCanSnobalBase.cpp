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

        rho_veg[hh] = 218.0; // change 10/18/16
        h2o_sat_veg[hh] = 0.0;


        snow_h2o_veg[hh] = 0.0;
        liq_h2o_veg[hh] = 0.0;
        m_s_veg[hh] = snow_h2o_veg[hh] + liq_h2o_veg[hh];

        cc_s_veg[hh] = 0.0;

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
        Qe_ice_sphere[hh] = 0.0;
        Qh_ice_sphere[hh] = 0.0;

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

    delmelt_veg[hh] = 0.0;
    delta_Q_veg[hh] = 0.0;

    // Is there a vegsnowcover?

    vegsnowcover[hh] = snow_h2o_veg[hh] > 0.0;

    // Calculate energy transfer terms

    if (!_e_bal_veg())
        return 0;

    // Adjust mass and calculate runoff

    _mass_bal();

    //  Update the averages for the energy terms and the totals for mass changes since the last output.

    // increment time
    current_time[hh] += time_step[hh];

    //  update interval values

    delmelt_veg_int[hh] += delmelt_veg[hh];
    delsub_veg_int[hh] += delsub_veg[hh];
    delevap_veg_int[hh] += delevap_veg[hh];
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
**      int _e_bal_veg(void) -- calculates point energy budget for the vegsnowcover
**
** DESCRIPTION
**      Calculates point energy budget for 2-layer vegsnowcover and adjusts the canopy snowpack temperature.
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

int ClassCanSnobalBase::_e_bal_veg(void)
{

    if (vegsnowcover[hh] || liq_h2o_veg[hh] > 0.0)
    {
        double resid;               // left over energy not accounted for in the ebal
        double Tstep = 0.25;         // increment to adjust canopy snow temperature by
        int niter = 1;
        int max_iter = 100;
        double T0_s_veg = T_s_veg[hh];

        do
        { /* iterate on canopy snow e bal */

            // calculate radiative terms
            _net_rad_veg();

            // calculate latent and sensible heat transfer
            if (!init_turb_transfer())
                return 0;

            // calculate advection
            _advec_veg();

            // veg snowpack energy budget
            delta_Q_veg[hh] = ((T_s_veg[hh] - T0_s_veg) * m_s_veg[hh] * CP_ICE(T_s_veg[hh])) / time_step[hh];

            resid = Qn_veg[hh] + Qh_veg[hh] + Ql_veg[hh] + Qp[hh] - delta_Q_veg[hh]; 

            // Check energy budget residual and if too large adjust canopy snow temperature. Temp adjust algorithm below is after CLASS.
            if (fabs(resid) < 5.0 || fabs(Tstep) < 1e-2)
            {
                break;
            }

            if (niter == 1)
            {
                if (resid > 0.0)
                { // we overshot the canopy snow surface temperature so try reducing it 1 k step at a time
                    T_s_veg[hh] += Tstep;
                }
                else
                {
                    T_s_veg[hh] -= Tstep;
                }
            }
            else
            {
                if ((resid > 0.0 && Tstep < 0.0) || (resid < 0.0 && Tstep > 0.0))
                {
                    Tstep = -Tstep / 2.0;
                }
                T_s_veg[hh] += Tstep;
            }
            niter += 1;

            // if (std::abs(T_s_veg[hh] - FREEZE) < 1.0E-6) // likely uneeded but is in CLASS
            // {
            // T_s_veg[hh] = FREEZE;
            // }

            // Check if max iterations were reached
            if (niter >= max_iter)
            {
                string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow);
                string SS = D + "hh " + to_string(hh);

                CRHMException TExcept2(SS.c_str(), TExcept::WARNING);
                LogError(TExcept2);

                CRHMException TExcept("Warning: Max iterations reached in canopy snow energy balance", TExcept::WARNING);
                LogError(TExcept);

                Qe_ice_sphere[hh] = 0.0;
            }
        } while (niter < max_iter); // breaks inside based on resid or temp step

        if (niter > max_iter)
        { // solution has not been reached, set canopy temp equal to air temperature
            T_s_veg[hh] = T_a[hh];

            Qn_veg[hh] = 0.0;

            Qh_veg[hh] = Ql_veg[hh] = qsub_veg[hh] = 0.0;

            Qp[hh] = 0.0;

            delta_Q_veg[hh] = 0.0;
        }
    }
    else
    {
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
**	temperature. This is relative to a snow clump sitting on the canopy.
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
    O_LW_cpysnow[hh] = 2.0 * SNOW_EMISSIVITY * STEF_BOLTZ * pow(T_s_veg[hh], 4.0f); // since we include incoming from atmosphere and from branch elements we multiply by two
    I_LW_cpy_2_cpy[hh] = CAN_EMISSIVITY*(1.0 - SNOW_EMISSIVITY)*O_LW_cpysnow[hh]; // canopy longwave reflected from ground and absorbed by the canopy (W m-2)

    // TODO move below to a function
    double SW_ext_in_canopy = S_n[hh] * (1-Albedo_veg[hh] - Tauc[hh]*(1-Albedo_surface[hh])); // Eq 6. from Pomeroy et al., (2009)
    I_LW_cpy[hh] = (CAN_EMISSIVITY * STEF_BOLTZ * pow(T_a[hh], 4.0f)) + SW_to_LW_fn[hh] * SW_ext_in_canopy; // Longwave emission from the canopy as in Pomeroy et al., (2009) Eq 10 but modified relative to calculate just the canopy emission assuming canopy is at air temperature at night
    Qn_veg[hh] = (S_n[hh]*(1-Albedo_vegsnow[hh])) + (I_lw[hh] + I_LW_cpy_2_cpy[hh] + I_LW_cpy[hh] - O_LW_cpysnow[hh]); // assumes canopy snow is getting full atmosphere input of LW on top and LW from canopy on branch may need to adjust contribution on top to also include some canopy emission
}

/*
** NAME
**      int init_turb_transfer(void) -- calculates turbulent transfer at a point within the canopy
**
** DESCRIPTION
**      Calculates point turbulent transfer (Qh_veg and Ql_veg) for a 1-layer
**	vegsnowcover. Ignores stability corrections since within the roughness elements.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

int ClassCanSnobalBase::init_turb_transfer(void) {

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

    if (calc_turb_transfer(P_a[hh], T_a[hh], rel_z_T, T_s_veg[hh], e_a_fix, e_s, u[hh], rel_z_u, Qh_veg[hh], Ql_veg[hh]))
        return 1; // !!!!!TB

    return 1;
}

/* ----------------------------------------------------------------------- */

int ClassCanSnobalBase::calc_turb_transfer(
    double press, // aiFr pressure (Pa)
    double ta,    // air temperature (K) at height za
    double tz,    // height of air temp measurement (m)
    double ts,    // surface temperature (K)
    double ea,    // vapor pressure (Pa) at height zq
    double es,    // vapor pressure (Pa) at surface
    double u,     // wind speed (m/s) at height zu
    double uz,    // height of wind speed measurement (m)

    // output variables

    double &CRHM_h, // sens heat flux (+ to surf) (W/m^2)
    double &CRHM_le // latent heat flux (+ to surf) (W/m^2)
)
{
    double h = 0; // sens heat flux (+ to surf) (W/m^2)
    double e = 0; // mass flux (+ to surf) (kg/m^2/s)
    double qa;    // specific humidity at height zq
    double qs;    // specific humidity at surface
    double dens;  // air density (kg/m3)

    double Nr;                      // Reynolds number
    double NuSh;                    // Nusselt number (-)
    double u_veg_ht;                // wind speed at canopy top
    double u_veg_mid;                // wind speed at mid canopy
    double z_veg_u;                   // height of within mid canopy wind speed (m)   
    double D;                       // diffusivity of water vapour in still air (m^2/s)
    const double KinVisc = 1.88E-5; /* Kinematic viscosity of air (Sask. avg. value) */
    const double ks = 0.0114;       // snow shape coefficient for jack pine
    const double Fract = 0.37;      // fractal dimension of intercepted snow
    double Ce;                      // canopy fullness index to represent how exposed snow is for sublimation, more sublimation for less snow in the canopy
    const double Radius = 0.0005;   /* Ice sphere radius, metres */
    double dice = 900.0;            // density of ice from canopy module
    double ra;                      // aerodynamic roughness (s/m)
    double ri;                      // resistance of moisture transfer from intercepted snow (s/m)
    double z_0;                     // roughness length
    int ier = 0;                    // return error code

    // check for bad input

    // temperatures are Kelvin
    if (ta <= 0 || ts <= 0)
    {
        CRHMException TExcept("temps not K", TExcept::TERMINATE);
        LogError(TExcept);
        ier = -2;
        return (ier);
    }

    // pressures must be positive
    if (ea <= 0 || es <= 0 || press <= 0 || ea >= press || es >= press)
    {

        string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow);
        string SS = D + "hh " + to_string(hh) + " 'calc_turb_transfer' " + ". Qh_veg: " + FloatToStrF(h, TFloatFormat::ffFixed, 10, 4) + " le: " + FloatToStrF(e, TFloatFormat::ffFixed, 10, 4);
        SS = SS + " ta: " + FloatToStrF(ta - FREEZE, TFloatFormat::ffFixed, 10, 4) +
             ", ts: " + FloatToStrF(ts - FREEZE, TFloatFormat::ffFixed, 10, 4) +
             ", ea: " + FloatToStrF(ea, TFloatFormat::ffFixed, 10, 4) +
             ", es: " + FloatToStrF(es, TFloatFormat::ffFixed, 10, 4) +
             ", u:  " + FloatToStrF(u, TFloatFormat::ffFixed, 10, 4) +
             ", m_s_veg:  " + FloatToStrF(m_s_veg[hh], TFloatFormat::ffFixed, 10, 4);

        CRHM_le = 0.0; // addition TB 09/23/14
        CRHM_h = 0.0;

        CRHMException TExcept2(SS.c_str(), TExcept::WARNING);
        LogError(TExcept2);

        // Manishankar made this change to keep the program running.
        // CRHMException TExcept("calc_turb_transfer: pressures must be positive", TERMINATE);
        CRHMException TExcept("calc_turb_transfer: pressures must be positive", TExcept::WARNING);
        LogError(TExcept);

        ier = -2;
        return (ier);
    }

    // vapor pressures can't exceed saturation if way off stop
    if ((es - 25.0) > sati(ts) || (ea - 25.0) > satw(ta))
    {
        CRHMException TExcept("calc_turb_transfer: vapor pressures can't exceed saturation", TExcept::TERMINATE);
        LogError(TExcept);
        ier = -2;
        return (ier);
    }
    // else fix them up
    if (es > sati(ts))
    {
        es = sati(ts);
    }
    if (ea > satw(ta))
    {
        ea = satw(ta);
    }

    if (u < 0.1) // mod by AC
        u = 0.1;
    else if (u > 15)
        u = 15;

    D = 2.06E-5 * pow(T_a[hh] / 273.15, 1.75);
    // TODO at plot scale eventualy changed from observed wind to simulated
    // z_veg_u = Ht[hh]*(2.0/3.0);
    // adst_wind_cpy_top(Ht[hh], u, z_u[hh], u_veg_ht);
    // cionco_canopy_wind_spd(Ht[hh], u_veg_ht, z_veg_u, u_veg_mid);
    Nr = 2 * Radius * u / KinVisc; // TODO update to use within canopy wind speed
    NuSh = 1.79 + 0.606 * sqrt(Nr);

    // air density at press, virtual temp of geometric mean of air and surface
    dens = GAS_DEN(press, MOL_AIR, VIR_TEMP(sqrt(ta * ts), sqrt(ea * es), press));

    // convert vapor pressures to specific humidities, to absolute handled within the Qe calc
    qa = SPEC_HUM(ea, press);
    qs = SPEC_HUM(es, press);

    // calculates how exposed canopy snow is to the atmosphere based on the fullness of the canopy, more exposed with less snow as more gaps / surface area
    if ((snow_h2o_veg[hh] / Lmax[hh]) <= 0.0) // Using Lmax instead of Lstar as gives more appropriate index of canopy fullness
        Ce = 0.07;
    else
        Ce = ks * pow((snow_h2o_veg[hh] / Lmax[hh]), -Fract); // Ce is higher when the canopy is less full with snow as more of it is exposed, TODO maybe limit snow canopy fraction to 1.0 also need to reconsider Lstar

    // ra = 1 / (u_veg_mid * VON_KARMAN * VON_KARMAN) * log(z_veg_u / Z_0_cansnow[hh]) * log(z_veg_u / Z_0_cansnow[hh]); // Eq. 6 from Pomeroy 2016, TODO switch to adjusted wind for increased applicability
    ra = 1 / (u * VON_KARMAN * VON_KARMAN) * log(tz / Z_0_cansnow[hh]) * log(tz / Z_0_cansnow[hh]); // Eq. 6 from Pomeroy 2016

    ri = 2.0 * dice * Radius * Radius / (3.0 * Ce * m_s_veg[hh] * D * NuSh); // Eq. 28 from Essery et al., 2003

    CRHM_le = (dens / (ra + ri)) * (qa - qs) * LH_SUB(T_s_veg[hh]); // Eq. 29 from Essery et al., 2003
    CRHM_h = (dens / ra) * CP_AIR * (T_a[hh] - T_s_veg[hh]); // Eq. 4 Essery et al., 2003 and Pomeroy et al., 2016

    return (ier);
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

    // calculate runoff of liquid water intercepted in the canopy */

    _runoff_veg();

    // adjust layer temps if there was a vegsnowcover at start of the
    //   timestep and there's still snow on the ground

    if(snow_h2o_veg[hh] > 0.0){
        vegsnowcover[hh] = 1;
        T_s_veg[hh] = new_tsno_veg(m_s_veg[hh], T_s_veg[hh], cc_s_veg[hh]);
    } else {
        vegsnowcover[hh] = 0;
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

// If no snow in the canopy, then just exit.

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
**      void _mass_unld(void) -- adjust the canopy snowpack's snow storage due to mass unloading of snow liquid water is handled seperately under runoff
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

    if (!vegsnowcover[hh]) { // no snow in the canopy exit early
        delunld_wind[hh] = 0.0;
        delunld_melt[hh] = 0.0;
        delunld_subl[hh] = 0.0;
        return;
    }

    // check maximum canopy snow load spill what is overflowing
    if (snow_h2o_veg[hh] > Lmax[hh])
    {
        delunld[hh] = snow_h2o_veg[hh] - Lmax[hh];
    }

    // melt induced mass unloading of solid snow based on ratio relative to canopy snowmelt similar method
    // to Andreadis et al., (2009) based on Storck's measurements
    delunld_melt[hh] = delmelt_veg[hh] * unld_to_melt_ratio[hh];


    // mass unloading due to sublimation first suggested in JM's thesis
    if(qsub_veg[hh] < 0.0){
        delunld_subl[hh] = -qsub_veg[hh] * unld_to_subl_ratio[hh]; // if sublimation rate is negative wrt the canopy then apply sublimation based unloading (switch the sign of qsub_veg too as this is how it was parameterized)
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
        double d0_wind = 0.5791121;  // displacement height observed at sparse forest around Fortress Forest Tower
        double z0m_wind = 0.4995565; // roughness length observed at above site

        // wind speed for wind induced unloading at 1/2 canopy height
        if ((Ht[hh] / 2 - d0_wind) > z0m_wind)
        {
            double Ustar = u[hh] * PBSM_constants::KARMAN / (log((z_u[hh] - d0_wind) / z0m_wind));
            u_mid = Ustar / PBSM_constants::KARMAN * log((Ht[hh] / 2 - d0_wind) / z0m_wind);
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
**      treats snow intercepted in the canopy using Pomeroy 1998 and liquid/ice as
**      in snobal.
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
    qsub_veg[hh] = Ql_veg[hh] / LH_SUB(T_s_veg[hh]);
    delsub_veg[hh] = qsub_veg[hh] * time_step[hh];

    // Apply mass changes based on the presence of snow or liquid water
    if (vegsnowcover[hh]) {
        // Snow is present in the canopy; modify snow water equivalent
        snow_h2o_veg[hh] += delsub_veg[hh];
        if (snow_h2o_veg[hh] < 0.0) {
            snow_h2o_veg[hh] = 0.0;
        }
    } 

    if (liq_h2o_veg[hh] > 0.0){
        // liquid water is present; modify liquid water content

         if (inhibit_evap[hh] == 0)
        { // use Granger when no snowcover
          if (liq_h2o_veg[hh] >= hru_evap[hh] * Cc[hh])
          {                                         // (evaporation in mm)
            delevap_veg[hh] = hru_evap[hh] * Cc[hh]; //
            liq_h2o_veg[hh] -= hru_evap[hh] * Cc[hh];
          }
          else
          {
            delevap_veg[hh] = liq_h2o_veg[hh];
            liq_h2o_veg[hh] = 0.0;
          }
        }
        else
        {                                                            // use Priestley-Taylor when snowcover
          double Q = S_n[hh] * 86400 / Global::Freq / 1e6 / lambda(T_a[hh]); // convert w/m2 to mm/m2/int

          if (S_n[hh] > 0.0)
            Pevap[hh] = 1.26 * delta(T_a[hh]) * Q / (delta(T_a[hh]) + gamma(P_a[hh], T_a[hh]));
          else
            Pevap[hh] = 0.0;

          if (liq_h2o_veg[hh] >= Pevap[hh] * Cc[hh])
          {                                      // (evaporation in mm)
            delevap_veg[hh] = Pevap[hh] * Cc[hh]; // check
            liq_h2o_veg[hh] -= Pevap[hh] * Cc[hh];
          }
          else
          {
            delevap_veg[hh] = liq_h2o_veg[hh]; // check
            liq_h2o_veg[hh] = 0.0;
          }
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
        m_s_veg[hh] = liq_h2o_veg[hh] + snow_h2o_veg[hh]; 

    } else {
        deldrip_veg[hh] = 0.0;
    }
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

/*
** NAME
**      int init_subl_ice_sphere -- calculates potential sublimation of an ice sphere (s^-1)
**
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
** 
*/

int ClassCanSnobalBase::init_subl_ice_sphere(void) {

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

    if (subl_ice_sphere(e_a_fix, e_s, T_a[hh], T_s_veg[hh], u[hh], P_a[hh]))
        return 1; // !!!!!TB

    return 0;
}

/* ----------------------------------------------------------------------- */

/*
** NAME subl_ice_sphere -- Sublimation rate from an ice sphere in the canopy (negative for sublimation of particle)
**
** DESCRIPTION -- Based on Eq. 45 from Pom 1995, requires iteration on canopy snow surface temp. Differs from Pom 1998 which is an analytical solution.
**
** RETURN -- 1 if ice bulb ebal convergence is met, 0 otherwise. Values are used for while loop on upper level.
**
** 
** 
*/
int ClassCanSnobalBase::subl_ice_sphere(
    double	ea,	// vapor pressure (Pa) at height zq
    double  es, // vapour pressure (Pa) at the canopy snow surface
    double	ta,	// air temperature (K) at height za
    double	ts,	// surface temperature (K)
    double  u, // wind speed (m/s) at height zu
    double	press)	// aiFr pressure (Pa)

{
    const double Radius = 0.0005;   /* Ice sphere radius, metres */
    const double KinVisc = 1.88E-5; /* Kinematic viscosity of air (Sask. avg. value) */
    double dice = 900.0;            // density of ice from canopy module
    double D;                       // diffusivity of water vapour in still air (m^s/s)
    double Nr;                      // Reynolds number
    double NuSh;                    // Nusselt number (-)
    double Lamb;                    // thermal conductivity of atmosphere
    double qa;                      // specific humidity at height zq
    double qs;                      // specific humidity at surface
    double dens;                    // air density (Pa)
    double u_veg_ht;                // wind speed at canopy top
    double QnetStar;                // net radiation to the ice sphere
    double resid;                   // energy balance residual relative to an ice sphere (j/s)
    double convergence_check = 0; //

    D = 2.06E-5 * pow(ta / 273.15, 1.75);
    adst_wind_cpy_top(Ht[hh], u, z_u[hh], u_veg_ht);
    Nr = 2 * Radius * u_veg_ht / KinVisc;
    NuSh = 1.79 + 0.606 * sqrt(Nr);
    Lamb = 0.00063*(ta)+0.0673;


    // air density at press, virtual temp of geometric mean of air and surface
    dens = GAS_DEN(press, MOL_AIR, VIR_TEMP(sqrt(ta * ts), sqrt(ea * es), press));

    // convert vapor pressures to specific humidities and then to absolute
    qa = SPEC_HUM(ea, press) * dens;
    qs = SPEC_HUM(es, press) * dens;

    // pressures must be positive
    if (ea <= 0 || es <= 0 || press <= 0 || ea >= press || es >= press)
    {

        string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow);
        string SS = D + "hh " + to_string(hh);

        CRHMException TExcept2(SS.c_str(), TExcept::WARNING);
        LogError(TExcept2);

        // Manishankar made this change to keep the program running.
        // CRHMException TExcept("calc_turb_transfer: pressures must be positive", TERMINATE);
        CRHMException TExcept("calc_turb_transfer: pressures must be positive", TExcept::WARNING);
        LogError(TExcept);
        return (0);
    }

    Qe_ice_sphere[hh] = (2.0 * M_PI * Radius * D * NuSh * (qa - qs)) * LH_SUB(ts);                     // Latent Heat Energy flux (j/s) relative to the ice sphere (negative for sublimation of particle).
    Qh_ice_sphere[hh] = 2.0 * M_PI * Radius * Lamb * NuSh * (ta - ts);                                 // Sensible heat transfer (j/s), +to surface

    QnetStar = M_PI * Radius * Radius * Qn_veg[hh];

    resid = QnetStar + Qe_ice_sphere[hh] + Qh_ice_sphere[hh];

    if (fabs(resid) < 1e-3 || fabs(Tstep_ice_sphere[hh]) < 1e-2)
    {                         
        convergence_check = 1; // ebal is satisfied while loop will exit on higher level
    }
    else
    { // ebal is NOT satisfied while loop will continue on higher level
        if (niter_ice_sphere[hh] == 1)
        {
            if (resid > 0.0)
            { // we overshot the canopy snow surface temperature so try reducing it 1 k step at a time
                T_s_veg[hh] += Tstep_ice_sphere[hh];
            }
            else
            {
                T_s_veg[hh] -= Tstep_ice_sphere[hh];
            }
        }
        else
        {
            if ((resid > 0.0 && Tstep_ice_sphere[hh] < 0.0) || (resid < 0.0 && Tstep_ice_sphere[hh] > 0.0))
            {
                Tstep_ice_sphere[hh] = -Tstep_ice_sphere[hh] / 2.0;
            }
            T_s_veg[hh] += Tstep_ice_sphere[hh];
        }
    }

    return (convergence_check);
}
