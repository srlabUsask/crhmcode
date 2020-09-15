//created by Manishankar Mondal

#include "ClassObstoPar.h"
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

ClassObstoPar* ClassObstoPar::klone(string name) const{
  return new ClassObstoPar(name);
}

void ClassObstoPar::decl(void) {

  Description = "'Every interval sets the parameter specified in parameter \"par_name\"to the value of the observation specified in parameter \"obs_name\".'";

  obs_name = declparam("obs_name", BASIN, "default_obs", "observation name", obs_name);

  par_name = declparam("par_name", BASIN, "default_par", "parameter name", par_name);

  if(par_name)
    declputparam("*", (par_name->Strings[0]).c_str(), "(m)", &Ht);


  if(obs_name)
    declreadobs((obs_name->Strings[0]).c_str(), NHRU, "height observation", "(m)", &Ht_obs);

  decldiag("Ht_var", NHRU, "variable name", "()", &Ht_var);
}

void ClassObstoPar::init(void) {
  nhru = getdim(NHRU);

  if(Ht_obs == NULL){
    CRHMException TExcept("\"Ht_obs\". No observation vegetation height data!  Using constant parameter value instead.", WARNING);
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