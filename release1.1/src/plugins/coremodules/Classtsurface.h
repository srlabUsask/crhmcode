//created by Manishankar Mondal

#include "ClassModule.h"

class Classtsurface : public ClassModule {
public:

Classtsurface(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_tsf;
float *hru_tsf_D;
float *hru_tsf_acc;
float *n_factor;
float *n_factor_T;
float *Zdt_last;
float *SWE_tc;
float *SWE_density;
float *hru_t_D;
float *hru_T_s_D;
float *hru_t_acc;
float *hru_T_s_acc;

// put inputs
float *Zdt; // not used as put. Allows Classtsurface to load before ClassXG

// declared parameters
const float *W_a; // Williams
const float *W_b;
const float *W_c;
const float *W_d;

const float *n_factor_a; // Woo
const float *n_factor_b;
const float *n_factor_c;

// variable inputs
const float *SWE;
const float *hru_t;
const float *netD;
const float *z_s;
const float *rho;
const float *T_s;
const float *G;
const float *tmin;
const float *snowdepth;
const float *xx;

void decl(void);
void init(void);
void run(void);

Classtsurface* klone(string name) const;
};