//created by Manishankar Mondal

#include "ClassHtobs.h"
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