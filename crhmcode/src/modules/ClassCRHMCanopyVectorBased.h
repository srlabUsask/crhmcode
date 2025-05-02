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

class ClassCRHMCanopyVectorBased:public ClassModule {

public:

ClassCRHMCanopyVectorBased(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

double Qsi_{ 0.0 }, Qli_ {0.0};

// observation variables

const double *Qsi { NULL };
const double *Qli { NULL };

// declared observation variables

double *Ts { NULL };
double *Qnsn { NULL };
double *Qsisn { NULL };
double *Qlisn { NULL };
double *Qlosn { NULL };

// put variables

double *SWE { NULL };

// declared variables

double *throughfall_rain { NULL };
double *throughfall_snow { NULL };
double *intercepted_snow { NULL };
double *intercepted_rain { NULL };
double *Qnsn_Var { NULL };
double *Qsisn_Var { NULL };
double *Qlisn_Var { NULL };
double *Qsw_veg_Var { NULL };
double *Qlw_veg_Var { NULL };

double *Clca { NULL };
double *k { NULL };
double *Tauc { NULL };
double *Pa { NULL };
double *ra { NULL };
double *u_FHt { NULL };
double *u_1_third_Ht { NULL };

double *LAI_ { NULL };


// variable inputs

const double *hru_t { NULL };
const double *hru_u { NULL };
const double *hru_rh { NULL };
const double *Albedo { NULL };
const double *QdflatE { NULL };

const double *hru_snow { NULL };
const double *hru_rain { NULL };

const double *SolAng { NULL };
const double *cosxs { NULL };
const double *cosxsflat { NULL };
const double *Qdfo { NULL };

const double *QsiS_Var { NULL };
const double *QsiA_Var { NULL };
const double *QliVt_Var { NULL };

// declared parameters:

const double *hru_elev { NULL };
const double *Ht { NULL };
const double *Cc { NULL };
const double *LAI { NULL };
const double *alpha { NULL };
const double *Z0snow { NULL };
const double *Zref { NULL };
const double *Zwind { NULL };
const double *Zvent { NULL };
const double *Surrounding_Ht { NULL };
const double *Gap_diameter { NULL };
const double *Alpha_c { NULL };
const double *B_canopy { NULL };

const long *CanopyClearing { NULL };
const long *CanopyWindSwitchIP { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassCRHMCanopyVectorBased* klone(string name) const;
};
