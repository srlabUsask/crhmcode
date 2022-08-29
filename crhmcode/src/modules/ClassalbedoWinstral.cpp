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

#include "ClassalbedoWinstral.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassalbedoWinstral* ClassalbedoWinstral::klone(string name) const{
  return new ClassalbedoWinstral(name);
}

void ClassalbedoWinstral::decl(void) {

  Description = "'Incomplete code to calculate snowcover albedo from a method proposed by Winstral.'";

  declstatvar("Albedo", TDim::NHRU, "Albedo", "()", &Albedo);

  declstatdiag("Ab_t", TDim::NHRU, "steps since albedo refresh", "()", &Ab_t);

  decllocal("irdalb", TDim::NHRU, "ir_diffuse decay", "()", &irdalb);

  decllocal("vddalb", TDim::NHRU, "visible_diffuse decay", "()", &vdalb);

  decldiagparam("maxdecay", TDim::NHRU, "[0.25]", "0.1", "0.5","maximum decay", "()", &maxdecay);

  decldiagparam("power", TDim::NHRU, "[1.4]", "-2.0", "2.0", "power function", "()", &power);

  decldiagparam("decay_period", TDim::NHRU, "[5000]", "100", "20000", "time over albedo decays", "()", &decay_period);

  decldiagparam("refresh", TDim::NHRU, "[1.0]", "0.5", "50.0", "minimum sub-canopy snowfall to refresh albedo", "(mm)", &refresh);

  decldiagparam("Albedo_Bare", TDim::NHRU, "[0.17]", "0.0", "1.0","Initial albedo for bare ground", "()", &Albedo_Bare);


  declgetvar("*",  "SWE", "(mm)", &SWE);

  declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void ClassalbedoWinstral::init(void) {

  nhru = getdim(TDim::NHRU);

  for (hh = 0; hh < nhru; ++hh){
    Ab_t[hh] = 0;
    irdalb[hh] = 0.24;
    vdalb[hh] = 0.02;
//    balbx[hh] = 0.0;
  }
}

void ClassalbedoWinstral::run(void) {

// albedo routine:

  for(hh = 0; chkStruct(); ++hh) {
    if(SWE[hh] > refresh[hh]){

      if(net_snow[hh] >= refresh[hh])
        Ab_t[hh] = 0;
      else
        Ab_t[hh] = Ab_t[hh] + 24.0/Global::Freq;

      irdalb[hh] = 0.24 + pow(Ab_t[hh]/decay_period[hh], power[hh]) * maxdecay[hh];

      vdalb[hh] = 0.02 + pow(Ab_t[hh]/decay_period[hh], power[hh]) * maxdecay[hh];

      Albedo[hh] = (1.0 - vdalb[hh])*0.48 + (1.0 - irdalb[hh])*0.52;
    }
    else
      Albedo[hh] = Albedo_Bare[hh];
  }
}

void ClassalbedoWinstral::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {

    string s = "'" + Name + " (albedo_Winstral)' ";
    LogMessage(hh, s.c_str());
  }
  LogDebug(" ");
}
