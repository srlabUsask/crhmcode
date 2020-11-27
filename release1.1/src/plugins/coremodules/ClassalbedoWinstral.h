//created by Manishankar Mondal

#include "ClassModule.h"

class ClassalbedoWinstral : public ClassModule {
public:

ClassalbedoWinstral(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Albedo { NULL };
  double *irdalb { NULL };
  double *vdalb { NULL };
//  double *balbx;
  double *Ab_t { NULL };

// get variables:

  const double *net_snow { NULL };
  const double *SWE { NULL };

// put variables:

// declared parameters
  const double *maxdecay { NULL };
  const double *power { NULL };
  const double *decay_period { NULL };
  const double *refresh { NULL };
  const double *Albedo_Bare { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassalbedoWinstral* klone(string name) const;
};