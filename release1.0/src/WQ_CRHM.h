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
double *scf;
double *Sd;
double *Sd_conc;
double **Sd_conc_lay;
double *gw;
double *gw_conc;
double **gw_conc_lay;
double *solute_deposit;
double *cum_solute_deposit;
double *soil_rechr;
double *soil_rechr_conc;
double **soil_rechr_conc_lay;
double *potential;
double *potential_mWQ;
double **potential_mWQ_lay;
double *direct_excs;
double *direct_excs_mWQ;
double **direct_excs_mWQ_lay;
double *soil_moist;
double *soil_moist_conc;
double **soil_moist_conc_lay;
double *soil_lower_max;
double *soil_lower;
double *soil_lower_conc;
double **soil_lower_conc_lay;
double *soil_gw;
double *soil_gw_conc;
double **soil_gw_conc_lay;
double *gw_flow;
double *gw_flow_conc;
double **gw_flow_conc_lay;
double *soil_ssr;
double *soil_ssr_conc;
double **soil_ssr_conc_lay;
double *rechr_ssr;
double *rechr_ssr_conc;
double **rechr_ssr_conc_lay;
double *soil_runoff;
double *soil_runoff_cWQ;
double **soil_runoff_cWQ_lay;
double *cum_soil_ssr;
double *cum_soil_ssr_mWQ;
double **cum_soil_ssr_mWQ_lay;
double *cum_rechr_ssr;
double *cum_Sd_ssr;
double *cum_Sd_gw;
double *cum_lower_ssr;
double *cum_rechr_ssr_mWQ;
double **cum_rechr_ssr_mWQ_lay;
double *cum_soil_runoff;
double *cum_soil_runoff_mWQ;
double **cum_soil_runoff_mWQ_lay;
double *cum_runoff_to_ssr;
double *cum_runoff_to_Sd;
double *cum_runoff_to_Sd_mWQ;
double **cum_runoff_to_Sd_mWQ_lay;
double *cum_redirected_residual;
double *cum_redirected_residual_mWQ;
double **cum_redirected_residual_mWQ_lay;
double *soil_gw_D;
double *soil_ssr_D;
double *gw_flow_D;
double *soil_runoff_D;
double *HK_V;
double *HK_A;
double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_over_Q;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;
double *redirected_residual;
double *redirected_residual_conc;
double **redirected_residual_conc_lay;
double *infil_act;
double *infil_act_conc;
double **infil_act_conc_lay;
double *cum_infil_act;
double *cum_infil_act_mWQ;
double **cum_infil_act_mWQ_lay;
double *infil_act_D;
double *tile_flow;
double *tile_flow_conc;
double **tile_flow_conc_lay;
double *Dequiv_depth;
double *x;
double *Dw;

// local variables
double *cum_soil_gw;
double *cum_soil_gw_mWQ;
double **cum_soil_gw_mWQ_lay;
double *cum_gw_flow;
double *cum_gw_flow_mWQ;
double **cum_gw_flow_mWQ_lay;
double *cum_hru_condense;
double *cum_Sd_evap;
double *soil_moist_Init;
double **soil_moist_conc_Init_lay;
double *soil_bottom_Init;
double **soil_bottom_conc_Init_lay;
double *soil_rechr_Init;
double **soil_top_conc_Init_lay;
double *Sd_Init;
double *gw_Init;
double *soil_moist_conc_Init;
double *soil_bottom_conc_Init;
double *soil_top_conc_Init;
double *Sd_conc_Init;
double **Sd_conc_Init_lay;
double *gw_conc_Init;
double **gw_conc_Init_lay;

double *snowinfil_buf;
double *runoff_buf;
double *meltrunoff_buf;
double *hru_evap_buf;

// declared parameters

const double *Sdmax;
const double *Sdinit;
const double *Sd_conc_init;
const double **Sd_conc_init_lay;
const double *gw_max;
const double *gw_init;
const double *gw_conc_init;
const double **gw_conc_init_lay;
const double *gw_K;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *soil_rechr_max;
const double *soil_rechr_init;
const double *soil_moist_max;
const double *soil_moist_init;
const double *soil_gw_K;
const double *rechr_ssr_K;
const double *lower_ssr_K;
const double *Sd_ssr_K;
const double *Sd_gw_K;
const double *rain_conc;
const double **rain_conc_lay;
const double *atmos_mWQ;
const double **atmos_mWQ_lay;
const double *sr_mix_rate;
const double *parleach;
const double *channel_slope;
const double *CV_SWE;
const double *side_slope;
const double *culvert_diam;
const double *culvert_water_Dmax;
const double *number_culverts;

const double *Ka;
const double *Kb;
const double *Di;
const double *Dd;
const double *soil_poro_moist;
const double *L;
const double *r;


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
const double *infil;
const double *snowinfil;
const double *meltrunoff; // frozen melt runoff
const double *runoff;     // liquid runoff
const double *hru_evap;
const double *SWE;
const double *SWE_max;
const double *SWE_conc;
const double **SWE_conc_lay;

// variable put inputs
double *conc_soil_rechr;
double **conc_soil_rechr_lay;
double *conc_soil_lower;
double **conc_soil_lower_lay;
double *conc_soil_moist;
double **conc_soil_moist_lay;
double *surfsoil_solub_mWQ;
double **surfsoil_solub_mWQ_lay;

