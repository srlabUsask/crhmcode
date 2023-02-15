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

class ClassVolumetric : public ClassModule {
public:

ClassVolumetric(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1001, "soil_gw") {}; // setting PeerVar. Cannot be "STATE" var

// declared parameters
const double *soil_Depth{ NULL };
const double *Si_correction{ NULL };
const double* fallstat_correction{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_rechr_max{ NULL };
const long *soil_type{ NULL };
const long *set_fallstat{ NULL };
const long* Volumetric_option{ NULL };


// declared variables
double *Volumetric{ NULL };
double *Volumetric_rechr{ NULL };
double *fallstat_V{ NULL };
double *Si_V{ NULL };
double *fallstat{ NULL };
double *Si{ NULL };

// variable inputs
const double *soil_moist{ NULL };
const double *soil_rechr{ NULL };

void decl(void);
void init(void);
void run(void);

ClassVolumetric* klone(string name) const;
};
