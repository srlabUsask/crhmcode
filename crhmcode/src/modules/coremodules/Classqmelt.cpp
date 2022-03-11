//created by Manishankar Mondal

#include "Classqmelt.h"

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

Classqmelt* Classqmelt::klone(string name) const{
  return new Classqmelt(name);
}

void Classqmelt::decl(void) {

  Description = "'Generates the drift and ground melt from hummock-covered hillslopes in the Arctic tundra. Original version but now CRHM compatible.' \
                 'using using observations \"ta\" (changed from t to avoid conflict with obs module) and \"ts\". '";

  Global::OBS_AS_IS = 1; // ClassModule uses only intvl for NFREQ observation reads

  declvar("Qm", TDim::NHRU, "degree day/daily mean air temperature/partitioned", "(MJ/m^2*int)", &Qm);

  declvar("Qg", TDim::NHRU, "degree day/daily mean skin temperature/partitioned", "(MJ/m^2*int)", &Qg);

  declvar("cum_Qm", TDim::NHRU, "cumulative melt flux from degree day/daily mean air temperature/partitioned", "(MJ/m^2)", &cum_Qm);

  declvar("cum_Qg", TDim::NHRU, "cumulative ground flux from degree day/daily mean skin temperature/partitioned", "(MJ/m^2)", &cum_Qg);

  decllocal("QmD", TDim::NHRU, "daily melt from degree day/daily mean air temperature", "(MJ/m^2)", &QmD);

  decllocal("QgD", TDim::NHRU, "daily ground flux from degree day/daily mean skin temperature", "(MJ/m^2)", &QgD);

  declparam("TIa0Mn", TDim::NHRU, "[0.0]", "-10", "10", "Qm: degree day/daily mean air temperature", "(" + string(DEGREE_CELSIUS) + ")", &TIa0Mn);

  declparam("TIa1Mn", TDim::NHRU, "[0.8844, 0.0]", "0", "10", "Qm: degree day/daily mean air temperature", "(MJ/d*"+string(DEGREE_CELSIUS)+")", &TIa1Mn);

  declparam("TIs0Mn", TDim::NHRU, "[0.0]", "-10", "10", "Qg: degree day/daily mean skin temperature", "(" + string(DEGREE_CELSIUS) + ")", &TIs0Mn);

  declparam("TIs1Mn", TDim::NHRU, "[0.0, 0.2]", "0", "10", "Qg: degree day/daily mean skin temperature", "(MJ/d*"+string(DEGREE_CELSIUS)+")", &TIs1Mn);


  declreadobs("ta", TDim::NOBS, "air temperature", "(" + string(DEGREE_CELSIUS) + ")", &t);

  declreadobs("ts", TDim::NOBS, "skin temperature", "(" + string(DEGREE_CELSIUS) + ")", &ts);


  declobsfunc("ta",  "Tmean", &tmean, TFun::AVG);
  declobsfunc("ts", "Tsmean", &tsmean, TFun::AVG);
  declobsfunc("ta",  "Tpos", &tpos, TFun::POS);
  declobsfunc("ts", "Tspos", &tspos, TFun::POS);
}

void Classqmelt::init(void) {

  nhru = getdim(TDim::NHRU);

  for(long hh = 0; hh < nhru; ++hh) {
    cum_Qg[hh] = 0.0;
    cum_Qm[hh] = 0.0;
    QmD[hh] = 0.0;
    QgD[hh] = 0.0;
  }
}

void Classqmelt::run(void) {

  bool start = getstep()%Global::Freq == 1;

  if(start) { // calculate daily regression

    for(hh = 0;  chkStruct(); ++hh) {
      if(tmean[0] - TIa0Mn[hh] > 0.0)
        QmD[hh] =  (tmean[0] - TIa0Mn[hh])*TIa1Mn[hh];   // mean air temperature degree day
      else
        QmD[hh] = 0.0;

      if(tsmean[0] - TIs0Mn[hh] > 0.0)
        QgD[hh] =  (tsmean[0] - TIs0Mn[hh])*TIs1Mn[hh];  // mean skin temperature degree day
      else
        QgD[hh] = 0.0;
    }
  }

  for(hh = 0;  chkStruct(); ++hh) {

    if(ts[0] > 0.0 && tsmean[0] > 0.0)
      Qg[hh] = QgD[hh]*ts[0]/tspos[0];  // distribute daily to interval
    else
      Qg[hh] = 0.0;

    cum_Qg[hh] += Qg[hh];

    if(t[0] > 0.0 && tmean[0] > 0.0)
      Qm[hh] = QmD[hh]*t[0]/tpos[0];  // distribute daily to interval
    else
      Qm[hh] = 0.0;

    cum_Qm[hh] += Qm[hh];
  }
}