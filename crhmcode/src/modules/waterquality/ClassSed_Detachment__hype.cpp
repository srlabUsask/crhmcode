// 11/20/19
//---------------------------------------------------------------------------
#pragma hdrstop

//#include <math.h>
#include <cmath>
#include <stdlib.h>

#include "ClassSed_Detachment.h"
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
double mannings_n = 0.104;  // check loch et al. 89 for values

// *******************




ClassSed_Detachment* ClassSed_Detachment::klone(string name) const{
  return new ClassSed_Detachment(name);
}


void ClassSed_Detachment::decl(void) {

  variation_set = VARIATION_ORG;

  declstatvar("conc_soil_rechr", TDim::NDEFN, "concentration in soil_rechr: (i_no3n=0) NO3-N, (i_nh4n=1) NH4-1, (i_don=2) DON, "
      "(i_srp=3) SRP, (i_dop=4) DOP, (i_pp=5) PP, (i_oc=6) OC", "(mg/l)", &conc_soil_rechr, &conc_soil_rechr_lay, numsubstances); //

  declstatvar("conc_soil_lower", TDim::NDEFN, "concentration in soil_lower: (i_no3n=0) NO3-N, (i_nh4n=1) NH4-1, (i_don=2) DON, "
      "(i_srp=3) SRP, (i_dop=4) DOP, (i_pp=5) PP, (i_oc=6) OC", "(mg/l)", &conc_soil_lower, &conc_soil_lower_lay, numsubstances);

  declgetvar("*", "runoff", "(mm)", &runoff);
  declgetvar("*", "scf", "()", &scf);

  declgetvar("*", "soil_runoff", "(mm)", &soil_runoff);
  declputvar("*", "soil_runoff_cWQ", "(mm)", &soil_runoff_cWQ,&soil_runoff_cWQ_lay);

  declstatvar("sedrelpool", TDim::NHRU, "sediment stored in conceptual storage pool", "(kg/int)", &sedrelpool);

// Vars for the vanRijn formulation
  decllocal("sed_diam_nodim", TDim::NHRU, "nondimensional sediment diameter", "()", &diam_nodim);
  decllocal("sed_tau_crit_nodim", TDim::NHRU, "nondimensional critical shear stress", "()", &tau_crit_nodim);
  declstatvar("sed_bed_flux", TDim::NHRU, "sediment bed flux", "(m^3/m/int)", &bed_flux);
  declstatvar("sed_tau_b_nodim", TDim::NHRU, "nondimensional bed shear stress", "(Pa)", &tau_b_nodim);
  declstatvar("sed_tau_b", TDim::NHRU, "bed shear stress", "(Pa)", &tau_b);
  declstatvar("sed_stream_depth", TDim::NHRU, "stream depth", "(m)", &stream_depth);

// set this as maximum expected water runoff per timestep (mm)
  declparam("sedrelmax", TDim::NHRU, "[20]", "1","1000", "maximum release fraction from the sediment pool", "(mm)", &sedrelmax);
  declparam("sedrelexp", TDim::NHRU, "[1]", "0.1","10", "sedrelexp", "()", &sedrelexp);
  declparam("sreroexp", TDim::NHRU, "[1]", "0.1","10", "sedrelexp", "()", &sreroexp);

  declparam("erodibility", TDim::NHRU, "[100]", "0","100", "erodibility", "(g/J)", &erodibility);
  declparam("cohesion", TDim::NHRU, "[100]", "0","100", "cohesion", "(kPa)", &cohesion);

// Parameters for the vanRijn formulation
  declparam("channel_pct", TDim::NHRU, "[0]", "0","100", "fraction of area containing rills", "()", &channel_pct);
  declparam("sedslope", TDim::NHRU, "[0.0001]", "0","10", "slope of the rill channels", "()", &sedslope);
  declparam("mannings_n", TDim::NHRU, "[0.1]", "0","2", "mannings n", "()", &mannings_n);
  declparam("d50", TDim::NHRU, "[0.0005]", "0","0.01", "D50", "(m)", &d50);
  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);



  declgetvar("*", "net_rain", "(mm)", &net_rain);

  variation_set = VARIATION_1;

  declgetvar("*", "snowmelt_int", "(mm/int)", &snowmelt_int);

  variation_set = VARIATION_2;

  declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD);

}


