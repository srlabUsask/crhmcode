//created by Manishankar Mondal

#include "ClassModule.h"

class Classcontribution : public ClassModule {
public:

Classcontribution(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long soil_runoffDiv {0};

// declared variables
double *contrib_area { NULL };
double *pre_contrib_area { NULL };
double *connected { NULL };
long  *N_connected { NULL };
long  *connectedTo { NULL };
double *Results { NULL };
double **Results_lay { NULL };
double *distrib_sum { NULL };
const double *distrib_Basin { NULL };
double *soil_runoff_Buf { NULL }; // buffered

// declared parameters
const double *basin_area { NULL };
const double *hru_area { NULL };
const double *Sdmax { NULL };
const double *distrib { NULL };
const double **distrib_hru { NULL };

// variable inputs
const double *soil_runoff { NULL };
const double *Sd { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcontribution* klone(string name) const;
};