//created by Manishankar Mondal

#include "ClassModule.h"

class Classcontribution : public ClassModule {
public:

Classcontribution(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long soil_runoffDiv;

// declared variables
double *contrib_area;
double *pre_contrib_area;
double *connected;
long  *N_connected;
long  *connectedTo;
double *Results;
double **Results_lay;
double *distrib_sum;
const double *distrib_Basin;
double *soil_runoff_Buf; // buffered

// declared parameters
const double *basin_area;
const double *hru_area;
const double *Sdmax;
const double *distrib;
const double **distrib_hru;

// variable inputs
const double *soil_runoff;
const double *Sd;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcontribution* klone(string name) const;
};