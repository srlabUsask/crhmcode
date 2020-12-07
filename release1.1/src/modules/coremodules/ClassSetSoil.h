//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassSetSoil : public ClassModule {
public:

ClassSetSoil(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *hru_lat{ NULL };
const double *hru_elev{ NULL };
const double *hru_GSL{ NULL };
const double *hru_ASL{ NULL };
const long *RUN_ID{ NULL };
const long *RUN_START{ NULL };
const long *RUN_END{ NULL };

const double *soil_Depth{ NULL };
const double *soil_Depth_rechr{ NULL };
const double *Vol_h2o_content{ NULL };
const double *soil_rechr_max{ NULL };
const double *soil_rechr_init{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_moist_init{ NULL };

const long *soil_type{ NULL };
const long *soiltype_rechr{ NULL };

TStringList *basin_name{ NULL };
TStringList *INIT_STATE{ NULL };
TStringList *hru_names{ NULL };
TStringList *RapidAdvance_to{ NULL };
TStringList *Loop_to{ NULL };
TStringList *StateVars_to_Update{ NULL };
TStringList *TraceVars{ NULL };

// declared variables
//long *run_ID;

// variable inputs

void decl(void);
void init(void);

ClassSetSoil* klone(string name) const;
};