//created by Manishankar Mondal

#include "ClassFlowInSnow.h"
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


ClassFlowInSnow* ClassFlowInSnow::klone(string name) const{
  return new ClassFlowInSnow(name);
}

void ClassFlowInSnow::decl(void) {

  Description = "'Calculates Flow in Snow.'";

  declvar("Ksat_snow", TDim::NHRU, "saturated permeability of snow", "(m^2)", &Ksat_snow);

  declvar("K_snow", TDim::NHRU, "intrinsic permeability of snow", "(m^2)", &K_snow);

  declvar("u_down", TDim::NHRU, "Colbeck's downward flux of water flow in snow based on Darcy's Law", "(m/s)", &u_down);

  declvar("K_down", TDim::NHRU, "mass flow of Colbeck's downward flux in snow", "(m/s)", &K_down);

  declvar("K_slope", TDim::NHRU, "mass flow in snow along slope", "(m/s)", &K_slope);

  declvar("Meltrunoff_K", TDim::NHRU, "melt runoff storage constant", "(d)", &Meltrunoff_K);

  decldiag("In_storage", TDim::NHRU, "melt runoff in storage at the beginning of interval!", "(mm)", &In_storage);

  decldiag("runKstorage_var", TDim::NHRU, "modified value of runKstorage", "(d)", &runKstorage_var);


  declparam("S_I", TDim::NHRU, "[3.3]", "1.0", "7.0", "soil index", "()", &S_I);

  declparam("d_g", TDim::NHRU, "[3.0]", "0.0", "10.0", "snow grain diameter", "(mm)", &d_g);

  declparam("t_inhibit_flow", TDim::NHRU, "[-2.0]", "-15", "5", "threshold temperature of inhibit flow in snow; i.e. inhibit when lower snowpack temperature is below this threshold temperature", "(°C)", &t_inhibit_flow);

  declparam("runKstorage_winter", TDim::NHRU, "[2.0]", "0", "200.0", "runoff storage constant when lower snowpack temperature is below the threshold temperature", "(d)", &runKstorage_winter);

  declparam("runKstorage_summer", TDim::NHRU, "[2.0]", "0", "200.0", "runoff storage constant for snowcover free period", "(d)", &runKstorage_summer);

  declparam("Sr", TDim::NHRU, "[0.07]", "0.0", "1.0", "residual saturation of snow", "()", &Sr);

  declparam("hru_GSL", TDim::NHRU, "[0.0]", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "()", &hru_GSL);

  declparam("route_L", TDim::NHRU, "[200.0]", "0.01", "1.0E10", "routing length", "(m)", &route_L);

  declputparam("*", "runKstorage", "(d)", &runKstorage);


  declgetvar("*", "rho", "((kg/m^3))", &rho);

  declgetvar("*", "h2o_sat", "()", &h2o_sat);

  declgetvar("*", "T_s_l", "(°C)", &T_s_l);

  declgetvar("*", "z_s", "((kg/m^3))", &z_s);

}

void ClassFlowInSnow::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; chkStruct(); ++hh) {
    Ksat_snow[hh] = 0.0;
    K_snow[hh] = 0.0;
    u_down[hh] = 0.0;
    K_down[hh] = 0.0;
    K_slope[hh] = 0.0;
    Meltrunoff_K[hh] = 0.0;
    runKstorage[hh] = 0.0;
    In_storage[hh] = 0.0;
  }

  Netroute_module = (ClassModule*) FindModule_from_parameter("*", "runKstorage");
}

void ClassFlowInSnow::run(void) {
  const double UnitWidth =1.0, UnitArea = 1.1;
  for(hh = 0; chkStruct(); ++hh) {
    if(rho[hh] > 0){
      if(T_s_l[hh] >= t_inhibit_flow[hh] && h2o_sat[hh] > Sr[hh]){
        Ksat_snow[hh] = 0.077*sqr((d_g[hh]/1000))*exp(-7.8*(rho[hh]/1000));
        K_snow[hh] = Ksat_snow[hh]*(pow((h2o_sat[hh]-Sr[hh])/(1-Sr[hh]), S_I[hh]));
        u_down[hh] = K_snow[hh]*1000*9.8/0.001787;
        K_down[hh] = u_down[hh]*z_s[hh]*UnitWidth/UnitArea;
        K_slope[hh] = K_down[hh]*sin(hru_GSL[hh]*DEGtoRAD);
        Meltrunoff_K[hh] = route_L[hh]/(K_slope[hh])/(60ll*60ll*24ll);
        runKstorage[hh] = route_L[hh]/(K_slope[hh])/(60ll*60ll*24ll);
        if(Meltrunoff_K[hh] > runKstorage_winter[hh]) {
          Meltrunoff_K[hh] = runKstorage_winter[hh];
          runKstorage[hh] = runKstorage_winter[hh];
        }
        runKstorage_var[hh] = runKstorage[hh];
//        In_storage[hh] = Netroute_module->Function2(runKstorage, hh);

      }
      else {
        if(T_s_l[hh]<t_inhibit_flow[hh]||h2o_sat[hh]<=Sr[hh]){
          u_down[hh] = 0.0;
          Meltrunoff_K[hh] = runKstorage_winter[hh];
          runKstorage[hh] = runKstorage_winter[hh];
          runKstorage_var[hh] = runKstorage[hh];
          In_storage[hh] = Netroute_module->Function2(runKstorage, hh);
        }
      }
    }
    else {
      Meltrunoff_K[hh] = runKstorage_summer[hh];
      runKstorage[hh] = runKstorage_summer[hh];
      runKstorage_var[hh] = runKstorage[hh];
      In_storage[hh] = Netroute_module->Function2(runKstorage, hh);
    }
  } // for
}