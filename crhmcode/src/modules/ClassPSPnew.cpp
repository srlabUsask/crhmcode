/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

// TODO canopy height always subtracted by 10?
//TODO pull from snowbal declreadobs("TsnowG", TDim::NHRU, "snow temperature", "(" + string(DEGREE_CELSIUS) + ")", &TsnowG, HRU_OBS_misc);
///TODO pull from interception module declreadobs("Lnot", TDim::NHRU, "tree weight",      "(kg/m^2)", &Lnot, HRU_OBS_misc);
// declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &QsIn, HRU_OBS_Q);
// not currently used declreadobs("Qso", TDim::NHRU, "Qso",      "(W/m^2)", &QsOut, HRU_OBS_Q);


#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassPSPnew.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassPSPnew *ClassPSPnew::klone(string name) const{
  return new ClassPSPnew(name);
}

void ClassPSPnew::decl(void) {

  // Observations

  variation_set = VARIATION_0 + VARIATION_1;

  declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

  variation_set = VARIATION_0 + VARIATION_2;

  declreadobs("Qli", TDim::NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);

  variation_set = VARIATION_1 + VARIATION_3 + VARIATION_4;

  declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);

  variation_set = VARIATION_2 + VARIATION_3;

  declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);

  variation_set = VARIATION_4;

  declgetvar("*", "QsiA_Var", "(W/m^2)", &QsiA_Var);

  variation_set = VARIATION_ORG;

  declvar("Qsubl", TDim::NHRU, "Canopy sublimation", "(mm/int)", &Qsubl);

  declvar("SnowLoad", TDim::NHRU, "Canopy snow load", "(kg/m^2)", &Load);

  declvar("Thru", TDim::NHRU, "Canopy fall through", "(kg/m^2)", &Thru);

  declvar("TCanSnow", TDim::NHRU, "snow Canopy temperature", "(" + string(DEGREE_CELSIUS) + ")", &TCanSnow);

  declvar("Tbiomass", TDim::NHRU, "biomass temperature", "(" + string(DEGREE_CELSIUS) + ")", &Tbiomass);

  declparam("InitN", TDim::NHRU, "0", "0", "200", "Number of periods before calculating sublimation", "()", &InitN);

  declparam("Sbar", TDim::NHRU, "6.6", "0.0", "20.0", "Uncorrected snow capacity", "(kg/m^2)", &Sbar);

  declparam("LAI", TDim::NHRU, "2.2", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

  declparam("Zcan", TDim::NHRU, "16", "0.0", "30.0", "Mid-canopy wind modelling height", "(m)", &Zcan);

  declparam("Zref", TDim::NHRU, "27", "0.0", "40.0", "Reference height", "(m)", &Zref);

  declparam("Ht", TDim::NHRU, "[20.0]", "0.001", "100.0", "Canopy height", "(m)", &Ht);

  declparam("Biomass", TDim::NHRU, "30.0", "0.0", "100.0", "Biomass", "(kg/m^2)", &Biomass);

  declparam("k", TDim::NHRU, "0.0113", "0.0", "1.0", "Snow shape coefficient", "()", &k);

  declparam("HeightH", TDim::NHRU, "20", "0.0", "100.0", "Canopy height", "(m)", &HeightH);

  declparam("WidthJ", TDim::NHRU, "75", "0.0", "100.0", "Canopy ", "(m)", &WidthJ);

  declgetvar("obs", "hru_u", "(m/s)", &hru_u);
  declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &TAref);
  declgetvar("obs", "hru_rh", "(%)", &RHref);
  declgetvar("obs", "hru_p", "(mm/int)", &hru_p);
  declgetvar("*", "SolAng", "(r)", &SolarAng);
  declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
  declgetvar("*", "QdroDext", "(W/m^2)", &QdroDext);
}

void ClassPSPnew::init(void) {

  nhru = getdim(TDim::NHRU);
  std::cout << "Number of HRUs: " << nhru << std::endl;

  T0CanSnow = new double[nhru];
  T0biomass = new double[nhru];

  for(long hh = 0; hh < nhru; hh++) {
    Qsubl[hh] = 0.0;
    Load[hh] = 0.0;
    Thru[hh] = 0.0;
    std::cout << "Initialized HRU " << hh << std::endl;
  }
}

