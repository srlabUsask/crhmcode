//created by Manishankar Mondal

#include "ClassModule.h"

class Classbasin : public ClassModule {
public:

Classbasin(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters
const long *RUN_ID;
const long *RUN_START;
const long *RUN_END;

const double *Meyer_B;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_lat;
const double *hru_elev;
const double *hru_GSL;
const double *hru_ASL;

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