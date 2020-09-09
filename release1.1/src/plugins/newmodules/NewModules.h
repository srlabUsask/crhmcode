// 11/28/19
//---------------------------------------------------------------------------

#ifndef OurModulesH
#define OurModulesH
//---------------------------------------------------------------------------

//#include "ClassModule.h"
#include "ClassModule.h"
//#include "ClassSnobalBase.h"

//#include "WQ_CRHM.h"
//#include "WQ_Soil_NPCcycling.h"
#include <stack>
#include <queue>

using namespace std;

extern "C" void  MoveModulesToGlobal(string DLLName = "CRHM");

float DepthofSnow(float SWE);
float SWEfromDepth(float Snow_Depth);
void ProbabilityThresholdNew(float SWE, float t, float Uten_Prob, float & Probability, float & Threshold, long Snow, float & SnowAge, long & DrySnow);
void Sum(float TQsalt, float TQsusp, float SBsum, float SBsalt, float & DriftH, float & SublH);
void Pbsm (float E_StubHt, float Uthr, float & DriftH, float & SublH,
           float t, float u, float rh, float Fetch, long N_S, float A_S);

class Classshared : public ClassModule {
public:

Classshared(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

// declared variables

void decl(void);
void init(void);

Classshared* klone(string name) const;
};

class ClassNOP : public ClassModule {
public:

ClassNOP(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

// declared variables

void decl(void);
void init(void);
void finish(bool good);

ClassNOP* klone(string name) const;
};


class TSTEP_REC { // time step information
public:

#define	DATA_TSTEP	   0
#define	NORMAL_TSTEP	   1
#define	MEDIUM_TSTEP	   2
#define	SMALL_TSTEP	   3

    // default for normal run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_NORMAL_THRESHOLD  60.0

// default for medium run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_MEDIUM_THRESHOLD  10.0

// default for small run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_SMALL_THRESHOLD  1.0


    int level;	    // timestep's level

    long time_step;   // length of timestep (seconds)

    int intervals;    // # of these timestep that are in the previous-level's timestep (not used for level 0: data tstep)

    float threshold;  // mass threshold for a layer to use this timestep (not used for level 0: data tstep)

    TSTEP_REC() : level(0), time_step(24 * 3600 / Global::Freq), intervals(1), threshold(0.0) {};

};

class  INPUT_REC { // climate-data input records
public:

    float S_n;	// net solar radiation (W/m^2)
    float I_lw;	// incoming longwave (thermal) rad (W/m^2)
    float T_a;	// air temp (C)
    float e_a;	// vapor pressure (Pa)
    float u;	// wind speed (m/sec)
    float T_g;	// soil temp at depth z_g (C)
    float F_g;	// soil flux at depth z_g (W/m^2)
};

class  PRECIP_REC { // precip-data input records
public:

    float	  m_pp;		// total precipitation mass (kg/m^2)
    float	  m_rain;	// mass of rain in precip   (kg/m^2)
    float	  m_snow;	// mass of snow in precip   (kg/m^2)
    float	  m_drift;	// mass of snow drift       (kg/m^2)
    float	  m_subl;	// mass of snow drift       (kg/m^2)
    float	  z_snow;	// depth of snow in precip  (m)
};

class ClassSnobalBase : public ClassModule {

public:

