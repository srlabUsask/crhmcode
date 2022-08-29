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


class ClassalbedoBaker : public ClassModule {
public:

ClassalbedoBaker(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Albedo { NULL };
  double *Ab_t { NULL };

// get variables:


 const double *net_snow { NULL };
 const double *SWE { NULL };

// put variables:

// declared parameters
  const double *Albedo_Bare { NULL };
  const double *Albedo_Snow { NULL };
  const double *refresh { NULL };

void decl(void);
void init(void);
void run(void);

ClassalbedoBaker* klone(string name) const;
};
