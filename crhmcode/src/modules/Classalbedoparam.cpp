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
