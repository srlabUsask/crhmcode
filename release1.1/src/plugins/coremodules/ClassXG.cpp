//created by Manishankar Mondal

#include "ClassXG.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM/ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

ClassXG* ClassXG::klone(string name) const{
  return new ClassXG(name);
}

void ClassXG::decl(void) {

  Description = "'A Simple Thaw-Freeze Algorithm (Changwei, 2013).' \
                 'using variable surface temperature hru_tsf (°C),' \
                 'using variable air temperature hru_t (°C) and uses parameter n_factor (Woo (2012, p. 57) to estimate surface temperature from the air temperature during snow free periods.'";

  ko = 0.21;  // W/(m K) organic material
  km = 2.50;  // W/(m K) mineral
  ka = 0.025; // W/(m K) air
  ki = 2.24;  // W/(m K) ice  2.24
  kw = 0.57;  // W/(m K) water   0.57

  variation_set = VARIATION_ORG;

  declstatvar("Zd_front", TDim::NDEFN, "depth of freezing/thawing fronts", "(m)", &Zd_front, &Zd_front_array, Global::nlay);

  declstatvar("Zdf", TDim::NHRU, "active freezing front", "(m)", &Zdf);

  declstatvar("Zdt", TDim::NHRU, "active thawing front", "(m)", &Zdt);

  declstatvar("Th_low_lay", TDim::NHRU, "lowest thawed layer", "()", &Th_low_lay);

  declstatvar("Fz_low_lay", TDim::NHRU, "lowest frozen layer", "()", &Fz_low_lay);

  declstatvar("nfront", TDim::NHRU, "number of freezing/thawing fronts", "()", &nfront);

  declstatvar("Bfr", TDim::NHRU, "freeze degree days", "(ºC*d)", &Bfr);

  declstatvar("Bth", TDim::NHRU, "thaw degree days", "(ºC*d)", &Bth);

  declvar("pf", TDim::NDEFN, "freezing ratios", "()", &pf, &pf_lay, Global::nlay);

  declvar("pt", TDim::NDEFN, "thawing ratios", "()", &pt, &pt_lay, Global::nlay);

  declstatvar("ttc", TDim::NDEFN, "thawing thermal conductivity", "(W/(m*K)", &ttc, &ttc_lay, Global::nlay);

  declstatvar("ftc", TDim::NDEFN, "freezing thermal conductivity", "(W/(m*K)", &ftc, &ftc_lay, Global::nlay);

  declstatvar("ttc_contents", TDim::NDEFN, "thawing 0/1 thaw/freeze", "()", &ttc_contents, &ttc_contents_lay, Global::nlay);

  declstatvar("ftc_contents", TDim::NDEFN, "freezing 0/1 freeze/thaw", "()", &ftc_contents, &ftc_contents_lay, Global::nlay);

  declvar("tc_composite", TDim::NDEFN, "freeze/thaw composite ftc/ttc value", "(W/(m*K)", &tc_composite, &tc_composite_lay, Global::nlay);

  declvar("tc_composite2", TDim::NDEFN, "freeze/thaw composite2 ftc/ttc value", "(W/(m*K)", &tc_composite2, &tc_composite2_lay, Global::nlay);

  declvar("layer_h2o", TDim::NDEFN, "water content", "(kg/m^3)", &layer_h2o, &h2o_lay, Global::nlay);

  decllocal("B", TDim::NHRU, "freeze degree days", "()", &B);

  decllocal("TrigAcc", TDim::NHRU, "freeze degree days", "()", &TrigAcc);

  decllocal("TrigState", TDim::NHRU, "1/0/-1 thaw/standby/freeze", "()", &TrigState);

  decldiag("XG_moist_d", TDim::NHRU, "soil moisture depth", "()", &XG_moist_d);

  decldiag("XG_rechr_d", TDim::NHRU, "XG calculated soil recharge depth", "()", &XG_rechr_d);

  decllocal("check_XG_moist", TDim::NHRU, "sum of XG soil_moist should equal SoilX soil_moist", "()", &check_XG_moist);

  decllocal("t_trend", TDim::NHRU, "temperature long term trend", "(°C)", &t_trend);

  decllocal("check_t", TDim::NHRU, "check temperature source", "(°C)", &check_t);

  declstatvar("XG_max", TDim::NDEFN, "layer maximum soil moisture content", "(mm)", &XG_max, &XG_max_lay, Global::nlay);

  declstatvar("XG_moist", TDim::NDEFN, "layer soil moisture content", "(mm)", &XG_moist, &XG_moist_lay, Global::nlay);

  declvar("theta", TDim::NDEFN, "XG theta calulated from soil moistures and defaults", "(m^3/m^3)", &theta, &theta_lay, Global::nlay);

  declstatvar("rechr_fract", TDim::NDEFN, "fraction of layer moisture assigned to soilX soil_rechr.", "()", &rechr_fract, &rechr_fract_lay, Global::nlay);

  declstatvar("moist_fract", TDim::NDEFN, "fraction of layer moisture assigned to soilX soil_moist.", "()", &moist_fract, &moist_fract_lay, Global::nlay);

  declstatvar("default_fract", TDim::NDEFN, "below defined soil_moist profile - use default ", "()", &default_fract, &default_fract_lay, Global::nlay);


  decldiagparam("Trigthrhld", TDim::NHRU, "[100.0]", "50.0", "1000.0", "Trigger reference level in degree days", "(ºC*d)", &Trigthrhld);

  declparam("N_Soil_layers", TDim::NHRU, "[2]", "1", "20", "number of soil layers. Must be less than or equal nlay. Define Parameters for layers used. All others are ignored", "()", &N_Soil_layers);

  declparam("calc_coductivity", TDim::NHRU, "[0]", "0", "1", "0 - linear method, 1 - use Johansen 1975", "()", &calc_coductivity);

  declparam("depths", TDim::NDEFN, "[0.5]", "0.0", "10.0", "depths(thickness) of soil layers", "(m)", &depths, &depths_lay, Global::nlay);

  declparam("por", TDim::NDEFN, "[0.5]", "0.0", "1.0", "porosity", "(m^3/m^3)", &por, &por_lay, Global::nlay);

  declparam("theta_default", TDim::NDEFN, "[0.5]", "0.0", "1.0", "default degree of saturation when not defined by soil module profile from module 'soilX')", "(m^3/m^3)", &theta_default, &theta_default_lay, Global::nlay);

  declparam("theta_min", TDim::NHRU, "[0.001]", "0.0001", "0.1", "minimum value of theta to prevent divide by zero errors)", "(m^3/m^3)", &theta_min);

  declparam("soil_solid_km", TDim::NDEFN, "[2.5]", "0.03", "4", "dry soil thermal conductivity", "(W/(m*K)", &soil_solid_km, &soil_solid_km_lay, Global::nlay);

  declparam("soil_solid_km_ki", TDim::NDEFN, "[2.5]", "0.03", "4", "saturated frozen soil thermal conductivity", "(W/(m*K)", &soil_solid_km_ki, &soil_solid_km_ki_lay, Global::nlay);

  declparam("soil_solid_km_kw", TDim::NDEFN, "[2.5]", "0.03", "4", "saturated unfrozen soil thermal conductivity.", "(W/(m*K)", &soil_solid_km_kw, &soil_solid_km_kw_lay, Global::nlay);

  declparam("SWE_k", TDim::NHRU, "[0.35]", "0.1", "1.0", "thermal conductivity of blowing snow.", "(W/(m*K)", &SWE_k);

  declparam("Zdf_init", TDim::NHRU, "[0]", "0.0", "3", "initial depth of freezing front. Maximum value limited by freezing algorithm.", "(m)", &Zdf_init);

  declparam("Zdt_init", TDim::NHRU, "[0]", "0.0", "3", "initial depth of thawing front. Maximum value limited by thawing algorithm.", "(m)", &Zdt_init);

  declparam("Zpf_init", TDim::NHRU, "[2]", "0.0", "30", "initial depth of permafrost front. Maximum value limited by thawing algorithm. If zero set to 2m", "(m)", &Zpf_init);

  declparam("freeze_kw_ki_update", TDim::NHRU, "[0]", "0", "1", "Change thermal conductivities kw to ki behind freezing front.", "()", &freeze_kw_ki_update);

  declparam("thaw_ki_kw_update", TDim::NHRU, "[0]", "0", "1", "Change thermal conductivities ki to kw behind thawing front.", "()", &thaw_ki_kw_update);

  declparam("k_update", TDim::NHRU, "[0]", "0", "2", "Change thermal conductivities ki to kw 0 - never, 1 _ after processing layer, 2 - continuously through layer.", "()", &k_update);

  declgetparam("*", "soil_moist_max", "(mm)", &soil_moist_max); // used since no declgetparam defined

  declgetparam("*", "soil_rechr_max", "(mm)", &soil_rechr_max); // used since no declgetparam defined


  declgetvar("*", "soil_moist", "(mm)", &soil_moist);

  declgetvar("*", "soil_rechr", "(mm)", &soil_rechr);


  variation_set = VARIATION_0;

  declgetvar("*", "hru_tsf", "(°C)", &hru_tsf);


  variation_set = VARIATION_1;

  declparam("n_factor_a", TDim::NHRU, "[0.5]", "0", "1.2", "n_factor = n_factor_a - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_a);

  declparam("n_factor_b", TDim::NHRU, "[0.54]", "0.0", "1.0", "n_factor = n_factor_b - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_b);

  declparam("n_factor_c", TDim::NHRU, "[0.05]", "0.0", "0.1", "n_factor = n_factor_c - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_c);

  decllocal("n_factor_T", TDim::NHRU, "Days after the start of thaw", "()", &n_factor_T);

  decllocal("n_factor", TDim::NHRU, "calculated value of n_factor from parameters. Woo (2012), p. 57", "()", &n_factor);

  declgetvar("*", "hru_t", "(°C)", &hru_t);

  declgetvar("*", "SWE", "(mm)", &SWE);


  variation_set = VARIATION_ORG;
}

void ClassXG::init(void) {

  nhru = getdim(TDim::NHRU);
  nlay = getdim(TDim::NLAY);

  front_size = nlay; // first two locations used by active Zdf and Zdt. Last location always 0.0, i.e. end of stack. Not related to nlay. Only dimensioned as nlay for convenience

  if(front_size < 4){ //
    CRHMException TExcept("number of layers (nlay) should 4 or greater to give 1 or more fronts.", TExcept::TERMINATE);
    LogError(TExcept);
  }

  for(hh = 0; hh < nhru; ++hh) {

    if(N_Soil_layers[hh] > nlay){
      CRHMException TExcept("nlay cannot be less than N_Soil_layers.", TExcept::TERMINATE);
      LogError(TExcept);
    }

    nfront[hh] = 0;
    Fz_low_lay[hh] = 1;
    Th_low_lay[hh] = 1;
    t_trend[hh] = 0.0;

    if(Zpf_init[hh] <= 0.0)
      const_cast<double *> (Zpf_init)[hh] = 2.0;

    for(long ll = 0; ll < nlay; ++ll)
      Zd_front_array[ll][hh] = 0.0;

    double rechrmax = soil_rechr_max[hh];
    double soilmax = soil_moist_max[hh];
    double profile_depth = 0.0;

    XG_rechr_d[hh] = 0.0;
    XG_moist_d[hh] = 0.0;

    for(long ll = 0; ll < N_Soil_layers[hh]; ++ll) {
      tc_composite_lay[ll][hh] = 0;
      tc_composite2_lay[ll][hh] = 0;
      profile_depth += depths_lay[ll][hh];

      XG_max_lay[ll][hh] = por_lay[ll][hh]*depths_lay[ll][hh]*1000.0;
      theta_lay[ll][hh] = theta_default_lay[ll][hh]; // initially make the default value

      if(rechrmax > 0.0){ // distribute moisture over layers
         if(rechrmax > XG_max_lay[ll][hh]){
           XG_rechr_d[hh] += depths_lay[ll][hh];
           rechr_fract_lay[ll][hh] = 1.0;
           rechrmax -= XG_max_lay[ll][hh];
         }
         else{
           double amount = rechrmax/XG_max_lay[ll][hh];
           rechr_fract_lay[ll][hh] = rechrmax/XG_max_lay[ll][hh];

           XG_rechr_d[hh] += depths_lay[ll][hh]*amount;
           double left = 1.0 - amount;
           if(soilmax >= XG_max_lay[ll][hh]*left){ // layer all used
             moist_fract_lay[ll][hh] = left;
             soilmax -= XG_max_lay[ll][hh]*left;
             XG_moist_d[hh] += depths_lay[ll][hh];
           }
           else { // layer partly used
             moist_fract_lay[ll][hh] = (soilmax - rechrmax)/XG_max_lay[ll][hh];
             double used = rechr_fract_lay[ll][hh] + moist_fract_lay[ll][hh];
             default_fract_lay[ll][hh] = 1.0 - used;
             XG_moist_d[hh] += (XG_rechr_d[hh] + depths_lay[ll][hh]*used);
             soilmax = 0.0;
           }
           rechrmax = 0.0;
         }
      }
      else if(soilmax > 0.0){ // distribute remaining moisture over layers
        if(soilmax >= XG_max_lay[ll][hh]){
           XG_moist_d[hh] += depths_lay[ll][hh];
           moist_fract_lay[ll][hh] = 1.0;
           soilmax -= XG_max_lay[ll][hh];
        }
        else{
          double amount = soilmax/XG_max_lay[ll][hh];
          XG_moist_d[hh] += depths_lay[ll][hh]*amount;
          moist_fract_lay[ll][hh] = amount;

          double left = 1.0 - amount;
          if(left) // adjust last layer depth
            default_fract_lay[ll][hh] = left;
          soilmax = 0.0;
        }
      }
      else{ // profile below active SoilX
        default_fract_lay[ll][hh] = 1;

      }
    } // for soil layers

// Calculate thermal conductivities

    Th_low_lay[hh] = 1;
    Fz_low_lay[hh] = 1;
    check_XG_moist[hh] = 0.0;

    for(long ll = 0; ll < N_Soil_layers[hh]; ++ll) {
      if(soil_moist_max[hh] > 0.0) // handle soil_moist_max = 0.0, i.e. slough
        XG_moist_lay[ll][hh] = rechr_fract_lay[ll][hh]*XG_max_lay[ll][hh]*soil_rechr[hh]/soil_rechr_max[hh]
                             + moist_fract_lay[ll][hh]*XG_max_lay[ll][hh]*(soil_moist[hh] - soil_rechr[hh])/(soil_moist_max[hh] - soil_rechr_max[hh]);
      else
        XG_moist_lay[ll][hh] = 0.0;

      check_XG_moist[hh] += XG_moist_lay[ll][hh];

      XG_moist_lay[ll][hh] += default_fract_lay[ll][hh]*XG_max_lay[ll][hh]*theta_default_lay[ll][hh]; // adjust for below profile theta

      theta_lay[ll][hh] =  XG_moist_lay[ll][hh]/XG_max_lay[ll][hh];

      if(theta_lay[ll][hh] <= theta_min[hh]) // do not allow zero values
        theta_lay[ll][hh] = theta_min[hh];

      h2o_lay[ll][hh] = theta_lay[ll][hh]*por_lay[ll][hh]*1000; // water kg/m3 was water fraction

      if(k_update[hh]){ // change all layers to dynamic
        if(ftc_contents_lay[ll][hh] == 1) // always set somewhere else
          ftc_lay[ll][hh] = get_ttc_lay(ll);
        else
          ftc_lay[ll][hh] = get_ftc_lay(ll);

        if(ttc_contents_lay[ll][hh] == 1) // always set somewhere else
          ttc_lay[ll][hh] = get_ftc_lay(ll);
        else
          ttc_lay[ll][hh] = get_ttc_lay(ll);
      }
      else{
        ftc_lay[ll][hh] = get_ftc_lay(ll);
        ttc_lay[ll][hh] = get_ttc_lay(ll);

        ftc_contents_lay[ll][hh] = 0;
        ttc_contents_lay[ll][hh] = 0;
      }
    } // for layers

    for(long ll = 1; ll < N_Soil_layers[hh]; ++ll) {
      pf_lay[ll][hh] = sqrt(ftc_lay[ll-1][hh]*h2o_lay[ll][hh]/(ftc_lay[ll][hh]*h2o_lay[ll-1][hh])); // water kg/m3
      pt_lay[ll][hh] = sqrt(ttc_lay[ll-1][hh]*h2o_lay[ll][hh]/(ttc_lay[ll][hh]*h2o_lay[ll-1][hh])); // water kg/m3
    }

    if(rechrmax != 0.0 || soilmax != 0.0){
      string S = string("'") + Name + " (XG)' too few layers (nlay) to handle soil_max in hru = " + to_string(hh+1).c_str();
      CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
      LogError(TExcept);
    }

    if(profile_depth + 0.00001 < Zpf_init[hh]){ // values in Debug Inspector identical but comparison true
      string S = string("'") + Name + " (XG)' sum of soil layer depths is less than the depth of the initial permafrost in hru = " + to_string(hh+1).c_str();
      CRHMException TExcept(S.c_str(), TExcept::WARNING);
      LogError(TExcept);
    }

    bool EndofProfile = false;

    for(long ll = 0; ll < nlay; ++ll) {

      if(ll+1 > N_Soil_layers[hh]){
        EndofProfile = true;
      }

      if(depths_lay[ll][hh] == 0.0 && !EndofProfile){
        CRHMException TExcept("Fewer soil layers defined than specified in N_Soil_layers.", TExcept::TERMINATE);
        LogError(TExcept);
      }
    } // for nlay

    TrigAcc[hh] = 0.0;
    TrigState[hh] = 0;
    B[hh] = 0.0;
    Zdf[hh] = 0.0;
    Zdt[hh] = 0.0;
    Bfr[hh] = 0.0;
    Bth[hh] = 0.0;

    if(variation == VARIATION_1)
      n_factor[hh] = 0.0;

  } // for hh
} // init

void ClassXG::run(void) {

  //double X; varible is unreferenced commenting out for now - jhs507
  //double X1; varible is unreferenced commenting out for now - jhs507
  //double Za; varible is unreferenced commenting out for now - jhs507
  double L = 335000;// the latent heat of fusion of ice(J/kg);
  long  nstep = getstep();

  for(hh = 0; chkStruct(); ++hh) {

    if(nstep == 1){
      const_cast<double *> (depths_lay[N_Soil_layers[hh]-1])[hh] = 100.0; // ensure stays in last layer. Must be here to be restored
      if(Zdf_init[hh] > 0.0 && Bfr[hh] <= 0.0) // not set by state file
        find_freeze_D(Zdf_init[hh]); // initialises Bfr and Zdf from Zdf_init
      if(Zdt_init[hh] && Zdt_init[hh] < Zpf_init[hh] && Bth[hh] <= 0.0) // not set by state file
        find_thaw_D(Zdt_init[hh]); // initialises Bth and Zdt from Zdt_init
    }


    if(nstep%Global::Freq == 1 || Global::Freq == 1) // end of every day
      B[hh] = 0.0;

    if(variation == VARIATION_ORG)
      B[hh] += hru_tsf[hh]/Global::Freq; // use hru_tsf
    else
      B[hh] += hru_t[hh]/Global::Freq; // use hru_t

    TrigAcc[hh] += B[hh];

    t_trend[hh] -= t_trend[hh]/192;

    t_trend[hh] += B[hh]/192;

    if(getstep()%Global::Freq == 0 || Global::Freq == 1){ // end of every day

      if(TrigAcc[hh] > Trigthrhld[hh]) // keep TrigAcc within +- Trigthrhld
        TrigAcc[hh] = Trigthrhld[hh];
      else if(TrigAcc[hh] < -Trigthrhld[hh])
        TrigAcc[hh] = -Trigthrhld[hh];

// Enter freeze or thaw from idle

      if(TrigAcc[hh] >= Trigthrhld[hh]/2.0 && TrigState[hh] == 0 && (Zdf[hh] > 0.0 || nfront[hh])){ // thaw
        TrigState[hh] = 1;
        Zd_front_array[1][hh] = -Zdf[hh];
        t_trend[hh] = 0.0;
      } // if

      if(TrigAcc[hh] <= -Trigthrhld[hh]/2.0 && TrigState[hh] == 0){ // freeze
        TrigState[hh] = -1;
        Zd_front_array[1][hh] = Zdt[hh];
        t_trend[hh] = 0.0;
      } // if

// Goto idle from freeze or thaw

      if(TrigState[hh] == -1 && TrigAcc[hh] >= Trigthrhld[hh]/2.0 && t_trend[hh] > 0.0){ // changing state from freeze
        TrigState[hh] = 0;

        if(Zdt[hh] > 0.0 && Zdf[hh] > 0.0){
          if(Zdt[hh] > Zdf[hh]){ // did not reach last thawing front
            push_front(Zdt[hh]);
            Zdt[hh] = 0.0;
            Bth[hh] = 0.0;
            Zd_front_array[0][hh] = 0.0;
            Zd_front_array[1][hh] = -Zdf[hh];
          } // if
        } // if
      } // if

      if(TrigState[hh] == 1 && TrigAcc[hh] <= -Trigthrhld[hh]/2.0 && t_trend[hh] < 0.0){ // changing state from thaw
        TrigState[hh] = 0;

        if(variation == VARIATION_1)
          n_factor[hh] = 0.0;

        if(Zdf[hh] > 0.0 && Zdt[hh] > 0.0){
          if(Zdf[hh] > Zdt[hh]){ // did not reach last freezing front
            push_front(-Zdf[hh]); // did not reach last freezing front
            Zdf[hh] = 0.0;
            Bfr[hh] = 0.0;
            Zd_front_array[0][hh] = 0.0;
            Zd_front_array[1][hh] = Zdt[hh];
          }
        }
      }

// Calculate thermal conductivities

    Th_low_lay[hh] = 1;
    Fz_low_lay[hh] = 1;
    check_XG_moist[hh] = 0.0;

    for(long ll = 0; ll < N_Soil_layers[hh]; ++ll) {
      if(soil_moist_max[hh] > 0.0) // handle soil_moist_max = 0.0, i.e. slough
        XG_moist_lay[ll][hh] = rechr_fract_lay[ll][hh]*XG_max_lay[ll][hh]*soil_rechr[hh]/soil_rechr_max[hh]
                             + moist_fract_lay[ll][hh]*XG_max_lay[ll][hh]*(soil_moist[hh] - soil_rechr[hh])/(soil_moist_max[hh] - soil_rechr_max[hh]);
      else
        XG_moist_lay[ll][hh] = 0.0;

      check_XG_moist[hh] += XG_moist_lay[ll][hh];

      XG_moist_lay[ll][hh] += default_fract_lay[ll][hh]*XG_max_lay[ll][hh]*theta_default_lay[ll][hh]; // adjust for below profile theta

      theta_lay[ll][hh] =  XG_moist_lay[ll][hh]/XG_max_lay[ll][hh];

      if(theta_lay[ll][hh] <= theta_min[hh]) // do not allow zero values
        theta_lay[ll][hh] = theta_min[hh];

      h2o_lay[ll][hh] = theta_lay[ll][hh]*por_lay[ll][hh]*1000; // water kg/m3 was water fraction

      if(k_update[hh]){ // change all layers to dynamic
        if(ftc_contents_lay[ll][hh] == 1) // always set somewhere else
          ftc_lay[ll][hh] = get_ttc_lay(ll);
        else
          ftc_lay[ll][hh] = get_ftc_lay(ll);

        if(ttc_contents_lay[ll][hh] == 1) // always set somewhere else
          ttc_lay[ll][hh] = get_ftc_lay(ll);
        else
          ttc_lay[ll][hh] = get_ttc_lay(ll);
      }
      else{
        ftc_lay[ll][hh] = get_ftc_lay(ll);
        ttc_lay[ll][hh] = get_ttc_lay(ll);

        ftc_contents_lay[ll][hh] = 0;
        ttc_contents_lay[ll][hh] = 0;
      }
    } // for layers

    for(long ll = 1; ll < N_Soil_layers[hh]; ++ll) {
      pf_lay[ll][hh] = sqrt(ftc_lay[ll-1][hh]*h2o_lay[ll][hh]/(ftc_lay[ll][hh]*h2o_lay[ll-1][hh])); // water kg/m3
      pt_lay[ll][hh] = sqrt(ttc_lay[ll-1][hh]*h2o_lay[ll][hh]/(ttc_lay[ll][hh]*h2o_lay[ll-1][hh])); // water kg/m3
    }

// Execute freeze or thaw

      if(TrigState[hh] < 0.0){ // handle freezing
        Bfr[hh] -= B[hh];  // Calculate the value of Degree-day for every day
        if(Bfr[hh] > 0.0){
          freeze(); // XG-Algorithm - Freezing
// check for thaw front
          if(Zdt[hh] > 0.0 && Zdf[hh] >= Zdt[hh]){
            if(nfront[hh] > 0){
              double Last = last_front();
              if(Last < 0.0){ // frozen front
                Zdf[hh] = pop_front();
                find_freeze_D(Zdf[hh]);
                double Last = last_front();
                if(Last > 0.0){ // thaw front
                  Zdt[hh] = pop_front();
                  find_thaw_D(Zdf[hh]);
                  Zd_front_array[1][hh] = Zdt[hh];
                }
                else if(Last < 0.0){ // never two frozen fronts together
//                  assert(0);
                  string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow) + " **never two frozen fronts together, check for thaw front (20447)";
                  string SS = D + "hh " + to_string(hh) + "Last: " + FloatToStrF(Last, TFloatFormat::ffFixed, 10, 4);
                  SS = SS + " Zdt[hh]: " + FloatToStrF(Zdt[hh], TFloatFormat::ffFixed, 10, 4)
                          + " Zdf[hh]: " + FloatToStrF(Zdt[hh], TFloatFormat::ffFixed, 10, 4);
                  CRHMException TExcept(SS.c_str(), TExcept::WARNING);
                  LogError(TExcept);
               }
                else{ // no thaw front
                  Zdt[hh] = 0.0;
                  Bth[hh] = 0.0;
                  Zd_front_array[1][hh] = 0.0;
                }
              }
              else if(Last < 0.0){ // never two freeze fronts together
//                  assert(0);
                  string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow) + " **never two thaw fronts together (20462)";
                  string SS = D + "hh " + to_string(hh) + "Last: " + FloatToStrF(Last, TFloatFormat::ffFixed, 10, 4);
                  SS = SS + " Zdt[hh]: " + FloatToStrF(Zdt[hh], TFloatFormat::ffFixed, 10, 4)
                          + " Zdf[hh]: " + FloatToStrF(Zdt[hh], TFloatFormat::ffFixed, 10, 4);
                  CRHMException TExcept(SS.c_str(), TExcept::WARNING);
                  LogError(TExcept);
              }
              else{ // no thaw layer
                Zdt[hh] = 0.0;
                Bth[hh] = 0.0;
                Zd_front_array[1][hh] = 0.0;
              }
            }
            else{ // no fronts
              Zdt[hh] = 0.0;
              Bth[hh] = 0.0;
              Zd_front_array[1][hh] = 0.0;
            }
          }
        }
        Zd_front_array[0][hh] = -Zdf[hh];
      } // freezing handled

      else if(TrigState[hh] > 0.0){ // Surface thawing lower ground frozen

        if(variation == VARIATION_1){
          if(SWE[hh] > 0.0)
            n_factor_T[hh] = 0.0;
          else
            ++n_factor_T[hh];

          n_factor[hh] = n_factor_a[hh] - n_factor_b[hh]*exp(-n_factor_c[hh]*n_factor_T[hh]);
          if(n_factor[hh] >= 0.0)
            B[hh] = B[hh]*n_factor[hh]; // modify
        }

        Bth[hh] += B[hh];  // Calculate the value of Degree-day for every day

        if(Bth[hh] <= 0.0){
          Bfr[hh] = Bth[hh];
          Zdt[hh] = 0.0;
          Bth[hh] = 0.0;
        }
        else{
          thaw(); // XG-Algorithm - Thawing
// check for freeze front
          if(Zdf[hh] > 0.0 && Zdt[hh] >= Zdf[hh]){
            if(nfront[hh] > 0){
              double Last = last_front();
              if(Last > 0.0){ // thaw front
                Zdt[hh] = pop_front();
                find_thaw_D(Zdt[hh]);
                Last = last_front();
                if(Last < 0.0){ // frozen front
                  Zdf[hh] = pop_front();
                  find_freeze_D(Zdf[hh]);
                  Zd_front_array[1][hh] = -Zdf[hh];
                }
                else if(Last > 0.0){ // never two thaw fronts together
//                  assert(0);
                  string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow) + " **check for freeze front, never two thaw fronts together (20522)";
                  string SS = D + "hh " + to_string(hh) + "Last: " + FloatToStrF(Last, TFloatFormat::ffFixed, 10, 4);
                  SS = SS + " Zdt[hh]: " + FloatToStrF(Zdt[hh], TFloatFormat::ffFixed, 10, 4)
                          + " Zdf[hh]: " + FloatToStrF(Zdt[hh], TFloatFormat::ffFixed, 10, 4);
                  CRHMException TExcept(SS.c_str(), TExcept::WARNING);
                  LogError(TExcept);
                }
                else{ // no frozen front
                  Zdf[hh] = 0.0; // no frozen layers
                  Bfr[hh] = 0.0;
                  Zd_front_array[1][hh] = 0.0;
                }
              }
              else if(Last < 0.0){ // never two freeze fronts together
//                  assert(0);
                  string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow) + " never two thaw fronts together (20537)";
                  string SS = D + "hh " + to_string(hh) + "Last: " + FloatToStrF(Last, TFloatFormat::ffFixed, 10, 4);
                  SS = SS + " Zdt[hh]: " + FloatToStrF(Zdt[hh], TFloatFormat::ffFixed, 10, 4)
                          + " Zdf[hh]: " + FloatToStrF(Zdt[hh], TFloatFormat::ffFixed, 10, 4);
                  CRHMException TExcept(SS.c_str(), TExcept::WARNING);
                  LogError(TExcept);
              }
              else{ // no thaw layer
                Zdf[hh] = 0.0;
                Bfr[hh] = 0.0;
                Zd_front_array[1][hh] = 0.0;
              }
            }
            else{ // no fronts
              Zdf[hh] = 0.0; // no frozen layer
              Bfr[hh] = 0.0;
              Zdt[hh] = 0.0;
              Bth[hh] = 0.0;
              TrigState[hh] = 0;
              Zd_front_array[1][hh] = 0.0;
            }
          } // if
        } // else
        Zd_front_array[0][hh] = Zdt[hh];
      } // thawing handled
    } // end of every day
  } // for hh
}

