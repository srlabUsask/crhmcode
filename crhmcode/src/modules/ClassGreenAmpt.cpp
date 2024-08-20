/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassGreenAmpt.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;



ClassGreenAmpt* ClassGreenAmpt::klone(string name) const{
  return new ClassGreenAmpt(name);
}

void ClassGreenAmpt::decl(void) {

  Description = "'Summer Green Ampt model.'";

  declvar("infil", TDim::NHRU,"Potential amount of rain water infiltrating the soil on each HRU", "(mm/int)", &infil);

  declstatdiag("cuminfil", TDim::NHRU, "cumulative potential rain water infiltration on each HRU", "(mm)", &cuminfil);

  declvar("runoff", TDim::NHRU, "rainfall runoff", "(mm/int)", &runoff);

  declstatdiag("cumrunoff", TDim::NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

  declvar("snowinfil", TDim::NHRU, "interval snowmelt infiltration", "(mm/int)", &snowinfil);

  declstatdiag("cumsnowinfil", TDim::NHRU, "cumulative snowmelt infiltration", "(mm)", &cumsnowinfil);

  declvar("meltrunoff", TDim::NHRU, "interval snowmelt runoff", "(mm/int)", &meltrunoff);

  declstatvar("cummeltrunoff", TDim::NHRU, "cumulative snowmelt runoff", "(mm/int)", &cummeltrunoff);


  decllocal("k", TDim::NHRU, "saturated hydraulic conductivity", "(mm/h)", &k);

  declstatdiag("F0", TDim::NHRU, "cumulative infiltation at the beginning of the time interval", "(mm)", &F0);

  decllocal("f0", TDim::NHRU, "infiltration rate at the beginning of the time interval", "(mm/h)", &f0);

  declstatdiag("F1", TDim::NHRU, "cumulative infiltration at the end of the time interval", "(mm)", &F1);

  decllocal("f1", TDim::NHRU, "infiltration rate at the end of the time interval", "(mm/h)", &f1);

  decllocal("dthbot", TDim::NHRU, "fraction value of soil water deficit", "()", &dthbot);

  decllocal("psidthbot", TDim::NHRU, "capillary suction at the fraction value of soil water deficit", "(mm)", &psidthbot);


  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("soil_type", TDim::NHRU, "[4]", "0", "12",
        "water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
        " 0 - 12", "()", &soil_type);

  declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0",
        "Maximum available water holding capacity of soil profile."//
        "Soil profile is surface to bottom of rooting zone", "(mm)", &soil_moist_max);

  declparam("soil_moist_init", TDim::NHRU, "[187.0]", "0.0", "2500.0",
        "Initial value of available water in soil profile", "(mm)", &soil_moist_init);


  declgetvar("*",  "net_rain", "(mm/int)", &net_rain);

  declgetvar("*",  "snowmeltD", "(mm/d)", &snowmelt);

  declputvar("*",  "soil_moist", "(mm)", &soil_moist);


}

void ClassGreenAmpt::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; hh < nhru; ++hh) {
    cuminfil[hh] = 0.0;
    cumrunoff[hh] = 0.0;
    cumsnowinfil[hh] = 0.0;
    cummeltrunoff[hh] = 0.0;

    F1[hh]        = soil_moist_max[hh];
    k[hh]         = soilproperties[soil_type[hh]][KSAT];
    dthbot[hh]    = (1.0 - soil_moist_init[hh]/soil_moist_max[hh]);
    psidthbot[hh] = soilproperties[soil_type[hh]][PSI]*dthbot[hh];
    f1[hh]        = calcf1(F1[hh], psidthbot[hh]);
  }
}

