//created by Manishankar Mondal

#include "ClassObs.h"
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



Classobs* Classobs::klone(string name) const{
  return new Classobs(name, "07/05/06");
}

void Classobs::decl(void) {

  Description = "'Converts measurement observations to HRU variables with corrections,' \
                 'original interval version,' \
                 'daily interval version for Annandale (additional inputs are observations t_min and t_max),' \
                 'inputs rain and snow observations (p and ppt not used)).'";

  variation_set = VARIATION_ORG;

  if(Global::nlay < 2){
    Global::nlay = 2;
    Global::maxlay = 2;
  }

  decldiagparam("HRU_OBS", TDim::NDEFN, "[1, 2, 3!]", "1", "100", "observation indirection table ([1] - t, rh and ea, [2] - p and ppt, [3] - u, [4] - Q, [5] - misc)", "()", &HRU_OBS, &HRU_OBS_Tables, 5);

  declparam("obs_elev", TDim::NDEFN, "[0]", "0.0", "100000.0", "observation measurement altitude table ([1] - t, rh and ea, [2] - p and ppt", "(m)", &obs_elev, &obs_elev_Tables, 2);

  declparam("hru_elev", TDim::NHRU, "[0]", "0.0", "100000.0", "HRU altitude", "(m)", &hru_elev);

  declparam("lapse_rate", TDim::NHRU, "[0.75]", "0", "2", "temperature lapse rate", "(°C/100m)", &lapse_rate);

  decldiagparam("precip_elev_adj", TDim::NHRU, "[0.0]", "-1.0", "1.0", "precipitation height adjustment {adjusted p(or ppt) = p(or ppt)*(1.0 + precip_elev_adj*elev_difference/100)}", "(1/100m)", &precip_elev_adj);

  decldiagparam("ElevChng_flag", TDim::NHRU, "[0]", "0", "1", "Elevation change control; 0 - maintain RH, 1 - keep Vp within Vsat maximum", "()", &ElevChng_flag);

  decldiagparam("ClimChng_flag", TDim::NHRU, "[0]", "0", "1", "Climate change control; 0 - maintain RH, 1 - keep Vp within Vsat maximum", "()", &ClimChng_flag);

  decldiagparam("ClimChng_t", TDim::NHRU, "[0]", "-50", "+50", "Climate change additive temperature change.", "(°C)", &ClimChng_t);

  decldiagparam("ClimChng_precip", TDim::NHRU, "[1]", "0.0", "10", "Climate change multiplative p/ppt change.", "()", &ClimChng_precip);

  Global::HRU_OBS = const_cast<long **> (HRU_OBS_Tables);

  Global::Warming_t = const_cast<double *> (this->ClimChng_t); // must be here to load do_t_day etc.

  Global::Warming_p = const_cast<double *> (this->ClimChng_precip); // must be here to load do_p etc.


  declreadobs("u", TDim::NHRU, "wind velocity", "(m/s)", &u, HRU_OBS_u);

  declreadobs("ppt", TDim::NHRU, "daily precipitation", "(mm/d)", &ppt, HRU_OBS_p_ppt, true);

  declreadobs("p", TDim::NHRU, "interval precipitation", "(mm/int)", &p, HRU_OBS_p_ppt, true);


  decldiag("t_obs", TDim::NFREQ, "observation temperature before modification by lapse rate and global warning", "(°C)", &t_obs, &t_obs_lay);


  declvar("hru_t", TDim::NHRU, "temperature", "(°C)", &hru_t);

  declvar("hru_rh", TDim::NHRU, "relative humidity", "(%)", &hru_rh);

  declvar("hru_ea", TDim::NHRU, "HRU vapour pressure", "(kPa)", &hru_ea);

  decldiag("hru_estar", TDim::NHRU, "HRU saturation vapour pressure", "(kPa)", &hru_estar);

  declvar("hru_u", TDim::NHRU, "wind velocity", "(m/s)", &hru_u);

  declvar("hru_p", TDim::NHRU, "total precip (includes snow catch adjustment", "(mm/int)", &hru_p);

  declvar("hru_rain", TDim::NHRU, "rain", "(mm/int)", &hru_rain);

  declvar("Pa", TDim::NHRU, "average surface pressure", "(kPa)", &Pa);

  decllocal("DTindx", TDim::ONE, "main loop Index", "()", &DTindx);

  decllocal("DTnow", TDim::ONE, "main loop Time", "()", &DTnow);

  declstatdiag("cumhru_rain", TDim::NHRU, "cumulative HRU rain", "(mm)", &cumhru_rain);

  declvar("hru_snow", TDim::NHRU, "snow", "(mm/int)", &hru_snow);

  declstatdiag("cumhru_snow", TDim::NHRU, "cumulative HRU snow", "(mm)", &cumhru_snow);

  declstatdiag("cumhru_snow_meas", TDim::NHRU, "cumulative HRU snow catch adjustment", "(mm)", &cumhru_snow_meas);

  declvar("hru_tmax", TDim::NHRU, "max daily temp", "(°C)", &hru_tmax);

  declvar("hru_tmin", TDim::NHRU, "min daily temp", "(°C)", &hru_tmin);

  declvar("hru_tmean", TDim::NHRU, "mean daily temp", "(°C)", &hru_tmean);

  declvar("hru_eamean", TDim::NHRU, "mean daily vapour pressure", "(kPa)", &hru_eamean);

  declvar("hru_umean", TDim::NHRU, "mean daily wind", "(m/s)", &hru_umean);

  declvar("hru_rhmean", TDim::NHRU,"daily mean relative humidity", "(%)", &hru_rhmean);

  declvar("hru_newsnow", TDim::NHRU, "new snow on HRU - 0=no, 1=yes", "()", &hru_newsnow);


  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  Global::RH_EA_obs = -1;

  decldiag("Tday", TDim::NFREQ, "observation t unavailable", "(°C)", &NotUsed, &tday_intvls);
  Exist = declobsfunc("t", "Tday", &NotUsed, TFun::INTVL, &tday_intvls);

  decldiag("RHday", TDim::NFREQ, "observation rh unavailable", "(kPa)", &NotUsed, &rhday_intvls);
  Exist = declobsfunc("rh", "RHday", &NotUsed, TFun::INTVL, &rhday_intvls, true);

  if(Exist >= 0)
    Global::RH_EA_obs = 0;

  decldiag("EAday", TDim::NFREQ, "observation ea unavailable", "(kPa)", &NotUsed, &eaday_intvls);
  Exist = declobsfunc("ea", "EAday", &NotUsed, TFun::INTVL, &eaday_intvls, true);

  if(Exist >= 0)
    if(Global::RH_EA_obs < 0){
      Global::RH_EA_obs = 1;
      CRHMException TExcept("The obs module is using the observation ea instead of RH. This is not yet implemented.\
      An optioin is to use the filter '$rh rh(t, ea)' in the observarion file before the separator line,\
      '########################################'", TExcept::TERMINATE);
      LogError(TExcept);
    }

  declobsfunc("u", "Umean", &umean, TFun::AVG);

  declobsfunc("ppt", "pptD", &pptD, TFun::FIRST, NULL, true);

  declobsfunc("p", "p", const_cast<double **> (&p), TFun::FOBS, NULL, true);


  variation_set = VARIATION_0 + VARIATION_1;

  declparam("catchadjust", TDim::NHRU, "[0]", "0", "3", "none - 0/Nipher - 1/MacDonald-Alter - 2 (not recommended)/Smith-Alter - 3", "()", &catchadjust);

  decldiagparam("ppt_daily_distrib", TDim::NHRU, "[1]", "0", "1", "0 - daily precip in first interval, 1 - equally divided over the day", "()", &ppt_daily_distrib);

  declparam("snow_rain_determination", TDim::NHRU, "[0]", "0", "2", "snow/rain determination: 0 - air temperature, 1 - ice bulb temperature, 2 - Harder", "()", &snow_rain_determination);

  decldiagparam("tmax_allrain", TDim::NHRU, "[4.0]", "-10", "10", "precip all rain if HRU air/ice bulb temperature above or equal to this value. Not used in Harder method.",
    "(°C)", &tmax_allrain);

  decldiagparam("tmax_allsnow", TDim::NHRU, "[0.0]", "-10", "10", "precip all snow if HRU air/ice bulb temperature below this value. Not used in Harder method",
    "(°C)", &tmax_allsnow);


  variation_set = VARIATION_1;

  declreadobs("t_max", TDim::NHRU, " daily maximum temperature", "(°C)", &t_max, HRU_OBS_t_rh_ea);

  declreadobs("t_min", TDim::NHRU, " daily minimumn temperature", "(°C)", &t_min, HRU_OBS_t_rh_ea);


  variation_set = VARIATION_2;

  declreadobs("obs_snow", TDim::NHRU, "snow observation", "(mm)", &obs_snow, HRU_OBS_Q);

  declreadobs("obs_rain", TDim::NHRU, "rain observation", "(mm)", &obs_rain, HRU_OBS_Q);


  variation_set = VARIATION_ORG;
}

