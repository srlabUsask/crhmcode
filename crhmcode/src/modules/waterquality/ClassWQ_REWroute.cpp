//created by Peter Lawford

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassWQ_REWroute.h"
//#include "../core/GlobalDll.h"
//#include "../core/ClassCRHM.h"
//#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassWQ_REWroute* ClassWQ_REWroute::klone(string name) const{
  return new ClassWQ_REWroute(name);
}

void ClassWQ_REWroute::decl(void) {

  Description = "'Handles the routing of surface and subsurface runoff from RBs (representative basins).' \
                    'uses Muskingum,' \
                    'uses Clark.'";

  variation_set = VARIATION_ORG;


  inflowCnt = declgrpvar("WS_ALL_inflow", "basinflow", "query variable = 'basinflow'", "(m^3/int)", &rew, &inflow_All);
  inflowConcCnt = declgrpvar("WS_ALL_inflow_mWQ", "basinflow_mWQ", "query variable = 'basinflow_mWQ'", "(kg/int)", &rew_mWQ, &inflow_mWQ_All);

  declvar("WS_inflow", TDim::NHRU, "inflow from each RB", "(m^3/int)", &inflow);
  declvar("WS_inflow_mWQ", TDim::NDEFN, "Concentration: inflow from each RB", "(kg/int)", &inflow_mWQ, &inflow_mWQ_lay, numsubstances);

  declstatdiag("cum_WSinflow", TDim::NHRU, "cumulative inflow from each RB", "(m^3)", &cuminflow);

  declvar("WS_outflow", TDim::NHRU, "outflow of each RB", "(m^3/int)", &outflow);
  declvar("WS_outflow_mWQ", TDim::NDEFN, "Concentration: outflow of each RB", "(kg/int)", &outflow_mWQ, &outflow_mWQ_lay, numsubstances);
  declstatdiag("cum_WSoutflow", TDim::NHRU, "cumulative outflow of each RB", "(m^3)", &cumoutflow);

  declvar("WS_flow", TDim::BASIN, "watershed surface and sub-surface outflow", "(m^3/int)", &flow);
  declvar("WS_flow_s", TDim::BASIN, "watershed surface and sub-surface outflow", "(m^3/s)", &flow_s);
  declstatdiag("cum_WSflow", TDim::BASIN, "cumulative watershed surface and sub-surface outflow", "(m^3)", &cumflow);


  gwCnt = declgrpvar("WS_ALL_gwflow", "basingw", "query variable = 'basingw'", "(m^3/int)", &gwrew, &gw_All);

  declvar("WS_gwinflow", TDim::NHRU, "gwinflow from each RB", "(m^3/int)", &gwinflow);
  declstatdiag("cum_WSgwinflow", TDim::NHRU, "cumulative gwinflow from each RB", "(m^3)", &cumgwinflow);

  declvar("WS_gwoutflow", TDim::NHRU, "gwoutflow of each RB", "(m^3/int)", &gwoutflow);
  declstatdiag("cum_WSgwoutflow", TDim::NHRU, "cumulative gwoutflow of each RB", "(m^3)", &cumgwoutflow);

  declvar("WS_gwflow", TDim::BASIN, "watershed ground water outflow", "(m^3/int)", &gwflow);
  declvar("WS_gwflow_s", TDim::BASIN, "watershed ground water outflow", "(m^3/s)", &gwflow_s);
  declstatdiag("cum_WSgwflow", TDim::BASIN, "cumulative watershed ground water outflow", "(m^3)", &cumgwflow);


  declparam("WS_Lag", TDim::NHRU, "[0.0]", "0.0","1.0E4.0", "inflow lag delay", "(h)", &WS_Lag);

  declparam("WS_gwLag", TDim::NHRU, "[0.0]", "0.0","1.0E4.0", "gwinflow lag delay", "(h)", &WS_gwLag);

  declparam("WS_whereto", TDim::NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", &WS_whereto);

  declparam("WS_order", TDim::NHRU, "1,2,3,4,5!", "1","1000", "RB outflow routing process order", "()", &WS_order);

  declparam("WS_gwwhereto", TDim::NHRU, "[0]", "0", "1000", "0 - watershed gwoutflow, or RB input", "()", &WS_gwwhereto);

  declparam("WS_gworder", TDim::NHRU, "1,2,3,4,5!", "1","1000", "RB gwoutflow routing process order", "()", &WS_gworder);


  variation_set = VARIATION_0;

  decldiag("WS_Ktravel_var", TDim::NHRU, "inflow storage constant (Muskingum method)", "(d)", &WS_Ktravel_var);

  decldiag("WS_gwKtravel_var", TDim::NHRU, "gwinflow storage constant (Muskingum method)", "(d)", &WS_gwKtravel_var);


  declparam("WS_route_n", TDim::NHRU, "[0.025]", "0.016","0.2", "Manning roughness coefficient", "()", &WS_route_n);

  declparam("WS_route_R", TDim::NHRU, "[0.5]", "0.01","1.0E4", "hydraulic radius", "(m)", &WS_route_R);

  declparam("WS_route_S0", TDim::NHRU, "[1e-3]", "1e-6","1.0", "longitudinal channel slope", "()", &WS_route_S0);

  declparam("WS_route_L", TDim::NHRU, "[3.69]", "0.01","1.0E10", "routing length", "(m)", &WS_route_L);

  declparam("WS_Channel_shp", TDim::NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &WS_Channel_shp);

  declparam("WS_X_M", TDim::NHRU, "[0.25]", "0.0","0.5", "dimensionless weighting factor", "()", &WS_route_X_M);

  declparam("WS_gwX_M", TDim::NHRU, "[0.25]", "0.0","0.5", "dimensionless weighting factor", "()", &WS_gwroute_X_M);


  variation_set = VARIATION_1;

  declparam("WS_Kstorage", TDim::NHRU, "[0.0]", "0.0","200.0", "inflow storage constant for RB (Clark method)", "(d)", &WS_Kstorage);

  declparam("WS_gwKstorage", TDim::NHRU, "[0.0]", "0.0","200.0", "gwinflow storage constant for RB (Clark method)", "(d)", &WS_gwKstorage);


  variation_set = VARIATION_ORG;
}

void ClassWQ_REWroute::init(void) {

/* VALIDATION OF INPUT PARAMETERS */

  for (int i=0; i<nhru; i++) {

    if (WS_order[i] < 1) {
      CRHMException Except("Module REW route All WS_order parameters must be > 0." , TExcept::TERMINATE);
      LogError(Except);
      throw Except;
    }

    if (WS_gworder[i] < 1) {
      CRHMException Except("Module REW route All WS_gworder parameters must be > 0." , TExcept::TERMINATE);
      LogError(Except);
      throw Except;
    }

  }

/**************/

  if(nhru < inflowCnt) {
    CRHMException Except("Module REW route # of HRUs must be >= # of groups." , TExcept::TERMINATE);
    LogError(Except);
    throw Except;
  }

  if(WS_whereto[WS_order[nhru-1]-1] != 0) {
    CRHMException Except("In module REW route 'whereto' for last RB must be zero." , TExcept::TERMINATE);
    LogError(Except);
    throw Except;
  }

  if(WS_gwwhereto[WS_gworder[nhru-1]-1] != 0) {
    CRHMException Except("In module REW route 'gwwhereto' for last RB must be zero." , TExcept::TERMINATE);
    LogError(Except);
    throw Except;
  }

  if(variation == VARIATION_ORG){
    const double Vw[3] = {1.67, 1.44, 1.33}; // rectangular - 0/parabolic - 1/triangular - 2

    for(hh = 0; hh < nhru; ++hh){
      double Vavg = (1.0/WS_route_n[hh])*pow(WS_route_R[hh], 2.0f/3.0f)*pow(WS_route_S0[hh], 0.5f);

      WS_gwKtravel_var[hh] = WS_route_L[hh]/(Vw[WS_Channel_shp[hh]]*Vavg)/86400.0; // (d)
      WS_Ktravel_var[hh] = WS_route_L[hh]/(Vw[WS_Channel_shp[hh]]*Vavg)/86400.0; // (d)
    }

    inflowDelay = new ClassMuskingum(inflow, outflow, WS_Ktravel_var, WS_route_X_M, WS_Lag, nhru);
    gwDelay = new ClassMuskingum(gwinflow, gwoutflow, WS_gwKtravel_var, WS_gwroute_X_M, WS_gwLag, nhru);

    inflowDelay_mWQ = new ClassMuskingum * [numsubstances];
//    gwDelay_mWQ = new ClassMuskingum * [numsubstances];

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
      inflowDelay_mWQ[Sub] = new ClassMuskingum(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], WS_Ktravel_var, WS_route_X_M, WS_Lag, nhru);
//      gwDelay_mWQ[Sub] = new ClassMuskingum(gwinflow_mWQ_lay[Sub], gwoutflow_mWQ_lay[Sub], WS_gwKtravel_var, WS_gwroute_X_M, WS_gwLag, nhru);
    }

    for(hh = 0; hh < nhru; ++hh){
      if(WS_gwKtravel_var[hh] >= (Global::Interval/(2.0*WS_gwroute_X_M[hh]))){
        string S = string("'" + Name + " (WQ_REW_route) GW Muskingum coefficient negative in HRU ").c_str();
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
      }

      if(gwDelay->c0[hh] < 0.0){
        gwDelay->c0[hh] = 0.0;
        gwDelay->c1[hh] = 1.0;
        gwDelay->c2[hh] = 0.0;
      }

      if(WS_Ktravel_var[hh] >= (Global::Interval/(2.0*WS_route_X_M[hh]))){
        string S = string("'" + Name + " (WQ_REW_route) inflow Muskingum coefficient negative in HRU ").c_str();
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
      }

      if(WS_Ktravel_var[hh] < (Global::Interval/(2.0*(1.0-WS_route_X_M[hh])))){ //inflowDelay->c0[hh] < 0.0
        inflowDelay->c0[hh] = 0.0;
        inflowDelay->c1[hh] = 1.0;
        inflowDelay->c2[hh] = 0.0;
      }
    }
  }
  else if(variation == VARIATION_1){
    Clark_inflowDelay = new ClassClark(inflow, outflow, WS_Kstorage, WS_Lag, nhru);
    Clark_gwDelay = new ClassClark(gwinflow, gwoutflow, WS_gwKstorage, WS_gwLag, nhru);

    Clark_inflowDelay_mWQ = new ClassClark * [numsubstances];
  //  Clark_gwDelay_mWQ = new ClassClark * [numsubstances];

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
      Clark_inflowDelay_mWQ[Sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], WS_Kstorage, WS_Lag, nhru);
