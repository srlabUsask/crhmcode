// 11/20/19
//---------------------------------------------------------------------------
#pragma hdrstop

#include "WQ_Soil_NPCcycling.h"
#include "NewModules.h"
#include "GlobalDll.h"

#include <cmath>
#include <stdlib.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------

using namespace std;
using namespace CRHM;

const float thetalow = 0.08;                     // Low(?) moisture coefficient (thetalow)
const float thetaupp = 0.12;                     // high(?) moisture coefficient (thetaupp)
const float satact = 0.6;
const float thetapow = 2; // changed from original HYPE: just gives a slight curvature in the calculation of smfcn that is more realistic (not a major change)
const float bulkdensity = 1300;
const float sreroexp = 1.0; // genpar(float m_sreroexp); surface runoff erosion exponent
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
const float smfdenitlim = 0.1; // limitation parameter of moisturefactor (mm) (smfdenitlim)
const float smfdenitpow = 1.0; // exponent of moisturefactor (smfdenitpow)
const float halfsatINsoil = 1.0;
const float ldprodpp = 1.0;
const float ldprodsp = 1.0;

const long i_no3n = 0; // NO3-N
const long i_nh4n = 1; // NH4-N
const long i_don = 2; // dissolved organic nitrogen
const long i_srp = 3; // soluble (reactive) phosphorus
const long i_dop = 4; // dissolved organic phosphorus
const long i_pp = 5; // particulate phosphorus
const long i_oc = 6; // (dissolved) organic carbon
const long maxsoilayers = 3; //

const float minFlow_WQ = 0.001f;

ClassWQ_SoilBGC* ClassWQ_SoilBGC::klone(string name) const{
  return new ClassWQ_SoilBGC(name);
}

