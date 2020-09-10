//created by Manishankar Mondal

#include "ClassModule.h"

class Classcontribution : public ClassModule {
public:

Classcontribution(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long soil_runoffDiv;

// declared variables
float *contrib_area;
float *pre_contrib_area;
float *connected;
long  *N_connected;
long  *connectedTo;
float *Results;
float **Results_lay;
float *distrib_sum;
const float *distrib_Basin;
float *soil_runoff_Buf; // buffered

// declared parameters
const float *basin_area;
const float *hru_area;
const float *Sdmax;
const float *distrib;
const float **distrib_hru;

// variable inputs
const float *soil_runoff;
const float *Sd;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcontribution* klone(string name) const;
};