//created by Manishankar Mondal

#include "Classalbedoobs.h"
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


Classalbedoobs* Classalbedoobs::klone(string name) const{
  return new Classalbedoobs(name);
}

void Classalbedoobs::decl(void) {

  Description = "'Every interval sets the variable \"Albedo\" to the value of the observation \"Albedo_obs\".'";

  declvar("Albedo", NHRU, "Albedo", "()", &Albedo);

  decldiagparam("Albedo_Value", NHRU, "[0.17]", "0.0", "1.0","Albedo", "()", &Albedo_Value);

  declreadobs("Albedo_obs", NHRU, "albedo observation", "()", &Albedo_obs, HRU_OBS_Q, true);

}

void Classalbedoobs::init(void) {
  nhru = getdim(NHRU);

  for (hh = 0; hh < nhru; ++hh){
    Albedo[hh] = Albedo_Value[hh];
  }

  if(Albedo_obs == NULL){
    CRHMException TExcept("\"albedo_obs\". No observation albedo data!  Using constant parameter value instead.", WARNING);
    LogError(TExcept);
  }
}

void Classalbedoobs::run(void) {
  if(Albedo_obs != NULL)
    for(hh = 0; chkStruct(); ++hh)
      Albedo[hh] = Albedo_obs[hh];
}