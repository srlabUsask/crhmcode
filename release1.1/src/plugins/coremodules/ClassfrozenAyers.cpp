//created by Manishankar Mondal

#include "ClassfrozenAyers.h"
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

ClassfrozenAyers* ClassfrozenAyers::klone(string name) const{
  return new ClassfrozenAyers(name);
}

void ClassfrozenAyers::decl(void) {

  Description = "'Frozen soil infiltration Zhao and Gray (1999) and Ayers, (1959) for unfrozen soil.'";

  declvar("infil", NHRU, "Potential rain infiltration", "(mm/int)", &infil);

  declstatdiag("cuminfil", NHRU, "cumulative potential rain infiltration", "(mm)", &cuminfil);

  declvar("snowinfil", NHRU, "melt infiltration", "(mm/int)", &snowinfil);

  declstatvar("cumsnowinfil", NHRU, "cumulative melt infiltration", "(mm)", &cumsnowinfil); // for looping

  declvar("cumsnowinfil_0", NHRU, "cumulative melt infiltration at beginning of frozen cycle", "(mm)", &cumsnowinfil_0); // for looping

  declvar("meltrunoff", NHRU, "melt runoff", "(mm/int)", &meltrunoff);

  declstatdiag("cummeltrunoff", NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

  declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

  declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

  decllocal("t0_Var", NHRU, "t0 value used by module", "(h)", &t0_Var);

  decllocal("t0_Acc", NHRU, "opportunity time", "(h)", &t0_Acc); // to reset every loop

  decllocal("INF", NHRU, "parametric calculation", "(mm)", &INF);

  decllocal("Julian_window", ONE, "currently in Julian window handling frozen infiltration.", "()", &Julian_window);

  decllocal("Julian_lockout", ONE, "lockout next frozen cycle until after this Julian date when t0_Julian is not set (i.e. 0).", "()", &Julian_lockout);

  decllocal("infiltype", NHRU, "infiltration type. PREMELT/RESTRICTED/LIMITED/UNLIMITED/SATURATED - 0/1/2/3/4 respectively", "()", &infiltype);

  decllocal("snowmeltD_last", NHRU, "yesterday's snowmelt. Used to determine the formation of ice lens.", "(mm/d)", &snowmeltD_last);

  decllocal("SWEPk", NHRU, "peak snow water equivalent", "(mm)", &SWEPk);


  declparam("t0", NHRU, "[0.0]", "0.0", "1000.0", "< 0 - calculate opportunity time, == 0 - calculate t0 from '0.65*SWE-5.0',  > 0 - use as opportunity time", "(h)", &t0);

  decldiagparam("S0", NHRU, "[1.0]", "0.0", "1.0", "surface saturation", "(mm^3/mm^3)", &S0);

  declparam("Si", NHRU, "[0.5]", "0.0", "1.0", "initial soil saturation (0 - 0.4m)", "(mm^3/mm^3)", &Si);

  decldiagparam("C", NHRU, "[1.0]", "0.0", "3.0", "coefficient", "()", &C);

  declparam("hru_tsoil", NHRU, "[269.15]", "223.0", "273.15", "soil average temperature at start of infiltration (0 - 0.4m)", "(ºK)", &hru_tsoil);

  decldiagparam("t_ice_lens", NHRU, "[-20]", "-50.0", "0.0", "overnight minimum to cause ice lens after major melt", "(ºC)", &t_ice_lens);

  declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0",
    "Maximum available water holding capacity of soil profile."//
    "Soil profile is surface to bottom of rooting zone",
    "(mm)", &soil_moist_max);

  declparam("texture", NHRU, "[1]", "1","4",
     "texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", &texture);

  declparam("groundcover", NHRU, "[1]", "1","6",
     "groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", &groundcover);

  decldiagparam("t0_Julian", ONE, "[30]", "0","366", "value > 0 - inhibit frozen algorithm till after this Julian date, 0 - enable frozen algorithm immediately when melt criteria is met", "()", &t0_Julian);

  declgetvar("*", "soil_moist", "(mm)", &soil_moist);

  declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD); // mm day

  declgetvar("*", "SWE", "(mm)", &SWE);

  declgetvar("*", "net_rain", "(mm/int)", &net_rain);

  declgetvar("*",  "hru_tmin", "(°C)", &hru_tmin);


  declreadobs("t0_inhibit", NHRU, "opportunity time inhibit", "()", &t0_inhibit, 0, true);
}

