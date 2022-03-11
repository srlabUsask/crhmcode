//created by Manishankar Mondal

#include "ClassMeltRunoff_Kstorage.h"

#include <algorithm>
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM/ClassCRHM.h"
#include "../newmodules/SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

ClassMeltRunoff_Kstorage* ClassMeltRunoff_Kstorage::klone(string name) const{
  return new ClassMeltRunoff_Kstorage(name);
}

void ClassMeltRunoff_Kstorage::decl(void) {

  Description = "'Calculates Melt Runoff Kstorage.'";

  declvar("Ksat", TDim::NHRU, "saturated hydraulic conductivity of porous snow media", "(m/s)", &Ksat);

  declvar("Meltrunoff_K", TDim::NHRU, "melt runoff storage constant", "(d)", &Meltrunoff_K);

  decldiag("In_storage", TDim::NHRU, "melt runoff in storage at the beginning of interval!", "(mm)", &In_storage);


  declparam("d_g", TDim::NHRU, "[3.0]", "0.0", "10.0", "snow grain diameter", "(mm)", &d_g);

  declparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

  declparam("inhibit_MeltRunoff_Kstorage", TDim::NHRU, "[0]", "0", "1", "inhibit MeltRunoff_Kstorage correction, 1 -> inhibit", "()", &inhibit_MeltRunoff_Kstorage);

  declputparam("*", "runKstorage", "(d)", &runKstorage);


  declparam("route_L", TDim::NHRU, "[200.0]", "0.01","1.0E10", "routing length", "(m)", &route_L);

  declparam("hru_GSL", TDim::NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string(DEGREE) + ")", &hru_GSL);


  declgetvar("*", "rho", "((kg/m^3))", &rho);

}

void ClassMeltRunoff_Kstorage::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; chkStruct(); ++hh) {
    Ksat[hh] = 0.0;
    Meltrunoff_K[hh] = 0.0;
    In_storage[hh] = 0.0;
  }

  Netroute_module = (ClassModule*) FindModule_from_parameter("*", "runKstorage");
}

void ClassMeltRunoff_Kstorage::run(void) {

//  if(getstep()%Global::Freq != 0) return;

  for(hh = 0; chkStruct(); ++hh) {
      if(rho[hh] > 0 && !inhibit_MeltRunoff_Kstorage[hh]){
        Ksat[hh] = 0.077*pow(((d_g[hh]/2.0)/1000), 2.0)*9.8/0.000001787*exp(-0.0078*rho[hh]);
          if((hru_GSL[hh]*DEGtoRAD) > 0) {
             Meltrunoff_K[hh] = route_L[hh]/(Ksat[hh]*tan(hru_GSL[hh]*DEGtoRAD))/(86400.0);
             runKstorage[hh] = route_L[hh]/(Ksat[hh]*tan(hru_GSL[hh]*DEGtoRAD))/(86400.0);
          }
          else {
             Meltrunoff_K[hh] = route_L[hh]/Ksat[hh]/(86400.0);
             runKstorage[hh] = route_L[hh]/Ksat[hh]/(86400.0);
          }

        In_storage[hh] = Netroute_module->Function2(runKstorage, hh);
      }
  }
}