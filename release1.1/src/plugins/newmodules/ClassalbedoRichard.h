//created by Manishankar Mondal

#include "ClassModule.h"


class ClassalbedoRichard : public ClassModule {
public:

ClassalbedoRichard(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// local class

    float dt;

// declared variables
float *Albedo;

// put variables:

// get variables:

 const float *net_snow;
 const float *SWE;

const float *T0;

// declared parameters
  const float *Albedo_Bare;
  const float *Albedo_Snow;
  const float *a1;       // Albedo decay time constant for cold snow (s)
  const float *a2;       // Albedo decay time constant for melting snow (s)
  const float *amin;     // Minimum albedo for aged snow
  const float *amax;     // Maximum albedo for fresh snow
  const float *smin;     // Minimum snowfall to refresh snow albedo (mm)

void decl(void);
void init(void);
void run(void);

ClassalbedoRichard* klone(string name) const;
};