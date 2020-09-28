//created by Manishankar Mondal

#include "ClassModule.h"

class ClassFlowInSnow : public ClassModule {
public:

ClassFlowInSnow(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module { NULL }; // used to call preser for simple projects

// declared variables
double* Ksat_snow {NULL};
double *K_snow { NULL };
double *u_down { NULL };
double *K_down { NULL };
double *K_slope { NULL };
double *Meltrunoff_K { NULL };
double *In_storage { NULL };
double *runKstorage_var { NULL };

// get variables:
const double *rho { NULL };
const double *h2o_sat { NULL };
const double *T_s_l { NULL };
const double *z_s { NULL };

// put variables
double  *runKstorage { NULL };

// declared parameters
const double *S_I { NULL };
const double *d_g { NULL };
const double *t_inhibit_flow { NULL };
const double *runKstorage_winter { NULL };
const double *runKstorage_summer { NULL };
const double *Sr { NULL };
const double  *hru_GSL { NULL };
const double  *route_L { NULL };
const long  *inhibit_MeltRunoff_Kstorage { NULL };

void decl(void);
void init(void);
void run(void);

ClassFlowInSnow* klone(string name) const;
};