// variable put inputs
double *hru_actet;
double *hru_cum_actet;

// local allocated arrays

double *redirected_residual_0;
double *Sd_0;
double *gw_0;
double *soil_rechr_0;
double *soil_moist_0;
double *soil_lower_0;
double *hru_evap_0;
double *gw_flow_0;
double *hru_actet_0;
double *hru_cum_actet_0;
double *cum_redirected_residual_0;
double *cum_hru_condense_0;
double *cum_Sd_evap_0;
double *cum_Sd_ssr_0;
double *cum_Sd_gw_0;
double *cum_lower_ssr_0;
double *cum_infil_act_0;
double *cum_gw_flow_0;
double *cum_soil_ssr_0;
double *cum_rechr_ssr_0;
double *cum_soil_runoff_0;
double *cum_runoff_to_Sd_0;
double *cum_runoff_to_ssr_0;
double *cum_soil_gw_0;
double *cum_solute_deposit_0;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Add_WQ(const long hru, double *var, double **var_cWQ, double *var2, double **var2_cWQ, double *var3, double **var3_cWQ);
void Set_WQ(const long hru, double *var, double *var_cWQ, double amount, double amount_cWQ);
void Reset_Basin_WQ(const long hru, double *var, double *var_cWQ);
void Reset_WQ(const long hru, double *var, double *var_cWQ);
void Reset_WQ(const long hru, double *var, double **var_cWQ_lay);

void Save();
void Restore(const long hh);
void copy_array(double *from, double *to);
void restore_hru(double *from, double *to, const long hh);

double FunctX(const double x);
void Sd_to_soil_mass(double Sdmass_2_soil);
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
double *ssrinflow;
double *ssrinflow_mWQ;
double **ssrinflow_mWQ_lay;
double *ssrcuminflow;
double *ssrcuminflow_mWQ;
double **ssrcuminflow_mWQ_lay;
double *ssroutflow;
double *ssroutflow_mWQ;
double **ssroutflow_mWQ_lay;
double *ssrcumoutflow;
double *ssrcumoutflow_mWQ;
double **ssrcumoutflow_mWQ_lay;

double *runinflow;
double *runinflow_mWQ;
double **runinflow_mWQ_lay;
double *runcuminflow;
double *runcuminflow_mWQ;
double **runcuminflow_mWQ_lay;
double *runoutflow;
double *runoutflow_mWQ;
double **runoutflow_mWQ_lay;
double *runcumoutflow;
double *runcumoutflow_mWQ;
double **runcumoutflow_mWQ_lay;

double *inflow;
double *inflow_mWQ;
double **inflow_mWQ_lay;
double *cuminflow;
double *cuminflow_mWQ;
double **cuminflow_mWQ_lay;
double *outflow;
double *outflow_mWQ;
double **outflow_mWQ_lay;
double *outflow_cWQ;
double **outflow_cWQ_lay;
double *cumoutflow;
double *cumoutflow_mWQ;
double **cumoutflow_mWQ_lay;
double *outflow_diverted;
double *outflow_diverted_conc;
double **outflow_diverted_conc_lay;
double *cumoutflow_diverted;
double *cumoutflow_diverted_mWQ;
double **cumoutflow_diverted_mWQ_lay;

double *gwinflow;
double *gwinflow_mWQ;
double **gwinflow_mWQ_lay;
double *gwcuminflow;
double *gwcuminflow_mWQ;
double **gwcuminflow_mWQ_lay;
double *gwoutflow;
double *gwoutflow_mWQ;
double **gwoutflow_mWQ_lay;
double *gwcumoutflow;
double *gwcumoutflow_mWQ;
double **gwcumoutflow_mWQ_lay;
double *gwoutflow_diverted;
double *gwoutflow_diverted_conc;
double **gwoutflow_diverted_conc_lay;
double *gwcumoutflow_diverted;
double *gwcumoutflow_diverted_mWQ;
double **gwcumoutflow_diverted_mWQ_lay;

double *basinflow;     // [BASIN] all HRUs
double *basinflow_conc;     // [BASIN] all HRUs
double **basinflow_conc_lay;     // [BASIN] all HRUs
double *basinflow_s;   // [BASIN] all HRUs
double *cumbasinflow;  // [BASIN] all HRUs
double *cumbasinflow_mWQ;  // [BASIN] all HRUs
double **cumbasinflow_mWQ_lay;  // [BASIN] all HRUs
double *basingw;       // [BASIN} all HRUs
double *basingw_conc;       // [BASIN} all HRUs
double **basingw_conc_lay;       // [BASIN} all HRUs
double *basingw_s;     // [BASIN} all HRUs
double *cumbasingw;    // [BASIN} all HRUs
double *cumbasingw_mWQ;    // [BASIN} all HRUs
double **cumbasingw_mWQ_lay;    // [BASIN} all HRUs

double *soil_ssr_Buf;    // buffered
double *soil_ssr_Buf_conc;    // buffered
double **soil_ssr_Buf_conc_lay;    // buffered
double *soil_runoff_Buf; // buffered
double *soil_runoff_Buf_conc; // buffered
double **soil_runoff_Buf_conc_lay; // buffered
double *soil_gw_Buf;     // buffered
double *soil_gw_Buf_conc;     // buffered
double **soil_gw_Buf_conc_lay;     // buffered

