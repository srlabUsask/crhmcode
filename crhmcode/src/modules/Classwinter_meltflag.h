//created by Manishankar Mondal

#include "../core/ClassModule.h"

class Classwinter_meltflag : public ClassModule {
public:

Classwinter_meltflag(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
long *meltflag{ NULL };
long *winter{ NULL };

// declared parameters
const double *hru_lat{ NULL };

// variable inputs
const double *hru_tmax{ NULL };
const double *hru_tmin{ NULL };
const double *QdroD{ NULL };
const double *SWE{ NULL };
const long  *hru_newsnow{ NULL };
const double *Albedo{ NULL };

void decl(void);
void init(void);
void run(void);

Classwinter_meltflag* klone(string name) const;
};
