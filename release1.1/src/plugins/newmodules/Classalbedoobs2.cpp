//created by Manishankar Mondal

#include "Classalbedoobs2.h"
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

Classalbedoobs2* Classalbedoobs2::klone(string name) const{
  return new Classalbedoobs2(name);
}

void Classalbedoobs2::decl(void) {

  Description = "'Every interval sets the variable Albedo to the value of the observation Albedo_obs with enhancements.'";

  declstatvar("Albedo", NHRU, "Albedo()", "()", &Albedo);

  declvar("meltflag", NHRU, "meltflag = 1 - melt true", "()", &meltflag);

  declvar("winter", NHRU, "winter = 1 - true", "()", &winter);

  declvar("net_snowD", NHRU, "daily snow fall", "(mm/d)", &net_snowD);

  declvar("newsnowcnt", NHRU, "snow age count", "()", &newsnowcnt);


  decldiagparam("Albedo_bare", NHRU, "[0.17]", "0.0", "1.0", "albedo for bare ground", "()", &Albedo_bare); // pseudo

  decldiagparam("Albedo_snow", NHRU, "[0.85]", "0.0", "1.0", "albedo for fresh snow covered ground", "()", &Albedo_snow); // pseudo

  declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(°)", &hru_lat);

  declreadobs("Albedo_obs", NHRU, "albedo observation", "()", &Albedo_obs, HRU_OBS_Q, true);


  declgetvar("*",    "hru_tmax", "(°C)", &hru_tmax);
  declgetvar("*",    "hru_tmin", "(°C)", &hru_tmin);
  declgetvar("*",    "hru_newsnow", "()", &hru_newsnow);
  declgetvar("*",    "SWE", "(mm)", &SWE);
  declgetvar("*",    "QdroD", "(MJ/m^2*d)", &QdroD);
  declgetvar("*",    "net_snow", "(mm/int)", &net_snow);
}

void Classalbedoobs2::init(void) {

  nhru = getdim(NHRU);

  if(Albedo_obs == NULL){
    CRHMException TExcept("\"albedo_obs\". No observation albedo data!  Using calculated albedo instead.", WARNING);
    LogError(TExcept);
  }
  else{
    CRHMException TExcept("\"albedo_obs\". Using observation albedo data!.", WARNING);
    LogError(TExcept);
  }

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

void Classalbedoobs2::run(void) {

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
      float hemisphere = (hru_lat[hh] < 0.0);
      if((!hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE[hh] > 5.0) {  // changed
        winter[hh] = 1;
        Albedo[hh] = Albedo_snow[hh];
      }
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

        float Qnc = -0.371 + 5.22*QdroD[hh]*(1 - Albedo[hh]);

        float MT = -0.064*jday + 6.69;

        if(hru_tmax[hh] < -6.0 && Qnc < 1.0){
          winter[hh] = 1;
          if(hru_tmin[hh] > -4.0 || Qnc > 1.0 && hru_tmax[hh] > 0.0 || hru_tmax[hh] > MT && Qnc > -0.5)
            meltflag[hh] = 1;
        }

        if(Albedo_obs)
          Albedo[hh] = Albedo_obs[hh]; // Albedo set internally by routine
        else
          albedo(jday, Qnc); // value

        if(!winter[hh]){
          if(Albedo[hh] < Albedo_bare[hh])
            Albedo[hh] = Albedo_bare[hh];
          meltflag[hh] = 1;
        }
      } // SWE > 0.0
    } // for HRU
  } //end of every day
}

void Classalbedoobs2::albedo(long jday, float Qnc) {

  float DR = 0.071;

  if(SWE[hh] > 60.0 && Albedo[hh] > 0.65)
    DR = 0.015;

  if(SWE[hh] > 60.0 && Albedo[hh] < 0.65)
    DR = 0.001;

  if(net_snowD[hh] > 0.25) { // SF = SWE*2 if density 0.005 (0.5cm)
    Albedo[hh] = Albedo[hh] + net_snowD[hh]*0.1*2.0; // daily value
    if(Albedo[hh] > Albedo_snow[hh])
      Albedo[hh] = Albedo_snow[hh];
  }

  if(winter[hh] == 1){

    if(newsnowcnt[hh] < 3) {
      Albedo[hh] = Albedo[hh] - 0.05;
    }
    else{
      float MT = -0.064*jday + 6.69;

      if(hru_tmin[hh] > -4.0 || Qnc > 1.0 && hru_tmax[hh] > 0.0 ||
              hru_tmax[hh] > MT && Qnc > -0.5) {
        Albedo[hh] = Albedo[hh] - DR;

      }
      else
        if(Albedo[hh] > 0.65)
          Albedo[hh] = Albedo[hh] - 0.006;
    }
  }
  else
    Albedo[hh] = Albedo[hh] - 0.02;
}