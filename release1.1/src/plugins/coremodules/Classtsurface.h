//created by Manishankar Mondal

#include "ClassModule.h"

class Classtsurface : public ClassModule {
public:

Classtsurface(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_tsf;
double *hru_tsf_D;
double *hru_tsf_acc;
double *n_factor;
double *n_factor_T;
double *Zdt_last;
double *SWE_tc;
double *SWE_density;
double *hru_t_D;
double *hru_T_s_D;
double *hru_t_acc;
double *hru_T_s_acc;

// put inputs
double *Zdt; // not used as put. Allows Classtsurface to load before ClassXG

// declared parameters
const double *W_a; // Williams
const double *W_b;
const double *W_c;
const double *W_d;

const double *n_factor_a; // Woo
const double *n_factor_b;
const double *n_factor_c;

// variable inputs
const double *SWE;
const double *hru_t;
const double *netD;
const double *z_s;
const double *rho;
const double *T_s;
const double *G;
const double *tmin;
const double *snowdepth;
const double *xx;

void decl(void);
void init(void);
void run(void);

Classtsurface* klone(string name) const;
};