//created by Manishankar Mondal

#include "Classlake.h"
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

Classlake* Classlake::klone(string name) const{
  return new Classlake(name);
}

void Classlake::decl(void) {

  Description = "'Calculates lake evaporation from the Meyer formula.'";

  declvar("hru_evap", TDim::NHRU, "interval evaporation", "(mm/int)", &hru_evap);

  declstatdiag("hru_cum_evap", TDim::NHRU, "cumulative interval evaporation", "(mm)", &hru_cum_evap);

  declvar("hru_actet", TDim::NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

  declstatdiag("hru_cum_actet", TDim::NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

  decldiag("Va", TDim::NHRU, "water vapour pressure, Vw*rh (Meyer)", "(mm)", &Va);

  decldiag("Vw", TDim::NHRU, "air vapour pressure (Meyer)", "(mm)", &Vw);

  declvar("lake_evap_month", TDim::NHRU, "monthly evaporation from rh", "(mm)", &lake_evap_month); // ***cannot be a state variable***

  declvar("hru_t_Mmean", TDim::NHRU, "HRU temperature", "(" + string(DEGREE_CELSIUS) + ")", &hru_t_Mmean);

  declvar("hru_rh_Mmean", TDim::NHRU, "HRU rh", "()", &hru_rh_Mmean);

  declvar("hru_u_Mmean", TDim::NHRU, "HRU wind speed", "(m/s)", &hru_u_Mmean);

  decllocal("hru_t_acc", TDim::NHRU, "HRU t accumulated", "(" + string(DEGREE_CELSIUS) + ")", &hru_t_acc);

  decllocal("hru_rh_acc", TDim::NHRU, "HRU rh accumulated", "()", &hru_rh_acc);

  decllocal("hru_u_acc", TDim::NHRU, "HRU u accumulated", "(m)", &hru_u_acc);

  decllocal("start_open_day", TDim::NHRU, "TDate format start of open water", "()", &start_open_day);

  decllocal("end_open_day", TDim::NHRU, "TDate format end of open water", "()", &end_open_day);

  decldiagparam("Meyer_C", TDim::NHRU, "[10.5]", "5.0", "15.0", "Meyer coefficient. (Recommended range 10.1->11)", "()", &Meyer_C);

  declparam("start_open_water", TDim::NHRU, "[120]", "1", "366", "Start of lake evaporation (Julian day)", "()", &start_open_water);

  declparam("end_open_water", TDim::NHRU, "[240]", "1", "366", "End of lake evaporation (Julian day)", "()", &end_open_water);

  decldiagparam("Meyer_B", TDim::TWELVE, "[-0.3, -2.8, -1.4, 2.0, 7.3, 8.8, 10.0, 9.6, 7.1, 3.0, -1.2, -2.6]", "-10.0", "20.0", "Meyer monthly intercept coefficient", "()", &Meyer_B);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_lat", TDim::NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(" + string(DEGREE) + ")", &hru_lat);

  declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);
  declgetvar("*", "hru_rh", "()", &hru_rh);
  declgetvar("*", "hru_u", "(m/s)", &hru_u);
}

void Classlake::init(void) {

  for (hh = 0; chkStruct(); ++hh){
    lake_evap_month[hh] = 0.0;
    hru_evap[hh] = 0.0;
    hru_cum_evap[hh] = 0.0;
    hru_actet[hh] = 0.0;
    hru_cum_actet[hh] = 0.0;
    hru_rh_acc[hh] = 0.0;
    hru_t_acc[hh] = 0.0;
    hru_t_Mmean[hh] = 0.0;
    hru_rh_Mmean[hh] = 0.0;
    hru_u_Mmean[hh] = 0.0;
    start_open_day[hh] = 0;
    end_open_day[hh] = 0;
  }

  N_intervals = 0;
  DoMean = false;
  Ahead = false;
}

