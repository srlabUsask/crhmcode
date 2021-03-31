// 05/02/19
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Hype_routines.h"
#include "NewModules.h"
#include "DefCRHMGlobal.h"

#include <math.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------

using namespace std;
using namespace CRHM;

const float thetalow = 0.1;                     // Low(?) moisture coefficient (thetalow)
const float thetaupp = 0.5;                     // high(?) moisture coefficient (thetaupp)
const float bulkdensity = 1300;
//const float soilcoh = 1.0; // soilpar(float m_soilcoh, long isoil);
const float sreroexp = 0.0; // genpar(float m_sreroexp); surface runoff erosion exponent
const float filtPbuf  = 1.0; // landpar(float m_filtPbuf, long iluse);
const float filtPother  = 1.0; // landpar(float m_filtPbuf, long iluse);
const float filtPinner  = 1.0; // landpar(float m_filtPbuf, long iluse);
const float pprelmax  = 1.0; // landpar(float m_filtPbuf, long iluse);
const float pprelexp  = 1.0; // genpar(float m_filtPbuf, long iluse);
const float Kfr = 1.0; // model parameter freundlich
const float Nfr = 1.0; // model parameter freundlichmodel parameter freundlich
const float Kadsdes = 1.0; // model parameter freundlich, adsorption or desportion rate (1/d)

const float halfsatTPwater  = 0.05;    // half stauration concentration, production in water (mg P/L)
const float maxprodwater    = 0.5;     // maximum part of IN/SRP pool that can be used for production per timestep
const float maxdegradwater  = 0.5;     // maximum part of ON/PP/OC pool that can be degraded per timestep
const float NPratio         = 1.0/7.2; // ratio for production/mineralisation in water
const float NCratio         = 5.7;     // NC ratio for production/mineralisation in water (värde från BIOLA)
const float maxdenitriwater = 999; // USE HYPEVARIABLES, ONLY
const float halfsatINwater = 999; //USE HYPEVARIABLES, ONLY

const float soilerod = 1.0;
const float satact = 1.0;
const float thetapow = 1.0;
const float smfdenitlim = 0.1; // limitation parameter of moisturefactor (mm) (smfdenitlim)
const float smfdenitpow = 1.0; // exponent of moisturefactor (smfdenitpow)
const float halfsatINsoil = 1.0;
const float ldprodpp = 1.0;
const float ldprodsp = 1.0;

const long i_in = 0; // inorganic nitrogen
const long i_on = 1; // organic nitrogen
const long i_sp = 2; // soluble (reactive) phosphorus, i.e. phosphate
const long i_pp = 3; // particulate phosphorus
const long i_oc = 4; // (dissolved) organic carbon

ClassWQ_Hype* ClassWQ_Hype::klone(string name) const{
  return new ClassWQ_Hype(name);
}

