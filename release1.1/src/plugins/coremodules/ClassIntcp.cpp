//created by Manishankar Mondal

#include "ClassIntcp.h"
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


Classintcp* Classintcp::klone(string name) const{
  return new Classintcp(name);
}

void Classintcp::decl(void) {

  Description = "'Substitutes for canopy in open environment - implements variable name change. hru_snow --> net_snow, hru_rain --> net_rain.'";

  declvar("net_rain", NHRU, "hru_rain minus interception", "(mm/int)", &net_rain);

  declstatdiag("cumnet_rain", NHRU, "cumulative hru_rain minus interception", "(mm)", &cumnet_rain);

  declvar("net_snow", NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

  declstatdiag("cumnet_snow", NHRU, "cumulative hru_snow minus interception", "(mm)", &cumnet_snow);

  declvar("net_p", NHRU, "hru_precipitation (rain and/or snow) less interception", "(mm/int)", &net_p);

  declvar("intcp_evap", NHRU, "HRU Evaporation from interception", "(mm/int)", &intcp_evap);


  declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);
  declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);
  declgetvar("*", "hru_p", "(mm/int)",  &hru_p);

}

void Classintcp::init(void) {

  nhru = getdim(NHRU);
  for(hh = 0; hh < nhru; ++hh) {
    cumnet_rain[hh] = 0.0;
    cumnet_snow[hh] = 0.0;
  }
}

void Classintcp::run(void) {

  for(hh = 0; chkStruct(); ++hh) {
    net_p[hh] = hru_p[hh];
    net_snow[hh] = hru_snow[hh];
    net_rain[hh] = hru_rain[hh];
    cumnet_rain[hh] += net_rain[hh];
    cumnet_snow[hh] += net_snow[hh];
    intcp_evap[hh] = 0.0;
  }
}

void Classintcp::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (intcp)'  cumnetrain  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (intcp)'  cumnetsnow  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_snow[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
  LogDebug(" ");
}