void ClassXG::freeze(void) { // XG-Algorithm - Freezing

  long lay = 1;
  double Za;
  double L = 335000; // the latent heat of fusion of ice(3.35�?105J/kg);

  Zdf[hh] = 0.0;

  double ftc;
  if(k_update[hh] == 2)
    ftc = Interpolated_ftc_lay(Zdf[hh], lay);
  else
    ftc = ftc_lay[lay-1][hh];

  Za = sqrt(2ll*86400ll*ftc*Bfr[hh]/(h2o_lay[lay-1][hh]*L));


  while(Za > depths_lay[lay-1][hh] && lay < N_Soil_layers[hh]){
    Zdf[hh] += depths_lay[lay-1][hh];

    Za = (Za - depths_lay[lay-1][hh])/pf_lay[lay][hh];
    ++lay;

    if(k_update[hh] > 0 && freeze_kw_ki_update[hh] && lay > Fz_low_lay[hh]){ // change layer to ki
      ftc_lay[Fz_low_lay[hh]-1][hh] = get_ttc_lay(Fz_low_lay[hh]-1);
      ftc_contents_lay[Fz_low_lay[hh]-1][hh] = 1;
      pf_lay[Fz_low_lay[hh]][hh] = sqrt(ftc_lay[Fz_low_lay[hh]-1][hh]*h2o_lay[Fz_low_lay[hh]][hh]/(ftc_lay[Fz_low_lay[hh]][hh]*h2o_lay[Fz_low_lay[hh]-1][hh])); // water kg/m3
      Fz_low_lay[hh] = lay;
      tc_composite_lay[lay-1][hh] = ftc_lay[lay-1][hh];
    }
  } // while
  Zdf[hh] += Za;

  if(Zdf[hh] > Zpf_init[hh])
    Zdf[hh] = Zpf_init[hh]; // limit to less than permafrost depth
}

