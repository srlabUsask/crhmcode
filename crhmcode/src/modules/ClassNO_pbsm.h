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

class ClassNO_pbsm : public ClassModule {
public:

ClassNO_pbsm(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
// declared variables
double *SWE{ NULL };
double *cumSno{ NULL };
double *snowdepth{ NULL };

// declared parameters
const double *basin_area{ NULL };
const double *hru_area{ NULL };
const long *inhibit_evap{ NULL };

// variable inputs
const double *net_snow{ NULL };
const long  *hru_newsnow{ NULL };

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNO_pbsm* klone(string name) const;
};