double *HRU_cumbasinflow;
double *HRU_cumbasinflow_mWQ;
double **HRU_cumbasinflow_mWQ_lay;
double *cum_to_Sd;
double *cum_to_Sd_mWQ;
double **cum_to_Sd_mWQ_lay;
double *cum_to_soil_rechr;
double *cum_to_soil_rechr_mWQ;
double **cum_to_soil_rechr_mWQ_lay;
double *Ktravel;         // [nhru] Muskingum
double *cum_preferential_flow_to_gw;

// local allocated arrays

double *outflow_0;
double *gwoutflow_0;
//double *soil_gw_Buf_0;

// declared parameters
const double *route_n;         // [nhru]
const double *route_R;         // [nhru]
const double *route_S0;        // [nhru]
const double *route_L;         // [nhru]
const double *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const double *Kstorage;
const double *Lag;
const double *ssrKstorage;
const double *ssrLag;
const double *runKstorage;
const double *runLag;
const double *gwKstorage;
const double *gwLag;

const double *basin_area;        // [BASIN]
const double *hru_area;
const long  *whereto;
const long  *order;
const long  *gwwhereto;
const double *Sdmax;
const double *soil_rechr_max;
const long  *preferential_flow; // [nhru]
const long  *Sd_ByPass;
const long  *soil_rechr_ByPass;

// variable inputs

const double *soil_gw; // N.B. gw_flow in original CRHM
const double *soil_gw_conc;
const double **soil_gw_conc_lay;
const double *soil_ssr;
const double *soil_ssr_conc;
const double **soil_ssr_conc_lay;
const double *soil_runoff;
const double *soil_runoff_cWQ;
const double **soil_runoff_cWQ_lay;

// variable puts
double *Sd;
double *Sd_conc;
double **Sd_conc_lay;
double *soil_moist;
double *soil_moist_conc;
double **soil_moist_conc_lay;
double *soil_lower;
double *soil_lower_conc;
double **soil_lower_conc_lay;
double *soil_rechr;
double *soil_rechr_conc;
double **soil_rechr_conc_lay;
double *redirected_residual;
double *redirected_residual_conc;
double **redirected_residual_conc_lay;
double *cum_redirected_residual;
double *cum_redirected_residual_mWQ;
double **cum_redirected_residual_mWQ_lay;
double *gw;
double *gw_conc;
double **gw_conc_lay;
double *conc_soil_rechr;
double **conc_soil_rechr_lay;
double *conc_soil_lower;
double **conc_soil_lower_lay;
double *conc_soil_moist;
double **conc_soil_moist_lay;

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

void Set_WQ(long hru, double *var, double *var_conc, double amount_conc, double amount);
void Reset_WQ(long hru, double *var, double **var_cWQ_lay);

void Save();
void Restore(const long hh);
void copy_array(double *from, double *to);
void restore_hru(double *from, double *to, const long hh);

virtual double Function1(double *I, long hh);
virtual double Function2(double *X, long hh);

ClassWQ_Netroute* klone(string name) const;
};