void ClassWQ_Hype::decl(void) {

  Description = "'Hype module.'";

  declstatvar("partP", NDEFN, "immobile pool of organic phosphorus adsorded to soil particles.", "(kg/km^2)", &partP, &partP_lay, maxsoillayers);

  declstatvar("refractoryN", NDEFN, "immobile pool of organic nitrogen in soil with slow turnover.", "(kg/km^2)", &refractoryN, &refractoryN_lay, maxsoillayers);

  declstatvar("refractoryP", NDEFN, "immobile pool of organic phosphorus in soil with slow turnover.", "(kg/km^2)", &refractoryP, &refractoryP_lay, maxsoillayers);

  declstatvar("refractoryC", NDEFN, "refractoryC pool in soil", "(kg/km^2)", &refractoryC, &refractoryC_lay, maxsoillayers);

  declstatvar("labileN", NDEFN, "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &labileN, &labileN_lay, maxsoillayers);

  declstatvar("labileP", NDEFN, "immobile pool of organic phosphorus in soil with rapid turnover.", "(kg/km^2)", &labileP, &labileP_lay, maxsoillayers);

  declstatvar("labileC", NDEFN, "labileC pool in soil", "(kg/km^2)", &labileC, &labileC_lay, maxsoillayers);

  declstatvar("DINpool", NDEFN, "inorg N pool in soil", "(kg/km^2)", &DINpool, &DINpool_lay, maxsoillayers);

  declstatvar("DONpool", NDEFN, "DON pool in soil", "(kg/km^2)", &DONpool, &DONpool_lay, maxsoillayers);

  declstatvar("SRPpool", NDEFN, "SRP pool in soil", "(kg/km^2)", &SRPpool, &SRPpool_lay, maxsoillayers);

  declstatvar("DOPpool", NDEFN, "DOP pool in soil", "(kg/km^2)", &DOPpool, &DOPpool_lay, maxsoillayers);

  declstatvar("uptakeN", NDEFN, "uptakeN", "(kg/km^2)", &uptakeN, &uptakeN_lay, maxsoillayers2);

  declstatvar("uptakeP", NDEFN, "uptakeP", "(kg/km^2)", &uptakeP, &uptakeP_lay, maxsoillayers2);

  declvar("water", NDEFN, "soil moisture", "(mm)", &water, &water_lay, maxsoillayers);

  declvar("Temp", NDEFN, "soil layer temperature", "(°C)", &Temp, &Temp_lay, maxsoillayers);

  declvar("denitrification", NDEFN, "denitrification (maxsoillayers", "(kg/int)", &denitrification, &denitrification_lay, maxsoillayers);


  declstatvar("conc_top", NDEFN, "concentration of inorganic nitrogen in soil moisture per land-soil", "(mg/l)", &conc_top, &conc_top_lay, numsubstances); //

  declstatvar("conc_bottom", NDEFN, "concentration of organic nitrogen in soil moisture per land-soil", "(mg/l)", &conc_bottom, &conc_bottom_lay, numsubstances);

  declstatvar("conc_below", NDEFN, "concentration of soluble (reactive) phosphorus, i.e. phosphate in soil moisture per land-soil", "(mg/l)", &conc_below, &conc_below_lay, numsubstances);

  declvar("source", NDEFN, "source of soil water nutrients through mineralization", "(kg/int)", &source, &source_lay, numsubstances);

  declvar("thickness", NDEFN, "thickness of soil layers", "(mm)", &thickness, &thickness_lay, numsubstances); // porosity = 1


  declvar("sink", NDEFN, "sink of nutrients in subroutine)", "(kg/km^2)", &sink, &sink_lay, numsubstances);

  declvar("sources_plant", NDEFN, "load from plant residues. Indexed as LAY -> substance", "(kg/int)", &sources_plant, &sources_plant_lay, numsubstances);

  declvar("sources_fertilizer", NDEFN, "load from fertilizer) Indexed as LAY -> substance", "(kg/int)", &sources_fertilizer, &sources_fertilizer_lay, numsubstances);


  declvar("fracminP", NHRU, "part of eroded P in mineral form", "()", &fracminP);

  declvar("nitrification", NHRU, "nitrification", "(kg/int)", &nitrification);

  declvar("cropuptake", NHRU, "crop uptake of nitrogen", "(kg/int)", &cropuptake);


  declparam("fc", NDEFN, "[1]", "0", "100", "water content at field capacity", "(mm)", &fc, &fc_lay, maxsoillayers);

  declparam("ep", NDEFN, "[1]", "0", "100", "water content: effective porosity", "(mm)", &ep, &ep_lay, maxsoillayers);

  declparam("wp", NDEFN, "[1]", "1", "66", "water content at wilting point", "(mm)", &wp, &wp_lay, maxsoillayers);

  declparam("pw", NDEFN, "[1]", "1", "66", "water content: total porosity", "(mm)", &pw, &pw_lay, maxsoillayers);


  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(°)", &hru_GSL);

  declparam("ccmax1", NHRU, "[0]", "0","10", "crop cover during summer", "()", &ccmax1);

  declparam("ccmax2", NHRU, "[0]", "0","10", "crop cover during winter and all year for year round", "()", &ccmax2);

  declparam("gcmax1", NHRU, "[0]", "0","10", "ground cover during summer", "()", &gcmax1);

  declparam("gcmax2", NHRU, "[0]", "0","10", "ground cover during winter and all year for year round", "()", &gcmax2);

  declparam("baredayno1", NHRU, "[0]", "1","366", "spring ploughing", "()", &baredayno1);

  declparam("baredayno2", NHRU, "[0]", "1","366", "sow date/beginning of growing season", "()", &baredayno2);

  declparam("baredayno3", NHRU, "[0]", "1","366", "harvest", "()", &baredayno3);

  declparam("baredayno4", NHRU, "[0]", "1","366", "autumn ploughing", "()", &baredayno4);

  declparam("baredayno5", NHRU, "[0]", "1","366", "winter crops sowing date", "()", &baredayno5);

  declparam("pardenN", NHRU, "[1]", "0", "100", "denitrification in soil", "(mm)", &pardenN);

  declparam("calcN", NHRU, "[0]", "0", "1", "flag for nitrogen simulation", "()", &calcN);

  declparam("calcP", NHRU, "[0]", "0", "1", "flag for phosphorus simulation", "()", &calcP);

  declparam("calcC", NHRU, "[0]", "0", "1", "flag for carbon simulation", "()", &calcC);

  declparam("Inhibit_Hype", BASIN, "[0]", "0", "1", "Bypass Hype routines", "()", &Inhibit_Hype);

  declparam("parminfN", NHRU, "[0]", "0", "1", "mineralisation of labileN: labileN to DIN", "(1/d)", &parminfN);

  declparam("parminfP", NHRU, "[0]", "0", "1", "mineralisation of labileP: labileP to DIP", "(1/d)", &parminfP);

  declparam("pardegrhN", NHRU, "[0]", "0", "1", "degradation of refractoryN: refractoryN to labileN", "(1/d)", &pardegrhN);

  declparam("pardegrhP", NHRU, "[0]", "0", "1", "degradation refractoryP: refractoryP to labileP", "(1/d)", &pardegrhP);

  declparam("pardisfN", NHRU, "[0]", "0", "1", "dissolution of labileN: labileN to DON", "(1/d)", &pardisfN);

  declparam("pardisfP", NHRU, "[0]", "0", "1", "dissolution of labileP: labileP to DOP", "(1/d)", &pardisfP);

  declparam("pardishN", NHRU, "[0]", "0", "1", "dissolution of refractoryN: refractoryN to DON", "(1/d)", &pardishN);

  declparam("pardishP", NHRU, "[0]", "0", "1", "dissolution of refractoryP: refractoryP to DOP", "(1/d)", &pardishP);

  declparam("klh",    NHRU, "[0]", "0", "100", "speed of transformation from litter to refractory", "(1/d)", &klh);

  declparam("klo",    NHRU, "[0]", "0", "100", "speed of transformation from litter to DOC", "(1/d)", &klo);

  declparam("kho",    NHRU, "[0]", "0", "100", "speed of transformation from refractory to DOC", "(1/d)", &kho);

  declparam("kof",    NHRU, "[0]", "0", "100", "speed of transformation from DOC to labileC", "(1/d)", &kof);

  declparam("koflim", NHRU, "[0.5]", "0", "100", "threshold for wetness for transformation DOC to labileC", "()", &koflim);

  declparam("minc",   NHRU, "[1]", "0", "100", "fraction mineralisation to DIC", "()", &minc);

  declparam("soimf",  NHRU, "[1]", "0", "100", "saturation soilmoisture factor", "()", &soimf);
  
  declparam("soimr",  NHRU, "[1]", "0", "100", "rate soilmoisture factor", "()", &soimr);
  
  declparam("fertNamount1", NHRU, "[1]", "0", "1000000", "fertiliser amount1 N", "(kg/km^2)", &fertNamount1);

  declparam("fertNamount2", NHRU, "[1]", "0", "1000000", "fertiliser amount2 N", "(kg/km^2)", &fertNamount2);

  declparam("fertPamount1", NHRU, "[1]", "0", "1000000", "fertiliser amount1 P", "(kg/km^2)", &fertPamount1);

  declparam("fertPamount2", NHRU, "[1]", "0", "1000000", "fertiliser amount2 P", "(kg/km^2)", &fertPamount2);

  declparam("fertday1", NHRU, "[0]", "0", "366", "day for fertilizing 1 (dayno)", "()", &fertday1);

  declparam("fertday2", NHRU, "[0]", "0", "366", "day for fertilizing 2 (dayno)", "()", &fertday2);

  declparam("resdayno", NHRU, "[0]", "0", "366", "day for residual (dayno), code 0 give residuals every day)", "()", &resdayno);

  declparam("manday1", NHRU, "[0]", "0", "366", "day for manureing 1)", "()", &manday1);

  declparam("manday2", NHRU, "[0]", "0", "366", "day for manureing 2)", "()", &manday2);

  declparam("fertdown1", NHRU, "[0.0]", "0", "1", "part[hh] of fertilizer amount1 ploughed down", "()", &fertdown1);

  declparam("fertdown2", NHRU, "[0.0]", "0", "1", "part[hh] of fertilizer amount2 ploughed down", "()", &fertdown2);

  declparam("mandown1", NHRU, "[0.0]", "0", "1", "part[hh] of manure amount1 ploughed down", "()", &mandown1);

  declparam("mandown2", NHRU, "[0.0]", "0", "1", "part[hh] of manure amount2 ploughed down", "()", &mandown2);

  declparam("manNamount1", NHRU, "[0.0]", "0", "1000000", "manure amount1 N", "(kg/km^2)", &manNamount1);

  declparam("manNamount2", NHRU, "[0.0]", "0", "1000000", "manure amount2 N", "(kg/km^2)", &manNamount2);

  declparam("manPamount1", NHRU, "[0.0]", "0", "1000000", "manure amount1 P", "(kg/km^2)", &manPamount1);

  declparam("manPamount2", NHRU, "[0.0]", "0", "1000000", "manure amount2 P", "(kg/km^2)", &manPamount2);

  declparam("resNamount", NHRU, "[0.0]", "0", "1000000", "residual amount of N", "(kg/km^2)", &resNamount);

  declparam("resPamount", NHRU, "[0.0]", "0", "1000000", "residual amount of P", "(kg/km^2)", &resPamount);

  declparam("resCamount", NHRU, "[0.0]", "0", "1", "litter fall of C", "(kg/km^2)", &resCamount);

  declparam("resfast", NHRU, "[0.0]", "0", "1", "part[hh] of residual amount to labileN/P pool (rest to refractoryN/P)", "()", &resfast);

  declparam("resdown", NHRU, "[0.0]", "0", "1", "part[hh] of residual amount to labileN/P pool (rest to refractoryN/P)", "()", &resdown);

  declparam("fertperiod", NHRU, "[1]", "1", "100", "days for fertilization.)", "()", &fertperiod);

  declparam("litterperiod", NHRU, "[1]", "1", "100", "days for litterfall.)", "()", &litterperiod);

  declparam("part", NHRU, "[1.0]", "0", "1", "fraction of HRU area under current crop.", "()", &part);

  declparam("manureNpart", NHRU, "[0.5]", "0", "1", "fraction of HRU for manure manureNpart/fastpart (N).", "()", &manureNpart);

  declparam("manureNfastpart", NHRU, "[0.5]", "0", "1", "fraction of HRU for manure labileP-refractoryP (P).", "()", &manureNfastpart);


  declparam("refractoryN_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with slow turnover.", "(kg/km^2)", &refractoryN_init, &refractoryN_init_lay, maxsoillayers);

  declparam("refractoryP_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic phosphorus in soil with slow turnover.", "(kg/km^2)", &refractoryP_init, &refractoryP_init_lay, maxsoillayers);

  declparam("refractoryC_init", NDEFN, "[0.0]", "0", "1000000", "refractoryC pool in soil", "(kg/km^2)", &refractoryC_init, &refractoryC_init_lay, maxsoillayers);

  declparam("labileN_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &labileN_init, &labileN_init_lay, maxsoillayers);

  declparam("labileP_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic phosphorus in soil with rapid turnover.", "(kg/km^2)", &labileP_init, &labileP_init_lay, maxsoillayers);

  declparam("labileC_init", NDEFN, "[0.0]", "0", "1000000", "labileC pool in soil", "(kg/km^2)", &labileC_init, &labileC_init_lay, maxsoillayers);

  declparam("N_uptake", NDEFN, "[0]", "0", "10", "plant N uptake per day.", "(kg/km^2)", &N_uptake, &N_uptake_lay, maxsoillayers);

  declparam("P_uptake", NDEFN, "[0]", "0", "10", "plant P uptake per day.", "(kg/km^2)", &P_uptake, &P_uptake_lay, maxsoillayers);

  declparam("conc_top_init", NDEFN, "[0.0]", "0", "1000", "initial concentration of inorganic nitrogen in soil moisture per land-soil", "(mg/l)", &conc_top_init, &conc_top_init_lay, numsubstances);

  declparam("conc_bottom_init", NDEFN, "[0.0]", "0", "1000", "concentration of organic nitrogen in soil moisture per land-soil", "(mg/l)", &conc_bottom_init, &conc_bottom_init_lay, numsubstances);


  declgetvar("*", "hru_t", "(°C)", &hru_t);

  declgetvar("*", "SWE", "(mm)", &SWE);

  declgetvar("*", "net_rain", "(mm)", &net_rain);

  declgetvar("*", "runoff", "(mm)", &runoff);

  declgetvar("*", "soil_moist", "(mm)", &soil_moist);

  declgetvar("*", "soil_rechr", "(mm)", &soil_rechr);

  declgetparam("*", "soil_moist_max", "(mm)", &soil_moist_max);

  declgetparam("*", "soil_rechr_max", "(mm)", &soil_rechr_max);
}

void ClassWQ_Hype::init(void) {

  nhru = getdim(NHRU);
  nlay = getdim(NLAY);

  for(hh = 0; hh < nhru; ++hh) {
    thickness_lay[0][hh] = soil_rechr_max[hh]/ep[hh];
    thickness_lay[1][hh] = (soil_moist_max[hh] - soil_rechr_max[hh])/ep[hh];
    thickness_lay[2][hh] = 0.0;

    fracminP[hh] = 0.0;
    nitrification[hh] = 0.0;
    cropuptake[hh] = 0.0;

    for(long ll = 0; ll < maxsoillayers; ++ll) {
      partP_lay[ll][hh];
      conc_top_lay[ll][hh] = conc_top_init_lay[ll][hh];
      conc_bottom_lay[ll][hh] = conc_bottom_init_lay[ll][hh];
      refractoryN_lay[ll][hh] = refractoryN_init_lay[ll][hh];
      refractoryP_lay[ll][hh] = refractoryP_init_lay[ll][hh];
      refractoryC_lay[ll][hh] = refractoryC_init_lay[ll][hh];
      labileN_lay[ll][hh] = labileN_init_lay[ll][hh];
      labileP_lay[ll][hh] = labileP_init_lay[ll][hh];
      labileC_lay[ll][hh] = labileC_init_lay[ll][hh];
      water_lay[ll][hh] = 0.0;
      DONpool_lay[ll][hh] = 0.0;
      DINpool_lay[ll][hh] = 0.0;
      DOPpool_lay[ll][hh] = 0.0;
      SRPpool_lay[ll][hh] = 0.0;
      denitrification_lay[ll][hh];
    }

    for(long ll = 0; ll < maxsoillayers2; ++ll) {
      uptakeN_lay[ll][hh] = 0.0;
      uptakeP_lay[ll][hh] = 0.0;
    }

    for(long Sub = 0; Sub < numsubstances; ++Sub) {
      conc_top_lay[Sub][hh] = conc_top_init_lay[Sub][hh];
      conc_bottom_lay[Sub][hh] = conc_bottom_init_lay[Sub][hh];
      conc_below_lay[Sub][hh] = 0.0;
      source_lay[Sub][hh] = 0.0;
      sink_lay[Sub][hh] = 0.0;
      sources_fertilizer_lay[Sub][hh] = 0.0;
      sources_plant_lay[Sub][hh] = 0.0;
    }
  }
}

void ClassWQ_Hype::run(void) {

  long step = getstep();
  long nstep = step% Global::Freq;

  if(step == 1){ // begining of run
    for(hh = 0; hh < nhru; ++hh) {
      const_cast<float *>  (klh)[hh] /= Global::Freq; // Parameters are backed up after "init".
      const_cast<float *>  (klo)[hh] /= Global::Freq; // Parameters may be modified.
      const_cast<float *>  (kho)[hh] /= Global::Freq; // Parameters are restored after run
      const_cast<float *>  (kof)[hh] /= Global::Freq;
      const_cast<float *>  (parminfN)[hh] /= Global::Freq;
      const_cast<float *>  (parminfP)[hh] /= Global::Freq;
      const_cast<float *>  (pardegrhN)[hh] /= Global::Freq;
      const_cast<float *>  (pardegrhP)[hh] /= Global::Freq;
      const_cast<float *>  (pardisfN)[hh] /= Global::Freq;
      const_cast<float *>  (pardisfP)[hh] /= Global::Freq;
      const_cast<float *>  (pardishN)[hh] /= Global::Freq;
      const_cast<float *>  (pardishP)[hh] /= Global::Freq;
      const_cast<float *>  (fertNamount1)[hh] /= Global::Freq;
      const_cast<float *>  (fertNamount2)[hh] /= Global::Freq;
      const_cast<float *>  (fertPamount1)[hh] /= Global::Freq;
      const_cast<float *>  (fertPamount2)[hh] /= Global::Freq;
      const_cast<float *>  (manNamount1)[hh] /= Global::Freq;
      const_cast<float *>  (manNamount2)[hh] /= Global::Freq;
      const_cast<float *>  (manPamount1)[hh] /= Global::Freq;
      const_cast<float *>  (manPamount2)[hh] /= Global::Freq;
      const_cast<float *>  (resNamount)[hh] /= Global::Freq;
      const_cast<float *>  (resPamount)[hh] /= Global::Freq;
      const_cast<float *>  (resCamount)[hh] /= Global::Freq;
      const_cast<float *>  (resfast)[hh] /= Global::Freq;
      const_cast<float *>  (resdown)[hh] /= Global::Freq;
      const_cast<float *>  (fertdown1)[hh] /= Global::Freq;
      const_cast<float *>  (fertdown2)[hh] /= Global::Freq;
      const_cast<float *>  (mandown1)[hh] /= Global::Freq;
      const_cast<float *>  (mandown2)[hh] /= Global::Freq;
    }
  } // begining of run

    if(Inhibit_Hype[0])
      return;

    dayno = julian("now");

    for(hh = 0; chkStruct(); ++hh){ // Using inhibit is dangerous
      water_lay[0][hh] = soil_rechr[hh]; // water_lay dimensioned 3 and soil_rechr and soil_moist only 2D.
      water_lay[1][hh] = soil_moist[hh] - soil_rechr[hh];
      for(long ii = 0; ii < maxsoillayers ; ++ii) // [maxsoillayers][maxsoillayers]
        Temp_lay[ii][hh] = hru_t[hh]; // convert air temperature to soil temperature ???
        
    } // for hh */

    for(hh = 0; chkStruct(); ++hh){
      soil_np_processes();
    }
}

void ClassWQ_Hype::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessage(hh, string("'" + Name + " (WQ_Hype)'").c_str(), BLANK);
  }
  LogDebug(" ");
}

