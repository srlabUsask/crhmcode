// 11/20/19
//---------------------------------------------------------------------------
#pragma hdrstop

//#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <assert.h>     /* assert */

#include "ClassSed_Detachment__modmmf.h"
#include "../newmodules/NewModules.h"
#include "../../core/GlobalDll.h"


using namespace std;
using namespace CRHM;


// ********* Extra constants:

double visc = 1.004e-6;  // kinematic viscosity coefficient of water (20C)
double g = 9.81;  // gravity (m/s2)
double rho_sed = 2650;  // kg/m3 for quartz
double rho_w = 1000;  // kg/m3 for water
double s = rho_sed / rho_w; 

// bed material sd could be calculated from 0.5 (D84/D50 + D16/D50) if the particle distribution profile was reliable enough
double bed_material_sd = 2.5;   // (sigma_s) From Van Rijn Suspended transport (84), p. 1630-1631
double von_Karman = 0.4;  // von Karman constant for clear flow
//double mannings_n = 0.104;  // check loch et al. 89 for values

// Constants for Van Rijn (suspended transport)
double MAX_BEDCONC = 0.65;

// *******************




ClassSed_Detachment* ClassSed_Detachment::klone(string name) const{
  return new ClassSed_Detachment(name);
}


void ClassSed_Detachment::decl(void) {

  variation_set = VARIATION_ORG;

/*****************************************************************
 * VARIABLES
******************************************************************/

// NOTES: The MMF routines are originally written for SI units (I.e. m^2).
// These units are kept internally within this module and converted to km^2 (the default for CRHM) 
// as the final step in runoff_sed_by_erosion() for inter-module transfer.

//  declgetvar("*", "runoff", "(mm)", &runoff);
  declgetvar("*", "scf", "()", &scf);

  declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);
  declputvar("*", "soil_runoff_mWQ", "(g/m^2/int)", &soil_runoff_mWQ,&soil_runoff_mWQ_lay);

  declstatvar("sedrelpool", TDim::NHRU, "sediment stored in conceptual storage pool", "(g/int)", &sedrelpool);

// Vars for the modified MMF formulation
  declstatvar("pct_sand", TDim::NHRU, "surface velocity for the tilled soil condition", "(m/s)", &pct_sand);

  declstatvar("v_std_bare",TDim::NHRU, "surface velocity for the standard bare soil condition", "(m/s)", &v_std_bare);
  declstatvar("v_actual",  TDim::NHRU, "surface velocity for the 'actual' soil condition", "(m/s)", &v_actual);
  declstatvar("v_veg",     TDim::NHRU, "surface velocity for the vegetated soil condition", "(m/s)", &v_veg);
  declstatvar("v_tillage", TDim::NHRU, "surface velocity for the tilled soil condition", "(m/s)", &v_tillage);

  declstatvar("DEP_immed_c", TDim::NHRU, "Percentage of clay deposited immediately", "(%)", &DEP_immed_c);
  declstatvar("DEP_immed_z", TDim::NHRU, "Percentage of silt deposited immediately", "(%)", &DEP_immed_z);
  declstatvar("DEP_immed_s", TDim::NHRU, "Percentage of sand deposited immediately", "(%)", &DEP_immed_s);
  declstatvar("DEP_channel_c", TDim::NHRU, "Percentage of clay deposited in runoff channel", "(%)", &DEP_channel_c);
  declstatvar("DEP_channel_z", TDim::NHRU, "Percentage of silt deposited in runoff channel", "(%)", &DEP_channel_z);
  declstatvar("DEP_channel_s", TDim::NHRU, "Percentage of sand deposited in runoff channel", "(%)", &DEP_channel_s);

