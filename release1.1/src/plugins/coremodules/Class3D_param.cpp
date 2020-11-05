//created by Manishankar Mondal

#include "Class3D_param.h"
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

Class3D_param* Class3D_param::klone(string name) const{
  return new Class3D_param(name);
}

void Class3D_param::decl(void) {

  Description = "'Initialises the variable \"Param_3D\" from the parameter \"Var_3D\".'";

  declvar("Var_3D", TDim::NHRU, "Var_3D", "()", &Var_3D);

  declparam("Param_3D", TDim::NHRU, "[0.17]", "0.0", "1.0","Param_3D", "()", &Param_3D);

}

void Class3D_param::init(void) {
  nhru = getdim(TDim::NHRU);

  for (hh = 0; hh < nhru; ++hh){
    Var_3D[hh] = Param_3D[hh];
  }
}

void Class3D_param::run(void) {
}

void Class3D_param::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {

    string s = "'" + Name + " (3D_param)' ";
    LogMessage(hh, s.c_str());
  }
  LogDebug(" ");
}