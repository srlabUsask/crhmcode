//created by Manishankar Mondal

#include "ClassModule.h"

class Classalbedoobs2 : public ClassModule {
public:

Classalbedoobs2(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const double *Albedo_obs;      // interval data

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

void albedo(long jday, double Qnc);

Classalbedoobs2* klone(string name) const;
};