// Vars for the vanRijn formulation
  decllocal(  "sed_diam50",    TDim::NHRU, "nondimensional sediment diameter", "()", &diam50);
  decllocal(  "sed_diam90",    TDim::NHRU, "nondimensional sediment diameter", "()", &diam90);
  decllocal(  "sed_diam_nodim",    TDim::NHRU, "nondimensional sediment diameter", "()", &diam_nodim);
  decllocal(  "sed_tau_crit_nodim",TDim::NHRU, "nondimensional critical shear stress", "()", &tau_crit_nodim);
  declstatvar("sed_bed_flux",      TDim::NHRU, "sediment bed flux", "(m^3/m/int)", &bed_flux);
  declstatvar("sed_tau_b_nodim",   TDim::NHRU, "nondimensional bed shear stress", "(Pa)", &tau_b_nodim);
  declstatvar("sed_tau_b",         TDim::NHRU, "bed shear stress", "(Pa)", &tau_b);
  declstatvar("sed_stream_depth",  TDim::NHRU, "stream depth", "(m)", &stream_depth);

  declstatvar("mob_rainsplash",  TDim::NHRU, "Rainsplash mobilized sediment", "(m)", &mob_rainsplash);
  declstatvar("mob_flow",  TDim::NHRU, "Flow mobilized sediment", "(m)", &mob_flow);
  declstatvar("sed_delivered_z",  TDim::NHRU, "Flow mobilized sediment", "(m)", &sed_delivered_z);
  declstatvar("sed_transported_z",  TDim::NHRU, "Flow mobilized sediment", "(m)", &sed_transported_z);


/*******************
 * PARAMETERS
 *******************/

// Parameters for the HYPE delay pool
// set this as maximum expected water runoff per timestep (mm)
  declparam("sedrelmax", TDim::NHRU, "[20]", "1","1000", "maximum release fraction from the sediment pool", "(mm)", &sedrelmax);
  declparam("sedrelexp", TDim::NHRU, "[1]", "0.1","10", "sedrelexp", "()", &sedrelexp);

//  declparam("cohesion", TDim::NHRU, "[100]", "0","100", "cohesion", "(kPa)", &cohesion);


// Parameters for the modified MMF formulation
  declparam("canopy_cvg", TDim::NHRU, "[0]", "0","100", "Percentage of canopy coverage", "(%)", &canopy_cvg);
  declparam("plant_height", TDim::NHRU, "[1.0]", "0","3", "Plant height", "(m)", &plant_height);
  declparam("ground_cover", TDim::NHRU, "[0.5]", "0","1", "ground cover fraction", "()", &ground_cover);
  declparam("sfcslope", TDim::NHRU, "[0.0001]", "0","10", "slope of the interrills", "()", &sfcslope);   // CRHM specifies slope in degrees
  declparam("slopelen", TDim::NHRU, "[50]", "1","1000", "slope length", "(m)", &slopelen);

  decldiagparam("mmf_d_bare",    TDim::BASIN, "[0.005]", "0","1", "mmf_d_bare",    "(m)", &mmf_d_bare);
// d_actual = 0.005 for unchanneled flow, 0.01 for shallow rills, and 0.25 for deeper rills
  decldiagparam("mmf_d_actual",  TDim::BASIN, "[0.010]", "0","1", "mmf_d_actual",  "(m)", &mmf_d_actual);
  decldiagparam("mmf_d_tillage", TDim::BASIN, "[0.005]", "0","1", "mmf_d_tillage", "(m)", &mmf_d_tillage);

  decldiagparam("mmf_n_bare",    TDim::BASIN, "[0.015]", "0","1", "mmf_n_bare",    "(m)", &mmf_n_bare);
  decldiagparam("mmf_n_actual",  TDim::BASIN, "[0.015]", "0","1", "mmf_n_actual",  "(m)", &mmf_n_actual);
// For tillage, n is calculated from tillage implement roughness table
//  decldiagparam("mmf_n_tillage", TDim::BASIN, "[0.3]", "0","1", "mmf_n_tillage", "(m)", &mmf_n_tillage);


// The default/suggested values for these parameters are based on Quansah 1982
// The value of Kc (clay erodibility) should be treated with care since, as shown by Poesen (1985) and Chisci et al. (1989), the detachability of clay particles has a very high variability
  decldiagparam("erodibility_clay", TDim::BASIN, "[0.1]", "0","1", "erodibility of clay", "(g/J)", &erodibility_clay);
  decldiagparam("erodibility_silt", TDim::BASIN, "[0.5]", "0","1", "erodibility of silt", "(g/J)", &erodibility_silt);
  decldiagparam("erodibility_sand", TDim::BASIN, "[0.3]", "0","1", "erodibility of sand", "(g/J)", &erodibility_sand);

  declparam("pct_clay", TDim::NHRU, "[33]", "0","100", "Percentage clay", "(%)", &pct_clay);
  declparam("pct_silt", TDim::NHRU, "[33]", "0","100", "Percentage silt", "(%)", &pct_silt);

