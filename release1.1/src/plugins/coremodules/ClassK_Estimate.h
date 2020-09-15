//created by Manishankar Mondal

#include "ClassModule.h"

class ClassK_Estimate : public ClassModule {
public:

ClassK_Estimate(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Ht_var;
  double *v_L_upper;
  double *v_L_lower;
  double *v_V_sd;
  double *v_V_soil;
  double *v_L_gw;
  double *rechr_ssr_K_V;
  double *lower_ssr_K_V;
  double *Sd_ssr_K_V;
  double *Sd_gw_K_V;
  double *soil_gw_K_V;
  double *gw_K_V;
  double *Dts_organic_runoff_K_V;
  double *Dts_snow_runoff_K_V;
  double *Ks_snow;
  double *v_L_organic;
  double *v_L_snow;

// declared observation variables

// declared parameters
  const double *Ks_lower;
  const double *Ks_upper;
  const double *Ks_gw;
  const double *hru_GSL;
//  const double *porosity;
  const double *PSD;
  const double *soil_rechr_max;
  const double *soil_moist_max;
//  const double *gw_max;

  const long *inhibit_evap;

// declared parameters
  const double *d_g;
  const double *Ks_organic;
  const double *PSD_org;
  const double *S_I;
  const long  *Inhibit_K_set;

// put parameters

  double *rechr_ssr_K;
  double *lower_ssr_K;
  double *Sd_ssr_K;
  double *Sd_gw_K;
  double *soil_gw_K;
  double *gw_K;
  double *Dts_organic_runoff_K;
  double *Dts_snow_runoff_K;

// put variables:

double *soil_rechr;
double *soil_moist;
double *gw;

// get variables:

const double *Dts;
const double *Dts_max;
const double *rho;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassK_Estimate* klone(string name) const;
};