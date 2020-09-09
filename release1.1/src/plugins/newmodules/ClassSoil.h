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
float *Sd;
float *gw;
float *soil_rechr;
float *soil_moist;
float *soil_gw;
float *Sd_gw;
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
float *infil_act;
float *cum_infil_act;
float *infil_act_D;

float *soil_runoff_stream;
float *weir_outflow;
float *weir_outflow_m3s;
float *weir_water_A;
float *weir_water_V;
float *weir_water_h;
float *weir_evap;
float *cum_weir_over_m3;
float *weir_crest_volume;
float *stream;
float *stream_to_Sd;
float *cum_stream;
float *stream_Grp_in;
float *stream_Grp_loss;
float *cum_stream_Grp_loss;

// local variables
float *cum_soil_gw;
float *cum_Sd_gw;
float *cum_gw_flow;
float *cum_hru_condense;
float *cum_Sd_evap;
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
const float *channel_slope;
const float *side_slope;
const float *culvert_diam;
const float *culvert_water_Dmax;
const float *number_culverts;

const float *weir_crest;
const float *weir_coefficient;
const float *weir_mult;
const float *weir_b;
const float *lake_mult;
const float *lake_power;
const float *lake_p;
const float *lake_S;
const float *runoff_stream;
const float *stream_runoff;
const float *stream_Sd;
const float *Wetlands_scaling_factor;    // temporary modification

const long *culvert_type;
const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;
const long *soil_withdrawal;
const long **soil_withdrawal_Tables;

// variable inputs
const float *infil;
const float *snowinfil;
const float *meltrunoff; // frozen melt runoff
const float *runoff;     // liquid runoff
const float *hru_evap;
const float *SD;

// variable put inputs
float *hru_actet;      // [nhru]
float *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoil* klone(string name) const;
};