void Classobs::init(void) {

  if(this->GroupCnt < 2){ // display for simple project and first group

    if(ppt == NULL && p == NULL && variation != VARIATION_2){
      CRHMException TExcept("No precipitation data.  Both p and ppt not available!", TExcept::TERMINATE);
      LogError(TExcept);
    }

    if(ppt){
      CRHMException TExcept("using daily precipitation (ppt) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    if(p){
      CRHMException TExcept("using interval precipitation (p) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    if(variation == VARIATION_1 && Global::Freq != 1){
      CRHMException TExcept("obs#1 (using daily maximun/minimum temperatures) only works with daily data", TExcept::TERMINATE);
      LogError(TExcept);
    }

    if(Global::RH_EA_obs == -1){
      CRHMException TExcept("No psychrometric data.  Both relative humidity (rh) and vapour pressure (ea) observations not available.", TExcept::TERMINATE);
      LogError(TExcept);
    }
    else if(Global::RH_EA_obs == 1){
      CRHMException TExcept("using vapour pressure (ea) observation.", TExcept::WARNING);
      LogError(TExcept);
    }
    else if(Global::RH_EA_obs == 0){
      CRHMException TExcept("using relative humidity (rh) observation.", TExcept::WARNING);
      LogError(TExcept);
    }
  }

  nhru = getdim(TDim::NHRU);
  nobs = getdim(TDim::NOBS);

  for(hh = 0; hh < nhru; ++hh) {
    cumhru_rain[hh] = 0.0;
    cumhru_snow[hh] = 0.0;
    cumhru_snow_meas[hh] = 0.0;

    Pa[hh] = 101.3f*pow((293.0f-0.0065f*hru_elev[hh])/293.0f, 5.26f);  // kPa

    DTnow[0] = 0.0;
    DTindx[0] = 0;
  }

  Global::HRU_OBS = const_cast<long **> (HRU_OBS_Tables);

}

void Classobs::pre_run(void) {

  Global::HRU_OBS = const_cast<long **> (HRU_OBS_Tables);

  Global::OBS_ELEV = const_cast<double **> (obs_elev_Tables);

  Global::obs_t = const_cast<double **> (this->tday_intvls);

  Global::obs_ea = const_cast<double **> (this->eaday_intvls);

  Global::obs_rh = const_cast<double **> (this->rhday_intvls);

  Global::obs_t_obs = this->t_obs_lay;


  Global::Warming_t = const_cast<double *> (this->ClimChng_t); // must be here to switch for groups.

  Global::Warming_p = const_cast<double *> (this->ClimChng_precip); // must be here to switch for groups.

  Global::hru_elev = const_cast<double *> (this->hru_elev);

  Global::lapse_rate = const_cast<double *> (this->lapse_rate);

  Global::ppt_adj = const_cast<double *> (this->precip_elev_adj);

  Global::RH_VP_flag = const_cast<long *> (this->ElevChng_flag);

  Global::RH_VP_flag2 = const_cast<long *> (this->ClimChng_flag);

  
}

void Classobs::run(void) {

double catchratio;
double Tmean, Tmax, Tmin, RHmean, EAmean;

long  nstep = getstep()%Global::Freq;
long tt = Global::DTindx%Global::Freq;

DTnow[0] = (double) Global::DTnow;
DTindx[0] = Global::DTindx;

//added by Manishankar to solve the address issue.
if (this->t_layvalues != NULL && this->rh_layvalues != NULL)
{
    tday_intvls = this->t_layvalues;
    rhday_intvls = this->rh_layvalues;
}
  for (hh = 0; chkStruct(); ++hh) {

    hru_t[hh] = tday_intvls[tt][hh];

    hru_rh[hh] = rhday_intvls[tt][hh];

    hru_ea[hh] = eaday_intvls[tt][hh];

    hru_estar[hh] = Common::estar(hru_t[hh]);

    hru_u[hh]  = max<double> (u[hh], 5.0e-2);

    if(nstep == 1 || Global::Freq == 1){
      hru_umean[hh]  = umean[hh];

      switch (variation){
        case VARIATION_ORG:
        case VARIATION_2:
          Tmean = 0.0;
          Tmax = -999.0;
          Tmin = 999.0;
          RHmean = 0.0;
          EAmean = 0.0;
          for(long tt = 0; tt < Global::Freq; ++tt){
            Tmean += tday_intvls[tt][hh];
            if(tday_intvls[tt][hh] > Tmax)
              Tmax = tday_intvls[tt][hh];
            if(tday_intvls[tt][hh] < Tmin)
              Tmin = tday_intvls[tt][hh];
            RHmean += rhday_intvls[tt][hh];
            EAmean += eaday_intvls[tt][hh];
          }

          hru_tmean[hh]  = Tmean/Global::Freq;
          hru_tmax[hh]   = Tmax;
          hru_tmin[hh]   = Tmin;
          hru_eamean[hh] = EAmean/Global::Freq;
          hru_rhmean[hh] = RHmean/Global::Freq;

          break;
        case VARIATION_1:
          hru_tmax[hh] = t_max[hh]; // To get same results in different compilers
          hru_tmin[hh] = t_min[hh]; // To get same results in different compilers
          hru_tmean[hh]  = (hru_tmax[hh] + hru_tmin[hh])/2.0;
          hru_eamean[hh] = hru_ea[hh]; // daily - only one value
          hru_rhmean[hh] = hru_rh[hh]; // daily - only one value
          break;
        } // switch
    }

    double umean = hru_umean[hh];
    if(umean > 8.0) umean = 8;

    if(variation != VARIATION_2){

      switch(catchadjust[hh]) {  //


        case 1:  // Nipher
          catchratio = 0.01*(-0.387*sqr(umean)-2.022*umean+100.0);
          if(catchratio < 0.3) catchratio = 0.3;

        break;

        case 2:  // MacDonald-Alter (not correct, use Smith-Alter)
          catchratio = 1.01*exp(-0.09*umean);

          if(catchratio > 1.0) catchratio = 1.0;

        break;

        case 3:  // Smith-Alter
          if(p != NULL)
            catchratio = 1.18*exp(-0.18*hru_u[hh]);  // for hourly observed wind and precipitation
          if(ppt != NULL)
            catchratio = exp(-0.2*umean);  // for daily observed wind and precipitation

          if(catchratio > 1.0) catchratio = 1.0;

        break;

        default: // none

          catchratio = 1.0;

      } // end switch

      if(p != NULL) // insert p
        hru_p[hh]    = p[hh];
      else
        hru_p[hh] = 0.0;

      if(ppt != NULL){ // merge ppt
        if(!ppt_daily_distrib[hh] && tmax_allsnow[hh] >= hru_tmax[hh]){
          if(getstep()%Global::Freq == 1) // only for snow and option to add all first interval
            hru_p[hh]    += pptD[hh];
          else
            hru_p[hh]    += 0.0;
        }
        else // distribute over day
          hru_p[hh]    += pptD[hh]/Global::Freq;
      }

      hru_snow[hh] = 0.0;
      hru_rain[hh] = 0.0;
      hru_newsnow[hh] = 0;

      if(snow_rain_determination[hh] == 2){ // Harder
        Harder();
        if(hru_snow[hh] > 0.0){
          cumhru_snow_meas[hh] += hru_snow[hh];
          hru_snow[hh] /= catchratio;
          hru_newsnow[hh] = 1;

          if(hru_rain[hh] > 0.0)
            hru_p[hh] = hru_rain[hh] + hru_snow[hh];
          else
            hru_p[hh] = hru_snow[hh];
        }
      }
      else{
        double Use;
        if(snow_rain_determination[hh])
          Use = Common::Ice_Bulb(hru_t[hh], hru_rh[hh], Pa[hh]);
        else
          Use = hru_t[hh];

        if(hru_p[hh] > 0.0) { //rain or snow determined by temperature
          if(Use >= tmax_allrain[hh]) { // all rain
            hru_rain[hh] = hru_p[hh];
          }
          else if(Use <= tmax_allsnow[hh]) { // all snow
            cumhru_snow_meas[hh] += hru_p[hh];
            hru_snow[hh] = hru_p[hh]/catchratio;
            hru_p[hh] = hru_snow[hh];
            hru_newsnow[hh] = 1;
          }
          else { // mixed
            hru_rain[hh] = hru_p[hh]*(tmax_allrain[hh] - Use)/(tmax_allrain[hh] - tmax_allsnow[hh]);
            cumhru_snow_meas[hh] += (hru_p[hh] - hru_rain[hh]);
            hru_snow[hh] = (hru_p[hh] - hru_rain[hh])/catchratio;
            hru_p[hh] = hru_rain[hh] + hru_snow[hh];
            hru_newsnow[hh] = 1;
          }
        }
      } // end if
    }
    else{
      hru_rain[hh] = obs_rain[hh];
      hru_snow[hh] = obs_snow[hh];
      hru_p[hh] = hru_rain[hh] + hru_snow[hh];
      if(hru_snow[hh] > 0.0)
        hru_newsnow[hh] = 1;
      else
        hru_newsnow[hh] = 0;

      cumhru_snow_meas[hh] += hru_snow[hh];
    }

    cumhru_rain[hh] += hru_rain[hh];
    cumhru_snow[hh] += hru_snow[hh];
  }
}

void Classobs::Harder(void) {

  double Tk, D, lamda, pta, L, Ti1, Ti2, crit, crit1, T1, T2, a, b, c, ratio, hru_icebulb;

  Tk = hru_t[hh] + CRHM_constants::Tm;

  D = 0.0000206*pow(Tk/CRHM_constants::Tm, 1.75);

  lamda = 0.000063*Tk + 0.00673;

  pta = 18.01528*((hru_rh[hh]/100.0)*0.611*exp((17.3*hru_t[hh])/(237.3 + hru_t[hh])))/(0.00831441*(hru_t[hh] + CRHM_constants::Tm))/1000.0;

  if(hru_t[hh] > 0.0)

    L = 1000*(2501.0 - (2.361*hru_t[hh]));

  else

    L = 1000.0*(2834.1 - 0.29*hru_t[hh] - 0.004*hru_t[hh]*hru_t[hh]);

  Ti1 = 250.0;

  crit = 9999.0;

  while(crit > 0.0001){ //Iteration solution optimised by using the newton-raphston method

    T1 = Ti1 + 0.001*Ti1;

    T2 = Ti1 - 0.001*Ti1;

    a = (-Ti1 + Tk + (L*D/lamda)*(pta - (18.01528*(0.611*exp((17.3*(Ti1 - CRHM_constants::Tm))/(237.3 + (Ti1 - CRHM_constants::Tm))))/(0.00831441*Ti1)/1000)));

    b = (-T1  + Tk + (L*D/lamda)*(pta - (18.01528*(0.611*exp((17.3*(T1 - CRHM_constants::Tm))/(237.3 + (T1 - CRHM_constants::Tm))))/(0.00831441*T1)/1000)));

    c =(-T2 + Tk + (L*D/lamda)*(pta - (18.01528*(0.611*exp((17.3*(T2 - CRHM_constants::Tm))/(237.3 + (T2 - CRHM_constants::Tm))))/(0.00831441*T2)/1000)));

    Ti2 = Ti1 - (a/((b - c)/(0.002*Ti1)));

    crit1 = Ti1 - Ti2;

    if(crit1 < 0.0)

      crit = -crit1;

    else

      crit = crit1;

    Ti1 = Ti2;

  } // end while

  hru_icebulb = Ti1 - CRHM_constants::Tm;

  if(hru_icebulb < -10.0) //Eoverflow if ratio calculated with icebulb < -39C

    ratio = 0.0;

  else

    ratio = 1.0/(1.0 + 2.50286*pow(0.125006, hru_icebulb));

  hru_snow[hh] = 0.0;

  hru_rain[hh] = 0.0;

  if(hru_p[hh] > 0.0) //rain or snow determined by ice bulb ratio

    hru_rain[hh] = hru_p[hh]*ratio;

  hru_snow[hh] = hru_p[hh]*(1.0-ratio);
}

void Classobs::finish(bool good) {

  double Allcumhru_rain = 0.0;
  double Allcumhru_snow = 0.0;

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (obs)'  cumhru_rain      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumhru_rain[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (obs)'  cumhru_snow (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumhru_snow[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (obs)'  cumhru_snow_meas (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumhru_snow_meas[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");

    Allcumhru_rain += cumhru_rain[hh]*hru_area[hh];
    Allcumhru_snow += cumhru_snow[hh]*hru_area[hh];
    LogDebug(" ");
  }

  LogMessage(string("'" + Name + " (obs)' Allcumhru_rain (mm*basin): ").c_str(), Allcumhru_rain);
  LogMessage(string("'" + Name + " (obs)' Allcumhru_snow (mm*basin): ").c_str(), Allcumhru_snow, "*** adjusted snowfall");
  LogMessage(string("'" + Name + " (obs)' Allcumhru_ppt  (mm*basin): ").c_str(), Allcumhru_rain + Allcumhru_snow, "*** rainfall + adjusted snowfall");
  LogDebug(" ");
}