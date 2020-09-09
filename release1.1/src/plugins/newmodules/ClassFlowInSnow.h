//created by Manishankar Mondal

#include "ClassModule.h"

class ClassFlowInSnow : public ClassModule {
public:

ClassFlowInSnow(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module; // used to call preser for simple projects

// declared variables
float *Ksat_snow;
float *K_snow;
float *u_down;
float *K_down;
float *K_slope;
float *Meltrunoff_K;
float *In_storage;
float *runKstorage_var;

// get variables:
const float *rho;
const float *h2o_sat;
const float *T_s_l;
const float *z_s;

// put variables
float  *runKstorage;

// declared parameters
const float *S_I;
const float *d_g;
const float *t_inhibit_flow;
const float *runKstorage_winter;
const float *runKstorage_summer;
const float *Sr;
const float  *hru_GSL;
const float  *route_L;
const long  *inhibit_MeltRunoff_Kstorage;

void decl(void);
void init(void);
void run(void);

ClassFlowInSnow* klone(string name) const;
};