class ClassWQ_pbsm : public ClassModule {
public:

ClassWQ_pbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

double hru_u_;

// declared variables

double *SWE_max;
double *SWE;
double *SWE_conc;
double **SWE_conc_lay;
double *Subl;
double *Subl_conc;
double **Subl_conc_lay;
double *Drift_in;
double *Drift_in_conc;
double **Drift_in_conc_lay;
double *Drift_out;       // HRU composite drift
double *Drift_out_conc;  // HRU composite drift
double **Drift_out_conc_lay;  // HRU composite drift
double *cumSubl;
double *cumSubl_mWQ;
double **cumSubl_mWQ_lay;
double *cumDriftOut;
double *cumDriftOut_mWQ;
double **cumDriftOut_mWQ_lay;
double *cumDriftIn;
double *cumDriftIn_mWQ;
double **cumDriftIn_mWQ_lay;
double *cumSno;
double *cumSno_mWQ;
double **cumSno_mWQ_lay;
double *snowdepth;
double *BasinSnowLoss;
double *BasinSnowLoss_mWQ;
double **BasinSnowLoss_mWQ_lay;
double *BasinSnowGain;
double *BasinSnowGain_mWQ;
double **BasinSnowGain_mWQ_lay;
double *cumBasinSnowLoss;
double *cumBasinSnowLoss_mWQ;
double **cumBasinSnowLoss_mWQ_lay;
double *cumBasinSnowGain;
double *cumBasinSnowGain_mWQ;
double **cumBasinSnowGain_mWQ_lay;
double *SublH;
double *DriftH;
double *Prob;
double *SnowAge;
double *SWE_Init;
long  *DrySnow;

// declared parameters
const double *fetch;
const double *Ht;
const double *distrib;
const double *basin_area;
const double *hru_area;
const double *A_S;
const double *u_D;
const double *Drift_offset;
const double *Drift_slope;
const double *Subl_offset;
const double *Subl_slope;
const double *N_S;
const double *rain_conc;
const double **rain_conc_lay;
const double *snow_conc;
const double **snow_conc_lay;
const double *atmos_mWQ;
const double **atmos_mWQ_lay;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const double *hru_t;
const double *hru_rh;
const double *hru_u;
const double *hru_Uadjust;
const double *net_snow;
const long  *hru_newsnow;

// local allocated arrays
double *BasinSnowGain_0;
double *cumBasinSnowGain_0;
double *BasinSnowLoss_0;
double *cumBasinSnowLoss_0;

double *hru_basin;
double *SWE_0;
double *SWE_Init_0;
double *z_s_0;
double *rho_0;

double *Drift_out_0;
double *Drift_in_0;
double *cumDriftIn_0;
double *cumDriftOut_0;
double *cumSubl_0;
double *Subl_0;
double *SublH_0;
double *DriftH_0;
double *cumSno_0;
double *Prob_0;
double *SnowAge_0;
long  *DrySnow_0;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Reset_WQ(long hru, double *var, double **var_WQ_lay);
void Save();
void Restore(const long hh);
void copy_array(long *from, long *to);
void copy_array(double *from, double *to);
void copy_basin(double *from, double *to);
void restore_hru(double *from, double *to, const long hh);
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

double *ssrinflow;
double *ssrinflow_mWQ;
double **ssrinflow_mWQ_lay;
double *ssrcuminflow;
double *ssrcuminflow_mWQ;
double **ssrcuminflow_mWQ_lay;
double *ssroutflow;
double *ssroutflow_mWQ;
double **ssroutflow_mWQ_lay;
double *ssrcumoutflow;
double *ssrcumoutflow_mWQ;
double **ssrcumoutflow_mWQ_lay;

double *runinflow;
double *runinflow_mWQ;
double **runinflow_mWQ_lay;
double *runcuminflow;
double *runcuminflow_mWQ;
double **runcuminflow_mWQ_lay;
double *runoutflow;
double *runoutflow_mWQ;
double **runoutflow_mWQ_lay;
double *runcumoutflow;
double *runcumoutflow_mWQ;
double **runcumoutflow_mWQ_lay;

double *inflow;
double *inflow_mWQ;
double **inflow_mWQ_lay;
double *cuminflow;
double *cuminflow_mWQ;
double **cuminflow_mWQ_lay;
double *outflow;
double *outflow_mWQ;
double **outflow_mWQ_lay;
double *outflow_cWQ;
double **outflow_cWQ_lay;
double *outflow_diverted;
double *outflow_diverted_conc;
double **outflow_diverted_conc_lay;
double *cumoutflow_diverted;
double *cumoutflow_diverted_mWQ;
double **cumoutflow_diverted_mWQ_lay;
double *cumoutflow;
double *cumoutflow_mWQ;
double **cumoutflow_mWQ_lay;

double *gwinflow;
double *gwinflow_mWQ;
double **gwinflow_mWQ_lay;
double *gwoutflow_diverted;
double *gwoutflow_diverted_conc;
double **gwoutflow_diverted_conc_lay;
double *gwcumoutflow_diverted;
double *gwcumoutflow_diverted_mWQ;
double **gwcumoutflow_diverted_mWQ_lay;
double *gwoutflow;
double *gwoutflow_mWQ;
double **gwoutflow_mWQ_lay;
double *gwcuminflow;
double *gwcuminflow_mWQ;
double **gwcuminflow_mWQ_lay;
double *gwcumoutflow;
double *gwcumoutflow_mWQ;
double **gwcumoutflow_mWQ_lay;

double *basinflow;     // [BASIN] all HRUs
double *basinflow_conc;     // [BASIN] all HRUs
double **basinflow_conc_lay;     // [BASIN] all HRUs
double *basinflow_s;   // [BASIN] all HRUs
double *cumbasinflow;  // [BASIN] all HRUs
double *cumbasinflow_mWQ;  // [BASIN] all HRUs
double **cumbasinflow_mWQ_lay;  // [BASIN] all HRUs
double *basingw;       // [BASIN} all HRUs
double *basingw_conc;       // [BASIN} all HRUs
double **basingw_conc_lay;       // [BASIN} all HRUs
double *basingw_s;     // [BASIN} all HRUs
double *cumbasingw;    // [BASIN} all HRUs
double *cumbasingw_mWQ;    // [BASIN} all HRUs
double **cumbasingw_mWQ_lay;    // [BASIN} all HRUs

double *soil_ssr_Buf;    // buffered
double *soil_ssr_Buf_conc;    // buffered
double **soil_ssr_Buf_conc_lay;    // buffered
double *soil_runoff_Buf; // buffered
double *soil_runoff_Buf_conc; // buffered
double **soil_runoff_Buf_conc_lay; // buffered
double *soil_gw_Buf;     // buffered
double *soil_gw_Buf_conc;     // buffered
double **soil_gw_Buf_conc_lay;     // buffered

double *HRU_cumbasinflow;
double *HRU_cumbasinflow_mWQ;
double **HRU_cumbasinflow_mWQ_lay;
double *cum_to_Sd;
double *cum_to_Sd_mWQ;
double **cum_to_Sd_mWQ_lay;
double *cum_to_soil_rechr;
double *cum_to_soil_rechr_mWQ;
double **cum_to_soil_rechr_mWQ_lay;
double *Used;    // [BASIN}
double *Used_mWQ;    // [BASIN}
double **Used_mWQ_lay;    // [BASIN}

double *distrib_sum;
double *Ktravel;         // [nhru] Muskingum
double *cum_preferential_flow_to_gw;
double *cumscaling_boost;    // [nhru]

// local allocated arrays

double *outflow_0;
double *gwoutflow_0;
//double *soil_gw_Buf_0;

// declared parameters
const double *route_n;         // [nhru]
const double *route_R;         // [nhru]
const double *route_S0;        // [nhru]
const double *route_L;         // [nhru]
const double *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const double *Kstorage;
const double *Lag;             // [nhru]
const double *ssrKstorage;     // [nhru]
const double *ssrLag;          // [nhru]
const double *runKstorage;     // [nhru]
const double *runLag;          // [nhru]
const double *gwKstorage;
const double *gwLag;
const long  *gwwhereto;       // [nhru]

const double *basin_area;      // [BASIN]
const double *hru_area;        // [nhru]
const double *distrib;
const double *distrib_Basin;
const double **distrib_hru;
const double *Sdmax;           // [nhru]
const double *soil_rechr_max;  // [nhru]
const long  *order;
const long  *preferential_flow; // [nhru]
const long  *Sd_ByPass;       // [nhru]
const long  *soil_rechr_ByPass;

const double *scaling_factor;    // temporary modification

// variable inputs
const double *soil_gw; // N.B. gw_flow in original CRHM
const double *soil_gw_conc;
const double **soil_gw_conc_lay;
const double *soil_ssr;
const double *soil_ssr_conc;
const double **soil_ssr_conc_lay;
const double *soil_runoff;
const double *soil_runoff_cWQ;
const double **soil_runoff_cWQ_lay;

// variable puts
double *Sd;
double *Sd_conc;
double **Sd_conc_lay;
double *soil_moist;
double *soil_moist_conc;
double **soil_moist_conc_lay;
double *soil_lower;
double *soil_lower_conc;
double **soil_lower_conc_lay;
double *soil_rechr;
double *soil_rechr_conc;
double **soil_rechr_conc_lay;
double *redirected_residual;
double *redirected_residual_conc;
double **redirected_residual_conc_lay;
double *cum_redirected_residual;
double *cum_redirected_residual_mWQ;
double **cum_redirected_residual_mWQ_lay;
double *gw;
double *gw_conc;
double **gw_conc_lay;
double *conc_soil_rechr;
double **conc_soil_rechr_lay;
double *conc_soil_lower;
double **conc_soil_lower_lay;
double *conc_soil_moist;
double **conc_soil_moist_lay;

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

void Set_WQ(long hru, double *var, double *var_conc, double amount_conc, double amount);
void Reset_WQ(long hru, double *var, double **var_conc_lay);

void Save();
void Restore(const long hh);
void copy_array(double *from, double *to);
void restore_hru(double *from, double *to, const long hh);

virtual double Function1(double *I, long hh);
virtual double Function2(double *X, long hh);

ClassWQ_Netroute_M_D* klone(string name) const;
};

