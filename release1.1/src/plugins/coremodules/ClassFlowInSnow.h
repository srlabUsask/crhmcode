//created by Manishankar Mondal

#include "ClassModule.h"

class ClassFlowInSnow : public ClassModule {
public:

ClassFlowInSnow(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module; // used to call preser for simple projects

// declared variables
double *Ksat_snow;
double *K_snow;
double *u_down;
double *K_down;
double *K_slope;
double *Meltrunoff_K;
double *In_storage;
double *runKstorage_var;

// get variables:
const double *rho;
const double *h2o_sat;
const double *T_s_l;
const double *z_s;

// put variables
double  *runKstorage;

// declared parameters
const double *S_I;
const double *d_g;
const double *t_inhibit_flow;
const double *runKstorage_winter;
const double *runKstorage_summer;
const double *Sr;
const double  *hru_GSL;
const double  *route_L;
const long  *inhibit_MeltRunoff_Kstorage;

void decl(void);
void init(void);
void run(void);

ClassFlowInSnow* klone(string name) const;
};