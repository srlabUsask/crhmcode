//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class Class_z_s_rho : public ClassModule {
public:

Class_z_s_rho(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double*  z_s{ NULL };            // total snowcover thickness (m)
  double*  rho{ NULL };            // average snowcover density (kg/m^3)

// variable inputs
const double *SWE{ NULL };

void decl(void);
void init(void);
void run(void);

Class_z_s_rho* klone(string name) const;
};