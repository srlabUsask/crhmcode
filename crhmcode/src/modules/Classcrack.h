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

class Classcrack : public ClassModule {
public:

Classcrack(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : 
    ClassModule(
        Name, 
        Version, 
        Lvl, 
        1001, // Set PeerRank to ensure proper module ordering below glacier modules
        "net_rain_org"
    ), Xinfil(NULL), timer(NULL) {};

// declared variables
double *snowinfil { NULL };
double *cumsnowinfil { NULL };
double *infil { NULL };
double *cuminfil { NULL };
double *meltrunoff { NULL };
double *cummeltrunoff { NULL };
double *runoff { NULL };
double *cumrunoff { NULL };
double *RainOnSnow { NULL };
double *RainOnSnowA { NULL };
long  *crackstat { NULL };
long  *crackon { NULL };

// declared parameters
const double *basin_area { NULL }; // [BASIN]
const double *hru_area { NULL };
const double *fallstat { NULL };
const double *Major { NULL };      // threshold for major melt event(default is 5 mm/day)
const long* infDays{ NULL }; // maximum number of days of snowmelt infiltration to frozen soil
const long  *PriorInfiltration { NULL };

// variable inputs
const double *hru_tmax { NULL };
const double *snowmelt { NULL };
const double *SWE { NULL };
const double *net_rain { NULL };

// local allocated arrays
double **Xinfil { NULL }; // [3] [nhru]
long *timer { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcrack* klone(string name) const;
};
