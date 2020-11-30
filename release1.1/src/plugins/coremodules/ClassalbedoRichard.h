//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"


class ClassalbedoRichard : public ClassModule {
public:

ClassalbedoRichard(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// local class

double dt {0.0};

// declared variables
double *Albedo { NULL };

// put variables:

// get variables:

 const double *net_snow { NULL };
 const double *SWE { NULL };

const double *T0 { NULL };

// declared parameters
  const double *Albedo_Bare { NULL };
  const double *Albedo_Snow { NULL };
  const double *a1 { NULL };       // Albedo decay time constant for cold snow (s)
  const double *a2 { NULL };       // Albedo decay time constant for melting snow (s)
  const double *amin { NULL };     // Minimum albedo for aged snow
  const double *amax { NULL };     // Maximum albedo for fresh snow
  const double *smin { NULL };     // Minimum snowfall to refresh snow albedo (mm)

void decl(void);
void init(void);
void run(void);

ClassalbedoRichard* klone(string name) const;
};