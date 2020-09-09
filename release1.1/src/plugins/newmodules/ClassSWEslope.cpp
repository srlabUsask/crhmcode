//created by Manishankar Mondal

#include "ClassSWEslope.h"
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

ClassSWEslope* ClassSWEslope::klone(string name) const{
  return new ClassSWEslope(name);
}

void ClassSWEslope::decl(void) {

  Description = "'calculates SWE slope transport (Bernhardt & Schulz, 2010).' \
                 'Standard version for use with the glacier module,' \
                 'Standard version for use without the glacier module. Identical code but links to snowmeltD.'";


  variation_max = VARIATION_1;


  declvar("SWE_out", NHRU, "outgoing snow slide transport SWE", "(mm/int)", &SWE_out);

  declvar("SWE_in", NHRU, "incoming snow slide transport SWE", "(mm/int)", &SWE_in);

  declstatdiag("cumSWE_in", NHRU, "incoming cumulative Slide transport SWE from other HRU", "(mm)", &cumSWE_in);

  declstatdiag("cumSWE_out", NHRU, "outgoing cumulative Slide transport SWE to other HRU", "(mm)", &cumSWE_out);

  declvar("Hd", NHRU, "SWE holding depth of snow", "(mm)", &Hd);

/* parameters */

  declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(°)", &hru_GSL);

  declparam("order", NHRU, "[1,2,3,4,5!]", "1","1000", "sequence of HRUs for slide routing ", "()", &order);

  declparam("Disable_SWEslope", NHRU, "[0]", "0","1", "set to 1 to disable module", "()", &Disable_SWEslope);

  declparam("Hd_min", NHRU, "[50.0]", "0", "750", "minimum SWE holding depth", "(mm)", &Hd_min);

  declparam("use_rho", NHRU, "[1]", "0", "1", "0: user defined snow density, 1: use rho from Snobal", "()", &use_rho);

  declparam("snow_density", NHRU, "[100]", "50", "750", "density of snow", "(kg/m^3)", &snow_density);

  declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("distrib_SWEslope", NDEFN, "[0.0]", "0.0", "1.0E6.0", "distribute this HRU iceflow to these HRUs. Source HRU can include itself in the re-distribution", "()", &distrib_SWEslope, &distrib_hru, nhru);


  declputvar("*", "SWE", "(mm)", &SWE);
  declgetvar("*", "rho", "(kg/m^3)", &rho);
}

void ClassSWEslope::init(void) {

  nhru = getdim(NHRU);

  for (hh = 0; hh < nhru; ++hh){
    SWE_in[hh] = 0.0;
    SWE_out[hh] = 0.0;
    cumSWE_in[hh] = 0.0;
    cumSWE_out[hh] = 0.0;
    Hd[hh] = 0.0;
  }
}

void ClassSWEslope::run(void) {

  for (long hh = 0; chkStruct(hh); ++hh){
    SWE_in[hh] = 0.0;
    SWE_out[hh] = 0.0;
    Hd[hh] = 0.0;
  }

  for (long hhh = 0; chkStruct(hhh); ++hhh) {
    if(Disable_SWEslope[hhh])
      continue;

    hh = order[hhh] - 1; // do HRUs in the desired sequence

    if(hru_GSL[hh] > 25.0){
      float den_snow;
      if (use_rho[hh])
        den_snow = rho[hh];
      else
        den_snow = snow_density[hh];

      Hd[hh] = 3178.4*pow(hru_GSL[hh], -1.998)*den_snow; // equation in mm SWE and slope in degrees

      if(Hd[hh] > Hd_min[hh] && SWE[hh] > Hd[hh]){

        float Used, total = 0.0;
        float Amount = SWE[hh];

        for(long To = 0; chkStruct(To); ++To) // distribute SWE flow of this HRU
          total += distrib_hru[hh][To]; // includes itself
          if(total == 0 || total <= distrib_hru[hh][hh]) break; // no distribution

        for(long To = 0; chkStruct(To); ++To) { // distribute SWE outflow of HRU
          if(hh != To && Amount > 0.0 && distrib_hru[hh][To] > 0.0){
            Used = Amount*distrib_hru[hh][To]/total;
            SWE_out[hh] = Used;
            cumSWE_out[hh] += Used;
            SWE[hh] -= Used;

            Used = Used*hru_area[hh]/hru_area[To]; // adjust to area of destination HRU
            SWE[To] += Used;
            SWE_in[To] = Used;
            cumSWE_in[To] += Used;
          } // if
        } // end for (hhh)
      } // end of moving
    } // slide possible
  } // end for (hh)
}

void ClassSWEslope::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (SWESlope)' cumSWE_in (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSWE_in[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SWESlope)' cumSWE_out (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSWE_out[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}