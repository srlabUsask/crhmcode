// ClassSed_Transport__vr07

// Update WS_outflow_mWQ based on van Rijn

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassSed_Transport__vr07.h"

using namespace CRHM;





ClassSed_Transport__vr07* ClassSed_Transport__vr07::klone(string name) const{
  return new ClassSed_Transport__vr07(name);
}


void ClassSed_Transport__vr07::decl(void) {

  Description = "'Handles the adjustment of sediment yield for channel transport capacity using the Van Rijn method, 2007 formulation.'";

  variation_set = VARIATION_ORG;

// Vars for the vanRijn formulation
//  declstatvar("pct_sand", TDim::NHRU, "surface velocity for the tilled soil condition", "(m/s)", &pct_sand);
  declstatvar("pct_sand", TDim::NHRU, "Percentage of sand", "()", &pct_sand);


  decllocal(  "sed_diam50",    TDim::NHRU, "50th percentile sediment diameter", "()", &diam50);
  decllocal(  "sed_diam90",    TDim::NHRU, "90th percentile sediment diameter", "()", &diam90);
//  decllocal(  "sed_diam_nodim",    TDim::NHRU, "nondimensional sediment diameter", "()", &diam_nodim);
  decllocal(  "sed_tau_crit_nodim",TDim::NHRU, "nondimensional critical shear stress", "()", &tau_crit_nodim);
  declstatvar("sed_bed_flux",      TDim::NHRU, "sediment bed flux", "(m^3/m/int)", &bed_flux);
  declstatvar("sed_tau_b_nodim",   TDim::NHRU, "nondimensional bed shear stress", "(Pa)", &tau_b_nodim);
  declstatvar("sed_tau_b",         TDim::NHRU, "bed shear stress", "(Pa)", &tau_b);
  declstatvar("sed_stream_depth",  TDim::NHRU, "stream depth", "(m)", &stream_depth);
  declstatvar("sed_stream_width",  TDim::NHRU, "stream width", "(m)", &stream_width);

  declstatvar("sedvr_suspended_mass",         TDim::NHRU, "suspended mass flux", "(kg/s)", &mass_suspended);
  declstatvar("sedvr_bedload_mass",         TDim::NHRU, "bedload mass flux", "(kg/s)", &mass_bedload);
  declstatvar("sedvr_outflow_mWQ",  TDim::NDEFN, "van Rijn total mass flux", "(g/int)", &sedvr_outflow_mWQ, &sedvr_outflow_mWQ_lay);

//  declstatvar("mob_rainsplash",  TDim::NHRU, "Rainsplash mobilized sediment", "(m)", &mob_rainsplash);
//  declstatvar("mob_flow",  TDim::NHRU, "Flow mobilized sediment", "(m)", &mob_flow);
//  declstatvar("sed_delivered_z",  TDim::NHRU, "Flow mobilized sediment", "(m)", &sed_delivered_z);
//  declstatvar("sed_transported_z",  TDim::NHRU, "Flow mobilized sediment", "(m)", &sed_transported_z);


// Parameters for the vanRijn formulation

  declparam("pct_clay", TDim::NHRU, "[10]", "0","100", "Percentage clay", "(%)", &pct_clay);
  declparam("pct_silt", TDim::NHRU, "[40]", "0","100", "Percentage silt", "(%)", &pct_silt);

//  declparam("channel_pct", TDim::NHRU, "[0]", "0","100", "fraction of area containing rills", "()", &channel_pct);
  declparam("channel_width", TDim::NHRU, "[0.1]", "0.1","10", "width of rill channels", "()", &channel_width);   // CRHM specifies slope in degrees
  declparam("channel_slope", TDim::NHRU, "[0.0001]", "0","10", "slope of the channels", "()", &channel_slope);   // CRHM specifies slope in degrees

  declparam("Channel_shp", TDim::NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &route_Cshp);

// sidewall angle is in degrees, used if v-channel shape is specified
  declparam("sidewall_angle", TDim::NHRU, "[10]", "0","90", "anglular slope of the channel sidewalls for triangular channels", "()", &sidewall_angle);   // CRHM specifies slope in degrees
  // check loch et al. 89 for values of mannings n for use in van Rijn
  declparam("vr_mannings_n", TDim::NHRU, "[0.104]", "0","2", "vanrijn mannings n", "()", &vr_mannings_n);
  // For choosing roughness, can refer to fig. 4 of [ van Rijn 2007, bedload ], or formulation
  // TODO: This is not used
  declparam("vr_roughness_height", TDim::NHRU, "[0.1]", "0","2", "vanrijn roughness height", "(m)", &vr_roughness_height);

// Critical velocity is usually between 0.25 and 0.5
// Set to 0.0 to calculate critical velocity using van Rijn (2007) formulation (based on Shields diagram)
  declparam("u_crit", TDim::NHRU, "[0.0]", "0.0", "1.0", "Critical velocity", "(m/s)", &u_crit);

  declparam("Nf", TDim::NHRU, "[0.3]", "0.0", "1.0", "Particle fall number", "(m/s)", &Nf);


  variation_set = VARIATION_1;   // Use this variation with REWs

// Correcting for channel frozen / unfrozen status
  scfCnt = declgrpvar("SCF_ALL", "scf", "query variable = 'scf'", "()", &scf_rew, &scf_All);


//  declvar("WS_outflow", TDim::NHRU, "outflow of each RB", "(m^3/int)", &outflow);
//  declvar("WS_outflow_mWQ", TDim::NDEFN, "Concentration: outflow of each RB", "(kg/int)", &outflow_mWQ, &outflow_mWQ_lay, numsubstances);
//  declputvar("*", "WS_outflow", "(m^3/int)", &outflow);
  declgetvar("*", "WS_outflow", "(m^3/int)", &outflow);
  declputvar("*", "WS_outflow_mWQ", "(g/int)", &outflow_mWQ, &outflow_mWQ_lay);



  variation_set = VARIATION_2;    // Use this variation with Netroute

  declgetvar("*", "scf", "()", &scf_netroute);

  declgetvar("*", "outflow", "(m^3/int)", &outflow);
  declputvar("*", "outflow_mWQ", "(g/int)", &outflow_mWQ, &outflow_mWQ_lay);


}