// The default/suggested values for these parameters are based on Quansah 1982
  decldiagparam("detachibility_clay", TDim::BASIN, "[1.0]", "0","3", "detachibility of clay", "(g/J)", &detachibility_clay);
  decldiagparam("detachibility_silt", TDim::BASIN, "[1.6]", "0","3", "detachibility of silt", "(g/J)", &detachibility_silt);
  decldiagparam("detachibility_sand", TDim::BASIN, "[1.5]", "0","3", "detachibility of sand", "(g/J)", &detachibility_sand);

  decldiagparam("mmf_mannings_n", TDim::NHRU, "[0.015]", "0","1", "MMF mannings n", "()", &mmf_mannings_n);
  decldiagparam("mmf_repr_depth", TDim::NHRU, "[0.005]", "0","0.3", "MMF representative depth", "()", &mmf_repr_depth);


// Parameters for the vanRijn formulation
//  declparam("channel_pct", TDim::NHRU, "[0]", "0","100", "fraction of area containing rills", "()", &channel_pct);
  declparam("channel_slope", TDim::NHRU, "[0.0001]", "0","10", "slope of the rill channels", "()", &channel_slope);   // CRHM specifies slope in degrees
  // check loch et al. 89 for values of mannings n for use in van Rijn
  declparam("vr_mannings_n", TDim::NHRU, "[0.104]", "0","2", "vanrijn mannings n", "()", &vr_mannings_n);
  declparam("vr_roughness_height", TDim::NHRU, "[0.104]", "0","2", "vanrijn roughness height", "(m)", &vr_roughness_height);
  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);



  declgetvar("*", "net_rain", "(mm)", &net_rain);

  variation_set = VARIATION_1;

  declgetvar("*", "snowmelt_int", "(mm/int)", &snowmelt_int);

  variation_set = VARIATION_2;

  declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD);

}


void ClassSed_Detachment::init(void) {

  initialize_modMMF();
  initialize_VANRIJN();
}

#define SED_CHANNEL 0

void ClassSed_Detachment::run(void) {
    long step = getstep();
    long nstep = step% Global::Freq;

    if(step == 1) { // begining of run
    }

    dayno = julian("now");

    for(hh = 0; chkStruct(); ++hh){ // Using inhibit is dangerous

// This is just for testing and verification.
// WS_outflow_conc should be approximately the same value at outlet
//        soil_runoff_cWQ_lay[SED_CHANNEL][hh] = 1;   // mg/L
        runoff_sed_by_erosion();

//        soil_runoff_cWQ_lay[SED_CHANNEL][hh] = 0.3;   // mg/L
    }

}


void ClassSed_Detachment::finish(bool good) {
}


/*****************************************************************
 * 
 * HYPE Routines
 * 
******************************************************************/


void ClassSed_Detachment::runoff_sed_by_erosion() {
    double erodingflow;   // Flow eroding the surface


    bed_flux[hh] = 0;   // just for testing

    const double erodedSed = calc_erosion();       // total eroded sediment (g/m2)
    assert(erodedSed >= 0);

    if(soil_runoff[hh] > minFlow_WQ) { // eroded sed goes back to soil if no surface runoff
        sedrelpool[hh] += erodedSed;
    }

    // sediment released from delay pool
    double sedReleased;
    
    if ( sedrelmax[hh] > 0.0) {
      sedReleased = std::fmin(sedrelpool[hh],
                              sedrelpool[hh]* pow(soil_runoff[hh]/sedrelmax[hh], sedrelexp[hh])); // (g/m^2/int) export
    } else {
      sedReleased = sedrelpool[hh];
    }
    sedrelpool[hh] -= sedReleased;

    // sediment concentration for sediment released from delay pool
    if (soil_runoff[hh] > 0) {
//        double newSedConc = sedReleased / soil_runoff[hh];  // kg/(1000m^3) = g/m^3
//        assert(newSedConc >= 0);
//        soil_runoff_cWQ_lay[SED_CHANNEL][hh] = newSedConc;

//        double newSedMass = sedReleased*1e6; // g/m2 -> g/km2
        double newSedMass = sedReleased; 
        assert(newSedMass >= 0);
        soil_runoff_mWQ_lay[SED_CHANNEL][hh] = newSedMass;
    }

}


