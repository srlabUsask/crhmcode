//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassSWEslope : public ClassModule {
public:

ClassSWEslope(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, "glacier_h2o, snowmeltD") {};

// declared variables
double *SWE_in{ NULL };
double *SWE_out{ NULL };
double *cumSWE_in{ NULL };
double *cumSWE_out{ NULL };
double *Hd{ NULL };

// declared parameters
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL }; // [nhru]
const double *hru_GSL{ NULL };    // [nhru]
const double *use_rho{ NULL };    // [nhru]
const double *snow_density{ NULL };    // [nhru]
const double *Hd_min{ NULL };    // [nhru]
const long *order{ NULL }; // [nhru]
const double *distrib_SWEslope{ NULL };
const double **distrib_hru{ NULL };
const long *Disable_SWEslope{ NULL }; // [nhru]

// variable put inputs
double *SWE{ NULL };

// variable inputs 
const double *rho{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSWEslope* klone(string name) const;
};