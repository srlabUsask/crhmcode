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

#include "ClassMeltRunoff_Lag.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassMeltRunoff_Lag* ClassMeltRunoff_Lag::klone(string name) const{
  return new ClassMeltRunoff_Lag(name);
}

void ClassMeltRunoff_Lag::decl(void) {

  Description = "'Calculates Melt Runoff.'";

  declvar("Tf", TDim::NHRU, "time lag after water percolated snowcover", "()", &Tf);  // minutes

  decldiag("In_Lagstorage", TDim::NHRU, "melt runoff in Lag storage at the beginning of interval!", "(mm)", &In_Lagstorage);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("inhibit_MeltRunoff_Lag", TDim::NHRU, "[0]", "0", "1", "inhibit MeltRunoff_Lag correction, 1 -> inhibit", "()", &inhibit_MeltRunoff_Lag);

  declputparam("*", "runLag", "(h)", &runLag);


  declgetvar("*", "snowmelt_int", "(mm)", &snowmelt_int);

}

void ClassMeltRunoff_Lag::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; chkStruct(); ++hh) {
    Tf[hh] = 0.0;
    In_Lagstorage[hh] = 0.0;
  }

  Netroute_module = (ClassModule*) FindModule_from_parameter("*", "runKstorage");
}

void ClassMeltRunoff_Lag::run(void) {

//  if(getstep()%Global::Freq != 0) return;

  for(hh = 0; chkStruct(); ++hh)
    if(!inhibit_MeltRunoff_Lag[hh]){
      if(snowmelt_int[hh] > 0.0)
        Tf[hh] = 250.0*pow(hru_area[hh], 0.17)*pow(snowmelt_int[hh], -0.5)/60.0;

      if(snowmelt_int[hh] <= 0.0)
        Tf[hh] = 0.0;

    In_Lagstorage[hh] = Netroute_module->Function1(Tf, hh);
  }
}
