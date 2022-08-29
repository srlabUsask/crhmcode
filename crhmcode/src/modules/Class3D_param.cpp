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

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "Class3D_param.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

Class3D_param* Class3D_param::klone(string name) const{
  return new Class3D_param(name);
}

void Class3D_param::decl(void) {

  Description = "'Initialises the variable \"Param_3D\" from the parameter \"Var_3D\".'";

  declvar("Var_3D", TDim::NHRU, "Var_3D", "()", &Var_3D);

  declparam("Param_3D", TDim::NHRU, "[0.17]", "0.0", "1.0","Param_3D", "()", &Param_3D);

}

void Class3D_param::init(void) {
  nhru = getdim(TDim::NHRU);

  for (hh = 0; hh < nhru; ++hh){
    Var_3D[hh] = Param_3D[hh];
  }
}

void Class3D_param::run(void) {
}

void Class3D_param::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {

    string s = "'" + Name + " (3D_param)' ";
    LogMessage(hh, s.c_str());
  }
  LogDebug(" ");
}
