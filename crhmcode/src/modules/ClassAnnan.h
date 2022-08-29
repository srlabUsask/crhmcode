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

class ClassAnnan : public ClassModule {
public:

	double QsiDT {0.0}, TauAT {0.0};

  ClassAnnan(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
//const double *SunAct;

// declared variables
double *hru_SunAct { NULL };
double *QsiA_Var { NULL };
double *QsiD_Var { NULL };
double *QsiS_Var { NULL };

// declared parameters
const double *krs { NULL };
const double *hru_elev { NULL };

// declared observations
double *QsiA { NULL };
double *QsiD { NULL };
double *QsiS { NULL };

// variable inputs
const double *QdflatE { NULL };
const double *QdflatD { NULL };
const double *QdroDext { NULL };
const double *Qdro { NULL };
const double *Qdfo { NULL };
const double *QdfoD { NULL };
const double *SunMax { NULL };
const double *hru_tmax { NULL };
const double *hru_tmin { NULL };

void decl(void);
void init(void);
void run(void);

ClassAnnan* klone(string name) const;
};