void ClassGreenAmpt::run(void) {

// greenampt routine

  for(hh = 0; chkStruct(); ++hh) {

    infil[hh] = 0.0;
    runoff[hh] = 0.0;
    snowinfil[hh] = 0.0;
    meltrunoff[hh] = 0.0;

    double melt = snowmelt[hh]/Global::Freq;
    double All = net_rain[hh] + melt;

    if(All > 0.0) {

      garain = All; // precipitation/interval
      intensity = All*Global::Freq/24.0; // convert to mm/h

      if(garain > 0.0) {
        if(soil_type[hh] == 12){ // handle pavement separately
          runoff[hh] =  garain;
        }
        else if(soil_type[hh] == 0 || soil_moist[hh] <= 0.0){ // handle water separately
          infil[hh] =  garain;
//          cuminfil[hh] += infil[hh];
        }
        else {
          F1[hh] = soil_moist[hh];
          dthbot[hh]    = (1.0 - soil_moist[hh]/soil_moist_max[hh]);
          psidthbot[hh] = soilproperties[soil_type[hh]][PSI]*dthbot[hh];

          infiltrate();

          infil[hh] = F1[hh] - F0[hh];
//          cuminfil[hh] += infil[hh];

          if(pond > 0.0){

            runoff[hh] = pond;
          }
        }
      }

      if(melt >= infil[hh]){
        snowinfil[hh] = melt;
        infil[hh] = 0.0;
      }
      else if(melt > 0.0){
        snowinfil[hh] = melt;
        infil[hh] -= snowinfil[hh];
      }
      else
        snowinfil[hh] = 0.0;

      if(melt - snowinfil[hh] >= pond){
        meltrunoff[hh] = melt - snowinfil[hh];
        runoff[hh] = 0.0;
      }
      else if(melt - snowinfil[hh] > 0.0){
        meltrunoff[hh] = melt - snowinfil[hh];
        runoff[hh] = pond - meltrunoff[hh];
      }
      else{
        meltrunoff[hh] = 0.0;
        runoff[hh] = pond;
      }

      cuminfil[hh] += infil[hh];
      cumrunoff[hh] += runoff[hh];

      cumsnowinfil[hh] += snowinfil[hh];
      cummeltrunoff[hh] += meltrunoff[hh];

    } // if(net_rain[hh] + net_snow[hh] > 0.0) greenampt routine
  } // for
}

void ClassGreenAmpt::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (GreenAmpt)' cuminfil(rain)      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (GreenAmpt)' cumrunoff(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (GreenAmpt)' cumsnowinfil(snow)  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (GreenAmpt)' cummeltrunoff(snow) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}

void ClassGreenAmpt::infiltrate(void){

  F0[hh] = F1[hh];

  if(soil_type[hh] == 0) { // water!
    pond += garain;
    return;
  }
  pond = 0.0;

  f0[hh] = calcf1(F0[hh], psidthbot[hh]);

  if(intensity > f0[hh]) {
    ponding();
    return;
  }

  F1[hh] = F0[hh] + garain;

  f1[hh] = calcf1(F1[hh], psidthbot[hh]);

  if(intensity > f1[hh])
    startponding();
}

void ClassGreenAmpt::ponding(void){

  F1[hh] = F0[hh] + garain;

  howmuch(F0[hh], Global::Interval*24.0);

  pond    += garain - (F1[hh] - F0[hh]);

  howmuch(F0[hh], Global::Interval*24.0);

}

void ClassGreenAmpt::startponding(void){

  double Fp = k[hh]*psidthbot[hh]/(intensity - k[hh]);
  double dt = (Fp - F0[hh])/intensity;

  howmuch(Fp, Global::Interval*24.0 - dt);

  pond    += garain - (F1[hh] - F0[hh]);

}

void ClassGreenAmpt::howmuch(double F0, double dt) {

  double LastF1;

  do {
    LastF1 = F1[hh];
    F1[hh] = F0 + k[hh]*dt + psidthbot[hh]*log((F1[hh] + psidthbot[hh])/(F0 + psidthbot[hh]));
  } while(fabs(LastF1 - F1[hh]) > 0.001);
}

double ClassGreenAmpt::calcf1(double F, double psidth){

  return k[hh]*(psidth/F + 1.0);
}