// Calculate nutrient processes in soil; sources, transformations, and retention
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Soil processes)
// ------------------------------------------------------------------------------

  void ClassWQ_Hype::soil_np_processes(){

        /*    USE MODVAR, ONLY : numsubstances,     & 10,     & i_in

    LOGICAL, INTENT(IN) :: calcN                    // <Status of nitrogen simulation
    LOGICAL, INTENT(IN) :: calcP                    // <Status of phosphorus simulation
    LOGICAL, INTENT(IN) :: calcC                    // <Status of organic carbon simulation
    long, INTENT(IN) :: dayno                       // <day number of the year
    float, INTENT(IN)    :: area                     // <class area (km2)
    float, INTENT(IN)    :: wp(10)        // <water content at wilting point (mm)
    float, INTENT(IN)    :: fc(10)        // <water content at field capacity (mm)
    float, INTENT(IN)    :: ep(10)        // <water content in effective porosity (mm)
    float, INTENT(IN)    :: common_uptake(2,2)       // <uptake by plants (kg NP/km2/timestep)
    float, INTENT(IN)    :: thickness[maxsoillayers] // <thickness of soil layers
    float, INTENT(IN)    :: ndays                    // <model parameter, days for fertilization
    float, INTENT(IN)    :: ldays                    // <model parameter, days for litterfall
    float, INTENT(OUT)   :: source(numsubstances)    // <source of soil water nutrients through mineralization
    float, INTENT(OUT)   :: sink(numsubstances)      // <OBS: denitrification sink only
    float, INTENT(OUT)   :: nitrification            // <nitrification
    float, INTENT(OUT)   :: denitrification(maxsoillayers)  // <denitrification
    float, INTENT(OUT)   :: cropuptake               // <crop uptake of IN
    float, INTENT(OUT)   :: sources(2,numsubstances)    // <loads of fertilizer and residuals (kg/timestep)
    float, INTENT(IN)    :: pardisfN            // <model parameter mineralisation labileN to dissolved ON
    float, INTENT(IN)    :: pardisfP            // <model parameter mineralisation labileP to dissolved OP
    float, INTENT(IN)    :: pardishN            // <model parameter mineralisation refractoryN to dissolved ON
    float, INTENT(IN)    :: pardishP            // <model parameter mineralisation refractoryP to dissolved OP
    float, INTENT(IN)    :: parminfN            // <model parameter mineralisation labileN
    float, INTENT(IN)    :: parminfP            // <model parameter mineralisation labileP
    float, INTENT(IN)    :: pardegrhN           // <model parameter degradation refractoryN
    float, INTENT(IN)    :: pardenN              // <model parameter denitrification in soil
    float, INTENT(IN)    :: pardegrhP           // <model parameter degradation refractoryP
    TYPE(soilstatetype),INTENT(INOUT)  :: soilstate // <Soil states
*/
// No substances modelled

// Calculate the nutrient processes
     crop_sources(); // fertilizer and residues, also orgC

    soil_pool_transformations();   // transformation from refractoryN->labileN->IN, ON->IN and labileP->SRP refractoryP -> labileP

    nitrification[hh] = source_lay[i_in][hh];

    plant_uptake(water_lay, conc_top_lay, conc_bottom_lay, sink_lay);

    if(i_in >= 0)
      cropuptake[hh] = sink_lay[i_in][hh];
    if(calcN[hh]){
      denitrification_lay[0][hh] = 0.0;
      denitrification_lay[1][hh] = 0.0;
      denitrification_lay[2][hh] = 0.0;

      if(thickness_lay[0][hh] > 0.0)
        soil_denitrification(wp_lay[0][hh] + fc_lay[0][hh] + ep_lay[0][hh], conc_top_lay);
      denitrification_lay[0][hh] = sink_lay[i_in][hh];
      if(thickness_lay[1][hh] > 0.0)
        soil_denitrification(wp_lay[1][hh] + fc_lay[1][hh] + ep_lay[1][hh], conc_bottom_lay);
      denitrification_lay[1][hh] = sink_lay[i_in][hh];
      if(thickness_lay[2][hh] > 0.0)
        soil_denitrification(wp_lay[2][hh] + fc_lay[2][hh] + ep_lay[2][hh], conc_below_lay);
      denitrification_lay[2][hh] = sink_lay[i_in][hh];
    }
  } // soil_np_processes