void ClassfrozenAyers::init(void) {

  nhru = getdim(NHRU);

  if(t0[0] <= 0.0){ // going to calculate oportunity time
    if(t0_inhibit == NULL){
      CRHMException TExcept(string("'" + Name + " (FrozenAyers)' calculating opportunity time using every melt interval!").c_str(), WARNING);
      LogError(TExcept);
    }
    else{
      CRHMException TExcept(string("'" + Name + " (FrozenAyers)' calculating opportunity time using selected intervals!").c_str(), WARNING);
      LogError(TExcept);
    }
  }

  for(hh = 0; hh < nhru; ++hh) {
    t0_Acc[hh] = 0.0;
    t0_Var[hh] = 0.0;
    cuminfil[hh] = 0.0;
    infil[hh] = 0.0;
    cumsnowinfil[hh] = 0.0;
    cumsnowinfil_0[hh] = 0.0;
    cummeltrunoff[hh] = 0.0;
    runoff[hh] = 0.0;
    cumrunoff[hh] = 0.0;
    INF[hh] = 0.0;
    SWEPk[hh] = 0.0;

    infiltype[hh] = PREMELT;
  }

  SetOpportunityTime = false;
  Julian_window[0] = 0; // before Julian date
  Julian_lockout[0] = 0;
}

