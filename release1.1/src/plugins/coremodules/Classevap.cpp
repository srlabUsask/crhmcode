//created by Manishankar Mondal

#include "Classevap.h"
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

Classevap* Classevap::klone(string name) const{
  return new Classevap(name);
}

void Classevap::decl(void) {

  Description = "'Calculates interval evaporation. Parameter \"evap_type\" selects Granger/Priestley-Taylor/Penman-Monteith.'";

  declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

  declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet); // , NULL, false, CRHM::DIAGNOSTIC

  declvar("hru_evap", NHRU, "interval evaporation", "(mm/int)", &evap);

  declvar("hru_evap_PT", NHRU, "Priestley-Taylor interval evaporation", "(mm/int)", &hru_evap_PT);

  declvar("hru_evapD", NHRU, "daily sum of interval evaporation", "(mm/d)", &evapD);

  declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation", "(mm)", &cum_evap);

  declvar("evapGrangerD", NHRU, "daily Granger evaporation", "(mm/d)", &evapGrangerD);

  decllocal("evap_G", NHRU, "relative evaporation", "()", &G);

  decllocal("evap_D", NHRU, "drying power", "()", &D);

  decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


  declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);

  declparam("evap_type", NHRU, "0", "0", "2", "Evaporation method for this HRU, 0 = Granger, 1 = Priestley-Taylor, 2 = Penman-Monteith.",
            "()", &evap_type);

  declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

  declparam("inhibit_evap_User", NHRU, "[0]", "0", "1", "inhibit evaporatation(User), 1 -> inhibit", "()", &inhibit_evap_User);

  decldiagparam("F_Qg", NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", &F_Qg);

  decldiagparam("rs", NHRU, "[0.0]", "0.0", "0.01", "stomatal resistance (Penman-Monteith); water 0.0, crops - 0.000579, short grass - 0.00081, forest - 0.002315", "(d/m)", &rs);

  declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height (Penman-Monteith)", "(m)", &Zwind);

  declgetvar("*", "Rn", "(mm/m^2*int)", &Rn);
  declgetvar("*", "RnD", "(mm/m^2*d)", &RnD);
  declgetvar("*", "RnD_POS", "(mm/m^2*d)", &RnD_POS);

  declgetvar("*",  "hru_t", "(°C)", &hru_t);
  declgetvar("*",  "hru_u", "(m/s)", &hru_u);
  declgetvar("*",  "hru_ea", "(kPa)", &hru_ea);

  declgetvar("*",  "hru_tmean", "(°C)", &hru_tmean);
  declgetvar("*",  "hru_umean", "(m/s)", &hru_umean);
  declgetvar("*",  "hru_eamean", "kPa", &hru_eamean);
}

void Classevap::init(void) {

  for(hh = 0; chkStruct(); ++hh) {

    Pa[hh] = 101.3f*pow((293.0f-0.0065f*hru_elev[hh])/293.0f, 5.26f);  // kPa
    cum_evap[hh] = 0.0;
    hru_cum_actet[hh] = 0.0;
    D[hh] = 0.0;
    G[hh] = 0.0;
  }
}

void Classevap::run(void) {

   double Q;

   long nstep = getstep() % Global::Freq;


   for(hh = 0; chkStruct(); ++hh) {

     evap[hh] = 0.0;
     hru_evap_PT[hh] = 0.0;
     hru_actet[hh] = 0.0;

     if(inhibit_evap[hh] || inhibit_evap_User[hh]){
       evapD[hh] = 0.0;
       evapGrangerD[hh] = 0.0;
       continue;
     }

     if(nstep == 1 || Global::Freq == 1) { // beginning of every day

       evapD[hh] = 0.0;
       evapGrangerD[hh] = 0.0;

       Q = RnD[hh]*(1.0 - F_Qg[hh]); // daily value (mm/d)

       if(Q > 0.0) {
         double Eal = fdaily(hru_umean[hh], Ht[hh])*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]);
         if(Eal > 0.0){
           D[hh] = Eal / ( Eal + Q);
           if(D[hh] > 1.0)
             D[hh] = 1.0;
         }
         else // happens when hru_eamean[hh] > hru_tmean[hh] because of lapse rate adjustment with increased height
           D[hh] = 0.0;

         G[hh] = 1.0 / ( 0.793 + 0.2*exp(4.902*D[hh])) + 0.006 * D[hh];
         evapGrangerD[hh] = (delta(hru_tmean[hh]) * G[hh] * Q + gamma(Pa[hh], hru_tmean[hh]) *
           G[hh] * Eal)/(delta(hru_tmean[hh]) * G[hh] + gamma(Pa[hh], hru_tmean[hh]));
       }
     }

