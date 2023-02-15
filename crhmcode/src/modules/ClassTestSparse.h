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

class ClassTestSparse : public ClassModule {
public:

ClassTestSparse(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long ObsCnt_N_up{0};
long ObsCnt_P_up{0};
long ObsCntMan_N_up{0};
long ObsCntMan_P_up{0};
long ObsCntRes_N_up{0};
long ObsCntRes_P_up{0};
long ObsCnt_N_down{0};
long ObsCnt_P_down{0};
long ObsCntMan_N_down{0};
long ObsCntMan_P_down{0};
long ObsCntRes_N_down{0};
long ObsCntRes_P_down{0};
long ObsCnt_fertperiod{0};
long ObsCnt_litterperiod{0};

// declared variables
double *Fert_N_Var{ NULL };
double *Fert_P_Var{ NULL };
double *Man_N_Var{ NULL };
double *Man_P_Var{ NULL };
double *Res_N_Var{ NULL };
double *Res_P_Var{ NULL };
double *Fert_period_Var{ NULL };
double *Litter_period_Var{ NULL };

// declared parameters

// put parameters

// declared observation variables
const double *Fert_N_up{ NULL };
const double *Fert_P_up{ NULL };
const double *Man_N_up{ NULL };
const double *Man_P_up{ NULL };
const double *Res_N_up{ NULL };
const double *Res_P_up{ NULL };
const double *Fert_N_down{ NULL };
const double *Fert_P_down{ NULL };
const double *Man_N_down{ NULL };
const double *Man_P_down{ NULL };
const double *Res_N_down{ NULL };
const double *Res_P_down{ NULL };
const double *Fert_period{ NULL };
const double *Litter_period{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassTestSparse* klone(string name) const;
};
