// ClassSed_Transport__vr

// Update WS_outflow_mWQ based on van Rijn

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassSed_Transport__vr.h"

using namespace CRHM;





ClassSed_Transport__vr* ClassSed_Transport__vr::klone(string name) const{
  return new ClassSed_Transport__vr(name);
}


void ClassSed_Transport__vr::decl(void) {

  Description = "'Handles the adjustment of sediment yield for channel transport capacity using te Van Rijn method.'";

//  declvar("WS_outflow", TDim::NHRU, "outflow of each RB", "(m^3/int)", &outflow);
//  declvar("WS_outflow_mWQ", TDim::NDEFN, "Concentration: outflow of each RB", "(kg/int)", &outflow_mWQ, &outflow_mWQ_lay, numsubstances);
//  declputvar("*", "WS_outflow", "(m^3/int)", &outflow);
  declgetvar("*", "WS_outflow", "(m^3/int)", &outflow);
  declputvar("*", "WS_outflow_mWQ", "(kg/int)", &outflow_mWQ, &outflow_mWQ_lay);



// Vars for the vanRijn formulation
  declstatvar("pct_sand", TDim::NHRU, "surface velocity for the tilled soil condition", "(m/s)", &pct_sand);


  decllocal(  "sed_diam50",    TDim::NHRU, "nondimensional sediment diameter", "()", &diam50);
  decllocal(  "sed_diam90",    TDim::NHRU, "nondimensional sediment diameter", "()", &diam90);
  decllocal(  "sed_diam_nodim",    TDim::NHRU, "nondimensional sediment diameter", "()", &diam_nodim);
  decllocal(  "sed_tau_crit_nodim",TDim::NHRU, "nondimensional critical shear stress", "()", &tau_crit_nodim);
  declstatvar("sed_bed_flux",      TDim::NHRU, "sediment bed flux", "(m^3/m/int)", &bed_flux);
  declstatvar("sed_tau_b_nodim",   TDim::NHRU, "nondimensional bed shear stress", "(Pa)", &tau_b_nodim);
  declstatvar("sed_tau_b",         TDim::NHRU, "bed shear stress", "(Pa)", &tau_b);
  declstatvar("sed_stream_depth",  TDim::NHRU, "stream depth", "(m)", &stream_depth);

  declstatvar("sedvr_suspended_mass",         TDim::NHRU, "bed shear stress", "(Pa)", &mass_suspended);
  declstatvar("sedvr_bedload_mass",         TDim::NHRU, "bed shear stress", "(Pa)", &mass_bedload);

//  declstatvar("mob_rainsplash",  TDim::NHRU, "Rainsplash mobilized sediment", "(m)", &mob_rainsplash);
//  declstatvar("mob_flow",  TDim::NHRU, "Flow mobilized sediment", "(m)", &mob_flow);
//  declstatvar("sed_delivered_z",  TDim::NHRU, "Flow mobilized sediment", "(m)", &sed_delivered_z);
//  declstatvar("sed_transported_z",  TDim::NHRU, "Flow mobilized sediment", "(m)", &sed_transported_z);


// Parameters for the vanRijn formulation

  declparam("pct_clay", TDim::NHRU, "[33]", "0","100", "Percentage clay", "(%)", &pct_clay);
  declparam("pct_silt", TDim::NHRU, "[33]", "0","100", "Percentage silt", "(%)", &pct_silt);

//  declparam("channel_pct", TDim::NHRU, "[0]", "0","100", "fraction of area containing rills", "()", &channel_pct);
  declparam("channel_width", TDim::NHRU, "[0.1]", "0.1","10", "width of rill channels", "()", &channel_width);   // CRHM specifies slope in degrees
  declparam("channel_slope", TDim::NHRU, "[0.0001]", "0","10", "slope of the rill channels", "()", &channel_slope);   // CRHM specifies slope in degrees
  // check loch et al. 89 for values of mannings n for use in van Rijn
  declparam("vr_mannings_n", TDim::NHRU, "[0.104]", "0","2", "vanrijn mannings n", "()", &vr_mannings_n);
  declparam("vr_roughness_height", TDim::NHRU, "[0.104]", "0","2", "vanrijn roughness height", "(m)", &vr_roughness_height);
  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

}




void ClassSed_Transport__vr::init(void) {
  initialize_VANRIJN();
}


void ClassSed_Transport__vr::run(void) {
  long step = getstep();
  long nstep = step% Global::Freq;

  long Sub = 0;

  for (hh = 0; chkStruct(); ++hh) {  // hh is object scope
    outflow_mWQ_lay[Sub][hh] = calc_vr_load_transport_rect(outflow[hh]);
  }
}

void ClassSed_Transport__vr::finish(bool good) {
}




/*****************************************************************
 * 
 * Particle-size Distribution Routines (Mozaffari 2022)
 * 
******************************************************************/