void ClassSed_Transport__vr07::init(void) {
  initialize_VANRIJN();
}


void ClassSed_Transport__vr07::run(void) {
  long step = getstep();
  long nstep = step% Global::Freq;

  long Sub = 0;

  for (hh = 0; chkStruct(); ++hh) {  // hh is object scope
    double vr_massflux = calc_vr_load_transport(outflow[hh]);   // g/int
    outflow_mWQ_lay[Sub][hh] = Nf[hh]*vr_massflux + (1.0-Nf[hh])*outflow_mWQ_lay[Sub][hh];
    sedvr_outflow_mWQ_lay[Sub][hh] = vr_massflux;
  }
}

void ClassSed_Transport__vr07::finish(bool good) {
}




/*****************************************************************
 * 
 * Particle-size Distribution Routines (Mozaffari 2022)
 * 
******************************************************************/

#define MIN_DIAM_MM 1.0e-2

// Very Coarse Sand Independent
// Returns percentile diameter in mm
double ClassSed_Transport__vr07::calc_vcsi_diam_percentile(double percentile, double pct_sand, double pct_silt) {
  double a = 0.088 * pct_silt - 0.255 * pct_sand;   // Mozaffari (2022) Eq. 19
  double b = a - 0.481 * pct_sand;  // Mozaffari (2022) Eq. 20
  double c = -0.09*a - 0.3 *b;   // Mozaffari (2022) Eq. 21
  double d = 100;  // Mozaffari (2022) Eq. 22

  // Solve Mozaffari (2022) Eq. 2 using Newton's Method
  // This diameter is in mm
  double diam = MIN_DIAM_MM;
  for (int i=0; i<5; i++) {
    double f_x = a*pow(log10(diam),3) + b*pow(log10(diam),2) + c*log10(diam) + d - percentile;
    double df_x = (1/(diam*log(10))) * ( 3*a*pow(log10(diam),2) + 2*b*log10(diam) + c);
    if (df_x == 0) df_x = 1e-10;
    diam = diam - f_x/df_x;
    if (diam > 2.0) diam = 2.0;
    if (diam < MIN_DIAM_MM) diam = MIN_DIAM_MM;
  }

  return diam;
}


