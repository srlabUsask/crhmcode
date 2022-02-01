//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassNetroute_D : public ClassModule {
public:

ClassNetroute_D(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv {0};
long soil_ssrDiv {0};
long soil_runoffDiv {0};
long soil_gwDiv {0};

// declared variables
double* inflow {NULL};           // [nhru]
double *cuminflow { NULL };        // [nhru]
double *outflow { NULL };          // [nhru]
double *outflow_diverted { NULL }; // [nhru]
double *cumoutflow_diverted { NULL }; // [nhru]
double *cumoutflow { NULL };       // [nhru]
double *cumscaling_boost { NULL }; // [nhru]
double *gwinflow { NULL };         // [nhru]
double *gwoutflow_diverted { NULL }; // [nhru]
double *gwcumoutflow_diverted { NULL }; // [nhru]
double *HRU_cumbasinflow { NULL }; // [nhru]

double *ssrinflow{ NULL };        // [nhru]
double *ssrcuminflow{ NULL };     // [nhru]
double *ssroutflow{ NULL };       // [nhru]
double *ssrcumoutflow{ NULL };    // [nhru]

double *runinflow{ NULL };        // [nhru]
double *runcuminflow{ NULL };     // [nhru]
double *runoutflow{ NULL };       // [nhru]
double *runcumoutflow{ NULL };    // [nhru]

double *gwoutflow{ NULL };       // [nhru]
double *gwcuminflow{ NULL };    // [nhru]
double *gwcumoutflow{ NULL };    // [nhru]

double *basinflow{ NULL };     // [BASIN] all HRUs
double *basinflow_s{ NULL };   // [BASIN] all HRUs
double *cumbasinflow{ NULL };  // [BASIN] all HRUs
double *basingw{ NULL };       // [BASIN} all HRUs
double *basingw_s{ NULL };     // [BASIN} all HRUs
double *cumbasingw{ NULL };    // [BASIN} all HRUs

double *soil_ssr_Buf{ NULL };    // buffered
double *soil_runoff_Buf{ NULL }; // buffered
double *soil_gw_Buf{ NULL };     // buffered

double *cum_to_Sd{ NULL };         // [nhru]
double *cum_to_soil_rechr{ NULL }; // [nhru]

double *distrib_sum{ NULL };
double *cum_preferential_flow_to_gw{ NULL };

ClassClark *hruDelay{ NULL };
ClassClark *ssrDelay{ NULL };
ClassClark *runDelay{ NULL };
ClassClark *gwDelay{ NULL };

// declared parameters
const double *Kstorage{ NULL };         // [nhru]
const double *Lag{ NULL };              // [nhru]
const double *ssrKstorage{ NULL };      // [nhru]
const double *ssrLag{ NULL };           // [nhru]
const double *runKstorage{ NULL };      // [nhru]
const double *runLag{ NULL };           // [nhru]
const double *gwKstorage{ NULL };       // [nhru]
const double *gwLag{ NULL };            // [nhru]
const long  *gwwhereto{ NULL };        // [nhru]

const double *basin_area{ NULL };        // [BASIN]
const double *hru_area{ NULL };          // [nhru]
const double *distrib{ NULL };
const double **distrib_hru{ NULL };
const double *distrib_Basin{ NULL };
const double *Sdmax{ NULL };             // [nhru]
const double *soil_rechr_max{ NULL };    // [nhru]
const long  *Sd_ByPass{ NULL };         // [nhru]
const long  *soil_rechr_ByPass{ NULL }; // [nhru]
const long  *order{ NULL }; // [nhru]
const long  *preferential_flow{ NULL }; // [nhru]

const double *scaling_factor{ NULL };    // temporary modification

// variable inputs
const double *soil_gw{ NULL };   // [nhru]
const double *soil_ssr{ NULL };    // [nhru]
const double *soil_runoff{ NULL }; // [nhru]

// variable puts
double *Sd{ NULL };
double *soil_moist{ NULL };
double *soil_rechr{ NULL };
double *redirected_residual{ NULL };
double *gw{ NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);
virtual double Function1(double *I, long hh);
virtual double Function2(double *X, long hh);

ClassNetroute_D* klone(string name) const;
};
