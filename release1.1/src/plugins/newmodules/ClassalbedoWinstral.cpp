//created by Manishankar Mondal

#include "ClassalbedoWinstral.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

ClassalbedoWinstral* ClassalbedoWinstral::klone(string name) const{
  return new ClassalbedoWinstral(name);
}

void ClassalbedoWinstral::decl(void) {

  Description = "'Incomplete code to calculate snowcover albedo from a method proposed by Winstral.'";

  declstatvar("Albedo", NHRU, "Albedo", "()", &Albedo);

  declstatdiag("Ab_t", NHRU, "steps since albedo refresh", "()", &Ab_t);

  decllocal("irdalb", NHRU, "ir_diffuse decay", "()", &irdalb);

  decllocal("vddalb", NHRU, "visible_diffuse decay", "()", &vdalb);

  decldiagparam("maxdecay", NHRU, "[0.25]", "0.1", "0.5","maximum decay", "()", &maxdecay);

  decldiagparam("power", NHRU, "[1.4]", "-2.0", "2.0", "power function", "()", &power);

  decldiagparam("decay_period", NHRU, "[5000]", "100", "20000", "time over albedo decays", "()", &decay_period);

  decldiagparam("refresh", NHRU, "[1.0]", "0.5", "50.0", "minimum sub-canopy snowfall to refresh albedo", "(mm)", &refresh);

  decldiagparam("Albedo_Bare", NHRU, "[0.17]", "0.0", "1.0","Initial albedo for bare ground", "()", &Albedo_Bare);


  declgetvar("*",  "SWE", "(mm)", &SWE);

  declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void ClassalbedoWinstral::init(void) {

  nhru = getdim(NHRU);

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