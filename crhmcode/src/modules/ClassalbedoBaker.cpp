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

#include <algorithm>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

#include "ClassalbedoBaker.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;



ClassalbedoBaker* ClassalbedoBaker::klone(string name) const{
  return new ClassalbedoBaker(name);
}

void ClassalbedoBaker::decl(void) {

  Description = "'Calculates snowcover albedo from a method proposed by Baker.'";

  declstatvar("Albedo", TDim::NHRU, "Albedo", "()", &Albedo);

  decllocal("Ab_t", TDim::NHRU, "timesteps since albedo refresh", "()", &Ab_t);

  decldiagparam("Albedo_Snow", TDim::NHRU, "[0.85]", "0.0", "1.0","Initial albedo for snow cover", "()", &Albedo_Snow);

  decldiagparam("Albedo_Bare", TDim::NHRU, "[0.17]", "0.0", "1.0","Initial albedo for bare ground", "()", &Albedo_Bare);

  decldiagparam("refresh", TDim::NHRU, "[3.0]", "0.0", "50.0", "minimum sub-canopy snowfall to refresh albedo", "(mm)", &refresh);


  declgetvar("*",  "SWE", "(mm)", &SWE);

  declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void ClassalbedoBaker::init(void) {

  nhru = getdim(TDim::NHRU);

  for (hh = 0; hh < nhru; ++hh){
    if(SWE[hh] > 1.0)
      Albedo[hh] = Albedo_Snow[hh];
    else
      Albedo[hh] = Albedo_Bare[hh];

    Ab_t[hh] = 0.0;
  }
}

void ClassalbedoBaker::run(void) {

  for(hh = 0; chkStruct(); ++hh) {
    if(SWE[hh] > 1.0){

// albedo routine:

      if(net_snow[hh] >= refresh[hh])
        Ab_t[hh] = 0;
      else
        Ab_t[hh] = Ab_t[hh] + 1;

// albedo decay formulation after (Baker et al., 1990):

        Albedo[hh] = 0.9 - 0.0473 * pow(Ab_t[hh]/Global::Freq, 0.1f);

// Baker, D.G., Ruschy, D.L., Wall, D.B., 1990.
//   The albedo decay of prairie snows. J. Appl. Meteor. 29 _2, 179-187

// if albedo < Albedo_Bare or no snow albedo == Albedo_Bare

       if(Albedo[hh] < Albedo_Bare[hh] || SWE[hh] <= 1.0)
         Albedo[hh] = Albedo_Bare[hh];
    }
    else
      Albedo[hh] = Albedo_Bare[hh];
  }
}
