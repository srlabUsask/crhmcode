//created by Manishankar Mondal

#include "ClassShutWall.h"
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

ClassShutWall* ClassShutWall::klone(string name) const{
  return new ClassShutWall(name);
}

 void ClassShutWall::decl(void) {

  Description = "'Evaluation evaporation model (Shuttleworth - Wallace).'";

  declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

  declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

  declvar("hru_evap", NHRU, "evaporation, interval calculation from daily", "(mm/int)", &evap);

  declvar("hru_evapD", NHRU, "daily evaporation", "(mm)", &evapD);

  declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation from daily", "(mm)", &cum_evap);

  decldiag("Cc", NHRU, "canopy weighting coefficient", "()", &Cc);

  decldiag("Cs", NHRU, "substrate weighting coefficient", "()", &Cs);

  decldiag("Ra", NHRU, "", "()", &Ra);

  decldiag("Rc", NHRU, "", "()", &Rc);

  decldiag("Rs", NHRU, "", "()", &Rs);

  decldiag("ETc", NHRU, "", "(mm/d)", &ETc);

  decldiag("ETs", NHRU, "", "(mm/d)", &ETs);

  decldiag("raa", NHRU, "aerodynamic resistance from canopy to reference height", "(s/m)", &raa);

  decldiag("rca", NHRU, "boundary resistance", "(s/m)", &rca);

  decldiag("rcs", NHRU, "canopy stomatal resistance", "(s/m)", &rcs);

  decldiag("rsa", NHRU, "aerodynamic resistance from soil to canopy", "(s/m)", &rsa);

  decldiag("rss", NHRU, "soil surface resistance", "(s/m)", &rss);


  decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


  declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declparam("basin_area", BASIN, "1", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

  decldiagparam("Cr", NHRU, "[0.7]", "0.3", "0.9", "extinction coefficient", "(s/m)", &Cr);

  declparam("LAI", NHRU, "[2.2]", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

  declparam("w", NHRU, "[0.004]", "0.0", "1.0", "canopy characteristic leaf width", "(m)", &w);

  declparam("z0g", NHRU, "[0.01]", "0.0", "1.0", "ground roughness length", "(m)", &z0g);

  declparam("rs", NHRU, "[250]", "0.0", "1e3", "mean stomatal resistance", "(s/m)", &rst);

  decldiagparam("gammab", NHRU, "[0.5]", "0.0", "1.0", "shielding factor", "()", &gammab);

  declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

  decldiagparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);


  declgetvar("*", "hru_u",  "(m/s)", &hru_u);
  declgetvar("*", "hru_t",  "(m/s)", &hru_t);
  declgetvar("*", "hru_ea", "kPa",   &hru_ea);

  declreadobs("Qn", NHRU, "net all-wave", "(W/m^2)", &Qn, HRU_OBS_Q);
  declreadobs("Qg", NHRU, "ground flux", "(W/m^2)", &Qg, HRU_OBS_Q);

}

void ClassShutWall::init(void) {

  nhru = getdim(NHRU);

  for(hh=0; hh < nhru; ++hh) {

    Pa[hh] = 101.3f*pow((293.0f-0.0065f*hru_elev[hh])/293.0f, 5.26f);  // kPa
    cum_evap[hh] = 0.0;
    hru_cum_actet[hh] = 0.0;
  }
}

void ClassShutWall::run(void) {

   const float Cp = 1.005; // (kj/kg/K)

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

     float U =hru_u[hh];

     float Ustar = CRHM_constants::kappa*U/log((Zwind[hh] - d)/z0);

     float kh = CRHM_constants::kappa*Ustar*(Ht[hh] - d);

     float rb = 100/n*sqrt(w[hh]/(0.1*U))/(1.0-exp(-n/2.0));

     raa[hh] = 1.0/(CRHM_constants::kappa*Ustar)*log((Zwind[hh]-d)/(Ht[hh] - d)) + Ht[hh]/(n*kh)*(exp(n*(1-(z0+d)/Ht[hh])) - 1.0);
     rca[hh] = rb*gammab[hh]/LAI[hh];
     rcs[hh] = rst[hh]/(2.0*LAI[hh]);
     rsa[hh] = (Ht[hh]*exp(n)/(n*kh))*(exp(-n*z0g[hh]/Ht[hh])-exp(-n*(z0+d)/Ht[hh]));
     rss[hh] = 4000;

     float Rn = Qn[hh] // Watts
                 *86400/1e3/lambda(hru_t[hh]); // (mm/d)
     float G =  Qg[hh] // Watts
                 *86400/1e3/lambda(hru_t[hh]); // (mm/d)
     float Rsn = Rn*exp(-Cr[hh]*LAI[hh]);


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

double ClassShutWall::gamma(float Pa, float t) // Psychrometric constant (kPa/°C)
{
   return(1.63 * Pa / lambda(t)); // lambda (kJ/(kg °C))
}

float ClassShutWall::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
  const float R = 2870;
   return (1E4*Pa /(R*( 273.15 + t))*(1.0 - 0.379*(ea/Pa)) ); //
}

float ClassShutWall::lambda(float t) // Latent heat of vaporization  (kJ/(kg °C))
{
   return( 2501.0 - 2.361 * t );
}

double ClassShutWall::delta(float t)  // Slope of sat vap p vs t, (kPa/°C)
{
  if (t > 0.0)
    return(2504.0*exp(17.27 * t/(t+237.3)) / sqr(t+237.3));
  else
    return(3549.0*exp( 21.88 * t/(t+265.5)) / sqr(t+265.5));
}