void ClassWQ_SoilBGC::decl(void) {

  Description = "'Soil biogeochemical cycling module.'";

  declstatvar("partP", NDEFN, "immobile/undissolved pool of organic phosphorus adsorded to soil particles.", "(kg/km^2)", &partP, &partP_lay, maxsoillayers);

  declstatvar("refractoryN", NDEFN, "immobile/undissolved pool of organic nitrogen in soil with slow turnover.", "(kg/km^2)", &refractoryN, &refractoryN_lay, maxsoillayers);

  declstatvar("refractoryP", NDEFN, "immobile/undissolved pool of organic phosphorus in soil with slow turnover.", "(kg/km^2)", &refractoryP, &refractoryP_lay, maxsoillayers);

  declstatvar("refractoryC", NDEFN, "immobile/undissolved pool of organic carbon with slow turnover.", "(kg/km^2)", &refractoryC, &refractoryC_lay, maxsoillayers);

  declstatvar("labileN", NDEFN, "immobile/undissolved pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &labileN, &labileN_lay, maxsoillayers);

  declstatvar("labileP", NDEFN, "immobile/undissolved pool of organic phosphorus in soil with rapid turnover.", "(kg/km^2)", &labileP, &labileP_lay, maxsoillayers);

  declstatvar("labileC", NDEFN, "immobile/undissolved pool of organic carbon in soil with rapid turnover.", "(kg/km^2)", &labileC, &labileC_lay, maxsoillayers);

  declstatvar("NO3_Npool", NDEFN, "NO3-N (nitrate-nitrogen, dissolved) pool in soil", "(kg/km^2)", &NO3_Npool, &NO3_Npool_lay, maxsoillayers);

  declstatvar("NH4_Npool", NDEFN, "NH4-N (ammonium-nitrogen, dissolved) pool in soil", "(kg/km^2)", &NH4_Npool, &NH4_Npool_lay, maxsoillayers);

  declstatvar("DONpool", NDEFN, "dissolved organic nitrogen pool in soil", "(kg/km^2)", &DONpool, &DONpool_lay, maxsoillayers);

  declstatvar("SRPpool", NDEFN, "soluble-reactive phosphorus pool in soil", "(kg/km^2)", &SRPpool, &SRPpool_lay, maxsoillayers);

  declstatvar("DOPpool", NDEFN, "dissolved organic phosphorus pool in soil", "(kg/km^2)", &DOPpool, &DOPpool_lay, maxsoillayers);

  declstatvar("PPrelpool", NHRU, "soil PP (particulate phosphorus) released to runoff due to erosion", "(kg/int)", &PPrelpool);
  
  declstatvar("plant_uptk_NO3N_mWQ", NDEFN, "plant uptake of NO3-N expressed as mass/int", "(kg/int)", &plant_uptk_NO3N_mWQ, &plant_uptk_NO3N_mWQ_lay, maxsoillayers);

  declstatvar("plant_uptk_NH4N_mWQ", NDEFN, "plant uptake of NH4-N expressed as mass/int", "(kg/int)", &plant_uptk_NH4N_mWQ, &plant_uptk_NH4N_mWQ_lay, maxsoillayers);

  declstatvar("plant_uptk_SRP_mWQ", NDEFN, "plant uptake of SRP expressed as mass/int", "(kg/int)", &plant_uptk_SRP_mWQ, &plant_uptk_SRP_mWQ_lay, maxsoillayers);

  declvar("water", NDEFN, "soil moisture", "(mm)", &water, &water_lay, maxsoillayers);
  
  declvar("watermax", NDEFN, "soil moisture", "(mm)", &watermax, &watermax_lay, maxsoillayers);

  declvar("Temp", NDEFN, "soil layer temperature", "(°C)", &Temp, &Temp_lay, maxsoillayers);

  declvar("denitrification", NDEFN, "denitrification (maxsoillayers", "(kg/int)", &denitrification, &denitrification_lay, maxsoillayers);

  declstatvar("denitrification_surfsoil", NHRU, "denitrification in WQ's surfsoil", "(kg/int)", &denitrification_surfsoil);

  declstatvar("conc_soil_rechr", NDEFN, "concentration in soil_rechr: (i_no3n=0) NO3-N, (i_nh4n=1) NH4-1, (i_don=2) DON, "
      "(i_srp=3) SRP, (i_dop=4) DOP, (i_pp=5) PP, (i_oc=6) OC", "(mg/l)", &conc_soil_rechr, &conc_soil_rechr_lay, numsubstances); //

  declstatvar("conc_soil_lower", NDEFN, "concentration in soil_lower: (i_no3n=0) NO3-N, (i_nh4n=1) NH4-1, (i_don=2) DON, "
      "(i_srp=3) SRP, (i_dop=4) DOP, (i_pp=5) PP, (i_oc=6) OC", "(mg/l)", &conc_soil_lower, &conc_soil_lower_lay, numsubstances);

  //declstatvar("conc_soil_moist", NDEFN, "concentration of soluble (reactive) phosphorus, i.e. phosphate in soil moisture per land-soil", "(mg/l)", &conc_soil_moist, &conc_soil_moist_lay, numsubstances);

  declvar("source", NDEFN, "source of soil water nutrients through mineralization", "(kg/int)", &source, &source_lay, numsubstances);

  declvar("sink", NDEFN, "sink of nutrients in subroutine)", "(kg/km^2)", &sink, &sink_lay, numsubstances);

  declvar("sources_plant", NDEFN, "nutrient load from plant residues. Indexed as LAY -> substance", "(kg/int)", &sources_plant, &sources_plant_lay, numsubstances);

  declvar("src_mineral_fertman_surfsoil", NDEFN, "load from fertilizer to surfsoil. Indexed as LAY -> substance", "(kg/int)", &src_mineral_fertman_surfsoil, &src_mineral_fertman_surfsoil_lay, numsubstances);

  declvar("src_mineral_fertman_soilrechr", NDEFN, "load from fertilizer) to soil_rechr. Indexed as LAY -> substance", "(kg/int)", &src_mineral_fertman_soilrechr, &src_mineral_fertman_soilrechr_lay, numsubstances);

  declvar("fracminP", NHRU, "part of eroded P in mineral form", "()", &fracminP);

  declvar("cropuptake", NHRU, "crop uptake of nitrogen", "(kg/int)", &cropuptake);

  declvar("surfsoil_solub_mWQ", NDEFN, "Mass in the surficial soil layer ready for mobilization: dissolved substances", "(kg/km2)", &surfsoil_solub_mWQ, &surfsoil_solub_mWQ_lay, numsubstances); //
  declvar("surfsoil_labileN_mWQ", NHRU, "Mass in the surficial soil layer ready for mobilization: Labile N", "(kg/km2)", &surfsoil_labileN_mWQ);
  declvar("surfsoil_labileP_mWQ", NHRU, "Mass in the surficial soil layer ready for mobilization: Labile P", "(kg/km2)", &surfsoil_labileP_mWQ);
  declvar("surfsoil_refractoryN_mWQ", NHRU, "Mass in the surficial soil layer ready for mobilization: Refractory N", "(kg/km2)", &surfsoil_refractoryN_mWQ);
  declvar("surfsoil_refractoryP_mWQ", NHRU, "Mass in the surficial soil layer ready for mobilization: Refractory N", "(kg/km2)", &surfsoil_refractoryP_mWQ);

  //declparam("ep", NDEFN, "[1.9]", "0.0", "2.0", "normalized effective porosity w.r.t. soil_rechr_max or soil_lower_max", "()", &ep, &ep_lay, maxsoillayers);

  declparam("wp", NDEFN, "[0]", "0.05", "0.2", "normalized wilting point w.r.t. soil_rechr_max or soil_lower_max", "()", &wp, &wp_lay, maxsoillayers);

  //declparam("pw", NDEFN, "[2]", "0.5", "2.0", "normalized total porosity w.r.t. soil_rechr_max or soil_lower_max", "()", &pw, &pw_lay, maxsoillayers);
 
  
  //declvar("fc_mm", NDEFN, "field capacity w.r.t. soil_rechr_max or soil_lower_max", "(mm)", &fc_mm, &fc_mm_lay, maxsoillayers);

  //declvar("ep_mm", NDEFN, "effective porosity w.r.t. soil_rechr_max or soil_lower_max", "(mm)", &ep_mm, &ep_mm_lay, maxsoillayers);

  declvar("wp_mm", NDEFN, "wilting point w.r.t. soil_rechr_max or soil_lower_max", "(mm)", &wp_mm, &wp_mm_lay, maxsoillayers);

  //declvar("pw_mm", NDEFN, "total porosity w.r.t. soil_rechr_max or soil_lower_max", "(mm)", &pw_mm, &pw_mm_lay, maxsoillayers);


  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(°)", &hru_GSL);

  declparam("ccmax1", NHRU, "[0]", "0","10", "crop cover during summer", "()", &ccmax1);

  // declparam("ccmax2", NHRU, "[0]", "0","10", "crop cover during winter and all year for year round", "()", &ccmax2);

  declparam("gcmax1", NHRU, "[0]", "0","10", "ground cover during summer", "()", &gcmax1);

  // declparam("gcmax2", NHRU, "[0]", "0","10", "ground cover during winter and all year for year round", "()", &gcmax2);

  /*
  declparam("baredayno1", NHRU, "[0]", "1","366", "spring ploughing", "()", &baredayno1);

  declparam("baredayno2", NHRU, "[0]", "1","366", "sow date/beginning of growing season", "()", &baredayno2);

  declparam("baredayno3", NHRU, "[0]", "1","366", "harvest", "()", &baredayno3);

  declparam("baredayno4", NHRU, "[0]", "1","366", "autumn ploughing", "()", &baredayno4);

  declparam("baredayno5", NHRU, "[0]", "1","366", "winter crops sowing date", "()", &baredayno5);
  */

  declparam("erodibility", NHRU, "[0]", "0","100", "erodibility", "(g/J)", &erodibility);

  declparam("cohesion", NHRU, "[0]", "0","100", "cohesion", "(kPa)", &cohesion);

  declparam("pardenN", NHRU, "[1]", "0", "100", "denitrification in soil", "(mm)", &pardenN);

  declparam("calcN", NHRU, "[0]", "0", "1", "flag for nitrogen simulation", "()", &calcN);

  declparam("calcP", NHRU, "[0]", "0", "1", "flag for phosphorus simulation", "()", &calcP);

  declparam("calcC", NHRU, "[0]", "0", "1", "flag for carbon simulation", "()", &calcC);

  declparam("Inhibit_Soil_BGC", BASIN, "[0]", "0", "1", "Bypass Hype routines", "()", &Inhibit_Soil_BGC);

  declparam("parminfN", NHRU, "[0]", "0", "1", "mineralisation of labileN: labileN to NH4", "(1/d)", &parminfN);

  declparam("parnitrfN", NHRU, "[0]", "0", "1", "nitrification: NH4 to NO3", "(1/d)", &parnitrfN);

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
  
  declparam("fertNamount_up", NHRU, "[1]", "0", "1000000", "fertiliser amount1 N", "(kg/km^2)", &fertNamount_up);

  declparam("fertNamount_down", NHRU, "[1]", "0", "1000000", "fertiliser amount2 N", "(kg/km^2)", &fertNamount_down);

  declparam("fertPamount_up", NHRU, "[1]", "0", "1000000", "fertiliser amount1 P", "(kg/km^2)", &fertPamount_up);

  declparam("fertPamount_down", NHRU, "[1]", "0", "1000000", "fertiliser amount2 P", "(kg/km^2)", &fertPamount_down);

  declparam("fertday_up", NHRU, "[0]", "0", "366", "day for fertilizing 1 (dayno)", "()", &fertday_up);

  declparam("fertday_down", NHRU, "[0]", "0", "366", "day for fertilizing 2 (dayno)", "()", &fertday_down);

  declparam("resday_up", NHRU, "[0]", "0", "366", "day for residual (dayno), code 0 give residuals every day)", "()", &resday_up);

  declparam("resday_down", NHRU, "[0]", "0", "366", "day for residual (dayno), code 0 give residuals every day)", "()", &resday_down);

  declparam("manday_up", NHRU, "[0]", "0", "366", "day for manureing 1)", "()", &manday_up);

  declparam("manday_down", NHRU, "[0]", "0", "366", "day for manureing 2)", "()", &manday_down);

  //declparam("fertdown1", NHRU, "[0.0]", "0", "1", " fertilizer amount1 ploughed down", "()", &fertdown1);

  //declparam("fertdown2", NHRU, "[0.0]", "0", "1", " fertilizer amount2 ploughed down", "()", &fertdown2);

  //declparam("mandown1", NHRU, "[0.0]", "0", "1", " manure amount1 ploughed down", "()", &mandown1);

  //declparam("mandown2", NHRU, "[0.0]", "0", "1", " manure amount2 ploughed down", "()", &mandown2);

  declparam("manNamount_up", NHRU, "[0.0]", "0", "1000000", "manure amount1 N", "(kg/km^2)", &manNamount_up);

  declparam("manNamount_down", NHRU, "[0.0]", "0", "1000000", "manure amount2 N", "(kg/km^2)", &manNamount_down);

  declparam("manPamount_up", NHRU, "[0.0]", "0", "1000000", "manure amount1 P", "(kg/km^2)", &manPamount_up);

  declparam("manPamount_down", NHRU, "[0.0]", "0", "1000000", "manure amount2 P", "(kg/km^2)", &manPamount_down);

  declparam("resNamount_up", NHRU, "[0.0]", "0", "1000000", "residual amount of N", "(kg/km^2)", &resNamount_up);

  declparam("resPamount_up", NHRU, "[0.0]", "0", "1000000", "residual amount of P", "(kg/km^2)", &resPamount_up);

  declparam("resNamount_down", NHRU, "[0.0]", "0", "1000000", "residual amount of N", "(kg/km^2)", &resNamount_down);

  declparam("resPamount_down", NHRU, "[0.0]", "0", "1000000", "residual amount of P", "(kg/km^2)", &resPamount_down);

  declparam("resCamount", NHRU, "[0.0]", "0", "1", "litter fall of C", "(kg/km^2)", &resCamount);

  declparam("resfast", NHRU, "[0.0]", "0", "1", " residual amount to labileN/P pool (rest to refractoryN/P)", "(-)", &resfast);

  //declparam("resdown", NHRU, "[0.0]", "0", "1", " residual amount to labileN/P pool (rest to refractoryN/P)", "(-)", &resdown);

  declparam("fertperiod", NHRU, "[1]", "1", "100", "days for fertilization.", "()", &fertperiod);

  declparam("litterperiod", NHRU, "[1]", "1", "100", "days for litterfall.", "()", &litterperiod);

  declparam("manureinogNfrac", NHRU, "[0.5]", "0", "1", "fraction of inorN in manure.", "(-)", &manureinogNfrac);

  declparam("manureinogPfrac", NHRU, "[0.5]", "0", "1", "fraction of inorN in manure.", "(-)", &manureinogPfrac);

   declparam("fertandman_inogNfrac_NO3Nfrac", NHRU, "[0.5]", "0", "1", "fraction of NO3-N in fraction of inorgN in fertilizer and manure.", "(-)", &fertandman_inogNfrac_NO3Nfrac);

  declparam("fertandman_inogNfrac_NH4frac", NHRU, "[0.5]", "0", "1", "fraction of NH4-N in fraction of inorgN in fertilizer and manure.", "(-)", &fertandman_inogNfrac_NH4Nfrac);

  declparam("refractoryNmass_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with slow turnover.", "(kg/km^2)", &refractoryNmass_init, &refractoryNmass_init_lay, maxsoillayers);

  declparam("refractoryPmass_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic phosphorus in soil with slow turnover.", "(kg/km^2)", &refractoryPmass_init, &refractoryPmass_init_lay, maxsoillayers);

  declparam("refractoryCmass_init", NDEFN, "[0.0]", "0", "1000000", "refractoryC pool in soil", "(kg/km^2)", &refractoryCmass_init, &refractoryCmass_init_lay, maxsoillayers);

  declparam("labileNmass_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &labileNmass_init, &labileNmass_init_lay, maxsoillayers);

  declparam("labilePmass_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic phosphorus in soil with rapid turnover.", "(kg/km^2)", &labilePmass_init, &labilePmass_init_lay, maxsoillayers);

  declparam("labileCmass_init", NDEFN, "[0.0]", "0", "1000000", "labileC pool in soil", "(kg/km^2)", &labileCmass_init, &labileCmass_init_lay, maxsoillayers);

  declparam("plant_uptk_NO3N", NDEFN, "[0]", "0", "10", "plant NO3-N uptake per day.", "(kg/km^2)", &plant_uptk_NO3N, &plant_uptk_NO3N_lay, maxsoillayers);

  declparam("plant_uptk_NH4N", NDEFN, "[0]", "0", "10", "plant NH4-N uptake per day.", "(kg/km^2)", &plant_uptk_NH4N, &plant_uptk_NH4N_lay, maxsoillayers);

  declparam("plant_uptk_SRP", NDEFN, "[0]", "0", "10", "plant P uptake per day.", "(kg/km^2)", &plant_uptk_SRP, &plant_uptk_SRP_lay, maxsoillayers);

  declparam("conc_soil_rechr_init", NDEFN, "[0.0]", "0", "1000", "initial concentration of inorganic nitrogen in soil moisture per land-soil", "(mg/l)", &conc_soil_rechr_init, &conc_soil_rechr_init_lay, numsubstances);

  declparam("conc_soil_lower_init", NDEFN, "[0.0]", "0", "1000", "concentration of organic nitrogen in soil moisture per land-soil", "(mg/l)", &conc_soil_lower_init, &conc_soil_lower_init_lay, numsubstances);

  declparam("surfsoil_massSolub_init", NDEFN, "[0.0]", "0", "1000", "initial concentration of inorganic nitrogen in surfsoil layer", "(mg/l)", &surfsoil_massSolub_init, &surfsoil_massSolub_init_lay, numsubstances);
  
  declparam("surfsoil_masslabileNmass_init", NHRU, "[0.0]", "0", "1000000", "initial mass of labile N in the surfsoil layer", "(kg/km^2)", &surfsoil_masslabileNmass_init);

  declparam("surfsoil_masslabilePmass_init", NHRU, "[0.0]", "0", "1000000", "initial mass of labile P in the surfsoil layer", "(kg/km^2)", &surfsoil_masslabilePmass_init);
  
  declparam("surfsoil_massrefractoryNmass_init", NHRU, "[0.0]", "0", "1000000", "initial mass of labile N in the surfsoil layer", "(kg/km^2)", &surfsoil_massrefractoryNmass_init);

  declparam("surfsoil_massrefractoryPmass_init", NHRU, "[0.0]", "0", "1000000", "initial mass of labile N in the surfsoil layer", "(kg/km^2)", &surfsoil_massrefractoryPmass_init);

  declparam("labileNmass_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &labileNmass_init, &labileNmass_init_lay, maxsoillayers);

  declparam("labileNmass_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &labileNmass_init, &labileNmass_init_lay, maxsoillayers);

  declparam("labileNmass_init", NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", &labileNmass_init, &labileNmass_init_lay, maxsoillayers);

  declgetvar("*", "hru_t", "(°C)", &hru_t);

  declgetvar("*", "snowmelt_int", "(mm/int)", &snowmelt_int);

  declgetvar("*", "SWE", "(mm)", &SWE);

  declgetvar("*", "net_rain", "(mm)", &net_rain);

  declgetvar("*", "runoff", "(mm)", &runoff);

  declgetvar("*", "soil_runoff", "(mm)", &soil_runoff);

  declputvar("*", "soil_runoff_cWQ", "(mm)", &soil_runoff_cWQ,&soil_runoff_cWQ_lay);

  declputvar("*", "SWE_conc", "(mg/l)", &SWE_conc, &SWE_conc_lay);

  declparam("soil_Depth", NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", &soil_Depth);
  
  declgetvar("*", "soil_moist", "(mm)", &soil_moist);

  declgetvar("*", "soil_rechr", "(mm)", &soil_rechr);

  declgetparam("*", "soil_moist_max", "(mm)", &soil_moist_max);

  declgetparam("*", "soil_rechr_max", "(mm)", &soil_rechr_max);
  
  
}

void ClassWQ_SoilBGC::init(void) {

  nhru = getdim(NHRU);
  nlay = getdim(NLAY);

  for(hh = 0; hh < nhru; ++hh) {
    fracminP[hh] = 0.0;
    cropuptake[hh] = 0.0;
    surfsoil_labileN_mWQ[hh] = surfsoil_masslabileNmass_init[hh] * hru_area[hh];
    surfsoil_labileP_mWQ[hh] = surfsoil_masslabilePmass_init[hh] * hru_area[hh];;
    surfsoil_refractoryN_mWQ[hh] = surfsoil_massrefractoryNmass_init[hh] * hru_area[hh];;
    surfsoil_refractoryP_mWQ[hh] = surfsoil_massrefractoryPmass_init[hh] * hru_area[hh];;
    denitrification_surfsoil[hh] = 0.0;

    for(long ll = 0; ll < maxsoillayers; ++ll) {
      refractoryN_lay[ll][hh] = refractoryNmass_init_lay[ll][hh] * hru_area[hh];
      refractoryP_lay[ll][hh] = refractoryPmass_init_lay[ll][hh] * hru_area[hh];
      refractoryC_lay[ll][hh] = refractoryCmass_init_lay[ll][hh] * hru_area[hh];
      labileN_lay[ll][hh] = labileNmass_init_lay[ll][hh] * hru_area[hh];
      labileP_lay[ll][hh] = labilePmass_init_lay[ll][hh] * hru_area[hh];
      labileC_lay[ll][hh] = labileCmass_init_lay[ll][hh] * hru_area[hh];
      water_lay[ll][hh] = 0.0;
      watermax_lay[ll][hh] = 0.0;
      NO3_Npool_lay[ll][hh] = 0.0;
      NH4_Npool_lay[ll][hh] = 0.0;
      DONpool_lay[ll][hh] = 0.0;
      SRPpool_lay[ll][hh] = 0.0;
      DOPpool_lay[ll][hh] = 0.0;
      partP_lay[ll][hh] = 0.0f;
      plant_uptk_NO3N_mWQ_lay[ll][hh] = 0.0;
      plant_uptk_NH4N_mWQ_lay[ll][hh] = 0.0;
      plant_uptk_SRP_mWQ_lay[ll][hh] = 0.0;
      denitrification_lay[ll][hh] = 0.0;

      float max;
      if(ll == 0)
        max = soil_rechr_max[hh];
      else
        max = soil_moist_max[hh] - soil_rechr_max[hh];

      wp_mm_lay[ll][hh] = max*wp_lay[ll][hh];
      //fc_mm_lay[ll][hh] = max;
      //ep_mm_lay[ll][hh] = max*ep_lay[ll][hh];
      //pw_mm_lay[ll][hh] = max*pw_lay[ll][hh]; // only used in soil_carbon_pool_transformations
    }

    for(long Sub = 0; Sub < numsubstances; ++Sub) {
      surfsoil_solub_mWQ_lay[Sub][hh] = surfsoil_massSolub_init_lay[Sub][hh];
      conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_init_lay[Sub][hh];
      conc_soil_lower_lay[Sub][hh] = conc_soil_lower_init_lay[Sub][hh];
      //conc_soil_moist_lay[Sub][hh] = 0.0;
      source_lay[Sub][hh] = 0.0;
      sink_lay[Sub][hh] = 0.0;
      src_mineral_fertman_surfsoil_lay[Sub][hh] = 0.0f;
      src_mineral_fertman_soilrechr_lay[Sub][hh] = 0.0f; 
      sources_plant_lay[Sub][hh] = 0.0;
    }
  }
}

void ClassWQ_SoilBGC::run(void) {

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

      const_cast<float *>  (fertNamount_up)[hh] /= Global::Freq;
      const_cast<float *>  (fertNamount_down)[hh] /= Global::Freq;
      const_cast<float *>  (fertPamount_up)[hh] /= Global::Freq;
      const_cast<float *>  (fertPamount_down)[hh] /= Global::Freq;
      const_cast<float *>  (manNamount_up)[hh] /= Global::Freq;
      const_cast<float *>  (manNamount_down)[hh] /= Global::Freq;
      const_cast<float *>  (manPamount_up)[hh] /= Global::Freq;
      const_cast<float *>  (manPamount_down)[hh] /= Global::Freq;
      const_cast<float *>  (resNamount_up)[hh] /= Global::Freq;
      const_cast<float *>  (resPamount_up)[hh] /= Global::Freq;
      const_cast<float *>  (resCamount)[hh] /= Global::Freq;
      const_cast<float *>  (resfast)[hh] /= Global::Freq;
      //const_cast<float *>  (resdown)[hh] /= Global::Freq;
      //const_cast<float *>  (fertdown1)[hh] /= Global::Freq;
      //const_cast<float *>  (fertdown2)[hh] /= Global::Freq;
      //const_cast<float *>  (mandown1)[hh] /= Global::Freq;
      //const_cast<float *>  (mandown2)[hh] /= Global::Freq;
    }
  } // begining of run

    if(Inhibit_Soil_BGC[0])
      return;

    dayno = julian("now");

    for(hh = 0; chkStruct(); ++hh){ // Using inhibit is dangerous
      water_lay[0][hh] = soil_rechr[hh]; // water_lay dimensioned 3 and soil_rechr and soil_moist only 2D.
      water_lay[1][hh] = soil_moist[hh] - soil_rechr[hh];
      watermax_lay[0][hh] = soil_rechr_max[hh]; 
      watermax_lay[1][hh] = soil_moist_max[hh] - soil_rechr_max[hh];
      for(long ii = 0; ii < maxsoillayers ; ++ii) // [maxsoillayers]
        Temp_lay[ii][hh] = hru_t[hh]; // convert air temperature to soil temperature ???
        
    } // for hh */

    for(hh = 0; chkStruct(); ++hh){
      soil_np_processes();
    }
}

void ClassWQ_SoilBGC::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessage(hh, string("'" + Name + " (WQ_Soil_BGC)'").c_str(), BLANK);
  }
  LogDebug(" ");
}

// Calculate nutrient processes in soil; sources, transformations, and retention
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Soil processes)
// ------------------------------------------------------------------------------

  void ClassWQ_SoilBGC::soil_np_processes(){

/*    USE MODVAR, ONLY : numsubstances,     & 10,     & i_no3n

    logical calcN                    // <Status of nitrogen simulation
    logical calcP                    // <Status of phosphorus simulation
    logical calcC                    // <Status of organic carbon simulation
    long    dayno                    // <day number of the year
    float   area                     // <class area (km2)
    float wp(10)                    // <water content at wilting point (mm)
    float fc(10)                    // <water content at field capacity (mm)
    float ep(10)                    // <water content in effective porosity (mm)
    float commoplant_uptk_NO3N(2,2)       // <uptake by plants (kg NP/km2/timestep)
    float thickness[maxsoillayers] // <thickness of soil layers
    float ndays                    // <model parameter, days for fertilization
    float ldays                    // <model parameter, days for litterfall
    float source(numsubstances)    // <source of soil water nutrients through mineralization
    float sink(numsubstances)      // <OBS: denitrification sink only
    float nitrification            // <nitrification
    float denitrification(maxsoillayers)  // <denitrification
    float cropuptake                  // <crop uptake of IN
    float sources(2,numsubstances)    // <loads of fertilizer and residuals (kg/timestep)
    float pardisfN                  // <model parameter mineralisation labileN to dissolved ON
    float pardisfP                  // <model parameter mineralisation labileP to dissolved OP
    float pardishN                  // <model parameter mineralisation refractoryN to dissolved ON
    float pardishP                  // <model parameter mineralisation refractoryP to dissolved OP
    float parminfN                  // <model parameter mineralisation labileN
    float parminfP                  // <model parameter mineralisation labileP
    float pardegrhN                 // <model parameter degradation refractoryN
    float pardenN                   // <model parameter denitrification in soil
    float pardegrhP                 // <model parameter degradation refractoryP
    float soilstate                 // <Soil states
*/
// No substances modelled
	  
// Calculate the nutrient processes
    nutrient_inputs(); // fertilizer, manure and residues, also orgC
	
    soil_pool_transformations();   // transformation from refractoryN->labileN->IN, ON->IN and labileP->SRP refractoryP -> labileP
	
	
    if (soil_runoff[hh] > 0.0f){
      runoff_pp_by_erosion();
    }	
    
	
    plant_uptake(conc_soil_rechr_lay, conc_soil_lower_lay, sink_lay);

	
    if(i_no3n >= 0)
      cropuptake[hh] = sink_lay[i_no3n][hh];

   if(calcN[hh]){	   
      denitrification_surfsoil[hh] = 0.0;
      denitrification_lay[0][hh] = 0.0;
      denitrification_lay[1][hh] = 0.0;
     	  
	  if (water_lay[0][hh] > 0.0)
		  soil_denitrification(0);
		  denitrification_lay[0][hh] = sink_lay[i_no3n][hh];
			  
	  if (water_lay[1][hh] > 0.0)
		  soil_denitrification(1);
		  denitrification_lay[1][hh] = sink_lay[i_no3n][hh];		
    }
   
  } // soil_np_processes

// Calculate and add the crops sources of nutrient to the soil(fertilization and crop residues).
//
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Nutrient sources - Fertilizer, Plant residues)
// --------------------------------------------------------------
      void  ClassWQ_SoilBGC::nutrient_inputs(){

/*
    USE MODVAR, ONLY : numsubstances, 10, cropdata, i_no3n,i_don,i_srp,i_pp,i_oc, prevdoy

    Argument declarations
    logical INTENT(IN) :: calcN    !<Status of nitrogen simulation
    logical INTENT(IN) :: calcP    !<Status of phosphorus simulation
    logical INTENT(IN) :: calcC    !<Status of organic carbon simulation
    float ndays                    !<number of days to spread fertilizer
    float ldays                    !<number of days to spread plant residuals
    float area                     !<class area (km2)
    float thickness(maxsoillayers) !<thickness of soil layers (m)
    float soilstate !<Soil states
    float sources(2,numsubstances) !<load from fertilizer and plant residues (kg/timestep) ****now sources_i_no3n_lay etc.***
*/

// Local variables
    long k,kcrop;
    float common_nadd[maxsoillayers][2]; // kg/km2   where 0 - manureinogNfrac, 1 - manurelabileNfrac
    float common_padd[maxsoillayers][2]; // kg/km2
    float common_nres[maxsoillayers][2]; // kg/km2
    float common_pres[maxsoillayers][2]; // kg/km2
    float common_cres[maxsoillayers][2]; // kg/km2

    float littdays;

    for(long ll = 0; ll < numsubstances; ++ll) {
      src_mineral_fertman_surfsoil_lay[ll][hh] = 0.0f;
      src_mineral_fertman_soilrechr_lay[ll][hh] = 0.0f;
      sources_plant_lay[ll][hh] = 0.0;
    }

    if(!(calcN[hh] || calcP[hh] || calcC[hh]))
      return;   // no substance modelled

    for (long ii = 0.0; ii < maxsoillayers; ++ii){
      for (long kk = 0.0; kk < 2; ++kk){ // kg/km2   where 0 - manureinogNfrac, 1 - manurelabileNfrac
        common_nadd[ii][kk]   = 0.0;
        common_padd[ii][kk]   = 0.0;
        common_nres[ii][kk]   = 0.0;
        common_pres[ii][kk]   = 0.0;
        common_cres[ii][kk]   = 0.0;
      }
    } // for

  int Y,M,D, H, Min;
  StandardConverterUtility::DecodeDateTime(Global::DTnow, &Y, &M, &D, &H, &Min);
  //Global::DTnow.DecodeDate(&Y,&M,&D);

  try{

  long prevdoy = (int)(StandardConverterUtility::EncodeDateTime(Y-1, 12, 31, 0, 0) - StandardConverterUtility::EncodeDateTime(Y-1, 1, 1, 0, 0)) + 1; // calculates #days in previous year

// Calculate common fertiliser and manure use (inorg 0, fast 1)   common_nadd[layer][inorg/fast or labile/humus)]

      if(fertday_up[hh] && ((dayno >= fertday_up[hh] && dayno < fertday_up[hh] + fertperiod[hh])  ||
           (dayno < fertday_up[hh] + fertperiod[hh] - prevdoy))){
          common_nadd[0][0] = common_nadd[0][inorg] + fertNamount_up[hh] / fertperiod[hh];
          common_padd[0][0] = common_padd[0][inorg] + fertPamount_up[hh] / fertperiod[hh];
          //common_nadd[1][0] = common_nadd[1][inorg] + fertNamount_down[hh] / fertperiod[hh]; // move some to lower layer
          //common_padd[1][0] = common_padd[1][inorg] + fertPamount_down[hh] / fertperiod[hh];
        //}
        //else{
        //  common_nadd[0][0] = common_nadd[0][inorg] + fertNamount_up[hh] / fertperiod[hh];
        //  common_padd[0][0] = common_padd[0][inorg] + fertPamount_up[hh] / fertperiod[hh];
        //}
      } // if

      if(fertday_down[hh] && ((dayno >= fertday_down[hh] && dayno < fertday_down[hh] + fertperiod[hh])  ||
           (dayno < fertday_down[hh] + fertperiod[hh] - prevdoy))){
        //if(water_lay[1][hh] > 0.0){
          //common_nadd[0][0] = common_nadd[0][inorg] + fertNamount_down[hh] / fertperiod[hh];
          //common_padd[0][0] = common_padd[0][inorg] + fertPamount_down[hh] / fertperiod[hh];
          common_nadd[1][0] = common_nadd[1][inorg] + fertNamount_down[hh] / fertperiod[hh]; // move some to lower layer
          common_padd[1][0] = common_padd[1][inorg] + fertPamount_down[hh] / fertperiod[hh];
        //}
        //else{
        //  common_nadd[0][0] = common_nadd[0][inorg] + fertNamount_down[hh] / fertperiod[hh];
        //  common_padd[0][0] = common_padd[0][inorg] + fertPamount_down[hh] / fertperiod[hh];
        //}
      } // if

      if(manday_up[hh] && ((dayno >= manday_up[hh] && dayno < manday_up[hh] + fertperiod[hh])  ||
           (dayno < manday_up[hh] + fertperiod[hh] - prevdoy))){
       // if(water_lay[1][hh] > 0.0){
          common_nadd[0][0] = common_nadd[0][inorg] + manNamount_up[hh] * manureinogNfrac[hh] / fertperiod[hh];
          common_padd[0][0] = common_padd[0][inorg] + manPamount_up[hh] * manureinogPfrac[hh] / fertperiod[hh];
          common_nadd[0][1] = common_nadd[0][fast] + manNamount_up[hh] * (1.0 - manureinogNfrac[hh]) / fertperiod[hh];
          common_padd[0][1] = common_padd[0][fast] + manPamount_up[hh] * (1.0 - manureinogPfrac[hh]) / fertperiod[hh];
          //common_nadd[1][0] = common_nadd[1][inorg] + manNamount_up[hh] * mandown1[hh] * manureinogNfrac[hh] / fertperiod[hh];
          //common_padd[1][0] = common_padd[1][inorg] + manPamount_up[hh] * mandown1[hh] * manureinogPfrac[hh] / fertperiod[hh];
          //common_nadd[1][1] = common_nadd[1][fast] + manNamount_up[hh] * mandown1[hh] * (1.0 - manureinogNfrac[hh]) / fertperiod[hh];
          //common_padd[1][1] = common_padd[1][fast] + manPamount_up[hh] * mandown1[hh] * (1.0 - manureinogPfrac[hh]) / fertperiod[hh];
        //}
        //else{
        //  common_nadd[0][0] = common_nadd[0][inorg] + manNamount_up[hh] * manureinogNfrac[hh] / fertperiod[hh];
        //  common_padd[0][0] = common_padd[0][inorg] + manPamount_up[hh] * manureinogPfrac[hh] / fertperiod[hh];
        //  common_nadd[0][1] = common_nadd[0][fast] + manNamount_up[hh] * (1.0 - manureinogNfrac[hh]) / fertperiod[hh];
        //  common_padd[0][1] = common_padd[0][fast] + manPamount_up[hh] * (1.0 - manureinogPfrac[hh]) / fertperiod[hh];
        //}
      } // if

      if(manday_down[hh] && ((dayno >= manday_down[hh] && dayno < manday_down[hh] + fertperiod[hh])  || (dayno < manday_down[hh] + fertperiod[hh] - prevdoy))){
        //if(water_lay[1][hh] > 0.0){
          //common_nadd[0][0] = common_nadd[0][inorg] + manNamount_down[hh] * (1.0 - mandown2[hh]) * manureinogNfrac[hh] / fertperiod[hh];
          //common_padd[0][0] = common_padd[0][inorg] + manPamount_down[hh] * (1.0 - mandown2[hh]) * manureinogPfrac[hh] / fertperiod[hh];
          //common_nadd[0][1] = common_nadd[0][fast] + manNamount_down[hh] * (1.0 - mandown2[hh]) * (1.-manureinogNfrac[hh]) / fertperiod[hh];
          //common_padd[0][1] = common_padd[0][fast] + manPamount_down[hh] * (1.0 - mandown2[hh]) * (1.-manureinogPfrac[hh]) / fertperiod[hh];
          common_nadd[1][0] = common_nadd[1][inorg] + manNamount_down[hh] * manureinogNfrac[hh] / fertperiod[hh];
          common_padd[1][0] = common_padd[1][inorg] + manPamount_down[hh] * manureinogPfrac[hh] / fertperiod[hh];
          common_nadd[1][1] = common_nadd[1][fast] + manNamount_down[hh] * (1.0-manureinogNfrac[hh]) / fertperiod[hh];
          common_padd[1][1] = common_padd[1][fast] + manPamount_down[hh] * (1.0-manureinogPfrac[hh]) / fertperiod[hh];
        //}
        //else{
        //  common_nadd[0][0] = common_nadd[0][inorg] + manNamount_down[hh] * manureinogNfrac[hh] / fertperiod[hh];
        //  common_padd[0][0] = common_padd[0][inorg] + manPamount_down[hh] * manureinogPfrac[hh] / fertperiod[hh];
        //  common_nadd[0][1] = common_nadd[0][fast] + manNamount_down[hh] * (1.0 - manureinogNfrac[hh]) / fertperiod[hh];
        //  common_padd[0][1] = common_padd[0][fast] + manPamount_down[hh] * (1.0 - manureinogPfrac[hh]) / fertperiod[hh];
        //}
      } // if


// Calculate common residues    fast(1)  labile        (0)  refractoryNpart

      //if(resday_up[hh] == 0) // fixes cannot modify a constant
      //  littdays = 365.0;   // litterfall every day
      //else
        littdays = litterperiod[hh]; // litterfall every day

      if(resday_up[hh] ||
           ((dayno >= resday_up[hh] && dayno < resday_up[hh] + littdays)  ||
           (dayno < resday_up[hh] + littdays - prevdoy))){
        //if(water_lay[1][hh] > 0.0){
          common_nres[0][0] = common_nres[0][inorg] + resfast[hh] *  resNamount_up[hh] / littdays;
          common_nres[0][1] = common_nres[0][fast] + (1.0 - resfast[hh]) *  resNamount_up[hh] / littdays;
          common_pres[0][0] = common_pres[0][inorg] + resfast[hh] *  resPamount_up[hh] / littdays;
          common_pres[0][1] = common_pres[0][fast] + (1.0 - resfast[hh]) *  resPamount_up[hh] / littdays;
          
          //common_cres[0][0] = common_cres[0][inorg] + resCamount[hh] * (1.0 - resdown[hh]) / littdays;  //CP121031
          //common_cres[1][0] = common_cres[1][inorg] + resCamount[hh] * resdown[hh] / littdays;
        //}
        //else{
        //  common_nres[0][0] = common_nres[0][inorg] + resfast[hh] *  resNamount_up[hh] / littdays;
        // common_nres[0][1] = common_nres[0][fast] + (1.0 - resfast[hh]) *  resNamount_up[hh] / littdays;
        //  common_pres[0][0] = common_pres[0][inorg] + resfast[hh] *  resPamount_up[hh] / littdays;
        //  common_pres[0][1] = common_pres[0][fast] + (1.0 - resfast[hh]) *  resPamount_up[hh] / littdays;
        //  common_cres[0][0] = common_cres[0][inorg] + resCamount[hh] / littdays;
        //}
      }

       if(resday_down[hh] ||
           ((dayno >= resday_down[hh] && dayno < resday_down[hh] + littdays)  ||
           (dayno < resday_down[hh] + littdays - prevdoy))){
        //if(water_lay[1][hh] > 0.0){
          common_nres[1][0] = common_nres[0][inorg] + resfast[hh] *  resNamount_down[hh] / littdays;
          common_nres[1][1] = common_nres[0][fast] + (1.0 - resfast[hh]) *  resNamount_down[hh] / littdays;
          common_pres[1][0] = common_pres[0][inorg] + resfast[hh] *  resPamount_down[hh] / littdays;
          common_pres[1][1] = common_pres[0][fast] + (1.0 - resfast[hh]) *  resPamount_down[hh] / littdays;
      }


// Add fertiliser and manure

      // mineral N (fertilizer and manure)
      if(calcN[hh]  &&  SUM(common_nadd, 0) > 0.0){

        if (SWE[hh]>minFlow_WQ){ // if SWE > 0, fertilizer goes to SWE 
          SWE_conc_lay[i_no3n][hh] += fertandman_inogNfrac_NO3Nfrac[hh] * common_nadd[0][inorg]/SWE[hh];
          SWE_conc_lay[i_nh4n][hh] += fertandman_inogNfrac_NH4Nfrac[hh] * common_nadd[0][inorg]/SWE[hh];
        }else{
          surfsoil_solub_mWQ_lay[i_no3n][hh] += fertandman_inogNfrac_NO3Nfrac[hh] * common_nadd[0][inorg];
          surfsoil_solub_mWQ_lay[i_nh4n][hh] += fertandman_inogNfrac_NH4Nfrac[hh] * common_nadd[0][inorg];
        }

        if(water_lay[0][hh] > 0.0){
          add_source_to_water(water_lay[0][hh], i_no3n, &conc_soil_rechr_lay[i_no3n][hh], fertandman_inogNfrac_NO3Nfrac[hh] * common_nadd[1][inorg]); // i_no3n      
          add_source_to_water(water_lay[0][hh], i_nh4n, &conc_soil_rechr_lay[i_nh4n][hh], fertandman_inogNfrac_NH4Nfrac[hh] * common_nadd[1][inorg]); // i_nh4
        } 
        else if(water_lay[1][hh] > 0.0){
          add_source_to_water(water_lay[1][hh], i_no3n, &conc_soil_lower_lay[i_no3n][hh], fertandman_inogNfrac_NO3Nfrac[hh] * common_nadd[1][inorg]); // i_no3n      
          add_source_to_water(water_lay[1][hh], i_nh4n, &conc_soil_lower_lay[i_nh4n][hh], fertandman_inogNfrac_NH4Nfrac[hh] * common_nadd[1][inorg]); // i_nh4
        }
        else{
          production_pool(1, labileN_lay[0][hh], common_nadd[1][inorg]);
          //sources_fertilizer_lay[i_don][hh] += common_nadd[0][inorg]; // OrgN load from fertilizer from soil layer 1 (kg)
        }
        src_mineral_fertman_surfsoil_lay[i_no3n][hh] += fertandman_inogNfrac_NO3Nfrac[hh] * (common_nadd[0][inorg]); // InorgN load from fertilizer from soil layer 1 (kg)
        src_mineral_fertman_surfsoil_lay[i_nh4n][hh] += fertandman_inogNfrac_NH4Nfrac[hh] * (common_nadd[0][inorg]); // InorgN load from fertilizer from soil layer 1 (kg)
        src_mineral_fertman_soilrechr_lay[i_no3n][hh] += fertandman_inogNfrac_NO3Nfrac[hh] * (common_nadd[1][inorg]); // InorgN load from fertilizer from soil layer 1 (kg)
        src_mineral_fertman_soilrechr_lay[i_nh4n][hh] += fertandman_inogNfrac_NH4Nfrac[hh] * (common_nadd[1][inorg]); // InorgN load from fertilizer from soil layer 1 (kg)

      }

      // mineral P (fertilizer and manure)
      if(calcP[hh]  &&  SUM(common_padd, 0) > 0.0){

        if (SWE[hh]>minFlow_WQ){ // if SWE > 0, fertilizer goes to SWE 
          SWE_conc_lay[i_srp][hh] += common_padd[0][inorg]/SWE[hh];
        }else{
          surfsoil_solub_mWQ_lay[i_srp][hh] += common_padd[0][inorg];
        }

        if(water_lay[0][hh] > 0.0){
          add_source_to_water(water_lay[0][hh], i_srp , &conc_soil_rechr_lay[i_srp][hh], common_padd[1][inorg]);     
        }
        else if(water_lay[1][hh] > 0.0){
          add_source_to_water(water_lay[1][hh], i_srp , &conc_soil_lower_lay[i_srp][hh], common_padd[1][inorg]);     
        }
        else{
          production_pool(1, labileP_lay[0][hh], common_padd[1][inorg]);
        }
        src_mineral_fertman_surfsoil_lay[i_srp][hh] += common_padd[0][inorg];      // SRP load from fertilizer, soil layer 1 (kg)
        src_mineral_fertman_soilrechr_lay[i_srp][hh] += common_nadd[1][inorg];      // SRP load from fertilizer, soil layer 1 (kg)
      }

      // manure organic N
      if(calcN[hh] && SUM(common_nadd, 1) > 0.0){ // refractoryNfastpart
          surfsoil_labileN_mWQ[hh] += common_nadd[0][1];
          labileN_lay[0][hh] += common_nadd[1][1];
          production_pool(1, hh, labileN_lay, common_nadd);
      }

      // manure organic P
      if(calcP[hh]  &&  SUM(common_padd, 1) > 0.0){
        surfsoil_labileP_mWQ[hh] += common_padd[0][1];
        labileP_lay[0][hh] += common_padd[1][1];
      }

// Add residues
      // N (labile and refractory)
      if(calcN[hh]  &&  (SUM(common_nres, 0) + SUM(common_nres, 1)) > 0.0){
        surfsoil_labileN_mWQ[hh] += common_nres[0][0];
        surfsoil_refractoryN_mWQ[hh] += common_nres[0][1];
        labileN_lay[0][hh] += common_nres[1][0];
        refractoryN_lay[0][hh] += common_nres[1][1];
        sources_plant_lay[i_don][hh] = SUM(common_nres, 0) + SUM(common_nres, 1); // OrgN load from residuals, all soil layers and N types (kg)
      }

      if(calcP[hh] && (SUM(common_pres, 0) + SUM(common_pres, 1)) > 0.0){
        surfsoil_labileP_mWQ[hh] += common_pres[0][0];
        surfsoil_refractoryP_mWQ[hh] += common_pres[0][1];
        labileP_lay[0][hh] += common_pres[1][0];
        refractoryP_lay[0][hh] += common_pres[1][1];
        sources_plant_lay[i_pp][hh] = SUM(common_pres, 0) + SUM(common_pres, 1); // PartP load from residuals, all soil layers and P types (kg)
      }

      if(calcC[hh]  &&  (SUM(common_cres, 0) + SUM(common_cres, 1)) > 0.0){
        if(water_lay[1][hh] > 0.0)
           production_pool(1, hh, labileC_lay, common_cres);
        else 
           production_pool(1, hh, labileC_lay, common_cres);

        sources_plant_lay[i_oc][hh] = SUM(common_cres, 0) + SUM(common_cres, 1); // OrgC load from residuals, all soil layers (kg)
      }
    }  // try
    catch(...)
    {
      //string S = E.Message + " at " +
		string S = string("Error ") + " at " +
		  StandardConverterUtility::GetDateTimeInString(Global::DTnow) + " (" + to_string(getstep()) + ") in '" + Global::OurModulesList->Strings[Global::CurrentModuleRun] +
          "'" + " (" + FloatToStrF(Global::DTnow, ffGeneral, 10, 6) + ") hh = " + FloatToStrF(hh, ffGeneral, 6, 0);
      LogError(S, WARNING);
      throw;
    }
  }  // crop_sources

