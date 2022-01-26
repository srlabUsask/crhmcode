//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassMod_Exec.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassMod_Exec* ClassMod_Exec::klone(string name) const{
  return new ClassMod_Exec(name);
}

void ClassMod_Exec::decl(void) {

  Description = "'Link variables and parameters to routines in external DLL.'";

  declvar("statusInit", TDim::ONE, "status of variables", "()", &statusInit);

  declvar("statusStep", TDim::ONE, "status of time step", "()", &statusStep);

  declvar("Dummy", TDim::NHRU, "non constant", "()", &Dummy);

  declvar("Dummy2", TDim::NHRU, "constant", "()", &Dummy2);

  DLL_name = declparam("DLL_name", TDim::ONE, " ", "DLL name, e.g. 'C:/Jose/Borland/Jose1.dll' ", DLL_name);

  trk_Vars = decldiagparam("trk_Vars", TDim::TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop.",  trk_Vars);

  chg_Pars = decldiagparam("chg_Pars", TDim::TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop.",  chg_Pars);

  decldiagparam("Borland_Dll", TDim::ONE, "1", "0", "1", "Borland_Dll requires an underscore before routine name", "()", &Borland_Dll);

}

void ClassMod_Exec::init(void) {

  Vars_Cnt = 0;
  Pars_Cnt = 0;

  string S;

  nhru = getdim(TDim::NHRU);

  ClassVar *newVar;
  ClassPar *newPar;

  S_Vars = "";
  S_Pars = "";

  VarArray = NULL;
  ParArray = NULL;

  bool Root = false;

  if (this->GroupCnt)
  {
      Root = true;
  }

  long  GetUnit;

  if(trk_Vars->size())
  {
    VarArray = new double * [trk_Vars->size()];

    for(size_t ii = 0; ii < trk_Vars->size(); ii++)
    {
      S = Common::trim(trk_Vars->at(ii));

      if (S.length() == 0)
      {
          break;
      }

      GetUnit = FindWildVarFloat(S.c_str(), newVar); // name changed 08/16/16 needs checked
      VarArray[ii] = newVar->values;
      S_Vars += (newVar->name  + " ").c_str();
      ++Vars_Cnt;
    }
  }

  if(chg_Pars->size())
  {
    ParArray = new double *[chg_Pars->size()];

    for(size_t ii = 0; ii < chg_Pars->size(); ++ii)
    {
      S = Common::trim(chg_Pars->at(ii));
      if(S.length() == 0)
        break;

      GetUnit = FindWildParFloat(S.c_str(), newPar, false, Root); // name
      ParArray[ii] = newPar->values;
      S_Pars += (newPar->param  + " ").c_str();
      ++Pars_Cnt;
    }

  }


  //Manishankar did this because this is commented as well in the previous NewModules.cpp file. Need to look at this maybe.

  //DLL = LoadLibrary(DLL_name->Strings[0].c_str()); // Borland  or gcc "C:/Jose/CodeBlocks_Jose/Jose_dll/bin/debug/Jose_Dll.dll

  //if (!DLL) {
  //  CRHMException TExcept((String("Could not open DLL file: ") + DLL_name->Strings[0]).c_str(), TERMINATE);
  //  LogError(TExcept);
  //}

  string Routine1 = "CRHM_Init";
  string Routine2 = "CRHM_Step";
  if(Borland_Dll[0]){
    Routine1 = "_" + Routine1;
    Routine2 = "_" + Routine2;
  }

  //Manishankar did this because this is commented as well in the previous NewModules.cpp file. Need to look at this maybe.

//// Get the address of the function.
//  LoadUserInit = (LoadModuleTypeInit *) GetProcAddress(DLL, Routine1.c_str());
//
//// Make sure we have the address then call the function.
//  if(!LoadUserInit) {
//    Imodules = FreeLibrary(DLL);
//    while(Imodules)
//      Imodules = FreeLibrary(DLL);
//
//    CRHMException TExcept((String("Could not open DLL file entry point: ") + Routine1).c_str(), TERMINATE);
//    LogError(TExcept);
//  }
//
//// Get the address of the function.
//  LoadUserStep = (LoadModuleTypeStep *) GetProcAddress(DLL, Routine2.c_str());
//
//// Make sure we have the address then call the function.
//  if(!LoadUserStep) {
//    Imodules = FreeLibrary(DLL);
//    while(Imodules)
//      Imodules = FreeLibrary(DLL);
//
//    CRHMException TExcept((String("Could not open DLL file entry point: ") + Routine2).c_str(), TERMINATE);
//    LogError(TExcept);
//  }
}

void ClassMod_Exec::run(void) {

if(getstep() == 1){
  statusInit[0] = LoadUserInit(this->Name.c_str(), this->GroupCnt, nhru, S_Vars.c_str(), Vars_Cnt, VarArray, S_Pars.c_str(), Pars_Cnt, ParArray);
}

double Fix = Global:: DTnow;
  statusStep[0] = LoadUserStep(Fix);
}

void ClassMod_Exec::finish(bool good) {

  statusStep[0] = LoadUserStep(0.0);

  //Manishankar did this because this is commented as well in the previous NewModules.cpp file. Need to look at this maybe.

  //if (DLL) {
  //  Imodules = FreeLibrary(DLL);
  //  while(Imodules)
  //    Imodules = FreeLibrary(DLL);
  //}

  delete[] VarArray;

  delete[] ParArray;
}
