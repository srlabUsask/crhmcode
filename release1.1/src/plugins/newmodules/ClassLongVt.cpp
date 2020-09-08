//created by Manishankar Mondal

#include "ClassLongVt.h"
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

ClassLongVt* ClassLongVt::klone(string name) const{
  return new ClassLongVt(name);
}

 void ClassLongVt::decl(void) {

  Description = "'LongVt: Calculates incoming long-wave radiation variable (QliVt_Var) (Sicart et al., 2005) using terrain view factor.' \
                 'using input Qsi (W/m^2) to calculate daily average,' \
                 'using input observation QsiDObs (W/m^2) for daily average,' \
                 'using input variable QsiD_Var (W/m^2) from module Annandale for daily average,' \
                 'using input observation Qli (W/m^2) for daily average.'";

  variation_set = VARIATION_ORG;

  declvar("tau", NHRU, "Atmospheric transmissivity = S/Sextra", "()", &tau);

  declvar("Qli_Var", NHRU, "calculated incoming long", "(W/m^2)", &Qli_Var);

  declvar("QliVt_Var", NHRU, "calculated incoming long in open environment", "(W/m^2)", &QliVt_Var);



  declgetvar("*", "QdroDext", "(MJ/m^2*d)", &QdroDext);

  declgetvar("*",  "hru_t", "(°C)", &hru_t);

  declgetvar("*",  "hru_ea", "(kPa)", &hru_ea);

  declgetvar("*",  "hru_rh", "()", &hru_rh);


  declparam("Vt", NHRU, "[0.3]", "0.0", "1.0", "terrain view factor (equivalent to 1-Vf)", "()", &Vt);

  decldiagparam("epsilon_s", NHRU, "[0.98]", "0.0", "1.0", "terrain emissivity", "()", &epsilon_s);


  variation_set = VARIATION_0;

  declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

  declobsfunc("Qsi", "QsiDavg", &QsiDavg, AVG, NULL, true); // must check for NULL


  variation_set = VARIATION_1;

  declreadobs("QsiDObs", NHRU, "incident short-wave", "(W/m^2)", &QsiD, HRU_OBS_Q);


  variation_set = VARIATION_2;

  declgetvar("*",  "QsiD_Var", "(W/m^2)", &QsiD_Var);


  variation_set = VARIATION_3;

  declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);


  variation_set = VARIATION_0 + VARIATION_1 + VARIATION_2;

  declobs("Qli", NHRU, "incoming calculated long-wave", "(W/m^2)", &Qli_out);


  variation_set = VARIATION_ORG;

}

void ClassLongVt::init(void) {
  nhru = getdim(NHRU);

  if(variation == VARIATION_ORG){
      if(!QsiDavg){ // only exists if an actual file observation
        CRHMException TExcept(string("'" + Name + " (LongVt)' using Qsi observation to calculate tau. Qsi appears to be a declared obs instead of read from a file.").c_str(), TERMINATE);
        LogError(TExcept);
      }
      else{
        CRHMException TExcept(string("'" + Name + " (LongVt)' using Qsi observation to calculate tau.").c_str(), WARNING);
        LogError(TExcept);
      }
  }
  else if(variation == VARIATION_1){
      CRHMException TExcept(string("'" + Name + " (LongVt)' using QsiDObs observation to calculate tau.").c_str(), WARNING);
      LogError(TExcept);
  }
  else if(variation == VARIATION_2){
      CRHMException TExcept(string("'" + Name + " (LongVt)' using Qsi_Var variable to calculate tau.").c_str(), WARNING);
      LogError(TExcept);
  }
  else if(variation == VARIATION_3){
      CRHMException TExcept(string("'" + Name + " (LongVt)' using Qli observation to convert to QliVT_Var.").c_str(), WARNING);
      LogError(TExcept);
  }
}

void ClassLongVt::run(void) {

  long hhmax;
  long nstep = getstep() % Global::Freq;


  for (hh = 0; chkStruct(); ++hh) {
    if(nstep == 1 || Global::Freq == 1){ // beginning of every day
      if(QdroDext[hh] >= 0.001) {    // 04/21/14
        switch(variation){
          case VARIATION_ORG:
            tau[hh] =  QsiDavg[hh]*86400/1E6/QdroDext[hh]; // 03/29/07
            break;
          case VARIATION_1:
            tau[hh] =  QsiD[hh]*86400/1E6/QdroDext[hh]; // 03/29/07
            break;
          case VARIATION_2:
            tau[hh] =  QsiD_Var[hh]*86400/1E6/QdroDext[hh]; // 03/29/07
            break;
        }
      }
      else
       tau[hh] = 0.8;     // 04/21/14
    }

    if(variation != VARIATION_3)
      Qli_Var[hh] = 1.24f*pow((hru_ea[hh]*10.0f)/(hru_t[hh] + CRHM_constants::Tm), 1.0f/7.0f)*(1.0f + 0.44f*hru_rh[hh]/100.0f - 0.18f*tau[hh])*CRHM_constants::sbc*pow(hru_t[hh]+CRHM_constants::Tm, 4.0f);
    else
      Qli_Var[hh] = Qli[hh];

    QliVt_Var[hh] = (1.0f - Vt[hh])*Qli_Var[hh] + Vt[hh]*epsilon_s[hh]*CRHM_constants::sbc*pow(hru_t[hh] + CRHM_constants::Tm, 4.0f);

    if(variation != VARIATION_3)
      Qli_out[hh] = QliVt_Var[hh];
  }
}