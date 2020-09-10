//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSWEslope : public ClassModule {
public:

ClassSWEslope(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, "glacier_h2o, snowmeltD") {};

// declared variables
float *SWE_in;
float *SWE_out;
float *cumSWE_in;
float *cumSWE_out;
float *Hd;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area; // [nhru]
const float *hru_GSL;    // [nhru]
const float *use_rho;    // [nhru]
const float *snow_density;    // [nhru]
const float *Hd_min;    // [nhru]
const long *order; // [nhru]
const float *distrib_SWEslope;
const float **distrib_hru;
const long *Disable_SWEslope; // [nhru]

// variable put inputs
float *SWE;

// variable inputs 
const float *rho;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSWEslope* klone(string name) const;
};