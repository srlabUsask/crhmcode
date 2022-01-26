//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassTestSparse.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassTestSparse* ClassTestSparse::klone(string name) const{
  return new ClassTestSparse(name);
}

  void ClassTestSparse::decl(void) {

  Description = "'TestSparse.'";


  declvar("Fert_N_Var", TDim::NHRU, "current hru N fertilizer amount", "(kg/km^2)", &Fert_N_Var);

  declvar("Fert_P_Var", TDim::NHRU, "current hru P fertilizer amount", "(kg/km^2)", &Fert_P_Var);

  declvar("Man_N_Var", TDim::NHRU, "current hru N manure amount", "(kg/km^2)", &Man_N_Var);

  declvar("Man_P_Var", TDim::NHRU, "current hru P manure amount", "(kg/km^2)", &Man_P_Var);

  declvar("Res_N_Var", TDim::NHRU, "current hru N residue amount", "(kg/km^2)", &Res_N_Var);

  declvar("Res_P_Var", TDim::NHRU, "current hru P residue amount", "(kg/km^2)", &Res_P_Var);

  declvar("Fert_period_Var", TDim::NHRU, "current period for spreading fertilizer and manure amount", "()", &Fert_period_Var);

  declvar("Litter_period_Var", TDim::NHRU, "current litter period for residue amount", "()", &Litter_period_Var);


  ObsCnt_N_up = declreadobs("Fert_N_up", TDim::NHRU, "annual N fertilizer dates and amount", "(kg/km^2)", &Fert_N_up, HRU_OBS_Q, true);

  ObsCnt_P_up = declreadobs("Fert_P_up", TDim::NHRU, "annual P fertilizer dates and amount", "(kg/km^2)", &Fert_P_up, HRU_OBS_Q, true);

  ObsCntMan_N_up = declreadobs("Man_N_up", TDim::NHRU, "annual N Manure dates and amount", "(kg/km^2)", &Man_N_up, HRU_OBS_Q, true);

  ObsCntMan_P_up = declreadobs("Man_P_up", TDim::NHRU, "annual P Manure dates and amount", "(kg/km^2)", &Man_P_up, HRU_OBS_Q, true);

  ObsCntRes_N_up = declreadobs("Res_N_up", TDim::NHRU, "annual N Residues dates and amount", "(kg/km^2)", &Res_N_up, HRU_OBS_Q, true);

  ObsCntRes_P_up = declreadobs("Res_P_up", TDim::NHRU, "annual P Residues dates and amount", "(kg/km^2)", &Res_P_up, HRU_OBS_Q, true);

  ObsCnt_N_down = declreadobs("Fert_N_up", TDim::NHRU, "annual N fertilizer dates and amount", "(kg/km^2)", &Fert_N_down, HRU_OBS_Q, true);

  ObsCnt_P_down = declreadobs("Fert_P_up", TDim::NHRU, "annual P fertilizer dates and amount", "(kg/km^2)", &Fert_P_down, HRU_OBS_Q, true);

  ObsCntMan_N_down = declreadobs("Man_N_up", TDim::NHRU, "annual N Manure dates and amount", "(kg/km^2)", &Man_N_down, HRU_OBS_Q, true);

  ObsCntMan_P_down = declreadobs("Man_P_up", TDim::NHRU, "annual P Manure dates and amount", "(kg/km^2)", &Man_P_down, HRU_OBS_Q, true);

  ObsCntRes_N_down = declreadobs("Res_N_up", TDim::NHRU, "annual N Residues dates and amount", "(kg/km^2)", &Res_N_down, HRU_OBS_Q, true);

  ObsCntRes_P_down = declreadobs("Res_P_up", TDim::NHRU, "annual P Residues dates and amount", "(kg/km^2)", &Res_P_down, HRU_OBS_Q, true);


  ObsCnt_fertperiod = declreadobs("Fert_period", TDim::NHRU, "spreading period for feritilzer and manure", "(d)", &Fert_period, HRU_OBS_Q, true);

  ObsCnt_litterperiod = declreadobs("Litter_period", TDim::NHRU, "Litterperiod for residue", "(d)", &Litter_period, HRU_OBS_Q, true);

}

void ClassTestSparse::init(void) {

  nhru = getdim(TDim::NHRU);

    if(ObsCnt_N_up > -1){
      CRHMException TExcept("Handling N fertilizer from (Fert_N_up) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    if(ObsCnt_P_up > -1){
      CRHMException TExcept("Handling P fertilizer from (Fert_P_up) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    if(ObsCntMan_N_up > -1){
      CRHMException TExcept("Handling N manure from (Man_N_up) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    if(ObsCntMan_P_up > -1){
      CRHMException TExcept("Handling P manure from (Man_P_up) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    if(ObsCntRes_N_up > -1){
      CRHMException TExcept("Handling N residues from (Res_N_up) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    if(ObsCntRes_P_up > -1){
      CRHMException TExcept("Handling P residues from (Res_P_up) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    if(ObsCnt_fertperiod > -1){
      CRHMException TExcept("Handling fertilizer and manure period (Fertperiod) observation.", TExcept::WARNING);
      LogError(TExcept);
    }

    for(hh = 0; hh < nhru; ++hh) {
       Fert_N_Var[hh] = 0.0;
       Fert_P_Var[hh] = 0.0;
       Man_N_Var[hh] = 0.0;
       Man_P_Var[hh] = 0.0;
       Res_N_Var[hh] = 0.0;
       Res_P_Var[hh] = 0.0;
       Fert_period_Var[hh] = 1;
       Litter_period_Var[hh] = 1;
    }

}

void ClassTestSparse::run(void) {

  long step = getstep();
  long nstep = step%Global::Freq;
  long today = julian("now");

  if(nstep == 1){ // beginning of every day
    for(hh = 0; chkStruct(); ++hh){
          if(ObsCnt_N_up >= hh)
            Fert_N_Var[hh] = Fert_N_up[hh];
          else
            Fert_N_Var[hh] = fLimit;

          if(ObsCnt_P_up >= hh)
            Fert_P_Var[hh] = Fert_P_up[hh];
          else
            Fert_P_Var[hh] = fLimit;

          if(ObsCntMan_N_up >= hh)
            Man_N_Var[hh] = Man_N_up[hh];
          else
            Man_N_Var[hh] = fLimit;

          if(ObsCntMan_P_up >= hh) // file open
            Man_P_Var[hh] = Man_P_up[hh];
          else
            Man_P_Var[hh] = fLimit;
          if(ObsCntRes_N_up >= hh)
            Res_N_Var[hh] = Res_N_up[hh];
          else
            Res_N_Var[hh] = fLimit;

          if(ObsCntRes_P_up >= hh) // file open
            Res_P_Var[hh] = Res_P_up[hh];
          else
            Res_P_Var[hh] = fLimit;

          if(ObsCnt_fertperiod > 0) // file open
            Fert_period_Var[hh] = Fert_period[hh];
          else
            Fert_period_Var[hh] = fLimit;

          if(ObsCnt_litterperiod > 0) // file open
            Litter_period_Var[hh] = Litter_period[hh];
          else
            Litter_period_Var[hh] = fLimit;
    } // for hh
  } // start of day
}

void ClassTestSparse::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
//    LogMessageA(hh, string("'" + Name + " (Grow_crops_annually)'  cumnetrain  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain[hh], hru_area[hh], basin_area[0]);
//    LogMessageA(hh, string("'" + Name + " (Grow_crops_annually)'  cumnetsnow  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_snow[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
  LogDebug(" ");
}
