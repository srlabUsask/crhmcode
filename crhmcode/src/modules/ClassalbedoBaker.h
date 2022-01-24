//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"


class ClassalbedoBaker : public ClassModule {
public:

ClassalbedoBaker(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Albedo { NULL };
  double *Ab_t { NULL };

// get variables:


 const double *net_snow { NULL };
 const double *SWE { NULL };

// put variables:

// declared parameters
  const double *Albedo_Bare { NULL };
  const double *Albedo_Snow { NULL };
  const double *refresh { NULL };

void decl(void);
void init(void);
void run(void);

ClassalbedoBaker* klone(string name) const;
};