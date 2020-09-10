//created by Manishankar Mondal

#include "ClassModule.h"

class ClassalbedoWinstral : public ClassModule {
public:

ClassalbedoWinstral(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  float *Albedo;
  float *irdalb;
  float *vdalb;
//  float *balbx;
  float *Ab_t;

// get variables:

  const float *net_snow;
  const float *SWE;

// put variables:

// declared parameters
  const float *maxdecay;
  const float *power;
  const float *decay_period;
  const float *refresh;
  const float *Albedo_Bare;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassalbedoWinstral* klone(string name) const;
};