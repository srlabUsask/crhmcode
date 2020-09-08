//created by Manishankar Mondal

#include "Classpbsm.h"
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

Classpbsm* Classpbsm::klone(string name) const{
  return new Classpbsm(name);
}

void Classpbsm::decl(void) {

  Description = "'calculates snow transport and sublimation (Pomeroy and Li, 1999).' \
                 'original version using hru_u,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u,' \
                 'using hru_u and a regression to use daily windspeed,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u and a regression to use daily windspeed.'";

  variation_set = VARIATION_0 + VARIATION_2;

  declgetvar("*", "hru_u", "(m/s)", &hru_u);


  variation_set = VARIATION_1 + VARIATION_3;

  declgetvar("*", "hru_Uadjust", "(m/s)", &hru_Uadjust);


  variation_set = VARIATION_2 + VARIATION_3;

  declparam("u_D", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed correction", "()", &u_D);

  declparam("Drift_offset", NHRU, "[0.0]", "0.0", "100.0", "Daily windspeed drift offset correction", "()", &Drift_offset);

  declparam("Drift_slope", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed drift slope correction", "()", &Drift_slope);

  declparam("Subl_offset", NHRU, "[0.0]", "0.0", "100.0", "Daily windspeed sublimation offset correction", "()", &Subl_offset);

  declparam("Subl_slope", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed sublimation slope correction", "()", &Subl_slope);


  variation_set = VARIATION_ORG;


  declstatvar("SWE", NHRU, "snow water equivalent", "(mm)", &SWE);

  declvar("Subl", NHRU, "interval sublimation", "(mm/int)", &Subl);

  declvar("Drift", NHRU, "interval transport", "(mm/int)", &Drift);

  decldiag("DriftH", NHRU, "interval transport", "(mm/int)", &DriftH);

  decldiag("SublH", NHRU, "interval sublimation", "(mm/int)", &SublH);

  decldiag("BasinSnowLoss", BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

  declstatdiag("cumSubl", NHRU, "cumulative sublimation", "(mm)", &cumSubl);

  declstatdiag("cumDrift", NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

  declstatdiag("cumBasinSnowLoss", BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

  declstatdiag("cumBasinSnowGain", BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

  declstatdiag("cumDriftIn", NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

  decllocal("hru_basin", NHRU, "conversion factor", "()", &hru_basin);

  decldiag("DrySnow", NHRU, "DrySnow", "()", &DrySnow);

  declstatdiag("SnowAge", NHRU, "SnowAge", "()", &SnowAge);

  declstatdiag("cumSno", NHRU, "cumulative snow", "(mm)", &cumSno);

  declvar("Prob", NHRU, "Probability", "()", &Prob);

  declvar("snowdepth", NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);

  declvar("rain_on_snow", NHRU, "mass of rain falling on snowcover", "(mm/int)", &rain_on_snow);

  declvar("cumrain_on_snow", NHRU, "cumulative rain on snow", "(mm)", &cumrain_on_snow);

  decllocal("SWE_Init", NHRU, "initial SWE", "(mm)", &SWE_Init);

/* parameters */

  declparam("fetch", NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

  declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

  declparam("distrib", NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - can sum to 1", "()", &distrib);

  decldiagparam("N_S", NHRU, "[320]", "1", "500", "vegetation number density", "(1/m^2)", &N_S);

  decldiagparam("A_S", NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", &A_S);

  declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporatation(System use only), 1 -> inhibit", "()", &inhibit_evap);

  decldiagparam("inhibit_bs", NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", &inhibit_bs);

  decldiagparam("inhibit_subl", NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

  declgetvar("*", "hru_t", "(°C)", &hru_t);
  declgetvar("*", "hru_rh", "(%)", &hru_rh);
  declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
  declgetvar("*", "net_snow", "(mm/int)", &net_snow);
  declgetvar("*", "net_rain", "(mm/int)", &net_rain);

}

void Classpbsm::init(void) {

  nhru = getdim(NHRU);

  cumBasinSnowLoss[0] = 0.0;
  cumBasinSnowGain[0] = 0.0;

  for (hh = 0; hh < nhru; ++hh) {
    SWE[hh] = 0.0;
    cumDrift[hh] = 0.0;
    cumDriftIn[hh] = 0.0;
    cumSubl[hh] = 0.0;
    cumSno[hh] = 0.0;
    SnowAge[hh] = 0.0;
    DrySnow[hh] = 0;
    snowdepth[hh] = 0.0;
    rain_on_snow[hh] = 0.0;
    cumrain_on_snow[hh] = 0.0;;

    if((hh > 0) && (Ht[hh] < Ht[hh-1]) && distrib[hh-1] > 0){
      CRHMException TExcept(string("'" + Name + " (pbsm)' vegetation heights not in ascending order.").c_str(), WARNING);
      LogError(TExcept);
    }
  }

  for (hh = 0; hh < nhru; ++hh)
    hru_basin[hh] = hru_area[hh]/basin_area[0];
}

/*****************************
  PBSMrun - PBSM module run function
  10/28/99 (tb) 06/11/99

******************************/

 // DepthofSnow

//float SWEfromDepth(float Snow_Depth){ // 3/5/98 Calculates SWE(mm) from Snow Depth(m)
//
//  float SWE;
//
//  if (Snow_Depth > 0.6)
//    SWE = 4.5608*Snow_Depth*100.0-128.06;
//  else if (Snow_Depth > 0.0205)
//    SWE = 2.39*Snow_Depth*100.0+2.05;
//  else
//    SWE = Snow_Depth;
//
//  return SWE;
//} // SWEfromDepth

void ProbabilityThresholdNew(float SWE, float t, float Uten_Prob, float & Probability, float & Threshold,
                             long Snow, float & SnowAge, long & DrySnow){

//Probability of blowing snow occurrence and threshold wind speeds determined by ambient air temperature and snow age

   float Wind, Mean, Variance, c;

        Wind = 0.0;
        Probability = 0.0;

   if(SWE <= 0.0) {   //no snow available
        DrySnow = false;
        SnowAge = 0.0;
        Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); // (m/s)
   }

   else if((Snow == true) && (t < 0.0))
   {
// with concurrent snowfall: new dry snow
        DrySnow = true;
        SnowAge = 24.0/Global::Freq;

        Mean = 0.365 * t + 0.00706 * sqr(t)
              + 0.91 * log((float)SnowAge) + 11.0;
        Variance = 0.145 * t + 0.00196 * sqr(t) + 4.23;

        while ((Wind <= Uten_Prob) && (Uten_Prob >= 3.0)) {
// Wind < 3 m/s too weak for dry snow transport

           Wind = Wind + 0.1;

           c = (-sqr(Wind - Mean))/(2.0*sqr(Variance));

           Probability = Probability + (1.0/(Variance * 2.5055)) * (exp(c)) * 0.1;
        } // {while do}
        Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); // (m/s)
   } // {if}

   else if((t < 0.0) && DrySnow)
   {
// {without concurrent snowfall: old dry snow}
        SnowAge = SnowAge + 24.0/Global::Freq;

        Mean = 0.365 * t + 0.00706 * sqr(t)
              + 0.91 * log((float)SnowAge) + 11.0;
        Variance = 0.145 * t + 0.00196 * sqr(t) + 4.23;

        while ((Wind <= Uten_Prob) && (Uten_Prob >= 3.0)) {
// Wind < 3 m/s too weak for dry snow transport
           Wind = Wind + 0.1;

           c = (-sqr(Wind - Mean))/(2.0*sqr(Variance));

           Probability = Probability + (1.0/(Variance * 2.5055)) * (exp(c)) * 0.1;
         } // while do

       Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); //(m/s)
   } // if
   else if ((t >= 0.0)  || !DrySnow)
   {
        DrySnow = false;             // or wet snow remains on the ground
        SnowAge = 0.0;
        Mean = 21.0;
        Variance = 7.0;

        while ((Wind <= Uten_Prob) && (Uten_Prob >7.0)) {    // loop to calculate P.
// wind < 7 m/s too weak for wet snow transport
            Wind = Wind + 0.1;
            c = (-sqr(Wind - Mean))/(2.0*sqr(Variance));
            Probability = Probability + (1.0/(Variance * 2.5055)) * (exp(c)) * 0.1;
        } // while do
        Threshold = 9.9;     // (m/s)
   } //if

} // Probability_threshold procedure

void Sum(float TQsalt, float TQsusp, float SBsum, float SBsalt, float & DriftH, float & SublH){

// total sublimation

   if  ((SBsum + SBsalt) >= 0.0)
     SublH = 0.0;
   else
     SublH = (SBsum + SBsalt)*(-1E+3); // -mgmm2s to mg/m^2/s to g/m^2/s

   DriftH = (TQsalt + TQsusp); // kg/m-width/s
// Convert to interval values

   SublH = SublH * Global::Interval*3600*24/1000.0; // g/m^2/s to mm/m^2/interval
   DriftH = DriftH * Global::Interval*3600*24;      // kg/m-width/s to kg/m-width/interval

} // sum procedure

void Pbsm (float E_StubHt, float Uthr, float & DriftH, float & SublH,
           float t, float u, float rh, float Fetch, long N_S, float A_S)
{

/*   Modified Calculations for Mean Particle Mass in this version
     program to calculate blowing snow horizontal flux, sublimation rate
     and latent heat flux due to snow sublimation for a variety of windspeeds,
     boundary layers and surface conditions.

     All variable and constants entered into the programme are in SI and
     use Canadian Atmospheric Environement Service Meteorological data
     format.  Snow transport is in kg per square meter per half hour
     from the surface to 5 metres height.  Sublimation is totaled to the top
     of the boundary layer for diffusion, based on the meteorological
     Fetch and is expressed in millimeters of blowing snow lost over
     a square meter of snow surface per half hour  */

  float   A,      Alpha,  B,      Bd,     Bound,  C,
  Diff,   DmDt,   Es,     H,
  Htran,  Hsalt,  Inc,    Lamb,   Lambda, Lb,
  Mpm,    Mpr,    Nh,     Nsalt,
  Nz,     Nuss,   Omega,  TQsalt,
  TQsum,  Qz,     RauTerm,Temp,
  Reyn,   SBsalt, Sbz,    SBsum,
  SigmaZ, Sigma2, SvDens, Usthr,  Ustar,
  UstarZ, Uz,     Vs,     Vsalt,  Sigma,
  Vsusp,  Z,      Zr,     Zstb;

//Compute stubble coefficients

   Zstb = 0.005*N_S*A_S*E_StubHt*100.0;      // Lettau, used for susp Z0''
   Lambda = N_S*A_S*E_StubHt;         // Raupach Eq. 1
   Sigma = (M_PI*A_S)/(4.0*E_StubHt); // Raupach Eq. 4

// Calculate the flux for interval
   TQsalt = 0.0;                      // Total saltation flux
   TQsum = 0.0;                       // Total Suspension
   SBsalt = 0.0;
   SBsum = 0.0;
   DriftH = 0.0;
   SublH = 0.0;

   Temp  = t + 273.0;                 // Convert to Deg. K

// Check for data errors    Fluxes set to zero for the interval
   if((Temp < 0.0) || (u < 1.0) || (rh < 0.01)) {return;}

   if(rh >= 1.0) rh = rh/100.0;       // handle %rh

   Lamb = 0.000076843*Temp + 0.003130762;   // therm. cond. of atm. (J/(msK))
   Diff = 2.06e-5f*pow(Temp/273.0f, 1.75f); // diffus. of w.vap. atmos. (m^2/s
   B = PBSM_constants::LATH * PBSM_constants::M/(PBSM_constants::R * Temp) - 1.0;

// find undersaturation of w. vapour at 2 metres
   Es = 611.15f * exp(22.452f*(Temp - 273.0f)/Temp);  //{sat pressure}
   SvDens = (Es*PBSM_constants::M)/(PBSM_constants::R*Temp);                       //{sat density}
   Sigma2 = rh - 1.0;                              //{undersaturation at 2 m}

   if(u > Uthr) {

// define saltation parameters and calculate saltation
//    rate using 10/1987 MODEL OF BLOWING SNOW EQUATIONS

      Usthr = 0.03697f*Uthr;                                  //{Eq. 6.3}
      Ustar = 0.02264f*pow(u, 1.295f);
      if(E_StubHt > 0.0001)                         //{Eq. 6.2 rev}
        RauTerm  = 1.0/((1.0-Sigma*Lambda)*(1.0+PBSM_constants::Beta*Lambda)); //{Raupach}
      else
        RauTerm  = 1.0;

      Hsalt = PBSM_constants::C2/(2.0f*PBSM_constants::g)*sqr(Ustar);                         //{Eq. 4.13}
      Nsalt = 2.0*PBSM_constants::rho/(PBSM_constants::C2*PBSM_constants::C3*Ustar)*(RauTerm - sqr(Usthr)/sqr(Ustar)); //{Eq. 4.14 updated}

      if(Nsalt <= 0.0) {
         Sum (TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
         return;
      }

      TQsalt = PBSM_constants::C1*PBSM_constants::rho*Usthr/(PBSM_constants::g*PBSM_constants::C3*Ustar)*(sqr(Ustar)*RauTerm - sqr(Usthr)); // Eq. 4.20

// calculate sublimation rate in the saltation layer

      Mpr= 100E-6;
      Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
      Alpha = 5.0;

      SigmaZ = Sigma2 * (1.019 + 0.027 * log(Hsalt)); // Eq. 6.20, Revised in May. 1997
      if(SigmaZ > -0.01) {SigmaZ = -0.01;}
      Vsalt = 0.6325 * Ustar + 2.3 * Usthr;          // Eq. 6.25
      Reyn = (2.0 * Mpr * Vsalt)/1.88E-5;            // Eq. 6.22
      Nuss = 1.79 + 0.606 * sqrt(Reyn);              // Eq. 6.21
      A = Lamb * Temp * Nuss;
      C = 1.0/(Diff * SvDens * Nuss);
      DmDt = ((2.0 * M_PI * Mpr * SigmaZ) - (Htran * B/A))/((PBSM_constants::LATH * B/A) + C);

      //{Eq. 6.16} {Gamma Dist. Corr.}
      Mpm = 4.0/3.0 * M_PI * PBSM_constants::DICE * Mpr*sqr(Mpr) *(1.0 + 3.0/Alpha + 2.0/sqr(Alpha));

      Vs = DmDt/Mpm;                // Sublimation rate coefficient Eq. 6.13
      SBsalt = Vs * Nsalt * Hsalt;  // Eq. 6.11

// calculate mass flux in the suspended layers and the sublimation
//     rate for layers of height Inc from height r to b

      Zr = 0.05628 * Ustar;         // Eq. 5.27
      Alpha = 15.0;
      Inc = 0.0001;

// Loop to find the first suspended drift density level, r
//     from the reference level Zr
//     To preserve continuity with saltation the first suspended
//     level drift density is less than or equal to Nsalt.

      TQsum = 0;
      SBsum = 0;

      Z = Zr + Inc;
      while (Z <= 0.15) {
         Nz = 0.8 * exp(-1.55*(pow(0.05628f*Ustar, -0.544f) - pow(Z, -0.544f)));

// Eq. 5.26, Revised in Dec. 1995
         if(Nz <= Nsalt) {goto Ten;}
         Z = Z + Inc;
      } //while
Ten:  Lb = Z + Inc;
      Z = Lb;
      Inc = 0.001;

// find height of fully-developed boundary layer for turbulent
//     diffusion using a form of Pasquills plume dispersion eq.
//     iterate towards Bound

      Bd = 1.0;
      Bound = PBSM_constants::ZD + (PBSM_constants::KARMAN2 * (Fetch - PBSM_constants::XD) * pow(log(Bd * 162.926f/
        sqr(Ustar)) * log(PBSM_constants::ZD * 162.926f/sqr(Ustar)), -0.5f));          // Eq. 6.9
      while (fabs(Bound - Bd) > 0.001) {
         Bd = Bound;
         Bound = PBSM_constants::ZD + (PBSM_constants::KARMAN2 * (Fetch - PBSM_constants::XD) * pow(log(Bd * 162.926f/
            sqr(Ustar)) * log(PBSM_constants::ZD * 162.926f/sqr(Ustar)), -0.5f));      // Eq. 6.9
      } //while


// Loop to calculate the suspended mass flux up to 5 metres
//     and the total sublimation rate to the top of the boundary layer
//   at increments of 1 mm to 50cm & increments of 10 cm to  b

Twenty: H = Z + Inc;
      while (H <= Bound) {
         Nh = 0.8 * exp(-1.55f*(pow(0.05628f*Ustar, -0.544f) - pow(H, -0.544f)));
         Nz = Nh;
         UstarZ = Ustar * pow(1.2f/(1.2f + Nz), 0.5f);                  // Eq. 5.17a
         Uz = (UstarZ/PBSM_constants::KARMAN) *log(H/((0.00613f *sqr(Ustar)) + Zstb));// Eq. 4.17r
         if(Uz > 0) {
	   Mpr = 4.6e-5 * pow(H, -0.258f);                            // Eq. 6.15
           if(H >= 5.0) {Mpr = 30E-6f;}

           Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
           Alpha = 4.08 + 12.6 * H;                                  // Eq. 6.14
           if(H >= 1.5) {Alpha = 25.0;}

           SigmaZ = Sigma2 * (1.019 + 0.027 * log(H));  // Eq. 6.20, Revised in May. 1997
           if(SigmaZ > -0.01) {SigmaZ = -0.01;}
	   Omega = 1.1e7f * pow(Mpr, 1.8f);               // Eq. 5.18
	   Vsusp = Omega + 0.0106f * pow(Uz, 1.36f);
           Reyn = (2.0f * Mpr * Vsusp)/1.88e-5f;          // Eq. 6.22
           Nuss = 1.79f + 0.606f * sqrt(Reyn);            // Eq. 6.21
           A = Lamb * Temp * Nuss;
           C = 1.0/(Diff * SvDens * Nuss);
           DmDt = ((2.0f*M_PI * Mpr * SigmaZ) - (Htran*B/A))/((PBSM_constants::LATH*B/A) + C);
           Mpm = 1.333f * M_PI * PBSM_constants::DICE * sqr(Mpr)*Mpr *   // Eq. 6.16
              (1.0f + 3.0f/Alpha + 2.0f/sqr(Alpha));       // Gamma Dist. Corr.
           Vs = DmDt/Mpm;                               // Eq. 6.13
           Sbz = Vs * Nz * Inc;                         // mg
           SBsum = SBsum + Sbz;                         // Eq. 6.12
           Qz = Nz * Uz * Inc;                          // Eq. 5.4
	   if(H >= 5.0) {Qz = 0.0;}
           TQsum = TQsum + Qz;                          // Eq. 5.5
	   if(Nz >= 1e-5) {
              if(((H-Inc) >= 0.5) && (H < 0.6)) {
                Inc = 0.1;
                Z = 0.5;
                goto Twenty;                            // re start the loop
              } //{if}
           }
           else {
              Sum (TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
              return;
           } // if
         }
         else {
            TQsalt = 0.0;
            TQsum = 0.0;
            SBsalt = 0.0;
            SBsum = 0.0;
            Sum (TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
            return;
         } // if
         H = H + Inc;
      } // while
   } // if
   Sum (TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
} //PBSM procedure}

void Classpbsm::run(void) {

  float Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
  float SumDrift, total, SWE_Max, transport;
  long step = getstep();

  if(step == 1)
    for (hh = 0; chkStruct(); ++hh)
      SWE_Init[hh] = SWE[hh];

  for (hh = 0; chkStruct(); ++hh) {

    if(net_snow[hh] > 0.0) {
      SWE[hh] = SWE[hh] + net_snow[hh];
      cumSno[hh] = cumSno[hh] + net_snow[hh];
    }

   if(variation == VARIATION_ORG || variation == VARIATION_2)
     hru_u_ = hru_u[hh];
   else
     hru_u_ = hru_Uadjust[hh];

   if(variation == VARIATION_2 || variation == VARIATION_3)
     hru_u_ = u_D[hh]*hru_u_;

   Drift[hh] = 0.0;
   Subl[hh] = 0.0;
   DriftH[hh] = 0.0;
   SublH[hh] = 0.0;
   Prob[hh] = 0.0;

   if(SWE[hh] > 0.0 && net_rain[hh] > 0.0){
     rain_on_snow[hh] = net_rain[hh];
     cumrain_on_snow[hh] += net_rain[hh];
   }
   if(SWE[hh] > 0.0 && !inhibit_bs[hh]) {

     E_StubHt = Ht[hh] - Common::DepthofSnow(SWE[hh]); // depths(m) SWE(mm)
     if(E_StubHt < 0.0001) E_StubHt = 0.0001;

     Ustar = 0.02264*pow(hru_u_, 1.295f); // Eq. 6.2 rev.,  Ustar over fallow

     if (E_StubHt > 0.01) {
       Znod = (sqr(Ustar)/163.3f)+0.5*N_S[hh]*E_StubHt*A_S[hh]; // Eq. 29, Snowcover Book
       Lambda = N_S[hh]*A_S[hh]*E_StubHt;  // Raupach Eq. 1

       Ustn  = Ustar*sqrt((PBSM_constants::Beta*Lambda)/(1.0+PBSM_constants::Beta*Lambda));

       Uten_Prob = (log(10.0/Znod))/PBSM_constants::KARMAN *min <float> (0.0, Ustar-Ustn);
     }
     else
     {
       Uten_Prob = hru_u_;
     } // end if


     ProbabilityThresholdNew(SWE[hh], hru_t[hh], Uten_Prob, Prob[hh], Ut, hru_newsnow[hh], SnowAge[hh], DrySnow[hh]);

     if (Prob[hh] > 0.001) {
       Ut = Ut * 0.8;

       Pbsm(E_StubHt, Ut, DriftH[hh], SublH[hh], hru_t[hh], hru_u_, hru_rh[hh], fetch[hh], N_S[hh], A_S[hh]);

       if(variation == VARIATION_2 || variation == VARIATION_3){
         DriftH[hh] = Drift_offset[hh] + DriftH[hh]*Drift_slope[hh];
         SublH[hh] = Subl_offset[hh] + SublH[hh]*Subl_slope[hh];
       }

       Drift[hh] = DriftH[hh]*Prob[hh]/fetch[hh];
       if(!inhibit_subl[hh])
         Subl[hh] = SublH[hh]*Prob[hh];

// handle insufficient snow pack

       if(Drift[hh] + Subl[hh] > SWE[hh]) {
         Subl[hh] = SWE[hh] * Subl[hh]/(Subl[hh] + Drift[hh]);
         Drift[hh] = SWE[hh] - Subl[hh];
       } // end if

       cumDrift[hh] = cumDrift[hh] + Drift[hh];
       cumSubl[hh] = cumSubl[hh] + Subl[hh];

       SWE[hh] = SWE[hh] - Subl[hh] - Drift[hh];
     }
   } // end if
 } // end for (hh)

 // distribute drift

  if(distrib[0] > 0.0) { // simulate transport entering basin using HRU 1
    float Drft = Drift[0]*distrib[0];
    SWE[0] += Drft;
    cumDriftIn[0] += Drft;
    cumBasinSnowGain[0] += Drft*hru_basin[0];  // **** hru_basin = hru_area/basin_area ****
  }

  BasinSnowLoss[0] = 0.0;
  long LastN = 0;

  if(!inhibit_bs[0]&& nhru == 1){
    BasinSnowLoss[0] = Drift[0];
    cumBasinSnowLoss[0] += BasinSnowLoss[0];
  }

  for (long nn = LastN; chkStruct(nn); ++nn) {
    if(distrib[nn] >= 0.0 && nn+1 < nhru) // skip till last HRU or -ve distribution
      continue;

    SumDrift = 0.0;
    for (long hhh = LastN; chkStruct(hhh, nn); ++hhh) // sum drift over range
      SumDrift += Drift[hhh]*hru_basin[hhh];

    if(SumDrift > 0.0){ // drift has occurred!
      for (long hh = LastN + 1; chkStruct(hh, nn+1); ++hh) {
        SWE_Max = SWEfromDepth(Ht[hh]);

        if(hh == nn) { // handle last HRU
          if(distrib[nn] > 0){
            float In = SumDrift/hru_basin[hh]; // remaining drift
            if(SWE_Max > SWE[hh] + In){ // fill snowpack, remainder leaves basin
              SWE[hh]  += In; // can handle all
              cumDriftIn[hh] += In;
              transport = 0.0;
            }
            else if(SWE_Max > SWE[hh]){ // cannot handle all
              cumDriftIn[hh] += (SWE_Max - SWE[hh]);
              transport -= (In -(SWE_Max - SWE[hh]))*hru_basin[hh];
              SWE[hh]  += SWE_Max - SWE[hh]; //  has to come last
            }
            else // zero or -ve - happens during melt??
              transport = SumDrift;
          }
          else if(distrib[nn] < 0){ // all drift deposited
              SWE[hh]  += SumDrift/hru_basin[hh]; // can handle all
              cumDriftIn[hh] += SumDrift/hru_basin[hh];
              transport = 0.0;
          }
          else // distrib[nn] == 0 -> all excess drift leaves basin
              transport = SumDrift;

          BasinSnowLoss[0] += (transport + Drift[hh]*hru_basin[hh]);
          cumBasinSnowLoss[0] += (transport + Drift[hh]*hru_basin[hh]);
        }
        else if(SWE_Max > SWE[hh] &&  distrib[hh] > 0.0) {
// handle intermediate HRUs with available storage and distrib > 0
          total = 0.0;
          for (long jj = hh; chkStruct(jj, nn+1); jj++) // calculate denominator        !!!! nn+1
            total += fabs(distrib[jj]);
// determine contribution and scale
          transport = SumDrift*fabs(distrib[hh])/total/hru_basin[hh];
          if(SWE_Max > SWE[hh] + transport) // sufficient capacity
            SWE[hh] += transport;
          else {
            transport = SWE_Max - SWE[hh];  // insufficient capacity
            SWE[hh] = SWE_Max;
          }
          SumDrift -= transport*hru_basin[hh]; // remove drift used from total available
          cumDriftIn[hh] += transport;
        } // end if
      } // end for (hh)
    } // end if
    LastN = nn+1;
  } // end for (nn)

    for (hh = 0; chkStruct(); ++hh) { // snow cover inhibits evaporation

      if(SWE[hh] > 0.0){
        const_cast<long*> (inhibit_evap)[hh] = 1;
        snowdepth[hh] = Common::DepthofSnow(SWE[hh]);
      }
      else{
        const_cast<long*> (inhibit_evap)[hh] = 0;
        snowdepth[hh] = 0.0;
      }
    } // end for (hh)
}

void Classpbsm::finish(bool good) {

  if(!good) return;

  float AllcumSubl = 0.0;
  float AllcumCover = cumBasinSnowGain[0] - cumBasinSnowLoss[0];

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (pbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm)' cumCover   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh]+cumDriftIn[hh]-cumDrift[hh]-cumSubl[hh], hru_area[hh], basin_area[0], "*** SWE just before melt");
    LogMessageA(hh, string("'" + Name + " (pbsm)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm)' SWE_change (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh] - SWE_Init[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");

    AllcumSubl += cumSubl[hh]*hru_area[hh];
    AllcumCover += (cumSno[hh]+cumDriftIn[hh]-cumDrift[hh]-cumSubl[hh])*hru_area[hh];
  }

  LogMessage(string("'" + Name + " (pbsm)' AllcumSubl  (mm*basin): ").c_str(), AllcumSubl, "*** cumulative sum of all HRUs cumSubl");
  LogMessage(string("'" + Name + " (pbsm)' AllcumCover (mm*basin): ").c_str(), AllcumCover, "*** SWE just before melt cumulative sum of all HRUs cumCover");
  LogDebug(" ");
  LogMessage("'pbsm' cumBasinSnowLoss (mm): ", cumBasinSnowLoss[0]);
  LogMessage("'pbsm' cumBasinSnowGain (mm): ", cumBasinSnowGain[0]);
  LogDebug(" ");

}