// Transformation between NP-pools in soil. Degradation/delay functions.
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Soil processes)
// ------------------------------------------------------------------------------

    void ClassWQ_SoilBGC::soil_pool_transformations(){
/*
    USE MODVAR, ONLY : numsubstances, maxsoillayers, i_no3n,i_don,i_srp,i_pp

    USE HYPEVARIABLES, ONLY : satact, Thetapow, Thetalow,T hetaupp

Argument declarations
    logical calcN                  !<flag for nitrogen simulation
    logical calcP                  !<flag for phosphorus simulation
    float wp(maxsoillayers)        !<water content at wilting point (mm)
    float fc(maxsoillayers)        !<water content at field capacity (mm)
    float ep(maxsoillayers)        !<water content: effectiv porosity (mm)
    float thickness(maxsoillayers) !<thickness of soil layers
    float source(numsubstances)    !<source of soil water nutrients through mineralization
    float pardisfN            !<model parameter mineralisation labileN to dissolved ON
    float pardisfP            !<model parameter mineralisation labileP to dissolved OP
    float pardishN            !<model parameter mineralisation refractoryN to dissolved ON
    float pardishP            !<model parameter mineralisation refractoryP to dissolved OP
    float minfNpar            !<model parameter mineralisation labileN
    float minfPpar            !<model parameter mineralisation labileP
    float degrhNpar           !<model parameter degradation refractoryN
    float degrhPpar           !<model parameter degradation refractoryP
    float soilstate           !<Soil states
*/

// Local variables
    long k;   // soillayer
    float degradhN[maxsoillayers] ,transfminN[maxsoillayers], transfnitrN[maxsoillayers];
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
      NO3_Npool_lay[ii][hh] = 0.0f;
      NH4_Npool_lay[ii][hh] = 0.0f;
      SRPpool_lay[ii][hh] = 0.0f;
      DONpool_lay[ii][hh] = 0.0f;
      DOPpool_lay[ii][hh] = 0.0f;
      partP_lay[ii][hh] = 0.0f;
      degradhN[ii] = 0.0f;
      transfminN[ii] = 0.0f;
      dissolfN[ii] = 0.0f;
      dissolhN[ii] = 0.0f;
      degradhP[ii] = 0.0f;
      transfP[ii] = 0.0f;
      dissolfP[ii] = 0.0f;
      dissolhP[ii] = 0.0f;
      smfcn[ii] = 0.0f;
    }

