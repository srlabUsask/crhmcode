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

class Classalbedo : public ClassModule {
public:

Classalbedo(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double* Albedo { NULL };
double *net_snowD { NULL };  // daily value sum(newsnow)
long *meltflag { NULL };
long *winter { NULL };
long  *newsnowcnt { NULL };

// declared parameters
const double* Albedo_bare { NULL };
const double *Albedo_snow { NULL };
const double *hru_lat { NULL };

// variable inputs
const double *hru_tmax { NULL };
const double *hru_tmin { NULL };
const double *QdroD { NULL };
const double *SWE { NULL };
const double *net_snow { NULL };
const long  *hru_newsnow { NULL };

void decl(void);
void init(void);
void run(void);

Classalbedo* klone(string name) const;
};
