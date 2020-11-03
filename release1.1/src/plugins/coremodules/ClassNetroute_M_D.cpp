//created by Manishankar Mondal

#include "ClassNetroute_M_D.h"
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

ClassNetroute_M_D* ClassNetroute_M_D::klone(string name) const{
  return new ClassNetroute_M_D(name);
}

double ClassNetroute_M_D::Function1(double *I, long hh) {
  return runDelay->ChangeLag(I, hh);
}

double ClassNetroute_M_D::Function2(double *X, long hh) {
  return runDelay->ChangeStorage(X, hh);
}

void ClassNetroute_M_D::decl(void) {

  Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route and Muskingum method for \"outflow\". Distributed flow.'";

  declvar("inflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

  declstatdiag("cuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

  declvar("outflow", NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

  declstatdiag("cumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

  decldiag("outflow_diverted", NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

  declstatdiag("cumoutflow_diverted", NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2/int)", &cumoutflow_diverted);

  declstatdiag("cum_to_Sd", NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

  declstatdiag("cum_to_soil_rechr", NHRU, "cumulative other HRU recycled tosoil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

  declvar("gwinflow", NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

  declstatdiag("gwcuminflow", NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

  declvar("gwoutflow", NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

  declstatdiag("gwcumoutflow", NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

  decldiag("gwoutflow_diverted", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

  declstatdiag("gwcumoutflow_diverted", NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted);

  declvar("ssrinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

  declstatdiag("ssrcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

  declvar("ssroutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &ssroutflow);

  declstatdiag("ssrcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &ssrcumoutflow);

  declstatdiag("HRU_cumbasinflow", NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

  declstatdiag("cum_preferential_flow_to_gw", NHRU, "cumulative other HRU's runoff to this HRU's gw via preferential flow path", "(mm)", &cum_preferential_flow_to_gw);

  declparam("preferential_flow", NHRU, "[0]", "0", "1","0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);

  declvar("runinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &runinflow);

  declstatdiag("runcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &runcuminflow);

  declvar("runoutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &runoutflow);

  declstatdiag("runcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &runcumoutflow);

  declstatdiag("cumscaling_boost", NHRU, "cumulative amout inflow boosted", "(mm*km^2)", &cumscaling_boost);

  declvar("basinflow", BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

  decldiag("basinflow_s", BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

  declstatdiag("cumbasinflow", BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

  declvar("basingw", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

  decldiag("basingw_s", BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

  declstatdiag("cumbasingw", BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

  decllocal("soil_ssr_Buf", NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

  decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

  decllocal("soil_gw_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_gw_Buf);

  decllocal("Ktravel", NHRU, "travel time", "(d)", &Ktravel);

  decllocal("distrib_sum", NHRU, "HRU distribution sum", "()", &distrib_sum);


  declparam("basin_area", BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

  declparam("Lag", NHRU, "[0.0]", "0.0","1.0E4.0", "lag delay", "(h)", &Lag);

  declparam("route_n", NHRU, "[0.025]", "0.016","0.2", "Manning roughness coefficient", "()", &route_n);

  declparam("route_R", NHRU, "[0.5]", "0.01","1.0E4", "hydraulic radius", "(m)", &route_R);

  declparam("route_S0", NHRU, "[1e-3]", "1e-6","1.0", "longitudinal channel slope", "()", &route_S0);

  declparam("route_L", NHRU, "[200.0]", "0.01","1.0E10", "routing length", "(m)", &route_L);

  declparam("route_X_M", NHRU, "[0.25]", "0.0","0.5", "dimensionless weighting factor", "()", &route_X_M);

  declparam("ssrKstorage", NHRU, "[0.0]", "0.0","200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

  declparam("ssrLag", NHRU, "[0.0]", "0.0","1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

  declparam("runKstorage", NHRU, "[0.0]", "0.0","200.0", "runoff storage constant", "(d)", &runKstorage);

  declparam("runLag", NHRU, "[0.0]", "0.0","1.0E4", "runoff lag delay", "(h)", &runLag);

  declparam("gwKstorage", NHRU, "[0.0]", "0.0","200.0", "gw storage constant", "(d)", &gwKstorage);

  declparam("gwLag", NHRU, "[0.0]", "0.0","1.0E4", "gw lag delay", "(h)", &gwLag);

  declparam("distrib_Route", NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs", "()", &distrib, &distrib_hru, nhru);

  declparam("distrib_Basin", NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_Route')", "()", &distrib_Basin);

  declparam("gwwhereto", NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

  declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0","Maximum depression storage", "(mm)", &Sdmax);

  declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

  decldiagparam("Sd_ByPass", NHRU, "[0]", "0", "1","0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

  decldiagparam("soil_rechr_ByPass", NHRU, "[1]", "0", "1","0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);

  declparam("Channel_shp", NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &route_Cshp);

  decldiagparam("scaling_factor", NHRU, "[1.0]", "0.0", "1.0E6","multiplies the input to Muskingum by this scaling factor.", "()", &scaling_factor); // temporary

  declparam("order", NHRU, "[1,2,3,4,5!]", "1","1000", "HRU routing process order", "()", &order);


  soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

  soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

  soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);


  declputvar("*", "Sd", "(mm)", &Sd);

  declputvar("*", "soil_moist", "(mm)", &soil_moist);

  declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

  declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

  declputvar("*", "gw", "(mm)", &gw);
}

void ClassNetroute_M_D::init(void) {

  nhru = getdim(NHRU);

  if(soil_ssrDiv > 1){
    string S = "Netroute_M_D:  \"soil_ssr\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  if(soil_runoffDiv > 1){
    string S = "Netroute_M_D:  \"soil_runoff\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  if(soil_gwDiv > 1){
    string S = "Netroute_M_D:  \"gw_flow\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  const double Vw[3] = {1.67, 1.44, 1.33}; // rectangular - 0/parabolic - 1/triangular - 2

  for(hh = 0; hh < nhru; ++hh){
    double Vavg = (1.0/route_n[hh])*pow(route_R[hh], 2.0/3.0)*pow(route_S0[hh], 0.5f); // (m/s)
    Ktravel[hh] = route_L[hh]/(Vw[route_Cshp[hh]]*Vavg)/86400.0; // (d)
  }

  hruDelay = new ClassMuskingum(inflow, outflow, Ktravel, route_X_M, Lag, nhru);
  ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
  runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
  gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

  for(hh = 0; hh < nhru; ++hh){
    if(Ktravel[hh] >= (Global::Interval/(2.0*route_X_M[hh]))){
      string S = string("'" + Name + " (Netroute_M_D) Muskingum coefficient negative in HRU ").c_str() + to_string(hh+1);
      CRHMException TExcept(S.c_str(), TExcept::WARNING);
      LogError(TExcept);
    }

    if(Ktravel[hh] < (Global::Interval/(2.0*(1.0-route_X_M[hh])))){ //    if(hruDelay->c0[hh] < 0.0)
      hruDelay->c0[hh] = 0.0;
      hruDelay->c1[hh] = 1.0;
      hruDelay->c2[hh] = 0.0;
    }
  }

  basinflow[0] = 0.0;
  basinflow_s[0] = 0.0;
  cumbasinflow[0] = 0.0;
  basingw[0] = 0.0;
  basingw_s[0] = 0.0;
  cumbasingw[0] = 0.0;

  for(hh = 0; hh < nhru; ++hh) {
    inflow[hh] = 0.0;
    cuminflow[hh] = 0.0;
    outflow[hh] = 0.0;
    outflow_diverted[hh] = 0.0;
    cumoutflow_diverted[hh] = 0.0;
    cumoutflow[hh] = 0.0;
    cumscaling_boost[hh] = 0.0;
    cum_to_Sd[hh] = 0.0;
    cum_to_soil_rechr[hh] = 0.0;
    cum_preferential_flow_to_gw[hh] = 0.0;

    gwinflow[hh] = 0.0;
    gwcuminflow[hh] = 0.0;
    gwcumoutflow[hh] = 0.0;
    gwcumoutflow_diverted[hh] = 0.0;
    HRU_cumbasinflow[hh] = 0.0;

    ssrinflow[hh] = 0.0;
    ssrcuminflow[hh] = 0.0;
    ssroutflow[hh] = 0.0;
    ssrcumoutflow[hh] = 0.0;

    runinflow[hh] = 0.0;
    runcuminflow[hh] = 0.0;
    runoutflow[hh] = 0.0;
    runcumoutflow[hh] = 0.0;

    soil_ssr_Buf[hh] = 0.0;
    soil_runoff_Buf[hh] = 0.0;
    soil_gw_Buf[hh] = 0.0;

    bool OK = false;
    for(long jj = 0; chkStruct(jj); ++jj)
      if(order[jj] - 1 == hh){
        OK = true;
        break;
      }

    if(!OK){
        string SS = string("'" + Name + " (Netroute_M_D)' the 'order' parameter does not have a unique value for each HRU");
        CRHMException Except(SS.c_str() , TExcept::ERR);
        LogError(Except);
        throw Except;
    }
  }
}

void ClassNetroute_M_D::run(void) {

  long nstep = getstep();
  nstep = nstep%Global::Freq;

  basinflow[0] = 0.0;
  basingw[0] = 0.0;

  if(getstep() == 1){
    for(hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
      distrib_sum[hh] = 0.0;

      for(long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
        if(distrib_hru[hh][hhh] < 0.0)
          const_cast<double **> (distrib_hru) [hh][hhh] = -distrib_hru[hh][hhh]*hru_area[hh];
        distrib_sum[hh] += distrib_hru[hh][hhh];
      }

      if(distrib_sum[hh] <= 0 && distrib_Basin[hh] <= 0.0){
        const_cast<double *> (distrib_Basin) [hh] = 1;
      }

      distrib_sum[hh] += distrib_Basin[hh];
    }
  }

  double gw_amount;

  for(long jj = 0; chkStruct(jj); ++jj){ // do HRUs in sequence

    for(hh = 0; chkStruct(hh); ++hh){
      if(order[hh] - 1 == jj)
        break;
    }

    if(soil_gwDiv == 1) // interval value
       soil_gw_Buf[hh] = soil_gw[hh];

    gwinflow[hh] = soil_gw_Buf[hh]*hru_area[hh];

    gwoutflow_diverted[hh] = 0.0;

    gw_amount = 0.0;

    for(long hhh = 0; chkStruct(hhh); ++hhh) {
      if(gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh])-1 == hh || abs(gwwhereto[hhh]) > nhru)){ // handles "gwwhereto" <> 0
        gwoutflow_diverted[hhh] = gwoutflow[hhh];
        gw_amount = gwoutflow_diverted[hhh];
        gwoutflow[hhh] = 0.0;
        gwcumoutflow_diverted[hhh] += gwoutflow_diverted[hhh];

        if(abs(gwwhereto[hhh]) <= nhru){
          if(gwwhereto[hhh] > 0){ // direct to HRU surface
            double free = soil_rechr_max[hh] - soil_rechr[hh];
            if(free > 0.0 && !soil_rechr_ByPass[hh]){
              if(free > gw_amount/hru_area[hh]){ // outflow (mm*km^2/int)
                soil_rechr[hh] += gw_amount/hru_area[hh];
                soil_moist[hh] += gw_amount/hru_area[hh];
                cum_to_soil_rechr[hh] += gw_amount/hru_area[hh];
                gw_amount = 0.0;
              }
              else {
                gw_amount = (gw_amount/hru_area[hh] - free)*hru_area[hh];
                cum_to_soil_rechr[hh] += free;
                soil_moist[hh] += free;
                soil_rechr[hh] = soil_rechr_max[hh];
              }
            }

            free = Sdmax[hh] - Sd[hh];
            if(free > 0.0 && gw_amount > 0.0 && !Sd_ByPass[hh]){
              if(free > gw_amount/hru_area[hh]){ // outflow (mm*km^2/int)
                Sd[hh] += gw_amount/hru_area[hh];
                cum_to_Sd[hh] += gw_amount/hru_area[hh];
                gw_amount = 0.0;
              }
              else {
                gw_amount = (gw_amount/hru_area[hh] - free)*hru_area[hh];
                cum_to_Sd[hh] += free;
                Sd[hh] = Sdmax[hh];
              }
            }
          } // hh > 0
          else{ // hh < 0
            gw[hh] += gw_amount/hru_area[hh];
            gw_amount = 0.0;
          }
        } // is HRU
        else{ // > nhru then put in basinflow
          basinflow[0] += gw_amount*1000; // (m3)
          HRU_cumbasinflow[hh] = gw_amount;
          cumoutflow[hh] += gw_amount;
          gw_amount = 0.0;
        }
      } // match hh
    } // for hhh

    gwcuminflow[hh] += gwinflow[hh];
    gwcumoutflow[hh] += gwoutflow[hh];

    inflow[hh] = gw_amount;
  } // for jj

  for(hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence

    if(soil_ssrDiv == 1) // interval value
       soil_ssr_Buf[hh] = soil_ssr[hh];

    if(soil_runoffDiv == 1) // interval value
       soil_runoff_Buf[hh] = soil_runoff[hh];

    runinflow[hh] = soil_runoff_Buf[hh]*hru_area[hh]; // includes melt and rain runoff
    runcuminflow[hh] += runinflow[hh];

    ssrinflow[hh] = soil_ssr_Buf[hh]*hru_area[hh]; // subsurface runoff
    ssrcuminflow[hh] += ssrinflow[hh];

    ssrcumoutflow[hh] += ssroutflow[hh];
    runcumoutflow[hh] += runoutflow[hh];

    inflow[hh] += scaling_factor[hh]*(runoutflow[hh] + ssroutflow[hh]); // add this HRU runoff and subsurface flow temporary change 10/07/11
    
    if(outflow[hh] > 0.0){

      double Used = outflow[hh]*distrib_Basin[hh]/distrib_sum[hh];
      if(distrib_Basin[hh] > 0.0){ // direct to basin

        basinflow[0] += Used*1000; // (m3)
        HRU_cumbasinflow[hh] += Used;
        cumoutflow[hh] += Used;
      }

      for(long To = 0; chkStruct(To); ++To) { // distribute outflow of HRUs

        if(hh != To && distrib_hru[hh][To] > 0.0){
          double Amount = (outflow[hh]-Used)/hru_area[To]*distrib_hru[hh][To]/(distrib_sum[hh]-distrib_Basin[hh]); // outflow (mm*km^2/int)

          if(preferential_flow[hh]) {
	          gw[To] += Amount;
	          cum_preferential_flow_to_gw[To] += Amount;
	          Amount = 0.0;
          }
          else {
            double free = soil_rechr_max[To] - soil_rechr[To];
            if(free > 0.0 && !soil_rechr_ByPass[To]){
              if(free > Amount){ // outflow (mm*km^2/int)
                soil_rechr[To] += Amount;
                soil_moist[To] += Amount;
                cum_to_soil_rechr[To] += Amount;
                Amount = 0.0;
              }
              else {
                Amount -= free;
                cum_to_soil_rechr[To] += free;
                soil_moist[To] += free;
                soil_rechr[To] = soil_rechr_max[To];
              }
            } // if

            free = Sdmax[To] - Sd[To];
            if(free > 0.0 && !Sd_ByPass[To] && Amount > 0.0){
              if(free > Amount){ // outflow (mm*km^2/int)
                Sd[To] += Amount;
                cum_to_Sd[To] += Amount;
                Amount = 0.0;
              }
              else {
                Amount -= free;
                cum_to_Sd[To] += free;
                Sd[To] = Sdmax[To];
              }
            } // if
          } // else

          if(Amount > 0.0)
            redirected_residual[To] += Amount*hru_area[To]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)

        } // contribute to this HRU
      } // distribute outflow over HRUs
    } // outflow > 0.0

    if(gwwhereto[hh] == 0) { // move to basin gw
      basingw[0] += gwoutflow[hh]*1000; // (m3) end of every day
      gwcumoutflow[hh] += gwoutflow[hh];
    }

    if(nstep == 0){ // end of every day
      if(soil_ssrDiv > 1) // daily value - ready for next day
         soil_ssr_Buf[hh] = soil_ssr[hh]/soil_ssrDiv;

      if(soil_runoffDiv > 1) // daily value - ready for next day
         soil_runoff_Buf[hh] = soil_runoff[hh]/soil_runoffDiv;

      if(soil_gwDiv > 1) // daily value - ready for next day
         soil_gw_Buf[hh] = soil_gw[hh]/soil_gwDiv;
    } // end if

  } // for hh

  for(hh = 0; chkStruct(hh); ++hh) {
    cuminflow[hh] += inflow[hh];
    cumscaling_boost[hh] += inflow[hh]*(scaling_factor[hh] - 1.0);

    outflow_diverted[hh] = 0.0;
    if(distrib_sum[hh] > 0.0){ // does not apply to last HRU
      for(long hhh = 0; chkStruct(hhh); ++hhh){
        outflow_diverted[hh] += outflow[hh]*distrib_hru[hh][hhh]/distrib_sum[hh];
      }
    }
    cumoutflow_diverted[hh] += outflow_diverted[hh];
  } // end for

  hruDelay->DoMuskingum();
  runDelay->DoClark();
  ssrDelay->DoClark();
  gwDelay->DoClark();

  basinflow_s[0] = basinflow[0]*Global::Freq/86400.0;
  basingw_s[0] = basingw[0]*Global::Freq/86400.0;

  cumbasinflow[0] += basinflow[0];
  cumbasingw[0] += basingw[0];
}

void ClassNetroute_M_D::finish(bool good) {

  double Allcuminflow = 0.0;
  double Allcumoutflow = 0.0;
  double Allcumoutflowdiverted = 0.0;

  double Allgwcuminflow = 0.0;
  double Allgwcumoutflow = 0.0;
  double Allgwcumoutflowdiverted = 0.0;

  double Allssrcuminflow = 0.0;
  double Allssrcumoutflow = 0.0;
  double Allruncuminflow = 0.0;
  double Allruncumoutflow = 0.0;

  double AllSdcuminflow = 0.0;
  double Allrechrcuminflow = 0.0;

  for(hh = 0; chkStruct(); ++hh) {

    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cuminflow              (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cumoutflow             (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cumoutflow_diverted    (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' hruDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' scaling_boost          (mm) (mm*km^2) (mm*basin): ").c_str(), cumscaling_boost[hh]/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' ssrcuminflow           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' ssrcumoutflow          (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' ssrDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' runoffcuminflow        (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' runoffcumoutflow       (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' runDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' gwcuminflow            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' gwcumoutflow           (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' gwcumdiverted          (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' gwDelay_in_storage     (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cum_to_Sd              (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cum_to_soil_rechr      (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
    LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' HRU_cumbasinflow       (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");

    Allcuminflow += cuminflow[hh];
    Allcumoutflow += cumoutflow[hh];
    Allcumoutflowdiverted += cumoutflow_diverted[hh];

    Allgwcuminflow += gwcuminflow[hh];
    Allgwcumoutflow += gwcumoutflow[hh];
    Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

    Allssrcumoutflow += ssrcumoutflow[hh];
    Allssrcuminflow += ssrcuminflow[hh];
    Allruncuminflow += runcuminflow[hh];
    Allruncumoutflow += runcumoutflow[hh];

    AllSdcuminflow += cum_to_Sd[hh]*hru_area[hh];
    Allrechrcuminflow += cum_to_soil_rechr[hh]*hru_area[hh];
  }

  LogMessage(string("'" + Name + " (Netroute_M_D)' cumulative surface & subsurface basinflow(m^3): ").c_str(), cumbasinflow[0]);
  LogMessage(string("'" + Name + " (Netroute_M_D)' cumulative basingw  (m^3): ").c_str(), cumbasingw[0]);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute_M_D)' Allgwcuminflow (mm*basin): ").c_str(), Allgwcuminflow);
  LogMessage(string("'" + Name + " (Netroute_M_D)' Allgwcumoutflow (mm*basin): ").c_str(), Allgwcumoutflow);
  LogMessage(string("'" + Name + " (Netroute_M_D)' Allgwcumoutflowdiverted (mm*basin): ").c_str(), Allgwcumoutflowdiverted);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute_M_D)' Allcuminflow (mm*basin): ").c_str(), Allcuminflow);
  LogMessage(string("'" + Name + " (Netroute_M_D)' Allcumoutflow (mm*basin): ").c_str(), Allcumoutflow);
  LogMessage(string("'" + Name + " (Netroute_M_D)' Allcumoutflowdiverted (mm*basin): ").c_str(), Allcumoutflowdiverted);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute_M_D)' Allssrcuminflow (mm*basin): ").c_str(), Allssrcuminflow);
  LogMessage(string("'" + Name + " (Netroute_M_D)' Allssrcumoutflow (mm*basin): ").c_str(), Allssrcumoutflow);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute_M_D)' Allruncuminflow (mm*basin): ").c_str(), Allruncuminflow);
  LogMessage(string("'" + Name + " (Netroute_M_D)' Allruncumoutflow (mm*basin): ").c_str(), Allruncumoutflow);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute_M_D)' AllSdcuminflow (mm*basin): ").c_str(), AllSdcuminflow);
  LogMessage(string("'" + Name + " (Netroute_M_D)' Allrechrcuminflow (mm*basin): ").c_str(), Allrechrcuminflow);
  LogDebug(" ");

  delete hruDelay;
  delete ssrDelay;
  delete runDelay;
  delete gwDelay;
}