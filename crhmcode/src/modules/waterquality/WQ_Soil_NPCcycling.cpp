#pragma hdrstop
#include <cmath>
#include <stdlib.h>
#include "WQ_Soil_NPCcycling.h"
#include "../newmodules/NewModules.h"
#include "../../core/GlobalDll.h"
#include "../../core/InstrumentLogger.h"

using namespace std; using namespace CRHM; const double thetalow = 0.08;
const double thetaupp = 0.12;
const double satact = 0.6;
const double thetapow = 2;
const double bulkdensity = 1300;
const double sreroexp = 1.0;
const double filtPbuf = 1.0;
const double filtPother = 1.0;
const double filtPinner = 1.0;
const double pprelmax = 1.0;
const double pprelexp = 1.0;
const double Kfr = 1.0;
const double Nfr = 1.0;
const double Kadsdes = 1.0;
const double halfsatTPwater = 0.05;
const double maxprodwater = 0.5;
const double maxdegradwater = 0.5;
const double NPratio = 1.0 / 7.2;
const double NCratio = 5.7;
const double maxdenitriwater = 999;
const double halfsatINwater = 999;
const double soilerod = 1.0;
const double smfdenitlim = 0.1;
const double smfdenitpow = 1.0;
const double halfsatINsoil = 1.0;
const double ldprodpp = 1.0;
const double ldprodsp = 1.0;
const long i_no3n = 0;
const long i_nh4n = 1;
const long i_don = 2;
const long i_srp = 3;
const long i_dop = 4;
const long i_pp = 5;
const long i_oc = 6;
const long maxsoilayers = 3;
const double minFlow_WQ = 0.001f;

