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

class ClassMeltRunoff_Lag : public ClassModule {
public:

ClassMeltRunoff_Lag(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module{ NULL }; // used to call preser for simple projects

// declared variables
double *In_Lagstorage{ NULL };
double *Tf{ NULL };

// get variables:
const double *snowmelt_int{ NULL };

// put variables
double *runLag{ NULL };

// declared parameters
const double *hru_area{ NULL };
const long  *inhibit_MeltRunoff_Lag{ NULL };

void decl(void);
void init(void);
void run(void);

ClassMeltRunoff_Lag* klone(string name) const;
};
