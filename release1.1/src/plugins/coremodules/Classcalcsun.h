//created by Manishankar Mondal

#include "ClassModule.h"

class Classcalcsun : public ClassModule {
public:

Classcalcsun(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , , QsiD_Var") {};

// declared observation variables
const double *Qsi;
const double *QsiD_Obs;
const double *SunAct;

// declared observation functions
double *Qsitot;

// declared variables
double *hru_SunAct;

// declared parameters

// variable inputs
const double *QdflatD;
const double *QdfoD;
const double *SunMax;
const double *QsiD_Var;

void decl(void);
void init(void);
void run(void);

Classcalcsun* klone(string name) const;
};