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

// TODO handle canopy snow frac
// TODO consistency with freezing point in kelvin 
// TODO canopy height always subtracted by 10?

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

  declvar("TCanSnow", TDim::NHRU, "snow Canopy temperature", "(" + string(DEGREE_CELSIUS) + ")", &TCanSnow);

  declvar("Tbiomass", TDim::NHRU, "biomass temperature", "(" + string(DEGREE_CELSIUS) + ")", &Tbiomass);

  declparam("Zcan", TDim::NHRU, "16", "0.0", "30.0", "Height within canopy to reduce wind speed to. This is the z variable in Eq. 1 in Chionco 1963.", "(m)", &Zcan);

  declparam("Biomass", TDim::NHRU, "30.0", "0.0", "100.0", "Biomass", "(kg/m^2)", &Biomass);

  declgetparam("*", "hru_T_g", "(" + string(DEGREE_CELSIUS) + ")", &hru_T_g); // input param for snobal
  declgetparam("*", "Lmax", "()", &Lmax); // input param for Canopy module
  declgetparam("*", "Zref", "()", &Zref); // input param for Canopy module
  declgetparam("*", "Zwind", "()", &Zwind); // input param for Canopy module
  declgetparam("*", "Ht", "()", &Ht); // input param for Canopy module  
  declgetparam("*", "LAI", "()", &LAI); // input param for Canopy module  
  declgetparam("*", "Cc", "()", &Cc); // input param for Canopy module  
  declgetparam("*", "Sbar", "()", &Sbar); // input param for Canopy module  
  declgetparam("*", "CanopyWindSwitch", "()", &CanopyWindSwitch); // input param for Canopy module  
  declgetparam("*", "Alpha_c", "()", &Alpha_c); // canopy albedo
  declgetparam("*", "Albedo_Snow", "()", &Albedo_Snow); // new snow albedo
  declgetparam("*", "B_canopy", "()", &B_canopy); // shortwave extinction coefficient for calculating longwave emission from the canopy (Pomeroy et al., 2009)

  declgetvar("obs", "hru_u", "(m/s)", &hru_u);
  declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &TAref);
  declgetvar("obs", "hru_rh", "(%)", &RHref);
  declgetvar("obs", "hru_p", "(mm/int)", &hru_p);
  declgetvar("*", "SolAng", "(r)", &SolarAng);
  declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
  declgetvar("*", "QdflatE", "(W/m^2)", &QdflatE);
  declgetvar("*", "Ts", "(" + string(DEGREE_CELSIUS) + ")", &Ts); // temperature of snowpack from Canopy module
  // declgetvar("*", "T_s_0", "(" + string(DEGREE_CELSIUS) + ")", &T_s_0); // temperature of the active layer from snobal
  declgetvar("*", "snowcover", "()", &snowcover); 
  declgetvar("*", "Snow_load", "()", &Snow_load);
  declgetvar("*", "rain_load", "()", &rain_load);
  declgetvar("*", "u_FHt", "()", &u_FHt);
  declgetvar("*", "Cp_h2o", "()", &Cp_h2o);
  declgetvar("*", "LAI_", "()", &LAI_);
  declgetvar("*", "Tauc", "()", &Tauc);
  declgetvar("*", "k", "()", &k);
  declgetvar("*", "cosxsflat", "(r)", &cosxsflat);
  declgetvar("*", "cosxs", "(r)", &cosxs);
  declgetvar("*", "Albedo", "()", &Albedo); // ground albedo
}

void ClassPSPnew::init(void) {

  nhru = getdim(TDim::NHRU);
  std::cout << "Number of HRUs: " << nhru << std::endl;

  T0CanSnow = new double[nhru];
  T0biomass = new double[nhru];

  for(long hh = 0; hh < nhru; hh++) {
    Qsubl[hh] = 0.0;
    std::cout << "Initialized HRU " << hh << std::endl;
  }
}

