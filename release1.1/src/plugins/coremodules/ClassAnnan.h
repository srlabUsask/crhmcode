//created by Manishankar Mondal

#include "ClassModule.h"

class ClassAnnan : public ClassModule {
public:

  float QsiDT, TauAT;

  ClassAnnan(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
//const float *SunAct;

// declared variables
float *hru_SunAct;
float *QsiA_Var;
float *QsiD_Var;
float *QsiS_Var;

// declared parameters
const float *krs;
const float *hru_elev;

// declared observations
float *QsiA;
float *QsiD;
float *QsiS;

// variable inputs
const float *QdflatE;
const float *QdflatD;
const float *QdroDext;
const float *Qdro;
const float *Qdfo;
const float *QdfoD;
const float *SunMax;
const float *hru_tmax;
const float *hru_tmin;

void decl(void);
void init(void);
void run(void);

ClassAnnan* klone(string name) const;
};