/*****************************************************************
 * 
 * van Rijn Support Routines
 * 
******************************************************************/


double ClassSed_Transport__vr07::calc_critical_shear_stress_nodim(double diam_nodim) {
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


double ClassSed_Transport__vr07::calc_critical_velocity(double d50, double d90, double streamdepth) {   // d50 (m), d90 (m), streamdepth (m)
// van Rijn (2007) specifies log(), but HECRAS clarifies that this should be log10
  if (d50 < 0.0005) {
    return 0.19 * pow(d50,0.1) * log10(12*streamdepth/(3*d90));
  } else {
    return 8.5 * pow(d50,0.6) * log10(12*streamdepth/(3*d90));   // valid up to 0.002 m (2mm) 
  }
}


/*****************************************************************
 * 
 * van Rijn Bedload Transport Routines
 * 
******************************************************************/


double ClassSed_Transport__vr07::calc_nodim_diam( double diam ) {
  return diam * pow( (s-1)*g/(visc*visc), 1.0/3);
}


double ClassSed_Transport__vr07::calc_flowdepth_from_manning__rect(double flow_rate) {  // flow_rate (m3/s)
//  global mannings_n
  
//  double h = pow (1.342281879 * flow_rate * vr_mannings_n[hh] / sqrt(tan(channel_slope[hh])),
//                  3.0/8.0);

// This assumes a very wide channel (w >> h)
//  double S = channel_slope[hh];   // tan(channel_slope[hh]);
// Assume slope is m/m
  double S = channel_slope[hh];   // tan(channel_slope[hh]);
  double base = flow_rate * vr_mannings_n[hh] / (sqrt(S) * channel_width[hh]);
  double h = pow ( base, 3.0/5.0 );

  return h;
}    


double ClassSed_Transport__vr07::calc_flowdepth_from_manning__Vchannel(double flow_rate) {
//  global mannings_n
  
//  double h = pow (1.342281879 * flow_rate * vr_mannings_n[hh] / sqrt(tan(channel_slope[hh])),
//                  3.0/8.0);

// This assumes a very wide channel (w >> h)
//  double S = channel_slope[hh];   // tan(channel_slope[hh]);
// Assume slope is m/m
  double S = channel_slope[hh];   // tan(channel_slope[hh]);
  double alpha = sidewall_angle[hh]*M_PI/180;
  double h = pow( 
                  flow_rate * vr_mannings_n[hh] * 
                  tan(alpha) * pow(S,-0.5) * 
                  pow(cos(alpha)/2, -2/3) , 3.0/8.0);

  return h;
}    


double ClassSed_Transport__vr07::calc_flowwidth_from_flowdepth__Vchannel(double flow_depth) {
  double alpha = sidewall_angle[hh]*M_PI/180;
  return flow_depth / tan(alpha);
}


/***************************************************************
 * Van Rijn Bedload transport capacity
*/

// This is stream load per unit of stream width (kg/s/m)
double ClassSed_Transport__vr07::calc_bedload_transport_cap_eq10(
  double streamvel,   // m/s
  double streamwidth,   // m
  double streamdepth)   // m
   {  // runoff: mm * km^2/int

  // f_silt: silt factor ( fsilt=1 for d50 / dsand )

  double diam90_t = diam90[hh];
  double diam50_t = diam50[hh];

  double f_silt = max(1.0, diam_sand/diam50_t); // should actually be d_sand / d_50
  
  double k_s_grain = 3*diam90_t;
  
//  if (12 * streamdepth / k_s_grain < 1) {
  if (12 * streamdepth / k_s_grain < 2) {
    return 0;
  }
  
  double fp_c = 8*g / sqr( 18 * log10( 12 * streamdepth / k_s_grain) );
//  printf("%f %f\n", streamdepth, k_s_grain);
  double fp_cw = bedload_beta * fp_c;
  // taup_b: instantaneous grain-related bed-shear stress    
  double taup_b = rho_w * fp_cw * sqr(streamvel) / 2;
//  printf("%f %f %f\n", taup_b, fp_cw, streamvel);
  double diam_nodim_t = calc_nodim_diam(diam50_t);
  double tau_crit_nodim = calc_critical_shear_stress_nodim(diam_nodim_t);

  if (taup_b < tau_crit_nodim) {
    return 0;
  }
  
  // Eq 10 (2007)
  double rho = rho_sed - rho_w;
//  printf("%f %f %f %f %f %f %f %f\n", bedload_gamma, f_silt, diam50_t, diam_nodim_t, taup_b, tau_crit_nodim, rho, bedload_nu);
  double q_b__vol = bedload_gamma * f_silt * diam50_t * pow(diam_nodim_t, -0.3) * sqrt(taup_b/rho) * \
              pow( (taup_b-tau_crit_nodim)/tau_crit_nodim , bedload_nu );

// Eq 12 (2007, bedload)
//  double q_b__vol = bedload_gamma * f_silt * diam50_t * pow(diam_nodim_t, -0.3) * sqrt(taup_b/rho) * \
//              pow( (taup_b-tau_crit_nodim)/tau_crit_nodim , bedload_nu );


//  assert(taup_b < 1e1);

  return q_b__vol;

/*
  double q_b;
  if (result_as_mass) {
      q_b = q_v__vol * rho_sed;
  } else {
      q_b = q_b__vol;
  }
  return q_b;
*/

}


// This is stream load per unit of stream width (kg/s/m)
double ClassSed_Transport__vr07::calc_bedload_transport_cap_eq12(
  double streamvel,   // m/s
  double streamwidth,   // m
  double streamdepth)   // m
   {  // runoff: mm * km^2/int

  // f_silt: silt factor ( fsilt=1 for d50 / dsand )

  double diam90_t = diam90[hh];  // m
  double diam50_t = diam50[hh];  // m

  // v: depth-averaged velocity
  // v_cr: critical depth-averaged velocity

  double u_crit_t;
  if (u_crit[hh] == 0.0) {
    u_crit_t = calc_critical_velocity(diam50_t, diam90_t, streamdepth); 
  } else {
    u_crit_t = u_crit[hh];
  }

  double M_e = (streamvel - u_crit_t) / sqrt((s - 1) * g * diam50_t);
  if (M_e < 0) {
//    printf("below thresh %f %f\n", streamvel, u_crit_t);
    return 0;
  }
  return 0.015 * rho_sed * streamvel * streamdepth * pow( (diam50_t/streamdepth), 1.2) * pow(M_e, 1.5);
}


/***************************************************************
 * Van Rijn Suspended transport capacity
 * (Reminder: hh is at object scope)
*/

// This is stream load per unit of stream width (kg/s/m)
double ClassSed_Transport__vr07::calc_suspended_transport_cap(
  double streamvel,   // m/s
  double streamwidth,   // m
  double streamdepth)   // m
{
  double u_crit_t;
  if (u_crit[hh] == 0.0) {
    u_crit_t = calc_critical_velocity(diam50[hh], diam90[hh], streamdepth); 
  } else {
    u_crit_t = u_crit[hh];
  }


  if (streamvel < u_crit[hh])
    return 0.0;

  double diam_nodim = calc_nodim_diam(diam50[hh]);
  double M_e = (streamvel - u_crit[hh]) / sqrt((s - 1) * g * diam50[hh]);

  return 0.012 *
         streamvel * diam50[hh] * pow(M_e, 2.4) * pow(diam_nodim, -0.6);
}


// returns total sediment load (g/int)
double ClassSed_Transport__vr07::calc_vr_load_transport(double streamflow ) {
  if (streamflow <= 0) return 0;  // Protect against spurious input values

//  double flow_rate = streamflow * 1000 * Global::Freq / 86400.0;  // mm*km^2/int -> m^3/s
  double flow_rate = streamflow * Global::Freq / 86400.0;  // m^3/int -> m^3/s

//  double streamdepth = calc_flowdepth_from_manning__rect(flow_rate);

  double streamdepth;
  double streamwidth;

  if (route_Cshp[hh] == 0) {
    streamdepth = calc_flowdepth_from_manning__rect(flow_rate);
    streamwidth = channel_width[hh];
  }
  if (route_Cshp[hh] == 1) {
    CRHMException TExcept("Sed_transport: parabolic channel shape not currently supported", TExcept::TERMINATE);
    LogError(TExcept);    
  }
  if (route_Cshp[hh] == 2) {
    streamdepth = calc_flowdepth_from_manning__Vchannel(flow_rate);    
    streamwidth = calc_flowwidth_from_flowdepth__Vchannel(streamdepth);
  }

  stream_depth[hh] = streamdepth;
  stream_width[hh] = streamwidth;

  if (flow_rate == 0) {
    mass_suspended[hh] = 0;
    mass_bedload[hh] = 0;
    return 0;
  }

//  double streamwidth = channel_width[hh];
  double streamvel = flow_rate/(streamdepth*streamwidth);

// kg/m3 * m(width) * [m3/s / m (width)]
  mass_suspended[hh] = streamwidth * calc_suspended_transport_cap(streamvel, streamwidth, streamdepth);  // kg/s

// The 'per meter' in q_bedload is per unit width of channel (cross-section)
  if (false) {
    double q_bedload_eq10 = calc_bedload_transport_cap_eq10(streamvel, streamwidth, streamdepth);   // kg/s/m
    mass_bedload[hh]   = streamwidth * q_bedload_eq10;  // 
  } else {
    double q_bedload_eq12 = calc_bedload_transport_cap_eq12(streamvel, streamwidth, streamdepth);   // kg/s/m
    mass_bedload[hh]   = streamwidth * q_bedload_eq12; 
  }
  // convert kg/s to g/int
  if (variation == VARIATION_1) {
    return (1.0f - scf_All[0][hh]) * ( mass_suspended[hh] + mass_bedload[hh] ) * 1000.0 * 86400.0 / Global::Freq;
  }
  if (variation == VARIATION_2) {
    return (1.0f - scf_netroute[hh]) * ( mass_suspended[hh] + mass_bedload[hh] ) * 1000.0 * 86400.0 / Global::Freq;
  }
}


/***************************************************************
 * Support routines
*/

void ClassSed_Transport__vr07::initialize_VANRIJN() {
  
  for (long hh = 0; hh < nhru; ++hh) {
    pct_sand[hh] = 100 - (pct_silt[hh] + pct_clay[hh]);
    diam50[hh] = 1e-3 * calc_vcsi_diam_percentile(50, pct_sand[hh], pct_silt[hh]);  // mm -> m
    diam90[hh] = 1e-3 * calc_vcsi_diam_percentile(90, pct_sand[hh], pct_silt[hh]);  // mm -> m
    /*
    diam_nodim[hh] = calc_nodim_diam(diam50[hh]);
    tau_crit_nodim[hh] = calc_critical_shear_stress_nodim_VANRIJN(diam_nodim[hh]);
    */
  }  
}


