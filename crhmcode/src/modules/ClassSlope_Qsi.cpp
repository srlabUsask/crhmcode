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

#include "ClassSlope_Qsi.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassSlope_Qsi* ClassSlope_Qsi::klone(string name) const{
  return new ClassSlope_Qsi(name);
}

void ClassSlope_Qsi::decl(void) {

  Description = "'Estimates interval short-wave on a slope from measured horizontal Qsi and theoretical values on the slope. Only needed if using observed Qsi otherwise this is handled withing the annandale module.',  \
                 ' Output as observations, QsiS (W/m^2) and QsiD_Obs (W/m^2),' \
                 ' Output as variables, QsiS_Var (W/m^2) and QsiD_Var (W/m^2).'";

  variation_set = VARIATION_ORG;

  declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

  declobsfunc("Qsi", "QsiD_Obs", &QsiD, TFun::AVG);

  declgetvar("*", "Qdro",   "(W/m^2)", &Qdro);
  declgetvar("*", "Qdfo",   "(W/m^2)", &Qdfo);
  declgetvar("*", "Qdflat", "(W/m^2)", &Qdflat);


  variation_set = VARIATION_0;

  declobs("QsiS", TDim::NHRU, "generated interval short-wave", "(W/m^2)", &QsiS);

  declobs("QsiD_Obs", TDim::NHRU, "average measured (Qsi) short-wave on horizontal", "(W/m^2)", &QsiD_Obs);


  variation_set = VARIATION_1;

  declvar("QsiS_Var", TDim::NHRU, "corrected short-wave on slope", "(W/m^2)", &QsiS_Var);

  declvar("QsiD_Var", TDim::NHRU, "average short-wave on horizontal", "(W/m^2)", &QsiD_Var);

  variation_set = VARIATION_ORG;
}

void ClassSlope_Qsi::init(void) {

  nhru = getdim(TDim::NHRU);
}

void ClassSlope_Qsi::run(void) {

  long nstep = getstep() % Global::Freq;

  for (hh = 0; chkStruct(); ++hh){
    double Short = Qdro[hh] + Qdfo[hh];
    double ShortC = 0.0;
    if(Qdflat[hh] > 1.0)
      ShortC = Qsi[hh]/Qdflat[hh]*Short;

    switch(variation) {
      case VARIATION_ORG:
        QsiS[hh] = ShortC;
        if(nstep == 1)
          QsiD_Obs[hh] = QsiD[hh]; // move mean from variable to declared observation
        break;
      case VARIATION_1:
        QsiS_Var[hh] = ShortC;
        if(nstep == 1)
          QsiD_Var[hh] = QsiD[hh]; // move mean from variable to declared observation
        break;
    } // switch

  }
}
