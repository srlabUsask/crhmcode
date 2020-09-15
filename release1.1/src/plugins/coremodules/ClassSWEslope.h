//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSWEslope : public ClassModule {
public:

ClassSWEslope(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, "glacier_h2o, snowmeltD") {};

// declared variables
double *SWE_in;
double *SWE_out;
double *cumSWE_in;
double *cumSWE_out;
double *Hd;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area; // [nhru]
const double *hru_GSL;    // [nhru]
const double *use_rho;    // [nhru]
const double *snow_density;    // [nhru]
const double *Hd_min;    // [nhru]
const long *order; // [nhru]
const double *distrib_SWEslope;
const double **distrib_hru;
const long *Disable_SWEslope; // [nhru]

// variable put inputs
double *SWE;

// variable inputs 
const double *rho;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSWEslope* klone(string name) const;
};