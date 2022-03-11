//created by Manishankar Mondal

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

using namespace CRHM;

void ClassSnobalBase::init(void) {

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

        T_s[hh] = -75.0; // temperatures inside Snobal model are K
        T_s_0[hh] = -75.0;
        T_s_l[hh] = -75.0;

        rho[hh] = 218.0; // change 10/18/16
        h2o_sat[hh] = 0.0;

        z_s[hh] = 0.0;
        z_s_0[hh] = 0.0;
        z_s_l[hh] = 0.0;

        m_s[hh] = 0.0;
        m_s_0[hh] = 0.0;
        m_s_l[hh] = 0.0;

        cc_s[hh] = 0.0;
        cc_s_0[hh] = 0.0;
        cc_s_l[hh] = 0.0;

        h2o[hh] = 0.0;
        h2o_max[hh] = 0.0;
        h2o_total[hh] = 0.0;
        melt[hh] = 0.0;
        z_snow[hh] = 0.0;
        ro_predict[hh] = 0.0;
        T_snow[hh] = 0.0;
        T_rain[hh] = 0.0;

        layer_count[hh] = 0;
        isothermal[hh] = 0;
        snowcover[hh] = 0;
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
        m_drift_cum[hh] = 0.0;
        m_subl_cum[hh] = 0.0;
        cumsnowmelt[hh] = 0.0;

        L_v_E[hh] = 0.0;
        E[hh] = 0.0;
        H[hh] = 0.0;
        G[hh] = 0.0;
        M[hh] = 0.0;
        R_n[hh] = 0.0;
        delta_Q[hh] = 0.0;
        delta_Q_0[hh] = 0.0;

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

void ClassSnobalBase::finish(bool good) { // only required for local storage and final output

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (Snobal)' m_precip_cum    (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_precip_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Snobal)' m_rain_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_rain_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Snobal)' m_snow_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_snow_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Snobal)' m_drift_cum     (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_drift_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Snobal)' m_subl_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), -m_subl_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Snobal)' SWE             (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_s[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
        LogMessageA(hh, string("'" + Name + " (Snobal)' E_s_cum         (mm) (mm*hru) (mm*hru/basin): ").c_str(), E_s_cum[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Snobal)' cumsnowmelt     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowmelt[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Snobal)' melt_direct_cum (mm) (mm*hru) (mm*hru/basin): ").c_str(), melt_direct_cum[hh], hru_area[hh], basin_area[0]);
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

void ClassSnobalBase::init_snow(void)
{
    double	rho_dry;	// snow density without H2O

    m_s[hh] = rho[hh] * z_s[hh];

    _calc_layers();

    if (layer_count[hh] == 0) {

        // If mass > 0, then it must be below threshold. So turn this little bit of mass into water.

        if (m_s[hh] > 0.0) {
            h2o_total[hh] += m_s[hh];
            melt_direct_int[hh] += m_s[hh];
        }

        rho[hh] = 0.0;
        m_s[hh] = cc_s[hh] = 0.0;
        m_s_0[hh] = cc_s_0[hh] = 0.0;
        m_s_l[hh] = cc_s_l[hh] = 0.0;

        // Note: Snow temperatures are set to MIN_SNOW_TEMP (as degrees K) instead of 0 K to keep quantization range in output image smaller.

        T_s[hh] = T_s_0[hh] = T_s_l[hh] = MIN_SNOW_TEMP + FREEZE;
        h2o_vol[hh] = h2o[hh] = h2o_max[hh] = h2o_sat[hh] = 0.0;
    }
    else {

        // Compute specific mass for each layer.

        _layer_mass();

        cc_s_0[hh] = _cold_content(T_s_0[hh], m_s_0[hh]);

        if (layer_count[hh] == 2) {
            cc_s_l[hh] = _cold_content(T_s_l[hh], m_s_l[hh]);
        }
        else {
            T_s_l[hh] = MIN_SNOW_TEMP + FREEZE;
            cc_s_l[hh] = 0.0;
        }

        // Compute liquid water content as volume ratio, and snow density without water.

        h2o_vol[hh] = h2o_sat[hh] * max_h2o_vol[hh];
        rho_dry = DRY_SNO_RHO(rho[hh], h2o_vol[hh]);

        // Determine maximum liquid water content (as specific mass) and the actual liquid water content (as specific mass).

        h2o_max[hh] = H2O_LEFT(z_s[hh], rho_dry, max_h2o_vol[hh]);

        h2o[hh] = h2o_sat[hh] * h2o_max[hh];
        stop_no_snow[hh] = 0; //????
    }
}

/*
** NAME
**      void _calc_layers(void) -- determine # of layers in snowcover and their depths
**
** DESCRIPTION
**      This routine determines the # of layers in the snowcover based its
**	depth and mass.  Usually, there are are 2 layers: the surface (active)
**	and the lower layer.  The depth of the surface layer is set to the
**	maximum depth for the surface layer (variable "max_z_s_0").  The
**	remaining depth constitutes the lower layer.  The routine checks
**	to see if the mass of this lower layer is above the minium threshold
**	(i.e., the mass threshold for the small run timestep).  If not,
**	the surface layer is the whole snowcover, and there's no lower
**	layer.
**
** GLOBAL VARIABLES READ
**	m_s
**	max_z_s_0
**	rho[hh]
**	tstep_info
**	z_s
**
** GLOBAL VARIABLES MODIFIED
**	layer_count
**	z_s
**	z_s_0
**	z_s_l
*/

void ClassSnobalBase::_calc_layers(void)
{
    if (m_s[hh] <= tstep_info[hh][SMALL_TSTEP].threshold) {

        // Less than minimum layer mass, so treat as no snowcover.

        layer_count[hh] = 0;
        z_s[hh] = z_s_0[hh] = z_s_l[hh] = 0.0;
    }
    else if (z_s[hh] < max_z_s_0[hh]) {

        // Not enough depth for surface layer and the lower layer, so just 1 layer: surface layer.

        layer_count[hh] = 1;
        z_s_0[hh] = z_s[hh];
        z_s_l[hh] = 0.0;
    }
    else {

        // Enough depth for both layers.

        layer_count[hh] = 2;
        z_s_0[hh] = max_z_s_0[hh];
        z_s_l[hh] = z_s[hh] - z_s_0[hh];

        // However, make sure there's enough MASS for the lower layer.  If not, then there's only 1 layer.

        if (z_s_l[hh] * rho[hh] < tstep_info[hh][SMALL_TSTEP].threshold) {
            layer_count[hh] = 1;
            z_s_0[hh] = z_s[hh];
            z_s_l[hh] = 0.0;
        }
    }
}

/*
** NAME
**      void _layer_mass(void) -- calculate the specific mass for each snow layer
**
** DESCRIPTION
**      This routine computes the specific mass for each snow layer in
**	the snowcover.  A layer's mass is based its depth and the
**	average snowcover density.
**
** GLOBAL VARIABLES READ
**	layer_count
**	rho
**	z_s_0
**	z_s_l
**
** GLOBAL VARIABLES MODIFIED
**	m_s_0
**	m_s_l
*/

void ClassSnobalBase::_layer_mass(void)
{
    if (layer_count[hh] == 0) {
        m_s_0[hh] = 0.0;
        m_s_l[hh] = 0.0;
    }
    else {  // layer_count is 1 or 2
        m_s_0[hh] = rho[hh] * z_s_0[hh];
        if (layer_count[hh] == 2)
            m_s_l[hh] = rho[hh] * z_s_l[hh];
        else
            m_s_l[hh] = 0.0;
    }
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

double ClassSnobalBase::_cold_content(
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
**	'precip_now' used be true.  Furthermore, the routine requires
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
**	layer_count
**	m_pp_data
**	m_rain_data
**	m_snow_data
**	more_pr_recs
**	precip_data
**	S_n
**	T_a
**	T_g
**	tstep_info
**	u
**	z_snow_data
**
** GLOBAL VARIABLES MODIFIED
**	precip_now
*/

void ClassSnobalBase::do_data_tstep(void) {

    int level; // loop index

  //  Copy values from first input record into global variables.

    S_n[hh] = input_rec1[hh].S_n;
    I_lw[hh] = input_rec1[hh].I_lw;
    T_a[hh] = input_rec1[hh].T_a;
    e_a[hh] = input_rec1[hh].e_a;
    u[hh] = input_rec1[hh].u;
    T_g[hh] = input_rec1[hh].T_g;
    F_g[hh] = input_rec1[hh].F_g;

    // Compute deltas for the climate input parameters over the CRHM data timestep.

    input_deltas[hh][DATA_TSTEP].S_n = input_rec2[hh].S_n - input_rec1[hh].S_n;
    input_deltas[hh][DATA_TSTEP].I_lw = input_rec2[hh].I_lw - input_rec1[hh].I_lw;
    input_deltas[hh][DATA_TSTEP].T_a = input_rec2[hh].T_a - input_rec1[hh].T_a;
    input_deltas[hh][DATA_TSTEP].e_a = input_rec2[hh].e_a - input_rec1[hh].e_a;
    input_deltas[hh][DATA_TSTEP].u = input_rec2[hh].u - input_rec1[hh].u;
    input_deltas[hh][DATA_TSTEP].T_g = input_rec2[hh].T_g - input_rec1[hh].T_g;
    input_deltas[hh][DATA_TSTEP].F_g = input_rec2[hh].F_g - input_rec1[hh].F_g;

    // If there is precipitation, then compute the amount of rain & snow in it.

    precip_info[hh]->m_drift = m_drift[hh];
    precip_info[hh]->m_subl = m_subl[hh];

    if (precip_now[hh]) {
        precip_info[hh]->m_pp = m_precip[hh];
        precip_info[hh]->m_snow = m_snow[hh];
        precip_info[hh]->m_rain = m_rain[hh];

        if (precip_info[hh]->m_snow > 0.0)
            precip_info[hh]->z_snow = z_snow[hh];
        else
            precip_info[hh]->z_snow = 0.0;

        // Mixed snow and rain

        if ((precip_info[hh]->m_snow > 0.0) && (precip_info[hh]->m_rain > 0.0)) {
            T_snow[hh] = FREEZE;
            h2o_sat_snow[hh] = 1.0;
            T_rain[hh] = T_pp[hh];
        }

        // Snow only

        else if (precip_info[hh]->m_snow > 0.0) {
            if (T_pp[hh] < FREEZE) {	/* Cold snow */
                T_snow[hh] = T_pp[hh];
                h2o_sat_snow[hh] = 0.0;
            }
            else {				/* Warm snow */
                T_snow[hh] = FREEZE;
                h2o_sat_snow[hh] = 1.0;
            }
        }

        // Rain only

        else if (precip_info[hh]->m_rain > 0.0) {
            T_rain[hh] = T_pp[hh];
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
**	layer_count
**	precip_now
**	tstep_info
**
** GLOBAL VARIABLES MODIFIED
*/

int ClassSnobalBase::_divide_tstep(TSTEP_REC* tstep) {  // record of timestep to be divided

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
        next_lvl_deltas->T_g = curr_lvl_deltas->T_g / next_lvl_tstep->intervals;
        next_lvl_deltas->F_g = curr_lvl_deltas->F_g / next_lvl_tstep->intervals;

        next_lvl_precip->m_pp = curr_lvl_precip->m_pp / next_lvl_tstep->intervals;
        next_lvl_precip->m_rain = curr_lvl_precip->m_rain / next_lvl_tstep->intervals;
        next_lvl_precip->m_snow = curr_lvl_precip->m_snow / next_lvl_tstep->intervals;
        next_lvl_precip->m_drift = curr_lvl_precip->m_drift / next_lvl_tstep->intervals;
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
**	layer_count
**	m_s
**	m_s_0
**	m_s_l
**
** GLOBAL VARIABLES MODIFIED
*/

int ClassSnobalBase::_below_thold(double	threshold) { // current timestep's threshold for a layer's mass

    if (layer_count[hh] == 0)
        return 0;

    if (layer_count[hh] == 1)
        return (m_s[hh] < threshold);
    else  /* layer_count == 2 */
        return ((m_s_0[hh] < threshold) || (m_s_l[hh] < threshold));
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
**      	T_g
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
**	delta_Q
**	delta_Q_0
**	E_s
**	G
**	H
**	L_v_E
**	layer_count
**	M
**	melt
**	precip_now
**	R_n
**	ro_predict
**
** GLOBAL VARIABLES MODIFIED
**	current_time
**	curr_time_hrs
**	delta_Q_0_bar
**	delta_Q_bar
**	e_a
**	G_bar
**	H_bar
**	h2o_total
**	I_lw
**	L_v_E_bar
**	M_bar
**	m_precip
**	m_rain

**	m_snow
**	R_n_bar
**	S_n
**	snowcover
**	T_a
**	T_g
**	u
**	time_step
**	z_snow
*/

int ClassSnobalBase::_do_tstep(TSTEP_REC* tstep)  // timestep's record
{
    time_step[hh] = tstep->time_step;

    m_precip[hh] = precip_info[hh][tstep->level].m_pp;
    m_rain[hh] = precip_info[hh][tstep->level].m_rain;
    m_snow[hh] = precip_info[hh][tstep->level].m_snow;
    m_drift[hh] = precip_info[hh][tstep->level].m_drift;
    m_subl[hh] = precip_info[hh][tstep->level].m_subl;
    z_snow[hh] = precip_info[hh][tstep->level].z_snow;

    h2o_total[hh] = 0.0;
    melt[hh] = 0.0;

    // Is there a snowcover?

    snowcover[hh] = (layer_count[hh] > 0);

    // Calculate energy transfer terms

    if (!_e_bal())
        return 0;

    // Adjust mass and calculate runoff

    _mass_bal();

    //  Update the averages for the energy terms and the totals for mass changes since the last output.

    // increment time
    current_time[hh] += time_step[hh];

    //  update interval values

    snowmelt_int[hh] += ro_predict[hh];
    E_s_int[hh] += E_s[hh];
    E_int[hh] += E[hh];
    E_s_0_int[hh] += E_s_0[hh];
    E_s_l_int[hh] += E_s_l[hh];

    //  Update the model's input parameters

    S_n[hh] += input_deltas[hh][tstep->level].S_n;
    I_lw[hh] += input_deltas[hh][tstep->level].I_lw;
    T_a[hh] += input_deltas[hh][tstep->level].T_a;
    e_a[hh] += input_deltas[hh][tstep->level].e_a;
    u[hh] += input_deltas[hh][tstep->level].u;
    T_g[hh] += input_deltas[hh][tstep->level].T_g;
    F_g[hh] += input_deltas[hh][tstep->level].F_g;

    return 1;
}

/*
** NAME
**      int _e_bal(void) -- calculates point energy budget for 2-layer snowcover
**
** DESCRIPTION
**      Calculates point energy budget for 2-layer snowcover.
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

int ClassSnobalBase::_e_bal(void) {

    if (snowcover[hh]) {

        // calculate energy xfer terms

        // calculate net radiation

        _net_rad();

        // calculate H & L_v_E  (and E as well)

        if (!_h_le())
            return 0;

        // calculate G & G_0(conduction/diffusion heat xfr)

        if (layer_count[hh] == 1) {

            if (T_g_or_G_flux[hh])
                G[hh] = F_g[hh]; // ground flux
            else
                G[hh] = g_soil(rho[hh], T_s_0[hh], T_g[hh], z_s_0[hh], z_g[hh], P_a[hh]);

            G_0[hh] = G[hh];
        }
        else {  //  layer_count[hh] == 2

            if (T_g_or_G_flux[hh])
                G[hh] = F_g[hh]; // ground flux
            else
                G[hh] = g_soil(rho[hh], T_s_l[hh], T_g[hh], z_s_l[hh], z_g[hh], P_a[hh]);

            G_0[hh] = g_snow(rho[hh], rho[hh], T_s_0[hh], T_s_l[hh], z_s_0[hh], z_s_l[hh], P_a[hh]);
        }

        // calculate advection

        _advec();

        // sum E.B. terms

        // surface energy budget

        delta_Q_0[hh] = R_n[hh] + H[hh] + L_v_E[hh] + G_0[hh] + M[hh];

        // total snowpack energy budget

        if (layer_count[hh] == 1)
            delta_Q[hh] = delta_Q_0[hh];
        else /* layer_count == 2 */
            delta_Q[hh] = delta_Q_0[hh] + G[hh] - G_0[hh];
    }
    else {
        R_n[hh] = 0.0;

        H[hh] = L_v_E[hh] = E[hh] = 0.0;

        G[hh] = G_0[hh] = 0.0;

        M[hh] = 0.0;

        delta_Q[hh] = delta_Q_0[hh] = 0.0;
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
**	T_s_0
**
** GLOBAL VARIABLES MODIFIED
**	R_n
*/

void ClassSnobalBase::_net_rad(void)
{
    //	R_n[hh] = S_n[hh] + (SNOW_EMISSIVITY * (I_lw[hh] - STEF_BOLTZ * pow(T_s_0[hh], 4.0f)));
    R_n[hh] = S_n[hh] + (I_lw[hh] - SNOW_EMISSIVITY * STEF_BOLTZ * pow(T_s_0[hh], 4.0f)); // correction 07/17/14
}

/*
** NAME
**      int _h_le(void) -- calculates turbulent transfer at a point
**
** DESCRIPTION
**      Calculates point turbulent transfer (H and L_v_E) for a 2-layer
**	snowcover.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

int ClassSnobalBase::_h_le(void) {

    double e_s, e_a_fix;
    double sat_vp;
    double rel_z_T; // relative z_T (temperature measurement height) above snow surface
    double rel_z_u; // relative z_u (windspeed measurement height) above snow surface

// calculate saturation vapor pressure

    e_s = sati(T_s_0[hh]);

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
        rel_z_T = z_T[hh] - z_s[hh];
        if (rel_z_T < 1.0)
            rel_z_T = 1.0;
        rel_z_u = z_u[hh] - z_s[hh];
        if (rel_z_u < 1.0)
            rel_z_u = 1.0;
    }

    // calculate H & L_v_E

    if (hle1(P_a[hh], T_a[hh], T_s_0[hh], rel_z_T, e_a_fix, e_s, rel_z_T, u[hh], rel_z_u, z_0[hh], H[hh], L_v_E[hh], E[hh]))
        return 1; // !!!!!TB

    return 1;
}

double ClassSnobalBase::g_soil(
    double	rho,	// snow layer's density (kg/m^3)
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
    kcs = KTS(rho);
    k_s = efcon(kcs, tsno, pa);

    g = ssxfr(k_s, k_g, tsno, tg, ds, dg);

    return (g);
}

double ClassSnobalBase::g_snow(
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
**      This routine calculates the advected energy for a 2-layer snowcover
**	if there's precipitation for the current timestep.
**
** GLOBAL VARIABLES READ
**	m_rain
**	m_snow
**	precip_now
**	T_rain
**	T_s_0
**	T_snow
**	time_step
**
** GLOBAL VARIABLES MODIFIED
**	M
*/

void ClassSnobalBase::_advec(void) {

    if (precip_now) {
        M[hh] = (heat_stor(CP_WATER(T_rain[hh]), m_rain[hh], (T_rain[hh] - T_s_0[hh])) +
            heat_stor(CP_ICE(T_snow[hh]), m_snow[hh], (T_snow[hh] - T_s_0[hh]))) / time_step[hh];
    }
    else
        M[hh] = 0.0;
}

/*
** NAME
**      void _mass_bal(void) -- calculates point mass budget of 2-layer snowcover
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

void ClassSnobalBase::_mass_bal(void) {

    // process blowing snow event
    //  _drift();

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

    // calculate runoff, and adjust snowcover */

    _runoff();

    // adjust layer temps if there was a snowcover at start of the
    //   timestep and there's still snow on the ground

    if (snowcover[hh]) {
        if (layer_count[hh] == 1) {
            T_s_0[hh] = new_tsno(m_s_0[hh], T_s_0[hh], cc_s_0[hh]);
            T_s[hh] = T_s_0[hh];
        }
        else if (layer_count[hh] == 2) {
            if (isothermal[hh])
                T_s[hh] = T_s_l[hh] = T_s_0[hh] = FREEZE;
            else {
                T_s_0[hh] = new_tsno(m_s_0[hh], T_s_0[hh], cc_s_0[hh]);
                T_s_l[hh] = new_tsno(m_s_l[hh], T_s_l[hh], cc_s_l[hh]);
                T_s[hh] = new_tsno(m_s[hh], T_s[hh], cc_s[hh]);
            }
        }
    }
}

/*
** NAME
**      void _time_compact(void) -- compact snowcover by gravity over time
**
** DESCRIPTION
**	This routine "ages" the snowcover by accounting for the compaction
**	or densification by gravity as time passes.  The snowcover's
**	density is increased using the following "half-saturation" function:
**
**		rho(time) = A / (1 + B/time)
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
**	rho		|	       *
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
**	rho
**	(and those variables modified by "_new_density")
**
*/

//  Time when half "saturation", i.e., maximum density is reached * (seconds).
// *  (864000 = 10 days * 24 hours/day * 60 mins/hr * 60 secs/min)

void ClassSnobalBase::_time_compact(void)
{
    const double A = 350; // Maximum density due to compaction by gravity (kg/m^2).
    const double B = 86400;

    double	time;	/* point on time axis corresponding to current density */
  // If the snow is already at or above the maximum density due compaction by gravity, then just leave.

    if (!snowcover[hh] || rho[hh] > A || m_s[hh] <= 0.0)
        return;

    // Given the current density, determine where on the time axis we are (i.e., solve the function above for "time").

    if (rho[hh] > 349)
        rho[hh] = 349;

    time = B / (A / rho[hh] - 1);

    // Move along the time axis by the time step, and calculate the density at this new time.

    rho[hh] = A / (1 + B / (time + time_step[hh]));

    // Adjust the snowcover for this new density.

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
**	snowcover.
**
** GLOBAL VARIABLES READ
**	h2o_sat_snow
**	m_rain
**	m_precip
**	max_h2o_vol
**	precip_now
**	rho_snow
**	snowcover
**	T_snow
**	z_snow
**
** GLOBAL VARIABLES MODIFIED
**	h2o
**	h2o_sat
**	h2o_total
**	rho
**	T_s
**	T_s_0
**	z_s[hh]
**	(and those variables modified by "_adj_snow" and "_init_snow")
*/

void ClassSnobalBase::_precip(void)
{
    double	h2o_vol_snow;	// liquid water content of new snowfall as volume ratio

    if (precip_now[hh]) {
        if (snowcover[hh]) {

            // Adjust snowcover's depth and mass by snowfall's depth and the total precipitation mass.

            _adj_snow(z_snow[hh], m_precip[hh]);


            // Determine the additional liquid water that's in the snowfall,
            //   and then add its mass to liquid water in the whole snowcover.

            h2o_vol_snow = h2o_sat_snow[hh] * max_h2o_vol[hh];
            h2o[hh] += H2O_LEFT(z_snow[hh], rho_snow[hh], h2o_vol_snow);
        }
        else { // no snowcover

    // Use snowfall, if any, to setup a new snowcover.

            if (m_snow[hh] > 0.0) {
                z_s[hh] = z_snow[hh];
                rho[hh] = rho_snow[hh];
                T_s[hh] = T_snow[hh];
                T_s_0[hh] = T_snow[hh];
                T_s_l[hh] = T_snow[hh];
                h2o_sat[hh] = h2o_sat_snow[hh];

                init_snow();
            }
        }

        // Add rainfall and water in the snowcover to total liquid water. ???? !!!!

        h2o_total[hh] += m_rain[hh];
        //    ro_predict[hh] += m_rain[hh];
    } // current precip

  // Add water in the snowcover to total liquid water.
    else // no precip
        h2o_total[hh] += h2o[hh];
}

void ClassSnobalBase::_drift(void)
{
    if (m_drift[hh] - m_subl[hh] == 0.0 || layer_count[hh] == 0)
        return;

    else if (m_drift[hh] - m_subl[hh] > 0.0) { // drift in
        _adj_snow((m_drift[hh] - m_subl[hh]) / rho[hh], m_drift[hh] - m_subl[hh]);
    }
    else { // drift out or sublimation
        _adj_snow((m_drift[hh] - m_subl[hh]) / rho[hh], m_drift[hh] - m_subl[hh]);
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
**	(and those variables modified by "_adj_snow")
*/

void ClassSnobalBase::_snowmelt(void) {

    double  Q_0;            // energy available for surface melt
    double  Q_l;	       // energy available for lower layer melt
    double  Q_freeze;       // energy used for re-freezing
    double  Q_left;         // energy left after re_freezing
    double  h2o_refrozen;   // amount of liquid H2O that was refrozen

// If no snow on ground at start of timestep, then just exit.

    if (!snowcover[hh]) {
        melt[hh] = 0.0;
        return;
    }

    // calculate melt or freezing, and adjust cold content

    // calculate surface melt

    // energy for surface melt
    Q_0 = (delta_Q_0[hh] * time_step[hh]) + cc_s_0[hh];

    if (Q_0 > 0.0) {
        melt[hh] = MELT(Q_0);
        cc_s_0[hh] = 0.0;
    }
    else if (Q_0 == 0.0) {
        melt[hh] = 0.0;
        cc_s_0[hh] = 0.0;
    }
    else {
        melt[hh] = 0.0;
        cc_s_0[hh] = Q_0;

        if (m_s[hh] < 2.0) // addition TB 06/03/10
            cc_s_0[hh] = 0.0;
    }


    // calculate lower layer melt

    if (layer_count[hh] == 2) {
        // energy for layer melt
        Q_l = ((G[hh] - G_0[hh]) * time_step[hh]) + cc_s_l[hh];

        if (Q_l > 0.0) {
            melt[hh] += MELT(Q_l);
            cc_s_l[hh] = 0.0;
        }
        else if (Q_l == 0.0)
            cc_s_l[hh] = 0.0;
        else
            cc_s_l[hh] = Q_l;
    }
    else {  // layer_count == 1
        Q_l = 0.0;
    }

    h2o_total[hh] += melt[hh];

    // adjust layers for re-freezing

    // adjust surface layer

    h2o_refrozen = 0.0;

    if (cc_s_0[hh] < 0.0) {
        // if liquid h2o present, calc refreezing and adj cc_s_0
        if (h2o_total[hh] > 0.0) {
            Q_freeze = h2o_total[hh] * (z_s_0[hh] / z_s[hh]) * LH_FUS(FREEZE);
            Q_left = Q_0 + Q_freeze;

            if (Q_left <= 0.0) {
                h2o_refrozen = h2o_total[hh] * (z_s_0[hh] / z_s[hh]);
                cc_s_0[hh] = Q_left;
            }
            else {
                h2o_refrozen = (h2o_total[hh] * (z_s_0[hh] / z_s[hh])) - MELT(Q_left);
                cc_s_0[hh] = 0.0;
            }
        }
    }

    // adjust lower layer for re-freezing

    if ((layer_count[hh] == 2) && (cc_s_l[hh] < 0.0)) {
        // if liquid h2o, calc re-freezing and adj cc_s_l[hh]
        if (h2o_total[hh] > 0.0) {
            Q_freeze = h2o_total[hh] * (z_s_l[hh] / z_s[hh]) * LH_FUS(FREEZE);
            Q_left = Q_l + Q_freeze;

            if (Q_left <= 0.0) {
                h2o_refrozen += h2o_total[hh] * (z_s_l[hh] / z_s[hh]);
                cc_s_l[hh] = Q_left;
            }
            else {
                h2o_refrozen += ((h2o_total[hh] * (z_s_l[hh] / z_s[hh])) - MELT(Q_left));
                cc_s_l[hh] = 0.0;
            }
        }
    }

    // Note:  because of rounding errors, h2o_refrozen may not
    //   be exactly the same as h2o_total.  Check for this case, and if so, then just zero out h2o_total.

    if (fabs(h2o_total[hh] - h2o_refrozen) <= 1e-8) {
        h2o_total[hh] = 0.0;
    }
    else {
        h2o_total[hh] -= h2o_refrozen;
    }

    // determine if snowcover is isothermal

    if ((layer_count[hh] == 2) && (cc_s_0[hh] == 0.0) && (cc_s_l[hh] == 0.0))
        isothermal[hh] = 1;
    else if ((layer_count[hh] == 1) && (cc_s_0[hh] == 0.0))
        isothermal[hh] = 1;
    else
        isothermal[hh] = 0;

    // adjust depth and density for melt

    if (melt[hh] > 0.0) { // !!!
        if (rho[hh] <= 0.0)
            rho[hh] = 750; // Maximum snow density (kg/m^3)

        _adj_snow(-(melt[hh] / rho[hh]), 0.0);
    }

    // set total cold content
    if (layer_count[hh] == 2)
        cc_s[hh] = cc_s_0[hh] + cc_s_l[hh];
    else // (layer_count[hh] == 1)
        cc_s[hh] = cc_s_0[hh];
}

/*
** NAME
**      void _new_density(void) -- adjust the snowcover's depth and layers for new density
**
** DESCRIPTION
**      This routine adjusts the snowcover's depth for a new density.  The
**	layers are also adjusted accordingly.
**
** GLOBAL VARIABLES READ
**	m_s
**	rho
**
** GLOBAL VARIABLES MODIFIED
**	z_s
**
**	(and those variables modified by "_adj_layers")
*/

void ClassSnobalBase::_new_density(void) {

    z_s[hh] = m_s[hh] / rho[hh];

    _adj_layers();
}

/*
** NAME
**      _adj_snow -- adjust the snowcover with changes in depth and/or mass
**
**      void
**	_adj_snow(
**	    double delta_z_s,	|* change in snowcover's depth *|
**	    double delta_m_s)	|* change is snowcover's mass *|
**
** DESCRIPTION
**      This routine adjusts the snowcover for a change in its depth or
**	its mass or both.  The snowcover's density is updated.  If there
**	is a change in the snowcover's depth, the # of layers is recomputed.
**	If there's just a change in the snowcover's mass with no change in
**	its depth, then just the specific masses for the layers are updated.
**
**	The routine ensures that the snowcover's density does NOT exceed
**	a maximum density (currently 750 kg/m^3).  If the adjustments to
**	the snowcover, for some reason, lead to an excessive density, the
**	density is clipped at the maximum, and the depth re-adjusted
**	accordingly.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**	m_s
**	rho
**	z_s
**
**	(and those variables modified by "_adj_layers" and "_layer_mass")
*/

void ClassSnobalBase::_adj_snow(
    double	delta_z_s,	// change in snowcover's depth
    double	delta_m_s)	// change is snowcover's mass
{

    const double MAX_SNOW_DENSITY = 750; // Maximum snow density (kg/m^3)

  // Update depth, mass, and then recompute density.
    z_s[hh] += delta_z_s;
    m_s[hh] += delta_m_s;

    if (z_s[hh] > 0.0)
        rho[hh] = m_s[hh] / z_s[hh];
    else {
        z_s[hh] = 0.0;
        m_s[hh] = 0.0;
    }

    // Clip density at maxium density if necessary.
    if (rho[hh] > MAX_SNOW_DENSITY) {
        rho[hh] = MAX_SNOW_DENSITY;
        z_s[hh] = m_s[hh] / rho[hh];
        _adj_layers();
    }
    // If a change in depth, adjust the layers' depths and masses.
    else {
        if (delta_z_s != 0.0)
            _adj_layers();
        else
            // Just a change in the snowcover's mass, so update the layers' masses.
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
**	E
**	layer_count
**	P_a
**	rho
**	T_g
**	T_s_l
**	T_s_0
**	time_step
**	z_g
**
** GLOBAL VARIABLES MODIFIED
**	E_s h2o_total
**
**	(and those variables modified by "_adj_snow")
*/

#define VAP_SUB (2.501 / 2.835) // ratio vaporization to sublimatin

void ClassSnobalBase::_evap_cond(void) {

    //        double  E_s_0;          // mass of evaporation to air (kg/m^2)
    //        double  E_s_l;          // mass of evaporation to soil (kg/m^2)
    double  E_l;	       // mass flux by evap/cond to soil (kg/m^2/s)
    double  e_g;            // soil vapor press
    double  e_s_l;          // lower snow layer's vapor press
    double  k;              // soil diffusion coef
    double  prev_h2o_tot;   // previous value of h2o_total variable
    double  q_delta;        // difference between snow & soil spec hum's
    double  q_g;            // soil spec hum
    double  q_s_l;          // lower snow layer's spec hum
    double  rho_air;        // air density
    double  T_bar;          // snow-soil mean temp

// calculate evaporation or condensation

// If no snow on ground at start of timestep, then just exit.

    if (!snowcover[hh]) {
        E_s[hh] = 0.0;
        return;
    }

    // Total mass change due to evap/cond at surface during timestep

    E_s_0[hh] = E[hh] * time_step[hh];

    //  Adjust total h2o for evaporative losses

    prev_h2o_tot = h2o_total[hh];

    if (h2o_total[hh] > 0.0) {
        h2o_total[hh] += (E_s_0[hh] * VAP_SUB);
        if (h2o_total[hh] <= 0.0)
            h2o_total[hh] = 0.0;
    }

    // Determine total mass change due to evap/cond at soil

    if (layer_count[hh] == 0)
        E_s_l[hh] = 0.0;
    else {
        if (layer_count[hh] == 2) {
            e_s_l = sati(T_s_l[hh]);
            T_bar = (T_g[hh] + T_s_l[hh]) / 2.0;
        }
        else {  /* layer_count == 1 */
            e_s_l = sati(T_s_0[hh]);
            T_bar = (T_g[hh] + T_s_0[hh]) / 2.0;
        }

        q_s_l = SPEC_HUM(e_s_l, P_a[hh]);
        e_g = sati(T_g[hh]);
        q_g = SPEC_HUM(e_g, P_a[hh]);
        q_delta = q_g - q_s_l;
        rho_air = GAS_DEN(P_a[hh], MOL_AIR, T_bar);
        k = DIFFUS(P_a[hh], T_bar);

        E_l = EVAP(rho_air, k, q_delta, z_g[hh]);

        /* total mass of evap/cond for time step */
        E_s_l[hh] = E_l * time_step[hh];

        /** adjust h2o_total for evaporative losses **/
        if (h2o_total[hh] > 0.0) {
            h2o_total[hh] += (E_s_l[hh] * VAP_SUB);
            if (h2o_total[hh] <= 0.0)
                h2o_total[hh] = 0.0;
        }
    }

    E_s[hh] = E_s_0[hh] + E_s_l[hh];

    //      adj mass and depth for evap/cond

    if (layer_count[hh] > 0)
        _adj_snow(((E_s[hh] + (prev_h2o_tot - h2o_total[hh])) / rho[hh]) / 2.0, E_s[hh]);
}

/*
** NAME
**      void _h2o_compact(void) -- compact snowcover due to liquid H2O that was added
**
** DESCRIPTION
**	This routine compacts or densifies the snowcover based on the
**	amount of liquid H2O that was added to the snowcover from melting
**	and rain.  The snowcover's density is increased using the
**	following "half-saturation" function:
**
**		delta_rho(h2o_added) = A / (1 + B/h2o_added)
**
**	A = "saturation-level" or asymtope which is the difference between
**	    the maximum density due to compaction by liquid H2O
**	    (approximately 550 kg/m^2) and the current density
**	B = the point for half of the saturation level is reached (5 %)
**	    (h2o_added = ratio of mass of liquid h2o added by melting and
**		         rain to the mass of the snowcover)
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
**	m_s
**	melt
**
** GLOBAL VARIABLES MODIFIED
**	rho
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

void ClassSnobalBase::_h2o_compact(void)
{

    double Alocal;         // difference between maximum & currentdensities

    double	h2o_added;	// ratio of mass of liquid H2O added from melting and rain to mass of snowcover

  // If the snow is already at or above the maximum density due compaction by liquid H2O, then just leave.

    if ((!snowcover[hh]) || (rho[hh] > MAX_DENSITY))
        return;

    Alocal = MAX_DENSITY - rho[hh];

    if (m_s[hh]) {  // !!! fudge
        if (precip_now[hh])
            h2o_added = (melt[hh] + m_rain[hh]) / m_s[hh];
        else
            h2o_added = melt[hh] / m_s[hh];

        if (h2o_added > 0.000001) {
            rho[hh] += Alocal / (1 + BB / h2o_added);
            _new_density(); // Adjust the snowcover for this new density.
        }
    }
}

void ClassSnobalBase::_adj_layers(void) {

    /*
    ** NAME
    **      _adj_layers -- adjust the layers because of new snowcover depth
    **
    ** SYNOPSIS
    **      #include "_snobal.h"
    **
    **      void
    **	_adj_layers(void);
    **
    ** DESCRIPTION
    **      This routine adjusts the layers of the snowcover because the
    **	snowcover's depth has changed.  It is assumed that the snowcover's
    **	density has already been updated.  The # of layers are recomputed
    **	based on the overall snowcover depth.  Their depths and masses
    **	are updated as well.  If a layer has been created due to an
    **	increase in the snowcover's depth, its temperature and cold content
    **	are initialized.
    **
    ** GLOBAL VARIABLES READ
    **	layer_count
    **
    ** GLOBAL VARIABLES MODIFIED
    **	cc_s
    **	cc_s_0
    **	cc_s_l
    **	h2o
    **	h2o_max
    **	h2o_total
    **	h2o_vol
    **	m_s
    **	m_s_0
    **	m_s_l
    **	rho
    **	T_s
    **	T_s_0
    **	T_s_l
    **
    **	(and those variables modified by "_calc_layer" and "_layer_mass")
    */

    /*
     *  Recompute then number of layers and see if there's been
     *  a change in the # of layers.  Note:  since this routine
     *  is called to adjust an existing snowcover, the current # of
     *  layers must be either 1 or 2 while the new # of layers may
     *  either be 0, 1 or 2.
     *
     *	current #	new #
     *	of layers	of layers
     *
     *	   1	   -->	   0
     *	   1	   -->	   1	(no change)
     *	   1	   -->	   2
     *	   2	   -->	   0
     *	   2	   -->	   1
     *	   2	   -->	   2	(no change)
     */
    int prev_layer_count;	// previous # of layers, if change in depth
    prev_layer_count = layer_count[hh];  // must be > 0
    _calc_layers();

    if (layer_count[hh] == 0) {

        // 1 or 2 layers --> 0 layers

        rho[hh] = 218.0; // 10/18/16

    // If mass > 0, then it must be below threshold. So turn this little bit of mass into water.

        if (m_s[hh] > 0.0) {
            snowmelt_int[hh] += m_s[hh];
            melt_direct_int[hh] += m_s[hh];
        }

        m_s[hh] = cc_s[hh] = 0.0;
        m_s_0[hh] = cc_s_0[hh] = 0.0;

        // Note: Snow temperatures are set to MIN_SNOW_TEMP (as degrees K) instead of 0 K to keep quantization range in output image smaller.

        T_s[hh] = T_s_0[hh] = MIN_SNOW_TEMP + FREEZE;

        if (prev_layer_count == 2) {
            m_s_l[hh] = cc_s_l[hh] = 0.0;
            T_s_l[hh] = MIN_SNOW_TEMP + FREEZE;
        }
        h2o_vol[hh] = h2o[hh] = h2o_max[hh] = h2o_sat[hh] = 0.0;
    }

    else {
        _layer_mass();

        if ((prev_layer_count == 1) && (layer_count[hh] == 2)) {

            // 1 layer --> 2 layers, add lower layer

            T_s_l[hh] = T_s[hh];
            cc_s_l[hh] = _cold_content(T_s_l[hh], m_s_l[hh]);
        }

        else if ((prev_layer_count == 2) && (layer_count[hh] == 1)) {

            // 2 layers --> 1 layer, remove lower layer

            T_s_l[hh] = MIN_SNOW_TEMP + FREEZE;
            cc_s_l[hh] = 0.0;
        }
    }
}

/*
** NAME
**      void _runoff(void) -- calculates runoff from snowcover
**
** DESCRIPTION
**      Calculates runoff for point energy budget 2-layer snowmelt model
**
** GLOBAL VARIABLES READ
**	h2o_total
**	layer_count
**	snowcover
**	max_h2o_vol
**	z_s
**
** GLOBAL VARIABLES MODIFIED
**	h2o
**	h2o_max
**	h2o_sat
**	h2o_vol
**	rho
**	ro_predict
*/

void ClassSnobalBase::_runoff(void) {

    double	m_s_dry;	/* snowcover's mass without liquid H2O */
    double	rho_dry;	/* snow density without liquid H2O */

// calculate runoff

// If no snow on ground at start of timestep or no layers currently, then all water (e.g., rain) is runoff.

    if ((!snowcover[hh]) || (layer_count[hh] == 0)) {
        ro_predict[hh] = h2o_total[hh];
        return;
    }

    //  Determine the snow density without any water, and the maximum liquid water the snow can hold.

    m_s_dry = m_s[hh] - h2o_total[hh];
    rho_dry = m_s_dry / z_s[hh];
    h2o_max[hh] = H2O_LEFT(z_s[hh], rho_dry, max_h2o_vol[hh]);

    // Determine runoff, and water left in the snow

    if (h2o_total[hh] > h2o_max[hh]) {
        ro_predict[hh] = h2o_total[hh] - h2o_max[hh];
        h2o[hh] = h2o_max[hh];
        h2o_sat[hh] = 1.0;
        h2o_vol[hh] = max_h2o_vol[hh];

        //  Update the snowcover's mass for the loss of runoff.

        _adj_snow(0.0, -ro_predict[hh]);
    }
    else {
        ro_predict[hh] = 0.0;
        h2o[hh] = h2o_total[hh];
        h2o_sat[hh] = h2o[hh] / h2o_max[hh];
        h2o_vol[hh] = h2o_sat[hh] * max_h2o_vol[hh];
    }
}

double satw(
    double  tk) {		/* air temperature (K)		*/

    double  x;
    double  l10;

    if (tk <= 0.) {
        CRHMException TExcept("satw temperature <= 0.0", TExcept::TERMINATE);
        LogError(TExcept);
    }

    errno = 0;
    l10 = log(1.e1);

    x = -7.90298 * (BOIL / tk - 1.0f) + 5.02808f * log(BOIL / tk) / l10 -
        1.3816e-7 * (pow(1.0e1, 1.1344e1f * (1.0 - tk / BOIL)) - 1.0f) +
        8.1328e-3 * (pow(1.0e1, -3.49149f * (BOIL / tk - 1.0f)) - 1.0f) +
        log(SEA_LEVEL) / l10;

    x = pow(1.0e1f, x);

    if (errno) {
        CRHMException TExcept("satw: bad return from log or pow", TExcept::TERMINATE);
        LogError(TExcept);
    }

    return(x);
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



double ClassSnobalBase::sati(double  tk) { //* air temperature (K)

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

double ClassSnobalBase::ssxfr(
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

double ClassSnobalBase::heat_stor(
    double	cp,	/* specific heat of layer (J/kg K) */
    double	spm,	/* layer specific mass (kg/m^2)    */
    double	tdif)	/* temperature change (K)          */
{
    double	stor;

    stor = cp * spm * tdif;

    return (stor);
}
/* ----------------------------------------------------------------------- */

double ClassSnobalBase::new_tsno(
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

double ClassSnobalBase::efcon(
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

int ClassSnobalBase::hle1(
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
        string SS = D + "hh " + to_string(hh) + " 'hle1' " + ". H: " + FloatToStrF(h, TFloatFormat::ffFixed, 10, 4) + " le: " + FloatToStrF(xlh * e, TFloatFormat::ffFixed, 10, 4);
        SS = SS + " ta: " + FloatToStrF(ta - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
            ", ts: " + FloatToStrF(ts - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
            ", ea: " + FloatToStrF(ea, TFloatFormat::ffFixed, 10, 4) +
            ", es: " + FloatToStrF(es, TFloatFormat::ffFixed, 10, 4) +
            ", u:  " + FloatToStrF(u, TFloatFormat::ffFixed, 10, 4) +
            ", m_s:  " + FloatToStrF(m_s[hh], TFloatFormat::ffFixed, 10, 4);

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

            // Eq 4.25, but no minus sign as we define positive H as toward surface

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
        string SS = D + "hh " + to_string(hh) + " 'hle1' " + Flag + ". H: " + FloatToStrF(h, TFloatFormat::ffFixed, 10, 4) + " le: " + FloatToStrF(xlh * e, TFloatFormat::ffFixed, 10, 4);
        SS = SS + " ta: " + FloatToStrF(ta - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
            ", ts: " + FloatToStrF(ts - CRHM_constants::Tm, TFloatFormat::ffFixed, 10, 4) +
            ", ea: " + FloatToStrF(ea, TFloatFormat::ffFixed, 10, 4) +
            ", es: " + FloatToStrF(es, TFloatFormat::ffFixed, 10, 4) +
            ", u:  " + FloatToStrF(u, TFloatFormat::ffFixed, 10, 4) +
            ", m_s:  " + FloatToStrF(m_s[hh], TFloatFormat::ffFixed, 10, 4);
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