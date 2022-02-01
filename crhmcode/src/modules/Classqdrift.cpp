//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "Classqdrift.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

Classqdrift* Classqdrift::klone(string name) const{
  return new Classqdrift(name);
}

void Classqdrift::decl(void) {

  Description = "'Generates the drift melt from hummock-covered hillslopes in the Arctic tundra. CRHM compatible.' \
                 'using using observation \"p\" original version. ' \
                 'using using variable \"hru_p\" to be CRHM compatible. '";

  Global::OBS_AS_IS = 1; // ClassModule uses only intvl for NFREQ observation reads

  declvar("SWE", TDim::NHRU, "mean snow water equivalent over HRU", "(mm)", &SWE);

  decllocal("driftmeltOrg", TDim::NHRU, "snow melt without delay", "(m^3/int)", &driftmelt); // pack

  declvar("driftmelt", TDim::NHRU, "snow melt with delay", "(m^3/int)", &driftmeltDly); // with delay

  decllocal("cumdriftmeltOrg", TDim::NHRU, "cumulative snow melt", "(km^3)", &cumdriftmelt); // pack

  declvar("driftmeltD", TDim::NHRU, "daily snow melt with delay", "(m^3/d)", &driftmeltD); // with delay

  declvar("snowmeltD", TDim::NHRU, "daily snow melt with delay", "(m^3/d)", &snowmeltD); // with delay

  declvar("cumdriftmelt", TDim::NHRU, "cumulative snow melt with delay", "(m^3)", &cumdriftmeltDly); // with delay


  declparam("DrainTo", TDim::NHRU, "[0]", "0", "20", " drift drain to hru, 0=NOWHERE, otherwise HRU# (1->MAXHRU)", "()", &DrainTo);

  declparam("InitSWE", TDim::NHRU, "[0.0]", "0", "1E3", "initial mean snow water equivalent", "(mm)", &InitSWE);

  declparam("length", TDim::NHRU, "[1]", "1", "1E4", "length normal to creek", "(m)", &length);

  declparam("meltstorage", TDim::NHRU, "[0]", "0", "20", "melt Storage", "(d)", &meltstorage);

  declparam("meltLag", TDim::NHRU, "[0]", "0", "48", "melt delay", "(h)", &meltLag);


  declgetvar("*", "Qm", "(MJ/m^2*int)", &Qm);


  variation_set = VARIATION_0;

  declreadobs("p", TDim::NOBS, "precipitation", "(mm/int)", &p, true); // share location

  declparam("Type", TDim::NHRU, "[NOTUSED]", "0", "2", "hru land type, 0=NOTUSED/1=DRIFT/2=HUMMOCK", "()", &Type);


  variation_set = VARIATION_1;

  declgetvar("*", "hru_p", "(mm/int)", &hru_p);


  variation_set = VARIATION_ORG;
}

void Classqdrift::init(void) {

  nhru = getdim(TDim::NHRU);

  Delaymelt = new ClassClark(driftmelt, driftmeltDly, meltstorage, meltLag, nhru);

  for (int hh = 0; hh < nhru; ++hh) {
    driftmelt[hh]    = 0.0;
    cumdriftmelt[hh] = 0.0;
    driftmeltDly[hh] = 0.0;
    driftmeltD[hh]   = 0.0;
    snowmeltD[hh]   = 0.0;
    cumdriftmeltDly[hh] = 0.0;

    SWE[hh] = InitSWE[hh];

    if(hh == 0) LogDebugT("Initial");

    if(variation == VARIATION_0 && Type[hh] != DRIFT)
      continue;  // drift

    double c = 0.0;
    if(SWE[hh] > 0.0)
      c = length[hh]*InitSWE[hh]/1E3;
    LogMessageA(hh, "(Drift  ) - water content (m^3) (m/m^2): ", c, length[hh]);
  }
}

void Classqdrift::run(void) {

  for (int hh = 0; hh < nhru; ++hh) {

    if((getstep() % Global::Freq) == 1) driftmeltD[hh] = 0.0; // reset beginning of day

    if(variation == VARIATION_0 && Type[hh] != DRIFT)
      continue;  // drift

    driftmelt[hh] = 0.0;

    if(SWE[hh] > 0.0) { // still drift

      if(Qm[hh] > 0.0) {
        double melt = Qm[hh]/334.4*1E3;

        if(melt > SWE[hh]){
          melt = SWE[hh];
          SWE[hh] = 0.0;
        }
        else
          SWE[hh] -= melt;

        double lastcumdriftmelt = cumdriftmelt[hh];  // following avoids round off error
        cumdriftmelt[hh] = length[hh]*InitSWE[hh]*(1.0 - sqr(SWE[hh]/InitSWE[hh])); // (mm.l)
        driftmelt[hh] = (cumdriftmelt[hh] - lastcumdriftmelt)/1E3; // (m3/Int)
      }
    }

    if(variation == VARIATION_ORG){
      if(p != NULL) // handle precipitation
        driftmelt[hh] += (p[0]*length[hh]);
    }
    else if(variation == VARIATION_1)
      driftmelt[hh] += (hru_p[0]*length[hh]);

  } // for loop

  Delaymelt->DoClark();

  for (hh = 0; hh < nhru; ++hh) {
    if(variation == VARIATION_ORG && Type[hh] != DRIFT)
      continue;  // drift
    cumdriftmeltDly[hh] += driftmeltDly[hh];
    driftmeltD[hh] += driftmeltDly[hh];
    snowmeltD[hh] = driftmeltD[hh];
  }
}

void Classqdrift::finish(bool good) {

  for (hh = 0; hh < nhru; ++hh) {

    if(hh == 0) LogDebugT("Final");

    if(variation == VARIATION_ORG && Type[hh] != DRIFT)
      continue;  // drift

    double c = 0.0;
    if(SWE[hh] > 0.0)
      c = length[hh]*InitSWE[hh]*sqr(SWE[hh]/InitSWE[hh])/1E3;
    LogMessageA(hh, "(Drift  ) - water content (m^3) (m/m^2): ", c, length[hh]);
    LogMessageA(hh, "(Drift  ) - water storage (m^3) (m/m^2): ", Delaymelt->Left(hh), length[hh]);
    LogDebug(" ");
  }

  delete Delaymelt;
}
