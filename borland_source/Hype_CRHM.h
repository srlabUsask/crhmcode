// 05/09/19
//---------------------------------------------------------------------------
#ifndef Hype_CRHMH
#define Hype_CRHMH
//---------------------------------------------------------------------------

#include "ClassModule.h"

#define numsubstances 5
#define maxsoillayers 3

using namespace std;

class ClassWQ_Soil : public ClassModule {
public:

ClassWQ_Soil(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;
long Sub;
long FaultsAllowed;

// declared variables
long *current_getstep;
float *funct_unmixed_layer;
float *Sd;
float *Sd_conc;
float **Sd_conc_lay;
float *gw;
float *gw_conc;
float **gw_conc_lay;
float *solute_deposit;
float *cum_solute_deposit;
float *soil_rechr;
float *soil_rechr_conc;
float **soil_rechr_conc_lay;
float *potential;
float *potential_mWQ;
float **potential_mWQ_lay;
float *direct_excs;
float *direct_excs_mWQ;
float **direct_excs_mWQ_lay;
float *soil_moist;
float *soil_moist_conc;
float **soil_moist_conc_lay;
float *soil_lower_max;
float *soil_lower;
float *soil_lower_conc;
float **soil_lower_conc_lay;
float *soil_gw;
float *soil_gw_conc;
float **soil_gw_conc_lay;
float *gw_flow;
float *gw_flow_conc;
float **gw_flow_conc_lay;
float *soil_ssr;
float *soil_ssr_conc;
float **soil_ssr_conc_lay;
float *rechr_ssr;
float *rechr_ssr_conc;
float **rechr_ssr_conc_lay;
float *soil_runoff;
float *soil_runoff_conc;
float **soil_runoff_conc_lay;
float *cum_soil_ssr;
float *cum_soil_ssr_mWQ;
float **cum_soil_ssr_mWQ_lay;
float *cum_rechr_ssr;
float *cum_Sd_ssr;
float *cum_Sd_gw;
float *cum_lower_ssr;
float *cum_rechr_ssr_mWQ;
float **cum_rechr_ssr_mWQ_lay;
float *cum_soil_runoff;
float *cum_soil_runoff_mWQ;
float **cum_soil_runoff_mWQ_lay;
float *cum_runoff_to_ssr;
float *cum_runoff_to_Sd;
float *cum_runoff_to_Sd_mWQ;
float **cum_runoff_to_Sd_mWQ_lay;
float *cum_redirected_residual;
float *cum_redirected_residual_mWQ;
float **cum_redirected_residual_mWQ_lay;
float *soil_gw_D;
float *soil_ssr_D;
float *gw_flow_D;
float *soil_runoff_D;
float *HK_V;
float *HK_A;
float *culvert_Q;
float *culvert_water_H;
float *culvert_water_A;
float *culvert_water_V;
float *culvert_over_Q;
float *culvert_evap;
float *cum_culvert;
float *cum_culvert_over;
float *HD;
float *redirected_residual;
float *redirected_residual_conc;
float **redirected_residual_conc_lay;
float *infil_act;
float *infil_act_conc;
float **infil_act_conc_lay;
float *cum_infil_act;
float *cum_infil_act_mWQ;
float **cum_infil_act_mWQ_lay;
float *infil_act_D;
float *tile_flow;
float *Dequiv_depth;
float *x;
float *Dw;

// local variables
float *cum_soil_gw;
float *cum_soil_gw_mWQ;
float **cum_soil_gw_mWQ_lay;
float *cum_gw_flow;
float *cum_gw_flow_mWQ;
float **cum_gw_flow_mWQ_lay;
float *cum_hru_condense;
float *cum_Sd_evap;
float *soil_moist_Init;
float **soil_moist_conc_Init_lay;
float *soil_bottom_Init;
float **soil_bottom_conc_Init_lay;
float *soil_rechr_Init;
float **soil_top_conc_Init_lay;
float *Sd_Init;
float *gw_Init;
float *soil_moist_conc_Init;
float *soil_bottom_conc_Init;
float *soil_top_conc_Init;
float *Sd_conc_Init;
float **Sd_conc_Init_lay;
float *gw_conc_Init;
float **gw_conc_Init_lay;

float *soil_rechr_change_mWQ;
float **soil_rechr_change_mWQ_lay;

float *soil_moist_change_mWQ;
float **soil_moist_change_mWQ_lay;

float *soil_bottom_change_mWQ;
float **soil_bottom_change_mWQ_lay;

float *Sd_change_mWQ;
float **Sd_change_mWQ_lay;

float *gw_change_mWQ;
float **gw_change_mWQ_lay;

float *snowinfil_buf;
float *runoff_buf;
float *meltrunoff_buf;
float *hru_evap_buf;

// declared parameters
const float *Sdmax;
const float *Sdinit;
const float *Sd_conc_init;
const float **Sd_conc_init_lay;
const float *gw_max;
const float *gw_init;
const float *gw_conc_init;
const float **gw_conc_init_lay;
const float *gw_K;
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *soil_rechr_max;
const float *soil_rechr_init;
const float *soil_moist_max;
const float *soil_moist_init;
const float *soil_gw_K;
const float *rechr_ssr_K;
const float *lower_ssr_K;
const float *Sd_ssr_K;
const float *Sd_gw_K;
const float *rain_conc;
const float **rain_conc_lay;
const float *Atmos_mWQ;
const float **Atmos_mWQ_lay;
const float *unmixed_surface_layer;
const float *channel_slope;
const float *CV_SWE;
const float *side_slope;
const float *culvert_diam;
const float *culvert_water_Dmax;
const float *number_culverts;

const float *Ka;
const float *Kb;
const float *Di;
const float *Dd;
const float *soil_poro_moist;
const float *L;
const float *r;


const long *soil_withdrawal;
const long **soil_withdrawal_Tables;
const long *culvert_type;
const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;
const long *calcN; // Status of nitrogen simulation
const long *calcP; // Status of phosphorus simulation
const long *calcC; // Status of organic carbon simulation


// variable inputs
const float *infil;
const float *snowinfil;
const float *meltrunoff; // frozen melt runoff
const float *runoff;     // liquid runoff
const float *hru_evap;
const float *SWE;
const float *SWE_max;
const float *SWE_conc;
const float **SWE_conc_lay;

// variable put inputs
float *conc_top;
float **conc_top_lay;
float *conc_bottom;
float **conc_bottom_lay;
float *conc_below;
float **conc_below_lay;

// variable put inputs
float *hru_actet;
float *hru_cum_actet;

// local allocated arrays

float *redirected_residual_0;
float *Sd_0;
float *gw_0;
float *soil_rechr_0;
float *soil_moist_0;
float *soil_lower_0;
float *hru_evap_0;
float *gw_flow_0;
float *hru_actet_0;
float *hru_cum_actet_0;
float *cum_redirected_residual_0;
float *cum_hru_condense_0;
float *cum_Sd_evap_0;
float *cum_Sd_ssr_0;
float *cum_Sd_gw_0;
float *cum_lower_ssr_0;
float *cum_infil_act_0;
float *cum_gw_flow_0;
float *cum_soil_ssr_0;
float *cum_rechr_ssr_0;
float *cum_soil_runoff_0;
float *cum_runoff_to_Sd_0;
float *cum_runoff_to_ssr_0;
float *cum_soil_gw_0;
float *cum_solute_deposit_0;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Add_WQ(const long hru, float *var, float **var_cWQ, float *var2, float **var2_cWQ, float *var3, float **var3_cWQ);
void Set_WQ(const long hru, float *var, float *var_cWQ, float amount, float amount_cWQ);
void Reset_Basin_WQ(const long hru, float *var, float *var_cWQ);
void Reset_WQ(const long hru, float *var, float *var_cWQ);
void Reset_WQ(const long hru, float *var, float **var_cWQ_lay);
void Save();
void Restore(const long hh);
void copy_array(float *from, float *to);
// void copy_basin(float *from, float *to);
void restore_hru(float *from, float *to, const long hh);
float FunctX(const float x);
ClassWQ_Soil* klone(string name) const;
};

class ClassWQ_Netroute : public ClassModule {
public:

ClassWQ_Netroute(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;
long Sub;

// declared variables
float *inflow;
float *inflow_mWQ;
float **inflow_mWQ_lay;
float *cuminflow;
float *cuminflow_mWQ;
float **cuminflow_mWQ_lay;
float *outflow;
float *outflow_mWQ;
float **outflow_mWQ_lay;
float *outflow_diverted;
float *outflow_diverted_conc;
float **outflow_diverted_conc_lay;
float *cumoutflow_diverted;
float *cumoutflow_diverted_mWQ;
float **cumoutflow_diverted_mWQ_lay;
float *cumoutflow;
float *cumoutflow_mWQ;
float **cumoutflow_mWQ_lay;
float *gwinflow;
float *gwinflow_mWQ;
float **gwinflow_mWQ_lay;
float *gwoutflow_diverted;
float *gwoutflow_diverted_conc;
float **gwoutflow_diverted_conc_lay;
float *gwcumoutflow_diverted;
float *gwcumoutflow_diverted_mWQ;
float **gwcumoutflow_diverted_mWQ_lay;

float *ssrinflow;
float *ssrinflow_mWQ;
float **ssrinflow_mWQ_lay;
float *ssrcuminflow;
float *ssrcuminflow_mWQ;
float **ssrcuminflow_mWQ_lay;
float *ssroutflow;
float *ssroutflow_mWQ;
float **ssroutflow_mWQ_lay;
float *ssrcumoutflow;
float *ssrcumoutflow_mWQ;
float **ssrcumoutflow_mWQ_lay;

float *runinflow;
float *runinflow_mWQ;
float **runinflow_mWQ_lay;
float *runcuminflow;
float *runcuminflow_mWQ;
float **runcuminflow_mWQ_lay;
float *runoutflow;
float *runoutflow_mWQ;
float **runoutflow_mWQ_lay;
float *runcumoutflow;
float *runcumoutflow_mWQ;
float **runcumoutflow_mWQ_lay;

float *gwoutflow;
float *gwoutflow_mWQ;
float **gwoutflow_mWQ_lay;
float *gwcuminflow;
float *gwcuminflow_mWQ;
float **gwcuminflow_mWQ_lay;
float *gwcumoutflow;
float *gwcumoutflow_mWQ;
float **gwcumoutflow_mWQ_lay;

float *basinflow;     // [BASIN] all HRUs
float *basinflow_conc;     // [BASIN] all HRUs
float **basinflow_conc_lay;     // [BASIN] all HRUs
float *basinflow_s;   // [BASIN] all HRUs
float *cumbasinflow;  // [BASIN] all HRUs
float *cumbasinflow_mWQ;  // [BASIN] all HRUs
float **cumbasinflow_mWQ_lay;  // [BASIN] all HRUs
float *basingw;       // [BASIN} all HRUs
float *basingw_conc;       // [BASIN} all HRUs
float **basingw_conc_lay;       // [BASIN} all HRUs
float *basingw_s;     // [BASIN} all HRUs
float *cumbasingw;    // [BASIN} all HRUs
float *cumbasingw_mWQ;    // [BASIN} all HRUs
float **cumbasingw_mWQ_lay;    // [BASIN} all HRUs

float *soil_ssr_Buf;    // buffered
float *soil_ssr_Buf_conc;    // buffered
float **soil_ssr_Buf_conc_lay;    // buffered
float *soil_runoff_Buf; // buffered
float *soil_runoff_Buf_conc; // buffered
float **soil_runoff_Buf_conc_lay; // buffered
float *soil_gw_Buf;     // buffered
float *soil_gw_Buf_conc;     // buffered
float **soil_gw_Buf_conc_lay;     // buffered

float *HRU_cumbasinflow;
float *HRU_cumbasinflow_mWQ;
float **HRU_cumbasinflow_mWQ_lay;
float *cum_to_Sd;
float *cum_to_Sd_mWQ;
float **cum_to_Sd_mWQ_lay;
float *cum_to_soil_rechr;
float *cum_to_soil_rechr_mWQ;
float **cum_to_soil_rechr_mWQ_lay;
float *cum_preferential_flow_to_gw;

ClassMuskingum *hruDelay;
ClassClark *Clark_hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const float *route_n;         // [nhru]
const float *route_R;         // [nhru]
const float *route_S0;        // [nhru]
const float *route_L;         // [nhru]
const float *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const float *Kstorage;
const float *Lag;
const float *ssrKstorage;
const float *ssrLag;
const float *runKstorage;
const float *runLag;
const float *gwKstorage;
const float *gwLag;

const float *basin_area;        // [BASIN]
const float *hru_area;
const long  *whereto;
const long  *order;
const long  *gwwhereto;
const float *Sdmax;
const float *soil_rechr_max;
const long  *preferential_flow; // [nhru]
const long  *Sd_ByPass;
const long  *soil_rechr_ByPass;

// variable inputs
const float *soil_gw;
const float *soil_gw_conc;
const float **soil_gw_conc_lay;
const float *soil_ssr_gw_mWQ;
const float **soil_ssr_gw_mWQ_lay;
const float *soil_runoff_gw_mWQ;
const float **soil_runoff_gw_mWQ_lay;
const float *soil_ssr;
const float *soil_ssr_conc;
const float **soil_ssr_conc_lay;
const float *soil_runoff;
const float *soil_runoff_conc;
const float **soil_runoff_conc_lay;

// variable puts
float *Sd;
float *Sd_conc;
float **Sd_conc_lay;
float *soil_moist;
float *soil_moist_conc;
float **soil_moist_conc_lay;
float *soil_lower;
float *soil_lower_conc;
float **soil_lower_conc_lay;
float *soil_rechr;
float *soil_rechr_conc;
float **soil_rechr_conc_lay;
float *redirected_residual;
float *redirected_residual_conc;
float **redirected_residual_conc_lay;
float *cum_redirected_residual;
float *cum_redirected_residual_mWQ;
float **cum_redirected_residual_mWQ_lay;
float *gw;
float *gw_conc;
float **gw_conc_lay;
float *conc_top;
float **conc_top_lay;
float *conc_bottom;
float **conc_bottom_lay;
float *conc_below;
float **conc_below_lay;

// local allocated arrays

float *basinflow_0;
float *basingw_0;
float *cumbasinflow_0;
float *cumbasingw_0;

float *outflow_0;
float *gwoutflow_0;
float *redirected_residual_0;
float *Sd_0;
float *gw_0;
float *soil_rechr_0;
float *soil_moist_0;
float *soil_lower_0;
float *outflow_diverted_0;
float *cum_redirected_residual_0;
float *cuminflow_0;
float *cumoutflow_0;
float *cumoutflow_diverted_0;
float *cum_to_Sd_0;
float *cum_to_soil_rechr_0;
float *gwcuminflow_0;
float *gwcumoutflow_0;
float *gwcumoutflow_diverted_0;
float *ssrcuminflow_0;
float *ssrcumoutflow_0;
float *runcuminflow_0;
float *runcumoutflow_0;
float *cum_preferential_flow_to_gw_0;
float *HRU_cumbasinflow_0;
//float *Used_mWQ;    // [BASIN}
//float **Used_mWQ_lay;    // [BASIN} 
float *Ktravel;         // [nhru] Muskingum

ClassMuskingum **hruDelay_cWQ; // [numsubstances] handled locally
ClassClark **Clark_hruDelay_cWQ;
ClassClark **ssrDelay_cWQ;
ClassClark **runDelay_cWQ;
ClassClark **gwDelay_cWQ;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Set_WQ(long hru, float *var, float *var_conc, float amount_conc, float amount);
void Reset_Basin_WQ(long hru, float *var, float *var_conc);
void Reset_WQ(long hru, float *var, float **var_cWQ_lay);

virtual float Function1(float *I, long hh);
virtual float Function2(float *X, long hh);

ClassWQ_Netroute* klone(string name) const;
};

class ClassWQ_pbsm : public ClassModule {
public:

ClassWQ_pbsm(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

float hru_u_;

// declared variables

float *SWE_max;
float *SWE;
float *SWE_conc;
float **SWE_conc_lay;
float *Subl;
float *Subl_conc;
float **Subl_conc_lay;
float *Drift_in;
float *Drift_in_conc;
float **Drift_in_conc_lay;
float *Drift_out;       // HRU composite drift
float *Drift_out_conc;  // HRU composite drift
float **Drift_out_conc_lay;  // HRU composite drift
float *cumSubl;
float *cumSubl_mWQ;
float **cumSubl_mWQ_lay;
float *cumDriftOut;
float *cumDriftOut_mWQ;
float **cumDriftOut_mWQ_lay;
float *cumDriftIn;
float *cumDriftIn_mWQ;
float **cumDriftIn_mWQ_lay;
float *cumSno;
float *cumSno_mWQ;
float **cumSno_mWQ_lay;
float *snowdepth;
float *BasinSnowLoss;
float *BasinSnowLoss_mWQ;
float **BasinSnowLoss_mWQ_lay;
float *BasinSnowGain;
float *BasinSnowGain_mWQ;
float **BasinSnowGain_mWQ_lay;
float *cumBasinSnowLoss;
float *cumBasinSnowLoss_mWQ;
float **cumBasinSnowLoss_mWQ_lay;
float *cumBasinSnowGain;
float *cumBasinSnowGain_mWQ;
float **cumBasinSnowGain_mWQ_lay;
float *SublH;
float *DriftH;
float *Prob;
float *SnowAge;
float *SWE_Init;
long  *DrySnow;

// declared parameters
const float *fetch;
const float *Ht;
const float *distrib;
const float *basin_area;
const float *hru_area;
const float *A_S;
const float *u_D;
const float *Drift_offset;
const float *Drift_slope;
const float *Subl_offset;
const float *Subl_slope;
const float *N_S;
const float *rain_conc;
const float **rain_conc_lay;
const float *snow_conc;
const float **snow_conc_lay;
const float *Atmos_mWQ;
const float **Atmos_mWQ_lay;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const float *hru_t;
const float *hru_rh;
const float *hru_u;
const float *hru_Uadjust;
const float *net_snow;
const long  *hru_newsnow;

// local allocated arrays
float *BasinSnowGain_0;
float *cumBasinSnowGain_0;
float *BasinSnowLoss_0;
float *cumBasinSnowLoss_0;

float *hru_basin;
float *SWE_0;
float *SWE_Init_0;
float *z_s_0;
float *rho_0;

float *Drift_out_0;
float *Drift_in_0;
float *cumDriftIn_0;
float *cumDriftOut_0;
float *cumSubl_0;
float *Subl_0;
float *SublH_0;
float *DriftH_0;
float *cumSno_0;
float *Prob_0;
float *SnowAge_0;
long  *DrySnow_0;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Reset_WQ(long hru, float *var, float **var_WQ_lay);
void Save();
void Restore(const long hh);
void copy_array(long *from, long *to);
void copy_array(float *from, float *to);
void copy_basin(float *from, float *to);
void restore_hru(float *from, float *to, const long hh);
void restore_hru(long *from, long *to, const long hh);

ClassWQ_pbsm* klone(string name) const;
}; 

class ClassWQ_Netroute_M_D : public ClassModule {
public:

ClassWQ_Netroute_M_D(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;
long Sub;

// declared variables
float *inflow;
float *inflow_mWQ;
float **inflow_mWQ_lay;
float *cuminflow;
float *cuminflow_mWQ;
float **cuminflow_mWQ_lay;
float *outflow;
float *outflow_mWQ;
float **outflow_mWQ_lay;
float *outflow_diverted;
float *outflow_diverted_conc;
float **outflow_diverted_conc_lay;
float *cumoutflow_diverted;
float *cumoutflow_diverted_mWQ;
float **cumoutflow_diverted_mWQ_lay;
float *cumoutflow;
float *cumoutflow_mWQ;
float **cumoutflow_mWQ_lay;
float *cumscaling_boost;    // [nhru]
float *gwinflow;
float *gwinflow_mWQ;
float **gwinflow_mWQ_lay;
float *gwoutflow_diverted;
float *gwoutflow_diverted_conc;
float **gwoutflow_diverted_conc_lay;
float *gwcumoutflow_diverted;
float *gwcumoutflow_diverted_mWQ;
float **gwcumoutflow_diverted_mWQ_lay;

float *ssrinflow;
float *ssrinflow_mWQ;
float **ssrinflow_mWQ_lay;
float *ssrcuminflow;
float *ssrcuminflow_mWQ;
float **ssrcuminflow_mWQ_lay;
float *ssroutflow;
float *ssroutflow_mWQ;
float **ssroutflow_mWQ_lay;
float *ssrcumoutflow;
float *ssrcumoutflow_mWQ;
float **ssrcumoutflow_mWQ_lay;

float *runinflow;
float *runinflow_mWQ;
float **runinflow_mWQ_lay;
float *runcuminflow;
float *runcuminflow_mWQ;
float **runcuminflow_mWQ_lay;
float *runoutflow;
float *runoutflow_mWQ;
float **runoutflow_mWQ_lay;
float *runcumoutflow;
float *runcumoutflow_mWQ;
float **runcumoutflow_mWQ_lay;

float *gwoutflow;
float *gwoutflow_mWQ;
float **gwoutflow_mWQ_lay;
float *gwcuminflow;
float *gwcuminflow_mWQ;
float **gwcuminflow_mWQ_lay;
float *gwcumoutflow;
float *gwcumoutflow_mWQ;
float **gwcumoutflow_mWQ_lay;

float *basinflow;     // [BASIN] all HRUs
float *basinflow_conc;     // [BASIN] all HRUs
float **basinflow_conc_lay;     // [BASIN] all HRUs
float *basinflow_s;   // [BASIN] all HRUs
float *cumbasinflow;  // [BASIN] all HRUs
float *cumbasinflow_mWQ;  // [BASIN] all HRUs
float **cumbasinflow_mWQ_lay;  // [BASIN] all HRUs
float *basingw;       // [BASIN} all HRUs
float *basingw_conc;       // [BASIN} all HRUs
float **basingw_conc_lay;       // [BASIN} all HRUs
float *basingw_s;     // [BASIN} all HRUs
float *cumbasingw;    // [BASIN} all HRUs
float *cumbasingw_mWQ;    // [BASIN} all HRUs
float **cumbasingw_mWQ_lay;    // [BASIN} all HRUs

float *soil_ssr_Buf;    // buffered
float *soil_ssr_Buf_conc;    // buffered
float **soil_ssr_Buf_conc_lay;    // buffered
float *soil_runoff_Buf; // buffered
float *soil_runoff_Buf_conc; // buffered
float **soil_runoff_Buf_conc_lay; // buffered
float *soil_gw_Buf;     // buffered
float *soil_gw_Buf_conc;     // buffered
float **soil_gw_Buf_conc_lay;     // buffered

float *HRU_cumbasinflow;
float *HRU_cumbasinflow_mWQ;
float **HRU_cumbasinflow_mWQ_lay;
float *cum_to_Sd;
float *cum_to_Sd_mWQ;
float **cum_to_Sd_mWQ_lay;
float *cum_to_soil_rechr;
float *cum_to_soil_rechr_mWQ;
float **cum_to_soil_rechr_mWQ_lay;
float *Used;    // [BASIN}
float *Used_mWQ;    // [BASIN}
float **Used_mWQ_lay;    // [BASIN}

float *distrib_sum;
float *Ktravel;         // [nhru] Muskingum
float *cum_preferential_flow_to_gw;

ClassMuskingum *hruDelay;
ClassClark *Clark_hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const float *route_n;         // [nhru]
const float *route_R;         // [nhru]
const float *route_S0;        // [nhru]
const float *route_L;         // [nhru]
const float *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const float *Kstorage;
const float *Lag;             // [nhru]
const float *ssrKstorage;     // [nhru]
const float *ssrLag;          // [nhru]
const float *runKstorage;     // [nhru]
const float *runLag;          // [nhru]
const float *gwKstorage;
const float *gwLag;
const long  *gwwhereto;       // [nhru]

const float *basin_area;      // [BASIN]
const float *hru_area;        // [nhru]
const float *distrib;
const float *distrib_Basin;
const float **distrib_hru;
const float *Sdmax;           // [nhru]
const float *soil_rechr_max;  // [nhru]
const long  *order;
const long  *preferential_flow; // [nhru]
const long  *Sd_ByPass;       // [nhru]

const float *scaling_factor;    // temporary modification

const long  *soil_rechr_ByPass;

// variable inputs
const float *soil_gw;
const float *soil_gw_conc;
const float **soil_gw_conc_lay;
const float *soil_ssr;
const float *soil_ssr_conc;
const float **soil_ssr_conc_lay;
const float *soil_ssr_gw_mWQ;
const float *soil_runoff;
const float *soil_runoff_conc;
const float **soil_runoff_conc_lay;
const float *soil_runoff_gw_mWQ;

// variable puts
float *Sd;
float *Sd_conc;
float **Sd_conc_lay;
float *soil_moist;
float *soil_moist_conc;
float **soil_moist_conc_lay;
float *soil_lower;
float *soil_lower_conc;
float **soil_lower_conc_lay;
float *soil_rechr;
float *soil_rechr_conc;
float **soil_rechr_conc_lay;
float *redirected_residual;
float *redirected_residual_conc;
float **redirected_residual_conc_lay;
float *cum_redirected_residual;
float *cum_redirected_residual_mWQ;
float **cum_redirected_residual_mWQ_lay;
float *gw;
float *gw_conc;
float **gw_conc_lay;
float *conc_top;
float **conc_top_lay;
float *conc_bottom;
float **conc_bottom_lay;
float *conc_below;
float **conc_below_lay;

// local allocated arrays

float *Amount_In_basin;
float *Amount_In_pref;
float *Amount_In_Soil;
float *Amount_In_Sd;
float *gwAmount_In_Soil;
float *gwAmount_In_Sd;

ClassMuskingum **hruDelay_mWQ; // [numsubstances] handled locally
ClassClark **Clark_hruDelay_mWQ;

ClassClark **ssrDelay_mWQ;
ClassClark **runDelay_mWQ;
ClassClark **gwDelay_mWQ;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Set_WQ(long hru, float *var, float *var_conc, float amount_conc, float amount);
void Reset_Basin_WQ(long hru, float *var, float *var_conc);
void Reset_WQ(long hru, float *var, float **var_conc_lay);

virtual float Function1(float *I, long hh);
virtual float Function2(float *X, long hh);

ClassWQ_Netroute_M_D* klone(string name) const;
};

class ClassWQ_Test_Hype : public ClassModule {
public:

ClassWQ_Test_Hype(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *infil;
float *snowinfil;
float *runoff;
float *meltrunoff;
float *hru_evap;
float *hru_cum_evap;
float *hru_cum_actet;
float *hru_actet;
float *net_rain;
float *SWE;
float *SWE_max;
float *hru_t;
float *SWE_conc;
float **SWE_conc_lay;

float *soil_moist;
float *soil_rechr;

// declared parameters
const float* infil_0;
const float* snowinfil_0;
const float* runoff_0;
const float* meltrunoff_0;
const float* hru_evap_0;
const float* hru_actet_0;
const float* hru_cum_evap_0;
const float* hru_cum_actet_0;
const float* net_rain_0;
const float* SWE_0;
const float* hru_t_0;
const float* SWE_conc_0;
const float** SWE_conc_lay_0;

const float* soil_rechr_0;
const float* soil_moist_0;
const float* soil_rechr_max;
const float* soil_moist_max;

const long  *Julian_start;
const long  *Julian_end;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_Test_Hype* klone(string name) const;
};

class ClassWQ_pbsmSnobal : public ClassModule {
public:

ClassWQ_pbsmSnobal(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

float hru_u_;

// declared variables

float *SWE_max;
float *SWE_conc;
float **SWE_conc_lay;
float *Subl;
float *Subl_conc;
float **Subl_conc_lay;
float *Drift;
float *Drift_in;
float *Drift_in_conc;
float **Drift_in_conc_lay;
float *Drift_out;       // HRU composite drift
float *Drift_out_conc;  // HRU composite drift
float **Drift_out_conc_lay;  // HRU composite drift
float *cumSubl;
float *cumSubl_mWQ;
float **cumSubl_mWQ_lay;
float *cumDriftOut;
float *cumDriftOut_mWQ;
float **cumDriftOut_mWQ_lay;
float *cumDrift;
float *cumDriftIn;
float *cumDriftIn_mWQ;
float **cumDriftIn_mWQ_lay;
float *cumSno;
float *cumSno_mWQ;
float **cumSno_mWQ_lay;
float *snowdepth;
float *BasinSnowLoss;
float *BasinSnowLoss_mWQ;
float **BasinSnowLoss_mWQ_lay;
float *BasinSnowGain;
float *BasinSnowGain_mWQ;
float **BasinSnowGain_mWQ_lay;
float *cumBasinSnowLoss;
float *cumBasinSnowLoss_mWQ;
float **cumBasinSnowLoss_mWQ_lay;
float *cumBasinSnowGain;
float *cumBasinSnowGain_mWQ;
float **cumBasinSnowGain_mWQ_lay;
float *SublH;
float *DriftH;
float *Prob;
float *SnowAge;
float *SWE_Init;
long  *DrySnow;

// declared parameters
const float *fetch;
const float *Ht;
const float *distrib;
const float *basin_area;
const float *hru_area;
const float *A_S;
const float *u_D;
const float *Drift_offset;
const float *Drift_slope;
const float *Subl_offset;
const float *Subl_slope;
const float *N_S;
const float *rain_conc;
const float **rain_conc_lay;
const float *snow_conc;
const float **snow_conc_lay;
const float *Atmos_mWQ;
const float **Atmos_mWQ_lay;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// put variable inputs
float *SWE; // actually m_s

// variable inputs
const float *z_s;
const float *rho;
const float *hru_t;
const float *hru_u;
const float *hru_Uadjust;
const float *net_snow;
const long  *hru_newsnow;
const float *hru_ea;

// local allocated arrays

float *BasinSnowGain_0;
float *cumBasinSnowGain_0;
float *BasinSnowLoss_0;
float *cumBasinSnowLoss_0;

float *hru_basin;
float *SWE_0;
float *SWE_Init_0;
float *z_s_0;
float *rho_0;

float *Drift_out_0;
float *Drift_in_0;
float *cumDriftIn_0;
float *cumDriftOut_0;
float *cumSubl_0;
float *Subl_0;
float *cumSno_0;
float *SnowAge_0;
long *DrySnow_0;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Reset_WQ(long hru, float *var, float **var_WQ_lay);
void Save();
void Restore(const long hh);
void copy_array(float *from, float *to);
void copy_array(long *from, long *to);
void copy_basin(float *from, float *to);
void restore_hru(float *from, float *to, const long hh);
void restore_hru(long *from, long *to, const long hh);

ClassWQ_pbsmSnobal* klone(string name) const;
};

class ClassWQ_mass_conc : public ClassModule {
public:

ClassWQ_mass_conc(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *inflow_conc;
float **inflow_conc_lay;
float *outflow_conc;
float **outflow_conc_lay;
float *runoutflow_conc;
float **runoutflow_conc_lay;
float *ssroutflow_conc;
float **ssroutflow_conc_lay;
float *gwoutflow_conc;
float **gwoutflow_conc_lay;

// declared parameters

// variable inputs
const float *inflow;
const float *inflow_mWQ;
const float **inflow_mWQ_lay;
const float *outflow;
const float *outflow_mWQ;
const float **outflow_mWQ_lay;
const float *runoutflow;
const float *runoutflow_mWQ;
const float **runoutflow_mWQ_lay;
const float *ssroutflow;
const float *ssroutflow_mWQ;
const float **ssroutflow_mWQ_lay;
const float *gwoutflow;
const float *gwoutflow_mWQ;
const float **gwoutflow_mWQ_lay;

void decl(void);
void init(void);
void run(void);

void Reset_WQ(float **var_lay);
void mass_to_conc(const float *var, const float **var_mWQ, float **var_conc);

ClassWQ_mass_conc* klone(string name) const;
};

class ClassWQ_Substitute_Hype : public ClassModule {
public:

ClassWQ_Substitute_Hype(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *conc_top;   // concentration of inorganic nitrogen *** from soilstate
float **conc_top_lay;
float *conc_bottom;   // concentration of organic nitrogen *** from soilstate
float **conc_bottom_lay;
float *conc_below;   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
float **conc_below_lay;

// declared parameters

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_Substitute_Hype* klone(string name) const;
};

class ClassWQ_Gen_Mass_Bal : public ClassModule {
public:

ClassWQ_Gen_Mass_Bal(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const float *basin_area;   // [BASIN]
const float *hru_area;

const float *In_obs;

const float *In_pbsm;
const float *Out_pbsm;
const float *Atmos_pbsm;

const float *In_WQ_pbsm;
const float *Out_WQ_pbsm;
const float *Atmos_WQ_pbsm;

const float *In_PrairieInfiltration;

const float *Atmos_evap;

float *WQ_Total_mass;
float *WQ_Total_mass_in;
float *WQ_Total_mass_out;
float *WQ_Total_mass_atmos;
float *WQ_hru_Total_mass;
float *WQ_hru_Total_mass_in;
float *WQ_hru_Total_mass_out;
float *WQ_hru_Total_mass_atmos;

TStringList *In_Vars_WQ_pbsm;
TStringList *In_Vars_WQ_pbsmSnowbal;
TStringList *In_Vars_WQ_pbsm_first;
TStringList *Out_Vars_WQ_pbsm;
TStringList *Out_Vars_WQ_pbsmSnowbal;
TStringList *Out_Vars_WQ_Netroute_M_D;
TStringList *Out_Vars_WQ_pbsm_last;
TStringList *Atmos_Vars_WQ_pbsm;
TStringList *Atmos_Vars_WQ_pbsmSnowbal;

TStringList *In_Vars_WQ_Soil;
TStringList *Out_Vars_WQ_Soil;
TStringList *Atmos_Vars_WQ_Soil;

//declared variables
long *run_ID;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Add_mass(TStringList* In_Vars_obs);
void Add_mass_first(TStringList* In_Vars_obs);
void Subtract_mass(TStringList* In_Vars_obs);
void Subtract_mass_last(TStringList* In_Vars_obs);
void Transfer_mass(TStringList* In_Vars_obs);
void mass_to_Atmosphere(TStringList* In_Vars_obs);

ClassWQ_Gen_Mass_Bal* klone(string name) const;
};

class ClassGrow_crops_annually : public ClassModule {
public:

ClassGrow_crops_annually(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long ObsCnt_N;
long ObsCnt_P;
long ObsCntMan_N;
long ObsCntMan_P;
long ObsCntRes_N;
long ObsCntRes_P;
long ObsCntPeriod_fert_man;

// declared variables
float *Fert_N_amount1;
float *Fert_P_amount1;
float *Man_N_amount1;
float *Man_P_amount1;
float *Fert_N_amount2;
float *Fert_P_amount2;
float *Man_N_amount2;
float *Man_P_amount2;
float *Res_N_amount;
float *Res_P_amount;
float *fert_man_period;
long *LockOut;

long  *SecondDown_fertN;
long  *SecondDown_fertP;
long  *SecondDown_manN;
long  *SecondDown_manP;

// declared parameters
const long  *Ag_YearStart;

// put parameters
const float *Htmax;
const float *Init_Crop_Ht_1;
const float *Crop_Grow_Rate_1;
const float *JCrop_Start_1;
const float *JCrop_Harvest_1;
const float *Crop_Htmax_1;
const float *Init_Crop_Ht_2;
const float *Crop_Grow_Rate_2;
const float *JCrop_Start_2;
const float *JCrop_Harvest_2;
const float *Crop_Htmax_2;
float *Ht;
float *fertNamount1;
float *fertPamount1;
float *fertNamount2;
float *fertPamount2;
float *manNamount1;
float *manPamount1;
float *manNamount2;
float *manPamount2;
float *resNamount;
float *resPamount;

float *manday1;
float *manday2;
float *fertday1;
float *fertday2;
float *resdayno;
float *fertperiod;

// declared observation variables
const float *Fert_N;
const float *Fert_P;
const float *Man_N;
const float *Man_P;
const float *Res_N;
const float *Res_P;
const float *Fert_period;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
bool Good_Dates(const float* date); 

ClassGrow_crops_annually* klone(string name) const;
};

#endif





