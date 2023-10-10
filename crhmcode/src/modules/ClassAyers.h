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

class ClassAyers : public ClassModule {
public:

ClassAyers(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : 
	ClassModule(
		Name, 
		Version, 
		Lvl, 
		1001, // Set PeerRank to ensure proper module ordering below glacier modules
		"net_rain_org"
	) {}; 

// declared variables
double *infil { NULL };
double *cuminfil { NULL };
double *runoff { NULL };
double *cumrunoff { NULL };
double *snowinfil { NULL };
double *cumsnowinfil { NULL };
double *meltrunoff { NULL };
double *cummeltrunoff { NULL };
double *melt_int { NULL }; // interval melt - from snowmelD

// declared parameters
const double *basin_area { NULL }; // [BASIN]
const double *hru_area { NULL };
const long  *texture { NULL };
const long  *groundcover { NULL };

// variable inputs
const double *net_rain { NULL };
const double *snowmeltD { NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassAyers* klone(string name) const;
};
