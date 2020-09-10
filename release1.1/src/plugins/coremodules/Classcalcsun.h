//created by Manishankar Mondal

#include "ClassModule.h"

class Classcalcsun : public ClassModule {
public:

Classcalcsun(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , , QsiD_Var") {};

// declared observation variables
const float *Qsi;
const float *QsiD_Obs;
const float *SunAct;

// declared observation functions
float *Qsitot;

// declared variables
float *hru_SunAct;

// declared parameters

// variable inputs
const float *QdflatD;
const float *QdfoD;
const float *SunMax;
const float *QsiD_Var;

void decl(void);
void init(void);
void run(void);

Classcalcsun* klone(string name) const;
};