/*****************************************************************
 * 
 * Modified [or Daily] Morgan-Morgan-Finney Routines
 * 
******************************************************************/


constexpr double ClassSed_Detachment::calc_rainsplash_energy(double intensity) {

// From Marshall and Palmer, suitable for North-western Europe
//    double Kintensity_A = 8.95;
//    double Kintensity_B = 8.44;

// From Laws and Parsons, suitable for North America east of the Rocky Mountains
// Also used in USLE (wischmeier and Smith, 1978)
  double Kintensity_A = 11.87;
  double Kintensity_B = 8.73;

  return Kintensity_A + Kintensity_B*log10(intensity);
}


void ClassSed_Detachment::calc_rainsplash_mobilization( sed_triple &rslt) {

  if(net_rain[hh] <= 5.0/Global::Freq) {     // TODO: shorter timestep, other threshold?
    rslt.c = 0;
    rslt.z = 0;
    rslt.s = 0;

    mob_rainsplash[hh] = 0;  // DEBUGGING
    return;
  }

  const double KE_throughfall = calc_rainsplash_energy(net_rain[hh]);
  const double KE_leaf_drainage = max(0.0, (15.8*pow(plant_height[hh],0.5)-5.87) );
  const double cvg_frac = canopy_cvg[hh]/100;
  const double imed = (cvg_frac*KE_leaf_drainage + (1-cvg_frac)*KE_throughfall) * net_rain[hh] * (1.0-scf[hh]);
  assert(imed >= 0);
  rslt.c = erodibility_clay[0] * (pct_clay[hh]/100) * imed;  // (g/J) * (%/100) * (J/m2)
  rslt.z = erodibility_silt[0] * (pct_silt[hh]/100) * imed;  // (g/J) * (%/100) * (J/m2)
  rslt.s = erodibility_sand[0] * (pct_sand[hh]/100) * imed;  // (g/J) * (%/100) * (J/m2)

  mob_rainsplash[hh] = rslt.z;   // DEBUGGING

  return;
}



void ClassSed_Detachment::calc_flow_mobilization(double runoff, sed_triple &rslt) {

  double common_groundcover = 0.0f;

//TODO: readd stones (ST)
  const double imed = pow(runoff, 1.5) * (1-(ground_cover[hh])) * pow(sin(sfcslope[hh]), 0.3) * (1.0-scf[hh]);
  rslt.c = detachibility_clay[0] * (pct_clay[hh]/100) * imed;
  rslt.z = detachibility_silt[0] * (pct_silt[hh]/100) * imed;
  rslt.s = detachibility_sand[0] * (pct_sand[hh]/100) * imed;

  mob_flow[hh] = rslt.z;   // DEBUGGING

}


// These functions rely on module parameters (not constexpr)
double ClassSed_Detachment::calc_flowvel_manning(double depth, double n) {
  if (channel_slope[hh] <= 0.0) {
    CRHMException TExcept("Sed_Detachment: channel slope must be greater than zero", TExcept::TERMINATE);
    LogError(TExcept);
  }
  return pow(depth, 0.667) * pow(channel_slope[hh], 0.5) / n;
}
double ClassSed_Detachment::calc_flowvel_veg() {
  // TODO: make this configurable
  const double stem_diam = 0.015;  // (cm)
  const double stem_count = 800;  // count per square meter (m-2)

  if (sfcslope[hh] <= 0.0) {
    CRHMException TExcept("Sed_Detachment: surface slope must be greater than zero", TExcept::TERMINATE);
    LogError(TExcept);
  }

  // Slope as a rise over run fraction
  double slope_rr = tan(sfcslope[hh]);
  return pow(2*g/(stem_diam*stem_count), 0.5) * pow(slope_rr, 0.5);
}
double ClassSed_Detachment::calc_tillage_n() {
  // TODO: fix this later
  const double RFR = 15;   // (m/m)
  return exp(-2.1132 + 0.0349*RFR);
}



