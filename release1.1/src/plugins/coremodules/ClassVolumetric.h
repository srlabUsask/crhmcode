//created by Manishankar Mondal

#include "ClassModule.h"

class ClassVolumetric : public ClassModule {
public:

ClassVolumetric(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, "soil_gw") {}; // setting PeerVar. Cannot be "STATE" var

// declared parameters
const double *soil_Depth{ NULL };
double *fallstat{ NULL };
const double *Si{ NULL };
const double *Si_correction{ NULL };
const double *soil_moist_max{ NULL };
const long *soil_type{ NULL };
const long *set_fallstat{ NULL };
//const long *fallstat_Si;

// declared variables
double *Volumetric{ NULL };
double *fallstat_V{ NULL };
double *Si_V{ NULL };

// variable inputs
const double *soil_moist{ NULL };

void decl(void);
void init(void);
void run(void);

ClassVolumetric* klone(string name) const;
};