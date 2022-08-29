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

class ClassSlope_Qsi : public ClassModule {
public:

ClassSlope_Qsi(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *QsiS_Var{ NULL };
double *QsiD_Var{ NULL };

// declared observations variable
const double *Qsi{ NULL };

// declared observations
double *QsiS{ NULL };
double *QsiD{ NULL };
double *QsiD_Obs{ NULL };

// variable inputs
const double *Qdro{ NULL };
const double *Qdfo{ NULL };
const double *Qdflat{ NULL };

void decl(void);
void init(void);
void run(void);

ClassSlope_Qsi* klone(string name) const;
};
