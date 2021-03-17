//created by Manishankar Mondal

#include "Classpbsm_M.h"
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



Classpbsm_M* Classpbsm_M::klone(string name) const{
  return new Classpbsm_M(name);
}

void Classpbsm_M::decl(void) {

  Description = "'Calculates snow transport and sublimation (Pomeroy and Li, 1999). This module has enhanced transport distribution features.'";

  declstatvar("SWE", TDim::NHRU, "snow water equivalent", "(mm)", &SWE);

  declvar("Subl", TDim::NHRU, "interval sublimation", "(mm/int)", &Subl);

  declvar("Drift", TDim::NHRU, "interval transport", "(mm/int)", &Drift);

  declvar("BasinSnowLoss", TDim::BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

  declstatvar("cumSubl", TDim::NHRU, "cumulative sublimation", "(mm)", &cumSubl);

  declstatvar("cumDrift", TDim::NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

  declstatvar("cumBasinSnowLoss", TDim::BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

  declstatvar("cumBasinSnowGain", TDim::BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

  decllocal("cumDriftIn", TDim::NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

  decllocal("DrySnow", TDim::NHRU, "DrySnow", "()", &DrySnow);

  decllocal("SnowAge", TDim::NHRU, "SnowAge", "()", &SnowAge);

  decllocal("this_distrib", TDim::NHRU, "current step distribution", "()", &this_distrib);

  declstatvar("cumSno", TDim::NHRU, "cumulative snow", "(mm)", &cumSno);

  declvar("Prob", TDim::NHRU, "Probability", "()", &Prob);

  declstatvar("snowdepth", TDim::NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);

  declvar("Q_leeslope", TDim::NHRU, "leeslope transport from HRU", "(mm)", &Q_leeslope);

  declvar("Q_valley", TDim::NHRU, "valley transport from HRU", "(mm)", &Q_valley);

  declvar("Results", TDim::NDEFN, "calulated distributions", "()", &Results, &Results_lay, nhru);

/* parameters */

  declparam("fetch", TDim::NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

  declparam("Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

  declparam("distrib", TDim::NDEFN, "[0.0, 1.0, 1.0, 1.0]", "0.0", "99.0", "distribution array", "()", &distrib, &distrib_hru, nhru);

  decldiagparam("N_S", TDim::NHRU, "[320]", "0.1", "500", "vegetation number density", "(1/m^2)", &N_S);

  decldiagparam("A_S", TDim::NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", &A_S);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("hru_GSL", TDim::NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string(DEGREE) + ")", &hru_GSL);

  decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

  declparam("inhibit_bs", TDim::NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", &inhibit_bs);

  decldiagparam("inhibit_subl", TDim::NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

  declparam("eq_prof", TDim::NHRU, "[0]", "0", "1", "0: use vegetation height, 1: use equilibrium profile depth as SWE_Max",  "()", &eq_prof);

  declparam("Zwind", TDim::NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);

  decldiagparam("Beta_M", TDim::NHRU, "[170.0]", "32.0", "170.0", "ratio of element to surface drag for vegetation; 170 for stalks, 320 for shrubs", "()", &Beta_M);

  declparam("hru_Ht", TDim::NHRU, "[0.0]", "0.0", "1000.0", "HRU feature height(m)", "(m)", &hru_Ht);

  declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);
  declgetvar("*", "hru_rh", "(%)", &hru_rh);
  declgetvar("*", "hru_u", "(m/s)", &hru_u);
  declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
  declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void Classpbsm_M::init(void) {

  nhru = getdim(TDim::NHRU);

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

    if((hh > 0) && (Ht[hh] < Ht[hh-1]) && distrib[hh-1] > 0){
         CRHMException TExcept("PBSM - vegetation heights not in ascending order", TExcept::WARNING);
         LogError(TExcept);
//         throw TExcept;
    }
  }

  hru_basin = new double[nhru];

  for (hh = 0; hh < nhru; ++hh)
    hru_basin[hh] = hru_area[hh]/basin_area[0];
}

void Classpbsm_M::run(void) {

  double Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
  double DriftH, SublH, CurrentDrift, SWE_Max, transport;
  //double total; varible is unreferenced commenting out for now - jhs507
  double VB_distrib = 0.0;

  for (hh = 0; chkStruct(); ++hh) {

    if(net_snow[hh] > 0.0) {
      SWE[hh] = SWE[hh] + net_snow[hh];
      cumSno[hh] = cumSno[hh] + net_snow[hh];
    }

   Drift[hh] = 0.0;
   Subl[hh] = 0.0;
   Prob[hh] = 0.0;
   Q_leeslope[hh] = 0.0;
   Q_valley[hh] = 0.0;

   if(SWE[hh] > 0.0 && !inhibit_bs[hh]) {

     E_StubHt = Ht[hh] - Common::DepthofSnow(SWE[hh]); // depths(m) SWE(mm)
     if(E_StubHt < 0.0001)
       E_StubHt = 0.0001;

     double d = 2.0/3.0*E_StubHt;

     double Z = 0.123*E_StubHt;

     double Wind = hru_u[hh]*log((10.0 - d)/Z)/log((Zwind[hh] - d)/Z);

     Ustar = 0.02264*pow(Wind, 1.295f); // Eq. 6.2 rev.,  Ustar over fallow

     if (E_StubHt > 0.01) {
       Znod = (sqr(Ustar)/163.3f)+0.5*N_S[hh]*E_StubHt*A_S[hh]; // Eq. 29, Snowcover Book
       Lambda = N_S[hh]*A_S[hh]*E_StubHt;  // Raupach Eq. 1

       Ustn  = Ustar*sqrt((Beta_M[hh]*Lambda)/(1.0+Beta_M[hh]*Lambda));

       Uten_Prob = (log(10.0/Znod))/PBSM_constants::KARMAN *sqrt(Ustar-Ustn);
     }
     else{
       Uten_Prob = Wind;
     } // end if

     ProbabilityThresholdNew(SWE[hh], hru_t[hh], Uten_Prob, Prob[hh], Ut, hru_newsnow[hh], SnowAge[hh], DrySnow[hh]);

     if (Prob[hh] > 0.001) {
       Ut = Ut * 0.8;

       Pbsm(E_StubHt, Ut, DriftH, SublH, hru_t[hh], Wind, hru_rh[hh], fetch[hh], N_S[hh], A_S[hh],
              hru_GSL[hh], hru_Ht[hh], Beta_M[hh], Q_leeslope[hh], Q_valley[hh]);

       Drift[hh] = DriftH*Prob[hh]/fetch[hh];
       if(!inhibit_subl[hh])
         Subl[hh] = SublH*Prob[hh];

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

 for (long hh = 0; chkStruct(hh); ++hh) {
    if(distrib_hru[hh][0] > 0.0) { // simulate transport entering basin using HRU 1
      double Drft = Drift[hh]*distrib_hru[hh][0];
      SWE[hh] += Drft;
      cumDriftIn[hh] += Drft;
      cumBasinSnowGain[0] += Drft*hru_basin[hh];  // **** hru_basin = hru_area/basin_area ****
    }
  }

  BasinSnowLoss[0] = 0.0;
  long LastN = 0;

  for (long nn = LastN; chkStruct(nn); ++nn) {
    if(distrib[nn] >= 0.0 && nn+1 < nhru) // skip till last HRU or -ve distribution
      continue;

    for (long cc = LastN; chkStruct(cc, hh-1); ++cc){ // handle drift over range
      CurrentDrift = Drift[cc]*hru_basin[cc];

      if(CurrentDrift > 0.0){ // drift has occurred!
        for (long hh = LastN+1; chkStruct(hh, nn+1); ++hh) {
          if(!eq_prof[hh]){ //use veg height to calculate SWE_Max
            SWE_Max = SWEfromDepth(Ht[hh]);
          }
          else{
            double tanEqSlope = (0.1818*100*tan(hru_GSL[cc]*DEGtoRAD) + 0.4309*100*tan(hru_GSL[hh]*DEGtoRAD) - 7.2887)/100;
            double EqProfDepth = hru_Ht[hh]/2*(1 - (tan(hru_GSL[hh]*DEGtoRAD) - tanEqSlope)/(tan(hru_GSL[hh]*DEGtoRAD)*(1 + tan(hru_GSL[hh]*DEGtoRAD)*tanEqSlope)));
            SWE_Max = SWEfromDepth(EqProfDepth);
          }

          if(hh == nn) { // handle last HRU
            if(fabs(distrib_hru[cc][hh])+ distrib_hru[nhru-1][hh] > 0.0)
              BasinSnowLoss[0] = CurrentDrift*distrib_hru[nhru-1][hh]/(fabs(distrib_hru[cc][hh])+ distrib_hru[nhru-1][hh]); // drift directly to basin loss
            else
              BasinSnowLoss[0] = 0;

            CurrentDrift -= BasinSnowLoss[0];

            SWE[hh] += CurrentDrift/hru_basin[hh];
            cumDriftIn[hh] += CurrentDrift/hru_basin[hh];
            if(SWE[hh] > SWE_Max){ // over filled!
              if(SWE[hh] - SWE_Max >= Drift[hh]){ // drift less than excess
                SWE[hh] -= Drift[hh];
                BasinSnowLoss[0] += Drift[hh];
              }
              else{ // drift more than excess
                BasinSnowLoss[0] += SWE[hh] - SWE_Max;
                SWE[hh] = SWE_Max;
              }
              BasinSnowLoss[0] *= hru_basin[hh];
              cumBasinSnowLoss[0] += BasinSnowLoss[0];
            }
          }
		  else if(SWE_Max > SWE[hh] &&  distrib_hru[cc][hh] > 0.0) {
  // handle intermediate HRUs with available storage and distrib > 0

			double sum = distrib_hru[nhru-1][cc]; // always the very last HRU
			for (long jj = hh; chkStruct(jj, nn+1); jj++) { // calculate denominator
              Results_lay[cc][jj] = 0.0;
              if(distrib_hru[cc][jj] != 88 && distrib_hru[cc][jj] != 99) {
                sum += fabs(distrib_hru[cc][jj]);
              }
            }
            if(distrib_hru[cc][hh] == 88 && Q_leeslope[hh] >= 0.0) { // leeward slope
              if(Q_leeslope[hh] > 0.0)
                this_distrib[hh] = (1 - sum)*Q_leeslope[hh]/(Q_leeslope[hh] + Q_valley[hh]);
              else
                this_distrib[hh] = 0.0;

                Results_lay[cc][hh] = this_distrib[hh];
//              sum += this_distrib[hh];
			  for (long kk = hh+1; chkStruct(kk, nn+1); kk++) {
				if(distrib_hru[cc][kk] == 99 && Q_valley[hh] >= 0.0){
				  if(Q_valley[hh] > 0.0)
					VB_distrib = (1 - sum)*Q_valley[hh]/(Q_leeslope[hh] + Q_valley[hh]);
				  else
					VB_distrib = 0.0;
				} // if
			  } // for kk
			}
			else if(distrib_hru[cc][hh] == 99){ //&& Q_valley[hh] >= 0.0) { // valley bottom
//              if(Q_valley[hh] > 0.0)
//				this_distrib[hh] = (1 - sum)*Q_valley[hh]/(Q_leeslope[hh] + Q_valley[hh]);
//              else
//                this_distrib[hh] = 0.0;
			  this_distrib[hh] = VB_distrib;

			  Results_lay[cc][hh] = this_distrib[hh];
//              sum += this_distrib[hh];
           }
            else{
			  this_distrib[hh] = distrib_hru[cc][hh];
			}

  // determine contribution and scale
			transport = CurrentDrift*fabs(this_distrib[hh])/hru_basin[hh]/1;
            if(SWE_Max > SWE[hh] + transport) // sufficient capacity
              SWE[hh] += transport;
            else {
              transport = SWE_Max - SWE[hh];  // insufficient capacity
              SWE[hh] = SWE_Max;
            }
            CurrentDrift -= transport*hru_basin[hh]; // remove drift used from total available
            cumDriftIn[hh] += transport;
          } // end if
        } // end for (hh)
      } // end if
    } // end for
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

void Classpbsm_M::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumCover   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh]+cumDriftIn[hh]-cumDrift[hh]-cumSubl[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsm_M)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh],        hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }

  LogMessage("'pbsm_M' cumulative basin snow loss (mm): ", cumBasinSnowLoss[0]); //
  LogMessage("'pbsm_M' cumulative basin snow gain (mm): ", cumBasinSnowGain[0]); //
  LogDebug(" ");

  delete[] hru_basin;
  hru_basin = NULL;
}

void Classpbsm_M::Sum(double TQsalt, double TQsusp, double SBsum, double SBsalt, double & DriftH, double & SublH)
{

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

void Classpbsm_M::Pbsm (double E_StubHt, double Uthr, double & DriftH, double & SublH,
           double t, double u, double rh, double Fetch,
           long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley)
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

  double   A,      Alpha,  B,      Bd,     Bound,  C,
  Diff,   DmDt,   Es,     H,
  Htran,  Hsalt,  Inc,    Lamb,   Lambda, Lb,
  Mpm,    Mpr,    Nh,     Nsalt,
  Nz,     Nuss,   Omega,  TQsalt,
  TQsum,  Qz,     RauTerm,Temp,
  Reyn,   SBsalt, Sbz,    SBsum,
  SigmaZ, Sigma2, SvDens, Usthr,  Ustar,
  UstarZ, Uz,     Vs,     Vsalt,  Sigma,
  Vsusp,  Z,      Zr,     Zstb,
  tX,     tH;
  //double Qdist; varible is unreferenced commenting out for now - jhs507


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
      Ustar = 0.02264f*pow(u, 1.295f);                         //{Eq. 6.2 rev}
      if(E_StubHt > 0.0001)                         //{Eq. 6.2 rev}
        RauTerm  = 1.0/((1.0-Sigma*Lambda)*(1.0+Beta_M*Lambda)); //{Raupach}
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

      Qdist_leeslope = 0;
      Qdist_valley = 0;

      Twenty: H = Z + Inc;
      while (H <= Bound) {
         Nh = 0.8 * exp(-1.55f*(pow(0.05628f*Ustar, -0.544f) - pow(H, -0.544f)));
         Nz = Nh;
         UstarZ = Ustar * pow(1.2f/(1.2f + Nz), 0.5f);                  // Eq. 5.17a
         Uz = (UstarZ/PBSM_constants::KARMAN) *log(H/((0.00613f *sqr(Ustar)) + Zstb));// Eq. 4.17r
	 if(Uz > 0) {
	   if(height <= 0)
	     tX = 0;
	   else
             tX = height/(Uz*tan(GSL*DEGtoRAD));

	   Mpr = 4.6e-5 * pow(H, -0.258f);                            // Eq. 6.15
           if(H >= 5.0) {Mpr = 30E-6f;}

           Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
           Alpha = 4.08 + 12.6 * H;                                  // Eq. 6.14
           if(H >= 1.5) {Alpha = 25.0;}

           SigmaZ = Sigma2 * (1.019 + 0.027 * log(H));  // Eq. 6.20, Revised in May. 1997
           if(SigmaZ > -0.01) {SigmaZ = -0.01;}
	   Omega = 1.1e7f * pow(Mpr, 1.8f);               // Eq. 5.18
           tH = (height + H)/Omega;
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
           Qz = Nz * Uz * Inc;

           if(tH < tX)
             Qdist_leeslope += Qz;
           else
             Qdist_valley += Qz;
                                       // Eq. 5.4
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