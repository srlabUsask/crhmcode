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


class Classebsm : public ClassModule {
public:

Classebsm(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , Qnsn_Var, , "){};

// declared observation variables
const double *Qnsn { NULL };
const double *QnD { NULL };

// declared variables
double *snowmeltD { NULL };
double *cumsnowmelt { NULL };
double *LW_ebsm { NULL };
double *u_ebsm { NULL };
double *Qmelt { NULL };
double *Qn_ebsm { NULL };
double *Qh_ebsm { NULL };
double *Qe_ebsm { NULL };
double *Qe_subl { NULL };
double *cumQe_subl { NULL };
double *Qp_ebsm { NULL };
double *Qnsn_Acc { NULL };

double *LWmax { NULL };
double *net_rainD { NULL };

// declared parameters
const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *tfactor { NULL };
const double *nfactor { NULL };
const double *Use_QnD { NULL };

// variable inputs
double *SWE { NULL };
const double *tmean { NULL };
const double *tmax { NULL };
const double *tmin { NULL };
const double *umean { NULL };
const double *rhmean { NULL };
const double *net_rain { NULL };
const double *Albedo { NULL };
const double *sunact { NULL };
const double *QdroD { NULL };
const double *QdfoD { NULL };
const double *sunmax { NULL };
const double *Qnsn_Var { NULL };

const long  *meltflag { NULL };
const long  *delay_melt { NULL };
const long  *Qe_subl_from_SWE { NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classebsm* klone(string name) const;
};
