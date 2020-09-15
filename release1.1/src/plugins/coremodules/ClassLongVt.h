//created by Manishankar Mondal

#include "ClassModule.h"


class ClassLongVt : public ClassModule {
public:

ClassLongVt(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , QsiD_Var, ") {};

// declared observation variables
  const double *Qsi;
  const double *QsiD;
  const double *Qli;

// declared observation functions
  double *QsiDavg;

// declared observations
  double *Qli_out;

// declared variables
  double *Qli_Var;
  double *QliVt_Var;
  double *tau;

// declared parameters
  const double *Vt;

//  const double *epsilon_clear;
  const double *epsilon_s;

// variable inputs
  const double *hru_t;
  const double *hru_ea;
  const double *hru_rh;
  const double *QdroDext;
  const double *QsiD_Var;

void decl(void);
void init(void);
void run(void);

ClassLongVt* klone(string name) const;
};