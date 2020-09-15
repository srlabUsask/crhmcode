//created by Manishankar Mondal

#include "ClassModule.h"


class ClassalbedoBaker : public ClassModule {
public:

ClassalbedoBaker(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Albedo;
  double *Ab_t;

// get variables:


 const double *net_snow;
 const double *SWE;

// put variables:

// declared parameters
  const double *Albedo_Bare;
  const double *Albedo_Snow;
  const double *refresh;

void decl(void);
void init(void);
void run(void);

ClassalbedoBaker* klone(string name) const;
};