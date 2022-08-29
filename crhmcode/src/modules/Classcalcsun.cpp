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

#include "Classcalcsun.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

Classcalcsun* Classcalcsun::klone(string name) const{
  return new Classcalcsun(name);
}

void Classcalcsun::decl(void) {

  Description = "'Calculates sunshine hours to replace field data', \
                 'Use actual sunshine hours or estimate from Qsi(W/m^2) when sunshine hours not available', \
                 'Use input Qsi (W/m^2) to estimate sunshine hours,' \
                 'Use input daily short-wave radiation observation(QsiD_Obs (W/m^2)), ' \
                 'Use input daily short-wave radiation variable (QsiD_Var (W/m^2)).'";

  variation_set = VARIATION_0;

  declreadobs("SunAct", TDim::NHRU, "sunshine hours", "(h)", &SunAct, HRU_OBS_Q, true); // must check for NULL


  variation_set = VARIATION_0 + VARIATION_1;

  declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q, true); // must check for NULL

  declobsfunc("Qsi", "Qsitot", &Qsitot, TFun::DTOT, NULL, true); // must check for NULL

  variation_set = VARIATION_2;

  declreadobs("QsiD_Obs", TDim::NHRU, "daily short-wave", "(W/m^2)", &QsiD_Obs, HRU_OBS_Q);


  variation_set = VARIATION_3;

  declgetvar("*", "QsiD_Var", "(W/m^2)", &QsiD_Var);


  variation_set = VARIATION_ORG;

  declgetvar("*", "QdflatD", "(MJ/m^2*d)", &QdflatD);
  declgetvar("*", "QdfoD",   "(MJ/m^2*d)", &QdfoD);
  declgetvar("*", "SunMax",  "(h)", &SunMax);

  declvar("hru_SunAct", TDim::NHRU, "Actual Sunshine", "(h)", &hru_SunAct);
}

void Classcalcsun::init(void) {
  nhru = getdim(TDim::NHRU);

      switch(variation) {

      case VARIATION_ORG:
        if(SunAct == NULL){
          CRHMException TExcept(string("'" + Name + " (calcsun)' sunshine hours observation missing. Using Qsi instead.").c_str(), TExcept::WARNING);
          LogError(TExcept);

          if(Qsi == NULL || Qsitot == NULL){
            CRHMException TExcept(string("'" + Name + " (calcsun)' Qsi interval observation missing.").c_str(), TExcept::TERMINATE);
            LogError(TExcept);
          }
        }
      break;

      case VARIATION_1:
        if(Qsi == NULL || Qsitot == NULL) {
          CRHMException TExcept(string("'" + Name + " (calcsun)' Qsi interval observation missing.").c_str(), TExcept::TERMINATE);
          LogError(TExcept);
        }
      break;

      case VARIATION_2:
        if(QsiD_Obs == NULL) {
          CRHMException TExcept(string("'" + Name + " (calcsun)' QsiD_Obs daily observation missing.").c_str(), TExcept::TERMINATE);
          LogError(TExcept);
        }
  } // switch
}

void Classcalcsun::run(void) {
double Temp = -9999;
double Ratio;

  long nstep = getstep() % Global::Freq;

  if(nstep == 1 || Global::Freq == 1) { // beginning of every day

    for (hh = 0; chkStruct(); ++hh) {

      switch(variation) {

      case VARIATION_ORG:
        if(SunAct){
          hru_SunAct[hh] = SunAct[hh];
          Temp = -9999;
          break;
        }
// fall through
      case VARIATION_1:
        Temp =  Qsitot[hh]*WtoMJ_D/Global::Freq - QdfoD[hh]; // observed direct incoming  - QdfoD[hh]
        break;

      case VARIATION_2:
        Temp =  QsiD_Obs[hh]*WtoMJ_D - QdfoD[hh]; // observed daily direct incoming  - QdfoD[hh]
        break;

      case VARIATION_3:
        Temp =  QsiD_Var[hh]*WtoMJ_D - QdfoD[hh]; // variable daily direct incoming  - QdfoD[hh]
        break;

      default :
        CRHMException TExcept(string("'" + Name + " (variation)' 'variation not defined.").c_str(), TExcept::TERMINATE);
        LogError(TExcept);
      } // switch

      if(Temp != -9999){
        if(Temp <= 0.0 || QdflatD[hh] - QdfoD[hh] <= 0.0)
          Ratio = 0.0;
        else{
          Ratio = Temp/(QdflatD[hh] - QdfoD[hh]); // incoming clear sky direct only
          if(Ratio > 1.0)
            Ratio = 1.0;
        }
        hru_SunAct[hh] = Ratio*SunMax[hh];
      }
    } // for
  } // beginning of every day
}
