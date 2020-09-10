//created by Manishankar Mondal

#include "ClassModule.h"

class ClassK_Estimate : public ClassModule {
public:

ClassK_Estimate(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  float *Ht_var;
  float *v_L_upper;
  float *v_L_lower;
  float *v_V_sd;
  float *v_V_soil;
  float *v_L_gw;
  float *rechr_ssr_K_V;
  float *lower_ssr_K_V;
  float *Sd_ssr_K_V;
  float *Sd_gw_K_V;
  float *soil_gw_K_V;
  float *gw_K_V;
  float *Dts_organic_runoff_K_V;
  float *Dts_snow_runoff_K_V;
  float *Ks_snow;
  float *v_L_organic;
  float *v_L_snow;

// declared observation variables

// declared parameters
  const float *Ks_lower;
  const float *Ks_upper;
  const float *Ks_gw;
  const float *hru_GSL;
//  const float *porosity;
  const float *PSD;
  const float *soil_rechr_max;
  const float *soil_moist_max;
//  const float *gw_max;

  const long *inhibit_evap;

// declared parameters
  const float *d_g;
  const float *Ks_organic;
  const float *PSD_org;
  const float *S_I;
  const long  *Inhibit_K_set;

// put parameters

  float *rechr_ssr_K;
  float *lower_ssr_K;
  float *Sd_ssr_K;
  float *Sd_gw_K;
  float *soil_gw_K;
  float *gw_K;
  float *Dts_organic_runoff_K;
  float *Dts_snow_runoff_K;

// put variables:

float *soil_rechr;
float *soil_moist;
float *gw;

// get variables:

const float *Dts;
const float *Dts_max;
const float *rho;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassK_Estimate* klone(string name) const;
};