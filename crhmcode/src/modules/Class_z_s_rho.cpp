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

#include "Class_z_s_rho.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

Class_z_s_rho* Class_z_s_rho::klone(string name) const{
  return new Class_z_s_rho(name);
}

void Class_z_s_rho::decl(void) {

  Description = "'Required when pbsmSnobal used with glacier and glacier_org. Replaces z_s and rho normally supplied by module SnobalCRHM to pbsmSnobal.'";

  declstatvar("z_s", TDim::NHRU, "total snowcover thickness", "(m)", &z_s);

  declstatvar("rho", TDim::NHRU, "average snowcover density", "(kg/m^3)", &rho);

  declgetvar("*", "SWE", "(mm)",        &SWE);

}

void Class_z_s_rho::init(void) {

  nhru = getdim(TDim::NHRU);

  for (hh = 0; chkStruct(); ++hh){
    z_s[hh] = 0.0;
    rho[hh] = 218.0; // 10/18/16
  }
}

void Class_z_s_rho::run(void) {

  //double SWE_Max; varible is unreferenced commenting out for now - jhs507

  for (hh = 0; chkStruct(); ++hh){
    z_s[hh] = Common::DepthofSnow(SWE[hh]); // returns zero if SWE <= 2.05 mm
    if(z_s[hh] > 0.0)
      rho[hh] = SWE[hh]/z_s[hh];
    else
      rho[hh] = 218.0; // 10/18/16
  }
}