// Calculate and add the crops sources of nutrient to the soil(fertilization and crop residues).
//
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Nutrient sources - Fertilizer, Plant residues)
// --------------------------------------------------------------
      void  ClassWQ_Hype::crop_sources(){

/*
    USE MODVAR, ONLY : numsubstances, 10, cropdata, i_in,i_on,i_sp,i_pp,i_oc, prevdoy

    Argument declarations
    LOGICAL, INTENT(IN) :: calcN                    !<Status of nitrogen simulation
    LOGICAL, INTENT(IN) :: calcP                    !<Status of phosphorus simulation
    LOGICAL, INTENT(IN) :: calcC                    !<Status of organic carbon simulation
    float, INTENT(IN)    :: ndays                    !<number of days to spread fertilizer
    float, INTENT(IN)    :: ldays                    !<number of days to spread plant residuals
    float, INTENT(IN)    :: area                   !<class area (km2)
    float, INTENT(IN)    :: thickness(maxsoillayers) !<thickness of soil layers (m)
    TYPE(soilstatetype),INTENT(INOUT)  :: soilstate !<Soil states
    float, INTENT(OUT)   :: sources(2,numsubstances) !<load from fertilizer and plant residues (kg/timestep) ****now sources_i_in_lay etc.***
*/

// Local variables
    long k,kcrop;
    float common_nadd[maxsoillayers][2]; // kg/km2   where 0 - manureNpart, 1 - manureNfastpart
    float common_padd[maxsoillayers][2]; // kg/km2
    float common_nres[maxsoillayers][2]; // kg/km2
    float common_pres[maxsoillayers][2]; // kg/km2
    float common_cres[maxsoillayers][2]; // kg/km2

    float littdays;

    for(long ll = 0; ll < numsubstances; ++ll) {
      sources_fertilizer_lay[ll][hh] = 0.0;
      sources_plant_lay[ll][hh] = 0.0;
    }

    if(!(calcN[hh] || calcP[hh] || calcC[hh]))
      return;   // no substance modelled

    for (long ii = 0.0; ii < maxsoillayers; ++ii){
      for (long kk = 0.0; kk < 2; ++kk){ // kg/km2   where 0 - manureNpart, 1 - manureNfastpart
        common_nadd[ii][kk]   = 0.0;
        common_padd[ii][kk]   = 0.0;
        common_nres[ii][kk]   = 0.0;
        common_pres[ii][kk]   = 0.0;
        common_cres[ii][kk]   = 0.0;
      }
    } // for

  Word Y,M,D;
  Global::DTnow.DecodeDate(&Y,&M,&D);
  long prevdoy = (int)(EncodeDate((Word)Y-1, (Word)12, (Word)31) - EncodeDate((Word)Y-1, (Word)1, (Word)1)) + 1; // calculates #days in previous year

// Calculate common fertiliser and manure use

    if(fertday1[hh] && ((dayno >= fertday1[hh] && dayno < fertday1[hh] + fertperiod[hh])  ||
         (dayno < fertday1[hh] + fertperiod[hh] - prevdoy))){
      if(thickness_lay[1][hh] > 0.0){
        common_nadd[0][0] = common_nadd[0][inorg] + part[hh] * fertNamount1[hh] * (1.0 - fertdown1[hh]) / fertperiod[hh];
        common_padd[0][0] = common_padd[0][inorg] + part[hh] * fertPamount1[hh] * (1.0 - fertdown1[hh]) / fertperiod[hh];
        common_nadd[1][0] = common_nadd[1][inorg] + part[hh] * fertNamount1[hh] * fertdown1[hh] / fertperiod[hh]; // move some to lower layer
        common_padd[1][0] = common_padd[1][inorg] + part[hh] * fertPamount1[hh] * fertdown1[hh] / fertperiod[hh];
      }
      else{
        common_nadd[0][0] = common_nadd[0][inorg] + part[hh] * fertNamount1[hh] / fertperiod[hh];
        common_padd[0][0] = common_padd[0][inorg] + part[hh] * fertPamount1[hh] / fertperiod[hh];
      }
    } // if

    if(fertday2[hh] && ((dayno >= fertday2[hh] && dayno < fertday2[hh] + fertperiod[hh])  ||
         (dayno < fertday2[hh] + fertperiod[hh] - prevdoy))){
      if(thickness_lay[1][hh] > 0.0){
        common_nadd[0][0] = common_nadd[0][inorg] + part[hh] * fertNamount2[hh] * (1.0 - fertdown2[hh]) / fertperiod[hh];
        common_padd[0][0] = common_padd[0][inorg] + part[hh] * fertPamount2[hh] * (1.0 - fertdown2[hh]) / fertperiod[hh];
        common_nadd[1][0] = common_nadd[1][inorg] + part[hh] * fertNamount2[hh] * fertdown2[hh] / fertperiod[hh]; // move some to lower layer
        common_padd[1][0] = common_padd[1][inorg] + part[hh] * fertPamount2[hh] * fertdown2[hh] / fertperiod[hh];
      }
      else{
        common_nadd[0][0] = common_nadd[0][inorg] + part[hh] * fertNamount2[hh] / fertperiod[hh];
        common_padd[0][0] = common_padd[0][inorg] + part[hh] * fertPamount2[hh] / fertperiod[hh];
      }
    } // if

    if(manday1[hh] && ((dayno >= manday1[hh] && dayno < manday1[hh] + fertperiod[hh])  ||
         (dayno < manday1[hh] + fertperiod[hh] - prevdoy))){
      if(thickness_lay[1][hh] > 0.0){
        common_nadd[0][0] = common_nadd[0][inorg] + part[hh] * manNamount1[hh] * (1.0 - mandown1[hh]) * manureNpart[hh] / fertperiod[hh];
        common_padd[0][0] = common_padd[0][inorg] + part[hh] * manPamount1[hh] * (1.0 - mandown1[hh]) * manureNfastpart[hh] / fertperiod[hh];
        common_nadd[0][1] = common_nadd[0][fast] + part[hh] * manNamount1[hh] * (1.0 - mandown1[hh]) * (1.0 - manureNpart[hh]) / fertperiod[hh];
        common_padd[0][1] = common_padd[0][fast] + part[hh] * manPamount1[hh] * (1.0 - mandown1[hh]) * (1.0 - manureNfastpart[hh]) / fertperiod[hh];
        common_nadd[1][0] = common_nadd[1][inorg] + part[hh] * manNamount1[hh] * mandown1[hh] * manureNpart[hh] / fertperiod[hh];
        common_padd[1][0] = common_padd[1][inorg] + part[hh] * manPamount1[hh] * mandown1[hh] * manureNfastpart[hh] / fertperiod[hh];
        common_nadd[1][1] = common_nadd[1][fast] + part[hh] * manNamount1[hh] * mandown1[hh] * (1.0 - manureNpart[hh]) / fertperiod[hh];
        common_padd[1][1] = common_padd[1][fast] + part[hh] * manPamount1[hh] * mandown1[hh] * (1.0 - manureNfastpart[hh]) / fertperiod[hh];
      }
      else{
        common_nadd[0][0] = common_nadd[0][inorg] + part[hh] * manNamount1[hh] * manureNpart[hh] / fertperiod[hh];
        common_padd[0][0] = common_padd[0][inorg] + part[hh] * manPamount1[hh] * manureNfastpart[hh] / fertperiod[hh];
        common_nadd[0][1] = common_nadd[0][fast] + part[hh] * manNamount1[hh] * (1.0 - manureNpart[hh]) / fertperiod[hh];
        common_padd[0][1] = common_padd[0][fast] + part[hh] * manPamount1[hh] * (1.0 - manureNfastpart[hh]) / fertperiod[hh];
      }
    } // if

    if(manday2[hh] && ((dayno >= manday2[hh] && dayno < manday2[hh] + fertperiod[hh])  || (dayno < manday2[hh] + fertperiod[hh] - prevdoy))){
      if(thickness_lay[1][hh] > 0.0){
        common_nadd[0][0] = common_nadd[0][inorg] + part[hh] * manNamount2[hh] * (1.0 - mandown2[hh]) * manureNpart[hh] / fertperiod[hh];
        common_padd[0][0] = common_padd[0][inorg] + part[hh] * manPamount2[hh] * (1.0 - mandown2[hh]) * manureNfastpart[hh] / fertperiod[hh];
        common_nadd[0][1] = common_nadd[0][fast] + part[hh] * manNamount2[hh] * (1.0 - mandown2[hh]) * (1.-manureNpart[hh]) / fertperiod[hh];
        common_padd[0][1] = common_padd[0][fast] + part[hh] * manPamount2[hh] * (1.0 - mandown2[hh]) * (1.-manureNfastpart[hh]) / fertperiod[hh];
        common_nadd[1][0] = common_nadd[1][inorg] + part[hh] * manNamount2[hh] * mandown2[hh] * manureNpart[hh] / fertperiod[hh];
        common_padd[1][0] = common_padd[1][inorg] + part[hh] * manPamount2[hh] * mandown2[hh] * manureNfastpart[hh] / fertperiod[hh];
        common_nadd[1][1] = common_nadd[1][fast] + part[hh] * manNamount2[hh] * mandown2[hh] * (1.0-manureNpart[hh]) / fertperiod[hh];
        common_padd[1][1] = common_padd[1][fast] + part[hh] * manPamount2[hh] * mandown2[hh] * (1.0-manureNfastpart[hh]) / fertperiod[hh];
      }
      else{
        common_nadd[0][0] = common_nadd[0][inorg] + part[hh] * manNamount2[hh] * manureNpart[hh] / fertperiod[hh];
        common_padd[0][0] = common_padd[0][inorg] + part[hh] * manPamount2[hh] * manureNfastpart[hh] / fertperiod[hh];
        common_nadd[0][1] = common_nadd[0][fast] + part[hh] * manNamount2[hh] * (1.0 - manureNpart[hh]) / fertperiod[hh];
        common_padd[0][1] = common_padd[0][fast] + part[hh] * manPamount2[hh] * (1.0 - manureNfastpart[hh]) / fertperiod[hh];
      }
    } // if

// Calculate common residues

    if(resdayno[hh] == 0) // fixes cannot modify a constant
      littdays = 365.0;   // litterfall every day
    else
      littdays = litterperiod[hh]; // litterfall every day

    if(resdayno[hh] == 0  ||
         ((dayno >= resdayno[hh] && dayno < resdayno[hh] + littdays)  ||
         (dayno < resdayno[hh] + littdays - prevdoy))){
      if(thickness_lay[1][hh] > 0.0){
        common_nres[0][0] = common_nres[0][0] + resfast[hh] * part[hh] * resNamount[hh] * (1.0 - resdown[hh]) / littdays;
        common_nres[0][1] = common_nres[0][1] + (1.0 - resfast[hh]) * part[hh] * resNamount[hh] * (1.0 - resdown[hh]) / littdays;
        common_pres[0][0] = common_pres[0][0] + resfast[hh] * part[hh] * resPamount[hh] * (1.0 - resdown[hh]) / littdays;
        common_pres[0][1] = common_pres[0][1] + (1.0 - resfast[hh]) * part[hh] * resPamount[hh] * (1.0 - resdown[hh]) / littdays;
        common_nres[1][0] = common_nres[1][0] + resfast[hh] * part[hh] * resNamount[hh] * resdown[hh] / littdays;
        common_nres[1][1] = common_nres[1][1] + (1.0 - resfast[hh]) * part[hh] * resNamount[hh] * resdown[hh] / littdays;
        common_pres[1][0] = common_pres[1][0] + resfast[hh] * part[hh] * resPamount[hh] * resdown[hh] / littdays;
        common_pres[1][1] = common_pres[1][1] + (1.0 - resfast[hh]) * part[hh] * resPamount[hh] * resdown[hh] / littdays;
        common_cres[0][0] = common_cres[0][0] + part[hh] * resCamount[hh] * (1.0 - resdown[hh]) / littdays;  //CP121031
        common_cres[1][0] = common_cres[1][0] + part[hh] * resCamount[hh] * resdown[hh] / littdays;
      }
      else{
        common_nres[0][0] = common_nres[0][0] + resfast[hh] * part[hh] * resNamount[hh] / littdays;
        common_nres[0][1] = common_nres[0][1] + (1.0 - resfast[hh]) * part[hh] * resNamount[hh] / littdays;
        common_pres[0][0] = common_pres[0][0] + resfast[hh] * part[hh] * resPamount[hh] / littdays;
        common_pres[0][1] = common_pres[0][1] + (1.0 - resfast[hh]) * part[hh] * resPamount[hh] / littdays;
        common_cres[0][0] = common_cres[0][0] + part[hh] * resCamount[hh] / littdays;
      }
    }

// Add fertiliser and manure

    if(calcN[hh]  &&  SUM(common_nadd, 0) > 0.0){ // refractoryNpart F
      if(water_lay[0][hh] > 0.0){
        add_source_to_water(water_lay[0][hh], i_in, &conc_top_lay[i_in][hh], common_nadd[0][0]); // i_in
        sources_fertilizer_lay[i_in][hh] += common_nadd[0][0]*hru_area[hh]; // InorgN load from fertilizer from soil layer 1 (kg)
      }
      else{
        production_pool(labileN_lay[0][hh], common_nadd[0][0]);
        sources_fertilizer_lay[i_on][hh] += common_nadd[0][0]*hru_area[hh]; // OrgN load from fertilizer from soil layer 1 (kg)
      }

      if(water_lay[1][hh] > 0.0){
        add_source_to_water(water_lay[1][hh], i_in, &conc_bottom_lay[i_in][hh], common_nadd[1][0]);
        sources_fertilizer_lay[i_in][hh] += common_nadd[1][0]*hru_area[hh]; // InorgN load from fertilizer from soil layer 2 (kg)
      }
      else if(thickness_lay[1][hh] > 0.0){
        production_pool(labileN_lay[1][hh], common_nadd[1][0]);
        sources_fertilizer_lay[i_on][hh] += common_nadd[1][0]*hru_area[hh]; // OrgN load from fertilizer from soil layer 2 (kg)
      }
    }

    if(calcP[hh]  &&  SUM(common_padd, 0) > 0.0){ // G
      if(water_lay[0][hh] > 0.0){
        add_source_to_water(water_lay[0][hh], i_sp , &conc_top_lay[i_sp][hh], common_padd[0][0]);
        sources_fertilizer_lay[i_sp][hh] += common_padd[0][0]*hru_area[hh];        // SRP load from fertilizer, soil layer 1 (kg)
      }
      else{
        production_pool(labileP_lay[0][hh], common_padd[0][0]);
        sources_fertilizer_lay[i_pp][hh] += common_padd[0][0]*hru_area[hh]; // PartP load from fertilizer, soil layer 1 (kg)
      }

      if(water_lay[1][hh] > 0.0){
        add_source_to_water(water_lay[1][hh], 1 , &conc_bottom_lay[i_sp][hh], common_padd[1][0]);
        sources_fertilizer_lay[i_sp][hh] += common_padd[1][0]*hru_area[hh]; // SRP load from fertilizer, soil layer 2 (kg)
      }
      else if(thickness_lay[1][hh] > 0.0){
        production_pool(labileP_lay[1][hh], common_padd[1][0]);
        sources_fertilizer_lay[i_pp][hh] += common_padd[1][0]*hru_area[hh]; // PartP load from fertilizer, soil layer 2 (kg)
      }
    }

    if(calcN[hh] && SUM(common_nadd, 1) > 0.0){ // refractoryNfastpart H
      if(thickness_lay[1][hh] > 0.0){
        production_pool(labileN_lay, common_nadd, 1); // :::
        sources_fertilizer_lay[i_on][hh] += SUM(common_nadd, 2)*hru_area[hh];  // OrgN load from fertilizer, both soil layers (kg)  ??? matrix
      }
      else{
        production_pool(labileN_lay, common_nadd, 1);
        sources_fertilizer_lay[i_on][hh] += common_nadd[1][2]*hru_area[hh];       // OrgN load from fertilizer, soil layer 1 (kg) ??? matrix
      }
    }

    if(calcP[hh]  &&  SUM(common_padd, 1) > 0.0){ // I
      if(thickness_lay[1][hh] > 0.0){
        production_pool(labileP_lay, common_padd, 1); // :::
        sources_fertilizer_lay[i_pp][hh] += SUM(common_padd, 1)*hru_area[hh]; // PartP load from fertilizer, both soil layers (kg)   ??? matrix
      }
      else{ // I
        production_pool(labileP_lay, common_padd, 1);
        sources_fertilizer_lay[i_pp][hh] += common_padd[0][1]*hru_area[hh]; // PartP load from fertilizer, soil layer 1 (kg)   ??? matrix
      }
    }

// Add residues

    if(calcN[hh]  &&  (SUM(common_nres, 0) + SUM(common_nres, 1)) > 0.0){ // J
      if(thickness_lay[1][hh] > 0.0){
         production_pool(labileN_lay, common_nres, 0); // :::
         production_pool(refractoryN_lay, common_nres, 1);
      }
      else{
         production_pool(labileN_lay[0][hh], common_nres[0][0]);
         production_pool(refractoryN_lay[0][hh], common_nres[0][1]);
      }
      sources_plant_lay[i_on][hh] = (SUM(common_nres, 0) + SUM(common_nres, 1))*hru_area[hh]; // OrgN load from residuals, all soil layers and N types (kg)
    }

    if(calcP[hh] && (SUM(common_pres, 0) + SUM(common_pres, 1)) > 0.0){ // K
      if(thickness_lay[1][hh]  > 0.0){
         production_pool(labileP_lay[0][hh], common_pres[0][0]);
         production_pool(refractoryP_lay[0][hh], common_pres[0][1]);
      }
      else{
         production_pool(labileP_lay[0][hh], common_pres[0][0]);
         production_pool(refractoryP_lay[0][hh], common_pres[0][1]);
      }
      sources_plant_lay[i_pp][hh] = (SUM(common_pres, 0) + SUM(common_pres, 1))*hru_area[hh]; // PartP load from residuals, all soil layers and P types (kg)
    }

    if(calcC[hh]  &&  (SUM(common_cres, 0) + SUM(common_cres, 1)) > 0.0){ // L
      if(thickness_lay[1][hh] > 0.0)
         production_pool(labileC_lay, common_cres, 0); // :::
      else // L
         production_pool(labileC_lay[0][hh], common_cres[0][0]); // :::

      sources_plant_lay[i_oc][hh] = (SUM(common_cres, 0) + SUM(common_cres, 1))*hru_area[hh]; // OrgC load from residuals, all soil layers (kg)
    }
  }  // crop_sources

