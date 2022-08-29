/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassREWroute_stream : public ClassModule {
public:

ClassREWroute_stream(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long instreamflowCnt{0};
long gwCnt{0};

// declared variables
double *rew{ NULL };

double **instreamflow_All{ NULL };
double **instreamflow_Grp_out_All{ NULL };

double *instreamflow{ NULL };        // [nhru]
double *cuminstreamflow{ NULL };     // [nhru]
double *outstreamflow{ NULL };       // [nhru]
double *cumoutstreamflow{ NULL };    // [nhru]

double *streamflow{ NULL };     // [BASIN] all HRUs
double *streamflow_s{ NULL };   // [BASIN] all HRUs
double *cumstreamflow{ NULL };  // [BASIN] all HRUs

double *WS_stream_Ktravel_var{ NULL };         // [nhru]

double *culvert_Q{ NULL };
double *culvert_water_H{ NULL };
double *culvert_water_A{ NULL };
double *culvert_water_V{ NULL };
double *culvert_water_O{ NULL };
double *culvert_evap{ NULL };
double *cum_culvert{ NULL };
double *cum_culvert_over{ NULL };
double *HD{ NULL };

ClassMuskingum *instreamflowDelay{ NULL };

ClassClark *Clark_instreamflowDelay{ NULL };

// declared parameters

const double *WS_stream_route_n{ NULL };         // [nhru]
const double *WS_stream_route_R{ NULL };         // [nhru]
const double *WS_stream_route_S0{ NULL };        // [nhru]
const double *WS_stream_route_L{ NULL };         // [nhru]
const long  *WS_stream_Channel_shp{ NULL };      // [nhru]

const double *WS_stream_Lag{ NULL };             // [nhru]
const double *WS_stream_route_X_M{ NULL };       // [nhru]
const long  *WS_stream_whereto_Grp{ NULL };     // [nhru]
const long  *WS_stream_wherefrom_HRU{ NULL };   // [nhru]
const long  *WS_stream_whereto_HRU{ NULL };     // [nhru]
const long  *WS_stream_order{ NULL };           // [nhru]

const double *WS_stream_Kstorage{ NULL };     // [nhru]

const double *WS_stream_channel_slope{ NULL };
const double *WS_stream_side_slope{ NULL };
const double *WS_stream_culvert_diam{ NULL };
const double *WS_stream_culvert_water_Dmax{ NULL };
const double *WS_stream_number_culverts{ NULL };

const long *WS_stream_culvert_type{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassREWroute_stream* klone(string name) const;
};
