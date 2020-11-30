//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassK_Estimate : public ClassModule {
public:

ClassK_Estimate(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Ht_var{ NULL };
  double *v_L_upper{ NULL };
  double *v_L_lower{ NULL };
  double *v_V_sd{ NULL };
  double *v_V_soil{ NULL };
  double *v_L_gw{ NULL };
  double *rechr_ssr_K_V{ NULL };
  double *lower_ssr_K_V{ NULL };
  double *Sd_ssr_K_V{ NULL };
  double *Sd_gw_K_V{ NULL };
  double *soil_gw_K_V{ NULL };
  double *gw_K_V{ NULL };
  double *Dts_organic_runoff_K_V{ NULL };
  double *Dts_snow_runoff_K_V{ NULL };
  double *Ks_snow{ NULL };
  double *v_L_organic{ NULL };
  double *v_L_snow{ NULL };

// declared observation variables

// declared parameters
  const double *Ks_lower{ NULL };
  const double *Ks_upper{ NULL };
  const double *Ks_gw{ NULL };
  const double *hru_GSL{ NULL };
//  const double *porosity{ NULL };
  const double *PSD{ NULL };
  const double *soil_rechr_max{ NULL };
  const double *soil_moist_max{ NULL };
//  const double *gw_max{ NULL };

  const long *inhibit_evap{ NULL };

// declared parameters
  const double *d_g{ NULL };
  const double *Ks_organic{ NULL };
  const double *PSD_org{ NULL };
  const double *S_I{ NULL };
  const long  *Inhibit_K_set{ NULL };

// put parameters

  double *rechr_ssr_K{ NULL };
  double *lower_ssr_K{ NULL };
  double *Sd_ssr_K{ NULL };
  double *Sd_gw_K{ NULL };
  double *soil_gw_K{ NULL };
  double *gw_K{ NULL };
  double *Dts_organic_runoff_K{ NULL };
  double *Dts_snow_runoff_K{ NULL };

// put variables:

double *soil_rechr{ NULL };
double *soil_moist{ NULL };
double *gw{ NULL };

// get variables:

const double *Dts{ NULL };
const double *Dts_max{ NULL };
const double *rho{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassK_Estimate* klone(string name) const;
};