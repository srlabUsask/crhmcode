//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSlope_Qsi : public ClassModule {
public:

ClassSlope_Qsi(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *QsiS_Var;
float *QsiD_Var;

// declared observations variable
const float *Qsi;

// declared observations
float *QsiS;
float *QsiD;
float *QsiD_Obs;

// variable inputs
const float *Qdro;
const float *Qdfo;
const float *Qdflat;

void decl(void);
void init(void);
void run(void);

ClassSlope_Qsi* klone(string name) const;
};