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

class ClassNetroute_M : public ClassModule {
public:

ClassNetroute_M(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv{0};
long soil_ssrDiv{0};
long soil_runoffDiv{0};
long soil_gwDiv{0};

// declared variables
double *inflow{ NULL };        // [nhru]
double *cuminflow{ NULL };     // [nhru]
double *outflow{ NULL };       // [nhru]
double *outflow_diverted{ NULL }; // [nhru]
double *cumoutflow_diverted{ NULL }; // [nhru]
double *cumoutflow{ NULL };    // [nhru]
double *gwinflow{ NULL };        // [nhru]

double *ssrinflow{ NULL };        // [nhru]
double *ssrcuminflow{ NULL };     // [nhru]
double *ssroutflow{ NULL };       // [nhru]
double *ssrcumoutflow{ NULL };    // [nhru]
double *HRU_cumbasinflow{ NULL }; // [nhru]

double *runinflow{ NULL };        // [nhru]
double *runcuminflow{ NULL };     // [nhru]
double *runoutflow{ NULL };       // [nhru]
double *runcumoutflow{ NULL };    // [nhru]

double *gwoutflow{ NULL };       // [nhru]
double *gwoutflow_diverted{ NULL }; // [nhru]
double *gwcuminflow{ NULL };     // [nhru]
double *gwcumoutflow{ NULL };    // [nhru]
double *gwcumoutflow_diverted{ NULL }; // [nhru]

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

double *Ktravel{ NULL };         // [nhru] Muskingum
double *cum_preferential_flow_to_gw{ NULL };

ClassMuskingum *hruDelay{ NULL };
ClassClark *ssrDelay{ NULL };
ClassClark *runDelay{ NULL };
ClassClark *gwDelay{ NULL };

// declared parameters
const double *route_n{ NULL };         // [nhru]
const double *route_R{ NULL };         // [nhru]
const double *route_S0{ NULL };        // [nhru]
const double *route_L{ NULL };         // [nhru]
const double *route_X_M{ NULL };       // [nhru]
const long  *route_Cshp{ NULL };      // [nhru]

const double *Lag{ NULL };              // [nhru]
const double *ssrKstorage{ NULL };      // [nhru]
const double *ssrLag{ NULL };           // [nhru]
const double *runKstorage{ NULL };      // [nhru]
const double *runLag{ NULL };           // [nhru]
const double *gwKstorage{ NULL };       // [nhru]
const double *gwLag{ NULL };            // [nhru]

const double *basin_area{ NULL };        // [BASIN]
const double *hru_area{ NULL };          // [nhru]
const long  *whereto{ NULL };           // [nhru]
const long  *gwwhereto{ NULL };         // [nhru]
const long  *order{ NULL };             // [nhru]
const double *Sdmax{ NULL };             // [nhru]
const double *soil_rechr_max{ NULL };    // [nhru]
const long  *Sd_ByPass{ NULL };         // [nhru]
const long  *soil_rechr_ByPass{ NULL }; // [nhru]
const long  *preferential_flow{ NULL }; // [nhru]

// variable inputs
const double *soil_gw{ NULL };     // [nhru]
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

ClassNetroute_M* klone(string name) const;
};
