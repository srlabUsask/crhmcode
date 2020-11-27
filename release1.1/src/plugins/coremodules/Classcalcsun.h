//created by Manishankar Mondal

#include "ClassModule.h"

class Classcalcsun : public ClassModule {
public:

Classcalcsun(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , , QsiD_Var") {};

// declared observation variables
const double *Qsi { NULL };
const double *QsiD_Obs { NULL };
const double *SunAct { NULL };

// declared observation functions
double *Qsitot { NULL };

// declared variables
double *hru_SunAct { NULL };

// declared parameters

// variable inputs
const double *QdflatD { NULL };
const double *QdfoD { NULL };
const double *SunMax { NULL };
const double *QsiD_Var { NULL };

void decl(void);
void init(void);
void run(void);

Classcalcsun* klone(string name) const;
};