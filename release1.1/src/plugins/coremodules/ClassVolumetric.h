//created by Manishankar Mondal

#include "ClassModule.h"

class ClassVolumetric : public ClassModule {
public:

ClassVolumetric(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, "soil_gw") {}; // setting PeerVar. Cannot be "STATE" var

// declared parameters
const float *soil_Depth;
float *fallstat;
const float *Si;
const float *Si_correction;
const float *soil_moist_max;
const long *soil_type;
const long *set_fallstat;
//const long *fallstat_Si;

// declared variables
float *Volumetric;
float *fallstat_V;
float *Si_V;

// variable inputs
const float *soil_moist;

void decl(void);
void init(void);
void run(void);

ClassVolumetric* klone(string name) const;
};