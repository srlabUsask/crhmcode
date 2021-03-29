//created by Manishankar Mondal

#include "ClassalbedoRichard.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM/ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;


ClassalbedoRichard* ClassalbedoRichard::klone(string name) const{
  return new ClassalbedoRichard(name);
}

void ClassalbedoRichard::decl(void) {

  Description = "'Calculates snow cover albedo from a method proposed by R.Essery.'";

  declstatvar("Albedo", TDim::NHRU, "Albedo", "()", &Albedo);

  decldiagparam("Albedo_Snow", TDim::NHRU, "[0.85]", "0.0", "1.0","Initial albedo for snow cover", "()", &Albedo_Snow);

  decldiagparam("Albedo_Bare", TDim::NHRU, "[0.17]", "0.0", "1.0","Initial albedo for bare ground", "()", &Albedo_Bare);

  decldiagparam("a1", TDim::NHRU, "[1.08e7]", "0.0", "1.0e8", "Albedo decay time constant for cold snow", "(s)", &a1);

  decldiagparam("a2", TDim::NHRU, "[7.2e5]", "0.0", "1.0e8", "Albedo decay time constant for melting snow", "(s)", &a2);

  decldiagparam("amin", TDim::NHRU, "[0.5]", "0.0", "1.0", "Minimum albedo for aged snow", "()", &amin);

  decldiagparam("amax", TDim::NHRU, "[0.84]", "0.0", "1.0", "Maximum albedo for fresh snow", "()", &amax);

  decldiagparam("smin", TDim::NHRU, "[10]", "0.0", "20", "Minimum snowfall to refresh snow albedo", "(mm/int)", &smin);

  declgetvar("*", "hru_tmean", "(" + string(DEGREE_CELSIUS) + ")", &T0);

  declgetvar("*",  "SWE", "(mm)", &SWE);

  declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void ClassalbedoRichard::init(void) {

  dt = 3600*24/Global::Freq;

  nhru = getdim(TDim::NHRU);

  for (hh = 0; hh < nhru; ++hh)
    if(SWE[hh] > 1.0)
      Albedo[hh] = Albedo_Snow[hh];
    else
      Albedo[hh] = Albedo_Bare[hh];

}

void ClassalbedoRichard::run(void) {

  for(hh = 0; chkStruct(); ++hh) {
    if(SWE[hh] > 1.0){

      if (T0[hh] < 0) // cold snow
        Albedo[hh] = Albedo[hh] - dt/a1[hh];
      else            // melting snow
        Albedo[hh] = (Albedo[hh] - amin[hh])*exp(-dt/a2[hh]) + amin[hh];

      Albedo[hh] = Albedo[hh] + (amax[hh] - Albedo[hh])*net_snow[hh]/smin[hh];

      if (Albedo[hh] < amin[hh]) Albedo[hh] = amin[hh];
      if (Albedo[hh] > amax[hh]) Albedo[hh] = amax[hh];
    }
    else
      Albedo[hh] = Albedo_Bare[hh];
  }
}