//created by Manishankar Mondal

#include "ClassModule.h"

class ClassREWroute : public ClassModule {
public:

ClassREWroute(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long inflowCnt;
long gwCnt;

// declared variables
float *rew;
float *gwrew;

float **inflow_All;
float **gw_All;

float *inflow;        // [nhru]
float *cuminflow;     // [nhru]
float *outflow;       // [nhru]
float *cumoutflow;    // [nhru]

float *gwinflow;        // [nhru]
float *cumgwinflow;     // [nhru]
float *gwoutflow;       // [nhru]
float *cumgwoutflow;    // [nhru]

float *flow;     // [BASIN] all HRUs
float *flow_s;   // [BASIN] all HRUs
float *cumflow;  // [BASIN] all HRUs

float *gwflow;     // [BASIN] all HRUs
float *gwflow_s;   // [BASIN] all HRUs
float *cumgwflow;  // [BASIN] all HRUs

float *WS_Ktravel_var;         // [nhru]
float *WS_gwKtravel_var;         // [nhru]

float *culvert_Q;
float *culvert_water_H;
float *culvert_water_A;
float *culvert_water_V;
float *culvert_water_O;
float *culvert_evap;
float *cum_culvert;
float *cum_culvert_over;
float *HD;

ClassMuskingum *inflowDelay;
ClassMuskingum *gwDelay;

ClassClark *Clark_inflowDelay;
ClassClark *Clark_gwDelay;

// declared parameters

const float *WS_route_n;         // [nhru]
const float *WS_route_R;         // [nhru]
const float *WS_route_S0;        // [nhru]
const float *WS_route_L;         // [nhru]
const long  *WS_Channel_shp;      // [nhru]

const float *WS_Lag;             // [nhru]
const float *WS_route_X_M;       // [nhru]
const long  *WS_whereto;         // [nhru]
const long  *WS_order;           // [nhru]

const float *WS_gwLag;           // [nhru]
const float *WS_gwroute_X_M;     // [nhru]
const long  *WS_gwwhereto;       // [nhru]
const long  *WS_gworder;         // [nhru]

const float *WS_Kstorage;     // [nhru]
const float *WS_gwKstorage;   // [nhru]

const float *WS_channel_slope;
const float *WS_side_slope;
const float *WS_culvert_diam;
const float *WS_culvert_water_Dmax;
const float *WS_number_culverts;

const long *WS_culvert_type;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassREWroute* klone(string name) const;
};