void ClassSed_Detachment::calc_flow_deposition( bool mixed_sed, sed_triple &rslt) {

// These values are from Modified MMF paper
  const double v_s_c = 2e-6;  // (m/s)
  const double v_s_z = 2e-3;  // (m/s)
  const double v_s_s = 2e-2;  // (m/s)

/* Explanation of the scale factor scl;
When applying these equations to deposition from runoff on hillslopes, the settling velocities used
earlier to describe deposition of particles immediately following their detachment by raindrop impact and runoff
need to be modified because the effective settling velocities for mixed particle sizes falling out of runoff in a
depositional environment are often much higher than those in sediment-free water (Zaneveld et al., 1982; Lovell
and Rose, 1991; Rose et al., 2003). They approach the maximum value of the distribution of settling velocities for
the particle size distribution of a given soil (Misra and Rose, 1991). A simple increase in value of the settling
velocities by an order of magnitude is used here to bring them in line with those obtained experimentally for
multi-particle sediments (Lovell and Rose, 1988; Hogarth et al., 2004). 
*/
  const double scl = (mixed_sed) ? 10.0 : 1.0;

  const double imed = slopelen[hh] / (v_std_bare[hh]*mmf_repr_depth[hh]);

  //  v_std is that for either the bare soil or vegetated condition
  rslt.c = min(100.0, 44.1 * pow( v_s_c*scl * imed , 0.29 ) );
  rslt.z = min(100.0, 44.1 * pow( v_s_z*scl * imed , 0.29 ) );
  rslt.s = min(100.0, 44.1 * pow( v_s_s*scl * imed , 0.29 ) );
}



void ClassSed_Detachment::calc_delivered_to_transport(sed_triple &rslt) {   // g/m2
  static sed_triple detached_rain;
  static sed_triple detached_flow;
//  static sed_triple deposited_pct;

  calc_rainsplash_mobilization(detached_rain);
  calc_flow_mobilization(soil_runoff[hh], detached_flow);
//  calc_flow_deposition(false, deposited_pct);  // not mixed sed because it occurs at the detachment site
  rslt.c = (detached_rain.c + detached_flow.c) * ( 1.0 - (DEP_immed_c[hh]/100) ); // + UPSLOPE!
  rslt.z = (detached_rain.z + detached_flow.z) * ( 1.0 - (DEP_immed_z[hh]/100) ); // + UPSLOPE!
  rslt.s = (detached_rain.s + detached_flow.s) * ( 1.0 - (DEP_immed_s[hh]/100) ); // + UPSLOPE!

  sed_delivered_z[hh] = rslt.z;  // DEBUGGING
}


void ClassSed_Detachment::calc_transport_capacity(sed_triple &rslt) {

  const double Q = soil_runoff[hh]*1000; // mm*km2 -> m3
  const double imed = (v_actual[hh]*v_veg[hh]*v_tillage[hh]/ pow(v_std_bare[hh],3) ) * Q * Q * sin(channel_slope[hh]);

// Why is transport capacity dependent on percentage of sediment type?
  rslt.c = imed * (pct_clay[hh]/100);
  rslt.z = imed * (pct_silt[hh]/100);
  rslt.s = imed * (pct_sand[hh]/100);

}


void ClassSed_Detachment::calc_mmf_sed_balance(sed_triple &rslt) {   // g/m2
  static sed_triple delivered;
  static sed_triple transport_cap;
//  static sed_triple deposited_pct;

  calc_delivered_to_transport(delivered);
  calc_transport_capacity(transport_cap);
//  calc_flow_deposition(true, deposited_pct);  // mixed sed because it occurs in the channel

  if (delivered.c <= transport_cap.c) {
    rslt.c = delivered.c;
  } else {
    rslt.c = max(transport_cap.c, delivered.c * (1 - DEP_channel_c[hh]/100) );
  }

  if (delivered.z <= transport_cap.z) {
    rslt.z = delivered.z;
  } else {
    rslt.z = max(transport_cap.z, delivered.z * (1 - DEP_channel_z[hh]/100) );
  }

  if (delivered.s <= transport_cap.s) {
    rslt.s = delivered.s;
  } else {
    rslt.s = max(transport_cap.s, delivered.s * (1 - DEP_channel_s[hh]/100) );
  }

  sed_transported_z[hh] = rslt.z; // DEBUGGING
}



double ClassSed_Detachment::calc_erosion() {   // g/m2

  sed_triple rslt = {0,0,0};
  calc_mmf_sed_balance(rslt);
  return rslt.c + rslt.z + rslt.s;

}


