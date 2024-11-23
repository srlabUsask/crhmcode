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

class ClassPSPnew : public ClassModule {
public:

ClassPSPnew(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared observation variables
// const double *TsnowG{ NULL };
// const double *Lnot{ NULL };

double Qsi_{ 0.0 }, Qli_ {0.0};

// observation variables
const double *Qsi { NULL };
const double *Qli { NULL };


// declared variables
double *Qsubl{ NULL };
double *Load{ NULL };
double *Thru{ NULL };
double *TCanSnow{ NULL };
double *Tbiomass{ NULL };
double *Qsisn_Var { NULL };
double *Qlisn_Var { NULL };

// declared parameters
const double *Sbar{ NULL };
const double *LAI{ NULL };
const double *Zcan{ NULL };
const double *Zref{ NULL };
const double *Ht{ NULL };
const double *Biomass{ NULL };
const double *k{ NULL };
const double *HeightH{ NULL };
const double *WidthJ{ NULL };
const long *InitN{ NULL };

// variable inputs
const double *RHref{ NULL };
const double *Qn{ NULL };
const double *QsIn{ NULL };
const double *QsOut{ NULL };
const double *hru_u{ NULL };
const double *hru_p{ NULL };
const double *TAref{ NULL };
const double *SolarAng{ NULL };
const double *hru_ea { NULL };
const double *QdflatE { NULL };
const double *QliVt_Var { NULL };
const double *QsiS_Var { NULL };
const double *QsiA_Var { NULL };



// local allocated arrays
double *T0CanSnow{ NULL };
double *T0biomass{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

class ClassPSPnew* klone(string name) const;

};
