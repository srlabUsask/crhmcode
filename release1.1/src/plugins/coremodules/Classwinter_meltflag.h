//created by Manishankar Mondal

#include "ClassModule.h"

class Classwinter_meltflag : public ClassModule {
public:

Classwinter_meltflag(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
long *meltflag;
long *winter;

// declared parameters
const double *hru_lat;

// variable inputs
const double *hru_tmax;
const double *hru_tmin;
const double *QdroD;
const double *SWE;
const long  *hru_newsnow;
const double *Albedo;

void decl(void);
void init(void);
void run(void);

Classwinter_meltflag* klone(string name) const;
};