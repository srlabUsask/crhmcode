//created by Manishankar Mondal

#include "ClassModule.h"

class Classwalmsley_wind : public ClassModule {
public:
Classwalmsley_wind(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_Uadjust{ NULL };
double *hru_Uchange{ NULL };
double *WR{ NULL };

// declared parameters
const double *Zwind{ NULL };
const double *Ax{ NULL };
const double *Bx{ NULL };
const double *L{ NULL };
const double *Walmsley_Ht{ NULL };

// varaible inputs
const double *hru_u{ NULL };

void decl(void);
void init(void);
void run(void);

Classwalmsley_wind* klone(string name) const;
};