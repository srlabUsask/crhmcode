//created by Manishankar Mondal

#include "Classalbedo.h"
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


Classalbedo* Classalbedo::klone(string name) const{
  return new Classalbedo(name);
}

void Classalbedo::decl(void) {

  Description = "'Estimates the snow albedo during the winter and the melt period. Use with \"ebsm\".'";

  declstatvar("Albedo", TDim::NHRU, "Albedo()", "()", &Albedo);

  declvar("meltflag", TDim::NHRU, "meltflag = 1 - melt true", "()", &meltflag);

  declvar("winter", TDim::NHRU, "winter = 1 - true", "()", &winter);

  declvar("net_snowD", TDim::NHRU, "daily snow fall", "(mm/d)", &net_snowD);

  declvar("newsnowcnt", TDim::NHRU, "snow age count", "()", &newsnowcnt);


  decldiagparam("Albedo_bare", TDim::NHRU, "[0.17]", "0.0", "1.0", "albedo for bare ground", "()", &Albedo_bare); // pseudo
  decldiagparam("Albedo_snow", TDim::NHRU, "[0.85]", "0.0", "1.0", "albedo for fresh snow covered ground", "()", &Albedo_snow); // pseudo

  declparam("hru_lat", TDim::NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "("+string(DEGREE)+")", &hru_lat);

  declgetvar("*",    "hru_tmax", "("+string(DEGREE_CELSIUS)+")", &hru_tmax);
  declgetvar("*",    "hru_tmin", "(" + string(DEGREE_CELSIUS) + ")", &hru_tmin);
  declgetvar("*",    "hru_newsnow", "()", &hru_newsnow);
  declgetvar("*",    "SWE", "(mm)", &SWE);
  declgetvar("*",    "QdroD", "(MJ/m^2*d)", &QdroD);
  declgetvar("*",    "net_snow", "(mm/int)", &net_snow);
}

void Classalbedo::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; hh < nhru; ++hh) {
    if(SWE[hh] > 5.0) {
      Albedo[hh]    = Albedo_snow[hh];
      winter[hh]    = 1;
    }
    else{
      Albedo[hh]    = Albedo_bare[hh];
      winter[hh]    = 0;
    }
    net_snowD[hh] = 0.0;
    meltflag[hh]  = 0;
    newsnowcnt[hh] = 0;
  }
}

void Classalbedo::run(void) {

  long nstep, jday;

  nstep = getstep()%Global::Freq;

  for(hh = 0; chkStruct(); ++hh){ // calculate daily snow accumulation

    if(nstep == 1 || Global::Freq == 1) // beginning of every day
      net_snowD[hh] = net_snow[hh];
    else
      net_snowD[hh]+= net_snow[hh];
  }

  if(nstep == 0 || Global::Freq == 1){ // end of every day

    jday = julian("now");

      for(hh = 0; chkStruct(); ++hh) {
        double hemisphere = (hru_lat[hh] < 0.0);
        if((!hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE[hh] > 5.0) {  // changed
          winter[hh] = 1;
          Albedo[hh] = Albedo_snow[hh];
        }
      continue;
    }

    for(hh = 0; chkStruct(); ++hh) {
      meltflag[hh] = 0;
      if(hru_newsnow[hh] > 0)
        newsnowcnt[hh] = 0;
      else
        newsnowcnt[hh] = newsnowcnt[hh]+1;

      if(SWE[hh] <= 0.0) {
        Albedo[hh] = Albedo_bare[hh];
        winter[hh] = 0;
        meltflag[hh] = 0;
      }
      else { // SWE[hh] > 0.0
        double DR = 0.071;

        if(SWE[hh] > 60.0 && Albedo[hh] > 0.65)
          DR = 0.015;

        if(SWE[hh] > 60.0 && Albedo[hh] < 0.65)
          DR = 0.001;

        if(net_snowD[hh] > 0.25) { // SF = SWE*2 if density 0.005 (0.5cm)
          Albedo[hh] = Albedo[hh] + net_snowD[hh]*0.1*2.0; // daily value
          if(Albedo[hh] > Albedo_snow[hh])
            Albedo[hh] = Albedo_snow[hh];
          continue;
        }

        double Qnc = -0.371 + 5.22*QdroD[hh]*(1 - Albedo[hh]);

        if(hru_tmax[hh] < -6.0 && Qnc < 1.0)
          winter[hh] = 1;

        if(Albedo[hh] <= Albedo_bare[hh])
          winter[hh] = 0;

        if(winter[hh] == 1) {
          if(newsnowcnt[hh] < 3) {
            Albedo[hh] = Albedo[hh] - 0.05;
            continue;
          }
          double MT = -0.064*jday + 6.69;

          if(hru_tmin[hh] > -4.0 || Qnc > 1.0 && hru_tmax[hh] > 0.0 ||
                  hru_tmax[hh] > MT && Qnc > -0.5) {
            Albedo[hh] = Albedo[hh] - DR;

            if(Albedo[hh] < Albedo_bare[hh])
              Albedo[hh] = Albedo_bare[hh];

            meltflag[hh] = 1;
          }
          else
            if(Albedo[hh] > 0.65)
              Albedo[hh] = Albedo[hh] - 0.006;
        }
        else {
          Albedo[hh] = Albedo[hh] - 0.02;
          if(Albedo[hh] < Albedo_bare[hh])
            Albedo[hh] = Albedo_bare[hh];
          meltflag[hh] = 1;
        }

      } // SWE > 0.0
    } // for HRU
  } //end of every day
}