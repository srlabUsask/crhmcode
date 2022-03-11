//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class Classalbedoobs2 : public ClassModule {
public:

Classalbedoobs2(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const double *Albedo_obs { NULL };      // interval data

// declared variables
double *Albedo { NULL };
double *net_snowD { NULL };  // daily value sum(newsnow)
long *meltflag { NULL };
long *winter { NULL };
long  *newsnowcnt { NULL };

// declared parameters
const double *Albedo_bare { NULL };
const double *Albedo_snow { NULL };
const double *hru_lat { NULL };

// variable inputs
const double *hru_tmax { NULL };
const double *hru_tmin { NULL };
const double *QdroD { NULL };
const double *SWE { NULL };
const double *net_snow { NULL };
const long  *hru_newsnow { NULL };

void decl(void);
void init(void);
void run(void);

void albedo(long jday, double Qnc);

Classalbedoobs2* klone(string name) const;
};