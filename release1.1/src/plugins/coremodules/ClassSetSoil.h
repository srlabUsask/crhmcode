//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSetSoil : public ClassModule {
public:

ClassSetSoil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_lat;
const float *hru_elev;
const float *hru_GSL;
const float *hru_ASL;
const long *RUN_ID;
const long *RUN_START;
const long *RUN_END;

const float *soil_Depth;
const float *soil_Depth_rechr;
const float *Vol_h2o_content;
const float *soil_rechr_max;
const float *soil_rechr_init;
const float *soil_moist_max;
const float *soil_moist_init;

const long *soil_type;
const long *soiltype_rechr;

TStringList *basin_name;
TStringList *INIT_STATE;
TStringList *hru_names;
TStringList *RapidAdvance_to;
TStringList *Loop_to;
TStringList *StateVars_to_Update;
TStringList *TraceVars;

// declared variables
//long *run_ID;

// variable inputs

void decl(void);
void init(void);

ClassSetSoil* klone(string name) const;
};