ClassWQ_SoilBGC * ClassWQ_SoilBGC :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::klone(string name) const@@@WQ_Soil_NPCcycling.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::klone(string name) const@@@WQ_Soil_NPCcycling.cpp>");
    return new ClassWQ_SoilBGC (name);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::klone(string name) const@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::decl(void)@@@WQ_Soil_NPCcycling.cpp>");
    Description = "'Soil biogeochemical cycling module.'";
    declstatvar ("partP", TDim :: NDEFN, "immobile/undissolved pool of organic phosphorus adsorded to soil particles.", "(kg/km^2)", & partP, & partP_lay, maxsoillayers);
    declstatvar ("refractoryN", TDim :: NDEFN, "immobile/undissolved pool of organic nitrogen in soil with slow turnover.", "(kg/km^2)", & refractoryN, & refractoryN_lay, maxsoillayers);
    declstatvar ("refractoryP", TDim :: NDEFN, "immobile/undissolved pool of organic phosphorus in soil with slow turnover.", "(kg/km^2)", & refractoryP, & refractoryP_lay, maxsoillayers);
    declstatvar ("refractoryC", TDim :: NDEFN, "immobile/undissolved pool of organic carbon with slow turnover.", "(kg/km^2)", & refractoryC, & refractoryC_lay, maxsoillayers);
    declstatvar ("labileN", TDim :: NDEFN, "immobile/undissolved pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", & labileN, & labileN_lay, maxsoillayers);
    declstatvar ("labileP", TDim :: NDEFN, "immobile/undissolved pool of organic phosphorus in soil with rapid turnover.", "(kg/km^2)", & labileP, & labileP_lay, maxsoillayers);
    declstatvar ("labileC", TDim :: NDEFN, "immobile/undissolved pool of organic carbon in soil with rapid turnover.", "(kg/km^2)", & labileC, & labileC_lay, maxsoillayers);
    declstatvar ("NO3_Npool", TDim :: NDEFN, "NO3-N (nitrate-nitrogen, dissolved) pool in soil", "(kg/km^2)", & NO3_Npool, & NO3_Npool_lay, maxsoillayers);
    declstatvar ("NH4_Npool", TDim :: NDEFN, "NH4-N (ammonium-nitrogen, dissolved) pool in soil", "(kg/km^2)", & NH4_Npool, & NH4_Npool_lay, maxsoillayers);
    declstatvar ("DONpool", TDim :: NDEFN, "dissolved organic nitrogen pool in soil", "(kg/km^2)", & DONpool, & DONpool_lay, maxsoillayers);
    declstatvar ("SRPpool", TDim :: NDEFN, "soluble-reactive phosphorus pool in soil", "(kg/km^2)", & SRPpool, & SRPpool_lay, maxsoillayers);
    declstatvar ("DOPpool", TDim :: NDEFN, "dissolved organic phosphorus pool in soil", "(kg/km^2)", & DOPpool, & DOPpool_lay, maxsoillayers);
    declstatvar ("PPrelpool", TDim :: NHRU, "soil PP (particulate phosphorus) released to runoff due to erosion", "(kg/int)", & PPrelpool);
    declstatvar ("plant_uptk_NO3N_mWQ", TDim :: NDEFN, "plant uptake of NO3-N expressed as mass/int", "(kg/int)", & plant_uptk_NO3N_mWQ, & plant_uptk_NO3N_mWQ_lay, maxsoillayers);
    declstatvar ("plant_uptk_NH4N_mWQ", TDim :: NDEFN, "plant uptake of NH4-N expressed as mass/int", "(kg/int)", & plant_uptk_NH4N_mWQ, & plant_uptk_NH4N_mWQ_lay, maxsoillayers);
    declstatvar ("plant_uptk_SRP_mWQ", TDim :: NDEFN, "plant uptake of SRP expressed as mass/int", "(kg/int)", & plant_uptk_SRP_mWQ, & plant_uptk_SRP_mWQ_lay, maxsoillayers);
    declvar ("water", TDim :: NDEFN, "soil moisture", "(mm)", & water, & water_lay, maxsoillayers);
    declvar ("watermax", TDim :: NDEFN, "soil moisture", "(mm)", & watermax, & watermax_lay, maxsoillayers);
    declvar ("Temp", TDim :: NDEFN, "soil layer temperature", "(" + string (DEGREE_CELSIUS) + ")", & Temp, & Temp_lay, maxsoillayers);
    declvar ("denitrification", TDim :: NDEFN, "denitrification (maxsoillayers", "(kg/int)", & denitrification, & denitrification_lay, maxsoillayers);
    declstatvar ("denitrification_surfsoil", TDim :: NHRU, "denitrification in WQ's surfsoil", "(kg/int)", & denitrification_surfsoil);
    declstatvar ("conc_soil_rechr", TDim :: NDEFN, "concentration in soil_rechr: (i_no3n=0) NO3-N, (i_nh4n=1) NH4-1, (i_don=2) DON, "
        "(i_srp=3) SRP, (i_dop=4) DOP, (i_pp=5) PP, (i_oc=6) OC", "(mg/l)", & conc_soil_rechr, & conc_soil_rechr_lay, numsubstances);
    declstatvar ("conc_soil_lower", TDim :: NDEFN, "concentration in soil_lower: (i_no3n=0) NO3-N, (i_nh4n=1) NH4-1, (i_don=2) DON, "
        "(i_srp=3) SRP, (i_dop=4) DOP, (i_pp=5) PP, (i_oc=6) OC", "(mg/l)", & conc_soil_lower, & conc_soil_lower_lay, numsubstances);
    declvar ("source", TDim :: NDEFN, "source of soil water nutrients through mineralization", "(kg/int)", & source, & source_lay, numsubstances);
    declvar ("sink", TDim :: NDEFN, "sink of nutrients in subroutine)", "(kg/km^2)", & sink, & sink_lay, numsubstances);
    declvar ("sources_plant", TDim :: NDEFN, "nutrient load from plant residues. Indexed as LAY -> substance", "(kg/int)", & sources_plant, & sources_plant_lay, numsubstances);
    declvar ("src_mineral_fertman_surfsoil", TDim :: NDEFN, "load from fertilizer to surfsoil. Indexed as LAY -> substance", "(kg/int)", & src_mineral_fertman_surfsoil, & src_mineral_fertman_surfsoil_lay, numsubstances);
    declvar ("src_mineral_fertman_soilrechr", TDim :: NDEFN, "load from fertilizer) to soil_rechr. Indexed as LAY -> substance", "(kg/int)", & src_mineral_fertman_soilrechr, & src_mineral_fertman_soilrechr_lay, numsubstances);
    declvar ("fracminP", TDim :: NHRU, "part of eroded P in mineral form", "()", & fracminP);
    declvar ("cropuptake", TDim :: NHRU, "crop uptake of nitrogen", "(kg/int)", & cropuptake);
    declvar ("surfsoil_solub_mWQ", TDim :: NDEFN, "Mass in the surficial soil layer ready for mobilization: dissolved substances", "(kg/km2)", & surfsoil_solub_mWQ, & surfsoil_solub_mWQ_lay, numsubstances);
    declvar ("surfsoil_labileN_mWQ", TDim :: NHRU, "Mass in the surficial soil layer ready for mobilization: Labile N", "(kg/km2)", & surfsoil_labileN_mWQ);
    declvar ("surfsoil_labileP_mWQ", TDim :: NHRU, "Mass in the surficial soil layer ready for mobilization: Labile P", "(kg/km2)", & surfsoil_labileP_mWQ);
    declvar ("surfsoil_refractoryN_mWQ", TDim :: NHRU, "Mass in the surficial soil layer ready for mobilization: Refractory N", "(kg/km2)", & surfsoil_refractoryN_mWQ);
    declvar ("surfsoil_refractoryP_mWQ", TDim :: NHRU, "Mass in the surficial soil layer ready for mobilization: Refractory N", "(kg/km2)", & surfsoil_refractoryP_mWQ);
    declparam ("wp", TDim :: NDEFN, "[0]", "0.05", "0.2", "normalized wilting point w.r.t. soil_rechr_max or soil_lower_max", "()", & wp, & wp_lay, maxsoillayers);
    declvar ("wp_mm", TDim :: NDEFN, "wilting point w.r.t. soil_rechr_max or soil_lower_max", "(mm)", & wp_mm, & wp_mm_lay, maxsoillayers);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("hru_GSL", TDim :: NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string (DEGREE) + ")", & hru_GSL);
    declparam ("ccmax1", TDim :: NHRU, "[0]", "0", "10", "crop cover during summer", "()", & ccmax1);
    declparam ("gcmax1", TDim :: NHRU, "[0]", "0", "10", "ground cover during summer", "()", & gcmax1);
    declparam ("erodibility", TDim :: NHRU, "[0]", "0", "100", "erodibility", "(g/J)", & erodibility);
    declparam ("cohesion", TDim :: NHRU, "[0]", "0", "100", "cohesion", "(kPa)", & cohesion);
    declparam ("pardenN", TDim :: NHRU, "[1]", "0", "100", "denitrification in soil", "(mm)", & pardenN);
    declparam ("calcN", TDim :: NHRU, "[0]", "0", "1", "flag for nitrogen simulation", "()", & calcN);
    declparam ("calcP", TDim :: NHRU, "[0]", "0", "1", "flag for phosphorus simulation", "()", & calcP);
    declparam ("calcC", TDim :: NHRU, "[0]", "0", "1", "flag for carbon simulation", "()", & calcC);
    declparam ("Inhibit_Soil_BGC", TDim :: BASIN, "[0]", "0", "1", "Bypass Hype routines", "()", & Inhibit_Soil_BGC);
    declparam ("parminfN", TDim :: NHRU, "[0]", "0", "1", "mineralisation of labileN: labileN to NH4", "(1/d)", & parminfN);
    declparam ("parnitrfN", TDim :: NHRU, "[0]", "0", "1", "nitrification: NH4 to NO3", "(1/d)", & parnitrfN);
    declparam ("parminfP", TDim :: NHRU, "[0]", "0", "1", "mineralisation of labileP: labileP to DIP", "(1/d)", & parminfP);
    declparam ("pardegrhN", TDim :: NHRU, "[0]", "0", "1", "degradation of refractoryN: refractoryN to labileN", "(1/d)", & pardegrhN);
    declparam ("pardegrhP", TDim :: NHRU, "[0]", "0", "1", "degradation refractoryP: refractoryP to labileP", "(1/d)", & pardegrhP);
    declparam ("pardisfN", TDim :: NHRU, "[0]", "0", "1", "dissolution of labileN: labileN to DON", "(1/d)", & pardisfN);
    declparam ("pardisfP", TDim :: NHRU, "[0]", "0", "1", "dissolution of labileP: labileP to DOP", "(1/d)", & pardisfP);
    declparam ("pardishN", TDim :: NHRU, "[0]", "0", "1", "dissolution of refractoryN: refractoryN to DON", "(1/d)", & pardishN);
    declparam ("pardishP", TDim :: NHRU, "[0]", "0", "1", "dissolution of refractoryP: refractoryP to DOP", "(1/d)", & pardishP);
    declparam ("klh", TDim :: NHRU, "[0]", "0", "100", "speed of transformation from litter to refractory", "(1/d)", & klh);
    declparam ("klo", TDim :: NHRU, "[0]", "0", "100", "speed of transformation from litter to DOC", "(1/d)", & klo);
    declparam ("kho", TDim :: NHRU, "[0]", "0", "100", "speed of transformation from refractory to DOC", "(1/d)", & kho);
    declparam ("kof", TDim :: NHRU, "[0]", "0", "100", "speed of transformation from DOC to labileC", "(1/d)", & kof);
    declparam ("koflim", TDim :: NHRU, "[0.5]", "0", "100", "threshold for wetness for transformation DOC to labileC", "()", & koflim);
    declparam ("minc", TDim :: NHRU, "[1]", "0", "100", "fraction mineralisation to DIC", "()", & minc);
    declparam ("soimf", TDim :: NHRU, "[1]", "0", "100", "saturation soilmoisture factor", "()", & soimf);
    declparam ("soimr", TDim :: NHRU, "[1]", "0", "100", "rate soilmoisture factor", "()", & soimr);
    declparam ("fertNamount_up", TDim :: NHRU, "[1]", "0", "1000000", "fertiliser amount1 N", "(kg/km^2)", & fertNamount_up);
    declparam ("fertNamount_down", TDim :: NHRU, "[1]", "0", "1000000", "fertiliser amount2 N", "(kg/km^2)", & fertNamount_down);
    declparam ("fertPamount_up", TDim :: NHRU, "[1]", "0", "1000000", "fertiliser amount1 P", "(kg/km^2)", & fertPamount_up);
    declparam ("fertPamount_down", TDim :: NHRU, "[1]", "0", "1000000", "fertiliser amount2 P", "(kg/km^2)", & fertPamount_down);
    declparam ("fertday_up", TDim :: NHRU, "[0]", "0", "366", "day for fertilizing 1 (dayno)", "()", & fertday_up);
    declparam ("fertday_down", TDim :: NHRU, "[0]", "0", "366", "day for fertilizing 2 (dayno)", "()", & fertday_down);
    declparam ("resday_up", TDim :: NHRU, "[0]", "0", "366", "day for residual (dayno), code 0 give residuals every day)", "()", & resday_up);
    declparam ("resday_down", TDim :: NHRU, "[0]", "0", "366", "day for residual (dayno), code 0 give residuals every day)", "()", & resday_down);
    declparam ("manday_up", TDim :: NHRU, "[0]", "0", "366", "day for manureing 1)", "()", & manday_up);
    declparam ("manday_down", TDim :: NHRU, "[0]", "0", "366", "day for manureing 2)", "()", & manday_down);
    declparam ("manNamount_up", TDim :: NHRU, "[0.0]", "0", "1000000", "manure amount1 N", "(kg/km^2)", & manNamount_up);
    declparam ("manNamount_down", TDim :: NHRU, "[0.0]", "0", "1000000", "manure amount2 N", "(kg/km^2)", & manNamount_down);
    declparam ("manPamount_up", TDim :: NHRU, "[0.0]", "0", "1000000", "manure amount1 P", "(kg/km^2)", & manPamount_up);
    declparam ("manPamount_down", TDim :: NHRU, "[0.0]", "0", "1000000", "manure amount2 P", "(kg/km^2)", & manPamount_down);
    declparam ("resNamount_up", TDim :: NHRU, "[0.0]", "0", "1000000", "residual amount of N", "(kg/km^2)", & resNamount_up);
    declparam ("resPamount_up", TDim :: NHRU, "[0.0]", "0", "1000000", "residual amount of P", "(kg/km^2)", & resPamount_up);
    declparam ("resNamount_down", TDim :: NHRU, "[0.0]", "0", "1000000", "residual amount of N", "(kg/km^2)", & resNamount_down);
    declparam ("resPamount_down", TDim :: NHRU, "[0.0]", "0", "1000000", "residual amount of P", "(kg/km^2)", & resPamount_down);
    declparam ("resCamount", TDim :: NHRU, "[0.0]", "0", "1", "litter fall of C", "(kg/km^2)", & resCamount);
    declparam ("resfast", TDim :: NHRU, "[0.0]", "0", "1", " residual amount to labileN/P pool (rest to refractoryN/P)", "(-)", & resfast);
    declparam ("fertperiod", TDim :: NHRU, "[1]", "1", "100", "days for fertilization.", "()", & fertperiod);
    declparam ("litterperiod", TDim :: NHRU, "[1]", "1", "100", "days for litterfall.", "()", & litterperiod);
    declparam ("manureinogNfrac", TDim :: NHRU, "[0.5]", "0", "1", "fraction of inorN in manure.", "(-)", & manureinogNfrac);
    declparam ("manureinogPfrac", TDim :: NHRU, "[0.5]", "0", "1", "fraction of inorN in manure.", "(-)", & manureinogPfrac);
    declparam ("fertandman_inogNfrac_NO3Nfrac", TDim :: NHRU, "[0.5]", "0", "1", "fraction of NO3-N in fraction of inorgN in fertilizer and manure.", "(-)", & fertandman_inogNfrac_NO3Nfrac);
    declparam ("fertandman_inogNfrac_NH4frac", TDim :: NHRU, "[0.5]", "0", "1", "fraction of NH4-N in fraction of inorgN in fertilizer and manure.", "(-)", & fertandman_inogNfrac_NH4Nfrac);
    declparam ("refractoryNmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with slow turnover.", "(kg/km^2)", & refractoryNmass_init, & refractoryNmass_init_lay, maxsoillayers);
    declparam ("refractoryPmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic phosphorus in soil with slow turnover.", "(kg/km^2)", & refractoryPmass_init, & refractoryPmass_init_lay, maxsoillayers);
    declparam ("refractoryCmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "refractoryC pool in soil", "(kg/km^2)", & refractoryCmass_init, & refractoryCmass_init_lay, maxsoillayers);
    declparam ("labileNmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", & labileNmass_init, & labileNmass_init_lay, maxsoillayers);
    declparam ("labilePmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic phosphorus in soil with rapid turnover.", "(kg/km^2)", & labilePmass_init, & labilePmass_init_lay, maxsoillayers);
    declparam ("labileCmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "labileC pool in soil", "(kg/km^2)", & labileCmass_init, & labileCmass_init_lay, maxsoillayers);
    declparam ("plant_uptk_NO3N", TDim :: NDEFN, "[0]", "0", "10", "plant NO3-N uptake per day.", "(kg/km^2)", & plant_uptk_NO3N, & plant_uptk_NO3N_lay, maxsoillayers);
    declparam ("plant_uptk_NH4N", TDim :: NDEFN, "[0]", "0", "10", "plant NH4-N uptake per day.", "(kg/km^2)", & plant_uptk_NH4N, & plant_uptk_NH4N_lay, maxsoillayers);
    declparam ("plant_uptk_SRP", TDim :: NDEFN, "[0]", "0", "10", "plant P uptake per day.", "(kg/km^2)", & plant_uptk_SRP, & plant_uptk_SRP_lay, maxsoillayers);
    declparam ("conc_soil_rechr_init", TDim :: NDEFN, "[0.0]", "0", "1000", "initial concentration of inorganic nitrogen in soil moisture per land-soil", "(mg/l)", & conc_soil_rechr_init, & conc_soil_rechr_init_lay, numsubstances);
    declparam ("conc_soil_lower_init", TDim :: NDEFN, "[0.0]", "0", "1000", "concentration of organic nitrogen in soil moisture per land-soil", "(mg/l)", & conc_soil_lower_init, & conc_soil_lower_init_lay, numsubstances);
    declparam ("surfsoil_massSolub_init", TDim :: NDEFN, "[0.0]", "0", "1000", "initial concentration of inorganic nitrogen in surfsoil layer", "(mg/l)", & surfsoil_massSolub_init, & surfsoil_massSolub_init_lay, numsubstances);
    declparam ("surfsoil_masslabileNmass_init", TDim :: NHRU, "[0.0]", "0", "1000000", "initial mass of labile N in the surfsoil layer", "(kg/km^2)", & surfsoil_masslabileNmass_init);
    declparam ("surfsoil_masslabilePmass_init", TDim :: NHRU, "[0.0]", "0", "1000000", "initial mass of labile P in the surfsoil layer", "(kg/km^2)", & surfsoil_masslabilePmass_init);
    declparam ("surfsoil_massrefractoryNmass_init", TDim :: NHRU, "[0.0]", "0", "1000000", "initial mass of labile N in the surfsoil layer", "(kg/km^2)", & surfsoil_massrefractoryNmass_init);
    declparam ("surfsoil_massrefractoryPmass_init", TDim :: NHRU, "[0.0]", "0", "1000000", "initial mass of labile N in the surfsoil layer", "(kg/km^2)", & surfsoil_massrefractoryPmass_init);
    declparam ("labileNmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", & labileNmass_init, & labileNmass_init_lay, maxsoillayers);
    declparam ("labileNmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", & labileNmass_init, & labileNmass_init_lay, maxsoillayers);
    declparam ("labileNmass_init", TDim :: NDEFN, "[0.0]", "0", "1000000", "immobile pool of organic nitrogen in soil with rapid turnover.", "(kg/km^2)", & labileNmass_init, & labileNmass_init_lay, maxsoillayers);
    declgetvar ("*", "hru_t", "(" + string (DEGREE_CELSIUS) + ")", & hru_t);
    declgetvar ("*", "snowmelt_int", "(mm/int)", & snowmelt_int);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "net_rain", "(mm)", & net_rain);
    declgetvar ("*", "runoff", "(mm)", & runoff);
    declgetvar ("*", "soil_runoff", "(mm)", & soil_runoff);
    declputvar ("*", "soil_runoff_cWQ", "(mm)", & soil_runoff_cWQ, & soil_runoff_cWQ_lay);
    declputvar ("*", "SWE_conc", "(mg/l)", & SWE_conc, & SWE_conc_lay);
    declparam ("soil_Depth", TDim :: NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", & soil_Depth);
    declgetvar ("*", "soil_moist", "(mm)", & soil_moist);
    declgetvar ("*", "soil_rechr", "(mm)", & soil_rechr);
    declgetparam ("*", "soil_moist_max", "(mm)", & soil_moist_max);
    declgetparam ("*", "soil_rechr_max", "(mm)", & soil_rechr_max);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::decl(void)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::init(void)@@@WQ_Soil_NPCcycling.cpp>");
    nhru = getdim (TDim :: NHRU);
    nlay = getdim (TDim :: NLAY);
    for (hh = 0; hh < nhru; ++ hh) {
        fracminP [hh] = 0.0;
        cropuptake [hh] = 0.0;
        surfsoil_labileN_mWQ [hh] = surfsoil_masslabileNmass_init [hh] * hru_area [hh];
        surfsoil_labileP_mWQ [hh] = surfsoil_masslabilePmass_init [hh] * hru_area [hh];
        ;
        surfsoil_refractoryN_mWQ [hh] = surfsoil_massrefractoryNmass_init [hh] * hru_area [hh];
        ;
        surfsoil_refractoryP_mWQ [hh] = surfsoil_massrefractoryPmass_init [hh] * hru_area [hh];
        ;
        denitrification_surfsoil [hh] = 0.0;
        for (long ll = 0; ll < maxsoillayers; ++ ll) {
            refractoryN_lay [ll] [hh] = refractoryNmass_init_lay [ll] [hh] * hru_area [hh];
            refractoryP_lay [ll] [hh] = refractoryPmass_init_lay [ll] [hh] * hru_area [hh];
            refractoryC_lay [ll] [hh] = refractoryCmass_init_lay [ll] [hh] * hru_area [hh];
            labileN_lay [ll] [hh] = labileNmass_init_lay [ll] [hh] * hru_area [hh];
            labileP_lay [ll] [hh] = labilePmass_init_lay [ll] [hh] * hru_area [hh];
            labileC_lay [ll] [hh] = labileCmass_init_lay [ll] [hh] * hru_area [hh];
            water_lay [ll] [hh] = 0.0;
            watermax_lay [ll] [hh] = 0.0;
            NO3_Npool_lay [ll] [hh] = 0.0;
            NH4_Npool_lay [ll] [hh] = 0.0;
            DONpool_lay [ll] [hh] = 0.0;
            SRPpool_lay [ll] [hh] = 0.0;
            DOPpool_lay [ll] [hh] = 0.0;
            partP_lay [ll] [hh] = 0.0f;
            plant_uptk_NO3N_mWQ_lay [ll] [hh] = 0.0;
            plant_uptk_NH4N_mWQ_lay [ll] [hh] = 0.0;
            plant_uptk_SRP_mWQ_lay [ll] [hh] = 0.0;
            denitrification_lay [ll] [hh] = 0.0;
            double max;
            if (ll == 0)
            {
                max = soil_rechr_max [hh];
            }

            else
            {
                max = soil_moist_max [hh] - soil_rechr_max [hh];
            }

            wp_mm_lay [ll] [hh] = max * wp_lay [ll] [hh];
        }
        for (long Sub = 0; Sub < numsubstances; ++ Sub) {
            surfsoil_solub_mWQ_lay [Sub] [hh] = surfsoil_massSolub_init_lay [Sub] [hh];
            conc_soil_rechr_lay [Sub] [hh] = conc_soil_rechr_init_lay [Sub] [hh];
            conc_soil_lower_lay [Sub] [hh] = conc_soil_lower_init_lay [Sub] [hh];
            source_lay [Sub] [hh] = 0.0;
            sink_lay [Sub] [hh] = 0.0;
            src_mineral_fertman_surfsoil_lay [Sub] [hh] = 0.0f;
            src_mineral_fertman_soilrechr_lay [Sub] [hh] = 0.0f;
            sources_plant_lay [Sub] [hh] = 0.0;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::init(void)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::run(void)@@@WQ_Soil_NPCcycling.cpp>");
    long step = getstep ();
    long nstep = step % Global :: Freq;
    if (step == 1)
    {
        for (hh = 0; hh < nhru; ++ hh) {
            const_cast < double * > (klh) [hh] /= Global :: Freq;
            const_cast < double * > (klo) [hh] /= Global :: Freq;
            const_cast < double * > (kho) [hh] /= Global :: Freq;
            const_cast < double * > (kof) [hh] /= Global :: Freq;
            const_cast < double * > (parminfN) [hh] /= Global :: Freq;
            const_cast < double * > (parminfP) [hh] /= Global :: Freq;
            const_cast < double * > (pardegrhN) [hh] /= Global :: Freq;
            const_cast < double * > (pardegrhP) [hh] /= Global :: Freq;
            const_cast < double * > (pardisfN) [hh] /= Global :: Freq;
            const_cast < double * > (pardisfP) [hh] /= Global :: Freq;
            const_cast < double * > (pardishN) [hh] /= Global :: Freq;
            const_cast < double * > (pardishP) [hh] /= Global :: Freq;
            const_cast < double * > (fertNamount_up) [hh] /= Global :: Freq;
            const_cast < double * > (fertNamount_down) [hh] /= Global :: Freq;
            const_cast < double * > (fertPamount_up) [hh] /= Global :: Freq;
            const_cast < double * > (fertPamount_down) [hh] /= Global :: Freq;
            const_cast < double * > (manNamount_up) [hh] /= Global :: Freq;
            const_cast < double * > (manNamount_down) [hh] /= Global :: Freq;
            const_cast < double * > (manPamount_up) [hh] /= Global :: Freq;
            const_cast < double * > (manPamount_down) [hh] /= Global :: Freq;
            const_cast < double * > (resNamount_up) [hh] /= Global :: Freq;
            const_cast < double * > (resPamount_up) [hh] /= Global :: Freq;
            const_cast < double * > (resCamount) [hh] /= Global :: Freq;
            const_cast < double * > (resfast) [hh] /= Global :: Freq;
        }
    }

    if (Inhibit_Soil_BGC [0])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::run(void)@@@WQ_Soil_NPCcycling.cpp>");
        return;
    }

    dayno = julian ("now");
    for (hh = 0; chkStruct (); ++ hh) {
        water_lay [0] [hh] = soil_rechr [hh];
        water_lay [1] [hh] = soil_moist [hh] - soil_rechr [hh];
        watermax_lay [0] [hh] = soil_rechr_max [hh];
        watermax_lay [1] [hh] = soil_moist_max [hh] - soil_rechr_max [hh];
        for (long ii = 0; ii < maxsoillayers; ++ ii)
            Temp_lay [ii] [hh] = hru_t [hh];
    }
    for (hh = 0; chkStruct (); ++ hh) {
        soil_np_processes ();
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::run(void)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::finish(bool good)@@@WQ_Soil_NPCcycling.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessage (hh, string ("'" + Name + " (WQ_Soil_BGC)'").c_str (), TExtra :: BLANK);
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::finish(bool good)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: soil_np_processes ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::soil_np_processes()@@@WQ_Soil_NPCcycling.cpp>");
    nutrient_inputs ();
    soil_pool_transformations ();
    if (soil_runoff [hh] > 0.0f)
    {
        runoff_pp_by_erosion ();
    }

    plant_uptake (conc_soil_rechr_lay, conc_soil_lower_lay, sink_lay);
    if (i_no3n >= 0)
    {
        cropuptake [hh] = sink_lay [i_no3n] [hh];
    }

    if (calcN [hh])
    {
        denitrification_surfsoil [hh] = 0.0;
        denitrification_lay [0] [hh] = 0.0;
        denitrification_lay [1] [hh] = 0.0;
        if (water_lay [0] [hh] > 0.0)
        {
            soil_denitrification (0);
        }

        denitrification_lay [0] [hh] = sink_lay [i_no3n] [hh];
        if (water_lay [1] [hh] > 0.0)
        {
            soil_denitrification (1);
        }

        denitrification_lay [1] [hh] = sink_lay [i_no3n] [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::soil_np_processes()@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: nutrient_inputs ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::nutrient_inputs()@@@WQ_Soil_NPCcycling.cpp>");
    double common_nadd [maxsoillayers] [2];
    double common_padd [maxsoillayers] [2];
    double common_nres [maxsoillayers] [2];
    double common_pres [maxsoillayers] [2];
    double common_cres [maxsoillayers] [2];
    double littdays;
    for (long ll = 0; ll < numsubstances; ++ ll) {
        src_mineral_fertman_surfsoil_lay [ll] [hh] = 0.0f;
        src_mineral_fertman_soilrechr_lay [ll] [hh] = 0.0f;
        sources_plant_lay [ll] [hh] = 0.0;
    }
    if (! (calcN [hh] || calcP [hh] || calcC [hh]))
    {

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::nutrient_inputs()@@@WQ_Soil_NPCcycling.cpp>");
        return;
    }

    for (long ii = 0; ii < maxsoillayers; ++ ii) {
        for (long kk = 0; kk < 2; ++ kk) {
            common_nadd [ii] [kk] = 0.0;
            common_padd [ii] [kk] = 0.0;
            common_nres [ii] [kk] = 0.0;
            common_pres [ii] [kk] = 0.0;
            common_cres [ii] [kk] = 0.0;
        }
    }
    int Y, M, D, H, Min;
    StandardConverterUtility :: DecodeDateTime (Global :: DTnow, & Y, & M, & D, & H, & Min);
    try {
        long prevdoy = (int) (StandardConverterUtility :: EncodeDateTime (Y - 1, 12, 31, 0, 0) - StandardConverterUtility :: EncodeDateTime (Y - 1, 1, 1, 0, 0)) + 1;
        if (fertday_up [hh] && ((dayno >= fertday_up [hh] && dayno < fertday_up [hh] + fertperiod [hh]) || (dayno < fertday_up [hh] + fertperiod [hh] - prevdoy)))
        {
            common_nadd [0] [0] = common_nadd [0] [inorg] + fertNamount_up [hh] / fertperiod [hh];
            common_padd [0] [0] = common_padd [0] [inorg] + fertPamount_up [hh] / fertperiod [hh];
        }

        if (fertday_down [hh] && ((dayno >= fertday_down [hh] && dayno < fertday_down [hh] + fertperiod [hh]) || (dayno < fertday_down [hh] + fertperiod [hh] - prevdoy)))
        {
            common_nadd [1] [0] = common_nadd [1] [inorg] + fertNamount_down [hh] / fertperiod [hh];
            common_padd [1] [0] = common_padd [1] [inorg] + fertPamount_down [hh] / fertperiod [hh];
        }

        if (manday_up [hh] && ((dayno >= manday_up [hh] && dayno < manday_up [hh] + fertperiod [hh]) || (dayno < manday_up [hh] + fertperiod [hh] - prevdoy)))
        {
            common_nadd [0] [0] = common_nadd [0] [inorg] + manNamount_up [hh] * manureinogNfrac [hh] / fertperiod [hh];
            common_padd [0] [0] = common_padd [0] [inorg] + manPamount_up [hh] * manureinogPfrac [hh] / fertperiod [hh];
            common_nadd [0] [1] = common_nadd [0] [fast] + manNamount_up [hh] * (1.0 - manureinogNfrac [hh]) / fertperiod [hh];
            common_padd [0] [1] = common_padd [0] [fast] + manPamount_up [hh] * (1.0 - manureinogPfrac [hh]) / fertperiod [hh];
        }

        if (manday_down [hh] && ((dayno >= manday_down [hh] && dayno < manday_down [hh] + fertperiod [hh]) || (dayno < manday_down [hh] + fertperiod [hh] - prevdoy)))
        {
            common_nadd [1] [0] = common_nadd [1] [inorg] + manNamount_down [hh] * manureinogNfrac [hh] / fertperiod [hh];
            common_padd [1] [0] = common_padd [1] [inorg] + manPamount_down [hh] * manureinogPfrac [hh] / fertperiod [hh];
            common_nadd [1] [1] = common_nadd [1] [fast] + manNamount_down [hh] * (1.0 - manureinogNfrac [hh]) / fertperiod [hh];
            common_padd [1] [1] = common_padd [1] [fast] + manPamount_down [hh] * (1.0 - manureinogPfrac [hh]) / fertperiod [hh];
        }

        littdays = litterperiod [hh];
        if (resday_up [hh] || ((dayno >= resday_up [hh] && dayno < resday_up [hh] + littdays) || (dayno < resday_up [hh] + littdays - prevdoy)))
        {
            common_nres [0] [0] = common_nres [0] [inorg] + resfast [hh] * resNamount_up [hh] / littdays;
            common_nres [0] [1] = common_nres [0] [fast] + (1.0 - resfast [hh]) * resNamount_up [hh] / littdays;
            common_pres [0] [0] = common_pres [0] [inorg] + resfast [hh] * resPamount_up [hh] / littdays;
            common_pres [0] [1] = common_pres [0] [fast] + (1.0 - resfast [hh]) * resPamount_up [hh] / littdays;
        }

        if (resday_down [hh] || ((dayno >= resday_down [hh] && dayno < resday_down [hh] + littdays) || (dayno < resday_down [hh] + littdays - prevdoy)))
        {
            common_nres [1] [0] = common_nres [0] [inorg] + resfast [hh] * resNamount_down [hh] / littdays;
            common_nres [1] [1] = common_nres [0] [fast] + (1.0 - resfast [hh]) * resNamount_down [hh] / littdays;
            common_pres [1] [0] = common_pres [0] [inorg] + resfast [hh] * resPamount_down [hh] / littdays;
            common_pres [1] [1] = common_pres [0] [fast] + (1.0 - resfast [hh]) * resPamount_down [hh] / littdays;
        }

        if (calcN [hh] && SUM (common_nadd, 0) > 0.0)
        {
            if (SWE [hh] > minFlow_WQ)
            {
                SWE_conc_lay [i_no3n] [hh] += fertandman_inogNfrac_NO3Nfrac [hh] * common_nadd [0] [inorg] / SWE [hh];
                SWE_conc_lay [i_nh4n] [hh] += fertandman_inogNfrac_NH4Nfrac [hh] * common_nadd [0] [inorg] / SWE [hh];
            }

            else
            {
                surfsoil_solub_mWQ_lay [i_no3n] [hh] += fertandman_inogNfrac_NO3Nfrac [hh] * common_nadd [0] [inorg];
                surfsoil_solub_mWQ_lay [i_nh4n] [hh] += fertandman_inogNfrac_NH4Nfrac [hh] * common_nadd [0] [inorg];
            }

            if (water_lay [0] [hh] > 0.0)
            {
                add_source_to_water (water_lay [0] [hh], i_no3n, & conc_soil_rechr_lay [i_no3n] [hh], fertandman_inogNfrac_NO3Nfrac [hh] * common_nadd [1] [inorg]);
                add_source_to_water (water_lay [0] [hh], i_nh4n, & conc_soil_rechr_lay [i_nh4n] [hh], fertandman_inogNfrac_NH4Nfrac [hh] * common_nadd [1] [inorg]);
            }

            else
            if (water_lay [1] [hh] > 0.0)
            {
                add_source_to_water (water_lay [1] [hh], i_no3n, & conc_soil_lower_lay [i_no3n] [hh], fertandman_inogNfrac_NO3Nfrac [hh] * common_nadd [1] [inorg]);
                add_source_to_water (water_lay [1] [hh], i_nh4n, & conc_soil_lower_lay [i_nh4n] [hh], fertandman_inogNfrac_NH4Nfrac [hh] * common_nadd [1] [inorg]);
            }

            else
            {
                production_pool (1, labileN_lay [0] [hh], common_nadd [1] [inorg]);
            }

            src_mineral_fertman_surfsoil_lay [i_no3n] [hh] += fertandman_inogNfrac_NO3Nfrac [hh] * (common_nadd [0] [inorg]);
            src_mineral_fertman_surfsoil_lay [i_nh4n] [hh] += fertandman_inogNfrac_NH4Nfrac [hh] * (common_nadd [0] [inorg]);
            src_mineral_fertman_soilrechr_lay [i_no3n] [hh] += fertandman_inogNfrac_NO3Nfrac [hh] * (common_nadd [1] [inorg]);
            src_mineral_fertman_soilrechr_lay [i_nh4n] [hh] += fertandman_inogNfrac_NH4Nfrac [hh] * (common_nadd [1] [inorg]);
        }

        if (calcP [hh] && SUM (common_padd, 0) > 0.0)
        {
            if (SWE [hh] > minFlow_WQ)
            {
                SWE_conc_lay [i_srp] [hh] += common_padd [0] [inorg] / SWE [hh];
            }

            else
            {
                surfsoil_solub_mWQ_lay [i_srp] [hh] += common_padd [0] [inorg];
            }

            if (water_lay [0] [hh] > 0.0)
            {
                add_source_to_water (water_lay [0] [hh], i_srp, & conc_soil_rechr_lay [i_srp] [hh], common_padd [1] [inorg]);
            }

            else
            if (water_lay [1] [hh] > 0.0)
            {
                add_source_to_water (water_lay [1] [hh], i_srp, & conc_soil_lower_lay [i_srp] [hh], common_padd [1] [inorg]);
            }

            else
            {
                production_pool (1, labileP_lay [0] [hh], common_padd [1] [inorg]);
            }

            src_mineral_fertman_surfsoil_lay [i_srp] [hh] += common_padd [0] [inorg];
            src_mineral_fertman_soilrechr_lay [i_srp] [hh] += common_nadd [1] [inorg];
        }

        if (calcN [hh] && SUM (common_nadd, 1) > 0.0)
        {
            surfsoil_labileN_mWQ [hh] += common_nadd [0] [1];
            labileN_lay [0] [hh] += common_nadd [1] [1];
            production_pool (1, hh, labileN_lay, common_nadd);
        }

        if (calcP [hh] && SUM (common_padd, 1) > 0.0)
        {
            surfsoil_labileP_mWQ [hh] += common_padd [0] [1];
            labileP_lay [0] [hh] += common_padd [1] [1];
        }

        if (calcN [hh] && (SUM (common_nres, 0) + SUM (common_nres, 1)) > 0.0)
        {
            surfsoil_labileN_mWQ [hh] += common_nres [0] [0];
            surfsoil_refractoryN_mWQ [hh] += common_nres [0] [1];
            labileN_lay [0] [hh] += common_nres [1] [0];
            refractoryN_lay [0] [hh] += common_nres [1] [1];
            sources_plant_lay [i_don] [hh] = SUM (common_nres, 0) + SUM (common_nres, 1);
        }

        if (calcP [hh] && (SUM (common_pres, 0) + SUM (common_pres, 1)) > 0.0)
        {
            surfsoil_labileP_mWQ [hh] += common_pres [0] [0];
            surfsoil_refractoryP_mWQ [hh] += common_pres [0] [1];
            labileP_lay [0] [hh] += common_pres [1] [0];
            refractoryP_lay [0] [hh] += common_pres [1] [1];
            sources_plant_lay [i_pp] [hh] = SUM (common_pres, 0) + SUM (common_pres, 1);
        }

        if (calcC [hh] && (SUM (common_cres, 0) + SUM (common_cres, 1)) > 0.0)
        {
            if (water_lay [1] [hh] > 0.0)
            {
                production_pool (1, hh, labileC_lay, common_cres);
            }

            else
            {
                production_pool (1, hh, labileC_lay, common_cres);
            }

            sources_plant_lay [i_oc] [hh] = SUM (common_cres, 0) + SUM (common_cres, 1);
        }

    }
    catch (...) {
        string moduleName;
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
            if (it -> first == Global :: CurrentModuleRun)
            {
                moduleName = it -> first;
            }

        }
        string S = string ("Error ") + " at " + StandardConverterUtility :: GetDateTimeInString (Global :: DTnow) + " (" + to_string (getstep ()) + ") in '" + moduleName + "'" + " (" + FloatToStrF (Global :: DTnow, TFloatFormat :: ffGeneral, 10, 6) + ") hh = " + FloatToStrF (hh, TFloatFormat :: ffGeneral, 6, 0);
        LogError (S, TExcept :: WARNING);
        throw;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::nutrient_inputs()@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: soil_pool_transformations ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::soil_pool_transformations()@@@WQ_Soil_NPCcycling.cpp>");
    double degradhN [maxsoillayers], transfminN [maxsoillayers], transfnitrN [maxsoillayers];
    double transfP [maxsoillayers], degradhP [maxsoillayers];
    double dissolfN [maxsoillayers], dissolfP [maxsoillayers];
    double dissolhN [maxsoillayers], dissolhP [maxsoillayers];
    double tmpfcn [maxsoillayers];
    double smfcn [maxsoillayers];
    source [hh] = 0.0;
    for (long ii = 0; ii < numsubstances; ++ ii) {
        source_lay [ii] [hh] = 0.0;
    }
    for (long ii = 0; ii < maxsoillayers; ++ ii) {
        NO3_Npool_lay [ii] [hh] = 0.0f;
        NH4_Npool_lay [ii] [hh] = 0.0f;
        SRPpool_lay [ii] [hh] = 0.0f;
        DONpool_lay [ii] [hh] = 0.0f;
        DOPpool_lay [ii] [hh] = 0.0f;
        partP_lay [ii] [hh] = 0.0f;
        degradhN [ii] = 0.0f;
        transfminN [ii] = 0.0f;
        dissolfN [ii] = 0.0f;
        dissolhN [ii] = 0.0f;
        degradhP [ii] = 0.0f;
        transfP [ii] = 0.0f;
        dissolfP [ii] = 0.0f;
        dissolhP [ii] = 0.0f;
        smfcn [ii] = 0.0f;
    }
    if (calcN [hh])
    {
        NO3_Npool_lay [0] [hh] = conc_soil_rechr_lay [i_no3n] [hh] * water_lay [0] [hh];
        NH4_Npool_lay [0] [hh] = conc_soil_rechr_lay [i_nh4n] [hh] * water_lay [0] [hh];
        DONpool_lay [0] [hh] = conc_soil_rechr_lay [i_don] [hh] * water_lay [0] [hh];
        NO3_Npool_lay [1] [hh] = conc_soil_lower_lay [i_no3n] [hh] * water_lay [1] [hh];
        NH4_Npool_lay [1] [hh] = conc_soil_lower_lay [i_nh4n] [hh] * water_lay [1] [hh];
        DONpool_lay [1] [hh] = conc_soil_lower_lay [i_don] [hh] * water_lay [1] [hh];
    }

    if (calcP [hh])
    {
        SRPpool_lay [0] [hh] = conc_soil_rechr_lay [i_srp] [hh] * water_lay [0] [hh];
        DOPpool_lay [0] [hh] = conc_soil_rechr_lay [i_dop] [hh] * water_lay [0] [hh];
        partP_lay [0] [hh] = conc_soil_rechr_lay [i_pp] [hh] * water_lay [0] [hh];
        SRPpool_lay [1] [hh] = conc_soil_lower_lay [i_srp] [hh] * water_lay [1] [hh];
        DOPpool_lay [1] [hh] = conc_soil_lower_lay [i_dop] [hh] * water_lay [1] [hh];
        partP_lay [1] [hh] = conc_soil_rechr_lay [i_pp] [hh] * water_lay [1] [hh];
    }

    for (long k = 0; k < maxsoillayers; ++ k) {
        if (water_lay [k] [hh] > 0.0)
        {
            tmpfcn [k] = tempfactor (Temp_lay [0] [hh]);
        }

        else
        {
            tmpfcn [k] = 0.0;
        }

    }
    smfcn [0] = moisturefactor (water_lay [0] [hh] / watermax_lay [0] [hh], wp_lay [0] [hh], satact, thetapow, thetalow, thetaupp);
    smfcn [1] = moisturefactor (water_lay [1] [hh] / watermax_lay [1] [hh], wp_lay [1] [hh], satact, thetapow, thetalow, thetaupp);
    if (calcN [hh])
    {
        degradhN [0] = pardegrhN [hh] * tmpfcn [0] * smfcn [0] * surfsoil_refractoryN_mWQ [hh];
        surfsoil_refractoryN_mWQ [hh] -= degradhN [0];
        surfsoil_labileN_mWQ [hh] += degradhN [0];
        degradhN [0] = pardegrhN [hh] * tmpfcn [0] * smfcn [0] * refractoryN_lay [0] [hh];
        degradhN [1] = pardegrhN [hh] * tmpfcn [1] * smfcn [1] * refractoryN_lay [1] [hh];
        if (water_lay [1] [hh] > 0.0)
        {
            retention_pool (2, hh, refractoryN_lay, degradhN);
            production_pool (2, hh, labileN_lay, degradhN);
        }

        else
        {
            retention_pool (1, hh, refractoryN_lay, degradhN);
            production_pool (1, hh, labileN_lay, degradhN);
        }

        transfminN [0] = std :: fmax (parminfN [hh] * tmpfcn [0] * smfcn [0] * surfsoil_labileN_mWQ [hh], 0.0f);
        surfsoil_labileN_mWQ [hh] -= transfminN [0];
        surfsoil_solub_mWQ_lay [i_nh4n] [hh] += transfminN [0];
        transfminN [0] = std :: fmax (parminfN [hh] * tmpfcn [0] * smfcn [0] * labileN_lay [0] [hh], 0.0f);
        transfminN [1] = std :: fmax (parminfN [hh] * tmpfcn [1] * smfcn [1] * labileN_lay [1] [hh], 0.0f);
        if (water_lay [1] [hh] > 0.0)
        {
            retention_pool (2, hh, labileN_lay, transfminN);
            production_pool (2, hh, NH4_Npool_lay, transfminN);
        }

        else
        {
            retention_pool (1, hh, labileN_lay, transfminN);
            production_pool (1, hh, NH4_Npool_lay, transfminN);
        }

        new_concentration (NH4_Npool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_nh4n] [hh]);
        if (water_lay [1] [hh] > 0.0)
        {
            new_concentration (NH4_Npool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_nh4n] [hh]);
        }

        transfnitrN [0] = std :: fmax (parnitrfN [hh] * tmpfcn [0] * smfcn [0] * surfsoil_solub_mWQ_lay [i_nh4n] [hh], 0.0f);
        surfsoil_solub_mWQ_lay [i_nh4n] [hh] -= transfnitrN [0];
        surfsoil_solub_mWQ_lay [i_no3n] [hh] += transfnitrN [0];
        transfnitrN [0] = std :: fmax (parnitrfN [hh] * tmpfcn [0] * smfcn [0] * NH4_Npool_lay [0] [hh], 0.0f);
        transfnitrN [1] = std :: fmax (parnitrfN [hh] * tmpfcn [1] * smfcn [1] * NH4_Npool_lay [1] [hh], 0.0f);
        if (water_lay [1] [hh] > 0.0)
        {
            retention_pool (2, hh, NH4_Npool_lay, transfnitrN);
            production_pool (2, hh, NO3_Npool_lay, transfnitrN);
        }

        else
        {
            retention_pool (1, hh, NH4_Npool_lay, transfnitrN);
            production_pool (1, hh, NO3_Npool_lay, transfnitrN);
        }

        new_concentration (NH4_Npool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_nh4n] [hh]);
        new_concentration (NO3_Npool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_no3n] [hh]);
        if (water_lay [1] [hh] > 0.0)
        {
            new_concentration (NH4_Npool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_nh4n] [hh]);
            new_concentration (NO3_Npool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_no3n] [hh]);
        }

    }

    if (calcP [hh])
    {
        degradhP [0] = pardegrhP [hh] * tmpfcn [0] * smfcn [0] * surfsoil_refractoryP_mWQ [hh];
        surfsoil_refractoryP_mWQ [hh] -= degradhP [0];
        surfsoil_labileP_mWQ [hh] += degradhP [0];
        degradhP [0] = pardegrhP [hh] * tmpfcn [0] * smfcn [0] * refractoryP_lay [0] [hh];
        degradhP [1] = pardegrhP [hh] * tmpfcn [1] * smfcn [1] * refractoryP_lay [1] [hh];
        if (water_lay [1] [hh] > 0.0)
        {
            retention_pool (2, hh, refractoryP_lay, degradhP);
            production_pool (2, hh, labileP_lay, degradhP);
        }

        else
        {
            retention_pool (1, hh, refractoryP_lay, degradhP);
            production_pool (1, hh, labileP_lay, degradhP);
        }

        transfP [0] = std :: fmax (parminfP [hh] * tmpfcn [0] * smfcn [0] * surfsoil_labileP_mWQ [hh], 0.0f);
        surfsoil_labileP_mWQ [hh] -= transfP [0];
        surfsoil_solub_mWQ_lay [i_srp] [hh] += transfP [0];
        transfP [0] = parminfP [hh] * tmpfcn [0] * smfcn [0] * labileP_lay [0] [hh];
        transfP [1] = parminfP [hh] * tmpfcn [1] * smfcn [1] * labileP_lay [1] [hh];
        if (water_lay [1] [hh] > 0)
        {
            retention_pool (2, hh, labileP_lay, transfP);
            production_pool (2, hh, SRPpool_lay, transfP);
        }

        else
        {
            retention_pool (1, hh, labileP_lay, transfP);
            production_pool (1, hh, SRPpool_lay, transfP);
        }

        new_concentration (SRPpool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_srp] [hh]);
        if (water_lay [1] [hh] > 0.0)
        {
            new_concentration (SRPpool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_srp] [hh]);
        }

    }

    if (calcN [hh])
    {
        dissolfN [0] = std :: fmax (pardisfN [hh] * tmpfcn [0] * smfcn [0] * surfsoil_labileN_mWQ [hh], 0.0f);
        surfsoil_labileN_mWQ [hh] -= dissolfN [0];
        surfsoil_solub_mWQ_lay [i_don] [hh] += dissolfN [0];
        dissolfN [0] = pardisfN [hh] * tmpfcn [0] * smfcn [0] * labileN_lay [0] [hh];
        dissolfN [1] = pardisfN [hh] * tmpfcn [1] * smfcn [1] * labileN_lay [1] [hh];
        if (water_lay [1] [hh] > 0.0)
        {
            retention_pool (2, hh, labileN_lay, dissolfN);
            production_pool (2, hh, DONpool_lay, dissolfN);
        }

        else
        {
            retention_pool (1, hh, labileN_lay, dissolfN);
            production_pool (1, hh, DONpool_lay, dissolfN);
        }

        dissolhN [0] = pardishN [hh] * tmpfcn [0] * smfcn [0] * surfsoil_refractoryN_mWQ [hh];
        surfsoil_refractoryN_mWQ [hh] -= dissolhN [0];
        surfsoil_solub_mWQ_lay [i_don] [hh] += dissolhN [0];
        dissolhN [0] = pardishN [hh] * tmpfcn [0] * smfcn [0] * refractoryN_lay [0] [hh];
        dissolhN [1] = pardishN [hh] * tmpfcn [1] * smfcn [1] * refractoryN_lay [1] [hh];
        if (water_lay [1] [hh] > 0.0)
        {
            retention_pool (2, hh, refractoryN_lay, dissolhN);
            production_pool (2, hh, DONpool_lay, dissolhN);
        }

        else
        {
            retention_pool (1, hh, refractoryN_lay, dissolhN);
            production_pool (1, hh, DONpool_lay, dissolhN);
        }

        new_concentration (DONpool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_don] [hh]);
        if (water_lay [1] [hh] > 0.0)
        {
            new_concentration (DONpool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_don] [hh]);
        }

    }

    if (calcP [hh])
    {
        dissolfP [0] = pardisfP [hh] * tmpfcn [0] * smfcn [0] * surfsoil_labileP_mWQ [hh];
        surfsoil_labileP_mWQ [hh] -= dissolfP [0];
        surfsoil_solub_mWQ_lay [i_dop] [hh] += dissolfP [0];
        dissolfP [0] = pardisfP [hh] * tmpfcn [0] * smfcn [0] * labileP_lay [0] [hh];
        dissolfP [1] = pardisfP [hh] * tmpfcn [1] * smfcn [1] * labileP_lay [1] [hh];
        if (water_lay [1] [hh] > 0.0)
        {
            retention_pool (2, hh, labileP_lay, dissolfP);
            production_pool (2, hh, DOPpool_lay, dissolfP);
        }

        else
        {
            retention_pool (1, hh, labileP_lay, dissolfP);
            production_pool (1, hh, DOPpool_lay, dissolfP);
        }

        dissolhP [0] = pardishP [hh] * tmpfcn [0] * smfcn [0] * surfsoil_refractoryP_mWQ [hh];
        surfsoil_refractoryP_mWQ [hh] -= dissolhP [0];
        surfsoil_solub_mWQ_lay [i_dop] [hh] += dissolhP [0];
        dissolhP [0] = pardishP [hh] * tmpfcn [0] * smfcn [0] * refractoryP_lay [0] [hh];
        dissolhP [1] = pardishP [hh] * tmpfcn [1] * smfcn [1] * refractoryP_lay [1] [hh];
        if (water_lay [1] [hh] > 0.0)
        {
            retention_pool (2, hh, refractoryP_lay, dissolhP);
            production_pool (2, hh, DOPpool_lay, dissolhP);
        }

        else
        {
            retention_pool (1, hh, refractoryP_lay, dissolhP);
            production_pool (1, hh, DOPpool_lay, dissolhP);
        }

        new_concentration (DOPpool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_dop] [hh]);
        if (water_lay [1] [hh] > 0.0)
        {
            new_concentration (DOPpool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_dop] [hh]);
        }

    }

    if (calcN [hh])
    {
        source_lay [i_no3n] [hh] = SUM (transfminN);
        source_lay [i_don] [hh] = SUM (dissolfN) + SUM (dissolhN);
    }

    if (calcP [hh])
    {
        source_lay [i_srp] [hh] = SUM (transfP);
        source_lay [i_pp] [hh] = SUM (dissolfP) + SUM (dissolhP);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::soil_pool_transformations()@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: plant_uptake (double ** conc_soil_rechr_lay, double ** conc_soil_lower_lay, double ** sink_lay)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::plant_uptake(double ** conc_soil_rechr_lay, double ** conc_soil_lower_lay, double ** sink_lay)@@@WQ_Soil_NPCcycling.cpp>");
    double maxpooluptake [maxsoillayers];
    double tmpfcn [maxsoillayers];
    double smfcn [maxsoillayers];
    double excess_pltup, plant_uptk_mWQ;
    plant_uptk_mWQ = 0.0f;
    excess_pltup = 0.0f;
    for (long kk = 0; kk < numsubstances; ++ kk)
        sink_lay [kk] [hh] = 0.0;
    for (long kk = 0; kk < maxsoillayers; ++ kk) {
        plant_uptk_NO3N_mWQ_lay [kk] [hh] = 0.0f;
        plant_uptk_NH4N_mWQ_lay [kk] [hh] = 0.0f;
        plant_uptk_SRP_mWQ_lay [kk] [hh] = 0.0f;
    }
    for (long k = 0; k < maxsoillayers; ++ k) {
        if (water_lay [k] [hh] > 0.0)
        {
            tmpfcn [k] = tempfactor (Temp_lay [0] [hh]);
        }

        else
        {
            tmpfcn [k] = 0.0;
        }

    }
    smfcn [0] = moisturefactor (water_lay [0] [hh] / watermax_lay [0] [hh], wp_lay [0] [hh], satact, thetapow, thetalow, thetaupp);
    smfcn [1] = moisturefactor (water_lay [1] [hh] / watermax_lay [1] [hh], wp_lay [1] [hh], satact, thetapow, thetalow, thetaupp);
    if (calcN [hh])
    {
        NO3_Npool_lay [0] [hh] = conc_soil_rechr_lay [i_no3n] [hh] * water_lay [0] [hh];
        NH4_Npool_lay [0] [hh] = conc_soil_rechr_lay [i_nh4n] [hh] * water_lay [0] [hh];
        NO3_Npool_lay [1] [hh] = conc_soil_lower_lay [i_no3n] [hh] * water_lay [1] [hh];
        NH4_Npool_lay [1] [hh] = conc_soil_lower_lay [i_nh4n] [hh] * water_lay [1] [hh];
    }

    if (calcP [hh])
    {
        SRPpool_lay [0] [hh] = conc_soil_rechr_lay [i_srp] [hh] * water_lay [0] [hh];
        SRPpool_lay [1] [hh] = conc_soil_lower_lay [i_srp] [hh] * water_lay [1] [hh];
    }

    maxpooluptake [0] = 0.0;
    maxpooluptake [1] = 0.0;
    if (water_lay [0] [hh] > wp_mm_lay [0] [hh])
    {
        maxpooluptake [0] = (water_lay [0] [hh] - wp_mm_lay [0] [hh]) / water_lay [0] [hh];
    }

    if (water_lay [1] [hh] > 0.0 && water_lay [1] [hh] > wp_mm_lay [1] [hh])
    {
        maxpooluptake [1] = (water_lay [1] [hh] - wp_mm_lay [1] [hh]) / water_lay [1] [hh];
    }

    if (calcN [hh])
    {
        plant_uptk_mWQ = std :: fmin (plant_uptk_NO3N_lay [0] [hh] * tmpfcn [0] * smfcn [0] * hru_area [hh], maxpooluptake [0] * (surfsoil_solub_mWQ_lay [i_no3n] [hh] + NO3_Npool_lay [0] [hh]));
        if (plant_uptk_mWQ <= surfsoil_solub_mWQ_lay [i_no3n] [hh])
        {
            surfsoil_solub_mWQ_lay [i_no3n] [hh] -= plant_uptk_mWQ;
            excess_pltup = 0.0f;
        }

        else
        {
            excess_pltup = plant_uptk_mWQ - surfsoil_solub_mWQ_lay [i_no3n] [hh];
            surfsoil_solub_mWQ_lay [i_no3n] [hh] = 0.0f;
            NO3_Npool_lay [0] [hh] -= excess_pltup;
        }

        plant_uptk_NO3N_mWQ_lay [0] [hh] = plant_uptk_mWQ - excess_pltup;
        plant_uptk_NO3N_mWQ_lay [1] [hh] = excess_pltup;
        plant_uptk_mWQ = min < double > (plant_uptk_NH4N_lay [0] [hh] * tmpfcn [0] * smfcn [0] * hru_area [hh], maxpooluptake [0] * (surfsoil_solub_mWQ_lay [i_nh4n] [hh] + NH4_Npool_lay [0] [hh]));
        if (plant_uptk_mWQ <= surfsoil_solub_mWQ_lay [i_nh4n] [hh])
        {
            surfsoil_solub_mWQ_lay [i_nh4n] [hh] -= plant_uptk_mWQ;
            excess_pltup = 0.0f;
        }

        else
        {
            excess_pltup = plant_uptk_mWQ - surfsoil_solub_mWQ_lay [i_nh4n] [hh];
            surfsoil_solub_mWQ_lay [i_no3n] [hh] = 0.0f;
            NH4_Npool_lay [0] [hh] -= excess_pltup;
        }

        plant_uptk_NH4N_mWQ_lay [0] [hh] = plant_uptk_mWQ - excess_pltup;
        plant_uptk_NH4N_mWQ_lay [1] [hh] = excess_pltup;
    }

    if (calcP [hh])
    {
        plant_uptk_mWQ = min < double > (plant_uptk_SRP_lay [0] [hh] * tmpfcn [0] * smfcn [0] * hru_area [hh], maxpooluptake [0] * (surfsoil_solub_mWQ_lay [i_srp] [hh] + SRPpool_lay [0] [hh]));
        if (plant_uptk_mWQ <= surfsoil_solub_mWQ_lay [i_srp] [hh])
        {
            surfsoil_solub_mWQ_lay [i_srp] [hh] -= plant_uptk_mWQ;
            excess_pltup = 0.0f;
        }

        else
        {
            excess_pltup = plant_uptk_mWQ - surfsoil_solub_mWQ_lay [i_srp] [hh];
            surfsoil_solub_mWQ_lay [i_srp] [hh] = 0.0f;
            SRPpool_lay [0] [hh] -= excess_pltup;
        }

        plant_uptk_SRP_mWQ_lay [0] [hh] = plant_uptk_mWQ - excess_pltup;
        plant_uptk_SRP_mWQ_lay [1] [hh] = excess_pltup;
    }

    if (calcN [hh])
    {
        sink_lay [i_no3n] [hh] = plant_uptk_NO3N_mWQ_lay [0] [hh] + plant_uptk_NO3N_mWQ_lay [1] [hh];
        sink_lay [i_nh4n] [hh] = plant_uptk_NH4N_mWQ_lay [0] [hh] + plant_uptk_NH4N_mWQ_lay [1] [hh];
    }

    if (calcP [hh])
    {
        sink_lay [i_srp] [hh] = plant_uptk_SRP_mWQ_lay [0] [hh] + plant_uptk_SRP_mWQ_lay [1] [hh];
    }

    if (calcN [hh])
    {
        new_concentration (NO3_Npool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_no3n] [hh]);
        new_concentration (NH4_Npool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_nh4n] [hh]);
        if (water_lay [1] [hh] > 0.0)
        {
            new_concentration (NO3_Npool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_no3n] [hh]);
            new_concentration (NH4_Npool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_nh4n] [hh]);
        }

        else
        {
            conc_soil_lower_lay [i_no3n] [hh] = 0.0f;
            conc_soil_lower_lay [i_nh4n] [hh] = 0.0f;
        }

    }

    if (calcP [hh])
    {
        new_concentration (SRPpool_lay [0] [hh], water_lay [0] [hh], & conc_soil_rechr_lay [i_srp] [hh]);
        if (water_lay [1] [hh] > 0.0)
        {
            new_concentration (SRPpool_lay [1] [hh], water_lay [1] [hh], & conc_soil_lower_lay [i_srp] [hh]);
        }

        else
        {
            conc_soil_lower_lay [i_srp] [hh] = 0.0f;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::plant_uptake(double ** conc_soil_rechr_lay, double ** conc_soil_lower_lay, double ** sink_lay)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: soil_denitrification (const long soil_layer)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::soil_denitrification(const long soil_layer)@@@WQ_Soil_NPCcycling.cpp>");
    double denitr [2];
    double denitr_surfsoil;
    double smfcn, concfcn;
    double tmpfcn = 0.0;
    double soil_max [2];
    for (long kk = 0; kk < numsubstances; ++ kk)
        sink_lay [kk] [hh] = 0.0;
    if (soil_layer == 0)
    {
        NO3_Npool_lay [soil_layer] [hh] = conc_soil_rechr_lay [0] [hh] * water_lay [soil_layer] [hh];
        soil_max [0] = soil_rechr_max [hh];
    }

    else
    {
        NO3_Npool_lay [soil_layer] [hh] = conc_soil_lower_lay [0] [hh] * water_lay [soil_layer] [hh];
        soil_max [1] = soil_moist_max [hh] - soil_rechr_max [hh];
    }

    tmpfcn = tempfactor (Temp_lay [0] [hh]);
    smfcn = exponential_moisturefactor (water_lay [soil_layer] [hh], soil_max [soil_layer], smfdenitlim, smfdenitpow);
    if (soil_layer == 0)
    {
        concfcn = halfsatconcfactor (conc_soil_rechr_lay [0] [hh], halfsatINsoil);
    }

    else
    {
        concfcn = halfsatconcfactor (conc_soil_lower_lay [0] [hh], halfsatINsoil);
    }

    if (soil_layer == 0)
    {
        denitr_surfsoil = pardenN [hh] * surfsoil_solub_mWQ_lay [i_no3n] [hh] * tmpfcn * smfcn * concfcn;
        surfsoil_solub_mWQ_lay [i_no3n] [hh] -= denitr_surfsoil;
        denitrification_surfsoil [hh] = denitr_surfsoil;
    }

    denitr [soil_layer] = pardenN [hh] * NO3_Npool_lay [soil_layer] [hh] * tmpfcn * smfcn * concfcn;
    retention_pool (1, hh, NO3_Npool_lay, denitr);
    sink_lay [soil_layer] [hh] = denitr [0];
    if (soil_layer == 0)
    {
        new_concentration (NO3_Npool_lay [soil_layer] [hh], water_lay [soil_layer] [hh], & conc_soil_rechr_lay [0] [hh]);
    }

    else
    {
        new_concentration (NO3_Npool_lay [soil_layer] [hh], water_lay [soil_layer] [hh], & conc_soil_lower_lay [0] [hh]);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::soil_denitrification(const long soil_layer)@@@WQ_Soil_NPCcycling.cpp>");
}
double ClassWQ_SoilBGC :: tempfactor (double temperature)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::tempfactor(double temperature)@@@WQ_Soil_NPCcycling.cpp>");
    double fcn;
    if (temperature < 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::tempfactor(double temperature)@@@WQ_Soil_NPCcycling.cpp>");
        return 0.0;
    }

    fcn = pow (2.0, (temperature - 20.0) / 10.0);
    if (temperature < 5.0)
    {
        fcn = fcn * temperature / 5.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::tempfactor(double temperature)@@@WQ_Soil_NPCcycling.cpp>");
    return fcn;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::tempfactor(double temperature)@@@WQ_Soil_NPCcycling.cpp>");
}
double ClassWQ_SoilBGC :: moisturefactor (double sm, double wp, double satsmf, double thetapow, double thetalow, double thetaupp)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::moisturefactor(double sm, double wp, double satsmf, double thetapow, double thetalow, double thetaupp)@@@WQ_Soil_NPCcycling.cpp>");
    double smfcn;
    if (sm >= 1)
    {
        smfcn = satsmf;
    }

    else
    if (sm <= wp)
    {
        smfcn = 0.0;
    }

    else
    {
        smfcn = std :: fmin (1.0, std :: fmin ((1 - satsmf) * pow ((1 - sm) / thetaupp, thetapow) + satsmf, pow ((sm - wp) / thetalow, thetapow)));
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::moisturefactor(double sm, double wp, double satsmf, double thetapow, double thetalow, double thetaupp)@@@WQ_Soil_NPCcycling.cpp>");
    return smfcn;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::moisturefactor(double sm, double wp, double satsmf, double thetapow, double thetalow, double thetaupp)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: soil_carbon_processes ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::soil_carbon_processes()@@@WQ_Soil_NPCcycling.cpp>");
    soil_carbon_pool_transformations ();
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::soil_carbon_processes()@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: soil_carbon_pool_transformations ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::soil_carbon_pool_transformations()@@@WQ_Soil_NPCcycling.cpp>");
    double DOCpool [maxsoillayers];
    double fasttorefractory [maxsoillayers];
    double doctofast [maxsoillayers];
    double transhC [maxsoillayers];
    double transfC [maxsoillayers];
    double tmpfcn [maxsoillayers], smfcn [maxsoillayers];
    double real1temp [1];
    double fracprod;
    if (calcC [hh] == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::soil_carbon_pool_transformations()@@@WQ_Soil_NPCcycling.cpp>");
        return;
    }

    DOCpool [0] = water_lay [0] [hh] * conc_soil_rechr_lay [i_oc] [hh];
    DOCpool [1] = water_lay [1] [hh] * conc_soil_lower_lay [i_oc] [hh];
    fracprod = 1.0 - minc [hh];
    for (long kk = 0; kk < maxsoillayers; ++ kk) {
        if (water_lay [kk] [hh] > 0.0)
        {
            tmpfcn [kk] = tempfactor (Temp_lay [kk] [hh]);
        }

        else
        {
            tmpfcn [kk] = 0.0;
        }

    }
    smfcn [0] = moisturefactor (water_lay [0] [hh] / watermax_lay [0] [hh], wp_lay [0] [hh], soimf [hh], thetapow, soimr [hh], thetaupp);
    smfcn [1] = moisturefactor (water_lay [1] [hh] / watermax_lay [1] [hh], wp_lay [1] [hh], soimf [hh], thetapow, soimr [hh], thetaupp);
    for (long kk = 0; kk < maxsoillayers; ++ kk)
        fasttorefractory [kk] = 0.0;
    if (water_lay [1] [hh] > 0.0)
    {
        for (long k = 0; k < 2; ++ k) {
            fasttorefractory [k] = klh [hh] * tmpfcn [k] * smfcn [k] * labileC_lay [k] [hh];
            retention_pool (maxsoillayers, hh, labileC_lay, fasttorefractory);
            production_pool (maxsoillayers, & refractoryC_lay [1] [hh], fracprod * fasttorefractory [1]);
        }
    }

    else
    {
        fasttorefractory [0] = klh [hh] * tmpfcn [0] * smfcn [0] * labileC_lay [0] [hh];
        retention_pool (maxsoillayers, hh, labileC_lay, fasttorefractory);
        real1temp [0] = fracprod * fasttorefractory [0];
        production_pool (maxsoillayers, hh, refractoryC_lay, real1temp);
    }

    for (long k = 0; k < maxsoillayers; ++ k)
        doctofast [k] = 0.0;
    for (long k = 0; k < maxsoillayers; ++ k)
        if (k == 0)
        {
            if (water_lay [k] [hh] > 0.0 && smfcn [k] < koflim [hh] && water_lay [k] [hh] < soil_rechr [hh] && Temp_lay [k] [hh] < 5.0)
            {
                doctofast [k] = kof [hh] * DOCpool [k];
            }

            else
            if (water_lay [k] [hh] > 0.0 && smfcn [k] < koflim [hh] && water_lay [k] [hh] < soil_moist [hh] && Temp_lay [k] [hh] < 5.0)
            {
                doctofast [k] = kof [hh] * DOCpool [k];
            }

        }

    if (water_lay [1] [hh] > 0)
    {
        production_pool (maxsoillayers, labileC_lay [1] [hh], fracprod * doctofast [1]);
    }

    else
    {
        real1temp [0] = fracprod * doctofast [0];
        production_pool (2, labileC_lay [0] [hh], real1temp [0]);
    }

    for (long k = 0; k < maxsoillayers; ++ k)
        transfC [k] = 0.0;
    if (water_lay [1] [hh] > 0.0)
    {
        transfC [1] = klo [hh] * tmpfcn [1] * smfcn [1] * labileC_lay [1] [hh];
        retention_pool (maxsoillayers, hh, labileC_lay, transfC);
        production_pool (maxsoillayers, DOCpool [1], fracprod * transfC [1]);
    }

    else
    {
        transfC [0] = klo [hh] * tmpfcn [0] * smfcn [0] * labileC [0];
        retention_pool (maxsoillayers, hh, labileC_lay, transfC);
        real1temp [0] = fracprod * transfC [0];
        production_pool (maxsoillayers, DOCpool [0], real1temp [0]);
    }

    for (long k = 0; k < maxsoillayers; ++ k)
        transhC [k] = 0.0;
    if (water_lay [1] [hh] > 0.0)
    {
        transhC [1] = kho [hh] * tmpfcn [1] * smfcn [1] * refractoryC [1];
        retention_pool (maxsoillayers, hh, refractoryC_lay, transhC);
        production_pool (2, DOCpool [1], fracprod * transhC [1]);
    }

    else
    {
        transhC [0] = kho [hh] * tmpfcn [0] * smfcn [0] * refractoryC_lay [0] [hh];
        retention_pool (maxsoillayers, hh, refractoryC_lay, transhC);
        real1temp [0] = fracprod * transhC [0];
        production_pool (2, DOCpool [0], real1temp [0]);
    }

    new_concentration (DOCpool [0], water_lay [0] [hh], & conc_soil_rechr_lay [i_oc] [hh]);
    if (water_lay [1] [hh] > 0.0)
    {
        new_concentration (DOCpool [1], water_lay [1] [hh], & conc_soil_lower_lay [i_oc] [hh]);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::soil_carbon_pool_transformations()@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: add_source_to_water (const double vol, const long n, double * conc, const double source)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::add_source_to_water(const double vol, const long n, double * conc, const double source)@@@WQ_Soil_NPCcycling.cpp>");
    if (vol > 0.0)
    {
        * conc = (* conc * vol + source) / vol;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::add_source_to_water(const double vol, const long n, double * conc, const double source)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: add_source_to_water (const double vol, long n, double conc, double source)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::add_source_to_water(const double vol, long n, double conc, double source)@@@WQ_Soil_NPCcycling.cpp>");
    if (vol > 0.0)
    {
        conc = (conc * vol + source) / vol;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::add_source_to_water(const double vol, long n, double conc, double source)@@@WQ_Soil_NPCcycling.cpp>");
}
double ClassWQ_SoilBGC :: exponential_moisturefactor (const double sm, const double pw, const double limpar, const double exp)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::exponential_moisturefactor(const double sm, const double pw, const double limpar, const double exp)@@@WQ_Soil_NPCcycling.cpp>");
    double smfcn;
    smfcn = 0.0;
    if ((sm / pw) > limpar)
    {
        smfcn = pow ((((sm / pw) - limpar) / (1.0 - limpar)), exp);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::exponential_moisturefactor(const double sm, const double pw, const double limpar, const double exp)@@@WQ_Soil_NPCcycling.cpp>");
    return smfcn;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::exponential_moisturefactor(const double sm, const double pw, const double limpar, const double exp)@@@WQ_Soil_NPCcycling.cpp>");
}
double ClassWQ_SoilBGC :: halfsatconcfactor (const double conc, const double par)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::halfsatconcfactor(const double conc, const double par)@@@WQ_Soil_NPCcycling.cpp>");
    double fcn;
    fcn = conc / (conc + par);

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::halfsatconcfactor(const double conc, const double par)@@@WQ_Soil_NPCcycling.cpp>");
    return fcn;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::halfsatconcfactor(const double conc, const double par)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: retention_pool (long n, long hh, double ** pool, double * sink)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::retention_pool(long n, long hh, double ** pool, double * sink)@@@WQ_Soil_NPCcycling.cpp>");
    double a;
    for (long k = 0; k < n; ++ k) {
        a = pool [k] [hh] - sink [k];
        if (a >= 0.0)
        {
            pool [k] [hh] = a;
        }

        else
        {
            sink [k] = pool [k] [hh];
            pool [k] [hh] = 0.0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::retention_pool(long n, long hh, double ** pool, double * sink)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: retention_pool (long n, double * pool, double * sink)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::retention_pool(long n, double * pool, double * sink)@@@WQ_Soil_NPCcycling.cpp>");
    double a;
    for (long k = 0; k < n; ++ k) {
        a = pool [k] - sink [k];
        if (a >= 0.0)
        {
            pool [k] = a;
        }

        else
        {
            sink [k] = pool [k];
            pool [k] = 0.0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::retention_pool(long n, double * pool, double * sink)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: retention_pool (double & pool, double & sink)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::retention_pool(double & pool, double & sink)@@@WQ_Soil_NPCcycling.cpp>");
    double a = pool - sink;
    if (a >= 0.0)
    {
        pool = a;
    }

    else
    {
        sink = pool;
        pool = 0.0f;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::retention_pool(double & pool, double & sink)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: production_pool (long n, long hh, double ** pool, const double source [] [2])
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::production_pool(long n, long hh, double ** pool, const double source [] [2])@@@WQ_Soil_NPCcycling.cpp>");
    for (long kk = 0; kk < maxsoillayers; ++ kk)
        pool [kk] [hh] = pool [kk] [hh] + source [kk] [n];
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::production_pool(long n, long hh, double ** pool, const double source [] [2])@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: production_pool (long n, long hh, double ** pool, const double * source)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::production_pool(long n, long hh, double ** pool, const double * source)@@@WQ_Soil_NPCcycling.cpp>");
    for (long kk = 0; kk < n; ++ kk)
        pool [kk] [hh] = pool [kk] [hh] + source [kk];
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::production_pool(long n, long hh, double ** pool, const double * source)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: production_pool (long n, double * pool, const double source)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::production_pool(long n, double * pool, const double source)@@@WQ_Soil_NPCcycling.cpp>");
    for (long kk = 0; kk < n; ++ kk)
        pool [kk] = pool [kk] + source;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::production_pool(long n, double * pool, const double source)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: production_pool (long n, double pool, const double source)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::production_pool(long n, double pool, const double source)@@@WQ_Soil_NPCcycling.cpp>");
    pool = pool + source;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::production_pool(long n, double pool, const double source)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: new_concentration (const double pool, const double vol, double * conc)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::new_concentration(const double pool, const double vol, double * conc)@@@WQ_Soil_NPCcycling.cpp>");
    if (vol > 0.0)
    {
        * conc = pool / vol;
    }

    else
    {
        * conc = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::new_concentration(const double pool, const double vol, double * conc)@@@WQ_Soil_NPCcycling.cpp>");
}
double ClassWQ_SoilBGC :: SUM (double X [maxsoillayers] [2], long part)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::SUM(double X [maxsoillayers] [2], long part)@@@WQ_Soil_NPCcycling.cpp>");
    double sum = 0.0;
    for (long ii = 0; ii < maxsoillayers; ++ ii)
        sum += X [ii] [part];

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::SUM(double X [maxsoillayers] [2], long part)@@@WQ_Soil_NPCcycling.cpp>");
    return sum;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::SUM(double X [maxsoillayers] [2], long part)@@@WQ_Soil_NPCcycling.cpp>");
}
double ClassWQ_SoilBGC :: SUM (double * X)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::SUM(double * X)@@@WQ_Soil_NPCcycling.cpp>");
    double sum = 0.0;
    for (long ii = 0; ii < maxsoillayers; ++ ii)
        sum += X [ii];

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::SUM(double * X)@@@WQ_Soil_NPCcycling.cpp>");
    return sum;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::SUM(double * X)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: runoff_pp_by_erosion ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::runoff_pp_by_erosion()@@@WQ_Soil_NPCcycling.cpp>");
    double PPrel;
    double srfilt;
    double erodingflow;
    double erodedP;
    double fracminP;
    double removePP [1];
    double removeHP [1];
    double surfrppmass;
    double newppconc;
    PPrel = 0.0f;
    srfilt = 0.0f;
    erodingflow = 0.0f;
    erodedP = 0.0f;
    fracminP = 0.0f;
    surfrppmass = 0.0f;
    newppconc = 0.0f;
    soil_runoff_cWQ_lay [i_pp] [hh] = 0.0f;
    calculate_erosion (erodedP);
    erodingflow = soil_runoff [hh];
    calculate_transport (erodingflow, erodedP);
    if (soil_runoff [hh] > minFlow_WQ)
    {
        srfilt = 1;
        surfrppmass = srfilt * erodedP / erodingflow;
        removePP [0] = soil_runoff [hh] * surfrppmass * fracminP;
        removeHP [0] = soil_runoff [hh] * surfrppmass * (1 - fracminP);
        retention_pool (surfsoil_solub_mWQ_lay [i_pp] [hh], removePP [0]);
        retention_pool (surfsoil_refractoryP_mWQ [hh], removeHP [0]);
        PPrelpool [hh] = removePP [0] + removeHP [0];
        PPrel = std :: fmin (PPrelpool [hh], PPrelpool [hh] * soil_runoff [hh] / pow (pprelmax, pprelexp));
        PPrelpool [hh] = PPrelpool [hh] - PPrel;
        newppconc = PPrel / soil_runoff [hh];
        soil_runoff_cWQ_lay [i_pp] [hh] = newppconc;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::runoff_pp_by_erosion()@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: calculate_erosion (double & erodedP)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::calculate_erosion(double & erodedP)@@@WQ_Soil_NPCcycling.cpp>");
    double MobilisedSed, MobilisedP, Rainfall_energy, cropcover, groundcover;
    double intensity;
    double common_cropcover, common_groundcover;
    fracminP [hh] = 0.0f;
    erodedP = 0.0f;
    common_cropcover = 0.0f;
    common_groundcover = 0.0f;
    if (cohesion == 0 || erodibility == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::calculate_erosion(double & erodedP)@@@WQ_Soil_NPCcycling.cpp>");
        return;
    }

    cropcover = ccmax1 [hh];
    groundcover = gcmax1 [hh];
    intensity = 1.0;
    if (snowmelt_int [hh] > 0.0)
    {
        intensity = 0.0;
    }

    MobilisedP = 0.0;
    if (net_rain [hh] > 0.0)
    {
        if (intensity > 0.0)
        {
            if (net_rain [hh] > 5.0 / Global :: Freq)
            {
                Rainfall_energy = 8.95 + 8.44 * log10 (net_rain [hh] * (0.257 + sin (2 * 3.14 * ((dayno - 70.) / 365.)) * 0.09) * 2.0);
            }

            else
            {
                Rainfall_energy = 0.0;
            }

            Rainfall_energy = net_rain [hh] * Rainfall_energy;
            MobilisedSed = Rainfall_energy * (1.0 - common_cropcover) * erodibility [hh];
            MobilisedP = 1.0E-3 * MobilisedSed * ((surfsoil_solub_mWQ_lay [i_pp] [hh] + surfsoil_refractoryP_mWQ [hh]) / (soil_Depth [hh] * bulkdensity));
        }

    }

    if (runoff [hh] > 0.0)
    {
        MobilisedSed = (((runoff [hh] * 365.0) * exp (sreroexp)) * (1.0 - common_groundcover) * (1.0 / (0.5 * cohesion [hh])) * sin (hru_GSL [hh] / 100.)) / 365.0;
        MobilisedP += 1.0E-3 * MobilisedSed * ((surfsoil_solub_mWQ_lay [i_pp] [hh] + surfsoil_refractoryP_mWQ [hh]) / (soil_Depth [hh] * bulkdensity));
    }

    erodedP = MobilisedP;
    fracminP [hh] = surfsoil_solub_mWQ_lay [i_pp] [hh] / (surfsoil_solub_mWQ_lay [i_pp] [hh] + surfsoil_refractoryP_mWQ [hh]);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::calculate_erosion(double & erodedP)@@@WQ_Soil_NPCcycling.cpp>");
}
void ClassWQ_SoilBGC :: calculate_transport (const double flow, double & erodedP)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_SoilBGC::calculate_transport(const double flow, double & erodedP)@@@WQ_Soil_NPCcycling.cpp>");
    double transportfactor;
    double enrichment;
    double max = 4.0;
    double stab = 1.5;
    double flowstab = 4.0;
    double trans1 = 4.0;
    double trans2 = 1.3;
    if (flow > 0.0)
    {
        if (flow > flowstab)
        {
            enrichment = stab;
        }

        else
        {
            enrichment = max - (max - stab) * flow / flowstab;
        }

    }

    else
    {
        enrichment = 0.0;
    }

    if (flow > 0.0)
    {
        transportfactor = std :: fmin (1.0, flow / pow (trans1, trans2));
    }

    else
    {
        transportfactor = 1.0;
    }

    erodedP = erodedP * transportfactor * enrichment;
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_SoilBGC::calculate_transport(const double flow, double & erodedP)@@@WQ_Soil_NPCcycling.cpp>");
}