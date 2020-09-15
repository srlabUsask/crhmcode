//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSoil : public ClassModule {
public:

ClassSoil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;

// declared observation variables

// declared variables
long *current_getstep;
double *Sd;
double *gw;
double *soil_rechr;
double *soil_moist;
double *soil_gw;
double *Sd_gw;
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
double *infil_act;
double *cum_infil_act;
double *infil_act_D;

double *soil_runoff_stream;
double *weir_outflow;
double *weir_outflow_m3s;
double *weir_water_A;
double *weir_water_V;
double *weir_water_h;
double *weir_evap;
double *cum_weir_over_m3;
double *weir_crest_volume;
double *stream;
double *stream_to_Sd;
double *cum_stream;
double *stream_Grp_in;
double *stream_Grp_loss;
double *cum_stream_Grp_loss;

// local variables
double *cum_soil_gw;
double *cum_Sd_gw;
double *cum_gw_flow;
double *cum_hru_condense;
double *cum_Sd_evap;
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
const double *channel_slope;
const double *side_slope;
const double *culvert_diam;
const double *culvert_water_Dmax;
const double *number_culverts;

const double *weir_crest;
const double *weir_coefficient;
const double *weir_mult;
const double *weir_b;
const double *lake_mult;
const double *lake_power;
const double *lake_p;
const double *lake_S;
const double *runoff_stream;
const double *stream_runoff;
const double *stream_Sd;
const double *Wetlands_scaling_factor;    // temporary modification

const long *culvert_type;
const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;
const long *soil_withdrawal;
const long **soil_withdrawal_Tables;

// variable inputs
const double *infil;
const double *snowinfil;
const double *meltrunoff; // frozen melt runoff
const double *runoff;     // liquid runoff
const double *hru_evap;
const double *SD;

// variable put inputs
double *hru_actet;      // [nhru]
double *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoil* klone(string name) const;
};