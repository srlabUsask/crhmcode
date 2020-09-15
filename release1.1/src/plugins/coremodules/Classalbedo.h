//created by Manishankar Mondal

#include "ClassModule.h"

class Classalbedo : public ClassModule {
public:

Classalbedo(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Albedo;
double *net_snowD;  // daily value sum(newsnow)
long *meltflag;
long *winter;
long  *newsnowcnt;

// declared parameters
const double *Albedo_bare;
const double *Albedo_snow;
const double *hru_lat;

// variable inputs
const double *hru_tmax;
const double *hru_tmin;
const double *QdroD;
const double *SWE;
const double *net_snow;
const long  *hru_newsnow;

void decl(void);
void init(void);
void run(void);

Classalbedo* klone(string name) const;
};