//      Clark_gwDelay_mWQ[sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], WS_gwKstorage, WS_gwLag, nhru);
    }
  }

  flow[0] = 0.0;
  flow_s[0] = 0.0;
  cumflow[0] = 0.0;

  gwflow[0] = 0.0;
  gwflow_s[0] = 0.0;
  cumgwflow[0] = 0.0;

  for(hh = 0; hh < nhru; ++hh) {
    Reset_WQ(hh, inflow, inflow_mWQ_lay);
    Reset_WQ(hh, outflow, outflow_mWQ_lay);

    cuminflow[hh] = 0.0;
    cumoutflow[hh] = 0.0;
    gwinflow[hh] = 0.0;
    cumgwinflow[hh] = 0.0;
    gwoutflow[hh] = 0.0;
    cumgwoutflow[hh] = 0.0;
  }
}

void ClassWQ_REWroute::run(void) {

  flow[0] = 0.0;
  gwflow[0] = 0.0;

  for(long jj = 0; jj < inflowCnt; ++jj) { // HRUs not in sequence

    int hh = WS_order[jj] - 1;

    if(rew[hh]) {
      inflow[hh] = inflow_All[hh][0]; // add this HRU runoff and subsurface flow
      for (long Sub = 0; Sub < numsubstances; ++Sub) {
        inflow_mWQ_lay[Sub][hh] = inflow_mWQ_All[hh][Sub]; // * inflow[hh];
      }
    } else {
      inflow[hh] = 0; // add this HRU runoff and subsurface flow
      for (long Sub = 0; Sub < numsubstances; ++Sub) {
        inflow_mWQ_lay[Sub][hh] = 0;
      }
    }

// Perform the tree-network routing at nodes
    for(long hhh = 0; chkStruct(hhh); ++hhh) {
      if(WS_whereto[hhh]-1 == hh && outflow[hhh] > 0.0) {
        if(outflow[hhh] > 0.0) {
          inflow[hh] += outflow[hhh];
          for (long Sub = 0; Sub < numsubstances; ++Sub) {
            inflow_mWQ_lay[Sub][hh] += outflow_mWQ_lay[Sub][hhh];
          }
        }
      }
    }

    cuminflow[hh] += inflow[hh];

  if(variation == VARIATION_ORG) {
    inflowDelay->DoMuskingum(hh); // need to update for later HRUs

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
      inflowDelay_mWQ[Sub]->DoMuskingum(hh);
    }
  } else {
    Clark_inflowDelay->DoClark(hh); // need to update for later HRUs

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
      Clark_inflowDelay_mWQ[Sub]->DoClark(hh);
    }
  }

  cumoutflow[hh] += outflow[hh];

  if(WS_whereto[hh] == 0) {
    flow[0] += outflow[hh]; // (already m^3)
    flow_s[0] = flow[0]*Global::Freq/86400.0;
  }
} //end for

  for(long jj = 0; jj < gwCnt; ++jj) { // HRUs not in sequence

    int hh = WS_gworder[jj] - 1;

    if(gwrew[hh])
      gwinflow[hh] = gw_All[hh][0]; // add this HRU runoff and subsurface flow
    else
      gwinflow[hh] = 0; // add this HRU runoff and subsurface flow

    for(long hhh = 0; chkStruct(hhh); ++hhh) {
      if(WS_gwwhereto[hhh]-1 == hh && gwoutflow[hhh] > 0.0){
        if(gwoutflow[hhh] > 0.0)
          gwinflow[hh] += gwoutflow[hhh];
      }
    }

    cumgwinflow[hh] += gwinflow[hh];

    if(variation == VARIATION_ORG)
      gwDelay->DoMuskingum(hh); // need to update for later HRUs
    else
      Clark_gwDelay->DoClark(hh); // need to update for later HRUs

// Apply sediment processes if necessary
    


    cumgwoutflow[hh] += gwoutflow[hh];

    if(WS_gwwhereto[hh] == 0) {
      gwflow[0] += gwoutflow[hh]; // (already m^3)
      gwflow_s[0] = gwflow[0]*Global::Freq/86400.0;
    }
  } //end for

  cumflow[0] += flow[0];
  cumgwflow[0] += gwflow[0];
}

