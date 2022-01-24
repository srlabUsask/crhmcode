//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassVolumetric : public ClassModule {
public:

ClassVolumetric(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1001, "soil_gw") {}; // setting PeerVar. Cannot be "STATE" var

// declared parameters
const double *soil_Depth{ NULL };
const double *Si_correction{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_rechr_max{ NULL };
const long *soil_type{ NULL };
const long *set_fallstat{ NULL };
const long* Volumetric_option{ NULL };


// declared variables
double *Volumetric{ NULL };
double *Volumetric_rechr{ NULL };
double *fallstat_V{ NULL };
double *Si_V{ NULL };
double *fallstat{ NULL };
double *Si{ NULL };

// variable inputs
const double *soil_moist{ NULL };
const double *soil_rechr{ NULL };

void decl(void);
void init(void);
void run(void);

ClassVolumetric* klone(string name) const;
};