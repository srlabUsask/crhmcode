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

#include "ClassObstoPar.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassObstoPar* ClassObstoPar::klone(string name) const{
  return new ClassObstoPar(name);
}

void ClassObstoPar::decl(void) {

  Description = "'Every interval sets the parameter specified in parameter \"par_name\"to the value of the observation specified in parameter \"obs_name\".'";

  obs_name = declparam("obs_name", TDim::BASIN, "default_obs", "observation name", obs_name);

  par_name = declparam("par_name", TDim::BASIN, "default_par", "parameter name", par_name);

  if (par_name)
  {
      declputparam("*", (par_name->at(0)).c_str(), "(m)", &Ht);
  }

  if (obs_name)
  {
      declreadobs((obs_name->at(0)).c_str(), TDim::NHRU, "height observation", "(m)", &Ht_obs);
  }

  decldiag("Ht_var", TDim::NHRU, "variable name", "()", &Ht_var);
}

void ClassObstoPar::init(void) {
  nhru = getdim(TDim::NHRU);

  if(Ht_obs == NULL){
    CRHMException TExcept("\"Ht_obs\". No observation vegetation height data!  Using constant parameter value instead.", TExcept::WARNING);
    LogError(TExcept);
  }

  for (hh = 0; hh < nhru; ++hh){
    Ht_var[hh] = Ht[hh];
  }
}

void ClassObstoPar::run(void) {
  if(Ht_obs != NULL)
    for(hh = 0; chkStruct(); ++hh){
      double H = Ht_obs[hh];
      if(H < 0.001)
        H = 0.001;
//      const_cast<double *> (Ht) [hh] = H;
      Ht[hh] = H;
      Ht_var[hh] = Ht[hh];
    }
}

void ClassObstoPar::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {

    string s = "'" + Name + " (Ht_obs)' ";
    LogMessage(hh, s.c_str());
    LogDebug(" ");
  }
}