void ClassSed_Detachment::init(void) {

  for (long hh = 0; hh < nhru; ++hh) {
      for (long Sub = 0; Sub < numsubstances; ++Sub) {
          conc_soil_rechr_lay[Sub][hh] = 0;
          conc_soil_lower_lay[Sub][hh] = 0;
      }
  }

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
//        conc_soil_rechr_lay[SED_CHANNEL][hh] = 1;   // mg/L
//        conc_soil_lower_lay[SED_CHANNEL][hh] = 1;   // mg/L

// This is just for testing and verification.
// WS_outflow_conc should be approximately the same value at outlet
//        soil_runoff_cWQ_lay[SED_CHANNEL][hh] = 1;   // mg/L
        runoff_sed_by_erosion();

//        soil_runoff_cWQ_lay[SED_CHANNEL][hh] = 0.3;   // mg/L
    }

}


void ClassSed_Detachment::finish(bool good) {
}



void ClassSed_Detachment::runoff_sed_by_erosion() {
    double erodedSed;       // total eroded sediment (kg/km2)
    double erodingflow;   // Flow eroding the surface


    bed_flux[hh] = 0;   // just for testing


    calculate_erosion(erodedSed); // calculate mobilised sediment at soil surface
    erodingflow = soil_runoff[hh]; // check
    calculate_transport(erodingflow, erodedSed);   // calculate amount of PP transported in fast flow paths  (kg/km2)

    if(soil_runoff[hh] > minFlow_WQ) { // eroded sed goes back to soil if no surface runoff
        sedrelpool[hh] += erodedSed;
    }

    // sediment released from delay pool
    double sedReleased = std::fmin(sedrelpool[hh],
                            sedrelpool[hh]* pow(soil_runoff[hh]/sedrelmax[hh], sedrelexp[hh])); // (kg/km^2/int) export
    sedrelpool[hh] -= sedReleased;

    // sediment concentration for sediment released from delay pool
    if (soil_runoff[hh] > 0) {
        double newSedConc = sedReleased / soil_runoff[hh];  // kg/(1000m^3) = g/m^3
        soil_runoff_cWQ_lay[SED_CHANNEL][hh] = newSedConc;
    }

}



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


double ClassSed_Detachment::calculate_rainsplash_mobilization__mmf() {

  if (erodibility[hh] == 0.0) return 0;


  double common_cropcover = 0.0f;

// See comparison in Morgan, 2001

// From Marshall and Palmer, suitable for North-western Europe
//    double Kintensity_A = 8.95;
//    double Kintensity_B = 8.44;

// From Laws and Parsons, suitable for North America east of the Rocky Mountains
// Also used in USLE (wischmeier and Smith, 1978)
  double Kintensity_A = 11.87;
  double Kintensity_B = 8.73;


// Check for snow limiting erosion

    double intensity = 1.0;    // intenspar;
    if (variation == VARIATION_1) {
      if(snowmelt_int[hh] > 0.0)
        intensity = 0.0;  // snow
    }

    if (variation == VARIATION_2) {
      if(snowmeltD[hh] > 0.0)
        intensity = 0.0;  // snow
    }


  if(net_rain[hh] > 0.0) {
    if(intensity > 0.0) {
      double Rainfall_energy = 0.0;   // (J)

      if(net_rain[hh] > 5.0/Global::Freq)     // TODO: shorter timestep, other threshold?
        Rainfall_energy = calc_rainsplash_energy(net_rain[hh]);

      Rainfall_energy = net_rain[hh] * Rainfall_energy;        // J/m2
      double RainMobilisedSed = Rainfall_energy * (1.0 - common_cropcover) * (1.0-scf[hh]) * erodibility[hh];  // g/m2

      return RainMobilisedSed;   // Mobilisation due to rainfall (g/m2)
    }
  }
  return 0;
}



