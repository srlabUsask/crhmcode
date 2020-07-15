//created by Manishankar Mondal

#include "ClassModule.h"

class Classbasin : public ClassModule {
public:

Classbasin(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters
const long *RUN_ID;
const long *RUN_START;
const long *RUN_END;

const float *Meyer_B;
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_lat;
const float *hru_elev;
const float *hru_GSL;
const float *hru_ASL;

TStringList *basin_name;
TStringList *INIT_STATE;
TStringList *hru_names;
TStringList *RapidAdvance_to;
TStringList *Loop_to;
TStringList *StateVars_to_Update;
TStringList *TraceVars;

//declared variables
long *run_ID;

void decl(void);
void init(void);

Classbasin* klone(string name) const;
};