//created by Manishankar Mondal

#include "ClassPrairieInfil.h"
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

ClassPrairieInfil* ClassPrairieInfil::klone(string name) const{
  return new ClassPrairieInfil(name);
}

void ClassPrairieInfil::decl(void) {

  Description = "'Handles frozen soil infiltration using Granger et al. 1984; Gray et al., 1986 and Ayers, 1959 for unfrozen soil.'";

  declvar("snowinfil", TDim::NHRU, "infiltration", "(mm/d)", &snowinfil);

  declstatdiag("cumsnowinfil", TDim::NHRU, "cumulative infiltration", "(mm)", &cumsnowinfil);

  declvar("meltrunoff", TDim::NHRU, "melt runoff", "(mm/d)", &meltrunoff);

  declstatdiag("cummeltrunoff", TDim::NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

  declvar("infil", TDim::NHRU,"Potential amount of water infiltrating the soil on each HRU", "(mm/int)", &infil);

  declstatdiag("cuminfil", TDim::NHRU, "cumulative potential infiltration on each HRU", "(mm)", &cuminfil);

  declvar("runoff", TDim::NHRU, "rainfall runoff", "(mm/int)", &runoff);

  declstatdiag("cumrunoff", TDim::NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

  declstatvar("crackstat", TDim::NHRU, "infiltration status", "()", &crackstat);

  declstatdiag("RainOnSnow", TDim::NHRU, "cumulative rain on snow", "(mm)", &RainOnSnow);

  declstatvar("crackon", TDim::NHRU,"crack cycle enabled", "()", &crackon);


  declstatdiag("RainOnSnowA", TDim::NHRU, "accumulated rain on snow", "(mm)", &RainOnSnowA);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("fallstat", TDim::NHRU, "[50.0]", "-1.0","100.0",
     "fall status 0.0 - unlimited/ 100.0 - restricted/ other - limited", "(%)", &fallstat);

  declparam("Major", TDim::NHRU, "[5]", "1", "100", "threshold for major melt", "(mm/d)", &Major);

  declparam("PriorInfiltration", TDim::NHRU, "[1]", "0", "1", "allow limited melt to infiltrate prior to first major melt", "(mm/d)", &PriorInfiltration);

  decldiagparam("infDays", TDim::NHRU, "[6]", "0", "20", " maximum number of days of snowmelt infiltration to frozen soil ", "(d)", &infDays);

  declparam("texture", TDim::NHRU, "[1]", "1","4",
     "texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", &texture);

  declparam("groundcover", TDim::NHRU, "[1]", "1","6",
     "groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", &groundcover);

  declgetvar("*",  "hru_tmax", "(°C)", &hru_tmax);
  declgetvar("*",  "snowmeltD", "(mm/d)", &snowmelt);
  declgetvar("*",  "SWE", "(mm)", &SWE);
  declgetvar("*",  "net_rain", "(mm/int)", &net_rain);
}

void ClassPrairieInfil::init(void) {

  nhru = getdim(TDim::NHRU);

  try 
  {

    Xinfil = new double*[3];   // Data [3] [nhru]
    for (int jj = 0; jj < 3; ++jj) 
    {
        Xinfil[jj] = new double[nhru];
    }

    timer = new long[nhru];

  }
  catch (std::bad_alloc) 
  {
    CRHMException Except("Could not allocate in module CRACK." , TExcept::TERMINATE);
    LogError(Except);
    throw Except;
  }

  for(hh = 0; chkStruct(); ++hh){ // every interval
    infil[hh] = 0.0;
    cuminfil[hh] = 0.0;
    snowinfil[hh] = 0.0;
    cumsnowinfil[hh] = 0.0;
    runoff[hh] = 0.0;
    cumrunoff[hh] = 0.0;
    meltrunoff[hh] = 0.0;
    cummeltrunoff[hh] = 0.0;

    RainOnSnow[hh] = 0.0;
    RainOnSnowA[hh] = 0.0;

    crackon[hh] = false;
    crackstat[hh] = 0;

    if (hh < nhru) 
    {
        timer[hh] = 0;
        Xinfil[0][hh] = 0.0;
        Xinfil[1][hh] = 0.0;
        Xinfil[2][hh] = 0.0;
    }
    
  }
}



void ClassPrairieInfil::run(void) {

  long nstep;

  nstep = getstep()%Global::Freq;

  for(hh = 0; chkStruct(); ++hh){ // every interval
    infil[hh] = 0.0;
    runoff[hh] = 0.0;
    if(net_rain[hh] > 0.0){
      if(crackon[hh])
        RainOnSnowA[hh] += net_rain[hh];
      else{
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
    }
  }

  if(nstep  ==  0) // end of every day
    for(hh = 0; chkStruct(); ++hh) {

      if(SWE[hh] > 25.0 && !crackon[hh]) {
        crackstat[hh] = 0;
        crackon[hh] = true; // initialise for current year
        timer[hh] = 0;
        Xinfil[0] [hh] = 0.0;
        Xinfil[1] [hh] = 0.0;
        Xinfil[2] [hh] = 0.0;
      }

      snowinfil[hh]= 0.0;
      meltrunoff[hh] = 0.0;

      if(crackon[hh] && snowmelt[hh] > 0.0) {

        if(timer[hh] > 0 && crackstat[hh] > 0)

  // ice lens forms, if next day below -10 limited

          if(fallstat[hh] > 0.0 && hru_tmax[0] < -10.0) crackstat[hh] = 10;

  // unlimited - (fallstat[hh].eq.0.0)

        if(fallstat[hh] <= 0.0) {

          snowinfil[hh] = snowmelt[hh];
          crackstat[hh] = 1;
        }

  // limited - (0.0 < fallstat[hh] < 100.0)

        else if(fallstat[hh] < 100.0){
          if(snowmelt[hh] >= Major[hh] || crackstat[hh] >= 1) {
            if(SWE[hh] > Xinfil[2][hh] && snowmelt[hh] >= Major[hh]) {
              infil_index(fallstat[hh]/100.0, SWE[hh], Xinfil[0][hh], Xinfil[1][hh], infDays[hh]);
              Xinfil[2][hh] = SWE[hh];
            }
            if(snowmelt[hh] >= Major[hh]) {
              if(crackstat[hh] <= 0)
                crackstat[hh] = 1;
              else
                crackstat[hh] = crackstat[hh] + 1;

              timer[hh] = 1;
              snowinfil[hh] = snowmelt[hh]*Xinfil[0][hh];
              if(snowinfil[hh] > Xinfil[1][hh]) snowinfil[hh]=Xinfil[1][hh];
            }
            else
              snowinfil[hh] = snowmelt[hh]*Xinfil[0][hh];

            if(crackstat[hh] > infDays[hh])
              snowinfil[hh] = 0;
          }
          else
            if(PriorInfiltration[hh])
              snowinfil[hh] = snowmelt[hh]; // zero by default
        }

  // restricted - (fallstat[hh].ge.100.0)

        else if(fallstat[hh] >= 100.0) {
          snowinfil[hh] = 0.0;
          crackstat[hh] = 1;
        }

        meltrunoff[hh] = snowmelt[hh] - snowinfil[hh];

        if(snowinfil[hh] > 0.0)
          snowinfil[hh] += RainOnSnowA[hh];
        else
          meltrunoff[hh] += RainOnSnowA[hh];

        cumsnowinfil[hh] += snowinfil[hh];
        cummeltrunoff[hh] += meltrunoff[hh];

        RainOnSnow[hh] += RainOnSnowA[hh];
        RainOnSnowA[hh] = 0.0;

      } // end if
      else if(snowmelt[hh] > 0.0){
        snowinfil[hh] = snowmelt[hh];
        cumsnowinfil[hh] += snowinfil[hh];
      }

      if(crackstat[hh] > 0 && SWE[hh] <= 0.0){
        crackon[hh] = false;
        crackstat[hh] = 0;
      }
    }   // end for
}

void ClassPrairieInfil::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' cumsnowinfil    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' cummeltrunoff   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' cuminfil(rain)  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' cumrunoff(rain) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' RainOnSnow      (mm) (mm*hru) (mm*hru/basin): ").c_str(), RainOnSnow[hh], hru_area[hh], basin_area[0], "** information only - amount of rain handled as snow.");
    LogDebug(" ");
  }

  if(Xinfil != NULL){
    for (int ii = 0; ii < 3; ii++)
      delete[] Xinfil[ii];  //Array [3] [nhru]

    delete[] Xinfil;
    Xinfil = NULL;
  }

  delete[] timer;
  timer = NULL;
}