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

class ClassSWEslope : public ClassModule {
public:

ClassSWEslope(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, "glacier_h2o, snowmeltD") {};

// declared variables
double *SWE_in{ NULL };
double *SWE_out{ NULL };
double *cumSWE_in{ NULL };
double *cumSWE_out{ NULL };
double *Hd{ NULL };

// declared parameters
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL }; // [nhru]
const double *hru_GSL{ NULL };    // [nhru]
const long* use_rho{NULL};    // [nhru], 12Apr2021: change from float to long
const double *snow_density{ NULL };    // [nhru]
const double *Hd_min{ NULL };    // [nhru]
const long *order{ NULL }; // [nhru]
const double *distrib_SWEslope{ NULL };
const double **distrib_hru{ NULL };
const long *Disable_SWEslope{ NULL }; // [nhru]

// variable put inputs
double *SWE{ NULL };

// variable inputs
const double *rho{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSWEslope* klone(string name) const;
};
