//created by Manishankar Mondal

#include "Classwinter_meltflag.h"
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

Classwinter_meltflag* Classwinter_meltflag::klone(string name) const{
  return new Classwinter_meltflag(name);
}

void Classwinter_meltflag::decl(void) {

  Description = "'Estimates the snow albedo during the winter and the melt period. Use with \"ebsm\".'";

  declvar("meltflag", TDim::NHRU, "meltflag = 1 - melt true", "()", &meltflag);

  declvar("winter", TDim::NHRU, "winter = 1 - true", "()", &winter);

  declparam("hru_lat", TDim::NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(°)", &hru_lat);

  declgetvar("*",    "hru_tmax", "(°C)", &hru_tmax);
  declgetvar("*",    "hru_tmin", "(°C)", &hru_tmin);
  declgetvar("*",    "SWE", "(mm)", &SWE);
  declgetvar("*",    "QdroD", "(MJ/m^2*d)", &QdroD);
  declgetvar("*",    "Albedo", "()", &Albedo);
}

void Classwinter_meltflag::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; hh < nhru; ++hh) {
    if(SWE[hh] > 5.0)
      winter[hh] = 1;
    else
      winter[hh]    = 0;

    meltflag[hh]  = 0;
  }
}

void Classwinter_meltflag::run(void) {

  long nstep, jday;

  nstep = getstep()%Global::Freq;

  if(nstep == 0 || Global::Freq == 1){ // end of every day

    jday = julian("now");

      for(hh = 0; chkStruct(); ++hh) {
        double hemisphere = (hru_lat[hh] < 0.0);
        if((!hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE[hh] > 5.0) {  // changed
          winter[hh] = 1;
        }
      continue;
    }

    for(hh = 0; chkStruct(); ++hh) {
      meltflag[hh] = 0;

      if(SWE[hh] <= 0.0) {
        winter[hh] = 0;
        meltflag[hh] = 0;
      }
      else { // SWE[hh] > 0.0

        double Qnc = -0.371 + 5.22*QdroD[hh]*(1 - Albedo[hh]);

        if(hru_tmax[hh] < -6.0 && Qnc < 1.0)
          winter[hh] = 1;

        if(winter[hh] == 1) {
          double MT = -0.064*jday + 6.69;

          if(hru_tmin[hh] > -4.0 || Qnc > 1.0 && hru_tmax[hh] > 0.0 || hru_tmax[hh] > MT && Qnc > -0.5) {
            meltflag[hh] = 1;
          }
        }
        else
          meltflag[hh] = 1;

      } // SWE > 0.0
    } // for HRU
  } //end of every day
}