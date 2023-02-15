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


class Classnetall : public ClassModule {
public:

Classnetall(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const double *t{ NULL };
const double *ea{ NULL };
const double **tday_intvls{ NULL };
const double **eaday_intvls{ NULL };
const double *NotUsed{ NULL };

// declared variables
double *net{ NULL };
double *Rn{ NULL }; // net converted to mm
double *netD{ NULL };
double *RnD{ NULL }; // netD converted to mm
double *RnD_POS{ NULL };
double *cum_net{ NULL };

// declared parameters

// variable inputs
const double *hru_t{ NULL };
const double *hru_ea{ NULL };
const double *Albedo{ NULL };
const double *hru_SunAct{ NULL };
const double *SunMax{ NULL };
const double *Qdro{ NULL };
const double *Qdfo{ NULL };
const double *pQdro{ NULL };
const double *pQdfo{ NULL };
const double **pQdro_FREQ{ NULL };
const double **pQdfo_FREQ{ NULL };

void decl(void);
void init(void);
void run(void);

Classnetall* klone(string name) const;
};