    ClassSnobalBase(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

    // declared variables

    //   snowpack information

    long* layer_count;    // number of layers in snowcover: 0, 1, or 2
    float* z_s;            // total snowcover thickness (m)
    float* z_s_0;          // active layer depth (m)
    float* z_s_l;          // lower layer depth (m)
    float* rho;            // average snowcover density (kg/m^3)
    float* m_s;            // snowcover's specific mass (kg/m^2). Init by init_snow.
    float* m_s_0;          // active layer specific mass (kg/m^2). Init by init_snow.
    float* m_s_l;          // lower layer specific mass (kg/m^2). Init by init_snow.
    float* T_s;            // average snowcover temp (K). Init by init_snow
    float* T_s_0;          // active snow layer temp (K)
    float* T_s_l;          // lower layer temp (C)
    float* cc_s;           // snowcover's cold content (J/m^2). Init by init_snow.
    float* cc_s_0;         // active layer cold content (J/m^2). Init by init_snow.
    float* cc_s_l;         // lower layer cold content (J/m^2). Init by init_snow.
    float* h2o_sat;        // % of liquid H2O saturation (relative water content, i.e., ratio of water in snowcover
//                                 to water that snowcover could hold at saturation)
    float* h2o_vol;        // liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless).init_snow
    float* h2o;            // liquid h2o content as specific mass(kg/m^2)
    float* h2o_max;        // max liquid h2o content as specific mass(kg/m^2)
    float* h2o_total;      // total liquid h2o: includes h2o in snowcover, melt, and rainfall (kg/m^2)

//   energy balance info for current timestep

    float* R_n;            // net allwave radiation (W/m^2)
    float* H;              // sensible heat xfr (W/m^2)
    float* L_v_E;          // latent heat xfr (W/m^2)
    float* G;              // heat xfr by conduction & diffusion from soil to snowcover (W/m^2)
    float* G_0;            // heat xfr by conduction & diffusion from soil or lower layer to active layer (W/m^2)
    float* M;              // advected heat from precip (W/m^2)
    float* delta_Q;        // change in snowcover's energy (W/m^2)
    float* delta_Q_0;      // change in active layer's energy (W/m^2)

//   mass balance vars for current timestep

    float* melt_direct_int;       // specific melt (kg/m^2 or m)
    float* sum;       // specific melt (kg/m^2 or m)
    float* SWE_change;       // interval change in SWE
    float* E_int;	    // mass flux by evap into air from active layer (kg/m^2/s)
    float* E_s_int;	    // mass of evap into air & soil from snowcover (kg/m^2)
    float* snowmelt_int;   // predicted specific runoff (m/sec)
    float* snowmeltD;      // daily predicted specific runoff (m/sec)
    float* snowmeltD_acc;      // daily predicted specific runoff accumulator (m/sec)

//   mass balance vars for variable timestep

    float* melt;        // specific melt (kg/m^2 or m)
    float* E;		 // mass flux by evap into air from active layer (kg/m^2/s)
    float* E_s;	 // mass of evap into air & soil from snowcover (kg/m^2)
    float* ro_predict;  // predicted specific runoff (m/sec)

    float* E_s_0;        // mass of evaporation to air (kg/m^2)
    float* E_s_l;        // mass of evaporation to soil (kg/m^2)
    float* E_l;	  // mass flux by evap/cond to soil (kg/m^2/s)

    float* E_s_0_int;        // mass of evaporation to air (kg/m^2)
    float* E_s_l_int;        // mass of evaporation to soil (kg/m^2)
    float* E_l_int;	  // mass flux by evap/cond to soil (kg/m^2/s)

//   precipitation info adjusted for current run timestep

    float* m_precip;	// specific mass of total precip (kg/m^2)
    float* m_rain;	// specific mass of rain in precip (kg/m^2)
    float* m_snow;	// specific mass in snow in precip (kg/m^2)
    float* m_drift;	// specific mass in snow drift (kg/m^2)
    float* m_subl;	// specific mass in snow sublimation (kg/m^2)
    float* rho_snow;   // density of snowfall (kg/m^3)
    float* T_pp;       // precip temp (K)
    float* z_snow;	// depth of snow in precip (m)

//   precipitation info for the current DATA timestep

    long* precip_now;	// precipitation occur for current timestep?
    float* T_rain;	// rain's temp (K)
    float* T_snow;	// snowfall's temp (K)
    float* h2o_sat_snow; // snowfall's % of liquid H2O saturation

//   local climate-data values for the current run timestep
    float* S_n;      // net solar radiation (W/m^2)
    float* I_lw;     // incoming longwave (thermal) rad (W/m^2)
    float* T_a;      // air temp (K)
    float* e_a;      // vapor pressure (Pa)
    float* u;        // wind speed (m/sec)
    float* T_g;      // soil temp at depth z_g (C)
    float* F_g;      // soil flux at depth z_g (W/m^2)

    long* isothermal; // melting?
    long* snowcover;  // snow on gnd at start of current timestep?
    long* stop_no_snow;       //

//   local variables
    float* P_a;            // air pressure (Pa)
    float* m_precip_cum;   //
    float* m_rain_cum;     //
    float* m_snow_cum;     //
    float* m_drift_cum;    //
    float* m_subl_cum;    //
    float* E_s_cum;        //
    float* cumsnowmelt;    //
    float* melt_direct_cum;       //
    float* Fault;       //

// debug variables
/*    float *Length;
    float **Length_array;
    float *Ustar;
    float **Ustar_array;
    float *e;
    float **e_array;
    float *h;
    float **h_array;
    long *ier;
    long **ier_array;
    long  *ArrayCnt; */

    // declared parameters

    //   measurement heights/depths

    const float* hru_elev;    // HRU elevation
    const float* basin_area;  // [BASIN]
    const float* hru_area;
    const float* KT_sand; // thermal conductivity of wet sand

    const long* relative_hts; // true if measurements heights, z_T and z_u, are relative to snow surface
                              // false if they are absolute heights above the ground
    const float* T_g_or_G_flux;    // soil temp or ground flux option
    const float* z_g;         // depth of soil temp meas (m)
    const float* z_u;         // height of wind measurement (m)
    const float* z_T;         // height of air temp & vapor pressure measurement (m)
    const float* z_0;         // roughness length
    const float* max_z_s_0;   // maximum active layer thickness (m)
    const float* max_h2o_vol; // max liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless)

//    void decl(void);

    void init(void);

    //    void run(void);

    void finish(bool good); // delete local storage used

    void init_snow(void);

    void _calc_layers(void);

    void _layer_mass(void);

    float _cold_content(float	temp, float	mass); // temperature of layer specific mass of layer

    void do_data_tstep(void);

    int _divide_tstep(TSTEP_REC* tstep); // record of timestep to be divided

    int _below_thold(float threshold);	 // current timestep's threshold for a layer's mass

    int _do_tstep(TSTEP_REC* tstep); // timestep's record

    int _e_bal(void);

    void _net_rad(void);

    int _h_le(void);

    float g_soil(
        float	rho,	// snow layer's density (kg/m^3)
        float	tsno,	// snow layer's temperature (K)
        float	tg,	// soil temperature (K)
        float	ds,	// snow layer's thickness (m)
        float	dg,	// dpeth of soil temperature measurement (m)
        float	pa);	// air pressure (Pa)

    float g_snow(
        float	rho1,	// upper snow layer's density (kg/m^3)
        float	rho2,	// lower  "     "        "    (kg/m^3)
        float	ts1,	// upper snow layer's temperature (K)
        float	ts2,	// lower  "     "         "       (K)
        float	ds1,	// upper snow layer's thickness (m)
        float	ds2,	// lower  "     "         "     (m)
        float	pa);	// air pressure (Pa)

    void _advec(void);

    void _mass_bal(void);

    void _time_compact(void);

    void _precip(void);

    void _snowmelt(void);

    void _drift(void);

    void _new_density(void);

    void _adj_snow(float delta_z_s, float delta_m_s); // change in snowcover's depth change is snowcover's mass

    void _evap_cond(void);

    void _h2o_compact(void);

    void _adj_layers(void);

    void _runoff(void);

    float new_tsno(float spm, float t0, float ccon);

    float heat_stor(float cp, float spm, float tdif);

    float sati(float tk);

    float ssxfr(float  k1, float  k2, float  t1, float  t2, float  d1, float  d2);

    float efcon(float k, float t, float p);

    int hle1(float press, float ta, float ts, float za, float ea, float es, float zq, float u, float zu,
        float z0, float& h, float& le, float& e);

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

class ClassSnobalX : public ClassSnobalBase {

    public:

    ClassSnobalX(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalX* klone(string name) const;

// variable climate-data inputs

    const float  *S_n_X;      // net solar radiation (W/m^2)
    const float  *I_lw_X;     // incoming longwave (thermal) rad (W/m^2)
    const float  *T_a_X;      // air temp (C)
    const float  *e_a_X;      // vapor pressure (Pa)
    const float  *u_X;        // wind speed (m/sec)
    const float  *T_g_X;      // soil temp at depth z_g (C)
    const float  *F_g_X;      // soil flux at depth z_g ()

// variable precipitation inputs

    const float  *m_precip_X;	// specific mass of total precip     (kg/m^2)
    const float  *m_rain_X;	// specific mass of rain in precip   (kg/m^2)
    const float  *m_snow_X;	// specific mass in snow in precip   (kg/m^2)
    const float  *m_drift_X;	// specific mass in snow drift       (kg/m^2)
    const float  *m_subl_X;	// specific mass of snow sublimation (kg/m^2)
    const float  *rho_snow_X;   // density of snowfall               (kg/m^3)
    const float  *T_pp_X;       // precip temp (C)


    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};


class ClassSnobalCRHM : public ClassSnobalBase {

    public:

    ClassSnobalCRHM(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalCRHM* klone(string name) const;

    float Qsi_;
    float Qli_;

// Observations

    const float *Qsi; // incoming solar radiation (W/m^2)
    const float *Qli; // incoming longwave (thermal) rad (W/m^2) long
    const float *T_g_Obs; // ground temperature at depth
    const float *F_g_Obs; // ground flux at depth

// variable climate-data inputs

    const float  *T_a_X;      // air temp (C) hru_t
    const float  *T_pp_X;       // precip temp (C) hru_t
    const float  *e_a_X;      // vapor pressure (Pa) hru_ea
    const float  *u_X;        // wind speed (m/sec)  hru_u
    const float  *Albedo;     // albedo ()
    const float  *Qsisn_Var;  // short wave at snow surface
    const float  *QsiS_Var;  // short wave at snow surface from Slope_Qsi
    const float  *Qlisn_Var;  // long wave at snow surface - through canopy
    const float  *QliVt_Var;  // long wave at snow surface - no canopy

// variable precipitation inputs

    const float  *m_precip_X;	// specific mass of total precip     (kg/m^2) net_p
    const float  *m_snow_X;	// specific mass in snow in precip   (kg/m^2) net_snow
    const float  *m_drift_X;	// specific mass in snow drift       (kg/m^2) Drift
    const float  *m_subl_X;	// specific mass of snow sublimation (kg/m^2) Subl

// put variable precipitation inputs

    float  *m_rain_X;	// specific mass of rain in precip   (kg/m^2) net_rain

// parameters

    const float  *rho_snow_X;       // density of snowfall               (kg/m^3)
    const float  *T_g_X;            // soil temp at depth z_g (C)
    const float  *F_g_X;            // soil flux at depth z_g (C)
    const long   *rain_soil_snow;  //
    float *snow_store; // accumulates snow till > 1+mm

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};




class ClassGrow_Crop : public ClassModule {
public:

ClassGrow_Crop(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Crop_Ht;

// declared parameters
const float *Ht;
const float *Crop_Grow_Rate;
const float *JCrop_Start;
const float *JCrop_Mature;
const float *JCrop_Harvest;
const float *Init_Crop_Ht;

// variable inputs

void decl(void);
void init(void);
void run(void);

ClassGrow_Crop* klone(string name) const;
};


#endif
