//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassGreencrack2.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassGreencrack2* ClassGreencrack2::klone(string name) const{
  return new ClassGreencrack2(name);
}

void ClassGreencrack2::decl(void) {

  Description = "'Handles frozen soil infiltration using Granger et al. 1984; Gray et al., 1986 and Ayers, 1959 for unfrozen soil.'";

  declvar("snowinfil", TDim::NHRU, "interval snowmelt infiltration", "(mm/int)", &snowinfil);

  declstatdiag("cumsnowinfil", TDim::NHRU, "cumulative snowmelt infiltration", "(mm)", &cumsnowinfil);

  declvar("meltrunoff", TDim::NHRU, "interval melt runoff", "(mm/int)", &meltrunoff);

  declstatdiag("cummeltrunoff", TDim::NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

  declvar("infil", TDim::NHRU,"interval rainfall infiltration", "(mm/int)", &infil);

  declstatdiag("cuminfil", TDim::NHRU, "cumulative rainfall  infiltration", "(mm)", &cuminfil);

  declvar("runoff", TDim::NHRU, "rainfall runoff", "(mm/int)", &runoff);

  declstatdiag("cumrunoff", TDim::NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

  declstatvar("crackstat", TDim::NHRU, "infiltration status", "()", &crackstat);

  declstatdiag("RainOnSnow", TDim::NHRU, "cumulative rain on snow", "(mm)", &RainOnSnow);

  declstatvar("crackon", TDim::NHRU,"crack cycle enabled", "()", &crackon);


  declstatdiag("RainOnSnowA", TDim::NHRU, "accumulated rain on snow", "(mm)", &RainOnSnowA);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("fallstat", TDim::NHRU, "[50.0]", "-1.0","100.0",
     "fall soil saturation status 0.0 - unlimited/ 100.0 - restricted/ other - limited", "(%)", &fallstat);

  declparam("Major", TDim::NHRU, "[5]", "1", "100", "threshold for major melt", "(mm/d)", &Major);

  declparam("PriorInfiltration", TDim::NHRU, "[1]", "0", "1", "allow limited melt to infiltrate prior to first major melt", "(mm/d)", &PriorInfiltration);

  decldiagparam("infDays", TDim::NHRU, "[6]", "0", "20", " maximum number of days of snowmelt infiltration to frozen soil ", "(d)", &infDays);

  decldiagparam("maxinfil", TDim::NHRU, "[0]", "0", "80", " maximum summer infiltration", "(d)", &maxinfil_prm);

  declparam("texture", TDim::NHRU, "[1]", "1","4",
     "texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "()", &texture);

  declparam("groundcover", TDim::NHRU, "[1]", "1","6",
     "groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "()", &groundcover);

  declgetvar("*",  "hru_tmax", "(" + string(DEGREE_CELSIUS) + ")", &hru_tmax);
  declgetvar("*",  "SWE", "(mm)", &SWE);
  declgetvar("*",  "net_rain", "(mm/int)", &net_rain);

  declgetvar("*",  "snowmeltD", "(mm/d)", &snowmeltD);

// ******************
// Parameters and variables for the Green-Ampt portion

  decldiagparam("psi_fixup", TDim::NHRU, "[1]", "0.1", "10", "psi fixup", "()", &psi_fixup);
  decldiagparam("ksat_fixup", TDim::NHRU, "[1]", "0.1", "10", "ksat fixup", "()", &ksat_fixup);
  decldiagparam("greenampt_on_recharge_zone", TDim::NHRU, "[0]", "0", "1", "ksat fixup", "()", &ga_rechr);

  declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
      "Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
      "and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

  declparam("soil_rechr_init", TDim::NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
      "soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

  declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0",
        "Maximum available water holding capacity of soil profile."//
        "Soil profile is surface to bottom of rooting zone", "(mm)", &soil_moist_max);

  declparam("soil_moist_init", TDim::NHRU, "[187.0]", "0.0", "2500.0",
        "Initial value of available water in soil profile", "(mm)", &soil_moist_init);

  declparam("soil_type", TDim::NHRU, "[4]", "0", "12",
        "water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
        " 0 - 12", "()", &soil_type);

  declputvar("*",  "soil_rechr", "(mm)", &soil_rechr);
  declputvar("*",  "soil_moist", "(mm)", &soil_moist);

  decllocal("k", TDim::NHRU, "saturated hydraulic conductivity", "(mm/h)", &k);
  decllocal("F0", TDim::NHRU, "cumulative infiltation at the beginning of the time interval", "(mm)", &F0);
  decllocal("f0", TDim::NHRU, "infiltration rate at the beginning of the time interval", "(mm/h)", &f0);
  decllocal("F1", TDim::NHRU, "cumulative infiltration at the end of the time interval", "(mm)", &F1);
  decllocal("f1", TDim::NHRU, "infiltration rate at the end of the time interval", "(mm/h)", &f1);
  decllocal("dthbot", TDim::NHRU, "fraction value of soil water deficit", "()", &dthbot);
  decllocal("psidthbot", TDim::NHRU, "capillary suction at the fraction value of soil water deficit", "(mm)", &psidthbot);


// ******************
// Parameters and variables for the variations

  variation_set = VARIATION_0;
  declgetvar("*",  "snowmeltD", "(mm/d)", &snowmelt);

  variation_set = VARIATION_1;
  declgetvar("*",  "snowmelt_int", "(mm/int)", &snowmelt);

}

void ClassGreencrack2::init(void) {

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

// Setup for the Green-Ampt code
  for(hh = 0; chkStruct(); ++hh){ // every interval
    double sminit, smmax;
    if (ga_rechr[hh] == 1) {
      sminit = soil_rechr_init[hh];
      smmax = soil_rechr_max[hh];
    } else {
      sminit = soil_moist_init[hh];
      smmax = soil_moist_max[hh];
    }

    F1[hh]        = smmax;
    k[hh]         = ksat_fixup[hh] * soilproperties[soil_type[hh]][KSAT];

    if(smmax > 0.0)  // handle zero
      dthbot[hh]    = (1.0 - sminit/smmax);
    else{
      dthbot[hh] = 1.0;
      continue;
    }

    psidthbot[hh] = psi_fixup[hh]*soilproperties[soil_type[hh]][PSI]*dthbot[hh];
    f1[hh]        = calcf1(F1[hh], psidthbot[hh])*Global::Interval*24.0;
  }


}



void ClassGreencrack2::applyCrack(double RainOnSnow_int) {
      // ice lens forms, if next day below -10 limited
      // unlimited - (fallstat[hh].eq.0.0)
      if (fallstat[hh] <= 0.0)
      {
          snowinfil[hh] = snowmelt[hh];
      }


      // limited - (0.0 < fallstat[hh] < 100.0)
      if ((fallstat[hh] > 0.0) && (fallstat[hh] < 100.0) )
      {
        if (snowmelt[hh] >= Major[hh]/24 || crackstat[hh] >= 1)
        {
          if (snowmelt[hh] >= Major[hh]/24)
          {
            snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];

            if (snowinfil[hh] > Xinfil[1][hh])
            {
                snowinfil[hh] = Xinfil[1][hh];
            }
          } else {
            snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];
          }

          if (crackstat[hh] > infDays[hh])
          {
              snowinfil[hh] = 0;
          }
        }
        else
        {
            if (PriorInfiltration[hh])
            {
                snowinfil[hh] = snowmelt[hh]; // zero by default
            }

        }

      }


      // restricted - (fallstat[hh].ge.100.0)
      if (fallstat[hh] >= 100.0)
      {
          snowinfil[hh] = 0.0;
      }

      meltrunoff[hh] = snowmelt[hh] - snowinfil[hh];

      if (snowinfil[hh] > 0.0)
      {
          snowinfil[hh] += RainOnSnow_int;
      }
      else
      {
          meltrunoff[hh] += RainOnSnow_int;
      }

      cumsnowinfil[hh] += snowinfil[hh];
      cummeltrunoff[hh] += meltrunoff[hh];

}



void ClassGreencrack2::run(void) {

  long nstep;

  nstep = getstep()%Global::Freq;

  for(hh = 0; chkStruct(); ++hh){ // every interval
    infil[hh] = 0.0;
    runoff[hh] = 0.0;
    snowinfil[hh] = 0.0;
    meltrunoff[hh] = 0.0;

    if(net_rain[hh] > 0.0) {
      if(crackon[hh]) {

        RainOnSnowA[hh] += net_rain[hh];

      } else {
/*
        double maxinfil = textureproperties[texture[hh] - 1] [groundcover[hh] - 1] * 24.0/Global::Freq; // mm/int
        if (maxinfil_prm[hh] > 0) 
          maxinfil = maxinfil_prm[hh];

        if(maxinfil > net_rain[hh])
          infil[hh] = net_rain[hh];
        else{
          infil[hh] = maxinfil;
          runoff[hh] = net_rain[hh] - maxinfil;
        }

        cuminfil[hh] += infil[hh];
        cumrunoff[hh] += runoff[hh];
*/

      garain = net_rain[hh]; // precipitation/interval
      intensity = net_rain[hh]*Global::Freq/24.0; // convert to mm/h


      double smt, sminit, smmax;
      if (ga_rechr[hh] == 1) {
        smt = soil_rechr[hh];
        sminit = soil_rechr_init[hh];
        smmax = soil_rechr_max[hh];
      } else {
        smt = soil_moist[hh];
        sminit = soil_moist_init[hh];
        smmax = soil_moist_max[hh];
      }


//      if(garain > 0.0) {
        if(soil_type[hh] == 12){ // handle pavement separately
          runoff[hh] =  garain;
        }
        else if(soil_type[hh] == 0 || smt <= 0.0){ // handle water separately
          infil[hh] =  garain;
          cuminfil[hh] += infil[hh];
        }
        else {
          F1[hh] = smt;
          dthbot[hh]    = (1.0 - smt/smmax);
          psidthbot[hh] = psi_fixup[hh]*soilproperties[soil_type[hh]][PSI]*dthbot[hh];
          if(soil_type[hh] > 0) // not water!
            f1[hh] = calcf1(F1[hh], psidthbot[hh])*Global::Interval*24.0; // infiltrate first interval rainfall (mm/h)

          infiltrate();

          infil[hh] = F1[hh] - F0[hh];
          cuminfil[hh] += infil[hh];

          if(pond > 0.0)
            runoff[hh] = pond;
        }
//      }

      cumrunoff[hh] += runoff[hh];

      }
    }

    if (snowmelt[hh] > 0) {
      if (crackon[hh]) {
        applyCrack(net_rain[hh]);
      } else {
        snowinfil[hh] = snowmelt[hh];
        cumsnowinfil[hh] += snowinfil[hh];
      }
    }
  }


// ====================
// Update soil frozen state once per day

  if (nstep == 0) // end of every day
  {
      for (hh = 0; chkStruct(); ++hh)
      {

          //If snow is larger than 25 mm and the frozen soil routine is off then we need to turn it on.
          if (SWE[hh] > 25.0 && !crackon[hh])
          {
              crackstat[hh] = 0;
              crackon[hh] = true; // initialise for current year
              timer[hh] = 0;
              Xinfil[0][hh] = 0.0;
              Xinfil[1][hh] = 0.0;
              Xinfil[2][hh] = 0.0;
          }

          //If soil is frozen and we have some snowmelt.
          if (crackon[hh] && snowmeltD[hh] > 0.0)
          {


              if (timer[hh] > 0 && crackstat[hh] > 0)
              {
                  if (fallstat[hh] > 0.0 && hru_tmax[0] < -10.0)
                  {
                      crackstat[hh] = 10;
                  }
              }

              // ice lens forms, if next day below -10 limited
              // unlimited - (fallstat[hh].eq.0.0)

              if (fallstat[hh] <= 0.0)
              {
//                  snowinfil[hh] = snowmelt[hh];
                  crackstat[hh] = 1;
              }

              // limited - (0.0 < fallstat[hh] < 100.0)

              else if (fallstat[hh] < 100.0)
              {
                  if (snowmeltD[hh] >= Major[hh] || crackstat[hh] >= 1)
                  {
                      if (SWE[hh] > Xinfil[2][hh] && snowmeltD[hh] >= Major[hh])
                      {
                          infil_index(fallstat[hh] / 100.0, SWE[hh], Xinfil[0][hh], Xinfil[1][hh], infDays[hh]);
                          Xinfil[2][hh] = SWE[hh];
                      }
                      if (snowmeltD[hh] >= Major[hh])
                      {
                          if (crackstat[hh] <= 0)
                          {
                              crackstat[hh] = 1;
                          }
                          else
                          {
                              crackstat[hh] = crackstat[hh] + 1;
                          }

                          timer[hh] = 1;
                          // snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];

                          // if (snowinfil[hh] > Xinfil[1][hh])
                          // {
                          //     snowinfil[hh] = Xinfil[1][hh];
                          // }
                      }
                      // else
                      // {
                      //     snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];
                      // }


                      // if (crackstat[hh] > infDays[hh])
                      // {
                      //     snowinfil[hh] = 0;
                      // }

                  }
                  // else
                  // {
                  //     if (PriorInfiltration[hh])
                  //     {
                  //         snowinfil[hh] = snowmelt[hh]; // zero by default
                  //     }

                  // }

              }

              // restricted - (fallstat[hh].ge.100.0)

              else if (fallstat[hh] >= 100.0)
              {
//                  snowinfil[hh] = 0.0;
                  crackstat[hh] = 1;
              }

              // meltrunoff[hh] = snowmelt[hh] - snowinfil[hh];

              // if (snowinfil[hh] > 0.0)
              // {
              //     snowinfil[hh] += RainOnSnowA[hh];
              // }
              // else
              // {
              //     meltrunoff[hh] += RainOnSnowA[hh];
              // }

              // cumsnowinfil[hh] += snowinfil[hh];
              // cummeltrunoff[hh] += meltrunoff[hh];

              RainOnSnow[hh] += RainOnSnowA[hh];
              RainOnSnowA[hh] = 0.0;

          } // end if
          // else if (snowmelt[hh] > 0.0)
          // {
          //     snowinfil[hh] = snowmelt[hh];
          //     cumsnowinfil[hh] += snowinfil[hh];
          // }

          if (crackstat[hh] > 0 && SWE[hh] <= 0.0)
          {
              crackon[hh] = false;
              crackstat[hh] = 0;
          }
      }   // end for
  }

}

void ClassGreencrack2::finish(bool good) {

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


void ClassGreencrack2::infiltrate(void){

  F0[hh] = F1[hh]; // last interval final values become initial values
  f0[hh] = f1[hh]; // last interval final values become initial values

  if(soil_type[hh] == 0) { // water!
    pond += garain;
    return;
  }
  pond = 0.0;

  f0[hh] = calcf1(F0[hh], psidthbot[hh]); // (mm/h)

  if(intensity > f0[hh]) { // (mm/h). Greater than initial
    ponding(); // already ponding
    return;
  }

  F1[hh] = F0[hh] + garain;

  f1[hh] = calcf1(F1[hh], psidthbot[hh]); // (mm/h)

  if(intensity > f1[hh]) // (mm/h). Greater than end
    startponding(); // ponding begins during interval
}

void ClassGreencrack2::ponding(void){

  F1[hh] = F0[hh] + garain;

  howmuch(F0[hh], Global::Interval*24.0);

  pond = F0[hh] + garain - F1[hh];
}

void ClassGreencrack2::startponding(void){ // ponding during interval

  double Fp = k[hh]*psidthbot[hh]/(intensity - k[hh]); // (mm/h)
  double dt = (Fp - F0[hh])/intensity;

  howmuch(F0[hh], Global::Interval*24.0 - dt);

  pond = F0[hh] + garain - F1[hh];
}

void ClassGreencrack2::howmuch(double F0, double dt) { // output is F1[hh]

  double LastF1;
  do {
    LastF1 = F1[hh];
    F1[hh] = F0 + k[hh]*dt + psidthbot[hh]*log((F1[hh] + psidthbot[hh])/(F0 + psidthbot[hh]));
  } while(fabs(LastF1 - F1[hh]) > 0.01);
}

double ClassGreencrack2::calcf1(double F, double psidth){ // calculates infitration rate

  return k[hh]*(psidth/F + 1.0); // (mm/h)
}