void ClassPSPnew::run(void) {

std::cout << "Entered RUN PSPnew.\n";
std::cout << "TAref = " << TAref[hh] << std::endl;
std::cout << "hru_u = " << hru_u[hh] << std::endl;
std::cout << "RHref = " << RHref[hh] << std::endl;
std::cout << "SolarAng = " << SolarAng[hh] << std::endl;
std::cout << "hru_ea = " << hru_ea[hh] << std::endl;
std::cout << "QdroDext = " << QdroDext[hh] << std::endl;


  const double GapFrac = 0.16;      /* Canopy gap fraction */
  const double UpperGF = 0.58;      /* Mid-canopy level gap fraction */
  const double Radius  = 0.0005;    /* Ice sphere radius, metres */
  const double KinVisc = 1.88E-5;   /* Kinematic viscosity of air (Sask. avg. value) */
  const double R = 8313.0;          /* Universal gas constant, J/(mole*K) */
  const double M = 18.01;           /* Molecular weight of water */
  const double RhoI = 900.0;        /* Density of ice, kg/m^3 */
  const double k1 = 0.0114;         /* Snow shape coefficient, Jackpine site */
  const double Fract = 0.4;         /* Fractal dimension */
  const double SnowAlb = 0.8;       /* Albedo for snow */
  const double CanAlb = 0.2;        /* Albedo for canopy */
  const double KARMAN = 0.4;        /* Von Karman"s constant */
  const double g = 9.8;             /* Gravitational acceleration, m/s^2 */
  const double SBC = 5.67E-8;       /* Stephan-Boltzmann constant W/m2*/
  const double SpHtAir = 1013.0;    /* Specific heat of air, J/(kg*K) */
  const double SpHtIce = 2090.0;    /* Specific heat of ice, J/(kg*K) */
  const double SpHtCan = 2700.0;    /* Specific heat of canopy (CLASS value), J/(kg*K) */
  const double Hs = 2838000.0;      // Latent heat of sublimation, J/kg

  long   TItNum, RHItNum, TItNum2;       // Used in iteration loops
  bool   Tup, RHup, Tup2;
  double I1, Cp, wtsubl, Unld;

  double StepT, StepRH, StepT2;
  double DblRHcan, DblTbarCan, DblTCanSnow;

  double RhoS, Lstar; // Hedstrom-Pomeroy, for L/L*

  double SVDensC, SVDensS, LambdaT, CanVent, A, Nr, NuSh, D,
          Vs, Vhr, Ce, Vi; // Pomeroy-Schmidt components

  /* Radiation model components */
  double QTrans50; // short wave radiation transmitted through to the canopy mid point height (W m-2)
  double Mu; // variable from equation 4 from Parv. & Pom 2000
  double QTrUp50; // solar radiation reflected off the surface snowpack and back to the canopy midpoint (W m-2)
  double QTrans100; // solar radiation transmitted through the canopy (W m-2)
  double CanSnowFrac; 

  double QlwUpC100; // longwave radiation emitted from the subcanopy snowpack and lower portion of the canopy (W m-2) 
  double tau_atm; // atmospheric transmissivity (-)
  double hru_ea_mb; // conversion of kpa to mb for clarity
  double F; // variable to scale incoming longwave radiation based on cloudiness from Sicart et al., (2006)
  double QlwInAtm; // longwave emission from cloudy skies calculated from Eq. 9 from Sicart et al., (2006)
  double QsDnStar; // downwelling shortwave radiation to the top of the ice sphere
  double QsUpStar; // upwelling shortwave radiation reflected from the ground surface hitting the bottom of the ice sphere
  double QlwUpStar; // upwelling longwave radiation from the surface snowpack and lower portion of the canopy hitting the bottom of the ice sphere
  double QlwDnStar; // downwelling longwave radiation from the atmosphere passing through the upper canopy gap (UpperGF), plus longwave emission from snow intercepted in the upper half of the canopy and any remaining exposed veg. elements
  double QlwOutStar; // longwave emission from the top and bottom of the ice sphere plan area
  double QnetStar; // net radiation to the ice sphere
  double RhoAir, SVDensA, VPref, Ustar, Uh, Ra, Ri,
         Stabil, Qe, Qh, dUdt; // CLASS components

  
  double RHrefhh; // holds RH as fraction instead of default percentage

  static long N;
  static double Z0m, Z0h, Disp, CdragH, CdragE;

  const double Cc = 0.82;
  const double Velw = 0.75;
  const double TsnowG = -4; // set to constant for now
  const double Lnot = 10; // set to constant for now

  for(long hh = 0; hh < nhru; hh++) {
    std::cout << "timestep = " << getstep() << std::endl; 


     switch (variation)
    {
    case VARIATION_ORG:
      Qsi_ = Qsi[hh];
      Qli_ = Qli[hh];
      break;
    case VARIATION_1:
      Qsi_ = Qsi[hh];
      Qli_ = QliVt_Var[hh];
      break;
    case VARIATION_2:
      Qsi_ = QsiS_Var[hh];
      Qli_ = Qli[hh];
      break;
    case VARIATION_3:
      Qsi_ = QsiS_Var[hh];
      Qli_ = QliVt_Var[hh];
      break;
    case VARIATION_4:
      Qsi_ = QsiA_Var[hh];
      Qli_ = QliVt_Var[hh];
      break;
    } // switch

   if(getstep() == 1) {
     Tbiomass[hh] = TAref[hh];
     TCanSnow[hh] = TAref[hh];
     T0CanSnow[hh] = TCanSnow[hh];
     T0biomass[hh] = Tbiomass[hh];
     N = 0;
     Z0m = Ht[hh]/10.0;            // One-time calc. of sfc. characteristics
     Z0h = Z0m/2.0;
     Disp = Ht[hh]*0.7;
     CdragH = (KARMAN/(log((Zref[hh]-Disp)/Z0h)))*(KARMAN/(log((Zref[hh]-Disp)/Z0m)));
     CdragE = sqr(KARMAN/(log(Zref[hh]/Ht[hh])));
   }

   Thru[hh] = 0.0;
   Qsubl[hh] = 0.0;

   if (N <= InitN[hh]) {// Starts depletion after Tcanopy is initialized
     Load[hh] =  Lnot;
     if (N < InitN[hh]) break;
   }

   RhoS = 67.92 + 51.25*exp(TAref[hh]/2.59);
   Lstar = Sbar[hh]*(0.27 + 46.0/RhoS)*LAI[hh];

   if(Load[hh] > Lstar) { // after increase in temperature
     Thru[hh] = Load[hh] - Lstar;
     Load[hh] = Lstar;
   }

   if(hru_p[hh] > 0.0) {
     Cp = Cc/(1.0 - (Cc*hru_u[hh]*HeightH[hh])/(Velw*WidthJ[hh]));
     if(Cp <= 0.0 || Cp > 1.0) Cp = 1.0;

     I1 = (Lstar-Load[hh])*(1 - exp(-Cp*hru_p[hh]/Lstar));

     Load[hh] = Load[hh] + I1; // add new snowfall
     Thru[hh] = Thru[hh] + (hru_p[hh] - I1); // remainder falls thru
   }

   if(Load[hh] <= 0.0) {
     Load[hh] = 0.0;
     break;
   }

   if(RHref[hh] > 1.5)
     RHrefhh = RHref[hh]/100.0;
   else
     RHrefhh = RHref[hh];

   DblTbarCan = TAref[hh]; //TAref[hh]; // fix for precision problem

   DblRHcan = RHrefhh; // RHref[hh]; // fix for precision problem
   DblTCanSnow  = TCanSnow[hh];

   CanSnowFrac = pow(Load[hh]/Lstar,0.8);

   VPref = RHrefhh* Common::estar(TAref[hh]);
   SVDensA = Common::SVDens(TAref[hh]);
   RhoAir =  10000.0*94.97/(2870.0*(TAref[hh]+273.15))*(1.0-0.379*VPref/94.97);

   Ustar = hru_u[hh]*KARMAN/(log((Zref[hh]-Disp)/Z0m));
   Uh = Ustar*(log((Ht[hh]-Disp)/Z0m))/KARMAN;
   Ra = 1.0/(CdragH*(hru_u[hh]+0.1));

   A = 2.4338+3.45753*exp(-Uh);                 /* Modified Cionco wind model */
   CanVent = Uh*exp(A*((Zcan[hh]-10)/(Ht[hh]-10)-1.0));  /* calculates canopy windspd  */

   Nr = 2*Radius*CanVent/KinVisc;
   NuSh = 1.79+0.606*sqrt(Nr);

   if (SolarAng[hh] > 0.001)  {
     Mu = LAI[hh]/(Ht[hh]-10)*(0.781*SolarAng[hh]*cos(SolarAng[hh])+0.0591); // equation 4 from Parv. & Pom 2000
     QTrans50 = Qsi_*exp(-Mu*(Ht[hh]-10)/2/sin(SolarAng[hh])); // incoming solar radiation multiplied by the transmissivity calculated from equation 3 in Parv. & Pom 2000, IOW short wave radiation transmitted through to the canopy mid point height
     QTrans100 = Qsi_*exp(-Mu*(Ht[hh]-10)/sin(SolarAng[hh])); // as above but calculates solar transmitted through the canopy
     QTrUp50 = (1.0-SnowAlb)*QTrans100*exp(LAI[hh]/(Ht[hh]-10)*0.0591*(Ht[hh]-10)/2); // solar radiation reflected off the surface snowpack and back to the canopy midpoint
   }
   else {
     QTrans50 = 0.0;
     QTrUp50 = 0.0;
   }

   TItNum = 0;
   StepT = 0.1;
   do { /* Canopy T iteration loop */
     TItNum = TItNum+1;
     if (TItNum > 1)  DblTbarCan += StepT;
     SVDensC = Common::SVDens(DblTbarCan);
     Ri = g/((TAref[hh]+DblTbarCan)/2.0+273.15)*(TAref[hh]-DblTbarCan)/(Zref[hh]-Ht[hh])
               /(sqr((hru_u[hh]-Uh)/(Zref[hh]-Ht[hh])));
     if (Ri < 0.0)  Stabil = pow((1.0 - 16.0*Ri), 0.75);
               else Stabil = sqr(1.0 - 5.0*Ri);

     RHItNum = 0;
     StepRH = 0.01;
     do { /* Canopy RH iteration loop */
       RHItNum = RHItNum + 1;
       if (RHItNum > 1)  DblRHcan += StepRH;
       LambdaT = 0.00063*(DblTbarCan+273.15)+0.0673;
       D = 2.06E-5*pow((DblTbarCan+273.15)/273.15 , 1.75);

       TItNum2 = 0;
       StepT2 = 0.01;
       do { /* Canopy Snow and Biomass[hh] T iteration loop */
         TItNum2 = TItNum2 + 1;
         if (TItNum2 > 1)  {
           DblTCanSnow += StepT2;
           Tbiomass[hh] = DblTbarCan + ((DblTbarCan - DblTCanSnow)*Load[hh]*SpHtIce)
                                       /(Biomass[hh]*SpHtCan);
         }

         // Subroutine to calculate radiation terms relative to the ice sphere,
         // this algorithm has been left unchanged but some symbols and comments have
         // been added for clarity. This differs from CLASS where the ebal is solved for the entire canopy
         // Values for incoming and outgoing solar rad previously were provided from obs
         // file and then longwave was calculated as a residual. This has been changed to
         // used modelled vars for all.

         /* Solve for outgoing longwave for lower portion of canopy */
         QlwUpC100 = SBC*(GapFrac*pow(TsnowG+273.15,4.0) +
                     (1.0-GapFrac)*((1.0-CanSnowFrac)*pow(Tbiomass[hh]+273.15,4.0)
                                 + CanSnowFrac*pow(DblTCanSnow+273.15,4.0)));
         //         double QlwIn = Qn[hh]-QsIn[hh]+QsOut[hh]+QlwOut;

         // incoming longwave radiation from cloudy sky following Sicart et al., (2006)
         tau_atm = Qsi_/QdroDext[hh]; 
         hru_ea_mb = hru_ea[hh]*10.0; // kPa to mb 
         F = (1 + 0.44 * DblRHcan - 0.18 * tau_atm); // scaling factor >= 1 to increase longwave emission due to cloudiness, could update to use non iterating RH if breaking here
         QlwInAtm = 1.24 * pow(hru_ea_mb / TAref[hh]+273.15, 1.0 / 7.0) * F * SBC * pow(TAref[hh]+273.15, 4); // Eq. 9 from Sicart et al., (2006)


          /* Solve for particle net radiation*/
         QsDnStar = M_PI*Radius*Radius*QTrans50*(1.0-SnowAlb);
         QsUpStar = M_PI*Radius*Radius*QTrUp50*(1.0-CanAlb);
         QlwUpStar = M_PI*Radius*Radius*QlwUpC100;
         QlwDnStar = M_PI*Radius*Radius*(QlwInAtm*UpperGF + SBC*(1.0-UpperGF)*
                              ((1.0-CanSnowFrac)*pow(Tbiomass[hh]+273.15,4.0)
                               + (CanSnowFrac*pow(DblTCanSnow+273.15,4.0))));
         QlwOutStar = 2*M_PI*Radius*Radius*SBC*pow(DblTCanSnow+273.15,4.0);
         QnetStar = QsDnStar+QsUpStar+QlwDnStar+QlwUpStar-QlwOutStar;

         SVDensS = Common::SVDens(DblTCanSnow);
         Vs = (2.0*M_PI*D*Radius*(SVDensC*DblRHcan-SVDensS)*NuSh)*Hs;
         Vhr = (2.0*M_PI*LambdaT*Radius*(DblTCanSnow-DblTbarCan)*NuSh - QnetStar);

         if ((Vs-Vhr) < 0.0)  {
           if (TItNum2 == 1)  {
             Tup2 = false;
             StepT2 = -StepT2;
           }
           else {
             if (Tup2)  StepT2 = -StepT2/10.0;
             Tup2 = false;
           }
         }
         else {
           if (TItNum2 == 1)  Tup2 = true;
           else {
             if (!Tup2)  StepT2 = -StepT2/10.0;
             Tup2 = true;
           }
         }
       } while (fabs(Vs-Vhr) >= 0.000001);

       Vs = Vs/(4.0/3.0*M_PI*pow(Radius, 3.0)*RhoI)/Hs;
       Ce = k1*pow(Load[hh]/Lstar, -Fract);
       Vi = Vs*Ce;
       Qsubl[hh] = Load[hh]*Vi*Hs;
       Qe = Hs*CdragE*(hru_u[hh]-Uh)*(SVDensA*RHrefhh-SVDensC*DblRHcan)*Stabil;

       if (Qe-Qsubl[hh] < 0.0)  {
         if (RHItNum == 1)  {
           RHup = false;
           StepRH = -StepRH;
         }
         else {
           if (RHup)  StepRH = -StepRH/10.0;
           RHup = false;
         }
       }
       else {
         if (RHItNum == 1)  RHup = true;
         else {
           if (!RHup)  StepRH = -StepRH/10.0;
           RHup = true;
         }
       }
     } while (fabs(Qsubl[hh]-Qe) >= 0.01);

     Qh = RhoAir*SpHtAir/Ra*(TAref[hh]-DblTbarCan)*Stabil;
     dUdt = ((Tbiomass[hh]-T0biomass[hh])*Biomass[hh]*SpHtCan
             +(DblTCanSnow-T0CanSnow[hh])*Load[hh]*SpHtIce)/(Global::Interval*24*3600.0);

//     if (Qn[hh]+Qh+Qe-dUdt < 0.0)  {
     if (Qh+Qe-dUdt < 0.0)  {
       if (TItNum ==1)  {
         Tup = false;
         StepT = -StepT;
       }
       else {
         if (Tup)  StepT = -StepT/10.0;
         Tup = false;
       }
     }
     else {
       if (TItNum == 1)  Tup = true;
       else {
         if (!Tup)  StepT = -StepT/10.0;
         Tup = true;
       }
     }
//   } while (fabs(Qn[hh]+Qe+Qh-dUdt) >= 0.01);
   } while (fabs(Qe+Qh-dUdt) >= 0.01);

  std::cout << "RHItNum = " << RHItNum << std::endl;
  std::cout << "TItNum = " << TItNum << std::endl;
  std::cout << "Qsi = " << Qsi_ << std::endl;
  std::cout << "CanSnowFrac = " << CanSnowFrac << std::endl;
  std::cout << "Tbiomass = " << Tbiomass << std::endl;
  std::cout << "DblTCanSnow = " << DblTCanSnow << std::endl;

  std::cout << "hru_ea_mb = " << hru_ea_mb << std::endl;
  std::cout << "tau_atm = " << tau_atm << std::endl;
  std::cout << "DblRHcan = " << DblRHcan << std::endl; 
  std::cout << "QlwUpC100 = " << QlwUpC100 << std::endl;  
  std::cout << "QlwInAtm = " << QlwInAtm << std::endl;
  std::cout << "QsDnStar = " << QnetStar << std::endl; 
  std::cout << "QsUpStar = " << QnetStar << std::endl; 
  std::cout << "QlwUpStar = " << QnetStar << std::endl; 
  std::cout << "QlwDnStar = " << QnetStar << std::endl;
  std::cout << "QnetStar = " << QnetStar << std::endl;

   TCanSnow[hh]  = DblTCanSnow;
   T0CanSnow[hh] = DblTCanSnow;
   T0biomass[hh] = Tbiomass[hh];

   wtsubl = -Qsubl[hh]*Global::Interval*24*3600.0/Hs; // make positive

   if(wtsubl > Load[hh]) {
     Qsubl[hh] = -Load[hh]/(Global::Interval*24*3600.0/Hs); // make W/m2
     wtsubl = Load[hh];
     Load[hh] = 0.0;
   }
   else
     Load[hh] = Load[hh] - wtsubl;

   if(hru_p[hh] > 0.0)
     if(I1 > wtsubl) {
       Unld = (I1 - wtsubl)*0.322;
       Load[hh] = Load[hh] - Unld;
       Thru[hh] = Thru[hh] + Unld;
     }
  }  // {for loop}
  N++;
}

void ClassPSPnew::finish(bool good) {

  delete[] T0CanSnow;
  T0CanSnow = NULL;
  delete[] T0biomass;
  T0biomass = NULL;
}
