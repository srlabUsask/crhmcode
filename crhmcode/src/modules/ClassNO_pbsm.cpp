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

#include "ClassNO_pbsm.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;


ClassNO_pbsm* ClassNO_pbsm::klone(string name) const{
  return new ClassNO_pbsm(name);
}

void ClassNO_pbsm::decl(void) {

  Description = "'Substitute for pbsm when there is no transport and sublimation.  Alternatve is \"pbsm\" with parameter \"inhibit_bs\" = 1.'";

  declstatvar("SWE", TDim::NHRU, "snow water equivalent", "(mm)", &SWE);

  declstatdiag("cumSno", TDim::NHRU, "cumulative snow", "(mm)", &cumSno);

  declvar("snowdepth", TDim::NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);


/* parameters */

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

  declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
  declgetvar("*",   "net_snow", "(mm/int)", &net_snow);

}

void ClassNO_pbsm::init(void) {

  nhru = getdim(TDim::NHRU);

  hru_basin = new double[nhru];

  for (hh = 0; hh < nhru; ++hh) {
    SWE[hh] = 0.0;
    cumSno[hh] = 0.0;
    hru_basin[hh] = hru_area[hh]/basin_area[0];
    snowdepth[hh] = 0.0;
  }
}

void ClassNO_pbsm::run(void) {

  for (hh = 0; chkStruct(); ++hh) {

    if(net_snow[hh] > 0.0) {
      SWE[hh] = SWE[hh] + net_snow[hh];
      cumSno[hh] = cumSno[hh] + net_snow[hh];
    }

    if(SWE[hh] > 0.0){
      const_cast<long*> (inhibit_evap)[hh] = 1;
      snowdepth[hh] = Common::DepthofSnow(SWE[hh]);
    }
    else{
      const_cast<long*> (inhibit_evap)[hh] = 0;
      snowdepth[hh] = 0;
    }
  }
}

void ClassNO_pbsm::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (NO_pbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
  }
  LogDebug(" ");
}