// Very Coarse Sand Independent
double ClassSed_Transport__vr::calc_vcsi_diam_percentile(double percentile, double pct_sand, double pct_silt) {
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


double ClassSed_Transport__vr::calc_critical_shear_stress_nodim_VANRIJN(double diam_nodim) {
// Taken from Shields curve (Fig. 1) of Van Rijn 1984 Part 1 - Bed load

  double A=0, B=0;  

  if (diam_nodim <= 4) {
      A = 0.24;
      B = -1;
  } else {
    if (diam_nodim <= 10) {
      A = 0.14;
      B = -0.64;
    } else {
      if (diam_nodim <= 20) {
        A = 0.04;
        B = -0.1;
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
      
  return A * pow(diam_nodim, B);
}


/*****************************************************************
 * 
 * van Rijn Bedload Transport Routines
 * 
******************************************************************/


double ClassSed_Transport__vr::calc_nodim_diam( double diam ) {
  return diam * pow( (s-1)*g/(visc*visc), 1.0/3);
}

double ClassSed_Transport__vr::calc_vanrijn_flowdepth_from_manning(double flow_rate) {
//  global mannings_n
  
  double h = pow (1.342281879 * flow_rate * vr_mannings_n[hh] / sqrt(tan(channel_slope[hh])),
                  3.0/8.0);
  return h;
}    
  
double ClassSed_Transport__vr::calc_vanrijn_flowvel_from_flowdepth(double flow_rate, double h) {
  return flow_rate / (h*h);
}

double ClassSed_Transport__vr::calc_bed_shear_stress(double stream_depth) {
  return rho_w * g * stream_depth * tan(channel_slope[hh]);
}

double ClassSed_Transport__vr::calc_nodim_shear_stress( double tau_b ) {
  return tau_b / ( rho_w * (s-1) * g * diam50[hh] );
}

double ClassSed_Transport__vr::calc_dim_bed_flux( double bed_flux_nodim ) {
  return bed_flux_nodim * sqrt( (s-1) * g * pow(diam50[hh], 3) );
}

//def calc_sedconc_from_bedflux( double bedflux, double flow_rate, doube channel_len )


double ClassSed_Transport__vr::VANRIJN( double tau_b_nodim , double tau_crit_nodim, double diam_nodim ) {
    return (0.053 / diam_nodim) * pow(tau_b_nodim/tau_crit_nodim - 1, 2.1);
}


/***************************************************************
 * Van Rijn Bedload transport capacity
*/

double ClassSed_Transport__vr::calc_bedload_transport_cap(double stream_depth) {  // runoff: mm * km^2/int
// Global::Freq: # intervals per day
//  double flow_rate = runoff * 1000 * Global::Freq / 86400.0;  // mm*km^2/int -> m^3/s

//  stream_depth[hh] = calc_vanrijn_flowdepth_from_manning(flow_rate);
  double tau_b = calc_bed_shear_stress( stream_depth);
  double tau_b_nodim = calc_nodim_shear_stress( tau_b );

// Different ways to calculate nondim bed flux from nondim shear stress
  // bed_flux_nodim = NIELSON( tau_b_nodim , tau_crit_nodim)

  if (tau_b_nodim < tau_crit_nodim[hh] ) return 0;

  double bed_flux_nodim = VANRIJN( tau_b_nodim , tau_crit_nodim[hh], diam_nodim[hh]);

  // bed flux (volume rate of transport per unit length of surface[channel] )  [I.e. m2/s]
  double bed_flux = calc_dim_bed_flux( bed_flux_nodim );

  return bed_flux;   // m3/m

//  double channel_len = ( channel_pct[hh] / 100 ) * hru_area[hh] * 1e6;  // (m) [km^2 -> m^2]

//  double mobilized_kg_s = bed_flux[hh] * rho_sed * channel_len * (1.0-scf[hh]);  // kg/s over entire area
//  return mobilized_kg_s * 1000 * 86400.0 / Global::Freq / hru_area[hh];  // return g/km^2/int

}





/***************************************************************
 * Van Rijn Suspended transport capacity
 * (Reminder: hh is at object scope)
*/

double ClassSed_Transport__vr::calc_vr_transport_stage(double streamwidth) {
  double shearvel_crit = sqrt( (s-1)*g*diam50[hh]*tau_crit_nodim[hh] );   // TODO: consider if this value may be different for suspension (PRL)

  double hydraulic_radius__bed = streamwidth;
  double chezy_coef_grains = 18 * log(12*hydraulic_radius__bed /(3*diam90[hh]) );   // Eq. 18
  double shearvel_grains = sqrt(g) / chezy_coef_grains;  // u'*    // Eq. 17
  return (shearvel_grains*shearvel_grains - shearvel_crit*shearvel_crit) / (shearvel_crit*shearvel_crit);   // Van Rijn (84) Eq 2
}

double ClassSed_Transport__vr::calc_vr_ref_level(double streamdepth) {
  // reference level = roughness height if bedform height is not known
  return max(0.01*streamdepth, vr_roughness_height[hh] );
}

double ClassSed_Transport__vr::calc_vr_ref_conc(double ref_level, double transport_stage) {
  return 0.015 * ( diam50[hh] / ref_level ) * ( pow(transport_stage,1.5) / pow(diam_nodim[hh],0.3) );   // van Rijn (84) Eq 38
}

double ClassSed_Transport__vr::calc_vr_diam_susp(double transport_stage) {
  return diam50[hh] * ( 1 + 0.011 * (bed_material_sd - 1) * (transport_stage - 25) );   // van Rijn (84) Eq 39
}

double ClassSed_Transport__vr::calc_vr_fallvel(double transport_stage) {
  double Ds = calc_vr_diam_susp(transport_stage);

  if (diam50[hh] < 100e-6) {
    return (1/18) * ( (s-1) * g * Ds * Ds / visc );  // van Rijn (84) Eq. 11
  }
  if (diam50[hh] < 1000e-6) {
    return 10 * (visc/Ds) * ( sqrt(! + 0.01*(s-1)*g*pow(Ds,3) / (visc*visc)) - 1 );    // van Rijn (84) Eq. 12
  }
  return 1.1 * sqrt( (s-1)*g*Ds );   // van Rijn (84) Eq. 13
}


double ClassSed_Transport__vr::calc_vr_shearvel(double streamdepth) {
  return sqrt(g * streamdepth * tan(channel_slope[hh]) );
}

double ClassSed_Transport__vr::calc_vr_beta_factor(double shearvel, double fallvel) {
  double ttt = fallvel / shearvel;
  ttt = max(0.1,ttt);
  ttt = min(1.0,ttt);
  return 1 + 2*ttt*ttt;   // Van Rijn (84) Eq. 22
}

double ClassSed_Transport__vr::calc_vr_phi_factor(double fallvel, double shearvel, double ref_conc) {
  return 2.5 * pow( (fallvel/shearvel), 0.8) * pow( ( ref_conc/MAX_BEDCONC ), 0.4);
}

double ClassSed_Transport__vr::calc_vr_susp_param(double transport_stage, double shearvel, double ref_conc) {
  double fallvel = calc_vr_fallvel(transport_stage);

  double beta_factor = calc_vr_beta_factor(shearvel, fallvel);
  double phi_factor = calc_vr_phi_factor(fallvel, shearvel, ref_conc);
  double susp_param = fallvel / (beta_factor * von_Karman * shearvel);  // Van Rijn (84) Eq. 3
  return susp_param + phi_factor;
}

double ClassSed_Transport__vr::calc_vr_f_factor(double ref_level, double ref_conc, double streamdepth, double transport_stage) {
  double shearvel = calc_vr_shearvel(streamdepth);

  double a_d = ref_level/streamdepth;
  double susp_param = calc_vr_susp_param(transport_stage, shearvel, ref_conc);   // Z', Eq. 33
  return ( pow(a_d,susp_param) - pow(a_d,1.2) ) / ( pow(1-a_d,susp_param) * (1.2 - susp_param) );  // Van Rijn (84) Eq. 44
}

// This is stream load per unit of stream width
double ClassSed_Transport__vr::calc_vr_susp_load_transport(double streamvel, double streamwidth, double streamdepth) {
  double transport_stage = calc_vr_transport_stage(streamwidth);
  double ref_level = calc_vr_ref_level(streamdepth);
  double ref_conc = calc_vr_ref_conc(ref_level, transport_stage);

  double f_factor = calc_vr_f_factor(ref_level, ref_conc, streamdepth, transport_stage);
  return f_factor * streamvel * streamdepth * ref_conc;
}

double ClassSed_Transport__vr::calc_vr_load_transport_rect(double streamflow ) {
  double flow_rate = streamflow * 1000 * Global::Freq / 86400.0;  // mm*km^2/int -> m^3/s

  double stream_depth = calc_vanrijn_flowdepth_from_manning(flow_rate);

  if (flow_rate == 0) {
    mass_suspended[hh] = 0;
    mass_bedload[hh] = 0;
    return 0;
  }

  mass_suspended[hh] = calc_vr_susp_load_transport(flow_rate/(stream_depth*channel_width[hh]), channel_width[hh], stream_depth);
  mass_bedload[hh] = calc_bedload_transport_cap(stream_depth);
  return mass_suspended[hh] + mass_bedload[hh];
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

void ClassSed_Transport__vr::initialize_VANRIJN() {
  for (long hh = 0; hh < nhru; ++hh) {
    diam50[hh] = 1e-3 * calc_vcsi_diam_percentile(50, pct_sand[hh], pct_silt[hh]);  // mm -> m
    diam90[hh] = 1e-3 * calc_vcsi_diam_percentile(90, pct_sand[hh], pct_silt[hh]);  // mm -> m
    diam_nodim[hh] = calc_nodim_diam(diam50[hh]);
    tau_crit_nodim[hh] = calc_critical_shear_stress_nodim_VANRIJN(diam_nodim[hh]);
  }
}


