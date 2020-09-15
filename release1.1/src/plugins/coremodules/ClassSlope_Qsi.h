//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSlope_Qsi : public ClassModule {
public:

ClassSlope_Qsi(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *QsiS_Var;
double *QsiD_Var;

// declared observations variable
const double *Qsi;

// declared observations
double *QsiS;
double *QsiD;
double *QsiD_Obs;

// variable inputs
const double *Qdro;
const double *Qdfo;
const double *Qdflat;

void decl(void);
void init(void);
void run(void);

ClassSlope_Qsi* klone(string name) const;
};