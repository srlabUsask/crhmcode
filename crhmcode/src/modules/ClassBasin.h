//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

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

std::vector<std::string> * basin_name { NULL };
std::vector<std::string> * INIT_STATE { NULL };
std::vector<std::string> * hru_names { NULL };
std::vector<std::string> * RapidAdvance_to { NULL };
std::vector<std::string> * Loop_to { NULL };
std::vector<std::string> * StateVars_to_Update { NULL };
std::vector<std::string> * TraceVars { NULL };

//declared variables
long *run_ID { NULL };

void decl(void);
void init(void);

Classbasin* klone(string name) const;
};