// Transformation between NP-pools in soil. Degradation/delay functions.
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Soil processes)
// ------------------------------------------------------------------------------

    void ClassWQ_Hype::soil_pool_transformations(){
/*
    USE MODVAR, ONLY : numsubstances, maxsoillayers, i_in,i_on,i_sp,i_pp

    USE HYPEVARIABLES, ONLY : satact, Thetapow, Thetalow,T hetaupp

Argument declarations
    LOGICAL, INTENT(IN) :: calcN    !<flag for nitrogen simulation
    LOGICAL, INTENT(IN) :: calcP    !<flag for phosphorus simulation
    float, INTENT(IN)    :: wp(maxsoillayers)        !<water content at wilting point (mm)
    float, INTENT(IN)    :: fc(maxsoillayers)        !<water content at field capacity (mm)
    float, INTENT(IN)    :: ep(maxsoillayers)        !<water content: effectiv porosity (mm)
    float, INTENT(IN)    :: thickness(maxsoillayers) !<thickness of soil layers
    float, INTENT(OUT)   :: source(numsubstances)    !<source of soil water nutrients through mineralization
    float, INTENT(IN)    :: pardisfN            !<model parameter mineralisation labileN to dissolved ON
    float, INTENT(IN)    :: pardisfP            !<model parameter mineralisation labileP to dissolved OP
    float, INTENT(IN)    :: pardishN            !<model parameter mineralisation refractoryN to dissolved ON
    float, INTENT(IN)    :: pardishP            !<model parameter mineralisation refractoryP to dissolved OP
    float, INTENT(IN)    :: minfNpar            !<model parameter mineralisation labileN
    float, INTENT(IN)    :: minfPpar            !<model parameter mineralisation labileP
    float, INTENT(IN)    :: degrhNpar           !<model parameter degradation refractoryN
    float, INTENT(IN)    :: degrhPpar           !<model parameter degradation refractoryP
    TYPE(soilstatetype),INTENT(INOUT)  :: soilstate !<Soil states
*/

// Local variables
    long k;   // soillayer
    float degradhN[maxsoillayers] ,transfN[maxsoillayers];
    float transfP[maxsoillayers], degradhP[maxsoillayers];
    float dissolfN[maxsoillayers], dissolfP[maxsoillayers];
    float dissolhN[maxsoillayers], dissolhP[maxsoillayers];
    float tmpfcn[maxsoillayers];
    float smfcn[maxsoillayers]; // sm[maxsoillayers],

    source[hh] = 0.0;
    
    for(long ii = 0; ii < numsubstances ; ++ii){ // [numsubstances][maxsoillayers]
      source_lay[ii][hh] = 0.0;
    }

    for(long ii = 0; ii < maxsoillayers ; ++ii){ // [maxsoillayers][maxsoillayers]
      DINpool_lay[ii][hh] = 0.0;
      SRPpool_lay[ii][hh] = 0.0;
      DONpool_lay[ii][hh] = 0.0;
      DOPpool_lay[ii][hh] = 0.0;
      degradhN[ii] = 0.0;
      transfN[ii] = 0.0;
      dissolfN[ii] = 0.0;
      dissolhN[ii] = 0.0;
      degradhP[ii] = 0.0;
      transfP[ii] = 0.0;
      dissolfP[ii] = 0.0;
      dissolhP[ii] = 0.0;
      smfcn[ii] = 0.0;
    }

// Current pools of N and P dissolved in soil water

    if(calcN[hh]){
      DINpool_lay[0][hh] = conc_top_lay[i_in][hh] * water_lay[0][hh];
      DONpool_lay[0][hh] = conc_top_lay[i_on][hh] * water_lay[0][hh];

      if(thickness_lay[1][hh] > 0.0){
        DINpool_lay[1][hh] = conc_bottom_lay[i_in][hh] * water_lay[1][hh];
        DONpool_lay[1][hh] = conc_bottom_lay[i_on][hh] * water_lay[1][hh];
      }

      if(thickness_lay[2][hh] > 0.0){
        DINpool_lay[2][hh] = conc_below_lay[i_in][hh] * water_lay[2][hh];
        DONpool_lay[2][hh] = conc_below_lay[i_on][hh] * water_lay[2][hh];
      }
    }

    if(calcP[hh]){
      SRPpool_lay[0][hh] = conc_top_lay[i_sp][hh] * water_lay[0][hh];
      DOPpool_lay[0][hh] = conc_top_lay[i_pp][hh] * water_lay[0][hh];
      if(thickness_lay[1][hh] > 0.0){
        SRPpool_lay[1][hh] = conc_bottom_lay[i_sp][hh] * water_lay[1][hh];
        DOPpool_lay[1][hh] = conc_bottom_lay[i_pp][hh] * water_lay[1][hh];
      }
      if(thickness_lay[2][hh] > 0.0){
        SRPpool_lay[2][hh] = conc_below_lay[i_sp][hh] * water_lay[2][hh];
        DOPpool_lay[2][hh] = conc_below_lay[i_pp][hh] * water_lay[2][hh];
      }
    }

// Temperature dependence factor

    for (long k = 0; k < maxsoillayers; ++k)
      if(thickness_lay[k][hh] > 0.0)
        tmpfcn[k] = tempfactor(Temp_lay[k][hh]); // requires soil temperature
      
// Soil moisture dependence factor

    smfcn[0] = moisturefactor(water_lay[0][hh], wp_lay[0][hh], wp_lay[0][hh]+fc_lay[0][hh]+ep_lay[0][hh], thickness_lay[0][hh], satact, thetapow, thetalow, thetaupp);
    smfcn[1] = moisturefactor(water_lay[1][hh], wp_lay[1][hh], wp_lay[1][hh]+fc_lay[1][hh]+ep_lay[1][hh], thickness_lay[1][hh], satact, thetapow, thetalow, thetaupp);
    smfcn[2] = moisturefactor(water_lay[2][hh], wp_lay[2][hh], wp_lay[2][hh]+fc_lay[2][hh]+ep_lay[2][hh], thickness_lay[2][hh], satact, thetapow, thetalow, thetaupp);

// Degradation of refractoryN to labileN

    if(calcN[hh]){
      degradhN[0] = pardegrhN[hh] * tmpfcn[0] * smfcn[0]* refractoryN_lay[0][hh];
      degradhN[1] = pardegrhN[hh] * tmpfcn[1] * smfcn[1]* refractoryN_lay[1][hh];
      degradhN[2] = pardegrhN[hh] * tmpfcn[2] * smfcn[2]* refractoryN_lay[2][hh];

      if(thickness_lay[2][hh] > 0.0){
         retention_pool(refractoryN_lay, degradhN, 3); // subtract - may change degradhN
         production_pool(labileN_lay, degradhN, 3); // add
      }
      else if(thickness_lay[1][hh] > 0.0){
         retention_pool(refractoryN_lay, degradhN, 3);      // subtract - may change degradhN  1:2
         production_pool(labileN_lay, degradhN, 3);      // add                        1:2
      }
      else{
         retention_pool(refractoryN_lay, degradhN, 3);      // subtract - may change degradhN
         production_pool(labileN_lay, degradhN, 3);      // add
      }

// Transformation of labileN to inorganic N

      transfN[0] = parminfN[hh] * tmpfcn[0] * smfcn[0] * labileN_lay[0][hh];     // kanske inte gÃ¶dseltillskott borde bero pÃ¥ Temp??
      transfN[1] = parminfN[hh] * tmpfcn[1] * smfcn[1] * labileN_lay[1][hh];
      transfN[2] = parminfN[hh] * tmpfcn[2] * smfcn[2] * labileN_lay[2][hh];

      if(thickness_lay[2][hh] > 0.0){
         retention_pool(labileN_lay, transfN, 3); // subtract - transfN may change in retention_pool
         production_pool(DINpool_lay, hh, transfN, 3);   // add
      }
      else if(thickness_lay[1][hh] > 0.0){
         retention_pool(labileN_lay, transfN, 3); // subtract - transfN may change in retention_pool (1:2)
         production_pool(DINpool_lay, hh, transfN, 3);   // add                                            //   (1:2)
      }
      else{
         retention_pool(labileN_lay, transfN, 3); // subtract - transfN may change in retention_pool
         production_pool(DINpool_lay, hh, transfN, 3);   // add
      }

// Calculate the new soil concentrations of IN

       new_concentration(DINpool_lay[0][hh], water_lay[0][hh], &conc_top_lay[i_in][hh]);
      if(thickness_lay[1][hh] > 0.0)
        new_concentration(DINpool_lay[1][hh], water_lay[1][hh], &conc_bottom_lay[i_in][hh]);
      if(thickness_lay[2][hh] > 0.0)
        new_concentration(DINpool_lay[2][hh],water_lay[2][hh], &conc_below_lay[i_in][hh]);
    } // calcN

// Degradation of refractoryP to labileP

    if(calcP[hh]){
      degradhP[0] = pardegrhP[hh] * tmpfcn[0] * smfcn[0] * refractoryP_lay[0][hh];
      degradhP[1] = pardegrhP[hh] * tmpfcn[1] * smfcn[1] * refractoryP_lay[1][hh];
      degradhP[2] = pardegrhP[hh] * tmpfcn[2] * smfcn[2] * refractoryP_lay[2][hh];

      if(thickness_lay[2][hh] > 0.0){
         retention_pool(refractoryP_lay, degradhP, 3); // subtract - may change degradhP
         production_pool(labileP_lay, degradhP, 3); // add
      }
      else if(thickness_lay[1][hh] > 0.0){
         retention_pool(refractoryP_lay, degradhP, 3); // subtract - may change degradhP  1:2
         production_pool(labileP_lay, degradhP, 3); // add
      }
      else{
         retention_pool(refractoryP_lay, degradhP, 3); // subtract - may change degradhP   1:2
         production_pool(labileP_lay, degradhP, 3); // add
      }

// Transformation of labileP to SRP

      transfP[0] = parminfP[hh] * tmpfcn[0] * smfcn[0] * labileP_lay[0][hh];
      transfP[1] = parminfP[hh] * tmpfcn[1] * smfcn[1] * labileP_lay[1][hh];
      transfP[2] = parminfP[hh] * tmpfcn[2] * smfcn[2] * labileP_lay[2][hh];

      if(thickness_lay[2][hh] > 0.0){
         retention_pool(labileP_lay, transfP, 3); // subtract - transfP may change in retention_pool
         production_pool(SRPpool_lay, hh, transfP, 3);
      }
      else if(thickness_lay[1][hh] > 0){
         retention_pool(labileP_lay, transfP, 3); // subtract - transfP may change in retention_pool
         production_pool(SRPpool_lay, hh, transfP, 3);
      }
      else{
         retention_pool(labileP_lay, transfP, 3); // subtract - transfP may change in retention_pool
         production_pool(SRPpool_lay, hh, transfP, 3);
      }

// Calculate the new soil concentrations of SRP

       new_concentration(SRPpool_lay[0][hh], water_lay[0][hh], &conc_top_lay[i_sp][hh]);
      if(thickness_lay[1][hh] > 0.0)
        new_concentration(SRPpool_lay[1][hh], water_lay[1][hh], &conc_bottom_lay[i_sp][hh]);
      if(thickness_lay[2][hh] > 0.0)
        new_concentration(SRPpool_lay[2][hh], water_lay[2][hh], &conc_below_lay[i_sp][hh]);
    } // calcP

// Transformation of labileN to dissolved organic N

    if(calcN[hh]){
      dissolfN[0] = pardisfN[hh] * tmpfcn[0] * smfcn[0] * labileN_lay[0][hh];
      dissolfN[1] = pardisfN[hh] * tmpfcn[1] * smfcn[1] * labileN_lay[1][hh];
      dissolfN[2] = pardisfN[hh] * tmpfcn[2] * smfcn[2] * labileN_lay[2][hh];

      if(thickness_lay[2][hh] > 0.0){
         retention_pool(labileN_lay, dissolfN, 3); // subtract - dissolfN may change in retention_pool
         production_pool(DONpool_lay, hh, dissolfN, 3);
      }
      else if(thickness_lay[1][hh] > 0.0){
         retention_pool(labileN_lay, dissolfN, 3); // subtract - dissolfN may change in retention_pool
         production_pool(DONpool_lay, hh, dissolfN, 3);
      }
      else{
         retention_pool(labileN_lay, dissolfN, 3); // subtract - dissolfN may change in retention_pool
         production_pool(DONpool_lay, hh, dissolfN, 3);
      }

// Transformation of refractoryN to dissolved organic N

      dissolhN[0] = pardishN[hh] * tmpfcn[0] * smfcn[0] * refractoryN_lay[0][hh];
      dissolhN[1] = pardishN[hh] * tmpfcn[1] * smfcn[1] * refractoryN_lay[1][hh];
      dissolhN[2] = pardishN[hh] * tmpfcn[2] * smfcn[2] * refractoryN_lay[2][hh];

      if(thickness_lay[2][hh] > 0.0){
         retention_pool(refractoryN_lay, dissolhN, 3); // subtract - dissolhN may change in retention_pool
         production_pool(DONpool_lay, hh, dissolhN, 3);       // add
      }
      else if(thickness_lay[1][hh] > 0.0){
         retention_pool(refractoryN_lay, dissolhN, 3); // subtract - dissolhN may change in retention_pool
         production_pool(DONpool_lay, hh, dissolhN, 3);       // add
      }
      else{
         retention_pool(refractoryN_lay, dissolhN, 3); // subtract - dissolhN may change in retention_pool
         production_pool(DONpool_lay, hh, dissolhN, 3);       // add
      }

// Calculate the new soil concentrations of ON

      new_concentration(DONpool_lay[0][hh], water_lay[0][hh], &conc_top_lay[i_on][hh]);
      new_concentration(DONpool_lay[1][hh], water_lay[1][hh], &conc_bottom_lay[i_on][hh]);
      new_concentration(DONpool_lay[2][hh], water_lay[2][hh], &conc_below_lay[i_on][hh]);

      if(thickness_lay[1][hh] > 0.0)
        new_concentration(DONpool_lay[1][hh], water_lay[1][hh], &conc_bottom_lay[i_on][hh]);

      if(thickness_lay[2][hh] > 0.0)
        new_concentration(DONpool_lay[3][hh], water_lay[2][hh], &conc_below_lay[i_on][hh]);
    } // calcN


// Transformation of labileP to dissolved organic P (DOP/PP)

    if(calcP[hh]){
      dissolfP[0] = pardisfP[hh] * tmpfcn[0] * smfcn[0] * labileP_lay[0][hh];
      dissolfP[1] = pardisfP[hh] * tmpfcn[1] * smfcn[1] * labileP_lay[1][hh];
      dissolfP[2] = pardisfP[hh] * tmpfcn[2] * smfcn[2] * labileP_lay[2][hh];

      if(thickness_lay[2][hh] > 0.0){
         retention_pool(labileP_lay, dissolfP, 3); // subtract - dissolfP may change in retention_pool
         production_pool(DOPpool_lay, hh, dissolfP, 3);      // add
      }
      else if(thickness_lay[1][hh] > 0.0){
         retention_pool(labileP_lay, dissolfP, 3); // subtract - dissolfP may change in retention_pool
         production_pool(DOPpool_lay, hh, dissolfP, 3);      // add
      }
      else{
         retention_pool(labileP_lay, dissolfP, 3); // subtract - dissolfP may change in retention_pool
         production_pool(DOPpool_lay, hh, dissolfP, 3);      // add
      }

// Transformation of refractoryP to dissolved organic P

      dissolhP[0] = pardishP[hh] * tmpfcn[0] * smfcn[0] * refractoryP_lay[0][hh];
      dissolhP[1] = pardishP[hh] * tmpfcn[1] * smfcn[1] * refractoryP_lay[1][hh];
      dissolhP[2] = pardishP[hh] * tmpfcn[2] * smfcn[2] * refractoryP_lay[2][hh];

      if(thickness_lay[2][hh] > 0.0){
         retention_pool(refractoryP_lay, dissolhP, 3); // subtract - dissolhP may change in retention_pool;
         production_pool(DOPpool_lay, hh, dissolhP, 3);       // add
      }
      else if(thickness_lay[1][hh] > 0.0){
         retention_pool(refractoryP_lay, dissolhP, 3); // subtract - dissolhP may change in retention_pool
         production_pool(DOPpool_lay, hh, dissolhP, 3);       // add
      }
      else{
         retention_pool(refractoryP_lay, dissolhP, 3); // subtract - dissolhP may change in retention_pool
         production_pool(DOPpool_lay, hh, dissolhP, 3);       // add
      }

// Calculate the new soil concentrations of PP (DOP)

      new_concentration(DOPpool_lay[0][hh], water_lay[0][hh], &conc_top_lay[i_pp][hh]);
      if(thickness_lay[1][hh] > 0.0)
        new_concentration(DOPpool_lay[1][hh], water_lay[1][hh], &conc_bottom_lay[i_pp][hh]);
      if(thickness_lay[2][hh]> 0.0)
        new_concentration(DOPpool_lay[2][hh], water_lay[2][hh], &conc_below_lay[i_pp][hh]);
    } // calcP

// Sum the sources (kg/km2)

    if(calcN[hh]){
       source_lay[i_in][hh] = SUM(transfN);
       source_lay[i_on][hh] = SUM(dissolfN) + SUM(dissolhN);
    }

    if(calcP[hh]){
       source_lay[i_sp][hh] = SUM(transfP);
       source_lay[i_pp][hh] = SUM(dissolfP) + SUM(dissolhP);
    }
  }  // soil_pool_transformations

