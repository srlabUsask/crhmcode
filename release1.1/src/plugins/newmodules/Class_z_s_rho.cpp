//created by Manishankar Mondal

#include "Class_z_s_rho.h"
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

Class_z_s_rho* Class_z_s_rho::klone(string name) const{
  return new Class_z_s_rho(name);
}

void Class_z_s_rho::decl(void) {

  Description = "'Required when pbsmSnobal used with glacier and glacier_org. Replaces z_s and rho normally supplied by module SnobalCRHM to pbsmSnobal.'";

  declstatvar("z_s", NHRU, "total snowcover thickness", "(m)", &z_s);

  declstatvar("rho", NHRU, "average snowcover density", "(kg/m^3)", &rho);

  declgetvar("*", "SWE", "(mm)",        &SWE);

}

void Class_z_s_rho::init(void) {

  nhru = getdim(NHRU);

  for (hh = 0; chkStruct(); ++hh){
    z_s[hh] = 0.0;
    rho[hh] = 218.0; // 10/18/16
  }
}

void Class_z_s_rho::run(void) {

  float SWE_Max;

  for (hh = 0; chkStruct(); ++hh){
    z_s[hh] = Common::DepthofSnow(SWE[hh]); // returns zero if SWE <= 2.05 mm
    if(z_s[hh] > 0.0)
      rho[hh] = SWE[hh]/z_s[hh];
    else
      rho[hh] = 218.0; // 10/18/16
  }
}