// Current pools of N and P dissolved in soil water

    if(calcN[hh]){
      NO3_Npool_lay[0][hh] = conc_soil_rechr_lay[i_no3n][hh] * water_lay[0][hh];
      NH4_Npool_lay[0][hh] = conc_soil_rechr_lay[i_nh4n][hh] * water_lay[0][hh];
      DONpool_lay[0][hh] = conc_soil_rechr_lay[i_don][hh] * water_lay[0][hh];
      NO3_Npool_lay[1][hh] = conc_soil_lower_lay[i_no3n][hh] * water_lay[1][hh];
      NH4_Npool_lay[1][hh] = conc_soil_lower_lay[i_nh4n][hh] * water_lay[1][hh];
      DONpool_lay[1][hh] = conc_soil_lower_lay[i_don][hh] * water_lay[1][hh];
    }

    if(calcP[hh]){
      SRPpool_lay[0][hh] = conc_soil_rechr_lay[i_srp][hh] * water_lay[0][hh];
      DOPpool_lay[0][hh] = conc_soil_rechr_lay[i_dop][hh] * water_lay[0][hh];
      partP_lay[0][hh] = conc_soil_rechr_lay[i_pp][hh] * water_lay[0][hh];
      SRPpool_lay[1][hh] = conc_soil_lower_lay[i_srp][hh] * water_lay[1][hh];
      DOPpool_lay[1][hh] = conc_soil_lower_lay[i_dop][hh] * water_lay[1][hh];
      partP_lay[1][hh] = conc_soil_rechr_lay[i_pp][hh] * water_lay[1][hh];
    }

// Temperature dependence factor
    for (long k = 0; k < maxsoillayers; ++k)
      if(water_lay[k][hh] > 0.0){
        tmpfcn[k] = tempfactor(Temp_lay[0][hh]); // requires soil temperature
      }

// Soil moisture dependence factor

    smfcn[0] = moisturefactor(water_lay[0][hh]/watermax_lay[0][hh],
            wp_lay[0][hh], 
            satact, thetapow, thetalow, thetaupp);
    smfcn[1] = moisturefactor(water_lay[1][hh]/watermax_lay[1][hh], 
            wp_lay[1][hh], 
            satact, thetapow, thetalow, thetaupp);

