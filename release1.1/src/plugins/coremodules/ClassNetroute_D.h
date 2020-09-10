//created by Manishankar Mondal

#include "ClassModule.h"

class ClassNetroute_D : public ClassModule {
public:

ClassNetroute_D(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
float *inflow;           // [nhru]
float *cuminflow;        // [nhru]
float *outflow;          // [nhru]
float *outflow_diverted; // [nhru]
float *cumoutflow_diverted; // [nhru]
float *cumoutflow;       // [nhru]
float *cumscaling_boost; // [nhru]
float *gwinflow;         // [nhru]
float *gwoutflow_diverted; // [nhru]
float *gwcumoutflow_diverted; // [nhru]
float *HRU_cumbasinflow; // [nhru]

float *ssrinflow;        // [nhru]
float *ssrcuminflow;     // [nhru]
float *ssroutflow;       // [nhru]
float *ssrcumoutflow;    // [nhru]

float *runinflow;        // [nhru]
float *runcuminflow;     // [nhru]
float *runoutflow;       // [nhru]
float *runcumoutflow;    // [nhru]

float *gwoutflow;       // [nhru]
float *gwcuminflow;    // [nhru]
float *gwcumoutflow;    // [nhru]

float *basinflow;     // [BASIN] all HRUs
float *basinflow_s;   // [BASIN] all HRUs
float *cumbasinflow;  // [BASIN] all HRUs
float *basingw;       // [BASIN} all HRUs
float *basingw_s;     // [BASIN} all HRUs
float *cumbasingw;    // [BASIN} all HRUs

float *soil_ssr_Buf;    // buffered
float *soil_runoff_Buf; // buffered
float *soil_gw_Buf;     // buffered

float *cum_to_Sd;         // [nhru]
float *cum_to_soil_rechr; // [nhru]

float *distrib_sum;
float *cum_preferential_flow_to_gw;

ClassClark *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const float *Kstorage;         // [nhru]
const float *Lag;              // [nhru]
const float *ssrKstorage;      // [nhru]
const float *ssrLag;           // [nhru]
const float *runKstorage;      // [nhru]
const float *runLag;           // [nhru]
const float *gwKstorage;       // [nhru]
const float *gwLag;            // [nhru]
const long  *gwwhereto;        // [nhru]

const float *basin_area;        // [BASIN]
const float *hru_area;          // [nhru]
const float *distrib;
const float **distrib_hru;
const float *distrib_Basin;
const float *Sdmax;             // [nhru]
const float *soil_rechr_max;    // [nhru]
const long  *Sd_ByPass;         // [nhru]
const long  *soil_rechr_ByPass; // [nhru]
const long  *order; // [nhru]
const long  *preferential_flow; // [nhru]

const float *scaling_factor;    // temporary modification

// variable inputs
const float *soil_gw;   // [nhru]
const float *soil_ssr;    // [nhru]
const float *soil_runoff; // [nhru]

// variable puts
float *Sd;
float *soil_moist;
float *soil_rechr;
float *redirected_residual;
float *gw;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);
virtual float Function1(float *I, long hh);
virtual float Function2(float *X, long hh);

ClassNetroute_D* klone(string name) const;
};