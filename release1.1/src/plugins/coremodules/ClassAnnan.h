//created by Manishankar Mondal

#include "ClassModule.h"

class ClassAnnan : public ClassModule {
public:

  double QsiDT, TauAT;

  ClassAnnan(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
//const double *SunAct;

// declared variables
double *hru_SunAct;
double *QsiA_Var;
double *QsiD_Var;
double *QsiS_Var;

// declared parameters
const double *krs;
const double *hru_elev;

// declared observations
double *QsiA;
double *QsiD;
double *QsiS;

// variable inputs
const double *QdflatE;
const double *QdflatD;
const double *QdroDext;
const double *Qdro;
const double *Qdfo;
const double *QdfoD;
const double *SunMax;
const double *hru_tmax;
const double *hru_tmin;

void decl(void);
void init(void);
void run(void);

ClassAnnan* klone(string name) const;
};