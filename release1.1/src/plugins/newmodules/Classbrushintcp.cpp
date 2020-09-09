//created by Manishankar Mondal

#include "Classbrushintcp.h"
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

Classbrushintcp* Classbrushintcp::klone(string name) const{
  return new Classbrushintcp(name);
}

void Classbrushintcp::decl(void) {

  declvar("SnowLoad", NHRU, "Canopy snow load", "(kg/m^2)", &Load);

  declvar("Thru", NHRU, "Canopy fall through", "(kg/m^2)", &Thru);

  declstatvar("cumThru", NHRU, "Cumulative canopy fall through", "(mm)", &cumThru);

  declvar("brushsubl", NHRU, "Canopy snow sublimation", "(mm/int)", &brushsubl);

  declstatvar("cumbrushsubl", NHRU, "Cumulative canopy snow sublimation", "(mm)", &cumbrushsubl);

  declvar("spherecoeff", NHRU, "pan to sphere coefficient", "(mm/g)", &spherecoeff);

  declvar("net_rain", NHRU, "hru_rain minus interception", "(mm/int)", &net_rain);

  declstatdiag("cum_net_rain", NHRU, "cumulative hru_rain minus interception", "(mm)", &cum_net_rain);

  declvar("net_snow", NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

  declvar("net_p", NHRU, "hru_precipitation (rain and/or snow) less interception", "(mm/int)", &net_p);

  declvar("intcp_evap", NHRU, "HRU Evaporation from interception", "(mm/int)", &intcp_evap);


  declparam("Ht", NHRU, "[20.0]", "0.001", "100.0", "Canopy height", "(m)", &Ht);

  declparam("Zcan", NHRU, "10.0", "0.0", "100.0", "Mid-canopy wind modelling height", "(m)", &Zcan);

  declparam("Zref", NHRU, "[20.0]", "0.0", "100.0", "Reference height. Set <= 0.0 to disable this module for this HRU", "(m)", &Zref);

  declparam("Sbar", NHRU, "6.6", "0.0", "20.0", "Uncorrected snow capacity", "(kg/m^2)", &Sbar);

  declparam("LAI", NHRU, "[2.2]", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

  declparam("WidthJ", NHRU, "[75]", "0.0", "100.0", "Canopy forested downwind distance", "(m)", &WidthJ);

  declparam("brushAtten", NHRU, "[1.0]", "0.2", "10.0", "Brush attenuation coefficient", "()", &brushAtten);

  declparam("Tunload", NHRU, "0.0", "-5.0", "5.0", "Canopy unload at daily mean temperature", "(°C)", &Tunload);

  declparam("basin_area", ONE, "3", "0.01", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "0.01", "1e+09", "hru area", "(km^2)", &hru_area);

  declgetvar("obs",  "hru_t", "(°C)", &hru_t);
  declgetvar("obs",  "hru_tmean", ", (°C)", &hru_tmean);
  declgetvar("obs",  "hru_rh", "()", &hru_rh);
  declgetvar("obs",  "hru_u", "(m/s)", &hru_u);
  declgetvar("obs",  "hru_rain", "(mm)", &hru_rain);
  declgetvar("obs",  "hru_snow", "(mm)", &hru_snow);
  declgetvar("obs",  "hru_p", "(mm)",  &hru_p);

  declputvar("pbsm", "cumSubl", "(mm)", &cumSubl);
}

void Classbrushintcp::init(void) {
  nhru = getdim(NHRU);

  for(hh = 0; chkStruct(); ++hh) {
    net_p[hh] = 0.0;
    net_rain[hh] = 0.0;
    net_snow[hh] = 0.0;
    brushsubl[hh] = 0.0;
    cumbrushsubl[hh] = 0.0;
    Thru[hh] = 0.0;
    cumThru[hh] = 0.0;
    Load[hh] = 0.0;
    intcp_evap[hh] = 0.0;
    spherecoeff[hh] = 0.0;
    cum_net_rain[hh] = 0.0;
  }
}

void Classbrushintcp::run(void) {

  const float LATH = 2.838E6; // latent heat of sublimation (J/kg) List 1949
  const float Qstar = 120;    // Solar Radiation Input
  const float Mpr = 0.5E-3;
  const float Cc = 0.82;
  const float Velw = 0.75;
  const float KARMAN = 0.4;
  const float KinVisc = 1.88e-5;     // kinematic viscosity of air (Sask. avg. value)
  const float M = 18.01;      //{molecular weight of water (kg/kmole)}
  const float R = 8313;       //{universal gas constant (J/(kmole K))}


  for(hh = 0; chkStruct(); ++hh) {

    if(Zref[hh] > 0.0) {

      Thru[hh]= 0.0;

      if(hru_tmean[hh] > Tunload[hh]) {
        Thru[hh] = Load[hh] + hru_snow[hh];
        Load[hh] = 0.0;
      }
      else {

        float RhoS = 67.92 + 51.25*exp(hru_t[hh]/2.59);
        float Lstar = Sbar[hh]*(0.27 + 46.0/RhoS)*LAI[hh];

        if(Load[hh] > Lstar) { // after increase in temperature
          Thru[hh] = Load[hh] - Lstar;
          Load[hh] = Lstar;
        }

        if(hru_snow[hh] > 0.0) {
          float Cp = Cc/(1.0 - (Cc*hru_u[hh]*Ht[hh])/(Velw*WidthJ[hh]));
          if(Cp <= 0.0 || Cp > 1.0) Cp = 1.0;

          float I1 = (Lstar-Load[hh])*(1 - exp(-Cp*hru_snow[hh]/Lstar));

          Load[hh] = Load[hh] + I1; // add new snowfall
          Thru[hh] = Thru[hh] + (hru_snow[hh] - I1); // remainder falls thru

        }

        if(Load[hh] > 0.0) {

          float Z0m = Ht[hh]/10.0;
          float Disp = Ht[hh]*0.7;
          float Ustar = hru_u[hh]*KARMAN/(log((Zref[hh]-Disp)/Z0m));
          float Uh = Ustar*(log((Ht[hh]-Disp)/Z0m))/KARMAN;

          float CanVent = Uh*exp(brushAtten[hh]*(Zcan[hh]/Ht[hh]-1.0));  /* calculates canopy windspd  */

          float Reyn = 2*Mpr*CanVent/KinVisc;
          float Nuss = 1.79+0.606*sqrt(Reyn);

          float Temp = hru_t[hh] + 273.15;
          float Lamb = 0.00063*Temp + 0.0673;                // therm. cond. of atm. (J/(msK))
          float Diff = 2.06E-5*pow(Temp/273.0, 1.75);        // diffus. of w.vap. atmos. (m2/s)
          float Sigma2 = hru_rh[hh]/100.0 - 1.0;             // undersaturation at 2 m
          float Htran = 0.9 * M_PI * sqr(Mpr) * Qstar;

          float SigmaZ = Sigma2 * (1.019 + 0.027 * log(Zcan[hh]));  // Eq. 6.20, Revised in May. 1997
          if(SigmaZ > -0.01) {SigmaZ = -0.01;}

          float A = Lamb * Temp * Nuss;
          float B = LATH * M/(R * Temp) - 1.0;
          float C = 1.0/(Diff * Common::SVDens(hru_t[hh]) * Nuss);
          float DmDt = -((2.0*M_PI * Mpr * SigmaZ) - (Htran*B/A))/((LATH*B/A) + C);
          DmDt *= 24.0*3600.0/Global::Freq; // convert to interval

          spherecoeff[hh] = 17.6*pow(cumbrushsubl[hh] + 0.001, -0.086);

          brushsubl[hh] = DmDt*spherecoeff[hh]*1000.0; //convert kg to gm

          if(brushsubl[hh] > Load[hh]) {
            brushsubl[hh] = Load[hh];
            Load[hh] = 0.0;
          }
          else
            Load[hh] -= brushsubl[hh];

          cumbrushsubl[hh] += brushsubl[hh];
          cumSubl[hh] += brushsubl[hh];
        }
      }

      net_snow[hh] = Thru[hh];
      cumThru[hh] += Thru[hh];

      net_rain[hh] = hru_rain[hh];
      net_p[hh] = hru_p[hh];
    }
    else {
      net_p[hh] = hru_p[hh];
      net_snow[hh] = hru_snow[hh];
      net_rain[hh] = hru_rain[hh];
    }
    cum_net_rain[hh] += net_rain[hh];
  }
}

void Classbrushintcp::finish(bool good) {
  for(hh = 0; chkStruct(); ++hh) {
    if(Zref[hh] > 0.0) {
      LogMessageA(hh, "'brushintcp' cumThru     (mm) (mm*hru) (mm*hru/basin): ", cumThru[hh], hru_area[hh], basin_area[0]);
      LogMessageA(hh, "'brushintcp' cumbrushsubl(mm) (mm*hru) (mm*hru/basin): ", cumbrushsubl[hh], hru_area[hh], basin_area[0]);
    }
    LogMessageA(hh, "'brushintcp' cumnetrain    (mm) (mm*hru) (mm*hru/basin): ", cum_net_rain[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}