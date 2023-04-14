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

// set this as maximum expected water runoff per timestep (mm)
  declparam("sedrelmax", TDim::NHRU, "[20]", "1","1000", "maximum release fraction from the sediment pool", "(mm)", &sedrelmax);
  declparam("sedrelexp", TDim::NHRU, "[1]", "0.1","10", "sedrelexp", "()", &sedrelexp);
  declparam("sreroexp", TDim::NHRU, "[1]", "0.1","10", "sedrelexp", "()", &sreroexp);

  declparam("erodibility", TDim::NHRU, "[100]", "0","100", "erodibility", "(g/J)", &erodibility);
  declparam("cohesion", TDim::NHRU, "[100]", "0","100", "cohesion", "(kPa)", &cohesion);


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


    calculate_erosion(erodedSed); // calculate mobilised sediment at soil surface
    erodingflow = soil_runoff[hh]; // check
    calculate_transport(erodingflow, erodedSed);   // calculate amount of PP transported in fast flow paths  (kg/km2)

    if(soil_runoff[hh] > minFlow_WQ) { // eroded sed goes back to soil if no surface runoff
        sedrelpool[hh] += erodedSed;
    }

    // sediment released from delay pool
    double sedReleased = std::fmin(sedrelpool[hh],
                            sedrelpool[hh]* pow(soil_runoff[hh]/sedrelmax[hh], sedrelexp[hh])); // export
    sedrelpool[hh] -= sedReleased;

    // sediment concentration for sediment released from delay pool
    if (soil_runoff[hh] > 0) {
        double newSedConc = sedReleased / soil_runoff[hh];
        soil_runoff_cWQ_lay[SED_CHANNEL][hh] = newSedConc;
    }

}



void ClassSed_Detachment::calculate_erosion(double& erodedSed) {
    double MobilisedSed = 0;

// See comparison in Morgan, 2001

// From Marshall and Palmer, suitable for North-western Europe
//    double Kintensity_A = 8.95;
//    double Kintensity_B = 8.44;

// From Laws and Parsons, suitable for North America east of the Rocky Mountains
// Also used in USLE (wischmeier and Smith, 1978)
    double Kintensity_A = 11.87;
    double Kintensity_B = 8.73;

    erodedSed = 0;

    double common_cropcover = 0.0f;
    double common_groundcover = 0.0f;
    if(cohesion[hh] == 0.0f || erodibility[hh] == 0.0f)
      return;      // no parameter values -> no erosion


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


// Particles are eroded by rain splash detachment and by overland flow

    MobilisedSed = 0.0;
    if(net_rain[hh] > 0.0) {
      if(intensity > 0.0) {
        double Rainfall_energy;

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

    if(runoff[hh] > 0.0) {
//       MobilisedSed = (((runoff[hh] * 365.0)*exp(sreroexp)) * (1.0 - common_groundcover) * (1.0/(0.5 * cohesion[hh])) * sin(hru_GSL[hh] / 100.)) / 365.0; // g/m2
// Modified (PRL)
// TODO: temporarily disabled factors for testing. reimplement (PRL)
//       MobilisedSed = ((pow(runoff[hh] * 365.0, sreroexp)) * (1.0 - common_groundcover) * (1.0/(0.5 * cohesion[hh])) * sin(hru_GSL[hh] / 100.)) / 365.0; // g/m2
        double FlowMobilisedSed = ((pow(runoff[hh], sreroexp[hh])) * (1.0 - common_groundcover) * (1.0-scf[hh]) * (1.0/(0.5 * cohesion[hh])) ); // g/m2
        MobilisedSed += FlowMobilisedSed;   // Mobilisation due to surface flow
    }

// Set output variables

    erodedSed = MobilisedSed;      // kg/km2

}


void ClassSed_Detachment::calculate_transport(const double flow, double& erodedSed) {
    double transportfactor = 1;
    double enrichment = 1;

    erodedSed = erodedSed * transportfactor * enrichment;
}
