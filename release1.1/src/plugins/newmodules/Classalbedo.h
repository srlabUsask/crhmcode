//created by Manishankar Mondal

#include "ClassModule.h"

class Classalbedo : public ClassModule {
public:

Classalbedo(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

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

Classalbedo* klone(string name) const;
};