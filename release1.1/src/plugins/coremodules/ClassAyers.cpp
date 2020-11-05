//created by Manishankar Mondal

#include "ClassAyers.h"
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

ClassAyers* ClassAyers::klone(string name) const{
  return new ClassAyers(name);
}

void ClassAyers::decl(void) {

  Description = "'Uses Ayers, 1959 for unfrozen soil. Snow is assumed to melt immediately on contact with the ground.'";

  declvar("infil", TDim::NHRU,"Potential amount of water infiltrating the soil on each HRU", "(mm/int)", &infil);

  declstatdiag("cuminfil", TDim::NHRU, "cumulative potential infiltration on each HRU", "(mm)", &cuminfil);

  declvar("runoff", TDim::NHRU, "rainfall runoff", "(mm/int)", &runoff);

  declstatdiag("cumrunoff", TDim::NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

  declvar("snowinfil", TDim::NHRU, "infiltration", "(mm/int)", &snowinfil);

  declstatdiag("cumsnowinfil", TDim::NHRU, "cumulative infiltration", "(mm)", &cumsnowinfil);

  declvar("meltrunoff", TDim::NHRU, "melt runoff", "(mm/int)", &meltrunoff);

  declstatdiag("cummeltrunoff", TDim::NHRU, "melt runoff", "(mm)", &cummeltrunoff);

  decllocal("melt_int", TDim::NHRU, "interval melt from snowmelD", "(mm/int)", &melt_int);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("texture", TDim::NHRU, "[1]", "1","4",
     "texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", &texture);

  declparam("groundcover", TDim::NHRU, "[1]", "1","6",
     "groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", &groundcover);

  declgetvar("*",  "net_rain", "(mm/int)", &net_rain);

  declgetvar("*",  "snowmeltD", "(mm/d)", &snowmeltD);
}

void ClassAyers::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; hh < nhru; ++hh) {
    cuminfil[hh] = 0.0;
    cumrunoff[hh] = 0.0;
    cumsnowinfil[hh] = 0.0;
    cummeltrunoff[hh] = 0.0;
  }
}

void ClassAyers::run(void) {

  long nstep = getstep() % Global::Freq;

  for(hh = 0; chkStruct(); ++hh){ // every interval
    infil[hh] = 0.0;
    runoff[hh] = 0.0;
    snowinfil[hh] = 0.0;
    meltrunoff[hh] = 0.0;

    if(nstep == 0)
      melt_int[hh] = snowmeltD[hh]/Global::Freq;

    double maxinfil = textureproperties[texture[hh] - 1] [groundcover[hh] - 1] * 24.0/Global::Freq; // mm/int

    if(melt_int[hh] > 0.0){
        if(maxinfil > melt_int[hh])
          snowinfil[hh] = melt_int[hh];
        else{
          snowinfil[hh] = maxinfil;
          meltrunoff[hh] = melt_int[hh] - maxinfil;
        }
        maxinfil -= snowinfil[hh];

        cumsnowinfil[hh] += snowinfil[hh];
        cummeltrunoff[hh] += meltrunoff[hh];
    }

    if(net_rain[hh] > 0.0){
      if(maxinfil > 0.0){
        if(maxinfil > net_rain[hh])
          infil[hh] = net_rain[hh];
        else{
          infil[hh] = maxinfil;
          runoff[hh] = net_rain[hh] - maxinfil;
        }
      }
      else
        runoff[hh] = net_rain[hh];

      cuminfil[hh] += infil[hh];
      cumrunoff[hh] += runoff[hh];
    }
  }
}

void ClassAyers::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (Ayers)' cuminfil(rain)      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Ayers)' cumrunoff(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Ayers)' cumsnowinfil(snow)  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Ayers)' cummeltrunoff(snow) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}