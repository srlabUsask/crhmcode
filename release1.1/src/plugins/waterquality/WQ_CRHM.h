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

long snowinfilDiv{0};
long meltrunoffDiv{0};
long runoffDiv{0};
long evapDiv{0};
long Sub{0};
long FaultsAllowed{0};

// declared variables
long* current_getstep{NULL};
double *scf{ NULL };
double *Sd{ NULL };
double *Sd_conc{ NULL };
double **Sd_conc_lay{ NULL };
double *gw{ NULL };
double *gw_conc{ NULL };
double **gw_conc_lay{ NULL };
double *solute_deposit{ NULL };
double *cum_solute_deposit{ NULL };
double *soil_rechr{ NULL };
double *soil_rechr_conc{ NULL };
double **soil_rechr_conc_lay{ NULL };
double *potential{ NULL };
double *potential_mWQ{ NULL };
double **potential_mWQ_lay{ NULL };
double *direct_excs{ NULL };
double *direct_excs_mWQ{ NULL };
double **direct_excs_mWQ_lay{ NULL };
double *soil_moist{ NULL };
double *soil_moist_conc{ NULL };
double **soil_moist_conc_lay{ NULL };
double *soil_lower_max{ NULL };
double *soil_lower{ NULL };
double *soil_lower_conc{ NULL };
double **soil_lower_conc_lay{ NULL };
double *soil_gw{ NULL };
double *soil_gw_conc{ NULL };
double **soil_gw_conc_lay{ NULL };
double *gw_flow{ NULL };
double *gw_flow_conc{ NULL };
double **gw_flow_conc_lay{ NULL };
double *soil_ssr{ NULL };
double *soil_ssr_conc{ NULL };
double **soil_ssr_conc_lay{ NULL };
double *rechr_ssr{ NULL };
double *rechr_ssr_conc{ NULL };
double **rechr_ssr_conc_lay{ NULL };
double *soil_runoff{ NULL };
double *soil_runoff_cWQ{ NULL };
double **soil_runoff_cWQ_lay{ NULL };
double *cum_soil_ssr{ NULL };
double *cum_soil_ssr_mWQ{ NULL };
double **cum_soil_ssr_mWQ_lay{ NULL };
double *cum_rechr_ssr{ NULL };
double *cum_Sd_ssr{ NULL };
double *cum_Sd_gw{ NULL };
double *cum_lower_ssr{ NULL };
double *cum_rechr_ssr_mWQ{ NULL };
double **cum_rechr_ssr_mWQ_lay{ NULL };
double *cum_soil_runoff{ NULL };
double *cum_soil_runoff_mWQ{ NULL };
double **cum_soil_runoff_mWQ_lay{ NULL };
double *cum_runoff_to_ssr{ NULL };
double *cum_runoff_to_Sd{ NULL };
double *cum_runoff_to_Sd_mWQ{ NULL };
double **cum_runoff_to_Sd_mWQ_lay{ NULL };
double *cum_redirected_residual{ NULL };
double *cum_redirected_residual_mWQ{ NULL };
double **cum_redirected_residual_mWQ_lay{ NULL };
double *soil_gw_D{ NULL };
double *soil_ssr_D{ NULL };
double *gw_flow_D{ NULL };
double *soil_runoff_D{ NULL };
double *HK_V{ NULL };
double *HK_A{ NULL };
double *culvert_Q{ NULL };
double *culvert_water_H{ NULL };
double *culvert_water_A{ NULL };
double *culvert_water_V{ NULL };
double *culvert_over_Q{ NULL };
double *culvert_evap{ NULL };
double *cum_culvert{ NULL };
double *cum_culvert_over{ NULL };
double *HD{ NULL };
double *redirected_residual{ NULL };
double *redirected_residual_conc{ NULL };
double **redirected_residual_conc_lay{ NULL };
double *infil_act{ NULL };
double *infil_act_conc{ NULL };
double **infil_act_conc_lay{ NULL };
double *cum_infil_act{ NULL };
double *cum_infil_act_mWQ{ NULL };
double **cum_infil_act_mWQ_lay{ NULL };
double *infil_act_D{ NULL };
double *tile_flow{ NULL };
double *tile_flow_conc{ NULL };
double **tile_flow_conc_lay{ NULL };
double *Dequiv_depth{ NULL };
double *x{ NULL };
double *Dw{ NULL };

// local variables
double *cum_soil_gw{ NULL };
double *cum_soil_gw_mWQ{ NULL };
double **cum_soil_gw_mWQ_lay{ NULL };
double *cum_gw_flow{ NULL };
double *cum_gw_flow_mWQ{ NULL };
double **cum_gw_flow_mWQ_lay{ NULL };
double *cum_hru_condense{ NULL };
double *cum_Sd_evap{ NULL };
double *soil_moist_Init{ NULL };
double **soil_moist_conc_Init_lay{ NULL };
double *soil_bottom_Init{ NULL };
double **soil_bottom_conc_Init_lay{ NULL };
double *soil_rechr_Init{ NULL };
double **soil_top_conc_Init_lay{ NULL };
double *Sd_Init{ NULL };
double *gw_Init{ NULL };
double *soil_moist_conc_Init{ NULL };
double *soil_bottom_conc_Init{ NULL };
double *soil_top_conc_Init{ NULL };
double *Sd_conc_Init{ NULL };
double **Sd_conc_Init_lay{ NULL };
double *gw_conc_Init{ NULL };
double **gw_conc_Init_lay{ NULL };

double *snowinfil_buf{ NULL };
double *runoff_buf{ NULL };
double *meltrunoff_buf{ NULL };
double *hru_evap_buf{ NULL };

// declared parameters

