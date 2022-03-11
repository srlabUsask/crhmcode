//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class Classbasin : public ClassModule {
public:

Classbasin(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters
const long *RUN_ID { NULL };
const long *RUN_START { NULL };
const long *RUN_END { NULL };

const double *Meyer_B { NULL };
const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *hru_lat { NULL };
const double *hru_elev { NULL };
const double* hru_GSL { NULL };
const double *hru_ASL { NULL };

TStringList *basin_name { NULL };
TStringList *INIT_STATE { NULL };
TStringList *hru_names { NULL };
TStringList *RapidAdvance_to { NULL };
TStringList *Loop_to { NULL };
TStringList *StateVars_to_Update { NULL };
TStringList *TraceVars { NULL };

//declared variables
long *run_ID { NULL };

void decl(void);
void init(void);

Classbasin* klone(string name) const;
};