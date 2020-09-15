//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSoilDS : public ClassModule {
public:

ClassSoilDS(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;

// declared observation variables

// declared variables
double *Sd;
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
double *Dts;
double *Dts_max;

// local variables
double *cum_soil_gw;
double *cum_gw_flow;
double *cum_hru_condense;
double *soil_moist_Init;
double *soil_rechr_Init;
double *Sd_Init;
double *gw_Init;
double *SWE_Init;
double *Dts_runoff_K;

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
const double *Dts_snow_max;
const double *Dts_organic_max;
const double *Dts_snow_init;
const double *Dts_snow_runoff_K;
const double *Dts_organic_runoff_K;
const double *Dts_organic_init;
const long *soil_withdrawal;
const long **soil_withdrawal_Tables;

const long *culvert_type;
const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;

// variable inputs
const double *infil;
const double *snowinfil;
const double *meltrunoff; // frozen melt runoff
const double *runoff;     // liquid runoff
const double *hru_evap;

// variable put inputs
double *hru_actet;      // [nhru]
double *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoilDS* klone(string name) const;
};