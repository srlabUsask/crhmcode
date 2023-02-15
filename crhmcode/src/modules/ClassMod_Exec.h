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

class ClassMod_Exec : public ClassModule {
public:

ClassMod_Exec(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

  //HINSTANCE DLL;
  long Imodules {0};
  string S_Vars;
  string S_Pars;
  long Vars_Cnt {0};
  long Pars_Cnt {0};

  typedef  long LoadModuleTypeInit(const char *Grp, long GrpNo, long hru_cnt, const char *S_Vars, long VarsNo, double **V, const char *V_Pars, long ParsNo, double **P);
  typedef  long LoadModuleTypeStep(double DTnow); // time step. Zero at end of run.

  LoadModuleTypeInit *LoadUserInit{ NULL };
  LoadModuleTypeStep *LoadUserStep{ NULL };

// Lingage arrays

  double **VarArray{ NULL };
  double **ParArray{ NULL };

// declared variables
double *Dummy{ NULL };
double *Dummy2{ NULL };
long *statusInit{ NULL };
long *statusStep{ NULL };

// declared parameters
std::vector<std::string> * DLL_name{ NULL };
std::vector<std::string> * chg_Pars{ NULL };
std::vector<std::string> * trk_Vars{ NULL };
const long *Borland_Dll{ NULL };

// variable inputs

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassMod_Exec* klone(string name) const;
};