class ClassWQ_Test_Hype : public ClassModule {
public:

ClassWQ_Test_Hype(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *infil;
double *snowinfil;
double *runoff;
double *meltrunoff;
double *hru_evap;
double *hru_cum_evap;
double *hru_cum_actet;
double *hru_actet;
double *net_rain;
double *SWE;
double *SWE_max;
double *hru_t;
double *SWE_conc;
double **SWE_conc_lay;

double *soil_moist;
double *soil_rechr;

// declared parameters
const double* infil_0;
const double* snowinfil_0;
const double* runoff_0;
const double* meltrunoff_0;
const double* hru_evap_0;
const double* hru_actet_0;
const double* hru_cum_evap_0;
const double* hru_cum_actet_0;
const double* net_rain_0;
const double* SWE_0;
const double* hru_t_0;
const double* SWE_conc_0;
const double** SWE_conc_lay_0;

const double* soil_rechr_0;
const double* soil_moist_0;
const double* soil_rechr_max;
const double* soil_moist_max;

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

double hru_u_;

// declared variables

double *SWE_max;
double *SWE_conc;
double **SWE_conc_lay;
double *Subl;
double *Subl_conc;
double **Subl_conc_lay;
double *Drift;
double *Drift_in;
double *Drift_in_conc;
double **Drift_in_conc_lay;
double *Drift_out;       // HRU composite drift
double *Drift_out_conc;  // HRU composite drift
double **Drift_out_conc_lay;  // HRU composite drift
double *cumSubl;
double *cumSubl_mWQ;
double **cumSubl_mWQ_lay;
double *cumDriftOut;
double *cumDriftOut_mWQ;
double **cumDriftOut_mWQ_lay;
double *cumDrift;
double *cumDriftIn;
double *cumDriftIn_mWQ;
double **cumDriftIn_mWQ_lay;
double *cumSno;
double *cumSno_mWQ;
double **cumSno_mWQ_lay;
double *snowdepth;
double *BasinSnowLoss;
double *BasinSnowLoss_mWQ;
double **BasinSnowLoss_mWQ_lay;
double *BasinSnowGain;
double *BasinSnowGain_mWQ;
double **BasinSnowGain_mWQ_lay;
double *cumBasinSnowLoss;
double *cumBasinSnowLoss_mWQ;
double **cumBasinSnowLoss_mWQ_lay;
double *cumBasinSnowGain;
double *cumBasinSnowGain_mWQ;
double **cumBasinSnowGain_mWQ_lay;
double *SublH;
double *DriftH;
double *Prob;
double *SnowAge;
double *SWE_Init;
long  *DrySnow;

// declared parameters
const double *fetch;
const double *Ht;
const double *distrib;
const double *basin_area;
const double *hru_area;
const double *A_S;
const double *u_D;
const double *Drift_offset;
const double *Drift_slope;
const double *Subl_offset;
const double *Subl_slope;
const double *N_S;
const double *rain_conc;
const double **rain_conc_lay;
const double *snow_conc;
const double **snow_conc_lay;
const double *atmos_mWQ;
const double **atmos_mWQ_lay;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// put variable inputs
double *SWE; // actually m_s

// variable inputs
const double *z_s;
const double *rho;
const double *hru_t;
const double *hru_u;
const double *hru_Uadjust;
const double *net_snow;
const long  *hru_newsnow;
const double *hru_ea;

// local allocated arrays

double *BasinSnowGain_0;
double *cumBasinSnowGain_0;
double *BasinSnowLoss_0;
double *cumBasinSnowLoss_0;

double *hru_basin;
double *SWE_0;
double *SWE_Init_0;
double *z_s_0;
double *rho_0;

double *Drift_out_0;
double *Drift_in_0;
double *cumDriftIn_0;
double *cumDriftOut_0;
double *cumSubl_0;
double *Subl_0;
double *cumSno_0;
double *SnowAge_0;
long *DrySnow_0;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

void Reset_WQ(long hru, double *var, double **var_WQ_lay);
void Save();
void Restore(const long hh);
void copy_array(double *from, double *to);
void copy_array(long *from, long *to);
void copy_basin(double *from, double *to);
void restore_hru(double *from, double *to, const long hh);
void restore_hru(long *from, long *to, const long hh);

ClassWQ_pbsmSnobal* klone(string name) const;
};

class ClassWQ_mass_conc : public ClassModule {
public:

ClassWQ_mass_conc(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *inflow_conc;
double **inflow_conc_lay;
double *outflow_conc;
double **outflow_conc_lay;
double *runoutflow_conc;
double **runoutflow_conc_lay;
double *ssroutflow_conc;
double **ssroutflow_conc_lay;
double *gwoutflow_conc;
double **gwoutflow_conc_lay;

// declared parameters

// variable inputs
const double *inflow;
const double *inflow_mWQ;
const double **inflow_mWQ_lay;
const double *outflow;
const double *outflow_mWQ;
const double **outflow_mWQ_lay;
const double *outflow_cWQ;
const double **outflow_cWQ_lay;
const double *runoutflow;
const double *runoutflow_mWQ;
const double **runoutflow_mWQ_lay;
const double *ssroutflow;
const double *ssroutflow_mWQ;
const double **ssroutflow_mWQ_lay;
const double *gwoutflow;
const double *gwoutflow_mWQ;
const double **gwoutflow_mWQ_lay;

void decl(void);
void init(void);
void run(void);

void Reset_WQ(double **var_lay);
void mass_to_conc(const double *var, const double **var_mWQ, double **var_conc);

ClassWQ_mass_conc* klone(string name) const;
};

class ClassWQ_Substitute_Hype : public ClassModule {
public:

ClassWQ_Substitute_Hype(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *conc_soil_rechr;   // concentration of inorganic nitrogen *** from soilstate
double **conc_soil_rechr_lay;
double *conc_soil_lower;   // concentration of organic nitrogen *** from soilstate
double **conc_soil_lower_lay;
double *conc_soil_moist;   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
double **conc_soil_moist_lay;

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

double *soil_moist_change_mWQ;
double **soil_moist_change_mWQ_lay;

double *soil_top_change_mWQ;
double **soil_top_change_mWQ_lay;
double *soil_top_mWQ_last;
double **soil_top_mWQ_lay_last;

double *soil_bottom_change_mWQ;
double **soil_bottom_change_mWQ_lay;
double *soil_bottom_mWQ_last;
double **soil_bottom_mWQ_lay_last;

double *soil_ssr_change_mWQ;
double **soil_ssr_change_mWQ_lay;
double *soil_ssr_mWQ_last;
double **soil_ssr_mWQ_lay_last;

double *Sd_change_mWQ;
double **Sd_change_mWQ_lay;
double *Sd_mWQ_last;
double **Sd_mWQ_lay_last;

double *gw_change_mWQ;
double **gw_change_mWQ_lay;
double *gw_mWQ_last;
double **gw_mWQ_lay_last;

double *soil_gw_change_mWQ;
double **soil_gw_change_mWQ_lay;
double *soil_gw_mWQ_last;
double **soil_gw_mWQ_lay_last;

double *gw_flow_change_mWQ;
double **gw_flow_change_mWQ_lay;
double *gw_flow_mWQ_last;
double **gw_flow_mWQ_lay_last;

double *infil_act_change_mWQ;
double **infil_act_change_mWQ_lay;
double *infil_act_mWQ_last;
double **infil_act_mWQ_lay_last;

double *redirected_residual_change_mWQ;
double **redirected_residual_change_mWQ_lay;
double *redirected_residual_mWQ_last;
double **redirected_residual_mWQ_lay_last;

double *soil_runoff_change_mWQ;
double **soil_runoff_change_mWQ_lay;
double *soil_runoff_mWQ_last;
double **soil_runoff_mWQ_lay_last;

// variable get inputs
const double *soil_rechr;
const double *soil_lower;
const double *soil_moist;
const double *soil_ssr;
const double *Sd;
const double *gw;
const double *soil_gw;
const double *gw_flow;
const double *infil_act;
const double *redirected_residual;
const double *soil_runoff;

const double *conc_soil_rechr;
const double **conc_soil_rechr_lay;
const double *conc_soil_lower;
const double **conc_soil_lower_lay;
const double *soil_ssr_conc;
const double **soil_ssr_conc_lay;
const double *Sd_conc;
const double **Sd_conc_lay;
const double *gw_conc;
const double **gw_conc_lay;
const double *soil_gw_conc;
const double **soil_gw_conc_lay;
const double *gw_flow_conc;
const double **gw_flow_conc_lay;
const double *infil_act_conc;
const double **infil_act_conc_lay;
const double *redirected_residual_conc;
const double **redirected_residual_conc_lay;
const double *soil_runoff_cWQ;
const double **soil_runoff_cWQ_lay;

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
double *Fert_N_amount_up;
double *Fert_P_amount_up;
double *Man_N_amount_up;
double *Man_P_amount_up;
double *Fert_N_amount_down;
double *Fert_P_amount_down;
double *Man_N_amount_down;
double *Man_P_amount_down;
double *Res_N_amount_up;
double *Res_P_amount_up;
double *Res_N_amount_down;
double *Res_P_amount_down;
//double *Fertday;
//double *Manday;
//double *Resday_up;
double *Fertperiod;
double *Litterperiod;
long *LockOut;

//long  *SecondDown_fert;
//long  *SecondDown_man;

// declared parameters
const long  *Ag_YearStart;

// put parameters
const double *Htmax;
const double *Init_Crop_Ht_1;
const double *Crop_Grow_Rate_1;
const double *JCrop_Start_1;
const double *JCrop_Harvest_1;
const double *Crop_Htmax_1;
const double *Init_Crop_Ht_2;
const double *Crop_Grow_Rate_2;
const double *JCrop_Start_2;
const double *JCrop_Harvest_2;
const double *Crop_Htmax_2;

double *Ht;
double *fertNamount_up;
double *fertPamount_up;
double *fertNamount_down;
double *fertPamount_down;
double *manNamount_up;
double *manPamount_up;
double *manNamount_down;
double *manPamount_down;
double *resNamount_up;
double *resPamount_up;
double *resNamount_down;
double *resPamount_down;

double *manday_up;
double *manday_down;
double *fertday_up;
double *fertday_down;
double *resday_up;
double *resday_down;
double *fertperiod;
long *litterperiod;

// declared observation variables
const double *Fert_N_up;
const double *Fert_P_up;
const double *Man_N_up;
const double *Man_P_up;
const double *Res_N_up;
const double *Res_P_up;
const double *Fert_N_down;
const double *Fert_P_down;
const double *Man_N_down;
const double *Man_P_down;
const double *Res_N_down;
const double *Res_P_down;
const double *Fert_period;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
bool Good_Dates(const double* date);

ClassGrow_crops_annually* klone(string name) const;
};

class ClassWQ_Gen_Mass_Var_Netroute : public ClassModule {
public:

ClassWQ_Gen_Mass_Var_Netroute(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

double *basinflow_change_mWQ;
double **basinflow_change_mWQ_lay;
double *basinflow_mWQ_last;
double **basinflow_mWQ_lay_last;

double *basingw_change_mWQ;
double **basingw_change_mWQ_lay;
double *basingw_mWQ_last;
double **basingw_mWQ_lay_last;

double *outflow_diverted_change_mWQ;
double **outflow_diverted_change_mWQ_lay;
double *outflow_diverted_mWQ_last;
double **outflow_diverted_mWQ_lay_last;

double *gwoutflow_diverted_change_mWQ;
double **gwoutflow_diverted_change_mWQ_lay;
double *gwoutflow_diverted_mWQ_last;
double **gwoutflow_diverted_mWQ_lay_last;

// variable get inputs
double *basinflow;
double *basingw;
double *outflow_diverted;
double *gwoutflow_diverted;

double *basinflow_conc;
double **basinflow_conc_lay;
double *basingw_conc;
double **basingw_conc_lay;
double *outflow_diverted_conc;
double **outflow_diverted_conc_lay;
double *gwoutflow_diverted_conc;
double **gwoutflow_diverted_conc_lay;

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
double* lapse_rate;
double* lapse_rate_Mthly;

void decl(void);
void init(void);
void run(void);

Classlapse_rate_Monthly_Mod* klone(string name) const;
};

class ClassGlacier_melt_debris_cover_estimate_Mod : public ClassModule {
public:

ClassGlacier_melt_debris_cover_estimate_Mod(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const double* debris_h;
const double* T_threshold;

// declared variables

double* lagT;
double* lagSW;
double* Gmelt_energy;
double* den_air;
double* K_kat;
double* Cp_water;
double* Xmelt;
double* Xmelt_int;
double* Xmelt_acc;
double* Xmelt_V5;

// put variables

double* Gn_ebsm;
double* Gh_ebsm;
double* Ge_ebsm;
double* Gp_ebsm;

// get variables

const double* Albedo;
const double* T_rain;
const double* hru_t;
const double* hru_ea;
const double* net_rain;
const double* Pa;
const double* Qnsn_Var;

// observations

const double* lagT1;
const double* lagT2;
const double* lagT3;
const double* lagT4;
const double* lagSW1;
const double* lagSW2;
const double* lagSW3;
const double* lagSW4;
const double* lagSW5;
const double* lagSW6;

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
double **current_area; // [NumSloughs] [nhru]
double **current_depth; // [NumSloughs] [nhru]
double **current_volume; // [NumSloughs] [nhru]
double **S_values; // [NumSloughs] [nhru]
double **h_values; // [NumSloughs] [nhru]
double **wetland_drainage; // [NumSloughs] [nhru]


// declared observation variables

// declared variables
double *gw;
double *soil_rechr;
double *soil_moist;
double *soil_gw;
double *gw_flow;
double *soil_ssr;
double *rechr_ssr;
double *soil_runoff;
double *cum_soil_ssr;
double *cum_rechr_ssr;
double *cum_soil_runoff;
double *cum_runoff_to_Sd;
double *cum_redirected_residual;
double *soil_gw_D;
double *soil_ssr_D;
double *gw_flow_D;
double *soil_runoff_D;
double *HK_V;
double *HK_A;
double *HD;
double *redirected_residual;
double *infil_act;
double *cum_infil_act;
double *infil_act_D;
double *Sd_water_frac;
double *contrib_frac;
double *wetlands_evap;
double *total_evap;
double *direct_rain;

double *Pond_water_frac; // Sd[hh]/Sdmax[hh]
double *Pond_evap;
double *Pond_area;
double *Pond_volume;
double *Pond_h;
double *Pond_hmax;
double *Pond_s;
double *Sd;
double *runoff_to_Pond;

double *Small_Ponds_water_frac; // Small_Ponds_Sd[hh]/Small_Ponds_Sdmax[hh]
double *Small_Ponds_evap;
double *Small_Ponds_area;
double *Small_Ponds_Sd;
double *runoff_to_Small_Ponds;
double *Small_Ponds_runoff_to_Pond;

// local variables
double *cum_soil_gw;
double *cum_gw_flow;
double *cum_hru_condense;
double *soil_moist_Init;
double *soil_rechr_Init;
double *Sd_Init;
double *gw_Init;
double *SWE_Init;

double *snowinfil_buf;
double *runoff_buf;
double *meltrunoff_buf;
double *hru_evap_buf;

// declared parameters
const double *Sdmax;
const double *Sdinit;
const double *gw_max;
const double *gw_init;
const double *gw_K;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *soil_rechr_max;
const double *soil_rechr_init;
const double *soil_moist_max;
const double *soil_moist_init;
const double *soil_gw_K;
const double *rechr_ssr_K;
const double *lower_ssr_K;
const double *Sd_ssr_K;
const double *Sd_gw_K;
const double *Sd_water_frac_max;
const double *evap_threshold;
const long *soil_withdrawal;
const long **soil_withdrawal_Tables;

const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;
const long *Sd_normal;

const double *Pond_p;
const double *Pond_C1;
const double *Pond_C2;
const double *Pond_C3;
const double *Pond_contrib_frac; // Pond fraction of basin
const double *Pond_area_max;

const double *Small_Ponds_Sdmax;
const double *Small_Ponds_Sdinit;
const double *Small_Ponds_p;
const double *Small_Ponds_C1;
const double *Small_Ponds_C2;
const double *Small_Ponds_C3;
const double *Small_Ponds_contrib_frac; // Small Ponds fraction of basin
const double *Small_Ponds_area_max;



// variable inputs
const double *infil;
const double *snowinfil;
const double *meltrunoff; // frozen melt runoff
const double *runoff;     // liquid runoff
const double *hru_evap;
const double *hru_evap_PT;

// variable put inputs
double *hru_actet;      // [nhru]
double *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoilPrairie* klone(string name) const;

double area_frac(const double area_frac);
void Pond_calc_h_A(const double s, const double p, const double volume, double &h, double &area);
void calc_h_and_S(const double maxvolume, const double maxarea, const double pval, double &S, double &h);
double Pond_area_frac(const double vol_frac, const long hh);
double Small_Ponds_area_frac(const double vol_frac, const long hh);
double Small_Ponds_runoff_frac(const double Sd_Sdmax, const long hh);
};

class ClassGlacier_debris_cover : public ClassModule {
public:

ClassGlacier_debris_cover(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const double* debris_h;
const double* T_threshold;

// declared variables

double* lagT;
double* lagSW;
double* Xmelt;
double* Xmelt_int;
double* Xmelt_acc;

// get variables

const double* Albedo;
const double* hru_t;
const double* Qnsn_Var;

// observations

const double* lagT1;
const double* lagT2;
const double* lagT3;
const double* lagT4;
const double* lagSW1;
const double* lagSW2;
const double* lagSW3;
const double* lagSW4;
const double* lagSW5;
const double* lagSW6;

void decl(void);
void init(void);
void run(void);

ClassGlacier_debris_cover* klone(string name) const;
};

class Class_lapse_rate_Monthly : public ClassModule {
public:

Class_lapse_rate_Monthly(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double* lapse_rate;
double* lapse_rate_Mthly;

void decl(void);
void init(void);
void run(void);

Class_lapse_rate_Monthly* klone(string name) const;
};

#endif





