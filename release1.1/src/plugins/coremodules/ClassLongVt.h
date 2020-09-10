//created by Manishankar Mondal

#include "ClassModule.h"


class ClassLongVt : public ClassModule {
public:

ClassLongVt(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , QsiD_Var, ") {};

// declared observation variables
  const float *Qsi;
  const float *QsiD;
  const float *Qli;

// declared observation functions
  float *QsiDavg;

// declared observations
  float *Qli_out;

// declared variables
  float *Qli_Var;
  float *QliVt_Var;
  float *tau;

// declared parameters
  const float *Vt;

//  const float *epsilon_clear;
  const float *epsilon_s;

// variable inputs
  const float *hru_t;
  const float *hru_ea;
  const float *hru_rh;
  const float *QdroDext;
  const float *QsiD_Var;

void decl(void);
void init(void);
void run(void);

ClassLongVt* klone(string name) const;
};