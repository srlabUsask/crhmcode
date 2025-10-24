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
#ifndef ClassCanopySnowBalanceBaseH
#define ClassCanopySnowBalanceBaseH

//created by Manishankar Mondal

#include "../core/ClassModule.h"
#include "INPUT_REC.h"
#include "TSTEP_REC.h"
#include "PRECIP_REC.h"

class ClassCanopySnowBalanceBase : public ClassModule {

public:

    ClassCanopySnowBalanceBase(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

    // declared variables

    //   snowpack information

    double* snow_h2o_veg{ NULL };            // snow h2o content as specific mass(kg/m^2)
    double* liq_h2o_veg{ NULL };            // liquid h2o content as specific mass(kg/m^2)
    double* m_s_veg{ NULL };            // snowcover's specific mass, liquid and snow (kg/m^2). Init by init_snow_veg.
    double* T_s_veg{ NULL };            // average snowcover temp (K). Init by init_snow_veg
    double* cc_s_veg{ NULL };           // snowcover's cold content (J/m^2). Init by init_snow_veg.
    double* h2o_sat_veg{ NULL };        // % of liquid H2O saturation (relative water content, i.e., ratio of water in snowcover
    double* h2o_vol_veg{ NULL };        // liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless).init_snow_veg
    double* max_liq_veg{ NULL };        // max liquid h2o content as specific mass(kg/m^2)

//   energy balance info for current timestep

    double* Qn_veg{ NULL };            // net allwave radiation wrt the canopy (W/m^2)
    double* Qh_veg{ NULL };              // sensible heat xfr positive towards the canopy (W/m^2)
    double* Ql_veg{ NULL };          // latent heat xfr positive towards the canopy (W/m^2)
    double* Qp{ NULL };              // advected heat from precip wrt the canopy (W/m^2)
    double* delta_Q_veg{ NULL };        // change in snowcover's energy wrt the canopy (W/m^2)
    const double  *Tauc{ NULL };     // Canopy transmittance through the entire canopy calculated in the canopy module


//   mass balance vars for current timestep

    double* delmelt_veg_int{ NULL };       // specific melt (kg/m^2 or m)
    double* delL{ NULL };       // interval change in SWE
    double* delevap_veg_int{ NULL };	    // mass of evap into air & soil from snowcover (kg/m^2*int) delunld_int
    double* delsub_veg_int{ NULL };	    // mass of evap into air & soil from snowcover (kg/m^2*int) delunld_int
    double* delunld_int{ NULL };	    // specific mass of canopy snow unloaded to subcanopy (kg/m^2*int)
    double* delunld{ NULL };	    // canopy snow unloading rate (kg/m^2*s)
    double* delunld_wind{ NULL };	    // solid snow unloading from the canopy induced by wind (kg/m^2*s)
    double* delunld_melt{ NULL };	    // canopy snow unloading rate due to melting (kg/m^2*s)
    double* delunld_subl{ NULL };	    // canopy snow unloading due to sublimation (kg/m^2*s)
    double* delunld_wind_int{ NULL };	    // solid snow unloading from the canopy induced by wind (kg/m^2*int)
    double* delunld_melt_int{ NULL };	    // canopy snow unloading rate due to melting (kg/m^2*int)
    double* delunld_subl_int{ NULL };	    // canopy snow unloading due to sublimation (kg/m^2*int)
    double* deldrip_veg_int{ NULL };	    // canopy snowmelt drainage (kg/m^2*int)

    double* delmelt_veg_day{ NULL };      // daily predicted specific runoff (m/sec)
    double* cmlmelt_veg_day{ NULL };      // daily predicted specific runoff accumulator (m/sec)

    const double* hru_evap{ NULL };      // liquid water evaporated off the canopy. computed in the evap module aka "internal evap". (kg m^-2)

    double* net_rain { NULL }; // throughfall rain + drip (runoff/melt drainage) of snow intercepted in the canopy (kg/m^2*int)
    double* net_snow { NULL }; // throughfall snow + unloaded snow from the canopy (kg/m^2*int)
    double* net_p { NULL }; // net rain + net snow (kg/m^2*int)

    const double *throughfall_rain { NULL }; // throughfall of rain, not in contact with the canopy to be added with canopy drip (kg/m^2*int)
    const double *throughfall_snow { NULL }; // throughfall of snow, not in contact with the canopy to be added with canopy snow unloading (kg/m^2*int)
    const double *z_s { NULL }; // total surface snowcover thickness from snobal module for relative heights calculation (m)

//   mass balance vars for variable timestep

    double* delmelt_veg{ NULL };        // specific melt (kg/m^2 or m)
    double* qsub_veg{ NULL };		 // mass flux by subl/evap (+ to surf) (kg/m^2/s)
    double* delsub_veg{ NULL };	 // mass flux by subl/evap (+ to surf) (kg/m^2/int)
    double* delevap_veg{ NULL };	 // mass flux by subl/evap (+ to surf) (kg/m^2/int)
    double* deldrip_veg{ NULL };  // predicted specific runoff (m/sec)
    double* E_l{ NULL };	  // mass flux by evap/cond to soil (kg/m^2/s)

//   precipitation info adjusted for current run timestep

    double* m_precip{ NULL };	// specific mass of total precip (kg/m^2)
    double* m_rain{ NULL };	// specific mass of rain in precip (kg/m^2)
    double* m_snow{ NULL };	// specific mass in snow in precip (kg/m^2)
    double* T_pp{ NULL };       // precip temp (K)

//   precipitation info for the current DATA timestep

    long* precip_now_veg{ NULL };	// precipitation occur for current timestep?
    double* T_rain_veg{ NULL };	// rain's temp (K)
    double* T_sf{ NULL };	// snowfall's temp (K)
    double* h2o_sat_veg_snow{ NULL }; // snowfall's % of liquid H2O saturation

//   local climate-data values for the current run timestep
    double* S_n{ NULL };      // net solar radiation (W/m^2)
    double* I_lw{ NULL };     // incoming longwave (thermal) rad (W/m^2)
    double* T_a{ NULL };      // air temp (K)
    double* e_a{ NULL };      // vapor pressure (Pa)
    double* u{ NULL };        // wind speed (m/sec)
    const double *T_s_0 { NULL }; // temp of the surface snowpack active layer (C)


    long* isothermal{ NULL }; // melting?
    long* vegsnowcover{ NULL };  // snow on veg at start of current timestep?
    long* stop_no_snow{ NULL };       //

//   local variables
    double* P_a{ NULL };            // air pressure (Pa)
    double* m_precip_cum{ NULL };   //
    double* m_rain_cum{ NULL };     //
    double* m_snow_cum{ NULL };     //
    double* E_s_cum{ NULL };        //
    double* cmlmelt_veg{ NULL };    //
    double* Fault{ NULL };       //
    double* I_LW_atm{ NULL };       // Downwelling longwave from the atmoshpere (W/m^2)
    double* I_LW_gnd{ NULL };       // Upwelling longwave from the ground (W/m^2)
    double* I_LW_cpy_2_cpy{ NULL };       // Longwave from the canopy reflected off the surface back to the canopy (W/m^2)
    double* O_LW_cpysnow{ NULL };       // Outgoing longwave radiation emitted from the canopy snow (W/m^2)
    double* I_LW_cpy{ NULL };       // Incoming longwave radiation emitted from the canopy (W/m^2)
    double* u_2_3rds{ NULL };       // Wind speed at 2/3 canopy height for canopy snow energy balance and unloading (m s^-1)
    double* rel_z_u{ NULL };       // Height of wind speed measurement relative to top of snowpack, only implemented if relative_hts[hh] == 1 (m)
    double* rel_z_T{ NULL };       // Height of temp measurement relative to top of snowpack, only implemented if relative_hts[hh] == 1 (m)

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
    const double  *Albedo_surface{ NULL };     // albedo of surface ()
    const double  *Albedo_veg{ NULL };     // albedo of vegetation ()
    const long* inhibit_evap{ NULL }; // inhibit evaporation, 1 -> inhibit
    const long* relative_hts{ NULL }; // true if measurements heights, z_T and z_u, are relative to snow surface
                              // false if they are absolute heights above the ground
    const double* z_u{ NULL };         // height of wind measurement (m)
    const double* z_T{ NULL };         // height of air temp & vapor pressure measurement (m)
    const double* Albedo_vegsnow{ NULL };         // albedo of snow on vegetation ()
    const double* SW_to_LW_fn{ NULL };         // dimensionless shortwave to longwave transfer efficiency function. 0.038 from Pomeroy et al., (2009) for marmot forced through the origin, alternative value is 0.023 from Fraser site. (-)
    const double* max_liq_veg_frac{ NULL };        // max liquid h2o content as fraction of snow mass (-)
    const double  *Cc{ NULL };       // canopy coverage, (1-sky view fraction)
    const double  *LAI{ NULL };       // LAI
    const double  *Lmax{ NULL };  // maximum canopy snow interception load, currently just used for sublimation exposure coef. 50 kg m-2 based on max observed in Storck et al. 2002, Floyd 2012 and Cebulski & Pomeroy (kg/m^2)
    const double  *Ht{ NULL };  // forest/vegetation height (m)
    const long  *CanopyWindSwitchCanSno{ NULL };  // Canopy wind model to use at height Zcan, 0 - for Cionco (dense canopy), 1 - for Prandtl-von Kármán log-linear relationship (sparse forest)".
    const long *MassUnloadingSwitch { NULL }; // canopy snow ablation parameterization to use, 0 - Cebulski & Pomeroy 2025 ablation paper, 1- Andreadis 2009, 2 - Roesch2001 (enable HP98/Ellis2010 using original canopy clearing gap module)

//    void decl(void);

    void init(void);

    //    void run(void);

    void finish(bool good); // delete local storage used

    void init_snow_veg(void);

    double _cold_content_veg(double	temp, double	mass); // temperature of layer specific mass of layer

    void do_data_tstep_veg(void);

    int _divide_tstep_veg(TSTEP_REC* tstep); // record of timestep to be divided

    int _below_thold_veg(double threshold);	 // current timestep's threshold for a layer's mass

    int _do_tstep_veg(TSTEP_REC* tstep); // timestep's record

    void compute_canopy_snow_wind(void);

    int _e_bal_veg(void);

    void _net_rad_veg(void);

    int init_turb_transfer(void);

    void _advec_veg(void);

    void _mass_bal(void);

    void _precip_veg(void);

    void _snowmelt(void);

    void _mass_unld(void);

    void _subl_evap(void);

    void _runoff_veg(void);

    double new_tsno_veg(double spm, double t0, double ccon);

    int calc_turb_transfer(double press, double ta, double rel_z_T, double ts, double ea, double es, double u, double rel_z_u,
             double &h, double &le);

    int subl_ice_sphere(double ea, double es, double ta, double ts, double u, double press);

    int init_subl_ice_sphere(void);

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
