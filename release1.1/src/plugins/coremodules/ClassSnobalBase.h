#ifndef ClassSnobalBaseH
#define ClassSnobalBaseH

//created by Manishankar Mondal

#include "ClassModule.h"
#include "INPUT_REC.h"
#include "TSTEP_REC.h"
#include "PRECIP_REC.h"

class ClassSnobalBase : public ClassModule {

public:

    ClassSnobalBase(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

    // declared variables

    //   snowpack information

    long* layer_count;    // number of layers in snowcover: 0, 1, or 2
    double* z_s;            // total snowcover thickness (m)
    double* z_s_0;          // active layer depth (m)
    double* z_s_l;          // lower layer depth (m)
    double* rho;            // average snowcover density (kg/m^3)
    double* m_s;            // snowcover's specific mass (kg/m^2). Init by init_snow.
    double* m_s_0;          // active layer specific mass (kg/m^2). Init by init_snow.
    double* m_s_l;          // lower layer specific mass (kg/m^2). Init by init_snow.
    double* T_s;            // average snowcover temp (K). Init by init_snow
    double* T_s_0;          // active snow layer temp (K)
    double* T_s_l;          // lower layer temp (C)
    double* cc_s;           // snowcover's cold content (J/m^2). Init by init_snow.
    double* cc_s_0;         // active layer cold content (J/m^2). Init by init_snow.
    double* cc_s_l;         // lower layer cold content (J/m^2). Init by init_snow.
    double* h2o_sat;        // % of liquid H2O saturation (relative water content, i.e., ratio of water in snowcover
//                                 to water that snowcover could hold at saturation)
    double* h2o_vol;        // liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless).init_snow
    double* h2o;            // liquid h2o content as specific mass(kg/m^2)
    double* h2o_max;        // max liquid h2o content as specific mass(kg/m^2)
    double* h2o_total;      // total liquid h2o: includes h2o in snowcover, melt, and rainfall (kg/m^2)

//   energy balance info for current timestep

    double* R_n;            // net allwave radiation (W/m^2)
    double* H;              // sensible heat xfr (W/m^2)
    double* L_v_E;          // latent heat xfr (W/m^2)
    double* G;              // heat xfr by conduction & diffusion from soil to snowcover (W/m^2)
    double* G_0;            // heat xfr by conduction & diffusion from soil or lower layer to active layer (W/m^2)
    double* M;              // advected heat from precip (W/m^2)
    double* delta_Q;        // change in snowcover's energy (W/m^2)
    double* delta_Q_0;      // change in active layer's energy (W/m^2)

//   mass balance vars for current timestep

    double* melt_direct_int;       // specific melt (kg/m^2 or m)
    double* sum;       // specific melt (kg/m^2 or m)
    double* SWE_change;       // interval change in SWE
    double* E_int;	    // mass flux by evap into air from active layer (kg/m^2/s)
    double* E_s_int;	    // mass of evap into air & soil from snowcover (kg/m^2)
    double* snowmelt_int;   // predicted specific runoff (m/sec)
    double* snowmeltD;      // daily predicted specific runoff (m/sec)
    double* snowmeltD_acc;      // daily predicted specific runoff accumulator (m/sec)

//   mass balance vars for variable timestep

    double* melt;        // specific melt (kg/m^2 or m)
    double* E;		 // mass flux by evap into air from active layer (kg/m^2/s)
    double* E_s;	 // mass of evap into air & soil from snowcover (kg/m^2)
    double* ro_predict;  // predicted specific runoff (m/sec)

    double* E_s_0;        // mass of evaporation to air (kg/m^2)
    double* E_s_l;        // mass of evaporation to soil (kg/m^2)
    double* E_l;	  // mass flux by evap/cond to soil (kg/m^2/s)

    double* E_s_0_int;        // mass of evaporation to air (kg/m^2)
    double* E_s_l_int;        // mass of evaporation to soil (kg/m^2)
    double* E_l_int;	  // mass flux by evap/cond to soil (kg/m^2/s)

//   precipitation info adjusted for current run timestep

    double* m_precip;	// specific mass of total precip (kg/m^2)
    double* m_rain;	// specific mass of rain in precip (kg/m^2)
    double* m_snow;	// specific mass in snow in precip (kg/m^2)
    double* m_drift;	// specific mass in snow drift (kg/m^2)
    double* m_subl;	// specific mass in snow sublimation (kg/m^2)
    double* rho_snow;   // density of snowfall (kg/m^3)
    double* T_pp;       // precip temp (K)
    double* z_snow;	// depth of snow in precip (m)

//   precipitation info for the current DATA timestep

    long* precip_now;	// precipitation occur for current timestep?
    double* T_rain;	// rain's temp (K)
    double* T_snow;	// snowfall's temp (K)
    double* h2o_sat_snow; // snowfall's % of liquid H2O saturation

//   local climate-data values for the current run timestep
    double* S_n;      // net solar radiation (W/m^2)
    double* I_lw;     // incoming longwave (thermal) rad (W/m^2)
    double* T_a;      // air temp (K)
    double* e_a;      // vapor pressure (Pa)
    double* u;        // wind speed (m/sec)
    double* T_g;      // soil temp at depth z_g (C)
    double* F_g;      // soil flux at depth z_g (W/m^2)

    long* isothermal; // melting?
    long* snowcover;  // snow on gnd at start of current timestep?
    long* stop_no_snow;       //

//   local variables
    double* P_a;            // air pressure (Pa)
    double* m_precip_cum;   //
    double* m_rain_cum;     //
    double* m_snow_cum;     //
    double* m_drift_cum;    //
    double* m_subl_cum;    //
    double* E_s_cum;        //
    double* cumsnowmelt;    //
    double* melt_direct_cum;       //
    double* Fault;       //

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

    const double* hru_elev;    // HRU elevation
    const double* basin_area;  // [BASIN]
    const double* hru_area;
    const double* KT_sand; // thermal conductivity of wet sand

    const long* relative_hts; // true if measurements heights, z_T and z_u, are relative to snow surface
                              // false if they are absolute heights above the ground
    const double* T_g_or_G_flux;    // soil temp or ground flux option
    const double* z_g;         // depth of soil temp meas (m)
    const double* z_u;         // height of wind measurement (m)
    const double* z_T;         // height of air temp & vapor pressure measurement (m)
    const double* z_0;         // roughness length
    const double* max_z_s_0;   // maximum active layer thickness (m)
    const double* max_h2o_vol; // max liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless)

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
        double	rho,	// snow layer's density (kg/m^3)
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

    void _drift(void);

    void _new_density(void);

    void _adj_snow(double delta_z_s, double delta_m_s); // change in snowcover's depth change is snowcover's mass

    void _evap_cond(void);

    void _h2o_compact(void);

    void _adj_layers(void);

    void _runoff(void);

    double new_tsno(double spm, double t0, double ccon);

    double heat_stor(double cp, double spm, double tdif);

    double sati(double tk);

    double ssxfr(double  k1, double  k2, double  t1, double  t2, double  d1, double  d2);

    double efcon(double k, double t, double p);

    int hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu,
        double z0, double& h, double& le, double& e);

    // time step information

    TSTEP_REC** tstep_info; 	// array of info for each timestep [nhru] [4]:
                                  //           0 : data timestep
                                  //           1 : normal run timestep
                                  //           2 : medium  "     "
                                  //           3 : small   "     "

    long* time_step;     // length current timestep (sec)
    long* current_time;  // start time of current time step (sec)

  // climate-data input records

    INPUT_REC* input_rec1;	// input data for start of data timestep [nhru]
    INPUT_REC* input_rec2;	//   "     "   "  end   "   "      "     [nhru]

    INPUT_REC** input_deltas;	// deltas for climate-input parameters
                                  //  over each timestep [nhru] [4]

    PRECIP_REC** precip_info;	// array of precip info adjusted for
                                  //  each timestep [nhru] [4]

    int** computed;		// array of flags for each timestep;
                                  //  true if computed values for input
                                  //   deltas and precip arrays [nhru] [4]
};

#endif