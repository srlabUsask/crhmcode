//created by Manishankar Mondal

#include "Classcontribution.h"
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

Classcontribution* Classcontribution::klone(string name) const{
  return new Classcontribution(name);
}

void Classcontribution::decl(void) {

  Description = "'calculates contributing area.'";

  declvar("contrib_area", NHRU, "contributing area", "(mm^2)", &contrib_area);

  declvar("pre_contrib_area", NHRU, "maximum contributing area of HRU before transfer", "(mm^2)", &pre_contrib_area);

  declvar("connected", NHRU, "connected HRUs", "()", &connected);

  declvar("N_connected", NHRU, "number of connected HRUs", "()", &N_connected);

  declvar("connectedTo", NHRU, "connected HRUs", "()", &connectedTo);

  declvar("Results", NDEFN, "calulated distributions", "()", &Results, &Results_lay, nhru);

  decllocal("distrib_sum", NHRU, "HRU distribution sum", "()", &distrib_sum);

  decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);



  declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0","Maximum depression storage", "(mm)", &Sdmax);

  declparam("distrib_Route", NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs", "()", &distrib, &distrib_hru, nhru);

  declparam("distrib_Basin", NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_Route')", "()", &distrib_Basin);


  soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);

  declgetvar("*", "Sd", "(mm)", &Sd);

}

void Classcontribution::init(void) {

  if(soil_runoffDiv > 1){
    string S = "Netroute:  \"soil_runoff\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), WARNING);
    LogError(TExcept);
  }

  nhru = getdim(NHRU);
  for(hh = 0; hh < nhru; ++hh) {
    contrib_area[hh] = 0.0;
    pre_contrib_area[hh] = 0.0;
  }
}

void Classcontribution::run(void) {

  long  nstep = getstep()%Global::Freq;

  if(getstep() == 1){
    for(hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
      distrib_sum[hh] = 0.0;

      for(long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
        if(distrib_hru[hh][hhh] < 0.0)
          const_cast<double **> (distrib_hru) [hh][hhh] = -distrib_hru[hh][hhh]*hru_area[hh];
        distrib_sum[hh] += distrib_hru[hh][hhh];
      }

      if(distrib_sum[hh] <= 0 && distrib_Basin[hh] <= 0.0){
        const_cast<double *> (distrib_Basin) [hh] = 1;
    }

    distrib_sum[hh] += distrib_Basin[hh];

    }
  }

  for(hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
    if(soil_runoffDiv == 1) // interval value
       soil_runoff_Buf[hh] = soil_runoff[hh];

    contrib_area[hh] = hru_area[hh]; // assign values
    pre_contrib_area[hh] = 0.0; // reset
    connected[hh] = 0.0; // clear values
    N_connected[hh] = 0; // clear values
    connectedTo[hh] = 0; // clear values
    for(long hhh = 0; chkStruct(hhh); ++hhh)
      Results_lay[hhh][hh] = 0.0;
  } // hh

  for(hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
    for(long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
      if((Sd[hh] >= Sdmax[hh] || soil_runoff_Buf[hh] > 0.0) && distrib_hru[hh][hhh] > 0.0){  //
        Results_lay[hhh][hh] = distrib_hru[hh][hhh]-1; // parameter value used as index
        connected[hh] += distrib_hru[hh][hhh]; // parameter value only
        connectedTo[hh] = hhh;
      }
    } // hhh
  } // hh

  for(long hh = 6; chkStruct(hh); ++hh) {
    if(connected[hh]){
      pre_contrib_area[hh] = contrib_area[hh];
      contrib_area[connectedTo[hh]] += contrib_area[hh];
      contrib_area[hh] = 0.0;
      ++N_connected[connectedTo[hh]];
      ++N_connected[nhru-1];
    }
  } // hh

  double sum2 = 0;
  for(long hh = 6; chkStruct(hh); ++hh) {
    sum2 += contrib_area[hh];
  } // hh

  if(nstep == 0){ // end of every day
    for(hh = 0; chkStruct(); ++hh) {
      if(soil_runoffDiv > 1) // daily value - ready for next day
         soil_runoff_Buf[hh] = soil_runoff[hh]/soil_runoffDiv;
    }
  }
}


void Classcontribution::finish(bool good) {
  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (intcp)'  contrib_area  (mm) (mm*hru) (mm*hru/basin): ").c_str(), contrib_area[hh], hru_area[hh], basin_area[0]);
  }
  LogDebug(" ");
}