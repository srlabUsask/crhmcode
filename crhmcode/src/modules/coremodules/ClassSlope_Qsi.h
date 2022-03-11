//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class ClassSlope_Qsi : public ClassModule {
public:

ClassSlope_Qsi(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *QsiS_Var{ NULL };
double *QsiD_Var{ NULL };

// declared observations variable
const double *Qsi{ NULL };

// declared observations
double *QsiS{ NULL };
double *QsiD{ NULL };
double *QsiD_Obs{ NULL };

// variable inputs
const double *Qdro{ NULL };
const double *Qdfo{ NULL };
const double *Qdflat{ NULL };

void decl(void);
void init(void);
void run(void);

ClassSlope_Qsi* klone(string name) const;
};