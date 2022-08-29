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

class Classqdrift : public ClassModule {
public:

Classqdrift(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

ClassClark *Delaymelt{ NULL };

// declared observation variables
const double *p{ NULL };

// input variables
const double *hru_p{ NULL };

// declared variables
double *SWE{ NULL };
double *driftmelt{ NULL };
double *driftmeltDly{ NULL };
double *cumdriftmelt{ NULL };
double *cumdriftmeltDly{ NULL };
double *driftmeltD{ NULL };
double *snowmeltD{ NULL };

// declared parameters
const long *Type{ NULL };      // NOTUSED, DRIFT or HUMMOCK
const long *DrainTo{ NULL };   // drain to HRU
const double *InitSWE{ NULL };  // initial SWE
const double *length{ NULL };   // length normal to creek
const double *meltstorage{ NULL };  // delay parameter (days)
const double *meltLag{ NULL };      // delay parameter (days)

// variable inputs
const double *Qm{ NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classqdrift* klone(string name) const;
};
