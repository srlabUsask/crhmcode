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
#ifndef ClassCanSnobalBaseH
#define ClassCanSnobalBaseH

//created by Manishankar Mondal

#include "../core/ClassModule.h"
#include "INPUT_REC.h"
#include "TSTEP_REC.h"
#include "PRECIP_REC.h"

class ClassCanSnobalBase : public ClassModule {

public:

    ClassCanSnobalBase(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

    // declared variables

    //   snowpack information

    double* z_veg_s{ NULL };            // total snowcover thickness (m)
    double* rho_veg{ NULL };            // average snowcover density (kg/m^3)
    double* m_s_veg{ NULL };            // snowcover's specific mass (kg/m^2). Init by init_snow.
    double* T_s_veg{ NULL };            // average snowcover temp (K). Init by init_snow
    double* cc_s_veg{ NULL };           // snowcover's cold content (J/m^2). Init by init_snow.
    double* cc_s_veg{ NULL };         // active layer cold content (J/m^2). Init by init_snow.
    double* h2o_sat_veg{ NULL };        // % of liquid H2O saturation (relative water content, i.e., ratio of water in snowcover
//                                 to water that snowcover could hold at saturation)
    double* h2o_vol_veg{ NULL };        // liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless).init_snow
    double* liq_h2o_veg{ NULL };            // liquid h2o content as specific mass(kg/m^2)
    double* h2o_max_veg{ NULL };        // max liquid h2o content as specific mass(kg/m^2)
    double* h2o_total_veg{ NULL };      // total liquid h2o: includes h2o in snowcover, melt, and rainfall (kg/m^2)

//   energy balance info for current timestep

    double* Qn_veg{ NULL };            // net allwave radiation wrt the canopy (W/m^2)
    double* Qh_veg{ NULL };              // sensible heat xfr wrt the canopy (W/m^2)
    double* Ql_veg{ NULL };          // latent heat xfr wrt the canopy (W/m^2)
    double* Qp{ NULL };              // advected heat from precip wrt the canopy (W/m^2)
    double* delta_Q_veg{ NULL };        // change in snowcover's energy wrt the canopy (W/m^2)

//   mass balance vars for current timestep

    double* delmelt_veg_int{ NULL };       // specific melt (kg/m^2 or m)
    double* delL{ NULL };       // interval change in SWE
    double* delsub_veg_int{ NULL };	    // mass of evap into air & soil from snowcover (kg/m^2*int)
    double* delunld{ NULL };	    // canopy snow unloading rate (kg/m^2*int)
    double* delunld_wind{ NULL };	    // solid snow unloading from the canopy induced by wind (kg/m^2*int)
    double* delunld_melt{ NULL };	    // canopy snow unloading rate due to melting (kg/m^2*int)
    double* delunld_subl{ NULL };	    // canopy snow unloading due to sublimation (kg/m^2*int)

    double* delmelt_veg_day{ NULL };      // daily predicted specific runoff (m/sec)
    double* cmlmelt_veg_day{ NULL };      // daily predicted specific runoff accumulator (m/sec)


//   mass balance vars for variable timestep

    double* delmelt_veg{ NULL };        // specific melt (kg/m^2 or m)
    double* qsub_veg{ NULL };		 // mass flux by evap into air from active layer (kg/m^2/s)
    double* delsub_veg{ NULL };	 // mass of evap into air & soil from snowcover (kg/m^2)
    double* deldrip_veg{ NULL };  // predicted specific runoff (m/sec)

    double* E_l{ NULL };	  // mass flux by evap/cond to soil (kg/m^2/s)


//   precipitation info adjusted for current run timestep

    double* m_precip{ NULL };	// specific mass of total precip (kg/m^2)
    double* m_rain{ NULL };	// specific mass of rain in precip (kg/m^2)
    double* m_snow{ NULL };	// specific mass in snow in precip (kg/m^2)
    double* m_subl{ NULL };	// specific mass in snow sublimation (kg/m^2)
    double* rho_snow{ NULL };   // density of snowfall (kg/m^3)
    double* T_pp{ NULL };       // precip temp (K)
    double* z_snow_veg{ NULL };	// depth of snow in precip (m)

//   precipitation info for the current DATA timestep

    long* precip_now_veg{ NULL };	// precipitation occur for current timestep?
    double* T_rain_veg{ NULL };	// rain's temp (K)
    double* T_snow_veg{ NULL };	// snowfall's temp (K)
    double* h2o_sat_veg_snow{ NULL }; // snowfall's % of liquid H2O saturation

//   local climate-data values for the current run timestep
    double* S_n{ NULL };      // net solar radiation (W/m^2)
    double* I_lw{ NULL };     // incoming longwave (thermal) rad (W/m^2)
    double* T_a{ NULL };      // air temp (K)
    double* e_a{ NULL };      // vapor pressure (Pa)
    double* u{ NULL };        // wind speed (m/sec)
    double* T_g{ NULL };      // soil temp at depth z_g (C)
    double* F_g{ NULL };      // soil flux at depth z_g (W/m^2)
    const double *T_s_0 { NULL }; // temp of the surface snowpack active layer (K)


    long* isothermal{ NULL }; // melting?
    long* vegsnowcover{ NULL };  // snow on veg at start of current timestep?
    long* stop_no_snow{ NULL };       //

//   local variables
    double* P_a{ NULL };            // air pressure (Pa)
    double* m_precip_cum{ NULL };   //
    double* m_rain_cum{ NULL };     //
    double* m_snow_cum{ NULL };     //
    double* m_subl_cum{ NULL };    //
    double* E_s_cum{ NULL };        //
    double* cmlmelt_veg{ NULL };    //
    double* melt_direct_cum{ NULL };       //
    double* Fault{ NULL };       //

// debug variables
/*    double *Length;
    double **Length_array;
    double *Ustar;
    double **Ustar_array;
    double *e;
    double **e_array;
    double *h;
    double **h_array;
    long *ier;
    long **ier_array;
    long  *ArrayCnt; */

    // declared parameters

    //   measurement heights/depths

    const double* hru_elev{ NULL };    // HRU elevation
    const double* basin_area{ NULL };  // [BASIN]
    const double* hru_area{ NULL };
    const double* KT_sand{ NULL }; // thermal conductivity of wet sand

    const long* relative_hts{ NULL }; // true if measurements heights, z_T and z_u, are relative to snow surface
                              // false if they are absolute heights above the ground
    const double* z_g{ NULL };         // depth of soil temp meas (m)
    const double* z_u{ NULL };         // height of wind measurement (m)
    const double* z_T{ NULL };         // height of air temp & vapor pressure measurement (m)
    const double* z_0_veg{ NULL };         // roughness length
    const double* max_h2o_vol_veg{ NULL }; // max liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless)
    const double  *Cc{ NULL };       // canopy coverage, (1-sky view fraction)
    const double  *Lmax{ NULL };  // maximum canopy snow interception load, currently just used for sublimation exposure coef. 50 kg m-2 based on max observed in Storck et al. 2002, Floyd 2012 and Cebulski & Pomeroy (kg/m^2)
    const double  *Ht{ NULL };  // forest/vegetation height (m)
    const long  *CanopyWindSwitch{ NULL };  // Canopy wind model to use at height Zcan, 0 - for Cionco (dense canopy), 1 - for Prandtl-von Kármán log-linear relationship (sparse forest)".
    const double  *melt_drip_ratio{ NULL };  // Ratio of mass unloading of solid snow due to melt compared to canopy snowmelt. (-)





//    void decl(void);

    void init(void);

    //    void run(void);

    void finish(bool good); // delete local storage used

    void init_snow(void);

    void _calc_layers(void);

    void _layer_mass(void);

    double _cold_content(double	temp, double	mass); // temperature of layer specific mass of layer

    void do_data_tstep(void);

    int _divide_tstep(TSTEP_REC* tstep); // record of timestep to be divided

    int _below_thold(double threshold);	 // current timestep's threshold for a layer's mass

    int _do_tstep(TSTEP_REC* tstep); // timestep's record

    int _e_bal(void);

    void _net_rad(void);

    int _h_le(void);

    double g_soil(
        double	rho_veg,	// snow layer's density (kg/m^3)
        double	tsno,	// snow layer's temperature (K)
        double	tg,	// soil temperature (K)
        double	ds,	// snow layer's thickness (m)
        double	dg,	// dpeth of soil temperature measurement (m)
        double	pa);	// air pressure (Pa)

    double g_snow(
        double	rho1,	// upper snow layer's density (kg/m^3)
        double	rho2,	// lower  "     "        "    (kg/m^3)
        double	ts1,	// upper snow layer's temperature (K)
        double	ts2,	// lower  "     "         "       (K)
        double	ds1,	// upper snow layer's thickness (m)
        double	ds2,	// lower  "     "         "     (m)
        double	pa);	// air pressure (Pa)

    void _advec(void);

    void _mass_bal(void);

    void _time_compact(void);

    void _precip(void);

    void _snowmelt(void);

    void _mass_unld(void);

    void _new_density(void);

    void _adj_snow(double delta_z_s, double delta_m_s); // change in snowcover's depth change is snowcover's mass

    void _evap_cond(void);

    void _h2o_compact(void);

    void _runoff(void);

    double new_tsno(double spm, double t0, double ccon);

    double heat_stor(double cp, double spm, double tdif);

    double sati(double tk);

    double ssxfr(double  k1, double  k2, double  t1, double  t2, double  d1, double  d2);

    double efcon(double k, double t, double p);

    int hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu,
        double z0, double& h, double& le, double& e);

    // time step information

    TSTEP_REC** tstep_info{ NULL }; 	// array of info for each timestep [nhru] [4]:
                                  //           0 : data timestep
                                  //           1 : normal run timestep
                                  //           2 : medium  "     "
                                  //           3 : small   "     "

    long* time_step{ NULL };     // length current timestep (sec)
    long* current_time{ NULL };  // start time of current time step (sec)

  // climate-data input records

    INPUT_REC* input_rec1{ NULL };	// input data for start of data timestep [nhru]
    INPUT_REC* input_rec2{ NULL };	//   "     "   "  end   "   "      "     [nhru]

    INPUT_REC** input_deltas{ NULL };	// deltas for climate-input parameters
                                  //  over each timestep [nhru] [4]

    PRECIP_REC** precip_info{ NULL };	// array of precip info adjusted for
                                  //  each timestep [nhru] [4]

    int** computed{ NULL };		// array of flags for each timestep;
                                  //  true if computed values for input
                                  //   deltas and precip arrays [nhru] [4]
};

#endif