void ClassXG::thaw(void) { // XG-Algorithm - Thawing

  long lay = 1;
  double Za;
  double L = 335000;// the latent heat of fusion of ice(3.35�?105J/kg);

  Zdt[hh] = 0.0;

  double ttc;
  if(k_update[hh] == 2)
    ttc = Interpolated_ttc_lay(Zdf[hh], lay);
  else
    ttc = ttc_lay[lay-1][hh];

  Za = sqrt(2ll*86400ll*ttc*Bth[hh]/(h2o_lay[lay-1][hh]*L)); //Stefan Equation

  while(Za > depths_lay[lay-1][hh] && lay < N_Soil_layers[hh]){
    Zdt[hh] += depths_lay[lay-1][hh];

    Za = (Za - depths_lay[lay-1][hh])/pt_lay[lay][hh];
    ++lay;

    if(k_update[hh] > 0 && thaw_ki_kw_update[hh] && lay > Th_low_lay[hh]){ // change layer to kw
      ttc_lay[Th_low_lay[hh]-1][hh] = get_ftc_lay(Th_low_lay[hh]-1);
      ttc_contents_lay[Th_low_lay[hh]-1][hh] = 1;
      pt_lay[Th_low_lay[hh]][hh] = sqrt(ttc_lay[Th_low_lay[hh]-1][hh]*h2o_lay[Th_low_lay[hh]][hh]/
        (ttc_lay[Th_low_lay[hh]][hh]*h2o_lay[Th_low_lay[hh]-1][hh]));
      Th_low_lay[hh] = lay;
      tc_composite_lay[lay-1][hh] = ttc_lay[lay-1][hh];
    }
  } // while
  Zdt[hh] += Za;

  if(Zdt[hh] > Zpf_init[hh])
    Zdt[hh] = Zpf_init[hh];
}

