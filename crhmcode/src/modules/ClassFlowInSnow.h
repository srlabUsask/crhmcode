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

class ClassFlowInSnow : public ClassModule {
public:

ClassFlowInSnow(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module { NULL }; // used to call preser for simple projects

// declared variables
double* Ksat_snow {NULL};
double *K_snow { NULL };
double *u_down { NULL };
double *K_down { NULL };
double *K_slope { NULL };
double *Meltrunoff_K { NULL };
double *In_storage { NULL };
double *runKstorage_var { NULL };

// get variables:
const double *rho { NULL };
const double *h2o_sat { NULL };
const double *T_s_l { NULL };
const double *z_s { NULL };

// put variables
double  *runKstorage { NULL };

// declared parameters
const double *S_I { NULL };
const double *d_g { NULL };
const double *t_inhibit_flow { NULL };
const double *runKstorage_winter { NULL };
const double *runKstorage_summer { NULL };
const double *Sr { NULL };
const double  *hru_GSL { NULL };
const double  *route_L { NULL };
const long  *inhibit_MeltRunoff_Kstorage { NULL };

void decl(void);
void init(void);
void run(void);

ClassFlowInSnow* klone(string name) const;
};
