//created by Manishankar Mondal

#include "ClassShutWallD.h"
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

ClassShutWallD* ClassShutWallD::klone(string name) const{
  return new ClassShutWallD(name);
}

 void ClassShutWallD::decl(void) {

  Description = "'Daily evaluation evaporation model (Shuttleworth - Wallace).'";

  declvar("hru_actet", TDim::NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

  declstatdiag("hru_cum_actet", TDim::NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

  declvar("hru_evapD", TDim::NHRU, "daily evaporation", "(mm)", &evapD);

  declstatdiag("hru_cum_evap", TDim::NHRU, "cumulative interval evaporation from daily", "(mm)", &cum_evap);

  declvar("Cc", TDim::NHRU, "canopy weighting coefficient", "()", &Cc);

  declvar("Cs", TDim::NHRU, "substrate weighting coefficient", "()", &Cs);

  decldiag("Ra", TDim::NHRU, "", "()", &Ra);

  decldiag("Rc", TDim::NHRU, "", "()", &Rc);

  decldiag("Rs", TDim::NHRU, "", "()", &Rs);

  decldiag("ETc", TDim::NHRU, "", "(mm/d)", &ETc);

  decldiag("ETs", TDim::NHRU, "", "(mm/d)", &ETs);

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

  decldiagparam("Cr", TDim::NHRU, "[0.7]", "0.3", "0.9", "extinction coefficient", "()", &Cr);

  declparam("LAI", TDim::NHRU, "[2.2]", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

  declparam("w", TDim::NHRU, "[0.004]", "0.0", "1.0", "canopy characteristic leaf width", "(m)", &w);

  declparam("z0g", TDim::NHRU, "[0.01]", "0.0", "1.0", "ground roughness length", "(m)", &z0g);

  declparam("rs", TDim::NHRU, "[250]", "0.0", "1e3", "mean stomatal resistance", "(s/m)", &rst);

  decldiagparam("gammab", TDim::NHRU, "[0.5]", "0.0", "1.0", "shielding factor", "()", &gammab);

  declparam("Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

  decldiagparam("Zwind", TDim::NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);


  declgetvar("*", "hru_umean",  "(m/s)", &hru_umean);
  declgetvar("*", "hru_tmean",  "(m/s)", &hru_tmean);
  declgetvar("*", "hru_eamean", "kPa",   &hru_eamean);

  declreadobs("Qn", TDim::NHRU, "net all-wave", "(W/m^2)", &Qn, HRU_OBS_Q);
  declreadobs("Qg", TDim::NHRU, "ground flux", "(W/m^2)", &Qg, HRU_OBS_misc);

  declobsfunc("Qn", "Qnmean", &Qnmean, TFun::AVG);
  declobsfunc("Qg", "Qgmean", &Qgmean, TFun::AVG);

}

void ClassShutWallD::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh=0; hh < nhru; ++hh) {

    Pa[hh] = 101.3f*pow((293.0f-0.0065f*hru_elev[hh])/293.0f, 5.26f);  // kPa
    cum_evap[hh] = 0.0;
    evapD[hh] = 0.0;
    hru_cum_actet[hh] = 0.0;
  }
}

void ClassShutWallD::run(void) {

   const double Cp = 1.005; // (kj/kg/K)

   long nstep = getstep() % Global::Freq;

   for(hh = 0; chkStruct(); ++hh) {

     if(inhibit_evap[hh])
       continue;

     if(nstep == 1){ // beginning of every day

       hru_actet[hh] = 0.0;

       double z0 = 0.13*Ht[hh];
       double d = 0.63*Ht[hh];

       double n;
       if(Ht[hh] < 1.0)
         n = 2.5;
       else if(Ht[hh] < 10.0)
         n = 2.306 +0.194*Ht[hh];
       else
         n = 4.25;

       double U = max<double> (hru_umean[hh], 0.1);

       double Ustar = CRHM_constants::kappa*U/log((Zwind[hh]-d)/z0);

       double kh = CRHM_constants::kappa*Ustar*(Ht[hh] - d);

       double rb = 100/n*sqrt(w[hh]/(0.1*U))/(1.0-exp(-n/2.0));

       raa[hh] = 1.0/(CRHM_constants::kappa*Ustar)*log((Zwind[hh]-d)/(Ht[hh]-d)) + Ht[hh]/(n*kh)*(exp(n*(1-(z0+d)/Ht[hh])) - 1.0);
       rca[hh] = rb*gammab[hh]/LAI[hh];
       rcs[hh] = rst[hh]/(2.0*LAI[hh]);
       rsa[hh] = (Ht[hh]*exp(n)/(n*kh))*(exp(-n*z0g[hh]/Ht[hh])-exp(-n*(z0+d)/Ht[hh]));
       rss[hh] = 4000;

       double Rn = Qnmean[hh] // Watts
                   *86400/1e3/lambda(hru_tmean[hh]); // (mm/d)
       double G =  Qgmean[hh] // Watts
                   *86400/1e3/lambda(hru_tmean[hh]); // (mm/d)
       double Rsn = Rn*exp(-Cr[hh]*LAI[hh]);


       Ra[hh] = (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh]))*raa[hh];
       Rc[hh] = (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh]))*rca[hh] + gamma(Pa[hh], hru_tmean[hh])*rcs[hh];
       Rs[hh] = (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh]))*rsa[hh] + gamma(Pa[hh], hru_tmean[hh])*rss[hh];

       Cc[hh] = 1.0/(1.0+Rc[hh]*Ra[hh]/(Rs[hh]*(Rc[hh]+Ra[hh])));
       Cs[hh] = 1.0/(1.0+Rs[hh]*Ra[hh]/(Rc[hh]*(Rs[hh]+Ra[hh])));

       ETc[hh] = (delta(hru_tmean[hh])*(Rn - G)
                   + ((RHOa(hru_tmean[hh], hru_eamean[hh], Pa[hh])*Cp*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]))
                   - (delta(hru_tmean[hh])*rca[hh]*(Rsn - G))/(raa[hh]+rca[hh])))
                   /(delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh])*(1.0 +rcs[hh]/(raa[hh]+rca[hh])));

       ETs[hh] = (delta(hru_tmean[hh])*(Rn - G)
                   + ((RHOa(hru_tmean[hh], hru_eamean[hh], Pa[hh])*Cp*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]))
                   - (delta(hru_tmean[hh])*rsa[hh]*(Rn - Rsn))/(raa[hh]+rsa[hh])))
                   /(delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh])*(1.0 +rss[hh]/(raa[hh]+rca[hh])));

       evapD[hh] = Cc[hh]*ETc[hh] + Cs[hh]*ETs[hh];

       cum_evap[hh] += evapD[hh];

     } //  beginning of every day
   } // for
}

void ClassShutWallD::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (ShuttleWallaceD)' hru_cum_evap (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_evap[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (ShuttleWallace)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh],     hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}

double ClassShutWallD::gamma(double Pa, double t) // Psychrometric constant (kPa/°C)
{
   return(1.63 * Pa / lambda(t)); // lambda (kJ/(kg °C))
}

double ClassShutWallD::RHOa(double t, double ea, double Pa) // atmospheric density (kg/m^3)
{
  const double R = 2870;
   return (1E4*Pa /(R*( 273.15 + t))*(1.0 - 0.379*(ea/Pa)) ); //
}

double ClassShutWallD::lambda(double t) // Latent heat of vaporization  (kJ/(kg °C))
{
   return( 2501.0 - 2.361 * t );
}

double ClassShutWallD::delta(double t)  // Slope of sat vap p vs t, (kPa/°C)
{
  if (t > 0.0)
    return(2504.0*exp(17.27 * t/(t+237.3)) / sqr(t+237.3));
  else
    return(3549.0*exp( 21.88 * t/(t+265.5)) / sqr(t+265.5));
}