//created by Manishankar Mondal

#include "ClassModule.h"

class ClassREWroute_stream : public ClassModule {
public:

ClassREWroute_stream(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long instreamflowCnt;
long gwCnt;

// declared variables
float *rew;

float **instreamflow_All;
float **instreamflow_Grp_out_All;

float *instreamflow;        // [nhru]
float *cuminstreamflow;     // [nhru]
float *outstreamflow;       // [nhru]
float *cumoutstreamflow;    // [nhru]

float *streamflow;     // [BASIN] all HRUs
float *streamflow_s;   // [BASIN] all HRUs
float *cumstreamflow;  // [BASIN] all HRUs

float *WS_stream_Ktravel_var;         // [nhru]

float *culvert_Q;
float *culvert_water_H;
float *culvert_water_A;
float *culvert_water_V;
float *culvert_water_O;
float *culvert_evap;
float *cum_culvert;
float *cum_culvert_over;
float *HD;

ClassMuskingum *instreamflowDelay;

ClassClark *Clark_instreamflowDelay;

// declared parameters

const float *WS_stream_route_n;         // [nhru]
const float *WS_stream_route_R;         // [nhru]
const float *WS_stream_route_S0;        // [nhru]
const float *WS_stream_route_L;         // [nhru]
const long  *WS_stream_Channel_shp;      // [nhru]

const float *WS_stream_Lag;             // [nhru]
const float *WS_stream_route_X_M;       // [nhru]
const long  *WS_stream_whereto_Grp;     // [nhru]
const long  *WS_stream_wherefrom_HRU;   // [nhru]
const long  *WS_stream_whereto_HRU;     // [nhru]
const long  *WS_stream_order;           // [nhru]

const float *WS_stream_Kstorage;     // [nhru]

const float *WS_stream_channel_slope;
const float *WS_stream_side_slope;
const float *WS_stream_culvert_diam;
const float *WS_stream_culvert_water_Dmax;
const float *WS_stream_number_culverts;

const long *WS_stream_culvert_type;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassREWroute_stream* klone(string name) const;
};