double ClassSed_Detachment::calculate_flow_mobilization_HYPE(double runoff) {

  double common_groundcover = 0.0f;

  if ( (runoff > 0.0) && (sreroexp[hh] > 0)) {
//       MobilisedSed = (((runoff[hh] * 365.0)*exp(sreroexp)) * (1.0 - common_groundcover) * (1.0/(0.5 * cohesion[hh])) * sin(hru_GSL[hh] / 100.)) / 365.0; // g/m2
// Modified (PRL)
// TODO: temporarily disabled factors for testing. reimplement (PRL)
//       MobilisedSed = ((pow(runoff[hh] * 365.0, sreroexp)) * (1.0 - common_groundcover) * (1.0/(0.5 * cohesion[hh])) * sin(hru_GSL[hh] / 100.)) / 365.0; // g/m2
      double FlowMobilisedSed = ((pow(runoff, sreroexp[hh])) * (1.0 - common_groundcover) * (1.0-scf[hh]) * (1.0/(0.5 * cohesion[hh])) ); // g/m2
      return FlowMobilisedSed;   // Mobilisation due to surface flow (g/m2)
  }
  return 0;
}



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


double ClassSed_Detachment::calc_nodim_diam( double diam ) {
  return diam * pow( (s-1)*g/(visc*visc), 1.0/3);
}

double ClassSed_Detachment::calc_rill_flowdepth_from_manning(double flow_rate) {
//  global mannings_n
  
  double h = pow (1.342281879 * flow_rate * mannings_n[hh] / sqrt(sedslope[hh]),
                  3.0/8.0);
  return h;
}    
  
double ClassSed_Detachment::calc_rill_flowvel_from_flowdepth(double flow_rate, double h) {
  return flow_rate / (h*h);
}

double ClassSed_Detachment::calc_bed_shear_stress(double stream_depth) {
  return rho_w * g * stream_depth * sedslope[hh];
}

double ClassSed_Detachment::calc_nodim_shear_stress( double tau_b ) {
  return tau_b / ( rho_w * (s-1) * g * d50[hh] );
}

double ClassSed_Detachment::calc_dim_bed_flux( double bed_flux_nodim ) {
  return bed_flux_nodim * sqrt( (s-1) * g * pow(d50[hh], 3) );
}

//def calc_sedconc_from_bedflux( double bedflux, double flow_rate, doube channel_len )


double ClassSed_Detachment::VANRIJN( double tau_b_nodim , double tau_crit_nodim, double diam_nodim ) {
    return (0.053 / diam_nodim) * pow(tau_b_nodim/tau_crit_nodim - 1, 2.1);
}



void ClassSed_Detachment::initialize_VANRIJN() {
  for (long hh = 0; hh < nhru; ++hh) {
    diam_nodim[hh] = calc_nodim_diam(d50[hh]);
    tau_crit_nodim[hh] = calc_critical_shear_stress_nodim_VANRIJN(diam_nodim[hh]);
  }
}


