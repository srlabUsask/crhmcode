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


class ClassLongVt : public ClassModule {
public:

ClassLongVt(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , QsiD_Var, ") {};

// declared observation variables
  const double *Qsi{ NULL };
  const double *QsiD{ NULL };
  const double *Qli{ NULL };

// declared observation functions
  double *QsiDavg{ NULL };

// declared observations
  double *Qli_out{ NULL };

// declared variables
  double *Qli_Var{ NULL };
  double *QliVt_Var{ NULL };
  double *tau{ NULL };

// declared parameters
  const double *Vt{ NULL };

//  const double *epsilon_clear;
  const double *epsilon_s{ NULL };

// variable inputs
  const double *hru_t{ NULL };
  const double *hru_ea{ NULL };
  const double *hru_rh{ NULL };
  const double *QdroDext{ NULL };
  const double *QsiD_Var{ NULL };

void decl(void);
void init(void);
void run(void);

ClassLongVt* klone(string name) const;
};