void ClassSed_Detachment::initialize_modMMF() {
  for (long hh = 0; hh < nhru; ++hh) {
    pct_sand[hh] = 100 - (pct_clay[hh] + pct_silt[hh]);
    assert(pct_clay[hh] >= 0);
    assert(pct_silt[hh] >= 0);
    assert(pct_sand[hh] >= 0);

    v_std_bare[hh] = calc_flowvel_manning(mmf_d_bare[0], mmf_n_bare[0]);
    v_actual[hh] = calc_flowvel_manning(mmf_d_actual[0], mmf_n_actual[0]);
    v_veg[hh] = calc_flowvel_veg();
    double mmf_n_tillage = calc_tillage_n();
    v_tillage[hh] = calc_flowvel_manning(mmf_d_tillage[0], mmf_n_tillage);

    sed_triple dep_immed;
    calc_flow_deposition(false, dep_immed);
    DEP_immed_c[hh] = dep_immed.c;
    DEP_immed_z[hh] = dep_immed.z;
    DEP_immed_s[hh] = dep_immed.s;

    sed_triple dep_channel;
    calc_flow_deposition(true, dep_channel);
    DEP_channel_c[hh] = dep_channel.c;
    DEP_channel_z[hh] = dep_channel.z;
    DEP_channel_s[hh] = dep_channel.s;

  }
}


/*****************************************************************
 * 
 * Particle-size Distribution Routines (Mozaffari 2022)
 * 
******************************************************************/

// Very Coarse Sand Independent
double ClassSed_Detachment::calc_vcsi_diam_percentile(double percentile, double pct_sand, double pct_silt) {
  double a = 0.088 * pct_silt - 0.255 * pct_sand;   // Mozaffari (2022) Eq. 19
  double b = a - 0.481 * pct_sand;  // Mozaffari (2022) Eq. 20
  double c = -0.09*a - 0.3 *b;   // Mozaffari (2022) Eq. 21
  double d = 100;  // Mozaffari (2022) Eq. 22

  // Solve Mozaffari (2022) Eq. 2 using Newton's Method
  double diam = 1.0e-6;
  for (int i=0; i<5; i++) {
    double f_x = a*pow(log10(diam),3) + b*pow(log10(diam),2) + c*log10(diam) + d - percentile;
    double df_x = (1/(diam*log(10))) * ( 3*a*pow(log10(diam),2) + 2*b*log10(diam) + c);
    if (df_x == 0) df_x = 1e-10;
    diam = diam - f_x/df_x;
    if (diam > 0.2) diam = 0.2;
    if (diam < 0.0001) diam = 0.0001;
  }

  return diam;
}


/*****************************************************************
 * 
 * van Rijn Support Routines
 * 
******************************************************************/


double ClassSed_Detachment::calc_critical_shear_stress_nodim_VANRIJN(double diam_nodim) {
  double A=0, B=0;  

  if (diam_nodim <= 4) {
      A = 0.24;
      B = 1;
  } else {
    if (diam_nodim <= 10) {
      A = 0.14;
      B = 0.64;
    } else {
      if (diam_nodim <= 20) {
        A = 0.04;
        B = 0.1;
      } else {
        if (diam_nodim <= 150) {
          A = 0.013;
          B = 0.29;
        } else {
          A = 0.056;
          B = 0;
        }
      }
    }
  }
      
  return A * pow(diam_nodim, -B);
}


/*****************************************************************
 * 
 * van Rijn Bedload Transport Routines
 * 
******************************************************************/


double ClassSed_Detachment::calc_nodim_diam( double diam ) {
  return diam * pow( (s-1)*g/(visc*visc), 1.0/3);
}

double ClassSed_Detachment::calc_vanrijn_flowdepth_from_manning(double flow_rate) {
//  global mannings_n
  
  double h = pow (1.342281879 * flow_rate * vr_mannings_n[hh] / sqrt(tan(channel_slope[hh])),
                  3.0/8.0);
  return h;
}    
  
double ClassSed_Detachment::calc_vanrijn_flowvel_from_flowdepth(double flow_rate, double h) {
  return flow_rate / (h*h);
}

double ClassSed_Detachment::calc_bed_shear_stress(double stream_depth) {
  return rho_w * g * stream_depth * tan(channel_slope[hh]);
}