// calculated every interval

     Q = Rn[hh]*(1.0 - F_Qg[hh]); // (mm/d)

     switch (evap_type[hh]){

       case 0: // Granger
         if(Q > 0.0 && evapGrangerD[hh] > 0.0 && RnD_POS[hh] > 0.0)
           evap[hh] = Q/RnD_POS[hh]/(1.0 - F_Qg[hh])*evapGrangerD[hh];
         else
           evap[hh] = 0.0;
         break;

       case 1: // Priestley-Taylor
         if(Q > 0.0)
           evap[hh] = 1.26*delta(hru_t[hh])*Q/(delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));
         else
           evap[hh] = 0.0;

         break;

       case 2: // Penman-Monteith
         if(Q > 0.0) {

           double Z0 = Ht[hh]/7.6;
           double d  = Ht[hh]*0.67;
           double ra = sqr(log((Zwind[hh] - d)/Z0))/(sqr(CRHM_constants::kappa)*hru_u[hh]);
           double RHOa = 1E3*Pa[hh] /(CRHM_constants::Rgas*(hru_t[hh] + CRHM_constants::Tm))*(1.0 - 0.379*hru_ea[hh]/Pa[hh]);
           double Cp = 1.005; // (kJ/kg/K)

           evap[hh] = (delta(hru_t[hh])*Q*Global::Freq + (RHOa*Cp/
                        (lambda(hru_t[hh])*1e3)*(Common::estar(hru_t[hh]) - hru_ea[hh])/(ra/86400)))/
                       (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])*(1.0 + rs[hh]/ra))/
                        Global::Freq;
         }
         else
           evap[hh] = 0.0;

         break;

     } // switch

     if(Q > 0.0) // Priestley-Taylor always calculated
       hru_evap_PT[hh] = 1.26*delta(hru_t[hh])*Q/(delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));

     cum_evap[hh] += evap[hh];
     evapD[hh] += evap[hh];
   } // for
}

void Classevap::finish(bool good) {

  double Allcum_evap = 0.0;
  double Allcum_actet = 0.0;

  string Evap_names[] = {"Granger", "Priestley-Taylor", "Penman-Monteith", "Dalton Bulk transfer"}; //added this array here. It has another instance in NewModules.cpp.

  for(hh = 0; chkStruct(); ++hh) {

    string s = "**** " + Evap_names[evap_type[hh]] + " ****";
    LogMessageA(hh, string("'" + Name + " (evap)' hru_cum_evap    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_evap[hh], hru_area[hh], basin_area[0], s.c_str());
    LogMessageA(hh, string("'" + Name + " (evap)' hru_cum_actet   (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");

    Allcum_evap += cum_evap[hh]*hru_area[hh];
    Allcum_actet += hru_cum_actet[hh]*hru_area[hh];
  }

  LogMessage(string("'" + Name + " (evap)' Allcum_evap  (mm*basin): ").c_str(), Allcum_evap, "*** potential evaporation");
  LogMessage(string("'" + Name + " (evap)' Allcum_actet (mm*basin): ").c_str(), Allcum_actet, "*** actual evaporation");
  LogDebug(" ");

}

double Classevap::gamma(double Pa, double t) // Psychrometric constant (kPa/°C)
{
   return( 0.00163 * Pa / lambda(t)); // lambda (mJ/(kg °C))
}

double Classevap::lambda(double t) // Latent heat of vaporization (mJ/(kg °C))
{
   return( 2.501 - 0.002361 * t );
}

double Classevap::delta(double t) // Slope of sat vap p vs t, kPa/°C
{
  if (t > 0.0)
    return(2504.0*exp(17.27 * t/(t+237.3)) / sqr(t+237.3));
  else
    return(3549.0*exp( 21.88 * t/(t+265.5)) / sqr(t+265.5));
}

double Classevap::fdaily(double u, double Ht){ // Drying power f(u) (mm/d/kPa)

   double Z0 = Ht*100.0/7.6;
   double a = 8.19 + 0.22*Z0;
   double b = 1.16 + 0.08*Z0;
   return a + b*u;
}