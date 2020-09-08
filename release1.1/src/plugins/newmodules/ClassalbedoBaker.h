//created by Manishankar Mondal

#include "ClassModule.h"


class ClassalbedoBaker : public ClassModule {
public:

ClassalbedoBaker(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  float *Albedo;
  float *Ab_t;

// get variables:


 const float *net_snow;
 const float *SWE;

// put variables:

// declared parameters
  const float *Albedo_Bare;
  const float *Albedo_Snow;
  const float *refresh;

void decl(void);
void init(void);
void run(void);

ClassalbedoBaker* klone(string name) const;
};