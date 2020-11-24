//created by Manishankar Mondal

#include "Classnetall.h"
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


Classnetall* Classnetall::klone(string name) const{
  return new Classnetall(name);
}

void Classnetall::decl(void) {

  Description = "'Models net all-wave radiation (Rn, RnD and RnD_POS) from sunshine hours, temperature and humidity using Brunt.'";

  declvar("net", TDim::NHRU, "all-wave net", "(MJ/m^2*int)", &net);

  decldiag("Rn", TDim::NHRU, "all-wave net", "(mm/m^2*int)", &Rn);

  declvar("netD", TDim::NHRU, "all-wave net", "(MJ/m^2*d)", &netD);

  declvar("RnD", TDim::NHRU, "all-wave net", "(mm/m^2*d)", &RnD);

  decldiag("RnD_POS", TDim::NHRU, "Sum of Positive all-wave net", "(mm/m^2*d)", &RnD_POS);

  declstatdiag("cum_net", TDim::NHRU, "cumulative all-wave net", "(MJ/m^2)", &cum_net);


  declgetvar("*", "hru_t", "(°C)", &hru_t);
  declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
  declgetvar("*", "hru_SunAct", "(h)", &hru_SunAct);

  declgetvar("*", "Tday", "(°C)",   &NotUsed, &tday_intvls); // from obs
  declgetvar("*", "EAday", "(kPa)", &NotUsed, &eaday_intvls); // from obs

  declgetvar("*", "SunMax", "(h)", &SunMax);
  declgetvar("*", "Qdro", "(W/m^2)",   &Qdro); // clear-sky direct (W/m^2)
  declgetvar("*", "Qdfo", "(W/m^2)",   &Qdfo); // clear-sky diffuse (W/m^2)
  declgetvar("*", "Albedo", "()", &Albedo);

  declgetvar("*", "pQdro", "(MJ/m^2*int)",  &pQdro, &pQdro_FREQ); // clear-sky direct (MJ/m^2/int)
  declgetvar("*", "pQdfo", "(MJ/m^2*int)",  &pQdfo, &pQdfo_FREQ); // clear-sky diffuse (MJ/m^2/int)
}

void Classnetall::init(void) {

  nhru = getdim(TDim::NHRU);

  for (hh = 0; hh < nhru; ++hh)
    cum_net[hh] = 0.0;
}

void Classnetall::run(void) {

  double netlong, shortw;

  long nstep = getstep() % Global::Freq;

  if(nstep == 1 || Global::Freq == 1){ // beginning of every day

    for (hh = 0; chkStruct(); ++hh) {
      netD[hh] = 0.0;
      RnD[hh] = 0.0;
      RnD_POS[hh] = 0.0;

      for (int ff = 0; ff < Global::Freq; ++ff) {
        if(SunMax[hh] > 0.0)
          netlong = -0.85 + 0.97*CRHM_constants::SB*pow(tday_intvls[ff][hh]+273.0f, 4)*(-0.39f+0.093f*sqrt(eaday_intvls[ff][hh]))*
                                    (0.26f+0.81f*(hru_SunAct[hh]/SunMax[hh]));
        else
          netlong = -0.85;

        if(hru_SunAct[hh] > 0.0 && SunMax[hh] > 0.0)
          shortw = (0.024f+0.974f*pow(hru_SunAct[hh]/SunMax[hh], 1.35f))*pQdro_FREQ[ff][hh] +
            (2.68f+2.2f*(hru_SunAct[hh]/SunMax[hh])-3.85f*sqr(hru_SunAct[hh]/SunMax[hh]))*pQdfo_FREQ[ff][hh];
        else
          shortw = (0.024f*pQdro_FREQ[ff][hh] + 2.68f*pQdfo_FREQ[ff][hh]);

        double Net = (shortw*(1.0f-Albedo[hh]) + netlong/Global::Freq); // MJ/interval
        netD[hh] +=  Net;

        Net = Net/(2.501f-0.002361f*tday_intvls[ff][hh]); // MJ/m^2 to mm/m^2

        RnD[hh] += Net;
        if(Net > 0.0) RnD_POS[hh] += Net;

      } // Interval loop
    } // HRU loop
  } // if first interval

  for (hh = 0; chkStruct(); ++hh) {

// t Kelvin degrees, ea bar

    if(SunMax[hh] > 0.0)
      netlong = -0.85f + 0.97*CRHM_constants::SB*pow(hru_t[hh]+273.0f, 4.0f)*(-0.39f+0.093f*sqrt(hru_ea[hh]))*
                                (0.26f+0.81f*(hru_SunAct[hh]/SunMax[hh]));
    else
      netlong = -0.85;

    if(hru_SunAct[hh] > 0.0 && SunMax[hh] > 0.0)
      shortw = (0.024f+0.974f*pow(hru_SunAct[hh]/SunMax[hh], 1.35f))*Qdro[hh]*WtoMJ_D +
        (2.68f+2.2f*(hru_SunAct[hh]/SunMax[hh])-3.85f*sqr(hru_SunAct[hh]/SunMax[hh]))*Qdfo[hh]*WtoMJ_D;
    else
      shortw = (0.024f*Qdro[hh] + 2.68f*Qdfo[hh])*WtoMJ_D;

    net[hh] = (shortw*(1.0f-Albedo[hh]) + netlong)/Global::Freq; // MJ/day to MJ/interval
    Rn[hh] = net[hh]/(2.501f-0.002361f*hru_t[hh]); // MJ/interval to mm/interval

    cum_net [hh] += net[hh]; // mm/interval

  } // HRU loop
}