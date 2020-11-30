//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class Classtsurface : public ClassModule {
public:

Classtsurface(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_tsf{ NULL };
double *hru_tsf_D{ NULL };
double *hru_tsf_acc{ NULL };
double *n_factor{ NULL };
double *n_factor_T{ NULL };
double *Zdt_last{ NULL };
double *SWE_tc{ NULL };
double *SWE_density{ NULL };
double *hru_t_D{ NULL };
double *hru_T_s_D{ NULL };
double *hru_t_acc{ NULL };
double *hru_T_s_acc{ NULL };

// put inputs
double *Zdt{ NULL }; // not used as put. Allows Classtsurface to load before ClassXG

// declared parameters
const double *W_a{ NULL }; // Williams
const double *W_b{ NULL };
const double *W_c{ NULL };
const double *W_d{ NULL };

const double *n_factor_a{ NULL }; // Woo
const double *n_factor_b{ NULL };
const double *n_factor_c{ NULL };

// variable inputs
const double *SWE{ NULL };
const double *hru_t{ NULL };
const double *netD{ NULL };
const double *z_s{ NULL };
const double *rho{ NULL };
const double *T_s{ NULL };
const double *G{ NULL };
const double *tmin{ NULL };
const double *snowdepth{ NULL };
const double *xx{ NULL };

void decl(void);
void init(void);
void run(void);

Classtsurface* klone(string name) const;
};