void Classlake::run(void) {

  dattim("now", itime);

  long nstep = getstep() % Global::Freq;

  if((nstep == 1 || Global::Freq == 1) && (getstep() == 1 || itime[2] == 1) && !Ahead){ // beginning of every day

    ThisMonth = itime[1];

    DoMean = false;
    Ahead = false; // differentiates read ahead month from processing month

    N_intervals = 0;

    for(hh = 0; chkStruct(); ++hh) {

	  // Manishankar commented this because TDate is not a datatype in vcc. Need to look at this maybe.

      //if((int) Global::DTnow >= end_open_day[hh]){ // convert Julian to TDate
      //  start_open_day[hh] = (double) TDate(itime[0]-1, 12, 31) + start_open_water[hh];

      //  if(end_open_water[hh] > start_open_water[hh])
      //    end_open_day[hh] = (double) TDate(itime[0]-1, 12, 31) + end_open_water[hh];
      //  else
      //    end_open_day[hh] = (double) TDate(itime[0], 12, 31) + end_open_water[hh];
      //}

      hru_t_Mmean[hh] = 0.0;
      hru_rh_Mmean[hh] = 0.0;
      hru_u_Mmean[hh] = 0.0;

      hru_t_acc[hh] = 0.0;
      hru_rh_acc[hh] = 0.0;
      hru_u_acc[hh] = 0.0;

      lake_evap_month[hh] = 0.0;
      Va[hh] = 0.0;
      Vw[hh] = 0.0;

      hru_actet[hh] = 0.0;
      hru_evap[hh] = 0.0;
    } // for

    for(hh = 0; chkStruct(); ++hh) {
      if((double) Global::DTnow + 0.01 >=  start_open_day[hh] && (double) Global::DTnow - 0.01 <=  end_open_day[hh]){
        //DaysMonth = MonthDaysCnt(Global::DTnow);
        DoMean = true;
        Ahead = true;
      }
      else // no evaporation this month
       return;
    } // for

    if(DoMean)
      ++Global::CRHMControlSaveCnt; // save state for backtrack

  } // beginning of month

  if(DoMean){
    if(--DaysMonth == 0 || last_timestep()){
      add();
      process();
      --Global::CRHMControlSaveCnt; // restore state to backtrack
      DoMean = false;
    } // if
    else{
      add();
    }
  } // if DoMean
  else if(N_intervals){ // normal entry after monthly lake evaporation
    Ahead = false;
    for(hh = 0; chkStruct(); ++hh) {
      hru_actet[hh] = 0.0;
      hru_evap[hh] = 0.0;

      if((double) Global::DTnow + 0.01 >= start_open_day[hh] && (double) Global::DTnow - 0.01 <= end_open_day[hh]){
        hru_evap[hh] = lake_evap_month[hh]/N_intervals;
        hru_cum_evap[hh] += hru_evap[hh];
      } // if
    } // for
  }
}

void Classlake::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {

    LogMessageA(hh, string("'" + Name + " (lake_evap)' hru_cum_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_evap[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (lake_evap)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");

  }
}

void Classlake::add(void) {
      ++N_intervals;
      for(hh = 0; chkStruct(); ++hh) {
        hru_t_acc[hh] += hru_t[hh];
        hru_rh_acc[hh] += hru_rh[hh];
        hru_u_acc[hh] += hru_u[hh];
      } // for
}

void Classlake::process(void) {

      for(hh = 0; chkStruct(); ++hh) {
        hru_t_Mmean[hh] = hru_t_acc[hh]/N_intervals;
        hru_rh_Mmean[hh] = hru_rh_acc[hh]/N_intervals;
        hru_u_Mmean[hh] = hru_u_acc[hh]/N_intervals;

        long Index = ThisMonth-1;
        if(hru_lat[hh] < 0.0) // Southern Hemisphere 6 months offset
          Index = (Index +6)%12;

        double Tw = 0.6*hru_t_Mmean[hh] + Meyer_B[Index];

        Vw[hh] = pow(10,(-7.903*(373.16/(Tw+273.16)-1)+(5.028*log10(373.16/(Tw+273.16)))
        -(0.0000001382*(pow(10, (11.34*(1-(373.16/(Tw+273.16)))))-1))
        +(0.008133*pow(10, (-3.491*((373.16/(Tw+273.16))-1)))))+3.006);

        Va[hh] = Vw[hh]*hru_rh_Mmean[hh]/100.0;

        lake_evap_month[hh] = 0.75002*Meyer_C[hh]*(Vw[hh]-Va[hh])*(1+0.06214*hru_u_Mmean[hh])*(1.0 + 3.28084e-5*hru_elev[hh]);

        hru_t_acc[hh] = 0.0;
        hru_rh_acc[hh] = 0.0;
        hru_u_acc[hh] = 0.0;
      } // for
}