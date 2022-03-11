//created by Manishankar Mondal

#include "ClassPSPnew.h"

#include <algorithm>
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM/ClassCRHM.h"
#include "../newmodules/SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

ClassPSPnew* ClassPSPnew::klone(string name) const{
  return new ClassPSPnew(name);
}

void ClassPSPnew::decl(void) {

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

  declgetvar("obs",    "hru_u",  "(m/s)",   &hru_u);
  declgetvar("obs",    "hru_t", "(" + string(DEGREE_CELSIUS) + ")",   &TAref);
  declgetvar("obs",    "hru_rh", "(%)",  &RHref);
  declgetvar("obs",    "hru_p",  "(mm/int)",   &hru_p);
  declgetvar("*",      "SolAng", "(r)",  &SolarAng);

  declreadobs("TsnowG", TDim::NHRU, "snow temperature", "(" + string(DEGREE_CELSIUS) + ")", &TsnowG, HRU_OBS_misc);
  declreadobs("Lnot", TDim::NHRU, "tree weight",      "(kg/m^2)", &Lnot, HRU_OBS_misc);
  declreadobs("Qsi", TDim::NHRU, "Qsi",      "(W/m^2)", &QsIn, HRU_OBS_Q);
  declreadobs("Qso", TDim::NHRU, "Qso",      "(W/m^2)", &QsOut, HRU_OBS_Q);

}

void ClassPSPnew::init(void) {

  nhru = getdim(TDim::NHRU);

  T0CanSnow = new double[nhru];
  T0biomass = new double[nhru];

  for(long hh = 0; hh < nhru; hh++) {
    Qsubl[hh] = 0.0;
    Load[hh] = 0.0;
    Thru[hh] = 0.0;
  }
}

  double SatVP(double Temp) /* outputs sat. vapor pressure, Pa */
    {if(Temp > 0.0)  return 611.0*exp(17.27*Temp/(Temp+237.3));
     else return 611.0*exp(21.88*Temp/(Temp+265.5));
  }

void ClassPSPnew::run(void) {

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

  double QTrans50, QTrUp50, CanSnowFrac; /* Radiation model components */

  double RhoAir, SVDensA, VPref, Ustar, Uh, Ra, Ri,
         Stabil, Qe, Qh, dUdt; // CLASS components

  static long N;
  static double Z0m, Z0h, Disp, CdragH, CdragE;

  const double Cc = 0.82;
  const double Velw = 0.75;

  for(long hh = 0; hh < nhru; hh++) {

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
     Load[hh] =  Lnot[0];
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

   double RHrefhh;
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
     double Mu = LAI[hh]/(Ht[hh]-10)*(0.781*SolarAng[hh]*cos(SolarAng[hh])+0.0591);
     QTrans50 = QsIn[hh]*exp(-Mu*(Ht[hh]-10)/2/sin(SolarAng[hh]));
     double QTrans100 = QsIn[hh]*exp(-Mu*(Ht[hh]-10)/sin(SolarAng[hh]));
     QTrUp50 = (1.0-SnowAlb)*QTrans100*exp(LAI[hh]/(Ht[hh]-10)*0.0591*(Ht[hh]-10)/2);
   }
   else {
     QTrans50 = 0;
     QTrUp50 =0;
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
              /* Solve for longwave */
         double QlwOut = SBC*(GapFrac*pow(TsnowG[0]+273.15,4.0) +
                     (1.0-GapFrac)*((1.0-CanSnowFrac)*pow(Tbiomass[hh]+273.15,4.0)
                                 + CanSnowFrac*pow(DblTCanSnow+273.15,4.0)));
//         double QlwIn = Qn[hh]-QsIn[hh]+QsOut[hh]+QlwOut;
         double QlwIn = QsIn[hh]+QsOut[hh]+QlwOut;

              /* Solve for particle net radiation*/
         double QsDnStar = M_PI*Radius*Radius*QTrans50*(1.0-SnowAlb);
         double QsUpStar = M_PI*Radius*Radius*QTrUp50*(1.0-CanAlb);
         double QlwUpStar = M_PI*Radius*Radius*QlwOut;
         double QlwDnStar = M_PI*Radius*Radius*(QlwIn*UpperGF + SBC*(1.0-UpperGF)*
                              ((1.0-CanSnowFrac)*pow(Tbiomass[hh]+273.15,4.0)
                               + (CanSnowFrac*pow(DblTCanSnow+273.15,4.0))));
         double QradStar = 2*M_PI*Radius*Radius*SBC*pow(DblTCanSnow+273.15,4.0);
         double QnetStar = QsDnStar+QsUpStar+QlwDnStar+QlwUpStar-QradStar;

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