void ClassfrozenAyers::run(void) {

  bool SetOpportunity = false;
  bool ClrOpportunity = false;

  long nstep = getstep() % Global::Freq;

  float SWE_sum = 0.0;

  for(hh = 0; chkStruct(); ++hh)
    SWE_sum += SWE[hh]; // used to reset opportunity time

  for(hh = 0; chkStruct(); ++hh) {

    if(nstep == 0){ // end of day
      snowmeltD_last[hh] = snowmeltD[hh];
      if(SWE[hh] > SWEPk[hh])
        SWEPk[hh] = SWE[hh];
    }
    else if(nstep == 1 &&                  // beginning of day
         hru_tmin[hh] <= t_ice_lens[hh] &&
         infiltype[hh] == LIMITED &&
         snowmeltD_last[hh] > 5.0){

      infiltype[hh] = RESTRICTED;

      LogMessage(hh, " ice lens formed at temperature of ", hru_tmin[hh], DT);
      LogDebug(" ");

      CRHMException TExcept(string(string("Ice lens formed in HRU ") + to_string(hh+1) +", at minimum temperature of " + FloatToStrF(hru_tmin[hh], ffGeneral, 4, 1)).c_str(), WARNING);
      LogError(TExcept);
    }

    infil[hh] = 0.0;
    runoff[hh] = 0.0;

    if(net_rain[hh] > 0.0){
      float maxinfil = textureproperties[texture[hh] - 1] [groundcover[hh] - 1] * 24.0/Global::Freq; // mm/int
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
    meltrunoff[hh] = 0.0;

    if(Julian_lockout[0] == julian("now"))
      Julian_lockout[0] = 0;

    float snowmelt = snowmeltD[hh]/Global::Freq;

    if(nstep == 1 && hh == 0){
      if(t0_Julian[0] == julian("now") || t0_Julian[0] == 0 && SWE_sum/nhru > 10 && snowmeltD[hh] > 2.0 && !Julian_lockout[0]){
        Update_infil = true;
        if(t0[0] < 0){
          Julian_window[0] = 1;
          for(long hhh = 0; chkStruct(hhh); ++hhh) // reset
            t0_Acc[hhh] = t0[hhh];
        }
        else
          for(long hhh = 0; chkStruct(hhh); ++hhh) // save t0 values
            t0_Var[hhh] = t0[hhh];

        Julian_lockout[0] = (julian("now") + 183)%365; // close after 6 months
      }
    }

    INF[hh] = 0.0;
    if(snowmelt > 0.0){ // snowmeltD[hh]/Global::Freq

      if(hh == (nhru-1) && (SWE_sum/nhru <= 2.0 || last_timestep())){ // end of melt
        if(SetOpportunityTime){ // was calculating opportunity time
          --Global::CRHMControlSaveCnt; // restore state to backtrack. NO output this cycle
          ClrOpportunity = true;

          for(long hhh = 0; chkStruct(hhh); ++hhh) // save opportunity time values
            t0_Var[hhh] = t0_Acc[hhh];

          SetOpportunityTime = false;
          string s = Name + " End save ";
          LogMessage(s.c_str(), DD);
          Julian_window[0] = 0;
        }
      }

      if(!SetOpportunityTime){ // normal operation
        float capacity;
        switch(infiltype[hh]) {
          case LIMITED :

            capacity = soil_moist_max[hh] - soil_moist[hh];
            if(capacity > 0.0 && (t0_Var[hh] || !t0[hh])) { // also handles divide by zero
              if(!t0[hh]){
                t0_Var[hh] = 0.65*SWEPk[hh] - 5.0;
                if(t0_Var[hh] < 24.0)
                  t0_Var[hh] = 24.0;
              }
              INF[hh] = C[hh]*pow(S0[hh], 2.92f)*pow(1.0f-Si[hh], 1.64f)*
                   pow((273.15f-hru_tsoil[hh])/273.15f, -0.45f)*pow(t0_Var[hh], 0.44f); // (mm)

              float INF0 = INF[hh]/t0_Var[hh];

              if(snowmelt <= INF0 && snowmelt <= capacity) {
                snowinfil[hh] = snowmelt;
                meltrunoff[hh] = 0.0;
              }
              else if(snowmelt > INF0){
                snowinfil[hh] = INF0;
                meltrunoff[hh] = snowmelt - INF0;
              }
              else {
                snowinfil[hh] = capacity;
                meltrunoff[hh] = snowmelt - capacity;
              }

              cumsnowinfil[hh] += snowinfil[hh];
              cummeltrunoff[hh] += meltrunoff[hh];

              if(cumsnowinfil[hh] - cumsnowinfil_0[hh] > INF[hh]) {
                  cummeltrunoff[hh] += (cumsnowinfil[hh] - cumsnowinfil_0[hh] - INF[hh]);
                  cumsnowinfil[hh] += INF[hh];
                  infiltype[hh] = RESTRICTED;
              }
            }
            else{
              meltrunoff[hh] = snowmelt;
              cummeltrunoff[hh] += meltrunoff[hh];
            }

            break;

          case UNLIMITED :
            snowinfil[hh] = snowmelt;
            cumsnowinfil[hh] += snowinfil[hh];
            break;
          case RESTRICTED :
            meltrunoff[hh] = snowmelt;
            cummeltrunoff[hh] += meltrunoff[hh];
            break;
          default :
            if(Si[hh] < 1.0){
              snowinfil[hh] = snowmelt;
              cumsnowinfil[hh] += snowinfil[hh];
            }
            else{
              meltrunoff[hh] = snowmelt;
              cummeltrunoff[hh] += meltrunoff[hh];
            }
            break;
        } // switch
      } // normal operation

      if(snowmeltD[hh] > 2.0){
        if(Julian_window[0] == 1 && !SetOpportunityTime){ // run ahead?
          SetOpportunity = true;
          ++Global::CRHMControlSaveCnt; // save state for backtrack. Inhibit output, including this interval
          string s = Name + " Start save ";
          LogMessage(s.c_str(), DD);
        }

        if(Update_infil){
          for(long hhh = 0; chkStruct(hhh); ++hhh){ // set infiltration

            SWEPk[hhh] = SWE[hhh];

            if(Si[hhh] >= 1.0)
              infiltype[hhh] = RESTRICTED;
            else if(Si[hhh] <= 0.0)
              infiltype[hhh] = UNLIMITED;
            else
              infiltype[hhh] = LIMITED;
          }
          cumsnowinfil_0[hh] = cumsnowinfil[hh];

          Update_infil = false;
        }
      } // snowmeltD[hh] > 2.0

      if(SetOpportunityTime){ // accummulate opportunity time
        if(t0_inhibit == NULL)
            t0_Acc[hh] += 24.0/Global::Freq;
        else if(t0_inhibit[hh] > 0)
          t0_Acc[hh] += 24.0/Global::Freq;
      }
    } // if(snowmelt > 0.0)
  } // for

  if(SetOpportunity)
    SetOpportunityTime = true;
  if(ClrOpportunity)
    SetOpportunityTime = false;
}

void ClassfrozenAyers::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (frozenAyers)' cumsnowinfil       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozenAyers)' cummeltrunoff      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozenAyers)' cuminfil(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozenAyers)' cumrunoff(rain)    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}