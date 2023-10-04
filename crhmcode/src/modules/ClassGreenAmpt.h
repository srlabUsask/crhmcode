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


class ClassGreenAmpt : public ClassModule {
public:

ClassGreenAmpt(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : 
	ClassModule(
		Name, 
		Version, 
		Lvl, 
		1001, // Set PeerRank to ensure proper module ordering below glacier modules 
		"net_rain_org"
	) {};

// declared variables
double *infil{ NULL };
double *cuminfil{ NULL };
double *runoff{ NULL };
double *cumrunoff{ NULL };
double *snowinfil{ NULL };
double *cumsnowinfil{ NULL };
double *meltrunoff{ NULL };
double *cummeltrunoff{ NULL };

// local variables
double *k{ NULL };
double *F0{ NULL };
double *f0{ NULL };
double *F1{ NULL };
double *f1{ NULL };
double *dthbot{ NULL };
double *psidthbot{ NULL };

// declared parameters
const double *basin_area{ NULL }; // [BASIN]
const double *hru_area{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_moist_init{ NULL };
const long  *soil_type{ NULL };

// variable inputs
const double *net_rain{ NULL };
const double *snowmelt{ NULL };
double *soil_moist{ NULL }; // changed to PUT

// class allocated
double garain {0.0};      // precipitation/int
double intensity {0.0};   // precipitation/int converted to mm/h
double pond {0.0};        // mm

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreenAmpt* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(double F0, double dt);

double calcf1(double F, double psidth);
};
