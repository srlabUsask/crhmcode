//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassMeltRunoff_Lag.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassMeltRunoff_Lag* ClassMeltRunoff_Lag::klone(string name) const{
  return new ClassMeltRunoff_Lag(name);
}

void ClassMeltRunoff_Lag::decl(void) {

  Description = "'Calculates Melt Runoff.'";

  declvar("Tf", TDim::NHRU, "time lag after water percolated snowcover", "()", &Tf);  // minutes

  decldiag("In_Lagstorage", TDim::NHRU, "melt runoff in Lag storage at the beginning of interval!", "(mm)", &In_Lagstorage);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("inhibit_MeltRunoff_Lag", TDim::NHRU, "[0]", "0", "1", "inhibit MeltRunoff_Lag correction, 1 -> inhibit", "()", &inhibit_MeltRunoff_Lag);

  declputparam("*", "runLag", "(h)", &runLag);


  declgetvar("*", "snowmelt_int", "(mm)", &snowmelt_int);

}

void ClassMeltRunoff_Lag::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; chkStruct(); ++hh) {
    Tf[hh] = 0.0;
    In_Lagstorage[hh] = 0.0;
  }

  Netroute_module = (ClassModule*) FindModule_from_parameter("*", "runKstorage");
}

void ClassMeltRunoff_Lag::run(void) {

//  if(getstep()%Global::Freq != 0) return;

  for(hh = 0; chkStruct(); ++hh)
    if(!inhibit_MeltRunoff_Lag[hh]){
      if(snowmelt_int[hh] > 0.0)
        Tf[hh] = 250.0*pow(hru_area[hh], 0.17)*pow(snowmelt_int[hh], -0.5)/60.0;

      if(snowmelt_int[hh] <= 0.0)
        Tf[hh] = 0.0;

    In_Lagstorage[hh] = Netroute_module->Function1(Tf, hh);
  }
}