// Calculate retention in soil due to plant uptake
// Inorganic nitrogen and phosphorus is removed.
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Soil processes - Vegetation nutrient uptake)
// -------------------------------------------------------------------
    void  ClassWQ_Hype::plant_uptake(float **soil_lay, float **conc_top_lay, float **conc_bottom_lay, float **sink_lay){

//    USE MODVAR, ONLY : numsubstances, maxsoillayers, i_in, i_sp

// Argument declarations
//    LOGICAL, INTENT(IN) :: calcN                     !<flag for nitrogen simulation
//    LOGICAL, INTENT(IN) :: calcP                     !<flag for phosphorus simulation
//    float, INTENT(IN)    :: common_uptake[2][2]      !<plant uptake (kg/km2/d), (N:P,sl1:sl2) [numsubstances(2)][maxsoillayers(2)]
//    float, INTENT(IN)    :: wp[maxsoillayers]        !<water content at wilting point (mm)
//    float, INTENT(IN)    :: thickness[maxsoillayers] !<thickness of soil layers
//    float, INTENT(IN)    :: soil[maxsoillayers]      !<soil moisture (mm)
//    float, INTENT(INOUT) :: conc(numsubstances,maxsoillayers)  !<concentration in soil moisture (mg/L etc)
//    float, INTENT(OUT)   :: sink(numsubstances)      !<sink of nutrients in this subroutine (kg/km2)

// Local variables
    float maxpooluptake[maxsoillayers2];

//    for(long kk = 0; kk < maxsoillayers2; ++kk){
//      DINpool_lay[kk][hh] = 0.0;
//      SRPpool_lay[kk][hh] = 0.0;
//      uptakeN_lay[kk][hh] = 0.0;
//      uptakeP_lay[kk][hh] = 0.0;
//    }

    for(long kk = 0; kk < numsubstances; ++kk)
      sink_lay[kk][hh] = 0.0;

    if(calcN[hh]){
      DINpool_lay[0][hh] = conc_top_lay[i_in][hh] * soil_lay[0][hh]; // soil_lay[soillayer][hru] and conc_lay[substance][soillayer]
      if(thickness_lay[1][hh] > 0.0)
        DINpool_lay[1][hh] = conc_bottom_lay[i_in][hh] * soil_lay[1][hh];
    }

    if(calcP[hh]){
      SRPpool_lay[0][hh] = conc_top_lay[i_sp][hh] * soil_lay[0][hh];
      if(thickness_lay[1][hh] > 0.0)
        SRPpool_lay[1][hh] = conc_bottom_lay[i_sp][hh] * soil_lay[1][hh];
    }

    maxpooluptake[0] = 0.0;
    maxpooluptake[1] = 0.0;

    if(soil_lay[0][hh] > 0.0)
      maxpooluptake[0] = soil_lay[0][hh]; // Maximum uptake dependent on soil moisture   - wp_lay[0][hh])/soil_lay[0][hh]
    if(thickness_lay[1][hh] > 0.0 && soil_lay[1][hh] > 0.0)
      maxpooluptake[1] = soil_lay[1][hh]; //  - wp_lay[1][hh])/soil_lay[1][hh]

// Calculate plant nutrient uptake

    if(calcN[hh]){
      uptakeN[0] = min <float>(N_uptake_lay[0][hh], maxpooluptake[0]*DINpool_lay[0][hh]);
      if(thickness_lay[1][hh] > 0.0)
        uptakeN[1] = min<float>(N_uptake_lay[1][hh], maxpooluptake[1]*DINpool_lay[1][hh]);

      if(thickness_lay[1][hh] > 0.0)
         retention_pool(DINpool_lay, hh, uptakeN, 2); // uptake may change in retention_pool ?
      else
         retention_pool(DINpool_lay, hh, uptakeN, 2); // uptake may change in retention_pool ?
    }

    if(calcP[hh]){
      uptakeP[0] = min<float>(P_uptake_lay[0][hh], maxpooluptake[0]*SRPpool_lay[0][hh]); // ??? matrix multiplication
      if(thickness_lay[1][hh] > 0.0)
        uptakeP[1] = min<float>(P_uptake_lay[1][hh], maxpooluptake[1]*SRPpool_lay[1][hh]); // ??? matrix multiplication

      if(thickness_lay[1][hh] > 0.0)
         retention_pool(SRPpool_lay, hh, uptakeP, 2);
      else
         retention_pool(SRPpool_lay, hh, uptakeP, 2);
    }

// Sum up the sinks (kg/km2)

    if(calcN[hh]){
      if(thickness_lay[1][hh] > 0.0)
        sink_lay[i_in][hh] = uptakeN[0] + uptakeN[1];
      else
        sink_lay[i_in][hh] = uptakeN[0];
    }

    if(calcP[hh]){
      if(thickness_lay[1][hh] > 0.0)
        sink_lay[i_sp][hh] = uptakeP[0] + uptakeP[1];
      else{
        sink_lay[i_sp][hh] = uptakeP[0];
      }
    }

// Calculate the new soil concentrations

    if(calcN[hh]){
       new_concentration(DINpool_lay[0][hh], soil_lay[0][hh], &conc_top_lay[i_in][hh]);
      if(thickness_lay[1][hh] > 0.0)
        new_concentration(DINpool_lay[1][hh], soil_lay[1][hh], &conc_bottom_lay[i_in][hh]);
    }

    if(calcP[hh]){
       new_concentration(SRPpool_lay[0][hh], soil_lay[0][hh], &conc_top_lay[i_sp][hh]);
      if(thickness_lay[1][hh] > 0.0)
        new_concentration(SRPpool_lay[1][hh], soil_lay[1][hh], &conc_bottom_lay[i_sp][hh]);
    }
  }  // plant_uptake

// Calculate retention in soil due to denitritfication
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Soil processes - Denitrification)
// ----------------------------------------------------------------------

  void  ClassWQ_Hype::soil_denitrification(const float maxwc, float **conc_lay){

// Argument declarations
//    float, INTENT(IN)    :: maxwc;        // <Maximum water content of soil (mm) !!! using soil_moist_max
//    float, INTENT(IN)    :: pardenN;       // <model parameter denitrification in soil
//    float, INTENT(IN)    :: soil;         // <soil water (mm) !!! using soil_moist
//    float, INTENT(IN)    :: stemp;        // <soil temperature (degree Celcius) !!! using temperature
//    float, INTENT(INOUT) :: concreview pc transfer new computer
(numsubstances);     // <concentration of soil water
//    float, INTENT(OUT)   :: sink(numsubstances);      // <sink of nutrient in this subroutine (kg/km2)

// Local variables
    float denitr[1];
    float tmpfcn, smfcn, concfcn ;

    // Substance modelled
    for(long kk = 0; kk < numsubstances; ++kk)
      sink_lay[kk][hh] = 0.0;

//    DINpool_lay[i_in][hh] = conc_lay[i_in][hh] * soil_moist[hh];    // Initial IN pool. conc_lay[substances][layers]

// Dependence factors of denitrification

    tmpfcn = tempfactor(Temp_lay[0][hh]);
    smfcn = exponential_moisturefactor(soil_moist[hh], soil_moist_max[hh], smfdenitlim, smfdenitpow);
    concfcn = halfsatconcfactor(conc_lay[i_in][hh], halfsatINsoil);

// Denitrification

    denitr[0] = pardenN[hh] * DINpool[0] * tmpfcn * smfcn * concfcn;
    retention_pool(DINpool_lay, denitr, 1); // denitr may change in retention_pool;

// Set the sink (kg/km2)
    sink_lay[i_in][hh] = denitr[0];

// Calculate the new soil concentrations
     new_concentration(DINpool_lay[i_in][hh], soil_moist[hh], &conc_lay[i_in][hh]);

  } // soil_denitrification

