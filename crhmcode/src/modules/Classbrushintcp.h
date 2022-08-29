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

class Classbrushintcp : public ClassModule {
public:

Classbrushintcp(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared variables
double *net_rain { NULL };
double *cum_net_rain { NULL };
double *net_snow { NULL };
double *net_p { NULL };
double *Load { NULL };
double *Thru { NULL };
double *cumThru { NULL };
double *brushsubl { NULL };
double *spherecoeff { NULL };
double *cumbrushsubl { NULL };
double *intcp_evap { NULL };

// declared parameters
const double *basin_area { NULL };   // [ONE]
const double *hru_area { NULL };
const double *Ht { NULL };
const double *Zref { NULL };
const double *Zcan { NULL };
const double *brushAtten { NULL };
const double *Sbar { NULL };
const double *LAI { NULL };
const double *WidthJ { NULL };
const double *Tunload { NULL };

// variable inputs
const double *hru_t { NULL };
const double *hru_tmean { NULL };
const double *hru_rh { NULL };
const double *hru_u { NULL };
const double *hru_p { NULL };
const double *hru_rain { NULL };
const double *hru_snow { NULL };

// variable inputs/outputs
double *cumSubl{ NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classbrushintcp* klone(string name) const;

};
