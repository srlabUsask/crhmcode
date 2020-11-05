//created by Manishankar Mondal

#include "ClassAnnan.h"
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

ClassAnnan* ClassAnnan::klone(string name) const{
  return new ClassAnnan(name);
}

void ClassAnnan::decl(void) {

  Description = "'Estimates incoming short wave radiation from daily minimum and maximum temperatures (Annandale et al. (2001)).' \
                 'outputs observations(QsiA, QsiD and QsiS) with sunshine hours variable (hru_SunAct),' \
                 'outputs variables (QsiA_Var, QsiD_Var and QsiS_Var) with sunshine hours variable (hru_SunAct).'";

  variation_set = VARIATION_ORG;

  declparam("krs", TDim::NHRU, "[0.16]", "0.15", "0.2", "location index, interior = 0.16/coastal = 0.19", "()", &krs);
  declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declgetvar("*", "hru_tmax", "(°C)",  &hru_tmax);
  declgetvar("*", "hru_tmin", "(°C)",  &hru_tmin);

  declgetvar("*", "QdroDext", "(MJ/m^2*d)", &QdroDext);
  declgetvar("*", "QdflatD", "(MJ/m^2*d)", &QdflatD);
  declgetvar("*", "QdflatE", "(W/m^2)", &QdflatE);
  declgetvar("*", "Qdro",   "(W/m^2)", &Qdro);
  declgetvar("*", "Qdfo",   "(W/m^2)", &Qdfo);
  declgetvar("*", "QdfoD",   "(MJ/m^2*d)", &QdfoD);
  declgetvar("*", "SunMax",  "(h)", &SunMax);

  declvar("hru_SunAct", TDim::NHRU, "Actual Sunshine", "(h)", &hru_SunAct);

  variation_set = VARIATION_0;

  declobs("QsiA", TDim::NHRU, "interval synthesized short-wave derived from Annandale method", "(W/m^2)", &QsiA);
  declobs("QsiD", TDim::NHRU, "daily synthesized short-wave derived from Annandale method", "(W/m^2)", &QsiD);
  declobs("QsiS", TDim::NHRU, "interval synthesized short-wave on slope derived from global and Annandale method", "(W/m^2)", &QsiS);

  variation_set = VARIATION_1;

  declvar("QsiA_Var", TDim::NHRU, "interval synthesized short-wave derived from Annandale method", "(W/m^2)", &QsiA_Var);
  declvar("QsiD_Var", TDim::NHRU, "daily synthesized short-wave derived from Annandale method", "(W/m^2)", &QsiD_Var);
  declvar("QsiS_Var", TDim::NHRU, "synthesized short-wave on slope derived from global and Annandale method", "(W/m^2)", &QsiS_Var);

  variation_set = VARIATION_ORG;
}

void ClassAnnan::init(void) {

  nhru = getdim(TDim::NHRU);
}

void ClassAnnan::run(void) {

  double QsiAT = 0.0;
  double QsiST = 0.0;

  for (hh = 0; chkStruct(); ++hh){
    long nstep = getstep() % Global::Freq;

    if(nstep == 1 || Global::Freq == 1) { // beginning of every day

      if(hru_tmax[hh] - hru_tmin[hh] < 0.00001)
        TauAT = 0.0;
      else
        TauAT = krs[hh]*(1.0 + 2.7E-5*hru_elev[hh])*pow(hru_tmax[hh] - hru_tmin[hh], 0.5f);

      QsiDT = QdroDext[hh]*TauAT*MJ_DtoW;

    } // if

    if(variation == VARIATION_ORG || variation == VARIATION_1){
      if(QdflatE[hh] > 1.0){
        QsiAT = QdflatE[hh]*TauAT;
        QsiST = (Qdro[hh] + Qdfo[hh])*QsiDT/(MJ_DtoW)/QdflatD[hh]; // on slope simplified
      }
      else{
        QsiAT = 0.0;
        QsiST = 0.0;
      }
    }

    double Ratio;
    double Temp =  QsiDT*WtoMJ_D - QdfoD[hh]; // observed direct incoming  - QdfoD[hh]
    if(Temp <= 0.0 || QdflatD[hh] - QdfoD[hh] <= 0.0)
      Ratio = 0.0;
    else{
      Ratio = Temp/(QdflatD[hh] - QdfoD[hh]); // incoming clear sky direct only
      if(Ratio > 1.0)
        Ratio = 1.0;
    }
    hru_SunAct[hh] = Ratio*SunMax[hh];

    switch(variation) {
      case VARIATION_ORG :
        QsiA[hh] = QsiAT;
        QsiS[hh] = QsiST;
        QsiD[hh] = QsiDT;
        break;

      case VARIATION_1 :
        QsiA_Var[hh] = QsiAT;
        QsiS_Var[hh] = QsiST;
        QsiD_Var[hh] = QsiDT;
    } // switch
  } // for
}