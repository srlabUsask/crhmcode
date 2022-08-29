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


class Classinterception : public ClassModule {
public:

Classinterception(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observations
const double *Qsi{ NULL };

// variable inputs
const double *hru_t{ NULL };
const double *hru_snow{ NULL };
const double *hru_rain{ NULL };
const double *hru_u{ NULL };
const double *hru_rh{ NULL };

// declared variables
double *SI_Lo{ NULL };
double *net_snow{ NULL };
double *net_rain{ NULL };
double *SI_Subl{ NULL };
double *Cum_Subl{ NULL };
double *Cum_net_snow{ NULL };
double *v{ NULL };

// declared parameters
const double *Sbar{ NULL };
const double *LAI{ NULL };
const double *k{ NULL };
const double *velw{ NULL };
const double *Ht{ NULL };
const double *WidthJ{ NULL };
const double *basin_area{ NULL };
const double *hru_area{ NULL };

// variable inputs

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classinterception* klone(string name) const;
};