double ClassXG::Interpolated_ttc_lay(double Za, long lay) { //

  if(!thaw_ki_kw_update[hh])
    return (ttc_lay[lay-1][hh]);

  double split = (Za - Zdt[hh])/depths_lay[lay-1][hh];
  if(split >= 1.0)
    split = 1.0;

  double combination = ttc_lay[lay-1][hh] - split*(ttc_lay[lay-1][hh] - ftc_lay[lay-1][hh]); // thawed(18k) to frozen (4k)

  tc_composite2_lay[lay-1][hh] = combination;

  return (combination);
}

double ClassXG::Interpolated_ftc_lay(double Za, long lay) { //

  if(!freeze_kw_ki_update[hh])
    return (ftc_lay[lay-1][hh]);

  double split = (Za - Zdf[hh])/depths_lay[lay-1][hh];
  if(split >= 1.0)
    split = 1.0;

  double combination = ftc_lay[lay-1][hh] + split*(ttc_lay[lay-1][hh] - ftc_lay[lay-1][hh]); // frozen (4k) to thawed(18k)

  tc_composite2_lay[lay-1][hh] = combination;

  return (combination);
}

void ClassXG::find_thaw_D(double dt) { // XG-Algorithm - Thawing - used by init
// solve for Bth from Zdt using Bisection method

  if(dt == 0)
    return;

  for(long B = 1; B < 50000; ++B){
    Bth[hh] = B;
    thaw();
    if(Zdt[hh] > dt || Zdt[hh] >= Zpf_init[hh])
      return;
  }

  string S = string("'") + Name + " (XG)' Zdt too large in hru = " + to_string(hh+1).c_str();
  CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
  LogError(TExcept);
  throw TExcept;
}


