//created by Manishankar Mondal

#include "Classfrozen.h"
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


Classfrozen* Classfrozen::klone(string name) const{
  return new Classfrozen(name);
}

void Classfrozen::decl(void) {

  Description = "'Frozen soil infiltration Zhao and Gray (1999).'";

  declvar("infil", TDim::NHRU, "Potential rain infiltration", "(mm/int)", &infil);

  declstatdiag("cuminfil", TDim::NHRU, "cumulative potential rain infiltration", "(mm)", &cuminfil);

  declvar("snowinfil", TDim::NHRU, "melt infiltration", "(mm/int)", &snowinfil);

  declstatvar("cumsnowinfil", TDim::NHRU, "cumulative melt infiltration", "(mm)", &cumsnowinfil); // for looping

  declvar("meltrunoff", TDim::NHRU, "melt runoff", "(mm/int)", &meltrunoff);

  declstatdiag("cummeltrunoff", TDim::NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

  declvar("runoff", TDim::NHRU, "rainfall runoff", "(mm/int)", &runoff);

  declstatdiag("cumrunoff", TDim::NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

  decllocal("t0_Var", TDim::NHRU, "t0 value used by module", "(h)", &t0_Var);

  decllocal("t0_Acc", TDim::NHRU, "opportunity time", "(h)", &t0_Acc); // to reset every loop

  decllocal("INF", TDim::NHRU, "parametric calculation", "(mm)", &INF);

  decllocal("Julian_window", TDim::ONE, "currently in Julian window handling frozen infiltration.", "()", &Julian_window);

  decllocal("Julian_lockout", TDim::ONE, "lockout next frozen cycle until after this Julian date when t0_Julian is not set (i.e. 0).", "()", &Julian_lockout);

  decllocal("infiltype", TDim::NHRU, "infiltration type. PREMELT/RESTRICTED/LIMITED/UNLIMITED/SATURATED - 0/1/2/3/4 respectively", "()", &infiltype);

  decllocal("snowmeltD_last", TDim::NHRU, "yesterday's snowmelt. Used to determine the formation of ice lens.", "(mm/d)", &snowmeltD_last);

  decllocal("SWEPk", TDim::NHRU, "peak snow water equivalent", "(mm)", &SWEPk);


  declparam("t0", TDim::NHRU, "[0.0]", "0.0", "1000.0", "< 0 - calculate opportunity time, == 0 - calculate t0 from '0.65*SWE-5.0',  > 0 - use as opportunity time", "(h)", &t0);

  decldiagparam("S0", TDim::NHRU, "[1.0]", "0.0", "1.0", "surface saturation", "(mm^3/mm^3)", &S0);

  declparam("Si", TDim::NHRU, "[0.5]", "0.0", "1.0", "initial soil saturation (0 - 0.4m)", "(mm^3/mm^3)", &Si);

  decldiagparam("C", TDim::NHRU, "[1.0]", "0.0", "3.0", "coefficient", "()", &C);

  declparam("hru_tsoil", TDim::NHRU, "[269.15]", "223.0", "273.15", "soil average temperature at start of infiltration (0 - 0.4m)", "(ºK)", &hru_tsoil);

  decldiagparam("t_ice_lens", TDim::NHRU, "[-20]", "-50.0", "0.0", "overnight minimum to cause ice lens after major melt", "(" + string(DEGREE_CELSIUS) + ")", &t_ice_lens);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0",
    "Maximum available water holding capacity of soil profile."//
    "Soil profile is surface to bottom of rooting zone",
    "(mm)", &soil_moist_max);

  decldiagparam("t0_Julian", TDim::ONE, "[30]", "0","366", "value > 0 - inhibit frozen algorithm till after this Julian date, 0 - enable frozen algorithm immediately when melt criteria is met.", "()", &t0_Julian);

  declgetvar("*", "soil_moist", "(mm)", &soil_moist);

  declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD); // mm day

  declgetvar("*", "SWE", "(mm)", &SWE);

  declgetvar("*", "net_rain", "(mm/int)", &net_rain);

  declgetvar("*",  "hru_tmin", "(" + string(DEGREE_CELSIUS) + ")", &hru_tmin);


  declreadobs("t0_inhibit", TDim::NHRU, "opportunity time inhibit", "()", &t0_inhibit, 0, true);
}

void Classfrozen::init(void) {

  nhru = getdim(TDim::NHRU);

  if(t0[0] <= 0.0){ // going to calculate oportunity time
    if(t0_inhibit == NULL){
      CRHMException TExcept("Frozen: calculating opportunity time using every melt (when applicable) interval!", TExcept::WARNING);
      LogError(TExcept);
    }
    else{
      CRHMException TExcept("Frozen: calculating opportunity time using selected melt (when applicable) intervals!", TExcept::WARNING);
      LogError(TExcept);
    }
  }

  for(hh = 0; hh < nhru; ++hh) {
    t0_Acc[hh] = 0.0;
    t0_Var[hh] = 0.0;
    cuminfil[hh] = 0.0;
    infil[hh] = 0.0;
    cumsnowinfil[hh] = 0.0;
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

void Classfrozen::run(void) {

  bool SetOpportunity = false;
  bool ClrOpportunity = false;

  long nstep = getstep() % Global::Freq;

  double SWE_sum = 0.0;

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

      LogMessage(hh, " ice lens formed at temperature of ", hru_tmin[hh], TExtra::DT);
      LogDebug(" ");

      CRHMException TExcept(string(string("Ice lens formed in HRU ") + to_string(hh+1) +", at minimum temperature of " + FloatToStrF(hru_tmin[hh], TFloatFormat::ffGeneral, 4, 1)).c_str(), TExcept::WARNING);
      LogError(TExcept);
    }

    infil[hh] = 0.0;

    if(net_rain[hh] > 0.0){
      infil[hh] = net_rain[hh];
      cuminfil[hh] += net_rain[hh];
    }

    snowinfil[hh] = 0.0;
    meltrunoff[hh] = 0.0;

    if(Julian_lockout[0] == julian("now"))
      Julian_lockout[0] = 0;

    double snowmelt = snowmeltD[hh]/Global::Freq;

    if(nstep == 1 && hh == 0){
      if(t0_Julian[0] == julian("now") || t0_Julian[0] == 0 && SWE_sum/nhru > 10 && snowmeltD[hh] > 2.0 && !Julian_lockout[0]){
        Update_infil = true;
        if(t0[0] <= 0){
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
          LogMessage(s.c_str(), TExtra::DD);
          Julian_window[0] = 0;
        }
      }

      if(!SetOpportunityTime){ // normal operation
        double capacity;
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

              double INF0 = INF[hh]/t0_Var[hh];

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

              if(cumsnowinfil[hh] > INF[hh]) {
                  cummeltrunoff[hh] += (cumsnowinfil[hh] - INF[hh]);
                  cumsnowinfil[hh] = INF[hh];
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
          LogMessage(s.c_str(), TExtra::DD);
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

void Classfrozen::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (frozen)' cumsnowinfil       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozen)' cummeltrunoff      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozen)' cuminfil(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (frozen)' cumrunoff(rain)    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}