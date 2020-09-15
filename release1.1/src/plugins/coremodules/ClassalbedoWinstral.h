//created by Manishankar Mondal

#include "ClassModule.h"

class ClassalbedoWinstral : public ClassModule {
public:

ClassalbedoWinstral(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Albedo;
  double *irdalb;
  double *vdalb;
//  double *balbx;
  double *Ab_t;

// get variables:

  const double *net_snow;
  const double *SWE;

// put variables:

// declared parameters
  const double *maxdecay;
  const double *power;
  const double *decay_period;
  const double *refresh;
  const double *Albedo_Bare;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassalbedoWinstral* klone(string name) const;
};