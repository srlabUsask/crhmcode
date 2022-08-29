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

class Classwalmsley_wind : public ClassModule {
public:
Classwalmsley_wind(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_Uadjust{ NULL };
double *hru_Uchange{ NULL };
double *WR{ NULL };

// declared parameters
const double *Zwind{ NULL };
const double *Ax{ NULL };
const double *Bx{ NULL };
const double *L{ NULL };
const double *Walmsley_Ht{ NULL };

// varaible inputs
const double *hru_u{ NULL };

void decl(void);
void init(void);
void run(void);

Classwalmsley_wind* klone(string name) const;
};
