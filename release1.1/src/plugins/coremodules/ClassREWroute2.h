//created by Manishankar Mondal

#include "ClassModule.h"

class ClassREWroute2 : public ClassModule {
public:

ClassREWroute2(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long inflowCnt;
long gwCnt;

// declared variables
double *rew;
double *gwrew;

double **inflow_All;
double **gw_All;

double *inflow;        // [nhru]
double *cuminflow;     // [nhru]
double *outflow;       // [nhru]
double *cumoutflow;    // [nhru]

double *gwinflow;        // [nhru]
double *cumgwinflow;     // [nhru]
double *gwoutflow;       // [nhru]
double *cumgwoutflow;    // [nhru]

double *flow;     // [BASIN] all HRUs
double *flow_s;   // [BASIN] all HRUs
double *cumflow;  // [BASIN] all HRUs

double *gwflow;     // [BASIN] all HRUs
double *gwflow_s;   // [BASIN] all HRUs
double *cumgwflow;  // [BASIN] all HRUs

double *WS_Ktravel_var;         // [nhru]
double *WS_gwKtravel_var;         // [nhru]

double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_over_Q;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;

ClassMuskingum *inflowDelay;
ClassMuskingum *gwDelay;

ClassClark *Clark_inflowDelay;
ClassClark *Clark_gwDelay;

// declared parameters

const double *WS_route_n;         // [nhru]
const double *WS_route_R;         // [nhru]
const double *WS_route_S0;        // [nhru]
const double *WS_route_L;         // [nhru]
const long  *WS_Channel_shp;      // [nhru]

const double *WS_Lag;             // [nhru]
const double *WS_route_X_M;       // [nhru]
const long  *WS_whereto;         // [nhru]
const long  *WS_order;           // [nhru]

const double *WS_gwLag;           // [nhru]
const double *WS_gwroute_X_M;     // [nhru]
const long  *WS_gwwhereto;       // [nhru]
const long  *WS_gworder;         // [nhru]

const double *WS_Kstorage;     // [nhru]
const double *WS_gwKstorage;   // [nhru]

const double *WS_channel_slope;
const double *WS_side_slope;
const double *WS_culvert_diam;
const double *WS_culvert_water_Dmax;
const double *WS_number_culverts;

const long *WS_culvert_type;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassREWroute2* klone(string name) const;
};