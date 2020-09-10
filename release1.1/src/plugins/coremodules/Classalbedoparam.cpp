//created by Manishankar Mondal

#include "Classalbedoparam.h"
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

Classalbedoparam* Classalbedoparam::klone(string name) const{
  return new Classalbedoparam(name);
}

void Classalbedoparam::decl(void) {

  Description = "'Initialises the variable \"Albedo\" from the parameter \"Albedo_Value\".'";

  declvar("Albedo", NHRU, "Albedo", "()", &Albedo);

  declparam("Albedo_Value", NHRU, "[0.17]", "0.0", "1.0","Albedo", "()", &Albedo_Value);

}

void Classalbedoparam::init(void) {
  nhru = getdim(NHRU);

  for (hh = 0; hh < nhru; ++hh){
    Albedo[hh] = Albedo_Value[hh];
  }
}

void Classalbedoparam::run(void) {
}