double ClassSed_Detachment::calculate_flow_mobilization_VANRIJN(double runoff) {  // runoff: mm * km^2/int
// Global::Freq: # intervals per day
  double flow_rate = runoff * 1000 * Global::Freq / 86400.0;  // mm*km^2/int -> m^3/s

  stream_depth[hh] = calc_rill_flowdepth_from_manning(flow_rate);
  tau_b[hh] = calc_bed_shear_stress( stream_depth[hh]);
  tau_b_nodim[hh] = calc_nodim_shear_stress( tau_b[hh] );

// Different ways to calculate nondim bed flux from nondim shear stress
  // bed_flux_nodim = NIELSON( tau_b_nodim , tau_crit_nodim)

  if (tau_b_nodim[hh] < tau_crit_nodim[hh] ) return 0;

  double bed_flux_nodim = VANRIJN( tau_b_nodim[hh] , tau_crit_nodim[hh], diam_nodim[hh]);

  // bed flux (volume rate of transport per unit length of surface[channel] )  [I.e. m2/s]
  bed_flux[hh] = calc_dim_bed_flux( bed_flux_nodim );

  double channel_len = ( channel_pct[hh] / 100 ) * hru_area[hh] * 1e6;  // (m) [km^2 -> m^2]

  double mobilized_kg_s = bed_flux[hh] * rho_sed * channel_len * (1.0-scf[hh]);  // kg/s over entire area
  return mobilized_kg_s * 1000 * 86400.0 / Global::Freq / hru_area[hh];  // return g/km^2/int

}



void ClassSed_Detachment::calculate_erosion(double& erodedSed) {

  erodedSed = 0;

//    if(cohesion[hh] == 0.0f)
//      return;      // no parameter values -> no erosion


  double MobilisedSed = 0;  // (g/m2)

// Particles are eroded by rain splash detachment and by overland flow

  if (net_rain[hh] > 0.0) {
    MobilisedSed += calculate_rainsplash_mobilization();
  }
    /*
    if(net_rain[hh] > 0.0) {
      if(intensity > 0.0) {
        double Rainfall_energy;   // (J)

        if(net_rain[hh] > 5.0/Global::Freq)     // TODO: shorter timestep, other threshold?
        // Taken from HYPE
//          Rainfall_energy = 8.95+8.44*log10(net_rain[hh]*(0.257+sin(2*3.14*((dayno-70.)/365.))*0.09)*2.0);
          Rainfall_energy = Kintensity_A + Kintensity_B*log10(net_rain[hh]);
        else
          Rainfall_energy = 0.0;

        Rainfall_energy = net_rain[hh] * Rainfall_energy;        // J/m2
        double RainMobilisedSed = Rainfall_energy * (1.0 - common_cropcover) * (1.0-scf[hh]) * erodibility[hh];  // g/m2

        MobilisedSed += RainMobilisedSed;   // Mobilisation due to rainfall
      }
    }
*/

  if (runoff[hh] > 0.0) {
//    MobilisedSed += calculate_flow_mobilization_HYPE(runoff[hh]);
    MobilisedSed += calculate_flow_mobilization_VANRIJN(runoff[hh]);
  }
/*
    if ( (runoff[hh] > 0.0) && (sreroexp[hh] > 0)) {
//       MobilisedSed = (((runoff[hh] * 365.0)*exp(sreroexp)) * (1.0 - common_groundcover) * (1.0/(0.5 * cohesion[hh])) * sin(hru_GSL[hh] / 100.)) / 365.0; // g/m2
// Modified (PRL)
// TODO: temporarily disabled factors for testing. reimplement (PRL)
//       MobilisedSed = ((pow(runoff[hh] * 365.0, sreroexp)) * (1.0 - common_groundcover) * (1.0/(0.5 * cohesion[hh])) * sin(hru_GSL[hh] / 100.)) / 365.0; // g/m2
        double FlowMobilisedSed = ((pow(runoff[hh], sreroexp[hh])) * (1.0 - common_groundcover) * (1.0-scf[hh]) * (1.0/(0.5 * cohesion[hh])) ); // g/m2
        MobilisedSed += FlowMobilisedSed;   // Mobilisation due to surface flow
    }
*/

// Set output variables

  erodedSed = MobilisedSed*1000;      // g/m2/int -> kg/km2/int

}


void ClassSed_Detachment::calculate_transport(const double flow, double& erodedSed) {
    double transportfactor = 1;
    double enrichment = 1;

    erodedSed = erodedSed * transportfactor * enrichment;
}
