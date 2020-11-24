//created by Manishankar Mondal

#include "ClassXGAyers.h"
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

ClassXGAyers* ClassXGAyers::klone(string name) const{
  return new ClassXGAyers(name);
}

void ClassXGAyers::decl(void) {

  Description = "'Snow melt handled by XG and and Ayers, .'";

  declvar("infil", TDim::NHRU, "Potential rain infiltration", "(mm/int)", &infil);

  declstatdiag("cuminfil", TDim::NHRU, "cumulative potential rain infiltration", "(mm)", &cuminfil);

  declvar("snowinfil", TDim::NHRU, "melt infiltration", "(mm/int)", &snowinfil);

  declstatvar("cumsnowinfil", TDim::NHRU, "cumulative melt infiltration", "(mm)", &cumsnowinfil); // for looping

  declvar("meltrunoff", TDim::NHRU, "melt runoff = 0.0", "(mm/int)", &meltrunoff);

  declstatdiag("cummeltrunoff", TDim::NHRU, "cumulative melt runoff = 0.0", "(mm)", &cummeltrunoff);

  declvar("runoff", TDim::NHRU, "rainfall runoff", "(mm/int)", &runoff);

  declstatdiag("cumrunoff", TDim::NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);


  declparam("texture", TDim::NHRU, "[1]", "1","4",
     "texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", &texture);

  declparam("groundcover", TDim::NHRU, "[1]", "1","6",
     "groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", &groundcover);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);


  declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD); // mm day

  declgetvar("*", "net_rain", "(mm/int)", &net_rain);
}

void ClassXGAyers::init(void) {

  nhru = getdim(TDim::NHRU);


  for(hh = 0; hh < nhru; ++hh) {
    infil[hh] = 0.0;
    runoff[hh] = 0.0;
    snowinfil[hh] = 0.0;
    meltrunoff[hh] = 0.0;
    cuminfil[hh] = 0.0;
    cumsnowinfil[hh] = 0.0;
    cummeltrunoff[hh] = 0.0;
    cumrunoff[hh] = 0.0;
  }
}

void ClassXGAyers::run(void) {


  long nstep = getstep() % Global::Freq;

  for(hh = 0; chkStruct(); ++hh) {

    infil[hh] = 0.0;
    runoff[hh] = 0.0;

    if(net_rain[hh] > 0.0){
      double maxinfil = textureproperties[texture[hh] - 1] [groundcover[hh] - 1] * 24.0/Global::Freq; // mm/int
      if(maxinfil > net_rain[hh])
        infil[hh] = net_rain[hh];
      else{
        infil[hh] = maxinfil;
        runoff[hh] = net_rain[hh] - maxinfil;
      }

      cuminfil[hh] += infil[hh];
      cumrunoff[hh] += runoff[hh];
    }

    snowinfil[hh] = 0.0;
    meltrunoff[hh] = snowmeltD[hh]/Global::Freq;
  } // for
}

void ClassXGAyers::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (frozenAyers)' cumsnowinfil       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozenAyers)' cummeltrunoff      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozenAyers)' cuminfil(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozenAyers)' cumrunoff(rain)    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}