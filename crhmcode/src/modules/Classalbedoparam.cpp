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

#include "Classalbedoparam.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

Classalbedoparam* Classalbedoparam::klone(string name) const{
  return new Classalbedoparam(name);
}

void Classalbedoparam::decl(void) {

  Description = "'Initialises the variable \"Albedo\" from the parameter \"Albedo_Value\".'";

  declvar("Albedo", TDim::NHRU, "Albedo", "()", &Albedo);

  declparam("Albedo_Value", TDim::NHRU, "[0.17]", "0.0", "1.0","Albedo", "()", &Albedo_Value);

}

void Classalbedoparam::init(void) {
  nhru = getdim(TDim::NHRU);

  for (hh = 0; hh < nhru; ++hh){
    Albedo[hh] = Albedo_Value[hh];
  }
}

void Classalbedoparam::run(void) {
}
