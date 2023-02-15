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

class ClassGrow_Crop : public ClassModule {
public:

ClassGrow_Crop(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Crop_Ht{ NULL };

// declared parameters
const double *Ht{ NULL };
const double *Crop_Grow_Rate{ NULL };
const double *JCrop_Start{ NULL };
const double *JCrop_Mature{ NULL };
const double *JCrop_Harvest{ NULL };
const double *Init_Crop_Ht{ NULL };

// variable inputs

void decl(void);
void init(void);
void run(void);

ClassGrow_Crop* klone(string name) const;
};
