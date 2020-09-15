//created by Manishankar Mondal

#include "ClassModule.h"

class Classwinter_meltflag : public ClassModule {
public:

Classwinter_meltflag(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
long *meltflag;
long *winter;

// declared parameters
const float *hru_lat;

// variable inputs
const float *hru_tmax;
const float *hru_tmin;
const float *QdroD;
const float *SWE;
const long  *hru_newsnow;
const float *Albedo;

void decl(void);
void init(void);
void run(void);

Classwinter_meltflag* klone(string name) const;
};