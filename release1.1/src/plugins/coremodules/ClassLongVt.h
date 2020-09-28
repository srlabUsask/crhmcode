//created by Manishankar Mondal

#include "ClassModule.h"


class ClassLongVt : public ClassModule {
public:

ClassLongVt(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , QsiD_Var, ") {};

// declared observation variables
  const double *Qsi{ NULL };
  const double *QsiD{ NULL };
  const double *Qli{ NULL };

// declared observation functions
  double *QsiDavg{ NULL };

// declared observations
  double *Qli_out{ NULL };

// declared variables
  double *Qli_Var{ NULL };
  double *QliVt_Var{ NULL };
  double *tau{ NULL };

// declared parameters
  const double *Vt{ NULL };

//  const double *epsilon_clear;
  const double *epsilon_s{ NULL };

// variable inputs
  const double *hru_t{ NULL };
  const double *hru_ea{ NULL };
  const double *hru_rh{ NULL };
  const double *QdroDext{ NULL };
  const double *QsiD_Var{ NULL };

void decl(void);
void init(void);
void run(void);

ClassLongVt* klone(string name) const;
};