// Degradation of refractoryN to labileN

    if(calcN[hh]){

      degradhN[0] = pardegrhN[hh] * tmpfcn[0] * smfcn[0]* surfsoil_refractoryN_mWQ[hh];
      surfsoil_refractoryN_mWQ[hh] -= degradhN[0];
      surfsoil_labileN_mWQ[hh] += degradhN[0];

      degradhN[0] = pardegrhN[hh] * tmpfcn[0] * smfcn[0]* refractoryN_lay[0][hh];
      degradhN[1] = pardegrhN[hh] * tmpfcn[1] * smfcn[1]* refractoryN_lay[1][hh];

      if(water_lay[1][hh] > 0.0){
         retention_pool(2, hh, refractoryN_lay, degradhN);      // subtract - may change degradhN  1:2
         production_pool(2, hh, labileN_lay, degradhN);      // add                        1:2
      }
      else{
         retention_pool(1, hh, refractoryN_lay, degradhN);      // subtract - may change degradhN
         production_pool(1, hh, labileN_lay, degradhN);      // add
      }

// Transformation of labileN into NH4 (mineralization/amonification)

      transfminN[0] = std::fmax(parminfN[hh] * tmpfcn[0] * smfcn[0] * surfsoil_labileN_mWQ[hh],0.0f);
      surfsoil_labileN_mWQ[hh] -= transfminN[0];
      surfsoil_solub_mWQ_lay[i_nh4n][hh] += transfminN[0];

      transfminN[0] = std::fmax(parminfN[hh] * tmpfcn[0] * smfcn[0] * labileN_lay[0][hh],0.0f); 
      transfminN[1] = std::fmax(parminfN[hh] * tmpfcn[1] * smfcn[1] * labileN_lay[1][hh],0.0f);

      if(water_lay[1][hh] > 0.0){
         retention_pool(2, hh, labileN_lay, transfminN); // subtract - transfminN may change in retention_pool (1:2)
         production_pool(2, hh, NH4_Npool_lay, transfminN);   // add                                            //   (1:2)
      }
      else{
         retention_pool(1, hh, labileN_lay, transfminN); // subtract - transfminN may change in retention_pool
         production_pool(1, hh, NH4_Npool_lay, transfminN);   // add
      }

       new_concentration(NH4_Npool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_nh4n][hh]);
      if(water_lay[1][hh] > 0.0)
        new_concentration(NH4_Npool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_nh4n][hh]);

// Transformation of NH4 into NH3 (nitrification)

      transfnitrN[0] = std::fmax(parnitrfN[hh] * tmpfcn[0] * smfcn[0] * surfsoil_solub_mWQ_lay[i_nh4n][hh],0.0f); 
      surfsoil_solub_mWQ_lay[i_nh4n][hh] -= transfnitrN[0];
      surfsoil_solub_mWQ_lay[i_no3n][hh] += transfnitrN[0];

      transfnitrN[0] = std::fmax(parnitrfN[hh] * tmpfcn[0] * smfcn[0] * NH4_Npool_lay[0][hh],0.0f); 
      transfnitrN[1] = std::fmax(parnitrfN[hh] * tmpfcn[1] * smfcn[1] * NH4_Npool_lay[1][hh],0.0f);

      if(water_lay[1][hh] > 0.0){
         retention_pool(2, hh, NH4_Npool_lay, transfnitrN); // subtract - transfminN may change in retention_pool (1:2)
         production_pool(2, hh, NO3_Npool_lay, transfnitrN);   // add                                            //   (1:2)
      }
      else{
         retention_pool(1, hh, NH4_Npool_lay, transfnitrN); // subtract - transfminN may change in retention_pool
         production_pool(1, hh, NO3_Npool_lay, transfnitrN);   // add
      }

       new_concentration(NH4_Npool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_nh4n][hh]);
       new_concentration(NO3_Npool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_no3n][hh]);
      if(water_lay[1][hh] > 0.0){
        new_concentration(NH4_Npool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_nh4n][hh]);
        new_concentration(NO3_Npool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_no3n][hh]);
      }
    } // calcN


// Degradation of refractoryP to labileP

    if(calcP[hh]){

      degradhP[0] = pardegrhP[hh] * tmpfcn[0] * smfcn[0]* surfsoil_refractoryP_mWQ[hh];
      surfsoil_refractoryP_mWQ[hh] -= degradhP[0];
      surfsoil_labileP_mWQ[hh] += degradhP[0];

      degradhP[0] = pardegrhP[hh] * tmpfcn[0] * smfcn[0] * refractoryP_lay[0][hh];
      degradhP[1] = pardegrhP[hh] * tmpfcn[1] * smfcn[1] * refractoryP_lay[1][hh];

      if(water_lay[1][hh] > 0.0){
         retention_pool(2, hh, refractoryP_lay, degradhP); // subtract - may change degradhP  1:2
         production_pool(2, hh, labileP_lay, degradhP); // add
      }
      else{
         retention_pool(1, hh, refractoryP_lay, degradhP); // subtract - may change degradhP   1:2
         production_pool(1, hh, labileP_lay, degradhP); // add
      }

// Transformation of labileP to SRP

      transfP[0] = std::fmax(parminfP[hh] * tmpfcn[0] * smfcn[0] * surfsoil_labileP_mWQ[hh],0.0f);
      surfsoil_labileP_mWQ[hh] -= transfP[0];
      surfsoil_solub_mWQ_lay[i_srp][hh] += transfP[0];

      transfP[0] = parminfP[hh] * tmpfcn[0] * smfcn[0] * labileP_lay[0][hh];
      transfP[1] = parminfP[hh] * tmpfcn[1] * smfcn[1] * labileP_lay[1][hh];

      if(water_lay[1][hh] > 0){
         retention_pool(2, hh, labileP_lay, transfP); // subtract - transfP may change in retention_pool
         production_pool(2, hh, SRPpool_lay, transfP);
      }
      else{
         retention_pool(1, hh, labileP_lay, transfP); // subtract - transfP may change in retention_pool
         production_pool(1, hh, SRPpool_lay, transfP);
      }

// Calculate the new soil concentrations of SRP

       new_concentration(SRPpool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_srp][hh]);
      if(water_lay[1][hh] > 0.0)
        new_concentration(SRPpool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_srp][hh]);
    } // calcP

// Transformation of labileN to dissolved organic N

    if(calcN[hh]){

      dissolfN[0] = std::fmax(pardisfN[hh] * tmpfcn[0] * smfcn[0] * surfsoil_labileN_mWQ[hh],0.0f);
      surfsoil_labileN_mWQ[hh] -= dissolfN[0];
      surfsoil_solub_mWQ_lay[i_don][hh] += dissolfN[0];

      dissolfN[0] = pardisfN[hh] * tmpfcn[0] * smfcn[0] * labileN_lay[0][hh];
      dissolfN[1] = pardisfN[hh] * tmpfcn[1] * smfcn[1] * labileN_lay[1][hh];

      if(water_lay[1][hh] > 0.0){
         retention_pool(2, hh, labileN_lay, dissolfN); // subtract - dissolfN may change in retention_pool
         production_pool(2, hh, DONpool_lay, dissolfN);
      }
      else{
         retention_pool(1, hh, labileN_lay, dissolfN); // subtract - dissolfN may change in retention_pool
         production_pool(1, hh, DONpool_lay, dissolfN);
      }

// Transformation of refractoryN to dissolved organic N

      dissolhN[0] = pardishN[hh] * tmpfcn[0] * smfcn[0] * surfsoil_refractoryN_mWQ[hh];
      surfsoil_refractoryN_mWQ[hh] -= dissolhN[0];
      surfsoil_solub_mWQ_lay[i_don][hh] += dissolhN[0];

      dissolhN[0] = pardishN[hh] * tmpfcn[0] * smfcn[0] * refractoryN_lay[0][hh];
      dissolhN[1] = pardishN[hh] * tmpfcn[1] * smfcn[1] * refractoryN_lay[1][hh];

      if(water_lay[1][hh] > 0.0){
         retention_pool(2, hh, refractoryN_lay, dissolhN); // subtract - dissolhN may change in retention_pool
         production_pool(2, hh, DONpool_lay, dissolhN);       // add
      }
      else{
         retention_pool(1, hh, refractoryN_lay, dissolhN); // subtract - dissolhN may change in retention_pool
         production_pool(1, hh, DONpool_lay, dissolhN);       // add
      }

// Calculate the new soil concentrations of ON

      new_concentration(DONpool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_don][hh]);
      if(water_lay[1][hh] > 0.0)
        new_concentration(DONpool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_don][hh]);
    } // calcN


// Transformation of labileP to dissolved organic P (DOP/PP)

    if(calcP[hh]){

      dissolfP[0] = pardisfP[hh] * tmpfcn[0] * smfcn[0] * surfsoil_labileP_mWQ[hh];
      surfsoil_labileP_mWQ[hh] -= dissolfP[0];
      surfsoil_solub_mWQ_lay[i_dop][hh] += dissolfP[0];

      dissolfP[0] = pardisfP[hh] * tmpfcn[0] * smfcn[0] * labileP_lay[0][hh];
      dissolfP[1] = pardisfP[hh] * tmpfcn[1] * smfcn[1] * labileP_lay[1][hh];

      if(water_lay[1][hh] > 0.0){
         retention_pool(2, hh, labileP_lay, dissolfP); // subtract - dissolfP may change in retention_pool
         production_pool(2, hh, DOPpool_lay, dissolfP);      // add
      }
      else{
         retention_pool(1, hh, labileP_lay, dissolfP); // subtract - dissolfP may change in retention_pool
         production_pool(1, hh, DOPpool_lay, dissolfP);      // add
      }

// Transformation of refractoryP to dissolved organic P

      dissolhP[0] = pardishP[hh] * tmpfcn[0] * smfcn[0] * surfsoil_refractoryP_mWQ[hh];
      surfsoil_refractoryP_mWQ[hh] -= dissolhP[0];
      surfsoil_solub_mWQ_lay[i_dop][hh] += dissolhP[0];

      dissolhP[0] = pardishP[hh] * tmpfcn[0] * smfcn[0] * refractoryP_lay[0][hh];
      dissolhP[1] = pardishP[hh] * tmpfcn[1] * smfcn[1] * refractoryP_lay[1][hh];

      if(water_lay[1][hh] > 0.0){
         retention_pool(2, hh, refractoryP_lay, dissolhP); // subtract - dissolhP may change in retention_pool
         production_pool(2, hh, DOPpool_lay, dissolhP);       // add
      }
      else{
         retention_pool(1, hh, refractoryP_lay, dissolhP); // subtract - dissolhP may change in retention_pool
         production_pool(1, hh, DOPpool_lay, dissolhP);       // add
      }

// Calculate the new soil concentrations of PP (DOP)

      new_concentration(DOPpool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_dop][hh]);
      if(water_lay[1][hh] > 0.0)
        new_concentration(DOPpool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_dop][hh]);
    } // calcP

// Sum the sources (kg/km2)

    if(calcN[hh]){
       source_lay[i_no3n][hh] = SUM(transfminN);
       source_lay[i_don][hh] = SUM(dissolfN) + SUM(dissolhN);
    }

    if(calcP[hh]){
       source_lay[i_srp][hh] = SUM(transfP);
       source_lay[i_pp][hh] = SUM(dissolfP) + SUM(dissolhP);
    }
  }  // soil_pool_transformations

