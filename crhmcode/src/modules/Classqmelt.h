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

class Classqmelt : public ClassModule {
public:

Classqmelt(string Name = "Qmelt", string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl){};

// declared variables
double *Qm{ NULL };      // MJ/m2/Int
double *Qg{ NULL };      // MJ/m2/Int
double *cum_Qm{ NULL };  // MJ/m2
double *cum_Qg{ NULL };  // MJ/m2
double *QmD{ NULL };     // MJ/m2
double *QgD{ NULL };     // MJ/m2

// declared parameters
const double *TIa0Mn{ NULL };
const double *TIa1Mn{ NULL };
const double *TIs0Mn{ NULL };
const double *TIs1Mn{ NULL };

// declared observations
const double *t{ NULL };      // DEGREE_CELSIUS
const double *ts{ NULL };     // DEGREE_CELSIUS
double *tmean{ NULL };  // DEGREE_CELSIUS
double *tpos{ NULL };   // DEGREE_CELSIUS
double *tsmean{ NULL }; // DEGREE_CELSIUS
double *tspos{ NULL };  // DEGREE_CELSIUS

void decl(void);
void init(void);
void run(void);

Classqmelt* klone(string name) const;
};
