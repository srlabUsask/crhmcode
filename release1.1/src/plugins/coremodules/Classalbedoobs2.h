//created by Manishankar Mondal

#include "ClassModule.h"

class Classalbedoobs2 : public ClassModule {
public:

Classalbedoobs2(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const float *Albedo_obs;      // interval data

// declared variables
float *Albedo;
float *net_snowD;  // daily value sum(newsnow)
long *meltflag;
long *winter;
long  *newsnowcnt;

// declared parameters
const float *Albedo_bare;
const float *Albedo_snow;
const float *hru_lat;

// variable inputs
const float *hru_tmax;
const float *hru_tmin;
const float *QdroD;
const float *SWE;
const float *net_snow;
const long  *hru_newsnow;

void decl(void);
void init(void);
void run(void);

void albedo(long jday, float Qnc);

Classalbedoobs2* klone(string name) const;
};