// Calculate retention in soil due to plant uptake
// Inorganic nitrogen and phosphorus is removed.
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Soil processes - Vegetation nutrient uptake)
// -------------------------------------------------------------------
    void  ClassWQ_SoilBGC::plant_uptake(float **conc_soil_rechr_lay, float **conc_soil_lower_lay, float **sink_lay){

//    USE MODVAR, ONLY : numsubstances, maxsoillayers, i_no3n, i_srp

// Argument declarations
//    logical calcN                  !<flag for nitrogen simulation
//    logical calcP                  !<flag for phosphorus simulation
//    float commoplant_uptk_NO3N[2][2]      !<plant uptake (kg/km2/d), (N:P,sl1:sl2) [numsubstances(2)][maxsoillayers(2)]
//    float wp[maxsoillayers]        !<water content at wilting point (mm)
//    float thickness[maxsoillayers] !<thickness of soil layers
//    float soil[maxsoillayers]      !<soil moisture (mm)
//    float conc(numsubstances,maxsoillayers)  !<concentration in soil moisture (mg/L etc)
//    float sink(numsubstances)      !<sink of nutrients in this subroutine (kg/km2)

// Local variables
    float maxpooluptake[maxsoillayers];
    float tmpfcn[maxsoillayers];
    float smfcn[maxsoillayers]; // sm[maxsoillayers],
    float excess_pltup, plant_uptk_mWQ;

    plant_uptk_mWQ = 0.0f;
    excess_pltup = 0.0f;

    for(long kk = 0; kk < numsubstances; ++kk)
      sink_lay[kk][hh] = 0.0;

    for(long kk = 0; kk < maxsoillayers; ++kk){
      plant_uptk_NO3N_mWQ_lay[kk][hh] = 0.0f;
      plant_uptk_NH4N_mWQ_lay[kk][hh] = 0.0f;
      plant_uptk_SRP_mWQ_lay[kk][hh] = 0.0f;
    }
    
  // Temperature dependence factor
      for (long k = 0; k < maxsoillayers; ++k)
        if(water_lay[k][hh] > 0.0){
          tmpfcn[k] = tempfactor(Temp_lay[0][hh]); // requires soil temperature
        }

  // Soil moisture dependence factor

      smfcn[0] = moisturefactor(water_lay[0][hh]/watermax_lay[0][hh],
              wp_lay[0][hh], 
              satact, thetapow, thetalow, thetaupp);
      smfcn[1] = moisturefactor(water_lay[1][hh]/watermax_lay[1][hh], 
              wp_lay[1][hh], 
              satact, thetapow, thetalow, thetaupp);

    if(calcN[hh]){
      NO3_Npool_lay[0][hh] = conc_soil_rechr_lay[i_no3n][hh] * water_lay[0][hh]; // soil_lay[soillayer][hru] and conc_lay[substance][soillayer]
      NH4_Npool_lay[0][hh] = conc_soil_rechr_lay[i_nh4n][hh] * water_lay[0][hh];
      NO3_Npool_lay[1][hh] = conc_soil_lower_lay[i_no3n][hh] * water_lay[1][hh];
      NH4_Npool_lay[1][hh] = conc_soil_lower_lay[i_nh4n][hh] * water_lay[1][hh];
    }

    if(calcP[hh]){
      SRPpool_lay[0][hh] = conc_soil_rechr_lay[i_srp][hh] * water_lay[0][hh];
      SRPpool_lay[1][hh] = conc_soil_lower_lay[i_srp][hh] * water_lay[1][hh];
    }

    maxpooluptake[0] = 0.0;
    maxpooluptake[1] = 0.0;

    if(water_lay[0][hh] > wp_mm_lay[0][hh])
      maxpooluptake[0] = (water_lay[0][hh] - wp_mm_lay[0][hh])/water_lay[0][hh]; // Maximum uptake dependent on soil moisture
    if(water_lay[1][hh] > 0.0 && water_lay[1][hh] > wp_mm_lay[1][hh])
      maxpooluptake[1] = (water_lay[1][hh] - wp_mm_lay[1][hh])/water_lay[1][hh];

// Calculate plant nutrient uptake (removed from surfsoil layer)

    if(calcN[hh]){
      // for NO3
      plant_uptk_mWQ = std::fmin(plant_uptk_NO3N_lay[0][hh]* tmpfcn[0] * smfcn[0] * hru_area[hh], 
                    maxpooluptake[0]*(surfsoil_solub_mWQ_lay[i_no3n][hh] + NO3_Npool_lay[0][hh]));
      if (plant_uptk_mWQ <= surfsoil_solub_mWQ_lay[i_no3n][hh]){
        surfsoil_solub_mWQ_lay[i_no3n][hh] -= plant_uptk_mWQ;
        excess_pltup = 0.0f;
      }else{
        excess_pltup = plant_uptk_mWQ - surfsoil_solub_mWQ_lay[i_no3n][hh];
        surfsoil_solub_mWQ_lay[i_no3n][hh] = 0.0f;
        NO3_Npool_lay[0][hh] -= excess_pltup;
      }

      
      //if(water_lay[1][hh] > 0.0)
      //  plant_uptk_NO3N_mWQ[1] = min<float>(plant_uptk_NO3N_lay[1][hh]* tmpfcn[0] * smfcn[0], maxpooluptake[1]*NO3_Npool_lay[1][hh]);

      //if(water_lay[1][hh] > 0.0)
      //   retention_pool(2, hh, NO3_Npool_lay, plant_uptk_NO3N_mWQ); // uptake may change in retention_pool ?
      //else
      //   retention_pool(1, hh, NO3_Npool_lay, plant_uptk_NO3N_mWQ); // uptake may change in retention_pool ?

      plant_uptk_NO3N_mWQ_lay[0][hh] = plant_uptk_mWQ - excess_pltup;
      plant_uptk_NO3N_mWQ_lay[1][hh] = excess_pltup;

      // for NH4
      plant_uptk_mWQ = min <float>(plant_uptk_NH4N_lay[0][hh]* tmpfcn[0] * smfcn[0] * hru_area[hh], 
                    maxpooluptake[0]*(surfsoil_solub_mWQ_lay[i_nh4n][hh] + NH4_Npool_lay[0][hh]));
      if (plant_uptk_mWQ <= surfsoil_solub_mWQ_lay[i_nh4n][hh]){
        surfsoil_solub_mWQ_lay[i_nh4n][hh] -= plant_uptk_mWQ;
        excess_pltup = 0.0f;
      }else{
        excess_pltup = plant_uptk_mWQ - surfsoil_solub_mWQ_lay[i_nh4n][hh];
        surfsoil_solub_mWQ_lay[i_no3n][hh] = 0.0f;
        NH4_Npool_lay[0][hh] -= excess_pltup;
      }

      //plant_uptk_NH4N_mWQ[0] = min <float>(plant_uptk_NH4N_lay[0][hh]* tmpfcn[0] * smfcn[0], maxpooluptake[0]*NH4_Npool_lay[0][hh]);
      //if(water_lay[1][hh] > 0.0)
      //  plant_uptk_NH4N_mWQ[1] = min<float>(plant_uptk_NH4N_lay[1][hh]* tmpfcn[0] * smfcn[0], maxpooluptake[1]*NH4_Npool_lay[1][hh]);

      //if(water_lay[1][hh] > 0.0)
      //   retention_pool(2, hh, NH4_Npool_lay, plant_uptk_NH4N_mWQ); // uptake may change in retention_pool ?
      //else
      //   retention_pool(1, hh, NH4_Npool_lay, plant_uptk_NH4N_mWQ); // uptake may change in retention_pool ?

      plant_uptk_NH4N_mWQ_lay[0][hh] = plant_uptk_mWQ - excess_pltup;
      plant_uptk_NH4N_mWQ_lay[1][hh] = excess_pltup;
    }

    if(calcP[hh]){
      plant_uptk_mWQ = min <float>(plant_uptk_SRP_lay[0][hh]* tmpfcn[0] * smfcn[0] * hru_area[hh], 
                    maxpooluptake[0]*(surfsoil_solub_mWQ_lay[i_srp][hh] + SRPpool_lay[0][hh]));
      if (plant_uptk_mWQ <= surfsoil_solub_mWQ_lay[i_srp][hh]){
        surfsoil_solub_mWQ_lay[i_srp][hh] -= plant_uptk_mWQ;
        excess_pltup = 0.0f;
      }else{
        excess_pltup = plant_uptk_mWQ - surfsoil_solub_mWQ_lay[i_srp][hh];
        surfsoil_solub_mWQ_lay[i_srp][hh] = 0.0f;
        SRPpool_lay[0][hh] -= excess_pltup;
      }

      //plant_uptk_SRP_mWQ[0] = min<float>(plant_uptk_SRP_lay[0][hh]* tmpfcn[0] * smfcn[0], maxpooluptake[0]*SRPpool_lay[0][hh]); // ??? matrix multiplication
      //if(water_lay[1][hh] > 0.0)
      //  plant_uptk_SRP_mWQ[1] = min<float>(plant_uptk_SRP_lay[1][hh]* tmpfcn[0] * smfcn[0], maxpooluptake[1]*SRPpool_lay[1][hh]); // ??? matrix multiplication

      //if(water_lay[1][hh] > 0.0)
      //   retention_pool(2, hh, SRPpool_lay, plant_uptk_SRP_mWQ);
      //else
      //   retention_pool(1, hh, SRPpool_lay, plant_uptk_SRP_mWQ);

      plant_uptk_SRP_mWQ_lay[0][hh] = plant_uptk_mWQ - excess_pltup;
      plant_uptk_SRP_mWQ_lay[1][hh] = excess_pltup;
    }

// Sum up the sinks (kg/km2)

    if(calcN[hh]){
      sink_lay[i_no3n][hh] =  plant_uptk_NO3N_mWQ_lay[0][hh] + plant_uptk_NO3N_mWQ_lay[1][hh];
      sink_lay[i_nh4n][hh] = plant_uptk_NH4N_mWQ_lay[0][hh] + plant_uptk_NH4N_mWQ_lay[1][hh];
    }

    if(calcP[hh]){
      sink_lay[i_srp][hh] = plant_uptk_SRP_mWQ_lay[0][hh] + plant_uptk_SRP_mWQ_lay[1][hh];
    }

// Calculate the new soil concentrations

    if(calcN[hh]){
       new_concentration(NO3_Npool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_no3n][hh]);
       new_concentration(NH4_Npool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_nh4n][hh]);
      if(water_lay[1][hh] > 0.0){
        new_concentration(NO3_Npool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_no3n][hh]);
        new_concentration(NH4_Npool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_nh4n][hh]);
      }else{
        conc_soil_lower_lay[i_no3n][hh] = 0.0f;
        conc_soil_lower_lay[i_nh4n][hh] = 0.0f;
      }
    }

    if(calcP[hh]){
       new_concentration(SRPpool_lay[0][hh], water_lay[0][hh], &conc_soil_rechr_lay[i_srp][hh]);
      if(water_lay[1][hh] > 0.0)
        new_concentration(SRPpool_lay[1][hh], water_lay[1][hh], &conc_soil_lower_lay[i_srp][hh]);
      else
       conc_soil_lower_lay[i_srp][hh] = 0.0f;
    }
  }  // plant_uptake


// Calculate retention in soil due to denitritfication
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Soil processes - Denitrification)
// ----------------------------------------------------------------------

  void  ClassWQ_SoilBGC::soil_denitrification(const long soil_layer){

// only handles two layers
//    float maxwc                 <Maximum water content of soil (mm)
//    float pardenN               <model parameter denitrification in soil
//    float soil                  <soil water (mm) using water_lay
//    float stemp                 <soil temperature (degree Celcius) !!! using temperature
//    long numsubstances          <concentration of soil water
//    float sink(numsubstances)   <sink of nutrient in this subroutine (kg/km2)

// Local variables
    float denitr[2]; //Manishankar did this to solve the problem of stack buffer overflow error. Previously this declaration was "float denitr[1]". I have just made this "float denitr[2]"
    float denitr_surfsoil;
    float smfcn, concfcn ;
    float tmpfcn = 0.0;
    float soil_max[2];

	

    // Substance modelled
    for(long kk = 0; kk < numsubstances; ++kk)
      sink_lay[kk][hh] = 0.0;

	
    if(soil_layer == 0){
      NO3_Npool_lay[soil_layer][hh] = conc_soil_rechr_lay[0][hh] * water_lay[soil_layer][hh]; // Initial IN pool. conc_lay[substances][layers]
      soil_max[0] = soil_rechr_max[hh]; // layer 1
    }
    else {
      NO3_Npool_lay[soil_layer][hh] = conc_soil_lower_lay[0][hh] * water_lay[soil_layer][hh]; // Initial IN pool. conc_lay[substances][layers]
      soil_max[1] = soil_moist_max[hh] - soil_rechr_max[hh]; // layer 2
    }

	
// Dependence factors of denitrification
    tmpfcn = tempfactor(Temp_lay[0][hh]);
    smfcn = exponential_moisturefactor(water_lay[soil_layer][hh], soil_max[soil_layer], smfdenitlim, smfdenitpow);
	
    if(soil_layer == 0)
      concfcn = halfsatconcfactor(conc_soil_rechr_lay[0][hh], halfsatINsoil);
	else
	{
	  concfcn = halfsatconcfactor(conc_soil_lower_lay[0][hh], halfsatINsoil);
	}

	

// Denitrification
    if(soil_layer == 0){ // surfsoil considered part of top soil layer
      denitr_surfsoil = pardenN[hh] * surfsoil_solub_mWQ_lay[i_no3n][hh] * tmpfcn * smfcn * concfcn;
      surfsoil_solub_mWQ_lay[i_no3n][hh] -= denitr_surfsoil;
      denitrification_surfsoil[hh] = denitr_surfsoil;
    }

	
	
    denitr[soil_layer] = pardenN[hh] * NO3_Npool_lay[soil_layer][hh] * tmpfcn * smfcn * concfcn;	 
	retention_pool(1, hh, NO3_Npool_lay, denitr); // denitr may change in retention_pool and NO3_Npool	
	
// Set the sink (kg/km2)
    sink_lay[soil_layer][hh] = denitr[0];

// Calculate the new soil concentrations
    if(soil_layer == 0)
     new_concentration(NO3_Npool_lay[soil_layer][hh], water_lay[soil_layer][hh], &conc_soil_rechr_lay[0][hh]);
    else
	{
     new_concentration(NO3_Npool_lay[soil_layer][hh], water_lay[soil_layer][hh], &conc_soil_lower_lay[0][hh]);
	}

	

  } // soil_denitrification

