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

class ClassObstoPar : public ClassModule {
public:

long Ht_obsCnt{0};

ClassObstoPar(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Ht_var{ NULL };

// declared observation variables
const double *Ht_obs{ NULL };      // interval data

// declared parameters
std::vector<std::string> * obs_name{ NULL };
std::vector<std::string> * par_name{ NULL };

double *Ht{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassObstoPar* klone(string name) const;
};
