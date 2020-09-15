//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSetSoil : public ClassModule {
public:

ClassSetSoil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_lat;
const double *hru_elev;
const double *hru_GSL;
const double *hru_ASL;
const long *RUN_ID;
const long *RUN_START;
const long *RUN_END;

const double *soil_Depth;
const double *soil_Depth_rechr;
const double *Vol_h2o_content;
const double *soil_rechr_max;
const double *soil_rechr_init;
const double *soil_moist_max;
const double *soil_moist_init;

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