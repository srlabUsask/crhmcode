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

class Classbasin : public ClassModule {
public:

Classbasin(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters
const long *RUN_ID { NULL };
const long *RUN_START { NULL };
const long *RUN_END { NULL };

const double *Meyer_B { NULL };
const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *hru_lat { NULL };
const double *hru_elev { NULL };
const double* hru_GSL { NULL };
const double *hru_ASL { NULL };

std::vector<std::string> * basin_name { NULL };
std::vector<std::string> * INIT_STATE { NULL };
std::vector<std::string> * hru_names { NULL };
std::vector<std::string> * RapidAdvance_to { NULL };
std::vector<std::string> * Loop_to { NULL };
std::vector<std::string> * StateVars_to_Update { NULL };
std::vector<std::string> * TraceVars { NULL };

//declared variables
long *run_ID { NULL };

void decl(void);
void init(void);

Classbasin* klone(string name) const;
};