void ClassPSPnew::run(void) {

  const double Radius = 0.0005;   /* Ice sphere radius, metres */
  const double KinVisc = 1.88E-5; /* Kinematic viscosity of air (Sask. avg. value) */
  const double R = 8313.0;        /* Universal gas constant, J/(mole*K) */
  const double M = 18.01;         /* Molecular weight of water */
  const double RhoI = 900.0;      /* Density of ice, kg/m^3 */
  const double k1 = 0.0114;       /* Snow shape coefficient, Jackpine site */
  const double Fract = 0.37;       /* Fractal dimension */
  const double KARMAN = 0.4;      /* Von Karman"s constant */
  const double g = 9.8;           /* Gravitational acceleration, m/s^2 */
  const double SpHtAir = 1013.0;  /* Specific heat of air, J/(kg*K) */
  const double SpHtIce = 2090.0;  /* Specific heat of ice, J/(kg*K) */
  const double SpHtCan = 2700.0;  /* Specific heat of canopy (CLASS value), J/(kg*K) */
  const double Hs = 2838000.0;    // Latent heat of sublimation, J/kg

  // TODO for the initialization of variables below their value is undefined. This means they could contain any value that was previously stored at that memory location. 

  long TItNum, RHItNum, TItNum2; // Used in iteration loops
  bool Tup, RHup, Tup2;
  double I1, Cp, wtsubl, Unld;

  double StepT, StepRH, StepT2;
  double DblRHcan, DblTbarCan, DblTCanSnow;

  double RhoS, Lstar; // Hedstrom-Pomeroy, for L/L*

  double LambdaT; // is the thermal conductivity of air (J m-1 s-1  K-1)
  double u_Zcan; // wind speed at height Zcan (m s-1)
  double SVDensC, SVDensS, A, Nr, NuSh, D,
      Vs, Vhr, Ce, Vi; // Pomeroy-Schmidt components

  /* Radiation model components */
  double QTrans50;  // short wave radiation transmitted through to the canopy mid point height (W m-2)
  double Mu;        // variable from equation 4 from Parv. & Pom 2000
  double Qext;      // extinction efficiency of the canopy from Pomeroy 2009
  double tau_can100;   // canopy transmittance to shortwave radiation (-)
  double tau_can50;   // canopy transmittance to shortwave radiation for the upper half of the canopy (-)
  double QTrUp50;   // solar radiation reflected off the surface snowpack and back to the canopy midpoint (W m-2)
  double QTrans100; // solar radiation transmitted through the canopy (W m-2)
  double CanSnowFrac;

  double QlwUp;  // upwelling longwave radiation emitted from the subcanopy snowpack and lower portion of the canopy (W m-2)
  double QlwDn;  // downwelling longwave radiation emitted from the subcanopy snowpack and upper portion of the canopy (W m-2)
  double tau_atm;    // atmospheric transmissivity (-)
  double tau_atm_prev_day; // atmospheric transmissivity (-) from the last measurement during the day to be used where we dont have tau estimates at night preferred method outside of Sask.
  bool is_tau_obs;  // flag to check if tau_atm has been assigned
  double hru_ea_mb;  // conversion of kpa to mb for clarity
  double F;          // variable to scale incoming longwave radiation based on cloudiness from Sicart et al., (2006)
  double QlwDnAtm;   // longwave emission from cloudy skies calculated from Eq. 9 from Sicart et al., (2006)
  double QsDnStar;   // downwelling shortwave radiation to the top of the ice sphere
  double QsUpStar;   // upwelling shortwave radiation reflected from the ground surface hitting the bottom of the ice sphere
  double QlwUpStar;  // upwelling longwave radiation from the surface snowpack and lower portion of the canopy hitting the bottom of the ice sphere
  double QlwDnStar;  // downwelling longwave radiation from the atmosphere passing through the upper canopy gap (UpperGF), plus longwave emission from snow intercepted in the upper half of the canopy and any remaining exposed veg. elements
  double QlwOutStar; // longwave emission from the top and bottom of the ice sphere plan area
  double QnetStar;   // net radiation to the ice sphere
  double SVDensA, VPref, Ustar, Ra,
      Stabil, Qe, Qh, dUdt; // CLASS components
  double Ri;                // Richardsons number representing the ratio of shear production of turbulence to buoyancy production
  double dTdz;              // characteristic temperature gradient (change in deg / change in height)
  double dudz;              // characteristic wind gradient (change in wind speed / change in height)
  double TbarLayer;         // mean temperature of the layer (K)
  double RhoAir;           // density of the canopy air (kg m-3)
  double ebal_check;       // diagnostic variable to converge on snow and biomass temperature while loop

  double RHrefhh; // holds RH as fraction instead of default percentage
  double TsnowG;  // snowcover active layer (surface temp) from snobal

  static long N;
  static double Z0m, Z0h, Disp, CdragH, CdragE;

  for (long hh = 0; hh < nhru; hh++){

    const double ZwindFHt = Ht[hh]; // wind speed height for u_FHt (m), equal to mean canopy height (Ht, m)
    const double GapFrac = 1-Cc[hh];    /* Canopy gap fraction */
    const double UpperGF = 1-(Cc[hh]/2);    /* Mid-canopy level gap fraction */

    // initilize canopy temperature at air temperature
    // NOTE: TCanSnow is set equal to 0 in the canopy module if found to be melting
    if (getstep() == 1){
      Tbiomass[hh] = TAref[hh];
      TCanSnow[hh] = TAref[hh];
      T0CanSnow[hh] = TCanSnow[hh];
      T0biomass[hh] = Tbiomass[hh];
      N = 0;
      Z0m = Ht[hh] / 10.0; // One-time calc. of sfc. characteristics
      Z0h = Z0m / 2.0;
      Disp = Ht[hh] * 0.7;
      CdragH = (KARMAN / (log((ZwindFHt - Disp) / Z0h))) * (KARMAN / (log((ZwindFHt - Disp) / Z0m)));
      CdragE = sqr(KARMAN / (log(ZwindFHt / Zcan[hh])));
      tau_atm_prev_day = 0.818; // only used if it incoming ext. solar is == 0 on first time step, tau as in Global.cpp else statement as in LongVt, from average nightly measurements in Sask. likely biased to more clear skies
      is_tau_obs = false; 
    }

    // incoming longwave radiation from cloudy sky following Sicart et al., (2006)
    // Need to track this on all time steps
      if (is_tau_obs){ // was tau observed on the prev. timestep?
        tau_atm_prev_day = tau_atm;
      }

      if (QdflatE[hh] > 0.001 && QdflatE[hh] > Qsi_) // is it daytime ...
      {
        tau_atm = Qsi_/QdflatE[hh]; // Sicart et al., (2006) eq. 4 for daytime
        is_tau_obs = true;
      }
      else {
        // tau_atm = 0.818; // tau as in Global.cpp else statement as in LongVt
        tau_atm = tau_atm_prev_day;
        is_tau_obs = false;
      }
      
      hru_ea_mb = hru_ea[hh]*10.0; // kPa to mb 
      F = (1 + 0.44 * DblRHcan - 0.18 * tau_atm); // scaling factor >= 1 to increase longwave emission due to cloudiness, could update to use non iterating RH if breaking here
      F = std::max(F, 1.0); // Ensure F is greater than or equal to 1 as in Sicart et al., (2006)

      QlwDnAtm = 1.24 * pow(hru_ea_mb / (TAref[hh]+273.15), 1.0 / 7.0) * F * CRHM_constants::sbc * pow((TAref[hh]+273.15), 4)*UpperGF; // Eq. 9 from Sicart et al., (2006)


    if ((Snow_load[hh] > 0.0) || rain_load[hh] > 0.0){

      switch (variation){
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

      RhoS = 67.92 + 51.25*exp(TAref[hh]/2.59);
      // Lstar = Sbar[hh]*(0.27 + 46.0/RhoS)*LAI[hh];

      if(snowcover[hh] == 1){
        // TsnowG = T_s_0[hh]; // ground temp is equal to snowbal active layer temp when we have snow on the ground
        TsnowG = Ts[hh]; // ground temp is equal to snow surface temperature calculated in Canopy module
      } else {
        TsnowG = hru_T_g[hh]; // if no snowcover set to the ground temperature constant set as param in snobal
      }

      if(RHref[hh] > 1.5)
        RHrefhh = RHref[hh]/100.0;
      else
        RHrefhh = RHref[hh];

      DblTbarCan = Tbiomass[hh];

      DblRHcan = RHrefhh; // RHref[hh]; // fix for precision problem
      DblTCanSnow  = TCanSnow[hh];

      CanSnowFrac = pow(Snow_load[hh]/Lmax[hh],0.8); // changed from HP98 Lstar to larger Lmax to better represent canopy

      VPref = RHrefhh* Common::estar(TAref[hh]);
      SVDensA = Common::SVDens(TAref[hh]);
      RhoAir =  10000.0*94.97/(2870.0*(TAref[hh]+273.15))*(1.0-0.379*VPref/94.97);

      Ra = 1.0/(CdragH*(u_FHt[hh]+0.1));

      switch (CanopyWindSwitch[hh])
      {
        case 0:
        {  // original using Cionco wind model for dense canopies
          if ((Zcan[hh] - (2.0 / 3.0) * Zwind[hh]) > 0.0){
            // u_FHt[hh] = hru_u[hh] * log((Ht[hh] - (2.0 / 3.0) * Zwind[hh]) / 0.123 * Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0 * Zwind[hh]) / 0.123 * Zwind[hh]); // currently calculated in Canopy module
            A = 2.4338 + 3.45753 * exp(-u_FHt[hh]);                       /* Modified Cionco wind model */
            u_Zcan = u_FHt[hh] * exp(A * ((Zcan[hh]) / (Ht[hh])-1.0)); /* calculates canopy windspd  */
          } else {
            u_Zcan = 0.0;
          }
          break;
        } // case 0

        case 1:
        { // Canopy wind profile developed at Fortress sparse canopy
          double d0 = 0.5791121; // displacement height observed at sparse forest around Fortress Forest Tower
          double z0m = 0.4995565; // roughness length observed at above site
          
          if ((Zcan[hh] - d0) > z0m){
            Ustar = hru_u[hh]*PBSM_constants::KARMAN/(log((Zwind[hh] - d0)/z0m));
            u_Zcan = Ustar/PBSM_constants::KARMAN * log((Zcan[hh] - d0)/z0m);
          } else {
            u_Zcan = 0.0;
          }
        } // case 1
      } // end of switch CanopyWind

      Nr = 2*Radius*u_Zcan/KinVisc;
      NuSh = 1.79+0.606*sqrt(Nr);



      if (SolarAng[hh] > 0.001)  {
        //Qext = 0.781*SolarAng[hh]*cos(SolarAng[hh])+0.0591; // from Pomeroy and Dion (1996)
        double limit = cosxsflat[hh] / cosxs[hh];
        if (limit > 2.0){
          limit = 2.0;
        }
        tau_can100 = Tauc[hh]; // calculated by canopy module
        tau_can50 = exp(-k[hh] * (LAI_[hh]/2) * limit); // Eq 7. from Pomeroy et al., (2009) but sin of solar angle is appled to k already
        
        QTrans50 = Qsi_ * tau_can50; // incoming solar radiation transmitted through to the canopy mid point height, albedo for the ice particle handled below
        QTrans100 = Qsi_ * tau_can100; // as above but calculates solar transmitted through the canopy
        QTrUp50 = QTrans100*Albedo[hh]*tau_can50; // solar radiation reflected off the surface snowpack and back to the canopy midpoint
      }
      else {
        QTrans50 = 0.0;
        QTrUp50 = 0.0;
      }

      TItNum = 0;
      StepT = 0.1;

      do { /* Canopy T iteration loop */
        TItNum = TItNum+1;
        if (TItNum > 1) {
          DblTbarCan += StepT;
        } 

        SVDensC = Common::SVDens(DblTbarCan);
        TbarLayer = (TAref[hh]+DblTbarCan)/2.0+273.15;
        dTdz = (TAref[hh]-DblTbarCan)/(Zref[hh]-Ht[hh]);
        dudz = (sqr((hru_u[hh]-u_FHt[hh])/(Zwind[hh]-ZwindFHt)));
        Ri = g/TbarLayer*dTdz/dudz;
        // Ri = g/((TAref[hh]+DblTbarCan)/2.0+273.15)*(TAref[hh]-DblTbarCan)/(Zref[hh]-Zcan[hh])
        //           /(sqr((hru_u[hh]-u_FHt[hh])/(Zwind[hh]-ZwindFHt)));

        if (Ri < 0.0) {
          Stabil = pow((1.0 - 16.0*Ri), 0.75);
        } else {
          Stabil = sqr(1.0 - 5.0*Ri);
        }

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
              Tbiomass[hh] = DblTbarCan + ((DblTbarCan - DblTCanSnow)*Snow_load[hh]*SpHtIce)
                                          /(Biomass[hh]*SpHtCan);
            }

            // Subroutine to calculate radiation terms relative to the ice sphere,
            // this algorithm has been left unchanged but some symbols and comments have
            // been added for clarity. This differs from CLASS where the ebal is solved for the entire canopy
            // Values for incoming and outgoing solar rad previously were provided from obs
            // file and then longwave was calculated as a residual. This has been changed to
            // used modelled vars for all.

            /* Solve for outgoing longwave for lower portion of canopy */
            double Kstar_H = Qsi_ * (1.0 - Alpha_c[hh] - Tauc[hh] * (1.0 - Albedo[hh])); // Eq. 6 from Pomeroy 2009, shortwave radiation absorbed by the canopy to be converted to longwave

            double QlwUP_veg = CRHM_constants::sbc * CRHM_constants::emiss_c * pow(Tbiomass[hh] + 273.15, 4.0f) * (1.0 - CanSnowFrac) * (1.0 - GapFrac); // upward longwave from exposed veg on the bottom of the canopy
            double QlwUP_cansnow = CRHM_constants::sbc * CRHM_constants::emiss * pow(DblTCanSnow + 273.15, 4.0f) * CanSnowFrac; // upward longwve from snow intercepted on the bottom of the canopy
            double QlwUP_surfsnow = CRHM_constants::sbc * CRHM_constants::emiss * pow(Ts[hh] + 273.15, 4.0f) * GapFrac; // upward longwave from ground

            QlwUp = QlwUP_veg + QlwUP_cansnow + QlwUP_surfsnow + (B_canopy[hh] * Kstar_H)/2; 

            // QlwUpC100 = CRHM_constants::sbc*(GapFrac*pow(TsnowG+273.15,4.0) +
            //             (1.0-GapFrac)*((1.0-CanSnowFrac)*pow(Tbiomass[hh]+273.15,4.0)
            //                         + CanSnowFrac*pow(DblTCanSnow+273.15,4.0)));
            //         double QlwIn = Qn[hh]-QsIn[hh]+QsOut[hh]+QlwOut;

            double QlwDn_veg = CRHM_constants::sbc * CRHM_constants::emiss_c * pow(Tbiomass[hh] + 273.15, 4.0f) * (1.0 - CanSnowFrac); // downwelling longwave from b
            double QlwDn_cansnow = CRHM_constants::sbc * CRHM_constants::emiss * pow(DblTCanSnow + 273.15, 4.0f) * CanSnowFrac; // upward longwve from snow intercepted on the bottom of the canopy

            QlwDn = QlwDn_veg + QlwDn_cansnow + QlwDnAtm + (B_canopy[hh] * Kstar_H)/2; 

              /* Solve for particle net radiation*/
            QsDnStar = M_PI*Radius*Radius*QTrans50*(1.0-Albedo_Snow[hh]); // shortwave through to the mid canopy snow particle
            QsUpStar = M_PI*Radius*Radius*QTrUp50*(1.0-Alpha_c[hh]);
            QlwUpStar = M_PI*Radius*Radius*QlwUp;
            QlwDnStar = M_PI*Radius*Radius*QlwDn;
            QlwOutStar = 2*M_PI*Radius*Radius*CRHM_constants::sbc*pow(DblTCanSnow+273.15,4.0); // TODO should this be 2piR^2 (i.e., two times the area of a circle for top and bottom or should this be a sphere?)
            QnetStar = QsDnStar+QsUpStar+QlwDnStar+QlwUpStar-QlwOutStar;

            SVDensS = Common::SVDens(DblTCanSnow);

            // Vs and Vhr below were originally Eq. 45 in Pom & Gray 1995 and differ from Eq. 7 in Parv. & Pom 2000, NO change in canopy or snow temp between the two equations
            //Vs = (2.0*M_PI*D*Radius*(SVDensC*DblRHcan-SVDensS)*NuSh)*Hs; // original in PSPnew
            Vs = (2.0*M_PI*Radius*D*NuSh*(SVDensC*DblRHcan-SVDensS))*Hs; // Latent Heat Energy flux (j/s) relative to the ice sphere (negative for sublimation of particle). SVDensS not multiplied by RH because assumed to be saturated i.e., at 1.0
            //Vhr = (2.0*M_PI*LambdaT*Radius*(DblTCanSnow-DblTbarCan)*NuSh);  // original in PSPnew except that QnetStar was subtracted here originally, now moved this down to the ebal check
            Vhr = 2.0*M_PI*Radius*LambdaT*NuSh*(DblTCanSnow-DblTbarCan); // Sensible heat transfer (j/s), positive when energy is transfered away from the ice sphere

            ebal_check = Vs - Vhr - QnetStar;
            //ebal_check = Vs - Vhr; // this was original, but Vhr was subtracted by QnetStar above

            if (ebal_check < 0.0){
              if (TItNum2 == 1)  {
                Tup2 = false;
                StepT2 = -StepT2;
              } else {
                if (Tup2)  StepT2 = -StepT2/10.0;
                Tup2 = false;
              }
            } else {
              if (TItNum2 == 1){
                Tup2 = true;
              } else {
                if (!Tup2)  StepT2 = -StepT2/10.0;
                Tup2 = true;
              }
            }
          } while (fabs(ebal_check) >= 0.000001); /* Canopy Snow and Biomass[hh] T iteration loop. Original threshold was 0.000001 */

          Vs = Vs/(4.0/3.0*M_PI*pow(Radius, 3.0)*RhoI)/Hs;
          Ce = k1*pow(Snow_load[hh]/Lmax[hh], -Fract); // using Lmax here results in lower canopy temp
          Vi = Vs*Ce;
          Qsubl[hh] = Snow_load[hh]*Vi*Hs;
          Qe = Hs*CdragE*(u_FHt[hh]-u_Zcan)*(SVDensA*RHrefhh-SVDensC*DblRHcan)*Stabil;


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
        } while (fabs(Qsubl[hh]-Qe) >= 0.01); /* Canopy RH iteration loop */

        Qh = RhoAir*SpHtAir/Ra*(TAref[hh]-DblTbarCan)*Stabil;
        dUdt = ((Tbiomass[hh]-T0biomass[hh])*Biomass[hh]*SpHtCan
                +(DblTCanSnow-T0CanSnow[hh])*Cp_h2o[hh])/(Global::Interval*24*3600.0);

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
        if (TItNum >= 1000) {
          CRHMException TExcept("TItNum >= 1000: Exiting Canopy T iteration loop early.", TExcept::WARNING);
          LogError(TExcept);
        }
      } while (fabs(Qe+Qh-dUdt) >= 0.01 && TItNum < 1000); /* Canopy T iteration loop */

      TCanSnow[hh]  = DblTCanSnow;
      T0CanSnow[hh] = DblTCanSnow;
      T0biomass[hh] = Tbiomass[hh];
      // std::cout << "RHtNum: " << RHItNum << std::endl;
      // std::cout << "TItNum2: " << TItNum2 << std::endl;
      // std::cout << "TItNum: " << TItNum << std::endl;
    }

  } // {for loop}

    N++;
}

void ClassPSPnew::finish(bool good) {

  delete[] T0CanSnow;
  T0CanSnow = NULL;
  delete[] T0biomass;
  T0biomass = NULL;
}