double ClassSed_Detachment::calc_nodim_shear_stress( double tau_b ) {
  return tau_b / ( rho_w * (s-1) * g * diam50[hh] );
}

double ClassSed_Detachment::calc_dim_bed_flux( double bed_flux_nodim ) {
  return bed_flux_nodim * sqrt( (s-1) * g * pow(diam50[hh], 3) );
}

//def calc_sedconc_from_bedflux( double bedflux, double flow_rate, doube channel_len )


double ClassSed_Detachment::VANRIJN( double tau_b_nodim , double tau_crit_nodim, double diam_nodim ) {
    return (0.053 / diam_nodim) * pow(tau_b_nodim/tau_crit_nodim - 1, 2.1);
}


/***************************************************************
 * Van Rijn Bedload transport capacity
*/

double ClassSed_Detachment::calc_bedload_transport_cap(double runoff) {  // runoff: mm * km^2/int
// Global::Freq: # intervals per day
  double flow_rate = runoff * 1000 * Global::Freq / 86400.0;  // mm*km^2/int -> m^3/s

  stream_depth[hh] = calc_vanrijn_flowdepth_from_manning(flow_rate);
  tau_b[hh] = calc_bed_shear_stress( stream_depth[hh]);
  tau_b_nodim[hh] = calc_nodim_shear_stress( tau_b[hh] );

// Different ways to calculate nondim bed flux from nondim shear stress
  // bed_flux_nodim = NIELSON( tau_b_nodim , tau_crit_nodim)

  if (tau_b_nodim[hh] < tau_crit_nodim[hh] ) return 0;

  double bed_flux_nodim = VANRIJN( tau_b_nodim[hh] , tau_crit_nodim[hh], diam_nodim[hh]);

  // bed flux (volume rate of transport per unit length of surface[channel] )  [I.e. m2/s]
  bed_flux[hh] = calc_dim_bed_flux( bed_flux_nodim );

  return bed_flux[hh];   // m3/m

//  double channel_len = ( channel_pct[hh] / 100 ) * hru_area[hh] * 1e6;  // (m) [km^2 -> m^2]

//  double mobilized_kg_s = bed_flux[hh] * rho_sed * channel_len * (1.0-scf[hh]);  // kg/s over entire area
//  return mobilized_kg_s * 1000 * 86400.0 / Global::Freq / hru_area[hh];  // return g/km^2/int

}





