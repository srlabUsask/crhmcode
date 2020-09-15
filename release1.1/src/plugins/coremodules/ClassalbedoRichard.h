//created by Manishankar Mondal

#include "ClassModule.h"


class ClassalbedoRichard : public ClassModule {
public:

ClassalbedoRichard(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// local class

    double dt;

// declared variables
double *Albedo;

// put variables:

// get variables:

 const double *net_snow;
 const double *SWE;

const double *T0;

// declared parameters
  const double *Albedo_Bare;
  const double *Albedo_Snow;
  const double *a1;       // Albedo decay time constant for cold snow (s)
  const double *a2;       // Albedo decay time constant for melting snow (s)
  const double *amin;     // Minimum albedo for aged snow
  const double *amax;     // Maximum albedo for fresh snow
  const double *smin;     // Minimum snowfall to refresh snow albedo (mm)

void decl(void);
void init(void);
void run(void);

ClassalbedoRichard* klone(string name) const;
};