const double *Sdmax{ NULL };
const double *Sdinit{ NULL };
const double *Sd_conc_init{ NULL };
const double **Sd_conc_init_lay{ NULL };
const double *gw_max{ NULL };
const double *gw_init{ NULL };
const double *gw_conc_init{ NULL };
const double **gw_conc_init_lay{ NULL };
const double *gw_K{ NULL };
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *soil_rechr_max{ NULL };
const double *soil_rechr_init{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_moist_init{ NULL };
const double *soil_gw_K{ NULL };
const double *rechr_ssr_K{ NULL };
const double *lower_ssr_K{ NULL };
const double *Sd_ssr_K{ NULL };
const double *Sd_gw_K{ NULL };
const double *rain_conc{ NULL };
const double **rain_conc_lay{ NULL };
const double *atmos_mWQ{ NULL };
const double **atmos_mWQ_lay{ NULL };
const double *sr_mix_rate{ NULL };
const double *parleach{ NULL };
const double *channel_slope{ NULL };
const double *CV_SWE{ NULL };
const double *side_slope{ NULL };
const double *culvert_diam{ NULL };
const double *culvert_water_Dmax{ NULL };
const double *number_culverts{ NULL };

const double *Ka{ NULL };
const double *Kb{ NULL };
const double *Di{ NULL };
const double *Dd{ NULL };
const double *soil_poro_moist{ NULL };
const double *L{ NULL };
const double *r{ NULL };


const long *soil_withdrawal{ NULL };
const long **soil_withdrawal_Tables{ NULL };
const long *culvert_type{ NULL };
const long *cov_type{ NULL };
const long *transp_limited{ NULL };
const long *soil_ssr_runoff{ NULL };
const long *inhibit_evap{ NULL };
const long *calcN{ NULL }; // Status of nitrogen simulation
const long *calcP{ NULL }; // Status of phosphorus simulation
const long *calcC{ NULL }; // Status of organic carbon simulation


// variable inputs
const double *infil{ NULL };
const double *snowinfil{ NULL };
const double *meltrunoff{ NULL }; // frozen melt runoff
const double *runoff{ NULL };     // liquid runoff
const double *hru_evap{ NULL };
const double *SWE{ NULL };
const double *SWE_max{ NULL };
const double *SWE_conc{ NULL };
const double **SWE_conc_lay{ NULL };

// variable put inputs
double *conc_soil_rechr{ NULL };
double **conc_soil_rechr_lay{ NULL };
double *conc_soil_lower{ NULL };
double **conc_soil_lower_lay{ NULL };
double *conc_soil_moist{ NULL };
double **conc_soil_moist_lay{ NULL };
double *surfsoil_solub_mWQ{ NULL };
double **surfsoil_solub_mWQ_lay{ NULL };

// variable put inputs
double *hru_actet{ NULL };
double *hru_cum_actet{ NULL };

// local allocated arrays

double *redirected_residual_0{ NULL };
double *Sd_0{ NULL };
double *gw_0{NULL};
double *soil_rechr_0{ NULL };
double *soil_moist_0{ NULL };
double *soil_lower_0{ NULL };
double *hru_evap_0{ NULL };
double *gw_flow_0{ NULL };
double *hru_actet_0{ NULL };
double *hru_cum_actet_0{ NULL };
double *cum_redirected_residual_0{ NULL };
double *cum_hru_condense_0{ NULL };
double *cum_Sd_evap_0{ NULL };
double *cum_Sd_ssr_0{ NULL };
double *cum_Sd_gw_0{ NULL };
double *cum_lower_ssr_0{ NULL };
double *cum_infil_act_0{ NULL };
double *cum_gw_flow_0{ NULL };
double *cum_soil_ssr_0{ NULL };
double *cum_rechr_ssr_0{ NULL };
double *cum_soil_runoff_0{ NULL };
double *cum_runoff_to_Sd_0{ NULL };
double *cum_runoff_to_ssr_0{ NULL };
double *cum_soil_gw_0{ NULL };
double *cum_solute_deposit_0{ NULL };

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

long meltrunoffDiv{0};
long soil_ssrDiv{0};
long soil_runoffDiv{0};
long soil_gwDiv{0};
//long Sub;

// declared variables
double *ssrinflow{ NULL };
double *ssrinflow_mWQ{ NULL };
double **ssrinflow_mWQ_lay{ NULL };
double *ssrcuminflow{ NULL };
double *ssrcuminflow_mWQ{ NULL };
double **ssrcuminflow_mWQ_lay{ NULL };
double *ssroutflow{ NULL };
double *ssroutflow_mWQ{ NULL };
double **ssroutflow_mWQ_lay{ NULL };
double *ssrcumoutflow{ NULL };
double *ssrcumoutflow_mWQ{ NULL };
double **ssrcumoutflow_mWQ_lay{ NULL };

double *runinflow{ NULL };
double *runinflow_mWQ{ NULL };
double **runinflow_mWQ_lay{ NULL };
double *runcuminflow{ NULL };
double *runcuminflow_mWQ{ NULL };
double **runcuminflow_mWQ_lay{ NULL };
double *runoutflow{ NULL };
double *runoutflow_mWQ{ NULL };
double **runoutflow_mWQ_lay{ NULL };
double *runcumoutflow{ NULL };
double *runcumoutflow_mWQ{ NULL };
double **runcumoutflow_mWQ_lay{ NULL };

double *inflow{ NULL };
double *inflow_mWQ{ NULL };
double **inflow_mWQ_lay{ NULL };
double *cuminflow{ NULL };
double *cuminflow_mWQ{ NULL };
double **cuminflow_mWQ_lay{ NULL };
double *outflow{ NULL };
double *outflow_mWQ{ NULL };
double **outflow_mWQ_lay{ NULL };
double *outflow_cWQ{ NULL };
double **outflow_cWQ_lay{ NULL };
double *cumoutflow{ NULL };
double *cumoutflow_mWQ{ NULL };
double **cumoutflow_mWQ_lay{ NULL };
double *outflow_diverted{ NULL };
double *outflow_diverted_conc{ NULL };
double **outflow_diverted_conc_lay{ NULL };
double *cumoutflow_diverted{ NULL };
double *cumoutflow_diverted_mWQ{ NULL };
double **cumoutflow_diverted_mWQ_lay{ NULL };

double *gwinflow{ NULL };
double *gwinflow_mWQ{ NULL };
double **gwinflow_mWQ_lay{ NULL };
double *gwcuminflow{ NULL };
double *gwcuminflow_mWQ{ NULL };
double **gwcuminflow_mWQ_lay{ NULL };
double *gwoutflow{ NULL };
double *gwoutflow_mWQ{ NULL };
double **gwoutflow_mWQ_lay{ NULL };
double *gwcumoutflow{ NULL };
double *gwcumoutflow_mWQ{ NULL };
double **gwcumoutflow_mWQ_lay{ NULL };
double *gwoutflow_diverted{ NULL };
double *gwoutflow_diverted_conc{ NULL };
double **gwoutflow_diverted_conc_lay{ NULL };
double *gwcumoutflow_diverted{ NULL };
double *gwcumoutflow_diverted_mWQ{ NULL };
double **gwcumoutflow_diverted_mWQ_lay{ NULL };

double *basinflow{ NULL };     // [BASIN] all HRUs
double *basinflow_conc{ NULL };     // [BASIN] all HRUs
double **basinflow_conc_lay{ NULL };     // [BASIN] all HRUs
double *basinflow_s{ NULL };   // [BASIN] all HRUs
double *cumbasinflow{ NULL };  // [BASIN] all HRUs
double *cumbasinflow_mWQ{ NULL };  // [BASIN] all HRUs
double **cumbasinflow_mWQ_lay{ NULL };  // [BASIN] all HRUs
double *basingw{ NULL };       // [BASIN} all HRUs
double *basingw_conc{ NULL };       // [BASIN} all HRUs
double **basingw_conc_lay{ NULL };       // [BASIN} all HRUs
double *basingw_s{ NULL };     // [BASIN} all HRUs
double *cumbasingw{ NULL };    // [BASIN} all HRUs
double *cumbasingw_mWQ{ NULL };    // [BASIN} all HRUs
double **cumbasingw_mWQ_lay{ NULL };    // [BASIN} all HRUs

double *soil_ssr_Buf{ NULL };    // buffered
double *soil_ssr_Buf_conc{ NULL };    // buffered
double **soil_ssr_Buf_conc_lay{ NULL };    // buffered
double *soil_runoff_Buf{ NULL }; // buffered
double *soil_runoff_Buf_conc{ NULL }; // buffered
double **soil_runoff_Buf_conc_lay{ NULL }; // buffered
double *soil_gw_Buf{ NULL };     // buffered
double *soil_gw_Buf_conc{ NULL };     // buffered
double **soil_gw_Buf_conc_lay{ NULL };     // buffered

double *HRU_cumbasinflow{ NULL };
double *HRU_cumbasinflow_mWQ{ NULL };
double **HRU_cumbasinflow_mWQ_lay{ NULL };
double *cum_to_Sd{ NULL };
double *cum_to_Sd_mWQ{ NULL };
double **cum_to_Sd_mWQ_lay{ NULL };
double *cum_to_soil_rechr{ NULL };
double *cum_to_soil_rechr_mWQ{ NULL };
double **cum_to_soil_rechr_mWQ_lay{ NULL };
double *Ktravel{ NULL };         // [nhru] Muskingum
double *cum_preferential_flow_to_gw{ NULL };

// local allocated arrays

double *outflow_0{ NULL };
double *gwoutflow_0{ NULL };
//double *soil_gw_Buf_0;

// declared parameters
const double *route_n{ NULL };         // [nhru]
const double *route_R{ NULL };         // [nhru]
const double *route_S0{ NULL };        // [nhru]
const double *route_L{ NULL };         // [nhru]
const double *route_X_M{ NULL };       // [nhru]
const long  *route_Cshp{ NULL };      // [nhru]

const double *Kstorage{ NULL };
const double *Lag{ NULL };
const double *ssrKstorage{ NULL };
const double *ssrLag{ NULL };
const double *runKstorage{ NULL };
const double *runLag{ NULL };
const double *gwKstorage{ NULL };
const double *gwLag{ NULL };

const double *basin_area{ NULL };        // [BASIN]
const double *hru_area{ NULL };
const long  *whereto{ NULL };
const long  *order{ NULL };
const long  *gwwhereto{ NULL };
const double *Sdmax{ NULL };
const double *soil_rechr_max{ NULL };
const long  *preferential_flow{ NULL }; // [nhru]
const long  *Sd_ByPass{ NULL };
const long  *soil_rechr_ByPass{ NULL };

// variable inputs

const double *soil_gw{ NULL }; // N.B. gw_flow in original CRHM
const double *soil_gw_conc{ NULL };
const double **soil_gw_conc_lay{ NULL };
const double *soil_ssr{ NULL };
const double *soil_ssr_conc{ NULL };
const double **soil_ssr_conc_lay{ NULL };
const double *soil_runoff{ NULL };
const double *soil_runoff_cWQ{ NULL };
const double **soil_runoff_cWQ_lay{ NULL };

// variable puts
double *Sd{ NULL };
double *Sd_conc{ NULL };
double **Sd_conc_lay{ NULL };
double *soil_moist{ NULL };
double *soil_moist_conc{ NULL };
double **soil_moist_conc_lay{ NULL };
double *soil_lower{ NULL };
double *soil_lower_conc{ NULL };
double **soil_lower_conc_lay{ NULL };
double *soil_rechr{ NULL };
double *soil_rechr_conc{ NULL };
double **soil_rechr_conc_lay{ NULL };
double *redirected_residual{ NULL };
double *redirected_residual_conc{ NULL };
double **redirected_residual_conc_lay{ NULL };
double *cum_redirected_residual{ NULL };
double *cum_redirected_residual_mWQ{ NULL };
double **cum_redirected_residual_mWQ_lay{ NULL };
double *gw{ NULL };
double *gw_conc{ NULL };
double **gw_conc_lay{ NULL };
double *conc_soil_rechr{ NULL };
double **conc_soil_rechr_lay{ NULL };
double *conc_soil_lower{ NULL };
double **conc_soil_lower_lay{ NULL };
double *conc_soil_moist{ NULL };
double **conc_soil_moist_lay{ NULL };

ClassMuskingum **hruDelay_mWQ{ NULL }; // [numsubstances] handled locally
ClassClark **Clark_hruDelay_mWQ{ NULL };
ClassClark **ssrDelay_mWQ{ NULL };
ClassClark **runDelay_mWQ{ NULL };
ClassClark **gwDelay_mWQ{ NULL };

ClassMuskingum *hruDelay{ NULL };
ClassClark *Clark_hruDelay{ NULL };
ClassClark *ssrDelay{ NULL };
ClassClark *runDelay{ NULL };
ClassClark *gwDelay{ NULL };

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

double hru_u_{0.0};

// declared variables

double *SWE_max{ NULL };
double *SWE{ NULL };
double *SWE_conc{ NULL };
double **SWE_conc_lay{ NULL };
double *Subl{ NULL };
double *Subl_conc{ NULL };
double **Subl_conc_lay{ NULL };
double *Drift_in{ NULL };
double *Drift_in_conc{ NULL };
double **Drift_in_conc_lay{ NULL };
double *Drift_out{ NULL };       // HRU composite drift
double *Drift_out_conc{ NULL };  // HRU composite drift
double **Drift_out_conc_lay{ NULL };  // HRU composite drift
double *cumSubl{ NULL };
double *cumSubl_mWQ{ NULL };
double **cumSubl_mWQ_lay{ NULL };
double *cumDriftOut{ NULL };
double *cumDriftOut_mWQ{ NULL };
double **cumDriftOut_mWQ_lay{ NULL };
double *cumDriftIn{ NULL };
double *cumDriftIn_mWQ{ NULL };
double **cumDriftIn_mWQ_lay{ NULL };
double *cumSno{ NULL };
double *cumSno_mWQ{ NULL };
double **cumSno_mWQ_lay{ NULL };
double *snowdepth{ NULL };
double *BasinSnowLoss{ NULL };
double *BasinSnowLoss_mWQ{ NULL };
double **BasinSnowLoss_mWQ_lay{ NULL };
double *BasinSnowGain{ NULL };
double *BasinSnowGain_mWQ{ NULL };
double **BasinSnowGain_mWQ_lay{ NULL };
double *cumBasinSnowLoss{ NULL };
double *cumBasinSnowLoss_mWQ{ NULL };
double **cumBasinSnowLoss_mWQ_lay{ NULL };
double *cumBasinSnowGain{ NULL };
double *cumBasinSnowGain_mWQ{ NULL };
double **cumBasinSnowGain_mWQ_lay{ NULL };
double *SublH{ NULL };
double *DriftH{ NULL };
double *Prob{ NULL };
double *SnowAge{ NULL };
double *SWE_Init{ NULL };
long  *DrySnow{ NULL };

// declared parameters
const double *fetch{ NULL };
const double *Ht{ NULL };
const double *distrib{ NULL };
const double *basin_area{ NULL };
const double *hru_area{ NULL };
const double *A_S{ NULL };
const double *u_D{ NULL };
const double *Drift_offset{ NULL };
const double *Drift_slope{ NULL };
const double *Subl_offset{ NULL };
const double *Subl_slope{ NULL };
const long *N_S{ NULL };
const double *rain_conc{ NULL };
const double **rain_conc_lay{ NULL };
const double *snow_conc{ NULL };
const double **snow_conc_lay{ NULL };
const double *atmos_mWQ{ NULL };
const double **atmos_mWQ_lay{ NULL };
const long *inhibit_evap{ NULL };
const long *inhibit_bs{ NULL };
const long *inhibit_subl{ NULL };

// variable inputs
const double *hru_t{ NULL };
const double *hru_rh{ NULL };
const double *hru_u{ NULL };
const double *hru_Uadjust{ NULL };
const double *net_snow{ NULL };
const long  *hru_newsnow{ NULL };

// local allocated arrays
double *BasinSnowGain_0{ NULL };
double *cumBasinSnowGain_0{ NULL };
double *BasinSnowLoss_0{ NULL };
double *cumBasinSnowLoss_0{ NULL };

double *hru_basin{ NULL };
double *SWE_0{ NULL };
double *SWE_Init_0{ NULL };
double *z_s_0{ NULL };
double *rho_0{ NULL };

double *Drift_out_0{ NULL };
double *Drift_in_0{ NULL };
double *cumDriftIn_0{ NULL };
double *cumDriftOut_0{ NULL };
double *cumSubl_0{ NULL };
double *Subl_0{ NULL };
double *SublH_0{ NULL };
double *DriftH_0{ NULL };
double *cumSno_0{ NULL };
double *Prob_0{ NULL };
double *SnowAge_0{ NULL };
long  *DrySnow_0{ NULL };

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

long meltrunoffDiv{0};
long soil_ssrDiv{0};
long soil_runoffDiv{0};
long soil_gwDiv{0};

// declared variables

double* ssrinflow{NULL};
double *ssrinflow_mWQ{ NULL };
double **ssrinflow_mWQ_lay{ NULL };
double *ssrcuminflow{ NULL };
double *ssrcuminflow_mWQ{ NULL };
double **ssrcuminflow_mWQ_lay{ NULL };
double *ssroutflow{ NULL };
double *ssroutflow_mWQ{ NULL };
double **ssroutflow_mWQ_lay{ NULL };
double *ssrcumoutflow{ NULL };
double *ssrcumoutflow_mWQ{ NULL };
double **ssrcumoutflow_mWQ_lay{ NULL };

double *runinflow{ NULL };
double *runinflow_mWQ{ NULL };
double **runinflow_mWQ_lay{ NULL };
double *runcuminflow{ NULL };
double *runcuminflow_mWQ{ NULL };
double **runcuminflow_mWQ_lay{ NULL };
double *runoutflow{ NULL };
double *runoutflow_mWQ{ NULL };
double **runoutflow_mWQ_lay{ NULL };
double *runcumoutflow{ NULL };
double *runcumoutflow_mWQ{ NULL };
double **runcumoutflow_mWQ_lay{ NULL };

double *inflow{ NULL };
double *inflow_mWQ{ NULL };
double **inflow_mWQ_lay{ NULL };
double *cuminflow{ NULL };
double *cuminflow_mWQ{ NULL };
double **cuminflow_mWQ_lay{ NULL };
double *outflow{ NULL };
double *outflow_mWQ{ NULL };
double **outflow_mWQ_lay{ NULL };
double *outflow_cWQ{ NULL };
double **outflow_cWQ_lay{ NULL };
double *outflow_diverted{ NULL };
double *outflow_diverted_conc{ NULL };
double **outflow_diverted_conc_lay{ NULL };
double *cumoutflow_diverted{ NULL };
double *cumoutflow_diverted_mWQ{ NULL };
double **cumoutflow_diverted_mWQ_lay{ NULL };
double *cumoutflow{ NULL };
double *cumoutflow_mWQ{ NULL };
double **cumoutflow_mWQ_lay{ NULL };

double *gwinflow{ NULL };
double *gwinflow_mWQ{ NULL };
double **gwinflow_mWQ_lay{ NULL };
double *gwoutflow_diverted{ NULL };
double *gwoutflow_diverted_conc{ NULL };
double **gwoutflow_diverted_conc_lay{ NULL };
double *gwcumoutflow_diverted{ NULL };
double *gwcumoutflow_diverted_mWQ{ NULL };
double **gwcumoutflow_diverted_mWQ_lay{ NULL };
double *gwoutflow{ NULL };
double *gwoutflow_mWQ{ NULL };
double **gwoutflow_mWQ_lay{ NULL };
double *gwcuminflow{ NULL };
double *gwcuminflow_mWQ{ NULL };
double **gwcuminflow_mWQ_lay{ NULL };
double *gwcumoutflow{ NULL };
double *gwcumoutflow_mWQ{ NULL };
double **gwcumoutflow_mWQ_lay{ NULL };

double *basinflow{ NULL };     // [BASIN] all HRUs
double *basinflow_conc{ NULL };     // [BASIN] all HRUs
double **basinflow_conc_lay{ NULL };     // [BASIN] all HRUs
double *basinflow_s{ NULL };   // [BASIN] all HRUs
double *cumbasinflow{ NULL };  // [BASIN] all HRUs
double *cumbasinflow_mWQ{ NULL };  // [BASIN] all HRUs
double **cumbasinflow_mWQ_lay{ NULL };  // [BASIN] all HRUs
double *basingw{ NULL };       // [BASIN} all HRUs
double *basingw_conc{ NULL };       // [BASIN} all HRUs
double **basingw_conc_lay{ NULL };       // [BASIN} all HRUs
double *basingw_s{ NULL };     // [BASIN} all HRUs
double *cumbasingw{ NULL };    // [BASIN} all HRUs
double *cumbasingw_mWQ{ NULL };    // [BASIN} all HRUs
double **cumbasingw_mWQ_lay{ NULL };    // [BASIN} all HRUs

double *soil_ssr_Buf{ NULL };    // buffered
double *soil_ssr_Buf_conc{ NULL };    // buffered
double **soil_ssr_Buf_conc_lay{ NULL };    // buffered
double *soil_runoff_Buf{ NULL }; // buffered
double *soil_runoff_Buf_conc{ NULL }; // buffered
double **soil_runoff_Buf_conc_lay{ NULL }; // buffered
double *soil_gw_Buf{ NULL };     // buffered
double *soil_gw_Buf_conc{ NULL };     // buffered
double **soil_gw_Buf_conc_lay{ NULL };     // buffered

double *HRU_cumbasinflow{ NULL };
double *HRU_cumbasinflow_mWQ{ NULL };
double **HRU_cumbasinflow_mWQ_lay{ NULL };
double *cum_to_Sd{ NULL };
double *cum_to_Sd_mWQ{ NULL };
double **cum_to_Sd_mWQ_lay{ NULL };
double *cum_to_soil_rechr{ NULL };
double *cum_to_soil_rechr_mWQ{ NULL };
double **cum_to_soil_rechr_mWQ_lay{ NULL };
double *Used{ NULL };    // [BASIN}
double *Used_mWQ{ NULL };    // [BASIN}
double **Used_mWQ_lay{ NULL };    // [BASIN}

double *distrib_sum{ NULL };
double *Ktravel{ NULL };         // [nhru] Muskingum
double *cum_preferential_flow_to_gw{ NULL };
double *cumscaling_boost{ NULL };    // [nhru]

// local allocated arrays

double *outflow_0{ NULL };
double *gwoutflow_0{ NULL };
//double *soil_gw_Buf_0;

// declared parameters
const double *route_n{ NULL };         // [nhru]
const double *route_R{ NULL };         // [nhru]
const double *route_S0{ NULL };        // [nhru]
const double *route_L{ NULL };         // [nhru]
const double *route_X_M{ NULL };       // [nhru]
const long  *route_Cshp{ NULL };      // [nhru]

const double *Kstorage{ NULL };
const double *Lag{ NULL };             // [nhru]
const double *ssrKstorage{ NULL };     // [nhru]
const double *ssrLag{ NULL };          // [nhru]
const double *runKstorage{ NULL };     // [nhru]
const double *runLag{ NULL };          // [nhru]
const double *gwKstorage{ NULL };
const double *gwLag{ NULL };
const long  *gwwhereto{ NULL };       // [nhru]

const double *basin_area{ NULL };      // [BASIN]
const double *hru_area{ NULL };        // [nhru]
const double *distrib{ NULL };
const double *distrib_Basin{ NULL };
const double **distrib_hru{ NULL };
const double *Sdmax{ NULL };           // [nhru]
const double *soil_rechr_max{ NULL };  // [nhru]
const long  *order{ NULL };
const long  *preferential_flow{ NULL }; // [nhru]
const long  *Sd_ByPass{ NULL };       // [nhru]
const long  *soil_rechr_ByPass{ NULL };

const double *scaling_factor{ NULL };    // temporary modification

// variable inputs
const double *soil_gw{ NULL }; // N.B. gw_flow in original CRHM
const double *soil_gw_conc{ NULL };
const double **soil_gw_conc_lay{ NULL };
const double *soil_ssr{ NULL };
const double *soil_ssr_conc{ NULL };
const double **soil_ssr_conc_lay{ NULL };
const double *soil_runoff{ NULL };
const double *soil_runoff_cWQ{ NULL };
const double **soil_runoff_cWQ_lay{ NULL };

// variable puts
double *Sd{ NULL };
double *Sd_conc{ NULL };
double **Sd_conc_lay{ NULL };
double *soil_moist{ NULL };
double *soil_moist_conc{ NULL };
double **soil_moist_conc_lay{ NULL };
double *soil_lower{ NULL };
double *soil_lower_conc{ NULL };
double **soil_lower_conc_lay{ NULL };
double *soil_rechr{ NULL };
double *soil_rechr_conc{ NULL };
double **soil_rechr_conc_lay{ NULL };
double *redirected_residual{ NULL };
double *redirected_residual_conc{ NULL };
double **redirected_residual_conc_lay{ NULL };
double *cum_redirected_residual{ NULL };
double *cum_redirected_residual_mWQ{ NULL };
double **cum_redirected_residual_mWQ_lay{ NULL };
double *gw{ NULL };
double *gw_conc{ NULL };
double **gw_conc_lay{ NULL };
double *conc_soil_rechr{ NULL };
double **conc_soil_rechr_lay{ NULL };
double *conc_soil_lower{ NULL };
double **conc_soil_lower_lay{ NULL };
double *conc_soil_moist{ NULL };
double **conc_soil_moist_lay{ NULL };

ClassMuskingum *hruDelay{ NULL };
ClassClark *Clark_hruDelay{ NULL };
ClassClark *ssrDelay{ NULL };
ClassClark *runDelay{ NULL };
ClassClark *gwDelay{ NULL };

ClassMuskingum **hruDelay_mWQ{ NULL }; // [numsubstances] handled locally
ClassClark **Clark_hruDelay_mWQ{ NULL };
ClassClark **ssrDelay_mWQ{ NULL };
ClassClark **runDelay_mWQ{ NULL };
ClassClark **gwDelay_mWQ{ NULL };

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
double *infil{ NULL };
double *snowinfil{ NULL };
double *runoff{ NULL };
double *meltrunoff{ NULL };
double *hru_evap{ NULL };
double *hru_cum_evap{ NULL };
double *hru_cum_actet{ NULL };
double *hru_actet{ NULL };
double *net_rain{ NULL };
double *SWE{ NULL };
double *SWE_max{ NULL };
double *hru_t{ NULL };
double *SWE_conc{ NULL };
double **SWE_conc_lay{ NULL };

double *soil_moist{ NULL };
double *soil_rechr{ NULL };

// declared parameters
const double* infil_0{ NULL };
const double* snowinfil_0{ NULL };
const double* runoff_0{ NULL };
const double* meltrunoff_0{ NULL };
const double* hru_evap_0{ NULL };
const double* hru_actet_0{ NULL };
const double* hru_cum_evap_0{ NULL };
const double* hru_cum_actet_0{ NULL };
const double* net_rain_0{ NULL };
const double* SWE_0{ NULL };
const double* hru_t_0{ NULL };
const double* SWE_conc_0{ NULL };
const double** SWE_conc_lay_0{ NULL };

const double* soil_rechr_0{ NULL };
const double* soil_moist_0{ NULL };
const double* soil_rechr_max{ NULL };
const double* soil_moist_max{ NULL };

const long  *Julian_start{ NULL };
const long  *Julian_end{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_Test_Hype* klone(string name) const;
};

class ClassWQ_pbsmSnobal : public ClassModule {
public:

ClassWQ_pbsmSnobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

double hru_u_{0.0};

// declared variables

double *SWE_max{ NULL };
double *SWE_conc{ NULL };
double **SWE_conc_lay{ NULL };
double *Subl{ NULL };
double *Subl_conc{ NULL };
double **Subl_conc_lay{ NULL };
double *Drift{ NULL };
double *Drift_in{ NULL };
double *Drift_in_conc{ NULL };
double **Drift_in_conc_lay{ NULL };
double *Drift_out{ NULL };       // HRU composite drift
double *Drift_out_conc{ NULL };  // HRU composite drift
double **Drift_out_conc_lay{ NULL };  // HRU composite drift
double *cumSubl{ NULL };
double *cumSubl_mWQ{ NULL };
double **cumSubl_mWQ_lay{ NULL };
double *cumDriftOut{ NULL };
double *cumDriftOut_mWQ{ NULL };
double **cumDriftOut_mWQ_lay{ NULL };
double *cumDrift{ NULL };
double *cumDriftIn{ NULL };
double *cumDriftIn_mWQ{ NULL };
double **cumDriftIn_mWQ_lay{ NULL };
double *cumSno{ NULL };
double *cumSno_mWQ{ NULL };
double **cumSno_mWQ_lay{ NULL };
double *snowdepth{ NULL };
double *BasinSnowLoss{ NULL };
double *BasinSnowLoss_mWQ{ NULL };
double **BasinSnowLoss_mWQ_lay{ NULL };
double *BasinSnowGain{ NULL };
double *BasinSnowGain_mWQ{ NULL };
double **BasinSnowGain_mWQ_lay{ NULL };
double *cumBasinSnowLoss{ NULL };
double *cumBasinSnowLoss_mWQ{ NULL };
double **cumBasinSnowLoss_mWQ_lay{ NULL };
double *cumBasinSnowGain{ NULL };
double *cumBasinSnowGain_mWQ{ NULL };
double **cumBasinSnowGain_mWQ_lay{ NULL };
double *SublH{ NULL };
double *DriftH{ NULL };
double *Prob{ NULL };
double *SnowAge{ NULL };
double *SWE_Init{ NULL };
long  *DrySnow{ NULL };

// declared parameters
const double *fetch{ NULL };
const double *Ht{ NULL };
const double *distrib{ NULL };
const double *basin_area{ NULL };
const double *hru_area{ NULL };
const double *A_S{ NULL };
const double *u_D{ NULL };
const double *Drift_offset{ NULL };
const double *Drift_slope{ NULL };
const double *Subl_offset{ NULL };
const double *Subl_slope{ NULL };
const long *N_S{ NULL };
const double *rain_conc{ NULL };
const double **rain_conc_lay{ NULL };
const double *snow_conc{ NULL };
const double **snow_conc_lay{ NULL };
const double *atmos_mWQ{ NULL };
const double **atmos_mWQ_lay{ NULL };
const long *inhibit_evap{ NULL };
const long *inhibit_bs{ NULL };
const long *inhibit_subl{ NULL };

// put variable inputs
double *SWE{ NULL }; // actually m_s

// variable inputs
const double *z_s{ NULL };
const double *rho{ NULL };
const double *hru_t{ NULL };
const double *hru_u{ NULL };
const double *hru_Uadjust{ NULL };
const double *net_snow{ NULL };
const long  *hru_newsnow{ NULL };
const double *hru_ea{ NULL };

// local allocated arrays

double *BasinSnowGain_0{ NULL };
double *cumBasinSnowGain_0{ NULL };
double *BasinSnowLoss_0{ NULL };
double *cumBasinSnowLoss_0{ NULL };

double *hru_basin{ NULL };
double *SWE_0{ NULL };
double *SWE_Init_0{ NULL };
double *z_s_0{ NULL };
double *rho_0{ NULL };

double *Drift_out_0{ NULL };
double *Drift_in_0{ NULL };
double *cumDriftIn_0{ NULL };
double *cumDriftOut_0{ NULL };
double *cumSubl_0{ NULL };
double *Subl_0{ NULL };
double *cumSno_0{ NULL };
double *SnowAge_0{ NULL };
long *DrySnow_0{ NULL };

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
double *inflow_conc{ NULL };
double **inflow_conc_lay{ NULL };
double *outflow_conc{ NULL };
double **outflow_conc_lay{ NULL };
double *runoutflow_conc{ NULL };
double **runoutflow_conc_lay{ NULL };
double *ssroutflow_conc{ NULL };
double **ssroutflow_conc_lay{ NULL };
double *gwoutflow_conc{ NULL };
double **gwoutflow_conc_lay{ NULL };

// declared parameters

// variable inputs
const double *inflow{ NULL };
const double *inflow_mWQ{ NULL };
const double **inflow_mWQ_lay{ NULL };
const double *outflow{ NULL };
const double *outflow_mWQ{ NULL };
const double **outflow_mWQ_lay{ NULL };
const double *outflow_cWQ{ NULL };
const double **outflow_cWQ_lay{ NULL };
const double *runoutflow{ NULL };
const double *runoutflow_mWQ{ NULL };
const double **runoutflow_mWQ_lay{ NULL };
const double *ssroutflow{ NULL };
const double *ssroutflow_mWQ{ NULL };
const double **ssroutflow_mWQ_lay{ NULL };
const double *gwoutflow{ NULL };
const double *gwoutflow_mWQ{ NULL };
const double **gwoutflow_mWQ_lay{ NULL };

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
double *conc_soil_rechr{ NULL };   // concentration of inorganic nitrogen *** from soilstate
double **conc_soil_rechr_lay{ NULL };
double *conc_soil_lower{ NULL };   // concentration of organic nitrogen *** from soilstate
double **conc_soil_lower_lay{ NULL };
double *conc_soil_moist{ NULL };   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
double **conc_soil_moist_lay{ NULL };

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

double *soil_moist_change_mWQ{ NULL };
double **soil_moist_change_mWQ_lay{ NULL };

double *soil_top_change_mWQ{ NULL };
double **soil_top_change_mWQ_lay{ NULL };
double *soil_top_mWQ_last{ NULL };
double **soil_top_mWQ_lay_last{ NULL };

double *soil_bottom_change_mWQ{ NULL };
double **soil_bottom_change_mWQ_lay{ NULL };
double *soil_bottom_mWQ_last{ NULL };
double **soil_bottom_mWQ_lay_last{ NULL };

double *soil_ssr_change_mWQ{ NULL };
double **soil_ssr_change_mWQ_lay{ NULL };
double *soil_ssr_mWQ_last{ NULL };
double **soil_ssr_mWQ_lay_last{ NULL };

double *Sd_change_mWQ{ NULL };
double **Sd_change_mWQ_lay{ NULL };
double *Sd_mWQ_last{ NULL };
double **Sd_mWQ_lay_last{ NULL };

double *gw_change_mWQ{ NULL };
double **gw_change_mWQ_lay{ NULL };
double *gw_mWQ_last{ NULL };
double **gw_mWQ_lay_last{ NULL };

double *soil_gw_change_mWQ{ NULL };
double **soil_gw_change_mWQ_lay{ NULL };
double *soil_gw_mWQ_last{ NULL };
double **soil_gw_mWQ_lay_last{ NULL };

double *gw_flow_change_mWQ{ NULL };
double **gw_flow_change_mWQ_lay{ NULL };
double *gw_flow_mWQ_last{ NULL };
double **gw_flow_mWQ_lay_last{ NULL };

double *infil_act_change_mWQ{ NULL };
double **infil_act_change_mWQ_lay{ NULL };
double *infil_act_mWQ_last{ NULL };
double **infil_act_mWQ_lay_last{ NULL };

double *redirected_residual_change_mWQ{ NULL };
double **redirected_residual_change_mWQ_lay{ NULL };
double *redirected_residual_mWQ_last{ NULL };
double **redirected_residual_mWQ_lay_last{ NULL };

double *soil_runoff_change_mWQ{ NULL };
double **soil_runoff_change_mWQ_lay{ NULL };
double *soil_runoff_mWQ_last{ NULL };
double **soil_runoff_mWQ_lay_last{ NULL };

// variable get inputs
const double *soil_rechr{ NULL };
const double *soil_lower{ NULL };
const double *soil_moist{ NULL };
const double *soil_ssr{ NULL };
const double *Sd{ NULL };
const double *gw{ NULL };
const double *soil_gw{ NULL };
const double *gw_flow{ NULL };
const double *infil_act{ NULL };
const double *redirected_residual{ NULL };
const double *soil_runoff{ NULL };

const double *conc_soil_rechr{ NULL };
const double **conc_soil_rechr_lay{ NULL };
const double *conc_soil_lower{ NULL };
const double **conc_soil_lower_lay{ NULL };
const double *soil_ssr_conc{ NULL };
const double **soil_ssr_conc_lay{ NULL };
const double *Sd_conc{ NULL };
const double **Sd_conc_lay{ NULL };
const double *gw_conc{ NULL };
const double **gw_conc_lay{ NULL };
const double *soil_gw_conc{ NULL };
const double **soil_gw_conc_lay{ NULL };
const double *gw_flow_conc{ NULL };
const double **gw_flow_conc_lay{ NULL };
const double *infil_act_conc{ NULL };
const double **infil_act_conc_lay{ NULL };
const double *redirected_residual_conc{ NULL };
const double **redirected_residual_conc_lay{ NULL };
const double *soil_runoff_cWQ{ NULL };
const double **soil_runoff_cWQ_lay{ NULL };

//declared variables
long *run_ID{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_Gen_Mass_Var_Soil* klone(string name) const;
};

class ClassGrow_crops_annually : public ClassModule {
public:

ClassGrow_crops_annually(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long ObsCnt_N_up{0};
long ObsCnt_P_up{0};
long ObsCntMan_N_up{0};
long ObsCntMan_P_up{0};
long ObsCntRes_N_up{0};
long ObsCntRes_P_up{0};
long ObsCnt_N_down{0};
long ObsCnt_P_down{0};
long ObsCntMan_N_down{0};
long ObsCntMan_P_down{0};
long ObsCntRes_N_down{0};
long ObsCntRes_P_down{0};
long ObsCnt_fertperiod{0};
long ObsCnt_litterperiod{0};

// declared variables
double *Fert_N_amount_up{ NULL };
double *Fert_P_amount_up{ NULL };
double *Man_N_amount_up{ NULL };
double *Man_P_amount_up{ NULL };
double *Fert_N_amount_down{ NULL };
double *Fert_P_amount_down{ NULL };
double *Man_N_amount_down{ NULL };
double *Man_P_amount_down{ NULL };
double *Res_N_amount_up{ NULL };
double *Res_P_amount_up{ NULL };
double *Res_N_amount_down{ NULL };
double *Res_P_amount_down{ NULL };
//double *Fertday;
//double *Manday;
//double *Resday_up;
double *Fertperiod{ NULL };
double *Litterperiod{ NULL };
long *LockOut{ NULL };

//long  *SecondDown_fert;
//long  *SecondDown_man;

// declared parameters
const long  *Ag_YearStart{ NULL };

// put parameters
const double *Htmax{ NULL };
const double *Init_Crop_Ht_1{ NULL };
const double *Crop_Grow_Rate_1{ NULL };
const double *JCrop_Start_1{ NULL };
const double *JCrop_Harvest_1{ NULL };
const double *Crop_Htmax_1{ NULL };
const double *Init_Crop_Ht_2{ NULL };
const double *Crop_Grow_Rate_2{ NULL };
const double *JCrop_Start_2{ NULL };
const double *JCrop_Harvest_2{ NULL };
const double *Crop_Htmax_2{ NULL };

double *Ht{ NULL };
double *fertNamount_up{ NULL };
double *fertPamount_up{ NULL };
double *fertNamount_down{ NULL };
double *fertPamount_down{ NULL };
double *manNamount_up{ NULL };
double *manPamount_up{ NULL };
double *manNamount_down{ NULL };
double *manPamount_down{ NULL };
double *resNamount_up{ NULL };
double *resPamount_up{ NULL };
double *resNamount_down{ NULL };
double *resPamount_down{ NULL };

double *manday_up{ NULL };
double *manday_down{ NULL };
double *fertday_up{ NULL };
double *fertday_down{ NULL };
double *resday_up{ NULL };
double *resday_down{ NULL };
long *fertperiod{ NULL };
long *litterperiod{ NULL };

// declared observation variables
const double *Fert_N_up{ NULL };
const double *Fert_P_up{ NULL };
const double *Man_N_up{ NULL };
const double *Man_P_up{ NULL };
const double *Res_N_up{ NULL };
const double *Res_P_up{ NULL };
const double *Fert_N_down{ NULL };
const double *Fert_P_down{ NULL };
const double *Man_N_down{ NULL };
const double *Man_P_down{ NULL };
const double *Res_N_down{ NULL };
const double *Res_P_down{ NULL };
const long *Fert_period{ NULL };

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

double *basinflow_change_mWQ{ NULL };
double **basinflow_change_mWQ_lay{ NULL };
double *basinflow_mWQ_last{ NULL };
double **basinflow_mWQ_lay_last{ NULL };

double *basingw_change_mWQ{ NULL };
double **basingw_change_mWQ_lay{ NULL };
double *basingw_mWQ_last{ NULL };
double **basingw_mWQ_lay_last{ NULL };

double *outflow_diverted_change_mWQ{ NULL };
double **outflow_diverted_change_mWQ_lay{ NULL };
double *outflow_diverted_mWQ_last{ NULL };
double **outflow_diverted_mWQ_lay_last{ NULL };

double *gwoutflow_diverted_change_mWQ{ NULL };
double **gwoutflow_diverted_change_mWQ_lay{ NULL };
double *gwoutflow_diverted_mWQ_last{ NULL };
double **gwoutflow_diverted_mWQ_lay_last{ NULL };

// variable get inputs
double *basinflow{ NULL };
double *basingw{ NULL };
double *outflow_diverted{ NULL };
double *gwoutflow_diverted{ NULL };

double *basinflow_conc{ NULL };
double **basinflow_conc_lay{ NULL };
double *basingw_conc{ NULL };
double **basingw_conc_lay{ NULL };
double *outflow_diverted_conc{ NULL };
double **outflow_diverted_conc_lay{ NULL };
double *gwoutflow_diverted_conc{ NULL };
double **gwoutflow_diverted_conc_lay{ NULL };

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
double* lapse_rate{ NULL };
double* lapse_rate_Mthly{ NULL };

void decl(void);
void init(void);
void run(void);

Classlapse_rate_Monthly_Mod* klone(string name) const;
};

class ClassGlacier_melt_debris_cover_estimate_Mod : public ClassModule {
public:

ClassGlacier_melt_debris_cover_estimate_Mod(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const double* debris_h{ NULL };
const double* T_threshold{ NULL };

// declared variables

double* lagT{ NULL };
double* lagSW{ NULL };
double* Gmelt_energy{ NULL };
double* den_air{ NULL };
double* K_kat{ NULL };
double* Cp_water{ NULL };
double* Xmelt{ NULL };
double* Xmelt_int{ NULL };
double* Xmelt_acc{ NULL };
double* Xmelt_V5{ NULL };

// put variables

double* Gn_ebsm{ NULL };
double* Gh_ebsm{ NULL };
double* Ge_ebsm{ NULL };
double* Gp_ebsm{ NULL };

// get variables

const double* Albedo{ NULL };
const double* T_rain{ NULL };
const double* hru_t{ NULL };
const double* hru_ea{ NULL };
const double* net_rain{ NULL };
const double* Pa{ NULL };
const double* Qnsn_Var{ NULL };

// observations

const double* lagT1{ NULL };
const double* lagT2{ NULL };
const double* lagT3{ NULL };
const double* lagT4{ NULL };
const double* lagSW1{ NULL };
const double* lagSW2{ NULL };
const double* lagSW3{ NULL };
const double* lagSW4{ NULL };
const double* lagSW5{ NULL };
const double* lagSW6{ NULL };

void decl(void);
void init(void);
void run(void);

ClassGlacier_melt_debris_cover_estimate_Mod* klone(string name) const;
};

class ClassSoilPrairie : public ClassModule {
public:

ClassSoilPrairie(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv{0};
long meltrunoffDiv{0};
long runoffDiv{0};
long evapDiv{0};

// allocated storage
double **current_area{ NULL }; // [NumSloughs] [nhru]
double **current_depth{ NULL }; // [NumSloughs] [nhru]
double **current_volume{ NULL }; // [NumSloughs] [nhru]
double **S_values{ NULL }; // [NumSloughs] [nhru]
double **h_values{ NULL }; // [NumSloughs] [nhru]
double **wetland_drainage{ NULL }; // [NumSloughs] [nhru]


// declared observation variables

// declared variables
double *gw{ NULL };
double *soil_rechr{ NULL };
double *soil_moist{ NULL };
double *soil_gw{ NULL };
double *gw_flow{ NULL };
double *soil_ssr{ NULL };
double *rechr_ssr{ NULL };
double *soil_runoff{ NULL };
double *cum_soil_ssr{ NULL };
double *cum_rechr_ssr{ NULL };
double *cum_soil_runoff{ NULL };
double *cum_runoff_to_Sd{ NULL };
double *cum_redirected_residual{ NULL };
double *soil_gw_D{ NULL };
double *soil_ssr_D{ NULL };
double *gw_flow_D{ NULL };
double *soil_runoff_D{ NULL };
double *HK_V{ NULL };
double *HK_A{ NULL };
double *HD{ NULL };
double *redirected_residual{ NULL };
double *infil_act{ NULL };
double *cum_infil_act{ NULL };
double *infil_act_D{ NULL };
double *Sd_water_frac{ NULL };
double *contrib_frac{ NULL };
double *wetlands_evap{ NULL };
double *total_evap{ NULL };
double *direct_rain{ NULL };

double *Pond_water_frac{ NULL }; // Sd[hh]/Sdmax[hh]
double *Pond_evap{ NULL };
double *Pond_area{ NULL };
double *Pond_volume{ NULL };
double *Pond_h{ NULL };
double *Pond_hmax{ NULL };
double *Pond_s{ NULL };
double *Sd{ NULL };
double *runoff_to_Pond{ NULL };

double *Small_Ponds_water_frac{ NULL }; // Small_Ponds_Sd[hh]/Small_Ponds_Sdmax[hh]
double *Small_Ponds_evap{ NULL };
double *Small_Ponds_area{ NULL };
double *Small_Ponds_Sd{ NULL };
double *runoff_to_Small_Ponds{ NULL };
double *Small_Ponds_runoff_to_Pond{ NULL };

// local variables
double *cum_soil_gw{ NULL };
double *cum_gw_flow{ NULL };
double *cum_hru_condense{ NULL };
double *soil_moist_Init{ NULL };
double *soil_rechr_Init{ NULL };
double *Sd_Init{ NULL };
double *gw_Init{ NULL };
double *SWE_Init{ NULL };

double *snowinfil_buf{ NULL };
double *runoff_buf{ NULL };
double *meltrunoff_buf{ NULL };
double *hru_evap_buf{ NULL };

// declared parameters
const double *Sdmax{ NULL };
const double *Sdinit{ NULL };
const double *gw_max{ NULL };
const double *gw_init{ NULL };
const double *gw_K{ NULL };
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *soil_rechr_max{ NULL };
const double *soil_rechr_init{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_moist_init{ NULL };
const double *soil_gw_K{ NULL };
const double *rechr_ssr_K{ NULL };
const double *lower_ssr_K{ NULL };
const double *Sd_ssr_K{ NULL };
const double *Sd_gw_K{ NULL };
const double *Sd_water_frac_max{ NULL };
const double *evap_threshold{ NULL };
const long *soil_withdrawal{ NULL };
const long **soil_withdrawal_Tables{ NULL };

const long *cov_type{ NULL };
const long *transp_limited{ NULL };
const long *soil_ssr_runoff{ NULL };
const long *inhibit_evap{ NULL };
const long *Sd_normal{ NULL };

const double *Pond_p{ NULL };
const double *Pond_C1{ NULL };
const double *Pond_C2{ NULL };
const double *Pond_C3{ NULL };
const double *Pond_contrib_frac{ NULL }; // Pond fraction of basin
const double *Pond_area_max{ NULL };

const double *Small_Ponds_Sdmax{ NULL };
const double *Small_Ponds_Sdinit{ NULL };
const double *Small_Ponds_p{ NULL };
const double *Small_Ponds_C1{ NULL };
const double *Small_Ponds_C2{ NULL };
const double *Small_Ponds_C3{ NULL };
const double *Small_Ponds_contrib_frac{ NULL }; // Small Ponds fraction of basin
const double *Small_Ponds_area_max{ NULL };



// variable inputs
const double *infil{ NULL };
const double *snowinfil{ NULL };
const double *meltrunoff{ NULL }; // frozen melt runoff
const double *runoff{ NULL };     // liquid runoff
const double *hru_evap{ NULL };
const double *hru_evap_PT{ NULL };

// variable put inputs
double *hru_actet{ NULL };      // [nhru]
double *hru_cum_actet{ NULL };


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

const double* debris_h{ NULL };
const double* T_threshold{ NULL };

// declared variables

double* lagT{ NULL };
double* lagSW{ NULL };
double* Xmelt{ NULL };
double* Xmelt_int{ NULL };
double* Xmelt_acc{ NULL };

// get variables

const double* Albedo{ NULL };
const double* hru_t{ NULL };
const double* Qnsn_Var{ NULL };

// observations

const double* lagT1{ NULL };
const double* lagT2{ NULL };
const double* lagT3{ NULL };
const double* lagT4{ NULL };
const double* lagSW1{ NULL };
const double* lagSW2{ NULL };
const double* lagSW3{ NULL };
const double* lagSW4{ NULL };
const double* lagSW5{ NULL };
const double* lagSW6{ NULL };

void decl(void);
void init(void);
void run(void);

ClassGlacier_debris_cover* klone(string name) const;
};

class Class_lapse_rate_Monthly : public ClassModule {
public:

Class_lapse_rate_Monthly(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double* lapse_rate{ NULL };
double* lapse_rate_Mthly{ NULL };

void decl(void);
void init(void);
void run(void);

Class_lapse_rate_Monthly* klone(string name) const;
};

#endif