/***************************************************************
 * Van Rijn Suspended transport capacity
*/

  double ClassSed_Detachment::calc_vr_transport_stage(double streamwidth) {
    double shearvel_crit = sqrt( (s-1)*g*diam50[hh]*tau_crit_nodim[hh] );   // TODO: consider if this value may be different for suspension (PRL)

    double hydraulic_radius__bed = streamwidth;
    double chezy_coef_grains = 18 * log(12*hydraulic_radius__bed /(3*diam90[hh]) );
    double shearvel_grains = sqrt(g) / chezy_coef_grains;  // u'*
    return (shearvel_grains*shearvel_grains - shearvel_crit*shearvel_crit) / (shearvel_crit*shearvel_crit);   // Van Rijn (84) Eq 2
  }

  double ClassSed_Detachment::calc_vr_ref_level(double streamdepth) {
    // reference level = roughness height if bedform height is not known
    return max(0.01*streamdepth, vr_roughness_height[hh] );
  }

  double ClassSed_Detachment::calc_vr_ref_conc(double ref_level, double transport_stage) {
    return 0.015 * ( diam50[hh] / ref_level ) * ( pow(transport_stage,1.5) / pow(diam_nodim[hh],0.3) );   // van Rijn (84) Eq 38
  }

  double ClassSed_Detachment::calc_vr_diam_susp(double transport_stage) {
    return diam50[hh] * ( 1 + 0.011 * (bed_material_sd - 1) * (transport_stage - 25) );   // van Rijn (84) Eq 39
  }

  double ClassSed_Detachment::calc_vr_fallvel(double transport_stage) {
    double Ds = calc_vr_diam_susp(transport_stage);

    if (diam50[hh] < 100e-6) {
      return (1/18) * ( (s-1) * g * Ds * Ds / visc );  // van Rijn (84) Eq. 11
    }
    if (diam50[hh] < 1000e-6) {
      return 10 * (visc/Ds) * ( sqrt(! + 0.01*(s-1)*g*pow(Ds,3) / (visc*visc)) - 1 );    // van Rijn (84) Eq. 12
    }
    return 1.1 * sqrt( (s-1)*g*Ds );   // van Rijn (84) Eq. 13
  }


  double ClassSed_Detachment::calc_vr_shearvel(double streamdepth) {
    return sqrt(g * streamdepth * tan(channel_slope[hh]) );
  }

  double ClassSed_Detachment::calc_vr_beta_factor(double shearvel, double fallvel) {
    double ttt = fallvel / shearvel;
    ttt = max(0.1,ttt);
    ttt = min(1.0,ttt);
    return 1 + 2*ttt*ttt;   // Van Rijn (84) Eq. 22
  }

  double ClassSed_Detachment::calc_vr_phi_factor(double fallvel, double shearvel, double ref_conc) {
    return 2.5 * pow( (fallvel/shearvel), 0.8) * pow( ( ref_conc/MAX_BEDCONC ), 0.4);
  }

  double ClassSed_Detachment::calc_vr_susp_param(double transport_stage, double shearvel, double ref_conc) {
    double fallvel = calc_vr_fallvel(transport_stage);

    double beta_factor = calc_vr_beta_factor(shearvel, fallvel);
    double phi_factor = calc_vr_phi_factor(fallvel, shearvel, ref_conc);
    double susp_param = fallvel / (beta_factor * von_Karman * shearvel);  // Van Rijn (84) Eq. 3
    return susp_param + phi_factor;
  }

  double ClassSed_Detachment::calc_vr_f_factor(double ref_level, double ref_conc, double streamdepth, double transport_stage) {
    double shearvel = calc_vr_shearvel(streamdepth);

    double a_d = ref_level/streamdepth;
    double susp_param = calc_vr_susp_param(transport_stage, shearvel, ref_conc);   // Z', Eq. 33
    return ( pow(a_d,susp_param) - pow(a_d,1.2) ) / ( pow(1-a_d,susp_param) * (1.2 - susp_param) );  // Van Rijn (84) Eq. 44
  }

  // This is stream load per unit of stream width
  double ClassSed_Detachment::calc_vr_susp_load_transport(double streamvel, double streamwidth, double streamdepth) {
    double transport_stage = calc_vr_transport_stage(streamwidth);
    double ref_level = calc_vr_ref_level(streamdepth);
    double ref_conc = calc_vr_ref_conc(ref_level, transport_stage);

    double f_factor = calc_vr_f_factor(ref_level, ref_conc, streamdepth, transport_stage);
    return f_factor * streamvel * streamdepth * ref_conc;
  }


  // beta is sediment diffusivity coefficient
//  double susp_load_transport = calc_vr_susp_load_transport();



/*
1. compute particle diameter, D# by Eq. 1
2. compute critical bed-shear velocity according to Shields, u* iCr
3. compute transport stage parameter, T by Eq. 2
4. compute reference level, a by Eq. 37
5. compute reference concentration, c„ by Eq. 38
6. compute particle size of suspended sediment, Ds by Eq. 39
7. compute fall velocity of suspended sediment, ws by Eqs. 11, 12 or 13
8. compute beta-factor by Eq. 22
9. compute overall bed-shear velocity, «* = (gdS)05
10. compute (p-factor by Eq. 34
11. compute suspension parameter Z and Z ' by Eqs. 3 and 33
12. compute F-factor by Eq. 44
13. compute suspended load transport, qs by Eq. 43
*/


/***************************************************************
 * Support routines
*/

void ClassSed_Detachment::initialize_VANRIJN() {
  for (long hh = 0; hh < nhru; ++hh) {
    diam50[hh] = 1e-3 * calc_vcsi_diam_percentile(50, pct_sand[hh], pct_silt[hh]);  // mm -> m
    diam90[hh] = 1e-3 * calc_vcsi_diam_percentile(90, pct_sand[hh], pct_silt[hh]);  // mm -> m
    diam_nodim[hh] = calc_nodim_diam(diam50[hh]);
    tau_crit_nodim[hh] = calc_critical_shear_stress_nodim_VANRIJN(diam_nodim[hh]);
  }
}