//---------------------------------------------------------------
// Calculates a temperature factor
// Based on: Q10=2,reference rate is at 20 degrees and with
// thresholds at 0 and 5 degrees (from COUP-model).
//
// @param[in] temperature Current temperature
// --------------------------------------------------------------
  float ClassWQ_Hype::tempfactor(float temperature){

// Local variables
    float fcn;

    fcn = pow(2.0, ((temperature - 20.0) / 10.0));
    if(temperature < 5.0) fcn = fcn * (temperature / 5.0);
    if(temperature < 0.0)  fcn = 0.0;
    return fcn;
  } // tempfactor

  //-----------------------------------------------------------------------------
  // Calculates a soil moisture dependence factor
  //
  // @param[in] sm       Soil moisture (mm)
  // @param[in] wp       Wilting point pore wolume (mm)
  // @param[in] pw       Total pore wolume (mm)
  // @param[in] thickm   Thickness of soil layer (m)
  // @param[in] satsmf   Saturated moisturefactor (satact)
  // @param[in] exp      Exponent of moisturefactor (thetapow)
  // @param[in] thetalow Low(?) moisture coefficient (thetalow)
  // @param[in] thetaupp High(?) moisture coefficient (thetaupp)
  //-----------------------------------------------------------------------------
  float ClassWQ_Hype::moisturefactor(float sm, float wp, float pw, float thickm, float satsmf, float exp, float thetalow, float thetaupp){
/*
    REAL, INTENT(IN)  :: sm     !soil moisture (mm)
    REAL, INTENT(IN)  :: wp     !wilting point pore wolume (mm)
    REAL, INTENT(IN)  :: pw     !total pore wolume (mm)
    REAL, INTENT(IN)  :: thickm !thickness of soil layer (m)
    REAL, INTENT(IN)  :: satsmf !saturated moisturefactor (satact)
    REAL, INTENT(IN)  :: exp    !exponent of moisturefactor (thetapow)
    REAL, INTENT(IN)  :: thetalow !low(?) moisture coefficient (thetalow)
    REAL, INTENT(IN)  :: thetaupp !high(?) moisture coefficient (thetaupp)
*/
// Local variables
    float thickness;  // thickness of soil layer (mm)
    float smfcn;     // soil moisture dependence factor

// Initiations
    smfcn = 0.0;
    thickness = thickm * 1000.0;      // mm

// Caclulate soilmoisture function value
    if(thickness > 0){
       if(sm >= pw)
          smfcn = satsmf;
       else if(sm <= wp)
          smfcn=0.0;
       else{
//        smfcn = min(1., (1-satsmf)*((pw-sm)/((thetaupp/100.)*thickness))**exp + satsmf, ((sm-wp)/((thetalow/100.)*thickness))**exp)
//        smfcn = min(1., (1-satsmf)*
//                           ((pw-sm)/(thetaupp/100.0*thickness))**exp + satsmf,
//                            ((sm-wp)/
//                            ((thetalow/100.)*thickness))**exp)

          float Ans = min <float> (1.0, (1.0-satsmf)*pow((pw-sm)/(thetaupp/100.0*thickm), exp) + satsmf);
          
          smfcn = min <float> (Ans, pow((sm-wp)/((thetalow/100.)*thickness), exp));
       }
    }

    return smfcn;

  } // FUNCTION moisturefactor

// Calculate eroded particles from soil and attached P
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Vegetation
//   and soil surface processes - Erosion calculations, Crop cover and ground cover)

// landuses: 1=Agricultural land 2=Forest 3=Bare rock, 4=Springcrops_autumnplough, 5=Wintercrops, 6=Rowcrops, 7=Oilseeds,
//           8=Intensive grassland,9=Extensive grassland, Springcrops_springplough, , , , , , , , , , , , ,

// jordart: 1=clay 2=till soils 3=bare rock/shallow soils, , , , , , , , , , , , ,
// combination(SLC), Landuse, Soil, cropid-main, cropid-2nd, crop-rotation, vegetation-type, Special-classes, tile-depth, drain-depth, #soil-layers, depth1, depth2, depth3
// Subroutine for organic carbon transformation processes in the soil
// Reference ModelDescription Chapter Organic carbon (Source of organic material and Soil processes)
// -----------------------------------------------------------------
  void ClassWQ_Hype::soil_carbon_processes(){
/*
    USE MODVAR, ONLY : maxsoillayers

    REAL, INTENT(IN)    :: klh      !<transformation parameter
    REAL, INTENT(IN)    :: klo      !<rate of transformation
    REAL, INTENT(IN)    :: kho      !<rate of transformation
    REAL, INTENT(IN)    :: kof      !<rate of transformation
    REAL, INTENT(IN)    :: koflim   !<threshold for transformation
    REAL, INTENT(IN)    :: minc     !<fraction mineralisation to DIC (-)
    REAL, INTENT(IN)    :: soimf    !<saturation soilmoisture factor (-)
    REAL, INTENT(IN)    :: soimr    !<rate soilmoisture factor (-)
    TYPE(soilstatetype),INTENT(INOUT)  :: soilstate   !<Soil states
*/
// Calculate the nutrient processes

    soil_carbon_pool_transformations();

  } // END SUBROUTINE soil_carbon_processes

// Subroutine for organic carbon transformation between pools in the soil
// Reference ModelDescription Chapter Organic carbon (Soil processes)
// --------------------------------------------------------------------
  void ClassWQ_Hype::soil_carbon_pool_transformations(){
/*
    USE MODVAR, ONLY : maxsoillayers,i_oc
    USE HYPEVARIABLES, ONLY :   &
         thetapow,thetalow,thetaupp

    !Argument declaration
    REAL, INTENT(IN)    :: wp(maxsoillayers)        !<water content at wilting point (mm)
    REAL, INTENT(IN)    :: fc(maxsoillayers)        !<water content at field capacity (mm)
    REAL, INTENT(IN)    :: pw(maxsoillayers)        !<water content: total porosity (mm)
    REAL, INTENT(IN)    :: thickness(maxsoillayers) !<thickness of soil layers
    REAL, INTENT(IN)    :: klh      !<transformation rate of labileC to refractoryC (d-1)
    REAL, INTENT(IN)    :: klo      !<degradation labileC (d-1)
    REAL, INTENT(IN)    :: kho      !<degradation refractoryC (d-1)
    REAL, INTENT(IN)    :: kof      !<transformation to labileC (d-1)
    REAL, INTENT(IN)    :: koflim   !<threshold for transformation to labileC (-)
    REAL, INTENT(IN)    :: minc     !<fraction mineralisation to DIC (-)
    REAL, INTENT(IN)    :: soimf    !<satuaration soilmoisture factor (-)
    REAL, INTENT(IN)    :: soimr    !<rate soilmoisture factor (-)
    TYPE(soilstatetype),INTENT(INOUT)  :: soilstate   !<Soil states
*/

// Local variables

    long k;   // soillayer
    float DOCpool[maxsoillayers];
    float fasttorefractory[maxsoillayers];
    float doctofast[maxsoillayers];
    float transhC[maxsoillayers];
    float transfC[maxsoillayers];
    float tmpfcn[maxsoillayers], smfcn[maxsoillayers];
    float real1temp[1];  // Local variableshelpvariable, needed for gfortran
    float fracprod;

    // Local variables Initialisation

    if(calcC[hh] == 0)
      return;

    DOCpool[0] = water_lay[0][hh] * conc_top_lay[i_oc][hh];    // soilstate%water(:,j,i) * soilstate%conc(i_oc,:,j,i)
    DOCpool[1] = water_lay[1][hh] * conc_bottom_lay[i_oc][hh]; // soilstate%water(:,j,i) * soilstate%conc(i_oc,:,j,i)
    DOCpool[2] = water_lay[2][hh] * conc_below_lay[i_oc][hh];  // soilstate%water(:,j,i) * soilstate%conc(i_oc,:,j,i)

    fracprod = 1.0 - minc[hh];    // fraction of degradationn that is not mineralised

    // Temperature dependence factor

    for(long kk = 0; kk < maxsoillayers; ++kk)
      if(thickness_lay[kk][hh] > 0.0)
        tmpfcn[kk] = tempfactor(Temp_lay[kk][hh]);

    // Soil moisture dependence factor

    smfcn[0] = moisturefactor(water_lay[0][hh], wp_lay[0][hh], pw_lay[0][hh], thickness_lay[0][hh], soimf[hh], thetapow, soimr[hh], thetaupp);
    smfcn[1] = moisturefactor(water_lay[1][hh], wp_lay[1][hh], pw_lay[1][hh], thickness_lay[1][hh], soimf[hh], thetapow, soimr[hh], thetaupp);
    smfcn[2] = moisturefactor(water_lay[2][hh], wp_lay[2][hh], pw_lay[2][hh], thickness_lay[2][hh], soimf[hh], thetapow, soimr[hh], thetaupp);

    // Transformation between labileC and refractoryC

    for(long kk = 0; kk < maxsoillayers; ++kk)
      fasttorefractory[kk] = 0.0;

    if(thickness_lay[2][hh] > 0.0){
      for(long kk = 0; kk < maxsoillayers; ++kk)
        fasttorefractory[kk] = klh[hh] * tmpfcn[kk] * smfcn[kk] * labileC_lay[kk][hh];
        retention_pool(labileC_lay, fasttorefractory, 3); // fasttorefractory may change in retention_pool :::(3,soilstate%labileC(:,j,i),fasttorefractory(:))
//        production_pool(&refractoryC_lay[2][hh], fracprod*fasttorefractory[2]); // (3,soilstate%refractoryC(:,j,i),fracprod*fasttorefractory(:))
    }
    else if(thickness_lay[1][hh] > 0.0){
      for(long k = 0; k < 2; ++k){
        fasttorefractory[k] = klh[hh] * tmpfcn[k] * smfcn[k] * labileC_lay[k][hh];
        retention_pool(labileC_lay, fasttorefractory, 3); // fasttorefractory may change in retention_pool ::: (2,soilstate%labileC(1:2,j,i),fasttorefractory(1:2))
//        production_pool(&refractoryC_lay[1][hh], fracprod*fasttorefractory[1]); // ::: (2,soilstate%refractoryC(1:2,j,i),fracprod*fasttorefractory(1:2))
      }
    }
    else{
      fasttorefractory[0] = klh[hh] * tmpfcn[0] * smfcn[0] * labileC_lay[0][hh];
      retention_pool(labileC_lay, fasttorefractory, 3); // fasttorefractory may change in retention_pool ::: (1,soilstate%labileC(1,j,i),fasttorefractory(1))
      real1temp[0] = fracprod*fasttorefractory[0];
      production_pool(refractoryC_lay, real1temp, 3); // ::: (1,soilstate%refractoryC(1,j,i),real1temp(1))-OK
    } //

    // Transformation of DOC to labileC

    for(long k = 0; k < maxsoillayers; ++k)
      doctofast[k] = 0.0;

    for(long k = 0; k < maxsoillayers; ++k)
      if(thickness_lay[k][hh] > 0.0 && smfcn[k] < koflim[hh] && water_lay[k][hh] < fc_lay[k][hh] + wp_lay[k][hh] && Temp_lay[k][hh] < 5.0)
        doctofast[k] = kof[hh]*DOCpool[k];

    if(thickness_lay[2][hh]){
       retention_pool(DOCpool, doctofast, 3); // doctofast may change in retention_pool ::: (3,DOCpool(:),doctofast(:)
       production_pool(labileC_lay[2][hh], fracprod*doctofast[2]); // ::: (maxsoillayers,DOCpool(:),fracprod*transfC(:))
    }
    else if(thickness_lay[1][hh] > 0){
       retention_pool(DOCpool, doctofast, 3); // doctofast may change in retention_pool ::: 2,DOCpool(1:2),doctofast(1:2))
       production_pool(labileC_lay[1][hh], fracprod*doctofast[1]);
    }
    else{
       retention_pool(DOCpool, doctofast, 3); // doctofast may change in retention_pool
       real1temp[0] = fracprod*doctofast[0];
       production_pool(labileC_lay[0][hh], real1temp[0]);
    } //

    // Transformation of labileC to DOC

    for(long k = 0; k < maxsoillayers; ++k)
      transfC[k] = 0.0;
    if(thickness_lay[2][hh] > 0.0){
      transfC[2] = klo[hh] * tmpfcn[2] * smfcn[2] * labileC_lay[2][hh];
       retention_pool(labileC_lay, transfC, 3); // transfC may change in retention_pool
       production_pool(DOCpool[2], fracprod*transfC[2]);
    }
    else if(thickness_lay[1][hh] > 0.0){
      transfC[1] = klo[hh] * tmpfcn[1] * smfcn[1] * labileC_lay[1][hh]; // ::: transfC(1:2) = klo * tmpfcn(1:2) * smfcn(1:2) * soilstate%labileC(1:2,j,i)
       retention_pool(labileC_lay, transfC, 3); // transfC may change in retention_pool
       production_pool(DOCpool[1], fracprod*transfC[1]);
      }
    else{
      transfC[0] = klo[hh] * tmpfcn[0] * smfcn[0] * labileC[0];
      retention_pool(labileC_lay, transfC, 3); // transfC may change in retention_pool
      real1temp[0]=fracprod*transfC[0];
      production_pool(DOCpool[0], real1temp[0]);
    } // 

    // Transformation of refractoryC to DOC
    for(long k = 0; k < maxsoillayers; ++k)
      transhC[k] = 0.0;
    if(thickness_lay[2][hh] > 0.0){
      transhC[2] = kho[hh] * tmpfcn[2] * smfcn[2] * refractoryC_lay[2][hh];
       retention_pool(refractoryC_lay, transhC, 3); // transhC may change in retention_pool
       production_pool(DOCpool[2], fracprod*transhC[2]);
    }
    else if(thickness_lay[1][hh] > 0.0){
      transhC[1] = kho[hh] * tmpfcn[1] * smfcn[1] * refractoryC[1];
      retention_pool(refractoryC_lay, transhC, 3); // transhC may change in retention_pool
      production_pool(DOCpool[1], fracprod*transhC[1]);
    }
    else{
      transhC[0] = kho[hh] * tmpfcn[0] * smfcn[0] * refractoryC_lay[0][hh];
       retention_pool(refractoryC_lay, transhC, 3);     // transhC may change in retention_pool
      real1temp[0] = fracprod*transhC[0];
       production_pool(DOCpool[0], real1temp[0]);
    } //

    // Calculate the new soil concentrations of DOC
     new_concentration(DOCpool[0], water_lay[0][hh], &conc_top_lay[i_oc][hh]);
    if(thickness_lay[1][hh] > 0.0)
      new_concentration(DOCpool[1], water_lay[1][hh], &conc_bottom_lay[i_oc][hh]);
    if(thickness_lay[2][hh] > 0.0)
      new_concentration(DOCpool[2], water_lay[2][hh], &conc_below_lay[i_oc][hh]);

  } // END SUBROUTINE soil_carbon_pool_transformations

