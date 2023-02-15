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

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassShutWall.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"

using namespace CRHM;

ClassShutWall* ClassShutWall::klone(string name) const{
  return new ClassShutWall(name);
}

 void ClassShutWall::decl(void) {

  Description = "'Evaluation evaporation model (Shuttleworth - Wallace).'";

  declvar("hru_actet", TDim::NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

  declstatdiag("hru_cum_actet", TDim::NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

  declvar("hru_evap", TDim::NHRU, "interval evaporation", "(mm/int)", &evap);

  declvar("hru_evapD", TDim::NHRU, "daily evaporation", "(mm)", &evapD);

  declstatdiag("hru_cum_evap", TDim::NHRU, "cumulative interval evaporation", "(mm)", &cum_evap);

  decldiag("Cc", TDim::NHRU, "canopy weighting coefficient", "()", &Cc);

  decldiag("Cs", TDim::NHRU, "substrate weighting coefficient", "()", &Cs);

  decldiag("Ra", TDim::NHRU, "aerodynamic resistance 'component'", "(mb/K*s/m)", &Ra);

  decldiag("Rc", TDim::NHRU, "canopy stomatal resistance 'component'", "(mb/K*s/m)", &Rc);

  decldiag("Rs", TDim::NHRU, "soil surface resistance 'component'", "(mb/K*s/m)", &Rs);

  decldiag("ETc", TDim::NHRU, "daily evaporation from canopy", "(mm/d)", &ETc);

  decldiag("ETs", TDim::NHRU, "daily evaporation from soil surface", "(mm/d)", &ETs);

  decldiag("raa", TDim::NHRU, "aerodynamic resistance from canopy to reference height", "(s/m)", &raa);

  decldiag("rca", TDim::NHRU, "boundary resistance", "(s/m)", &rca);

  decldiag("rcs", TDim::NHRU, "canopy stomatal resistance", "(s/m)", &rcs);

  decldiag("rsa", TDim::NHRU, "aerodynamic resistance from soil to canopy", "(s/m)", &rsa);

  decldiag("rss", TDim::NHRU, "soil surface resistance", "(s/m)", &rss);


  decllocal("Pa", TDim::NHRU, "Atmospheric pressure", "(kPa)", &Pa);


  declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declparam("basin_area", TDim::BASIN, "1", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

  decldiagparam("Cr", TDim::NHRU, "[0.7]", "0.3", "0.9", "extinction coefficient", "(s/m)", &Cr);

  declparam("LAI", TDim::NHRU, "[2.2]", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

  declparam("w", TDim::NHRU, "[0.004]", "0.0", "1.0", "canopy characteristic leaf width", "(m)", &w);

  declparam("z0g", TDim::NHRU, "[0.01]", "0.0", "1.0", "ground roughness length", "(m)", &z0g);

  declparam("rs", TDim::NHRU, "[250]", "0.0", "1e3", "mean stomatal resistance", "(s/m)", &rst);

  decldiagparam("gammab", TDim::NHRU, "[0.5]", "0.0", "1.0", "shielding factor", "()", &gammab);

  declparam("Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

  decldiagparam("Zwind", TDim::NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);


  declgetvar("*", "hru_u",  "(m/s)", &hru_u);
  declgetvar("*", "hru_t",  "(m/s)", &hru_t);
  declgetvar("*", "hru_ea", "kPa",   &hru_ea);

  declreadobs("Qn", TDim::NHRU, "net all-wave", "(W/m^2)", &Qn, HRU_OBS_Q);
  declreadobs("Qg", TDim::NHRU, "ground flux", "(W/m^2)", &Qg, HRU_OBS_Q);

}

void ClassShutWall::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh=0; hh < nhru; ++hh) {

    Pa[hh] = 101.3f*pow((293.0f-0.0065f*hru_elev[hh])/293.0f, 5.26f);  // kPa
    cum_evap[hh] = 0.0;
    hru_cum_actet[hh] = 0.0;
  }
}

void ClassShutWall::run(void) {

   const double Cp = 1.005; // (kj/kg/K)

   long nstep = getstep() % Global::Freq;

   for(hh = 0; chkStruct(); ++hh) {

     evapD[hh] = 0.0;
     hru_actet[hh] = 0.0;

     if(inhibit_evap[hh])
       continue;

     if(nstep == 1){ // beginning of every day

       z0 = 0.13*Ht[hh];
       d = 0.63*Ht[hh];

       if(Ht[hh] < 1.0)
         n = 2.5;
       else if(Ht[hh] < 10.0)
         n = 2.306 +0.194*Ht[hh];
       else
         n = 4.25;

     } //  beginning of every day

     double U =hru_u[hh];

     double Ustar = CRHM_constants::kappa*U/log((Zwind[hh] - d)/z0);

     double kh = CRHM_constants::kappa*Ustar*(Ht[hh] - d);

     double rb = 100/n*sqrt(w[hh]/(0.1*U))/(1.0-exp(-n/2.0));

     raa[hh] = 1.0/(CRHM_constants::kappa*Ustar)*log((Zwind[hh]-d)/(Ht[hh] - d)) + Ht[hh]/(n*kh)*(exp(n*(1-(z0+d)/Ht[hh])) - 1.0);
     rca[hh] = rb*gammab[hh]/LAI[hh];
     rcs[hh] = rst[hh]/(2.0*LAI[hh]);
     rsa[hh] = (Ht[hh]*exp(n)/(n*kh))*(exp(-n*z0g[hh]/Ht[hh])-exp(-n*(z0+d)/Ht[hh]));
     rss[hh] = 4000;

     double Rn = Qn[hh] // Watts
                 *86400/1e3/lambda(hru_t[hh]); // (mm/d)
     double G =  Qg[hh] // Watts
                 *86400/1e3/lambda(hru_t[hh]); // (mm/d)
     double Rsn = Rn*exp(-Cr[hh]*LAI[hh]);


     Ra[hh] = (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]))*raa[hh];
     Rc[hh] = (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]))*rca[hh] + gamma(Pa[hh], hru_t[hh])*rcs[hh];
     Rs[hh] = (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]))*rsa[hh] + gamma(Pa[hh], hru_t[hh])*rss[hh];

     Cc[hh] = 1.0/(1.0+Rc[hh]*Ra[hh]/(Rs[hh]*(Rc[hh]+Ra[hh])));
     Cs[hh] = 1.0/(1.0+Rs[hh]*Ra[hh]/(Rc[hh]*(Rs[hh]+Ra[hh])));

     ETc[hh] = (delta(hru_t[hh])*(Rn - G)
                 + ((RHOa(hru_t[hh], hru_ea[hh], Pa[hh])*Cp*(Common::estar(hru_t[hh]) - hru_ea[hh]))
                 - (delta(hru_t[hh])*rca[hh]*(Rsn - G))/(raa[hh]+rca[hh])))
                 /(delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])*(1.0 +rcs[hh]/(raa[hh]+rca[hh])));

     ETs[hh] = (delta(hru_t[hh])*(Rn - G)
                 + ((RHOa(hru_t[hh], hru_ea[hh], Pa[hh])*Cp*(Common::estar(hru_t[hh]) - hru_ea[hh]))
                 - (delta(hru_t[hh])*rsa[hh]*(Rn - Rsn))/(raa[hh]+rsa[hh])))
                 / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])*(1.0 +rss[hh]/(raa[hh]+rca[hh])));

     evap[hh] = (Cc[hh]*ETc[hh] + Cs[hh]*ETs[hh])/Global::Freq;

     cum_evap[hh] += evap[hh];

     evapD[hh] += evap[hh];

   } // for
}

void ClassShutWall::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (ShuttleWallace)' hru_cum_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_evap[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (ShuttleWallace)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh],     hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}

double ClassShutWall::gamma(double Pa, double t) // Psychrometric constant (kPa/DEGREE_CELCIUS)
{
   return(1.63 * Pa / lambda(t)); // lambda (kJ/(kg DEGREE_CELCIUS))
}

double ClassShutWall::RHOa(double t, double ea, double Pa) // atmospheric density (kg/m^3)
{
  const double R = 2870;
   return (1E4*Pa /(R*( 273.15 + t))*(1.0 - 0.379*(ea/Pa)) ); //
}

double ClassShutWall::lambda(double t) // Latent heat of vaporization  (kJ/(kg DEGREE_CELCIUS))
{
   return( 2501.0 - 2.361 * t );
}

double ClassShutWall::delta(double t)  // Slope of sat vap p vs t, (kPa/DEGREE_CELCIUS)
{
  if (t > 0.0)
    return(2504.0*exp(17.27 * t/(t+237.3)) / sqr(t+237.3));
  else
    return(3549.0*exp( 21.88 * t/(t+265.5)) / sqr(t+265.5));
}
