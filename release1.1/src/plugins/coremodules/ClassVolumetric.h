//created by Manishankar Mondal

#include "ClassModule.h"

class ClassVolumetric : public ClassModule {
public:

ClassVolumetric(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, "soil_gw") {}; // setting PeerVar. Cannot be "STATE" var

// declared parameters
const double *soil_Depth;
double *fallstat;
const double *Si;
const double *Si_correction;
const double *soil_moist_max;
const long *soil_type;
const long *set_fallstat;
//const long *fallstat_Si;

// declared variables
double *Volumetric;
double *fallstat_V;
double *Si_V;

// variable inputs
const double *soil_moist;

void decl(void);
void init(void);
void run(void);

ClassVolumetric* klone(string name) const;
};