//---------------------------------------------------------------
// Calculates a temperature factor
// Based on: Q10=2,reference rate is at 20 degrees and with
// thresholds at 0 and 5 degrees (from COUP-model).
//
// temperature Current temperature
// --------------------------------------------------------------
float ClassWQ_SoilBGC::tempfactor(float temperature){

// Local variables
    float fcn;

     if(temperature < 0.0)
       return 0.0;

    fcn = pow(2.0, (temperature - 20.0)/ 10.0);
    if(temperature < 5.0)
      fcn = fcn*temperature/5.0;

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
  float ClassWQ_SoilBGC::moisturefactor(float sm, float wp, float satsmf, float thetapow, float thetalow, float thetaupp){
/*
    float  sm     !soil moisture fraction w.r.t soil_moist_max
    float  wp     !wilting point pore wolume w.r.t soil_moist_max
    float  pw     !total pore wolume w.r.t soil_moist_max
    float  thickm !thickness of soil layer (m)
    float  satsmf !saturated moisturefactor (satact)
    float  exp    !exponent of moisturefactor (thetapow)
    float  thetalow !low(?) moisture coefficient (thetalow)
    float  thetaupp !high(?) moisture coefficient (thetaupp)
*/
// Local variables
    float smfcn;     // soil moisture dependence factor

// Caclulate soilmoisture function value
    if(sm >= 1)
       smfcn = satsmf;
    else if(sm <= wp)
       smfcn=0.0;
    else{
     smfcn = std::fmin(1.0, std::fmin(
             (1-satsmf)*pow((1-sm)/thetaupp, thetapow) + satsmf,
             pow((sm-wp)/thetalow, thetapow))); 
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
  void ClassWQ_SoilBGC::soil_carbon_processes(){
/*
    USE MODVAR, ONLY : maxsoillayers

    float  klh      !<transformation parameter
    float  klo      !<rate of transformation
    float  kho      !<rate of transformation
    float  kof      !<rate of transformation
    float  koflim   !<threshold for transformation
    float  minc     !<fraction mineralisation to DIC (-)
    float  soimf    !<saturation soilmoisture factor (-)
    float  soimr    !<rate soilmoisture factor (-)
    float  soilstate   !<Soil states
*/
// Calculate the nutrient processes

    soil_carbon_pool_transformations();

  } // end soil_carbon_processes

// Subroutine for organic carbon transformation between pools in the soil
// Reference ModelDescription Chapter Organic carbon (Soil processes)
// --------------------------------------------------------------------
  void ClassWQ_SoilBGC::soil_carbon_pool_transformations(){
/*
    USE MODVAR, ONLY : maxsoillayers,i_oc
    USE HYPEVARIABLES, ONLY :   &
         thetapow,thetalow,thetaupp

    !Argument declaration
    float wp(maxsoillayers)        !<water content at wilting point (mm)
    float fc(maxsoillayers)        !<water content at field capacity (mm)
    float pw(maxsoillayers)        !<water content: total porosity (mm)
    float thickness(maxsoillayers) !<thickness of soil layers
    float klh                      !<transformation rate of labileC to refractoryC (d-1)
    float klo                      !<degradation labileC (d-1)
    float kho                      !<degradation refractoryC (d-1)
    float kof                      !<transformation to labileC (d-1)
    float koflim                   !<threshold for transformation to labileC (-)
    float minc                     !<fraction mineralisation to DIC (-)
    float soimf                    !<satuaration soilmoisture factor (-)
    float soimr                    !<rate soilmoisture factor (-)
    float soilstate                !<Soil states
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

    DOCpool[0] = water_lay[0][hh] * conc_soil_rechr_lay[i_oc][hh];    // soilstate%water(:,j,i) * soilstate%conc(i_oc,:,j,i)
    DOCpool[1] = water_lay[1][hh] * conc_soil_lower_lay[i_oc][hh]; // soilstate%water(:,j,i) * soilstate%conc(i_oc,:,j,i)

    fracprod = 1.0 - minc[hh];    // fraction of degradationn that is not mineralised

    // Temperature dependence factor
    for(long kk = 0; kk < maxsoillayers; ++kk)
      if(water_lay[kk][hh] > 0.0){
        tmpfcn[kk] = tempfactor(Temp_lay[kk][hh]);
    }

    // Soil moisture dependence factor

    smfcn[0] = moisturefactor(water_lay[0][hh]/watermax_lay[0][hh], 
            wp_lay[0][hh], 
            soimf[hh], thetapow, soimr[hh], thetaupp);
    smfcn[1] = moisturefactor(water_lay[1][hh]/watermax_lay[1][hh], 
            wp_lay[1][hh], 
            soimf[hh], thetapow, 
            soimr[hh], thetaupp);

    // Transformation between labileC and refractoryC

    for(long kk = 0; kk < maxsoillayers; ++kk)
      fasttorefractory[kk] = 0.0;

    if(water_lay[1][hh] > 0.0){
      for(long k = 0; k < 2; ++k){
        fasttorefractory[k] = klh[hh] * tmpfcn[k] * smfcn[k] * labileC_lay[k][hh];
        retention_pool(maxsoillayers, hh, labileC_lay, fasttorefractory); // fasttorefractory may change in retention_pool ::: (2,soilstate%labileC(1:2,j,i),fasttorefractory(1:2))
        production_pool(maxsoillayers, &refractoryC_lay[1][hh], fracprod*fasttorefractory[1]); // ::: (2,soilstate%refractoryC(1:2,j,i),fracprod*fasttorefractory(1:2))
      }
    }
    else{
      fasttorefractory[0] = klh[hh] * tmpfcn[0] * smfcn[0] * labileC_lay[0][hh];
      retention_pool(maxsoillayers, hh, labileC_lay, fasttorefractory); // fasttorefractory may change in retention_pool ::: (1,soilstate%labileC(1,j,i),fasttorefractory(1))
      real1temp[0] = fracprod*fasttorefractory[0];
      production_pool(maxsoillayers, hh, refractoryC_lay, real1temp); // ::: (1,soilstate%refractoryC(1,j,i),real1temp(1))-OK
    } //

    // Transformation of DOC to labileC

    for(long k = 0; k < maxsoillayers; ++k)
      doctofast[k] = 0.0;

    for(long k = 0; k < maxsoillayers; ++k)
      if(k == 0)
        if(water_lay[k][hh] > 0.0 && smfcn[k] < koflim[hh] && water_lay[k][hh] < soil_rechr[hh] && Temp_lay[k][hh] < 5.0)
          doctofast[k] = kof[hh]*DOCpool[k];
      else
        if(water_lay[k][hh] > 0.0 && smfcn[k] < koflim[hh] && water_lay[k][hh] < soil_moist[hh] && Temp_lay[k][hh] < 5.0)
          doctofast[k] = kof[hh]*DOCpool[k];

    if(water_lay[1][hh] > 0){
       // retention_pool(maxsoillayers, DOCpool, doctofast); // doctofast may change in retention_pool ::: 2,DOCpool(1:2),doctofast(1:2))
       production_pool(maxsoillayers, labileC_lay[1][hh], fracprod*doctofast[1]);
    }
    else{
       // retention_pool(maxsoillayers, DOCpool, doctofast); // doctofast may change in retention_pool
       real1temp[0] = fracprod*doctofast[0];
       production_pool(2, labileC_lay[0][hh], real1temp[0]);
    } //

    // Transformation of labileC to DOC

    for(long k = 0; k < maxsoillayers; ++k)
      transfC[k] = 0.0;
    if(water_lay[1][hh] > 0.0){
      transfC[1] = klo[hh] * tmpfcn[1] * smfcn[1] * labileC_lay[1][hh]; // ::: transfC(1:2) = klo * tmpfcn(1:2) * smfcn(1:2) * soilstate%labileC(1:2,j,i)
      retention_pool(maxsoillayers, hh, labileC_lay, transfC); // transfC may change in retention_pool
      production_pool(maxsoillayers, DOCpool[1], fracprod*transfC[1]);
    }
    else{
      transfC[0] = klo[hh] * tmpfcn[0] * smfcn[0] * labileC[0];
      retention_pool(maxsoillayers, hh, labileC_lay, transfC); // transfC may change in retention_pool
      real1temp[0]=fracprod*transfC[0];
      production_pool(maxsoillayers, DOCpool[0], real1temp[0]);
    } // 

    // Transformation of refractoryC to DOC
    for(long k = 0; k < maxsoillayers; ++k)
      transhC[k] = 0.0;
    if(water_lay[1][hh] > 0.0){
      transhC[1] = kho[hh] * tmpfcn[1] * smfcn[1] * refractoryC[1];
      retention_pool(maxsoillayers, hh, refractoryC_lay, transhC); // transhC may change in retention_pool
      production_pool(2, DOCpool[1], fracprod*transhC[1]);
    }
    else{
      transhC[0] = kho[hh] * tmpfcn[0] * smfcn[0] * refractoryC_lay[0][hh];
      retention_pool(maxsoillayers, hh, refractoryC_lay, transhC);     // transhC may change in retention_pool
      real1temp[0] = fracprod*transhC[0];
      production_pool(2, DOCpool[0], real1temp[0]);
    } //

    // Calculate the new soil concentrations of DOC
     new_concentration(DOCpool[0], water_lay[0][hh], &conc_soil_rechr_lay[i_oc][hh]);
    if(water_lay[1][hh] > 0.0)
      new_concentration(DOCpool[1], water_lay[1][hh], &conc_soil_lower_lay[i_oc][hh]);

  } // END SUBROUTINE soil_carbon_pool_transformations

// Subroutine add an amount of substance to a water body and recalculate the concentration
// ----------------------------------------------------------------
  void ClassWQ_SoilBGC::add_source_to_water(const float vol, const long n, float *conc, const float source){

// float vol        !<water body (mm)
// long n           !<numsubstance = size of conc-array
// float conc(n)    !<conc of water body (mg/l)
// float source(n)  !<amount to be added (kg/km2)

    if(vol > 0.0)
       *conc = (*conc*vol + source)/ vol;

  }  // add_source_to_water

// Subroutine add an amount of substance to a water body and recalculate the concentration
// ----------------------------------------------------------------
  void ClassWQ_SoilBGC::add_source_to_water(const float vol, long n, float conc, float source){

// float vol        !<water body (mm)
// long  n          !<numsubstance = size of conc-array
// float conc(n)    !<conc of water body (mg/l)
// float source(n)  !<amount to be added (kg/km2)

    if(vol > 0.0)
       conc = (conc*vol + source)/ vol;

  }  // add_source_to_water


// -----------------------------------------------------------------------------
// Calculates an exponential soil moisture dependence factor
  //
  //  @param[in] sm     Soil moisture (mm)
  //  @param[in] pw     Total pore wolume (mm)
  //  @param[in] limpar Limitation parameter of moisturefactor (mm) (smfdenitlim)
  //  @param[in] exp    Exponent of moisturefactor (smfdenitpow)
// -----------------------------------------------------------------------------

    float ClassWQ_SoilBGC::exponential_moisturefactor(const float sm, const float pw, const float limpar, const float exp){

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
  float ClassWQ_SoilBGC::halfsatconcfactor(const float conc, const float par){

//  Local variables
    float fcn;

    fcn = conc / (conc + par);
    return  fcn;

  } // halfsatconcfactor

void ClassWQ_SoilBGC::retention_pool(long n, long hh, float **pool, float *sink){

// long n        !<number of soillayers = size of pool-array
// float pool(n) !<soil pool array
// float sink(n) !<amount to be removed

  float a;
  for(long k = 0; k < n; ++k){ // layers
    a = pool[k][hh] - sink[k];
    if(a >= 0.0)
      pool[k][hh] = a;
    else{
      sink[k] = pool[k][hh];
      pool[k][hh] = 0.0;
    }
  }
} // retention_pool

void ClassWQ_SoilBGC::retention_pool(long n, float *pool, float *sink){

// long n        !<number of soillayers = size of pool-array
// float pool(n) !<soil pool array
// float sink(n) !<amount to be removed

  float a;
  for(long k = 0; k < n; ++k){ // layers
    a = pool[k] - sink[k];
    if(a >= 0.0)
      pool[k] = a;
    else{
      sink[k] = pool[k];
      pool[k] = 0.0;
    }
  }
} // retention_pool

void ClassWQ_SoilBGC::retention_pool(float &pool, float &sink){

  float a = pool - sink;
    if(a >= 0.0)
      pool = a;
    else{
      sink = pool;
      pool = 0.0f;
    }

}

  void ClassWQ_SoilBGC::production_pool(long n, long hh, float **pool, const float source[][2]){

//    long n           // <number of soillayers = size of pool-array
//    float pool(n)   // <soil pool array (kg/km2) or (mg/m2)
//    float source(n) // <amount to be added (kg/km2) or (mg/m2)

    for(long kk = 0; kk < maxsoillayers; ++kk)
      pool[kk][hh] = pool[kk][hh] + source[kk][n];

  }  // production_pool 

  void ClassWQ_SoilBGC::production_pool(long n, long hh, float **pool, const float *source){

//    long n           // <number of soillayers = size of pool-array
//    float pool(n)   // <soil pool array (kg/km2) or (mg/m2)
//    float source(n) // <amount to be added (kg/km2) or (mg/m2)

    for(long kk = 0; kk < n; ++kk)
      pool[kk][hh] = pool[kk][hh] + source[kk];

  }  // production_pool 

  void ClassWQ_SoilBGC::production_pool(long n, float *pool, const float source){

//    long n          // <number of soillayers = size of pool-array
//    float pool(n)   // <soil pool array (kg/km2) or (mg/m2)
//    float source(n) // <amount to be added (kg/km2) or (mg/m2)

    for(long kk = 0; kk < n; ++kk)  // layers
      pool[kk] = pool[kk] + source;

  }  // production_pool 

  void ClassWQ_SoilBGC::production_pool(long n, float pool, const float source){

//    long n          // <number of soillayers = size of pool-array
//    float pool(n)   // <soil pool array (kg/km2) or (mg/m2)
//    float source(n) // <amount to be added (kg/km2) or (mg/m2)

      pool = pool + source;

  }  // production_pool 

// Calculates concentration based on water volume and amount of one substance
// ---------------------------------------------------------------------
      void ClassWQ_SoilBGC::new_concentration(const float pool, const float vol, float *conc){ // return by reference

//    float pool !<amount          (kg/km2) or (mg/m2)
//    float vol  !<volume          (mm)
//    float conc !<concentation    (mg/L)

    if(vol > 0.0)
      *conc = pool / vol;
    else
      *conc = 0.0;

  }  // new_concentration

// Calculates concentration based on water volume and amount of one substance
// ---------------------------------------------------------------------

float ClassWQ_SoilBGC::SUM(float X[maxsoillayers][2], long part){

  float sum = 0.0;
  for(long ii = 0; ii < maxsoillayers; ++ii)
    sum += X[ii][part];

  return sum;
}

float ClassWQ_SoilBGC::SUM(float *X){
  float sum = 0.0;
  for(long ii = 0; ii < maxsoillayers; ++ii)
    sum += X[ii];

  return sum;
}


// **********
// Erosion of soil phosphorus with fast flow, surface flow and
// macropore flow. Also including delay in temporary storage. The
// eroded P is transported as PP by all runoff flows. Both partP and refractoryP
// contribute to eroded P.
//
// Reference Model Description Chapter Nitrogen and phosphorus in land routines (Vegetation
// and soil surface processes - Erosion calculations)

void ClassWQ_SoilBGC::runoff_pp_by_erosion(){

/*
    USE MODVAR, ONLY : soilthick, basin, genpar, landpar, soilpar
    USE HYPEVARIABLES, ONLY : m_soilcoh,m_soilerod,m_sreroexp, m_filtPbuf,m_filtPinner,m_filtPother, m_pprelmax,m_pprelexp


    int, INTENT(IN) :: isoil     // index of soil type
    int, INTENT(IN) :: iluse     // index of landuse
    float, INTENT(IN)    :: prec      // precipitation (rainfall only)
    float, INTENT(IN)    :: runoff   // surface runoff (mm/timestep)
    float, INTENT(IN)    :: totflow     // total runoff (runoff, tilerunoff, soilrunoff layer 1-3)
    float, INTENT(INOUT) :: soil_runoff_cWQ_lay    // PP concentration surface runoff (mg/L)
    float, INTENT(INOUT) :: csoil1      // PP concentration soil runoff layer 1 (mg/L)
    float, INTENT(INOUT) :: csoil2      // PP concentration soil runoff layer 2 (mg/L)
    TYPE(snowicestatetype),INTENT(INOUT)  :: frozenstate   // Snow and ice states
    TYPE(soilstatetype),INTENT(INOUT)  :: soilstate   // Soil states
*/
// Local variables
    float PPrel;         // PP released from delay pool
    float srfilt;        // total filtration of surface runoff PP
    float erodingflow;   // Flow eroding the surface
    float erodedP;       // total eroded PP (kg/km2)
    float fracminP;      // fraction of erodedP in mineral form (from partP)
    float removePP[1];   // actually lost PP (kg/km2) [1][2]
    float removeHP[1];   // actually lost refractoryP (kg/km2) [1][2]
    float surfrppmass;   // variables to temporary hold PP-konc of macropores and runoff
    float newppconc;     // PP concentration for PP released from delay pool

    PPrel = 0.0f;
    srfilt = 0.0f;
    erodingflow = 0.0f;
    erodedP = 0.0f;
    fracminP = 0.0f;
    //removePP[1] = 0.0f;
    //removeHP[1] = 0.0f;
    surfrppmass = 0.0f;
    newppconc = 0.0f;
    soil_runoff_cWQ_lay[i_pp][hh] = 0.0f; // reset

// Calculate PP erosion

    calculate_erosion(erodedP); // calculate mobilised PP at soil surface  !!! fix

    erodingflow = soil_runoff[hh]; // check
    calculate_transport(erodingflow, erodedP);   // calculate amount of PP transported in fast flow paths  (kg/km2)

    if(soil_runoff[hh] > minFlow_WQ) { // erodedP goes back to soil if no surface runoff

// Calculate resulting PP concentration of surface runoff

      //srfilt = filtPother + closewater[hh] * (1.0 + buffer[hh] * filtPbuf - 1.0) + filtPinner * (1.0 - closewater[hh]);
      srfilt = 1;
      surfrppmass = srfilt * erodedP / erodingflow;

// Remove eroded P from soil

      removePP[0] = soil_runoff[hh]*surfrppmass*fracminP;     // kg/km2
      removeHP[0] = soil_runoff[hh]*surfrppmass*(1-fracminP); // kg/km2
      retention_pool(surfsoil_solub_mWQ_lay[i_pp][hh], removePP[0]);
      retention_pool(surfsoil_refractoryP_mWQ[hh], removeHP[0]);

// Add PP of tile drainage and surface flow to temporary PP pool

      PPrelpool[hh] = removePP[0] + removeHP[0];   // add sources

// Calculate release from temporary PP pool and new concentrations of the flows;

      PPrel = std::fmin(PPrelpool[hh], PPrelpool[hh]* soil_runoff[hh]/ pow(pprelmax, pprelexp)); // export
      PPrelpool[hh] = PPrelpool[hh] - PPrel;
      newppconc = PPrel / soil_runoff[hh];
      soil_runoff_cWQ_lay[i_pp][hh] = newppconc;
      //conc_soil_rechr_lay[i_pp][hh] += newppconc;
      //conc_soil_lower_lay[1][hh] += newppconc;
    }
  } // runoff_pp_by_erosion

void ClassWQ_SoilBGC::calculate_erosion(float& erodedP){
/*  from "npc_soil_proc.f90" called from "soilmodel0.f90" definitions in "modvar.f90"
    USE HYPEVARIABLES, ONLY : bulkdensity
    USE MODVAR, ONLY : 10,     &
         find_croppart,   &
         cropdata,                        &
         basin,           &
         pi


    float, INTENT(IN)      :: prec          // precipitation (rainfall only)
    float, INTENT(IN)      :: thickness     // upper soillayer thickness (m)
    float, INTENT(IN)      :: surfacerunoff // saturated overland flow and excess infiltration (mm)
    float, INTENT(OUT)     :: erodedP       // eroded phosphorus (kg/km2)
    float, INTENT(IN)      :: cohesion      // (kPa)
    float, INTENT(IN)      :: erodibility   // (g/J)
    float, INTENT(IN)      :: snow          // snow water (mm) i.e. snowmelt
    float, INTENT(IN)      :: sreroexp      // surface runoff erosion exponent
    float, INTENT(IN)      :: partP(maxsoillayers)       // partP pool (kg/km2)
    float, INTENT(IN)      :: refractoryP(maxsoillayers) // refractoryP pool (kg/km2)
    float, INTENT(OUT)     :: fracminP      // part[hh] of eroded P in mineral form
*/

    // Local variables
    long kcrop, k;
    float MobilisedSed, MobilisedP, Rainfall_energy, cropcover, groundcover;
    float intensity;
    float bd1, bd2, bd3, bd4, bd5;  // cultivation dates
    float common_cropcover, common_groundcover, maxday1, maxday2;

    fracminP[hh] = 0.0f;
    erodedP = 0.0f;

    common_cropcover = 0.0f;
    common_groundcover = 0.0f;
    if(cohesion == 0 || erodibility == 0)
      return;      // no parameter values -> no erosion

/*
// Calculate current cropcover and groundcover

    for(kcrop = 0; kcrop < 2; ++kcrop){
       if(k==0)
         continue;                         // no crop given
//       if(part[hh] > 0){
          bd1 = baredayno1[hh];        // spring ploughing
          bd2 = baredayno2[hh];        // sow date / beginning of growing season
          bd3 = baredayno3[hh];        // harvest
          bd4 = baredayno4[hh];        // autumn ploughing
          bd5 = baredayno5[hh];        // winter crops sowing date
          if(bd1==0  &  bd4==0) {      // year-round-crop
             cropcover = ccmax1[hh];   // during summer
             groundcover = gcmax1[hh]; // during summer
          }
          else{                                          // spring, winter and row crops
             maxday1 = float(int(bd2 + (bd3-bd2)/2.));   // day of maximum crop and ground cover in summer
             maxday2 = float(int(bd5 + (365-bd5)/2.));   // day of maximum crop and ground cover for winter crops in autumn
             if(bd5 > 0){                                // winter crop
                if(dayno < bd2){
                   cropcover   = ccmax2[hh];
                   groundcover = gcmax2[hh];
                }
                else if(dayno < maxday1){
                   cropcover   = ccmax2[hh] + (ccmax1[hh]-ccmax2[hh])*((dayno - bd2) /(maxday1 - bd2));
                   groundcover = gcmax2[hh] + (gcmax1[hh]-gcmax2[hh])*((dayno - bd2) /(maxday1 - bd2));
                }
                else if(dayno < bd3){
                   cropcover   = ccmax1[hh];
                   groundcover = gcmax1[hh];
                }
                else if(dayno < bd4){
                   cropcover   = gcmax1[hh];
                   groundcover = gcmax1[hh];
                }
                else if(dayno < bd5){
                   cropcover = 0.;
                   groundcover = 0.;
                }
                else if(dayno < maxday2){
                   cropcover   = ccmax2[hh] * ((dayno - bd5) /(maxday2 - bd5));
                   groundcover = gcmax2[hh] * ((dayno - bd5) /(maxday2 - bd5));
                }
                else{
                   cropcover   = ccmax2[hh];
                   groundcover = gcmax2[hh];
                }
             }
             else if(bd1 > 0){                          // spring crop (or row crop) with spring ploughing
                if(dayno < bd1){
                   cropcover   = gcmax1[hh];
                   groundcover = gcmax1[hh];
                }
                else if(dayno < bd2){
                   cropcover   = 0.;
                   groundcover = 0.;
                }
                else if(dayno < maxday1) {
                   cropcover   = ccmax1[hh] * ((dayno - bd2) /(maxday1 - bd2));
                   groundcover = gcmax1[hh] * ((dayno - bd2) /(maxday1 - bd2));
                }
                else if(dayno < bd3) {
                   cropcover   = ccmax1[hh];
                   groundcover = gcmax1[hh];
                }
                else{
                   cropcover   = gcmax1[hh];
                   groundcover = gcmax1[hh];
                }
             }
             else{                                         // spring crop (or row crop) with autumn ploughing
                if(dayno < bd2){
                   cropcover   = 0.;
                   groundcover = 0.;
                }
                else if(dayno < maxday1) {
                   cropcover   = ccmax1[hh] * ((dayno - bd2) /(maxday1 - bd2));
                   groundcover = gcmax1[hh] * ((dayno - bd2) /(maxday1 - bd2));
                }
                else if(dayno < bd3) {
                   cropcover   = ccmax1[hh];
                   groundcover = gcmax1[hh];
                }
                else if(dayno < bd4) {
                   cropcover   = gcmax1[hh];
                   groundcover = gcmax1[hh];
                }
                else{
                   cropcover   = 0.0;
                   groundcover = 0.0;
                }
             }
          }
          common_cropcover   = common_cropcover*cropcover; // removed 1.0 - part[hh]
          common_groundcover = common_groundcover*groundcover;
//       } // part[hh] > 0
    }
    common_cropcover   = 1.0 - common_cropcover;
    common_groundcover = 1.0 - common_groundcover;

*/

cropcover   = ccmax1[hh];
groundcover = gcmax1[hh];

// Check for snow limiting erosion

    intensity = 1.0;    // intenspar;
    if(snowmelt_int[hh] > 0.0)
      intensity = 0.0;  // snow

// Particles (and attached P) is eroded by rain splash detachment and by overland flow

    MobilisedP = 0.0;
    if(net_rain[hh] > 0.0) {
      if(intensity > 0.0) {
        if(net_rain[hh] > 5.0/Global::Freq)     // TODO: shorter timestep, other threshold?
          Rainfall_energy = 8.95+8.44*log10(net_rain[hh]*(0.257+sin(2*3.14*((dayno-70.)/365.))*0.09)*2.0);
        else
          Rainfall_energy = 0.0;

        Rainfall_energy = net_rain[hh] * Rainfall_energy;        // J/m2
        MobilisedSed = Rainfall_energy * (1.0 - common_cropcover) * erodibility[hh];  // g/m2
        MobilisedP = 1.0E-3 * MobilisedSed * ((surfsoil_solub_mWQ_lay[i_pp][hh] + surfsoil_refractoryP_mWQ[hh]) / (soil_Depth[hh] * bulkdensity));    // kgP / km2
      }
    }
    if(runoff[hh] > 0.0) {
       MobilisedSed = (((runoff[hh] * 365.0)*exp(sreroexp)) * (1.0 - common_groundcover) * (1.0/(0.5 * cohesion[hh])) * sin(hru_GSL[hh] / 100.)) / 365.0; // g/m2
       MobilisedP += 1.0E-3 * MobilisedSed * ((surfsoil_solub_mWQ_lay[i_pp][hh] + surfsoil_refractoryP_mWQ[hh]) / (soil_Depth[hh] * bulkdensity));
    }

// Set output variables

    erodedP = MobilisedP;      // kg/km2
    fracminP[hh] = surfsoil_solub_mWQ_lay[i_pp][hh] / (surfsoil_solub_mWQ_lay[i_pp][hh] + surfsoil_refractoryP_mWQ[hh]);

  } // calculate_erosion

//Calculate how much particulate P is transported with sediment
// Reference ModelDescription Chapter Nitrogen and phosphorus in land routines (Vegetation
// and soil surface processes - Erosion calculations)

  void ClassWQ_SoilBGC::calculate_transport(const float flow, float& erodedP){

//    float, INTENT(IN)    :: flow      // Fast flow
//    float, INTENT(INOUT) :: erodedP   // Mobilised P

// Local variables
    float transportfactor;
    float enrichment;

// Local parameters
    float max = 4.0;
    float stab = 1.5;
    float flowstab = 4.0;
    float trans1 = 4.0;
    float trans2 = 1.3;

// Enrichment - finer soil particles are more likely to be eroded and contain more P per weight unit

    if(flow > 0.0){
      if(flow > flowstab)
        enrichment = stab;
      else
        enrichment = max - (max-stab)* flow / flowstab;
    }
    else
      enrichment = 0.0;

// Transport capacity of fast flowing water may limit transport

    if(flow > 0.0)
      transportfactor = std::fmin(1.0, flow/pow(trans1, trans2));
    else
      transportfactor = 1.0;

    erodedP = erodedP * transportfactor * enrichment;
} // calculate_transport

