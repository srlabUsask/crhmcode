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

#include "ClassHtobs.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassHtobs* ClassHtobs::klone(string name) const{
  return new ClassHtobs(name);
}

void ClassHtobs::decl(void) {

  Description = "'Every interval sets the variable \"Ht_var\" to the value of the observation \"Ht_obs\".'";

  declvar("Ht_var", TDim::NHRU, "vegetation height", "(m)", &Ht_var);

  declputparam("*", "Ht", "(m)", &Ht);


  declreadobs("Ht_obs", TDim::NHRU, "height observation", "(m)", &Ht_obs, HRU_OBS_misc, true);

}

void ClassHtobs::init(void) {
  nhru = getdim(TDim::NHRU);

  if(Ht_obs == NULL){
    CRHMException TExcept("\"Ht_obs\". No observation vegetation height data!  Using constant parameter value instead.", TExcept::WARNING);
    LogError(TExcept);
  }

  for (hh = 0; hh < nhru; ++hh){
    Ht_var[hh] = Ht[hh];
  }
}

void ClassHtobs::run(void) {
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
