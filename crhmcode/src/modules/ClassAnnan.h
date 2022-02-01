//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassAnnan : public ClassModule {
public:

	double QsiDT {0.0}, TauAT {0.0};

  ClassAnnan(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
//const double *SunAct;

// declared variables
double *hru_SunAct { NULL };
double *QsiA_Var { NULL };
double *QsiD_Var { NULL };
double *QsiS_Var { NULL };

// declared parameters
const double *krs { NULL };
const double *hru_elev { NULL };

// declared observations
double *QsiA { NULL };
double *QsiD { NULL };
double *QsiS { NULL };

// variable inputs
const double *QdflatE { NULL };
const double *QdflatD { NULL };
const double *QdroDext { NULL };
const double *Qdro { NULL };
const double *Qdfo { NULL };
const double *QdfoD { NULL };
const double *SunMax { NULL };
const double *hru_tmax { NULL };
const double *hru_tmin { NULL };

void decl(void);
void init(void);
void run(void);

ClassAnnan* klone(string name) const;
};