void ClassXG::find_freeze_D(double df) { // XG-Algorithm - Thawing - used by init
// solve for Bfr from Zdt using Bisection method

  if(df == 0)
    return;

  for(long B = 1; B < 50000; ++B){
    Bfr[hh] = B;
    freeze();
    if(Zdf[hh] > df || Zdf[hh] >= Zpf_init[hh])
      return;
  }

  string S = string("'") + Name + " (XG)' Zdf too large in hru = " + to_string(hh+1).c_str();
  CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
  LogError(TExcept);
  throw TExcept;
}

void ClassXG::push_front(double D) {

  if(nfront[hh] >= front_size-3){ // space to allocate plus Zdf/Zdt(2 slots) plus top of stack indicator
    string S = string("'") + Name + " (XG)' too many fronts in hru = " + to_string(hh+1).c_str();
    CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
    LogError(TExcept);
    throw TExcept;
  }

  for(long ii = nfront[hh]+1; 2 <= ii ; --ii) // move contents up
    Zd_front_array[ii+1][hh] = Zd_front_array[ii][hh];

  ++nfront[hh];
  Zd_front_array[2][hh] = D; // add new entry
}

double ClassXG::pop_front(void) {

double D = fabs(Zd_front_array[2][hh]); // always positive

  for(long ii = 2; ii < nfront[hh]+1; ++ii) // move contents down
    Zd_front_array[ii][hh] = Zd_front_array[ii+1][hh];

  Zd_front_array[nfront[hh]+1][hh] = 0.0; // clear memory

  --nfront[hh];

  return D;
}