// Subroutine add an amount of substance to a water body and recalculate the concentration
// ----------------------------------------------------------------
  void ClassWQ_Hype::add_source_to_water(const float vol, const long n, float *conc, const float source){

// Argument declarations
// float, INTENT(IN)    :: vol        !<water body (mm)
// long, INTENT(IN)     :: n          !<numsubstance = size of conc-array
// float, INTENT(INOUT) :: conc(n)    !<conc of water body (mg/l)
// float, INTENT(IN)    :: source(n)  !<amount to be added (kg/km2)

    if(vol > 0.0)
       *conc = (*conc*vol + source)/ vol;

  }  // add_source_to_water

// Subroutine add an amount of substance to a water body and recalculate the concentration
// ----------------------------------------------------------------
  void ClassWQ_Hype::add_source_to_water(const float vol, long n, float conc, float source){

// Argument declarations
// float, INTENT(IN)    :: vol        !<water body (mm)
// long, INTENT(IN) :: n              !<numsubstance = size of conc-array
// float, INTENT(INOUT) :: conc(n)    !<conc of water body (mg/l)
// float, INTENT(IN)    :: source(n)  !<amount to be added (kg/km2)

    if(vol > 0.0)
       conc = (conc*vol + source)/ vol;

  }  // add_source_to_water

// ---------------------------------------------------------------
// Calculates a temperature factor Based on: Q10=2,reference rate is at 20 degrees and with thresholds at 0 and 5 degrees (from COUP-model).
// param[in] temperature Current temperature
// --------------------------------------------------------------
    float ClassWQ_Hype::tempfactor2(const float temperature){

// float, INTENT(IN)  :: temperature     current temperature

// Local variables
      float fcn;
      return 0.0; // fix !!!!!!!!

      fcn = pow(2.0, (temperature - 20.0) / 10.0);

      if(temperature < 5.0)
        fcn = fcn * (temperature / 5.0);

      if(temperature < 0.0)
        fcn = 0.0;

      return fcn;

  } // tempfactor2

// -----------------------------------------------------------------------------
// Calculates an exponential soil moisture dependence factor
  //
  //  @param[in] sm     Soil moisture (mm)
  //  @param[in] pw     Total pore wolume (mm)
  //  @param[in] limpar Limitation parameter of moisturefactor (mm) (smfdenitlim)
  //  @param[in] exp    Exponent of moisturefactor (smfdenitpow)
// -----------------------------------------------------------------------------

    float ClassWQ_Hype::exponential_moisturefactor(const float sm, const float pw, const float limpar, const float exp){

//    float, INTENT(IN)  :: sm     !soil moisture (mm)
//    float, INTENT(IN)  :: pw     !total pore wolume (mm)
//    float, INTENT(IN)  :: limpar !limitation parameter of moisturefactor (mm) (smfdenitlim)
//    float, INTENT(IN)  :: exp    !exponent of moisturefactor (smfdenitpow)

// Local variables
    float smfcn;      // soil moisture dependence factor

// Initiations
    smfcn = 0.0;

// Calculate soilmoisture function value
    if((sm/pw) > limpar){
       smfcn = pow((((sm / pw)-limpar)/(1.0-limpar)), exp);
    }

    return smfcn;

  } // exponential_moisturefactor

// ----------------------------------------------------------------
// Calculates a concentration dependence factor
//  Based on: half saturation function
//
//  @param[in] conc Current concentration
//  @param[in] par  Half saturation concentration
// ----------------------------------------------------------------
  float ClassWQ_Hype::halfsatconcfactor(const float conc, const float par){

//  Local variables
    float fcn;

    fcn = conc / (conc + par);
    return  fcn;

  } // halfsatconcfactor

void ClassWQ_Hype::retention_pool(float **pool, float *sink, long maxlayers){

// Argument declarations

// INTEGER, INTENT(IN) :: n       !<number of soillayers = size of pool-array
// REAL, INTENT(INOUT) :: pool(n) !<soil pool array
// REAL, INTENT(INOUT) :: sink(n) !<amount to be removed

  float a;
  for(long k = 0; k < maxlayers; ++k){ // layers
    a = pool[k][hh] - sink[k];
    if(a >= 0.0)
      pool[k][hh] = a;
    else{
      sink[k] = pool[k][hh];
      pool[k][hh] = 0.0;
    }
  }
} // retention_pool

void ClassWQ_Hype::retention_pool(float **pool, long hh, float *sink, long maxlayers){

// Argument declarations

// INTEGER, INTENT(IN) :: n       !<number of soillayers = size of pool-array
// REAL, INTENT(INOUT) :: pool(n) !<soil pool array
// REAL, INTENT(INOUT) :: sink(n) !<amount to be removed

  float a;

  for(long k = 0; k < maxlayers; ++k){  // layers
    a = pool[k][hh] - sink[k];
    if(a >= 0.0)
      pool[k][hh] = a;
    else{
      sink[k] = pool[k][hh];
      pool[k][hh] = 0.0;
    }
  }
} // retention_pool

void ClassWQ_Hype::retention_pool(float *pool, float *sink, long maxlayers){

// Argument declarations

// INTEGER, INTENT(IN) :: n       !<number of soillayers = size of pool-array
// REAL, INTENT(INOUT) :: pool(n) !<soil pool array
// REAL, INTENT(INOUT) :: sink(n) !<amount to be removed

  float a;

  for(long k = 0; k < maxlayers; ++k){  // layers
    a = pool[k] - sink[k];
    if(a >= 0.0)
      pool[k] = a;
    else{
      sink[k] = pool[k];
      pool[k] = 0.0;
    }
  }
} // retention_pool

  void ClassWQ_Hype::production_pool(float **pool, const float *source, long maxlayers){

// Argument declarations

//    long, INTENT(IN) :: n             // <number of soillayers = size of pool-array
//    float, INTENT(INOUT) :: pool(n)   // <soil pool array (kg/km2) or (mg/m2)
//    float, INTENT(IN)    :: source(n) // <amount to be added (kg/km2) or (mg/m2)

    for(long kk = 0; kk < maxlayers; ++kk) // layers
      pool[kk][hh] = pool[kk][hh] + source[kk];

  }  // production_pool

  void ClassWQ_Hype::production_pool(float **pool, const float source[][2], long Application){

// Argument declarations

//    long, INTENT(IN) :: n             // <number of soillayers = size of pool-array
//    float, INTENT(INOUT) :: pool(n)   // <soil pool array (kg/km2) or (mg/m2)
//    float, INTENT(IN)    :: source(n) // <amount to be added (kg/km2) or (mg/m2)

    for(long kk = 0; kk < maxsoillayers; ++kk)
      pool[kk][hh] = pool[kk][hh] + source[kk][Application];

  }  // production_pool

  void ClassWQ_Hype::production_pool(float *pool, const float *source, long maxlayers){

// Argument declarations

//    long, INTENT(IN) :: n             // <number of soillayers = size of pool-array
//    float, INTENT(INOUT) :: pool(n)   // <soil pool array (kg/km2) or (mg/m2)
//    float, INTENT(IN)    :: source(n) // <amount to be added (kg/km2) or (mg/m2)

    for(long kk = 0; kk < maxlayers; ++kk)  // layers
      pool[kk] = pool[kk] + source[kk];

  }  // production_pool

  void ClassWQ_Hype::production_pool(float **pool, long hh, const float *source, long maxlayers){

// Argument declarations

//    long, INTENT(IN) :: n             // <number of soillayers = size of pool-array
//    float, INTENT(INOUT) :: pool(n)   // <soil pool array (kg/km2) or (mg/m2)
//    float, INTENT(IN)    :: source(n) // <amount to be added (kg/km2) or (mg/m2)

    for(long kk = 0; kk < maxlayers; ++kk)  // layers
      pool[kk][hh] = pool[kk][hh] + source[kk];

  }  // production_pool

  void ClassWQ_Hype::production_pool(float *pool, float source){

// Argument declarations
//    long n;         // number of soillayers = size of pool-array
//    float pool(n)   // soil pool array     (kg/km2) or (mg/m2)
//    float source(n) // amount to be added  (kg/km2) or (mg/m2)

    *pool = *pool + source;

  } // END SUBROUTINE production_pool

  void ClassWQ_Hype::production_pool(float pool, float source){ // return by reference

    pool = pool + source;

  } // END SUBROUTINE production_pool

// Calculates concentration based on water volume and amount of one substance
// ---------------------------------------------------------------------
      void ClassWQ_Hype::new_concentration(const float pool, const float vol, float *conc){ // return by reference

// Argument declarations
//    float, INTENT(IN)    :: pool !<amount          (kg/km2) or (mg/m2)
//    float, INTENT(IN)    :: vol  !<volume          (mm)
//    float, INTENT(INOUT) :: conc !<concentation    (mg/L)

    if(vol > 0.0)
      *conc = pool / vol;
    else
      *conc = 0.0;

  }  // new_concentration

// Calculates concentration based on water volume and amount of one substance
// ---------------------------------------------------------------------
/*  void ClassWQ_Hype::new_concentration(const float pool, const float vol, float **conc){

// Argument declarations
//    float, INTENT(IN)    :: pool !<amount          (kg/km2) or (mg/m2)
//    float, INTENT(IN)    :: vol  !<volume          (mm)
//    float, INTENT(INOUT) :: conc !<concentation    (mg/L)

    if(vol > 0.0)
      conc[i_in][hh] = pool / vol;
    else
      conc[i_in][hh] = 0.0;

  }  // new_concentration  */


  float ClassWQ_Hype::SUM(float X[maxsoillayers][2], long Substance){

    float sum = 0.0;
    for(long ii = 0; ii < maxsoillayers; ++ii)
      sum += X[ii][Substance];

    return sum;
  }

  float ClassWQ_Hype::SUM(float *X){
    float sum = 0.0;
    for(long ii = 0; ii < maxsoillayers; ++ii)
      sum += X[ii];

    return sum;
  }



