// 11/30/19
//---------------------------------------------------------------------------
#ifndef WQ_CRHMH
#define WQ_CRHMH
//---------------------------------------------------------------------------

#include "ClassModule.h"

#define numsubstances 7
#define maxsoillayers 2

using namespace std;

class ClassWQ_Soil : public ClassModule {
public:

ClassWQ_Soil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;
long Sub;
long FaultsAllowed;

// declared variables
long *current_getstep;
float *scf;
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
float *soil_runoff_cWQ;
float **soil_runoff_cWQ_lay;
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
float *tile_flow_conc;
float **tile_flow_conc_lay;
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
const float *atmos_mWQ;
const float **atmos_mWQ_lay;
const float *sr_mix_rate;
const float *parleach;
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
float *conc_soil_rechr;
float **conc_soil_rechr_lay;
float *conc_soil_lower;
float **conc_soil_lower_lay;
float *conc_soil_moist;
float **conc_soil_moist_lay;
float *surfsoil_solub_mWQ;
float **surfsoil_solub_mWQ_lay;

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
void restore_hru(float *from, float *to, const long hh);

float FunctX(const float x);
void Sd_to_soil_mass(float Sdmass_2_soil);
ClassWQ_Soil* klone(string name) const;
};

class ClassWQ_Netroute : public ClassModule {
public:

ClassWQ_Netroute(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;
//long Sub;

// declared variables
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

float *inflow;
float *inflow_mWQ;
float **inflow_mWQ_lay;
float *cuminflow;
float *cuminflow_mWQ;
float **cuminflow_mWQ_lay;
float *outflow;
float *outflow_mWQ;
float **outflow_mWQ_lay;
float *outflow_cWQ;
float **outflow_cWQ_lay;
float *cumoutflow;
float *cumoutflow_mWQ;
float **cumoutflow_mWQ_lay;
float *outflow_diverted;
float *outflow_diverted_conc;
float **outflow_diverted_conc_lay;
float *cumoutflow_diverted;
float *cumoutflow_diverted_mWQ;
float **cumoutflow_diverted_mWQ_lay;

float *gwinflow;
float *gwinflow_mWQ;
float **gwinflow_mWQ_lay;
float *gwcuminflow;
float *gwcuminflow_mWQ;
float **gwcuminflow_mWQ_lay;
float *gwoutflow;
float *gwoutflow_mWQ;
float **gwoutflow_mWQ_lay;
float *gwcumoutflow;
float *gwcumoutflow_mWQ;
float **gwcumoutflow_mWQ_lay;
float *gwoutflow_diverted;
float *gwoutflow_diverted_conc;
float **gwoutflow_diverted_conc_lay;
float *gwcumoutflow_diverted;
float *gwcumoutflow_diverted_mWQ;
float **gwcumoutflow_diverted_mWQ_lay;

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
float *Ktravel;         // [nhru] Muskingum
float *cum_preferential_flow_to_gw;

// local allocated arrays

float *outflow_0;
float *gwoutflow_0;
//float *soil_gw_Buf_0;

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

const float *soil_gw; // N.B. gw_flow in original CRHM
const float *soil_gw_conc;
const float **soil_gw_conc_lay;
const float *soil_ssr;
const float *soil_ssr_conc;
const float **soil_ssr_conc_lay;
const float *soil_runoff;
const float *soil_runoff_cWQ;
const float **soil_runoff_cWQ_lay;

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
float *conc_soil_rechr;
float **conc_soil_rechr_lay;
float *conc_soil_lower;
float **conc_soil_lower_lay;
float *conc_soil_moist;
float **conc_soil_moist_lay;

ClassMuskingum **hruDelay_mWQ; // [numsubstances] handled locally
ClassClark **Clark_hruDelay_mWQ;
ClassClark **ssrDelay_mWQ;
ClassClark **runDelay_mWQ;
ClassClark **gwDelay_mWQ;

ClassMuskingum *hruDelay;
ClassClark *Clark_hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Set_WQ(long hru, float *var, float *var_conc, float amount_conc, float amount);
void Reset_WQ(long hru, float *var, float **var_cWQ_lay);

void Save();
void Restore(const long hh);
void copy_array(float *from, float *to);
void restore_hru(float *from, float *to, const long hh);

virtual float Function1(float *I, long hh);
virtual float Function2(float *X, long hh);

ClassWQ_Netroute* klone(string name) const;
};

class ClassWQ_pbsm : public ClassModule {
public:

ClassWQ_pbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

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
const float *atmos_mWQ;
const float **atmos_mWQ_lay;
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

ClassWQ_Netroute_M_D(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables

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

float *inflow;
float *inflow_mWQ;
float **inflow_mWQ_lay;
float *cuminflow;
float *cuminflow_mWQ;
float **cuminflow_mWQ_lay;
float *outflow;
float *outflow_mWQ;
float **outflow_mWQ_lay;
float *outflow_cWQ;
float **outflow_cWQ_lay;
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
float *cumscaling_boost;    // [nhru]

// local allocated arrays

float *outflow_0;
float *gwoutflow_0;
//float *soil_gw_Buf_0;

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
const long  *soil_rechr_ByPass;

const float *scaling_factor;    // temporary modification

// variable inputs
const float *soil_gw; // N.B. gw_flow in original CRHM
const float *soil_gw_conc;
const float **soil_gw_conc_lay;
const float *soil_ssr;
const float *soil_ssr_conc;
const float **soil_ssr_conc_lay;
const float *soil_runoff;
const float *soil_runoff_cWQ;
const float **soil_runoff_cWQ_lay;

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
float *conc_soil_rechr;
float **conc_soil_rechr_lay;
float *conc_soil_lower;
float **conc_soil_lower_lay;
float *conc_soil_moist;
float **conc_soil_moist_lay;

ClassMuskingum *hruDelay;
ClassClark *Clark_hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

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
void Reset_WQ(long hru, float *var, float **var_conc_lay);

void Save();
void Restore(const long hh);
void copy_array(float *from, float *to);
void restore_hru(float *from, float *to, const long hh);

virtual float Function1(float *I, long hh);
virtual float Function2(float *X, long hh);

ClassWQ_Netroute_M_D* klone(string name) const;
};

class ClassWQ_Test_Hype : public ClassModule {
public:

ClassWQ_Test_Hype(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

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

ClassWQ_pbsmSnobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

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
const float *atmos_mWQ;
const float **atmos_mWQ_lay;
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

ClassWQ_mass_conc(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

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
const float *outflow_cWQ;
const float **outflow_cWQ_lay;
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

ClassWQ_Substitute_Hype(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *conc_soil_rechr;   // concentration of inorganic nitrogen *** from soilstate
float **conc_soil_rechr_lay;
float *conc_soil_lower;   // concentration of organic nitrogen *** from soilstate
float **conc_soil_lower_lay;
float *conc_soil_moist;   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
float **conc_soil_moist_lay;

// declared parameters

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_Substitute_Hype* klone(string name) const;
};

class ClassWQ_Gen_Mass_Var_Soil : public ClassModule {
public:

ClassWQ_Gen_Mass_Var_Soil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

float *soil_moist_change_mWQ;
float **soil_moist_change_mWQ_lay;

float *soil_top_change_mWQ;
float **soil_top_change_mWQ_lay;
float *soil_top_mWQ_last;
float **soil_top_mWQ_lay_last;

float *soil_bottom_change_mWQ;
float **soil_bottom_change_mWQ_lay;
float *soil_bottom_mWQ_last;
float **soil_bottom_mWQ_lay_last;

float *soil_ssr_change_mWQ;
float **soil_ssr_change_mWQ_lay;
float *soil_ssr_mWQ_last;
float **soil_ssr_mWQ_lay_last;

float *Sd_change_mWQ;
float **Sd_change_mWQ_lay;
float *Sd_mWQ_last;
float **Sd_mWQ_lay_last;

float *gw_change_mWQ;
float **gw_change_mWQ_lay;
float *gw_mWQ_last;
float **gw_mWQ_lay_last;

float *soil_gw_change_mWQ;
float **soil_gw_change_mWQ_lay;
float *soil_gw_mWQ_last;
float **soil_gw_mWQ_lay_last;

float *gw_flow_change_mWQ;
float **gw_flow_change_mWQ_lay;
float *gw_flow_mWQ_last;
float **gw_flow_mWQ_lay_last;

float *infil_act_change_mWQ;
float **infil_act_change_mWQ_lay;
float *infil_act_mWQ_last;
float **infil_act_mWQ_lay_last;

float *redirected_residual_change_mWQ;
float **redirected_residual_change_mWQ_lay;
float *redirected_residual_mWQ_last;
float **redirected_residual_mWQ_lay_last;

float *soil_runoff_change_mWQ;
float **soil_runoff_change_mWQ_lay;
float *soil_runoff_mWQ_last;
float **soil_runoff_mWQ_lay_last;

// variable get inputs
const float *soil_rechr;
const float *soil_lower;
const float *soil_moist;
const float *soil_ssr;
const float *Sd;
const float *gw;
const float *soil_gw;
const float *gw_flow;
const float *infil_act;
const float *redirected_residual;
const float *soil_runoff;

const float *conc_soil_rechr;
const float **conc_soil_rechr_lay;
const float *conc_soil_lower;
const float **conc_soil_lower_lay;
const float *soil_ssr_conc;
const float **soil_ssr_conc_lay;
const float *Sd_conc;
const float **Sd_conc_lay;
const float *gw_conc;
const float **gw_conc_lay;
const float *soil_gw_conc;
const float **soil_gw_conc_lay;
const float *gw_flow_conc;
const float **gw_flow_conc_lay;
const float *infil_act_conc;
const float **infil_act_conc_lay;
const float *redirected_residual_conc;
const float **redirected_residual_conc_lay;
const float *soil_runoff_cWQ;
const float **soil_runoff_cWQ_lay;

//declared variables
long *run_ID;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_Gen_Mass_Var_Soil* klone(string name) const;
};

class ClassGrow_crops_annually : public ClassModule {
public:

ClassGrow_crops_annually(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long ObsCnt_N_up;
long ObsCnt_P_up;
long ObsCntMan_N_up;
long ObsCntMan_P_up;
long ObsCntRes_N_up;
long ObsCntRes_P_up;
long ObsCnt_N_down;
long ObsCnt_P_down;
long ObsCntMan_N_down;
long ObsCntMan_P_down;
long ObsCntRes_N_down;
long ObsCntRes_P_down;
long ObsCnt_fertperiod;
long ObsCnt_litterperiod;

// declared variables
float *Fert_N_amount_up;
float *Fert_P_amount_up;
float *Man_N_amount_up;
float *Man_P_amount_up;
float *Fert_N_amount_down;
float *Fert_P_amount_down;
float *Man_N_amount_down;
float *Man_P_amount_down;
float *Res_N_amount_up;
float *Res_P_amount_up;
float *Res_N_amount_down;
float *Res_P_amount_down;
//float *Fertday;
//float *Manday;
//float *Resday_up;
float *Fertperiod;
float *Litterperiod;
long *LockOut;

//long  *SecondDown_fert;
//long  *SecondDown_man;

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
float *fertNamount_up;
float *fertPamount_up;
float *fertNamount_down;
float *fertPamount_down;
float *manNamount_up;
float *manPamount_up;
float *manNamount_down;
float *manPamount_down;
float *resNamount_up;
float *resPamount_up;
float *resNamount_down;
float *resPamount_down;

float *manday_up;
float *manday_down;
float *fertday_up;
float *fertday_down;
float *resday_up;
float *resday_down;
float *fertperiod;
long *litterperiod;

// declared observation variables
const float *Fert_N_up;
const float *Fert_P_up;
const float *Man_N_up;
const float *Man_P_up;
const float *Res_N_up;
const float *Res_P_up;
const float *Fert_N_down;
const float *Fert_P_down;
const float *Man_N_down;
const float *Man_P_down;
const float *Res_N_down;
const float *Res_P_down;
const float *Fert_period;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
bool Good_Dates(const float* date);

ClassGrow_crops_annually* klone(string name) const;
};

class ClassWQ_Gen_Mass_Var_Netroute : public ClassModule {
public:

ClassWQ_Gen_Mass_Var_Netroute(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

float *basinflow_change_mWQ;
float **basinflow_change_mWQ_lay;
float *basinflow_mWQ_last;
float **basinflow_mWQ_lay_last;

float *basingw_change_mWQ;
float **basingw_change_mWQ_lay;
float *basingw_mWQ_last;
float **basingw_mWQ_lay_last;

float *outflow_diverted_change_mWQ;
float **outflow_diverted_change_mWQ_lay;
float *outflow_diverted_mWQ_last;
float **outflow_diverted_mWQ_lay_last;

float *gwoutflow_diverted_change_mWQ;
float **gwoutflow_diverted_change_mWQ_lay;
float *gwoutflow_diverted_mWQ_last;
float **gwoutflow_diverted_mWQ_lay_last;

// variable get inputs
float *basinflow;
float *basingw;
float *outflow_diverted;
float *gwoutflow_diverted;

float *basinflow_conc;
float **basinflow_conc_lay;
float *basingw_conc;
float **basingw_conc_lay;
float *outflow_diverted_conc;
float **outflow_diverted_conc_lay;
float *gwoutflow_diverted_conc;
float **gwoutflow_diverted_conc_lay;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_Gen_Mass_Var_Netroute* klone(string name) const;
};

class Classlapse_rate_Monthly_Mod : public ClassModule {
public:

Classlapse_rate_Monthly_Mod(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float* lapse_rate;
float* lapse_rate_Mthly;

void decl(void);
void init(void);
void run(void);

Classlapse_rate_Monthly_Mod* klone(string name) const;
};

class ClassGlacier_melt_debris_cover_estimate_Mod : public ClassModule {
public:

ClassGlacier_melt_debris_cover_estimate_Mod(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const float* debris_h;
const float* T_threshold;

// declared variables

float* lagT;
float* lagSW;
float* Gmelt_energy;
float* den_air;
float* K_kat;
float* Cp_water;
float* Xmelt;
float* Xmelt_int;
float* Xmelt_acc;
float* Xmelt_V5;

// put variables

float* Gn_ebsm;
float* Gh_ebsm;
float* Ge_ebsm;
float* Gp_ebsm;

// get variables

const float* Albedo;
const float* T_rain;
const float* hru_t;
const float* hru_ea;
const float* net_rain;
const float* Pa;
const float* Qnsn_Var;

// observations

const float* lagT1;
const float* lagT2;
const float* lagT3;
const float* lagT4;
const float* lagSW1;
const float* lagSW2;
const float* lagSW3;
const float* lagSW4;
const float* lagSW5;
const float* lagSW6;

void decl(void);
void init(void);
void run(void);

ClassGlacier_melt_debris_cover_estimate_Mod* klone(string name) const;
};

class ClassSoilPrairie : public ClassModule {
public:

ClassSoilPrairie(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;

// allocated storage
float **current_area; // [NumSloughs] [nhru]
float **current_depth; // [NumSloughs] [nhru]
float **current_volume; // [NumSloughs] [nhru]
float **S_values; // [NumSloughs] [nhru]
float **h_values; // [NumSloughs] [nhru]
float **wetland_drainage; // [NumSloughs] [nhru]


// declared observation variables

// declared variables
float *gw;
float *soil_rechr;
float *soil_moist;
float *soil_gw;
float *gw_flow;
float *soil_ssr;
float *rechr_ssr;
float *soil_runoff;
float *cum_soil_ssr;
float *cum_rechr_ssr;
float *cum_soil_runoff;
float *cum_runoff_to_Sd;
float *cum_redirected_residual;
float *soil_gw_D;
float *soil_ssr_D;
float *gw_flow_D;
float *soil_runoff_D;
float *HK_V;
float *HK_A;
float *HD;
float *redirected_residual;
float *infil_act;
float *cum_infil_act;
float *infil_act_D;
float *Sd_water_frac;
float *contrib_frac;
float *wetlands_evap;
float *total_evap;
float *direct_rain;

float *Pond_water_frac; // Sd[hh]/Sdmax[hh]
float *Pond_evap;
float *Pond_area;
float *Pond_volume;
float *Pond_h;
float *Pond_hmax;
float *Pond_s;
float *Sd;
float *runoff_to_Pond;

float *Small_Ponds_water_frac; // Small_Ponds_Sd[hh]/Small_Ponds_Sdmax[hh]
float *Small_Ponds_evap;
float *Small_Ponds_area;
float *Small_Ponds_Sd;
float *runoff_to_Small_Ponds;
float *Small_Ponds_runoff_to_Pond;

// local variables
float *cum_soil_gw;
float *cum_gw_flow;
float *cum_hru_condense;
float *soil_moist_Init;
float *soil_rechr_Init;
float *Sd_Init;
float *gw_Init;
float *SWE_Init;

float *snowinfil_buf;
float *runoff_buf;
float *meltrunoff_buf;
float *hru_evap_buf;

// declared parameters
const float *Sdmax;
const float *Sdinit;
const float *gw_max;
const float *gw_init;
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
const float *Sd_water_frac_max;
const float *evap_threshold;
const long *soil_withdrawal;
const long **soil_withdrawal_Tables;

const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;
const long *Sd_normal;

const float *Pond_p;
const float *Pond_C1;
const float *Pond_C2;
const float *Pond_C3;
const float *Pond_contrib_frac; // Pond fraction of basin
const float *Pond_area_max;

const float *Small_Ponds_Sdmax;
const float *Small_Ponds_Sdinit;
const float *Small_Ponds_p;
const float *Small_Ponds_C1;
const float *Small_Ponds_C2;
const float *Small_Ponds_C3;
const float *Small_Ponds_contrib_frac; // Small Ponds fraction of basin
const float *Small_Ponds_area_max;



// variable inputs
const float *infil;
const float *snowinfil;
const float *meltrunoff; // frozen melt runoff
const float *runoff;     // liquid runoff
const float *hru_evap;
const float *hru_evap_PT;

// variable put inputs
float *hru_actet;      // [nhru]
float *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoilPrairie* klone(string name) const;

float area_frac(const float area_frac);
void Pond_calc_h_A(const float s, const float p, const float volume, float &h, float &area);
void calc_h_and_S(const float maxvolume, const float maxarea, const float pval, float &S, float &h);
float Pond_area_frac(const float vol_frac, const long hh);
float Small_Ponds_area_frac(const float vol_frac, const long hh);
float Small_Ponds_runoff_frac(const float Sd_Sdmax, const long hh);
};

class ClassGlacier_debris_cover : public ClassModule {
public:

ClassGlacier_debris_cover(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const float* debris_h;
const float* T_threshold;

// declared variables

float* lagT;
float* lagSW;
float* Xmelt;
float* Xmelt_int;
float* Xmelt_acc;

// get variables

const float* Albedo;
const float* hru_t;
const float* Qnsn_Var;

// observations

const float* lagT1;
const float* lagT2;
const float* lagT3;
const float* lagT4;
const float* lagSW1;
const float* lagSW2;
const float* lagSW3;
const float* lagSW4;
const float* lagSW5;
const float* lagSW6;

void decl(void);
void init(void);
void run(void);

ClassGlacier_debris_cover* klone(string name) const;
};

class Class_lapse_rate_Monthly : public ClassModule {
public:

Class_lapse_rate_Monthly(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float* lapse_rate;
float* lapse_rate_Mthly;

void decl(void);
void init(void);
void run(void);

Class_lapse_rate_Monthly* klone(string name) const;
};

#endif