double ClassXG::last_front(void){

  if(!nfront[hh])
    return 0.0;
  else
    return (Zd_front_array[2][hh]);
}

/*double ClassXG::SWE_to_rho(double SWE) { // Pomeroy et al (1998)

// solve for desity from SWE using Bisection method

  double h1 = 0.6, h2 = 8.00, e, h, rho;
  long iter_max = 0;
  do {
    h = (h1 + h2)/2.0; // m
    rho = (450.0 - 204.7/h*(1.0 - exp(-h/0.673)));
    e = rho*h - SWE; // original equation was cm
    if(e < 0)
      h1 += (h2 - h1)/2.0;
    else
      h2 -= (h2 - h1)/2.0;

  } while(fabs(e) > 0.001 && h > 0.601 && ++iter_max < 100); // below 60cm the density is 250 kg/m3

  return rho;
}*/

void ClassXG::finish(bool good) {
  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (XG)'  Zdt     (mm): ").c_str(), Zdt[hh]);
    LogMessageA(hh, string("'" + Name + " (XG)'  Zdf     (mm): ").c_str(), Zdf[hh]);
    LogMessageA(hh, string("'" + Name + " (XG)'  nfront  ()  : ").c_str(), nfront[hh]);
  }
  LogDebug(" ");
}

double ClassXG::get_ftc_lay(long lay){ // unfrozen(thawed) soil to be frozen
  if(calc_coductivity[hh]){
    return (soil_solid_km_ki_lay[lay][hh] - soil_solid_km_lay[lay][hh])*sqr(h2o_lay[lay][hh]/(1000.0*por_lay[lay][hh])) + soil_solid_km_lay[lay][hh];
  }
  else
    return (1.0 - por_lay[lay][hh])*soil_solid_km_lay[lay][hh] + h2o_lay[lay][hh]/1000.0*kw + (por_lay[lay][hh] - h2o_lay[lay][hh]/1000.0)*ka;
}

double ClassXG::get_ttc_lay(long lay){ // frozen soil to be unfrozen(thawed)
  if(calc_coductivity[hh]){
    return  soil_solid_km_lay[lay][hh]*pow(soil_solid_km_ki_lay[lay][hh]/soil_solid_km_lay[lay][hh], h2o_lay[lay][hh]/(1000.0*por_lay[lay][hh]));
  }
  else
    return (1.0 - por_lay[lay][hh])*soil_solid_km_lay[lay][hh] + h2o_lay[lay][hh]/1000.0*ki + (por_lay[lay][hh] - h2o_lay[lay][hh]/1000.0)*ka;
}