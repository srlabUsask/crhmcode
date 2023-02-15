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

class Class_z_s_rho : public ClassModule {
public:

Class_z_s_rho(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double*  z_s{ NULL };            // total snowcover thickness (m)
  double*  rho{ NULL };            // average snowcover density (kg/m^3)

// variable inputs
const double *SWE{ NULL };

void decl(void);
void init(void);
void run(void);

Class_z_s_rho* klone(string name) const;
};
