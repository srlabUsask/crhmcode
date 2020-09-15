//created by Manishankar Mondal

#include "ClassModule.h"

class ClassREWroute_stream : public ClassModule {
public:

ClassREWroute_stream(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long instreamflowCnt;
long gwCnt;

// declared variables
double *rew;

double **instreamflow_All;
double **instreamflow_Grp_out_All;

double *instreamflow;        // [nhru]
double *cuminstreamflow;     // [nhru]
double *outstreamflow;       // [nhru]
double *cumoutstreamflow;    // [nhru]

double *streamflow;     // [BASIN] all HRUs
double *streamflow_s;   // [BASIN] all HRUs
double *cumstreamflow;  // [BASIN] all HRUs

double *WS_stream_Ktravel_var;         // [nhru]

double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_water_O;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;

ClassMuskingum *instreamflowDelay;

ClassClark *Clark_instreamflowDelay;

// declared parameters

const double *WS_stream_route_n;         // [nhru]
const double *WS_stream_route_R;         // [nhru]
const double *WS_stream_route_S0;        // [nhru]
const double *WS_stream_route_L;         // [nhru]
const long  *WS_stream_Channel_shp;      // [nhru]

const double *WS_stream_Lag;             // [nhru]
const double *WS_stream_route_X_M;       // [nhru]
const long  *WS_stream_whereto_Grp;     // [nhru]
const long  *WS_stream_wherefrom_HRU;   // [nhru]
const long  *WS_stream_whereto_HRU;     // [nhru]
const long  *WS_stream_order;           // [nhru]

const double *WS_stream_Kstorage;     // [nhru]

const double *WS_stream_channel_slope;
const double *WS_stream_side_slope;
const double *WS_stream_culvert_diam;
const double *WS_stream_culvert_water_Dmax;
const double *WS_stream_number_culverts;

const long *WS_stream_culvert_type;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassREWroute_stream* klone(string name) const;
};