void ClassWQ_REWroute::finish(bool good) {
  for(hh = 0; hh < inflowCnt; ++hh) {
    LogMessageA(hh, string("'" + Name + " (REW_route)' cuminflow          (m^3) (m^3): ").c_str(), cuminflow[hh], 1.0);
    LogMessageA(hh, string("'" + Name + " (REW_route)' cumoutflow         (m^3) (m^3): ").c_str(), cumoutflow[hh], 1.0);
    if(variation == VARIATION_ORG)
      LogMessageA(hh, string("'" + Name + " (REW_route)' inflowDelay_in_storage (m^3) (m^3): ").c_str(), inflowDelay->Left(hh), 1.0);
    else
      LogMessageA(hh, string("'" + Name + " (REW_route)' Clark_inflowDelay_in_storage (m^3) (m^3): ").c_str(), Clark_inflowDelay->Left(hh), 1.0);

    LogMessageA(hh, string("'" + Name + " (REW_route)' cumgwinflow  (m^3) (m^3): ").c_str(), cumgwinflow[hh], 1.0);
    LogMessageA(hh, string("'" + Name + " (REW_route)' cumgwoutflow (m^3) (m^3): ").c_str(), cumgwoutflow[hh], 1.0);
    if(variation == VARIATION_ORG)
      LogMessageA(hh, string("'" + Name + " (REW_route)' gwDelay_in_storage (m^3) (m^3): ").c_str(), gwDelay->Left(hh), 1.0);
    else
      LogMessageA(hh, string("'" + Name + " (REW_route)' Clark_gwDelay_in_storage (m^3) (m^3): ").c_str(), Clark_gwDelay->Left(hh), 1.0);

    LogDebug(" ");
  }

  LogMessage(string("'" + Name + " (REW_route)' cumflow (m^3): ").c_str(), cumflow[0]);
  LogMessage(string("'" + Name + " (REW_route)' cumgwflow (m^3): ").c_str(), cumgwflow[0]);
  LogDebug(" ");

  if(variation == VARIATION_ORG){
    delete inflowDelay;
    delete gwDelay;
  }
  else{
    delete Clark_inflowDelay;
    delete Clark_gwDelay;
  }
}


void ClassWQ_REWroute::Reset_WQ(long hru, double* var, double** var_WQ_lay) {
    var[hru] = 0.0;
    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        var_WQ_lay[Sub][hru] = 0.0;
    }
}
