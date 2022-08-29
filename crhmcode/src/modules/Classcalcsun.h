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

class Classcalcsun : public ClassModule {
public:

Classcalcsun(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , , QsiD_Var") {};

// declared observation variables
const double *Qsi { NULL };
const double *QsiD_Obs { NULL };
const double *SunAct { NULL };

// declared observation functions
double *Qsitot { NULL };

// declared variables
double *hru_SunAct { NULL };

// declared parameters

// variable inputs
const double *QdflatD { NULL };
const double *QdfoD { NULL };
const double *SunMax { NULL };
const double *QsiD_Var { NULL };

void decl(void);
void init(void);
void run(void);

Classcalcsun* klone(string name) const;
};
