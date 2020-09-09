// 11/21/19
//---------------------------------------------------------------------------

//#include "vcl.h"
#pragma hdrstop

#include "NewModules.h"
#include "WQ_CRHM.h"
#include "WQ_Soil_NPCcycling.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM.h"

#include "SnobalDefines.h"
#include <cmath>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

#include "ClassBasin.h" //added by Manishankar Mondal
#include "ClassGlobal.h" //added by Manishankar Mondal
#include "ClassObs.h" //added by Manishankar Mondal
#include "ClassIntcp.h" //added by Manishankar Mondal
#include "Classpbsm.h" //added by Manishankar Mondal
#include "ClassNO_pbsm.h" //added by Manishankar Mondal
#include "Classtsurface.h" //added by Manishankar Mondal 
#include "Classalbedo.h" //added by Manishankar Mondal 
#include "Classnetall.h" //added by Manishankar Mondal 
#include "Classebsm.h" //added by Manishankar Mondal
#include "ClassTs.h" //added by Manishankar Mondal
#include "ClassNeedle.h" //added by Manishankar Mondal
#include "ClassSimpleRichard.h" //added by Manishankar Mondal
#include "Classevap.h" //added by Manishankar Mondal
#include "ClassevapD.h" //added by Manishankar Mondal
#include "Classsbsm.h" //added by Manishankar Mondal
#include "Classcrack.h" //added by Manishankar Mondal
#include "ClassKevin.h" //added by Manishankar Mondal
#include "ClassGreencrack.h" //added by Manishankar Mondal
#include "Classfrostdepth.h" //added by Manishankar Mondal
#include "Classfrozen.h" //added by Manishankar Mondal
#include "ClassNetroute.h" //added by Manishankar Mondal
#include "Classinterception.h" //added by Manishankar Mondal
#include "ClassGreenAmpt.h" //added by Manishankar Mondal
#include "Classalbedoparam.h" //added by Manishankar Mondal
#include "Classalbedoobs.h" //added by Manishankar Mondal
#include "ClassHtobs.h" //added by Manishankar Mondal
#include "ClasspbsmSnobal.h" //added by Manishankar Mondal
#include "ClassalbedoRichard.h" //added by Manishankar Mondal
#include "ClassalbedoBaker.h" //added by Manishankar Mondal
#include "ClassHMSA.h" //added by Manishankar Mondal
#include "Classwalmsley_wind.h" //added by Manishankar Mondal
#include "ClassNetroute_M.h" //added by Manishankar Mondal
#include "ClassREWroute2.h" //added by Manishankar Mondal
#include "ClassLongVt.h" //added by Manishankar Mondal
#include "Classpbsm_M.h" //added by Manishankar Mondal
#include "ClassNetroute_D.h" //added by Manishankar Mondal
#include "ClassNetroute_M_D.h" //added by Manishankar Mondal
#include "ClassSetSoil.h" //added by Manishankar Mondal
#include "ClassVolumetric.h" //added by Manishankar Mondal
#include "ClassAnnan.h" //added by Manishankar Mondal
#include "Classcalcsun.h" //added by Manishankar Mondal
#include "ClassObstoPar.h" //added by Manishankar Mondal
#include "ClassPrairieInfil.h" //added by Manishankar Mondal
#include "ClassCRHMCanopy.h" //added by Manishankar Mondal
#include "ClassPSPnew.h" //added by Manishankar Mondal
#include "Classbrushintcp.h" //added by Manishankar Mondal
#include "ClassAyers.h" //added by Manishankar Mondal
#include "ClassSlope_Qsi.h" //added by Manishankar Mondal
#include "ClassfrozenAyers.h" //added by Manishankar Mondal
#include "ClassSoil.h" //added by Manishankar Mondal
#include "Classevap_Resist.h" //added by Manishankar Mondal
#include "ClassevapD_Resist.h" //added by Manishankar Mondal
#include "ClassShutWall.h" //added by Manishankar Mondal
#include "ClassShutWallD.h" //added by Manishankar Mondal
#include "ClassIceBulb.h" //added by Manishankar Mondal
#include "Classlake.h" //added by Manishankar Mondal
#include "ClassalbedoWinstral.h" //added by Manishankar Mondal
#include "ClassK_Estimate.h" //added by Manishankar Mondal
#include "ClassevapX.h" //added by Manishankar Mondal
#include "Class3D_param.h" //added by Manishankar Mondal
#include "ClassMeltRunoff_Lag.h" //added by Manishankar Mondal
#include "ClassMeltRunoff_Kstorage.h" //added by Manishankar Mondal
#include "ClassREWroute.h" //added by Manishankar Mondal
#include "ClassXG.h" //added by Manishankar Mondal
#include "Classcontribution.h" //added by Manishankar Mondal
#include "ClassSoilX.h" //added by Manishankar Mondal
#include "ClassMod_Exec.h" //added by Manishankar Mondal
#include "ClassFlowInSnow.h" //added by Manishankar Mondal
#include "ClassSoilDS.h" //added by Manishankar Mondal
#include "Classalbedoobs2.h" //added by Manishankar Mondal
#include "Classwinter_meltflag.h" //added by Manishankar Mondal
#include "Class_z_s_rho.h" //added by Manishankar Mondal
#include "Classqmelt.h" //added by Manishankar Mondal
#include "Classquinton.h" //added by Manishankar Mondal
#include "Classqdrift.h" //added by Manishankar Mondal
#include "ClassXGAyers.h" //added by Manishankar Mondal
#include "ClassCRHMCanopyClearing.h" //added by Manishankar Mondal
#include "ClassCRHMCanopyClearingGap.h" //added by Manishankar Mondal
#include "ClassREWroute_stream.h" //added by Manishankar Mondal
#include "ClassICEflow.h" //added by Manishankar Mondal
#include "Classglacier.h" //added by Manishankar Mondal
#include "Classglacier_debris.h" //added by Manishankar Mondal
#include "ClassSWEslope.h" //added by Manishankar Mondal
#include "ClassTestSparse.h" //added by Manishankar Mondal
#include "ClassGrow_Crop.h" //added by Manishankar Mondal



//---------------------------------------------------------------------------

#pragma package(smart_init)

#define numsubstances 5

#ifndef M_PI
#define M_PI   3.14159265358979323846
#endif



using namespace std;
using namespace CRHM;



const long i_no3n = 0; // inorganic nitrogen
const long i_don = 1; // organic nitrogen
const long i_srp = 2; // soluble (reactive) phosphorus, i.e. phosphate
const long i_pp = 3; // particulate phosphorus
const long i_oc = 4; // (dissolved) organic carbon

extern double xLimit;
extern long lLimit;

Administer DLLModules("08/25/08", "Modules_New");
bool RELEASE = false;

void MoveModulesToGlobal(string DLLName){

  DLLModules.AddModule(new Classshared("Shared", "10/25/10", CRHM::CUSTOM)); // essential for parameter screen
  DLLModules.AddModule(new ClassNOP("NOP", "05/20/16", CRHM::ADVANCE)); // essential for parameter screen
  DLLModules.AddModule(new Classbasin("basin", "02/24/12", CRHM::BASIC));
  DLLModules.AddModule(new Classglobal("global", "04/19/13", CRHM::BASIC));
  DLLModules.AddModule(new Classobs("obs", "04/17/18", CRHM::BASIC));
  DLLModules.AddModule(new Classintcp("intcp", "02/24/15", CRHM::BASIC));
  DLLModules.AddModule(new ClassGrow_Crop("Grow_Crop", "04/04/15", CRHM::ADVANCE));

  DLLModules.AddModule(new Classcalcsun("calcsun", "10/01/13", CRHM::BASIC));

  DLLModules.AddModule(new ClassNO_pbsm("NO_pbsm", "11/15/06", CRHM::ADVANCE));
  DLLModules.AddModule(new Classpbsm("pbsm", "11/20/17", CRHM::BASIC));
  DLLModules.AddModule(new Classsbsm("sbsm", "10/21/09", CRHM::ADVANCE));

  DLLModules.AddModule(new ClassAnnan("Annandale", "07/14/11", CRHM::ADVANCE));

  DLLModules.AddModule(new Classebsm("ebsm", "01/18/16", CRHM::BASIC));

  DLLModules.AddModule(new ClassLongVt("longVt", "02/10/16", CRHM::ADVANCE));

  DLLModules.AddModule(new ClassSlope_Qsi("Slope_Qsi", "07/14/11", CRHM::ADVANCE));

  DLLModules.AddModule(new Classalbedo("albedo", "08/11/11", CRHM::BASIC));
  DLLModules.AddModule(new Classnetall("netall", "03/22/16", CRHM::BASIC));
  DLLModules.AddModule(new Classevap("evap", "07/17/19", CRHM::BASIC));
  DLLModules.AddModule(new ClassevapD("evapD", "11/04/09", CRHM::ADVANCE));
  DLLModules.AddModule(new Classevap_Resist("evap_Resist", "11/21/16", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassevapD_Resist("evapD_Resist", "09/08/09", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassShutWall("ShuttleWallace", "10/05/06", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassShutWallD("ShuttleWallaceD", "10/05/06", CRHM::ADVANCE));

  DLLModules.AddModule(new Classcrack("crack", "09/03/08", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassPrairieInfil("PrairieInfiltration", "03/22/13", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassAyers("Ayers", "01/11/17", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassGreencrack("Greencrack", "03/22/13", CRHM::BASIC));
  DLLModules.AddModule(new ClassGreenAmpt("GreenAmpt", "03/29/10", CRHM::ADVANCE));
  DLLModules.AddModule(new Classfrozen("frozen", "08/03/17", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassfrozenAyers("frozenAyers", "08/02/16", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassSoil("Soil", "02/01/19", CRHM::BASIC));
  DLLModules.AddModule(new ClassevapX("evapX", "12/18/12", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassSoilX("SoilX", "11/28/17", CRHM::ADVANCE)); // nlay >= 2 check added
  DLLModules.AddModule(new ClassSoilDS("SoilDetention", "11/28/17", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassSoilPrairie("SoilPrairie", "11/29/19", CRHM::PROTO)); // prototype wetlands
  DLLModules.AddModule(new Classglacier("glacier", "03/12/19", CRHM::ADVANCE));
  DLLModules.AddModule(new Classglacier_debris("glacier_debris", "11/22/19", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassGlacier_debris_cover("Glacier_debris_cover", "10/17/19", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassSWEslope("SWESlope", "11/01/17", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassICEflow("ICEflow", "12/31/18", CRHM::ADVANCE));

  DLLModules.AddModule(new ClassNetroute("Netroute", "06/20/18", CRHM::BASIC));
  DLLModules.AddModule(new ClassNetroute_D("Netroute_D", "06/20/18", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassNetroute_M("Netroute_M", "06/20/18", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassNetroute_M_D("Netroute_M_D", "10/26/18", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassREWroute("REW_route", "06/19/18", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassREWroute_stream("REW_route_stream", "07/09/18", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassREWroute2("REW_route2", "06/19/18", CRHM::ADVANCE));

  DLLModules.AddModule(new ClassSnobalCRHM("SnobalCRHM", "11/21/16", CRHM::ADVANCE));
  DLLModules.AddModule(new ClasspbsmSnobal("pbsmSnobal", "01/05/17", CRHM::ADVANCE));

  DLLModules.AddModule(new ClassCRHMCanopy("Canopy", "06/14/17", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassCRHMCanopyClearing("CanopyClearing", "04/05/19", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassCRHMCanopyClearingGap("CanopyClearingGap", "04/05/19", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassNeedle("NeedleLeaf", "07/19/11", CRHM::ADVANCE));
  DLLModules.AddModule(new Classwalmsley_wind("walmsley_wind", "07/30/08", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassXG("XG", "10/03/17", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassXGAyers("XGAyers", "05/19/17", CRHM::PROTO));

  DLLModules.AddModule(new ClassSetSoil("SetSoil", "10/21/09", CRHM::ADVANCE));
  DLLModules.AddModule(new ClassVolumetric("Volumetric", "05/30/19", CRHM::ADVANCE));
  DLLModules.AddModule(new Classtsurface("tsurface", "01/15/19", CRHM::PROTO));

  DLLModules.AddModule(new Classalbedoparam("albedo_param", "11/22/05", CRHM::SUPPORT));
  DLLModules.AddModule(new Classalbedoobs("albedo_obs", "11/22/05", CRHM::SUPPORT));
  DLLModules.AddModule(new ClassalbedoRichard("albedo_Richard", "03/19/15", CRHM::SUPPORT));
  DLLModules.AddModule(new ClassalbedoBaker("albedo_Baker", "03/19/15", CRHM::SUPPORT));
  DLLModules.AddModule(new ClassalbedoWinstral("albedo_Winstral", "03/19/15", CRHM::SUPPORT));
  DLLModules.AddModule(new ClassHtobs("Ht_obs", "12/02/09", CRHM::SUPPORT));
  DLLModules.AddModule(new ClassObstoPar("obs_par", "07/19/10", CRHM::SUPPORT));

  DLLModules.AddModule(new Classfrostdepth("frostdepth", "08/11/11", CRHM::CUSTOM));

  DLLModules.AddModule(new Classqmelt("Qmelt", "03/31/16", CRHM::CUSTOM));
  DLLModules.AddModule(new Classquinton("Quinton", "03/31/16", CRHM::CUSTOM));
  DLLModules.AddModule(new Classqdrift("Qdrift", "03/31/16", CRHM::CUSTOM));

  DLLModules.AddModule(new ClassSimpleRichard("SimpleSnow", "03/24/06", CRHM::CUSTOM));
  DLLModules.AddModule(new ClassKevin("Kevin", "08/11/11", CRHM::OBSOL));
  DLLModules.AddModule(new ClassTs("Tsnow", "01/15/13", CRHM::CUSTOM));
  DLLModules.AddModule(new ClassK_Estimate("K_Estimate", "01/16/18", CRHM::ADVANCE)); // fixed 'put' descriptions

  DLLModules.AddModule(new ClassSnobalX("Snobal", "02/03/16", CRHM::OBSOL));
  DLLModules.AddModule(new Classinterception("interception", "11/03/06", CRHM::OBSOL));
  DLLModules.AddModule(new Classlake("lake_evap", "07/04/12", CRHM::ADVANCE));

  if(!RELEASE){
    DLLModules.AddModule(new ClassTestSparse("TestSparse", "05/29/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassHMSA("HMSA", "01/16/13", CRHM::PROTO));
    DLLModules.AddModule(new ClassIceBulb("IceBulb", "11/20/17", CRHM::PROTO));
    DLLModules.AddModule(new Class3D_param("3D_param", "03/18/13", CRHM::PROTO));
    DLLModules.AddModule(new ClassMeltRunoff_Lag("MeltRunoff_Lag", "09/03/13", CRHM::PROTO));
    DLLModules.AddModule(new ClassMeltRunoff_Kstorage("MeltRunoff_Kstorage", "09/03/13", CRHM::PROTO));
    DLLModules.AddModule(new ClassFlowInSnow("FlowInSnow", "08/19/14", CRHM::PROTO));
    DLLModules.AddModule(new ClassMod_Exec("Exec", "02/26/14", CRHM::PROTO));
    DLLModules.AddModule(new Classcontribution("contribution", "01/29/14", CRHM::PROTO));
    DLLModules.AddModule(new Classalbedoobs2("albedo_obs2", "11/18/14", CRHM::PROTO));
    DLLModules.AddModule(new Classwinter_meltflag("winter_meltflag", "02/12/15", CRHM::PROTO));
    DLLModules.AddModule(new Class_z_s_rho("z_s_and_rho", "04/09/15", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_Test_Hype("WQ_Test", "05/01/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_Substitute_Hype("WQ_Soil_BGC_substitute", "12/11/18", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_Soil("WQ_Soil", "10/17/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_Netroute("WQ_Netroute", "08/26/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_Netroute_M_D("WQ_Netroute_M_D", "09/11/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_pbsm("WQ_pbsm", "01/21/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_pbsmSnobal("WQ_pbsmSnobal", "04/26/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_SoilBGC("WQ_Soil_BGC", "11/01/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_mass_conc("WQ_mass_to_conc", "12/01/18", CRHM::PROTO));
    DLLModules.AddModule(new ClassGrow_crops_annually("Grow_crops_annually", "06/05/19", CRHM::PROTO));
    DLLModules.AddModule(new ClassWQ_Gen_Mass_Var_Netroute("WQ_Gen_Mass_Var_Netroute", "06/20/19", CRHM::ADVANCE));
    DLLModules.AddModule(new ClassWQ_Gen_Mass_Var_Soil("WQ_Gen_Mass_Var_Soil", "06/20/19", CRHM::ADVANCE));
    DLLModules.AddModule(new Classlapse_rate_Monthly_Mod("lapse_rate_Monthly_Mod", "11/22/19", CRHM::ADVANCE));
    DLLModules.AddModule(new ClassGlacier_melt_debris_cover_estimate_Mod("Glacier_melt_debris_cover_estimate_Mod", "11/22/19", CRHM::ADVANCE));
  }
                                                             
  DLLModules.AddModel("Prairie using sunshine hours or Qsi generated sunshine hours", "basin, global, obs, calcsun, intcp, pbsm, albedo, netall, ebsm, evap, PrairieInfiltration, Soil, Netroute");
  DLLModules.AddModel("Prairie slope using Qsi generated sunshine hours", "basin, global, obs, Slope_Qsi#3, intcp, calcsun#1, netall, pbsm, albedo, ebsm, evap, PrairieInfiltration, Soil, Netroute");
  DLLModules.AddModel("Prairie Annandale", "basin, global, obs, Annandale#1, intcp, netall, pbsm, albedo, ebsm, evap, PrairieInfiltration, Soil, Netroute");
  DLLModules.AddModel("Canopy/Clearing using Qsi", "basin, global, obs, calcsun, longVt, netall, evap, CanopyClearing#1, pbsm, albedo, ebsm#1, frozenAyers, Soil, Netroute");
  DLLModules.AddModel("Canopy/Clearing slope using Qsi", "basin, global, obs, Slope_Qsi#1, longVt, calcsun#3, netall, evap, CanopyClearing#3, pbsm, albedo, ebsm#1, frozenAyers, Soil, Netroute");
  DLLModules.AddModel("Canopy/Clearing using Annandale(Slope)", "basin, global, obs, Annandale#1, longVt#2, netall, evap, CanopyClearing#3, pbsm, albedo, ebsm#1, frozenAyers, Soil, Netroute");
  DLLModules.AddModel("Canopy/Clearing using Annandale(horizontal)", "basin, global, obs, Annandale#1, longVt#2, netall, evap, CanopyClearing#4, pbsm, albedo, ebsm#1, frozenAyers, Soil, Netroute");
  DLLModules.AddModel("NeedleLeaf with walmsley_wind", "basin, global, obs, calcsun, intcp, walmsley_wind, longVt, netall, albedo, pbsm#1, NeedleLeaf#1, evap, ebsm#1, PrairieInfiltration, Soil, Netroute");
  DLLModules.AddModel("Prairie using Qsi and Snobal", "basin, global, obs, calcsun, intcp, longVt, netall, pbsmSnobal, albedo, evap, SnobalCRHM#2, PrairieInfiltration, Soil, Netroute");
  DLLModules.AddModel("Prairie using Annandale and Snobal", "basin, global, obs, Annandale#1, intcp, longVt, netall, pbsmSnobal, albedo, evap, SnobalCRHM#2, PrairieInfiltration, Soil, Netroute");
  DLLModules.AddModel("Canopy/Clearing using Annandale(Slope) and Snobal", "basin, global, obs, Annandale#1, longVt#2, netall, evap, CanopyClearing#3, pbsmSnobal, albedo, SnobalCRHM#2, frozenAyers, Soil, Netroute");

  DLLModules.LoadCRHM(DLLName);

}
// All these at 0% saturation from Chow pg 115 except fcap
// Wilt = Chow's por-eff por, fcap from Floods in Canada
// Soil curves of form K = Ks / (A*Psi^3 + 1 )
// data from Clapp and Hornberger (1978). Original table appears In Dingman (2002)
// porosity/air entry tension/pore size distribution
// AVAIL ->     1 - Sand, at pcts < 0.25, limited to 0.25*pcts*avail_evap.
//              2 - loam, at pcts < 0.5,  limited to 0.5*pcts*avail_evap.
//              3 - clay, at pcts < 0.67 && pcts > 0.33, limited to pcts*avail_evap and
//                        at pcts < 0.33 limited to 0.5*pcts*avail_evap
//              4 organic, unlimted availability
//              where pcts = (soil moist)/(soil moist max)
// psi, k(mm/h), wilt, fcap,  porG, porE, air entry, pore size ?? b, AVAIL
// {PSI,  KSAT,  WILT,  FCAP, PORG,   PORE,     AIRENT, PORESZ ?? b, AVAIL}
//  mm    mm/h


Classshared* Classshared::klone(string name) const{
  return new Classshared(name);
}

void Classshared::decl(void) {

  Description = "'System module only. NEVER use!'";

}

void Classshared::init(void) {

}

ClassNOP* ClassNOP::klone(string name) const{
  return new ClassNOP(name);
}

void ClassNOP::decl(void) {

  Description = "'NO operation module. Use only in macro declstruct as filler.'";

}

void ClassNOP::init(void) {

}

void ClassNOP::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessage(hh, string("'" + Name + " (NOP)'").c_str(), BLANK);
  }
  LogDebug(" ");
}


ClassSnobalX* ClassSnobalX::klone(string name) const{
  return new ClassSnobalX(name);
}

void ClassSnobalX::decl(void) {

    Description = "'A model using the energy balance to calculate snowmelt (Marks, et. al (1997)). Non standard module.'";

    declstatvar("layer_count", NHRU, "number of layers in snowcover: 0, 1, or 2", "()", &layer_count);
    declstatvar("isothermal", NHRU, "melting: 0/1", "()", &isothermal);
    declstatvar("snowcover", NHRU, "snow on gnd at start of current timestep: 0/1", "()", &snowcover);

    declvar("R_n", NHRU, "net allwave radiation", "(W/m^2)", &R_n);
    declvar("H", NHRU, "sensible heat xfr", "(W/m^2)", &H);
    declvar("L_v_E", NHRU, "latent heat xfr", "(W/m^2)", &L_v_E);
    declvar("G", NHRU, "heat xfr by conduction & diffusion from soil to snowcover", "(W/m^2)", &G);
    declvar("M", NHRU, "advected heat from precip", "(W/m^2)", &M);
    declvar("delta_Q", NHRU, "change in snowcover's energy", "(W/m^2)", &delta_Q);
    declvar("G_0", NHRU, "heat xfr by conduction & diffusion from soil or lower layer to active layer", "(W/m^2)", &G_0);
    declvar("delta_Q_0", NHRU, "change in active layer's energy", "(W/m^2)", &delta_Q_0);

    declstatvar("cc_s_0", NHRU, "active layer cold content", "(J/m^2)", &cc_s_0);
    declstatvar("cc_s_l", NHRU, "lower layer cold content", "(J/m^2)", &cc_s_l);
    declstatvar("cc_s", NHRU, "snowcover's cold content", "(J/m^2)", &cc_s);
    declstatvar("h2o", NHRU, "liquid h2o content as specific mass", "(kg/m^2)", &h2o);

    decllocal("E_s", NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2)", &E_s);
    decllocal("E", NHRU, "mass flux by evap into air from active layer", "(kg/m^2*s)", &E);
    decllocal("E_s_0", NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0);
    decllocal("E_s_l", NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l);
    decllocal("melt", NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2)", &melt);
    declvar("ro_predict", NHRU, "predicted specific runoff", "(m/s)", &ro_predict);
    declvar("h2o_total", NHRU, "total liquid h2o: includes h2o in snowcover, melt, and rainfall", "(kg/m^2)", &h2o_total);

    decldiag("E_s_int", NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2*int)", &E_s_int);
    decldiag("E_int", NHRU, "mass flux by evap into air from active layer", "(kg/m^2*int)", &E_int);
    decldiag("E_s_0_int", NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0_int);
    decldiag("E_s_l_int", NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l_int);
    declvar("melt_direct_int", NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2*int)", &melt_direct_int);
    declstatvar("sum", NHRU, "sum of SWE, snowmelt, drift, subl", "(mm)", &sum);
    declvar("snowmelt_int", NHRU, "snow melt", "(kg/m^2*int)", &snowmelt_int);
    declvar("snowmeltD", NHRU, "daily snow melt", "(mm/d)", &snowmeltD);
    declvar("cumsnowmelt", NHRU, "cumulative melt", "(mm)", &cumsnowmelt);

    declstatvar("z_s_0", NHRU, "active layer depth", "(m)", &z_s_0);
    declstatvar("z_s_l", NHRU, "lower layer depth", "(m)", &z_s_l);
    declstatvar("z_s", NHRU, "total snowcover thickness", "(m)", &z_s);

    declstatvar("rho", NHRU, "average snowcover density", "(kg/m^3)", &rho);

    declstatvar("m_s_0", NHRU, "active layer specific mass", "(kg/m^2)", &m_s_0);
    declstatvar("m_s_l", NHRU, "lower layer specific mass", "(kg/m^2)", &m_s_l);
    declstatvar("SWE", NHRU, "snowcover's specific mass", "(kg/m^2)", &m_s);

    declstatvar("T_s_0", NHRU, "active snow layer temp", "(Â°C)", &T_s_0);
    declstatvar("T_s_l", NHRU, "lower layer temp", "(Â°C)", &T_s_l);
    declstatvar("T_s", NHRU, "average snowcover temp", "(Â°C)", &T_s);

    declvar("h2o_sat", NHRU, "fraction of liquid H2O saturation (0 to 1.0)", "()", &h2o_sat);
    declvar("h2o_vol", NHRU, "liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &h2o_vol);
    declvar("h2o_max", NHRU, "max liquid h2o content as specific mass", "(kg/m^2)", &h2o_max);

    declvar("z_snow", NHRU, "depth of snow in precip", "(m)", &z_snow);
    declvar("h2o_sat_snow", NHRU, "snowfall's % of liquid H2O saturation", "()", &h2o_sat_snow);

    declvar("precip_now", NHRU, "precipitation occur for current timestep - 0/1", "()", &precip_now);
    declvar("T_rain", NHRU, "rain's temp", "(Â°C)", &T_rain);
    declvar("T_snow", NHRU, "snowfall's temp", "(Â°C)", &T_snow);

    decllocal("S_n_L",  NHRU, "net solar radiation", "(W/m^2)", &S_n);
    decllocal("I_lw_L", NHRU, "incoming longwave (thermal) rad ", "(W/m^2)", &I_lw);
    decllocal("T_a_L",  NHRU, "air temp", "(Â°C)", &T_a);
    decllocal("e_a_L",  NHRU, "vapor pressure", "(Pa)", &e_a);
    decllocal("u_L",    NHRU, "wind speed", "(m/s)", &u);
    decllocal("T_g_L",  NHRU, "soil temp at depth z_g", "(Â°C)", &T_g); // should be K but causes unit fault

    decllocal("m_precip_L", NHRU, "specific mass of total precip", "(kg/m^2)", &m_precip);
    decllocal("m_rain_L", NHRU, "specific mass of rain in precip", "(kg/m^2)", &m_rain);
    decllocal("m_snow_L", NHRU, "specific mass in snow in precip", "(kg/m^2)", &m_snow);
    decllocal("m_drift_L", NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_drift);
    decllocal("m_subl_L", NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_subl);
    decllocal("rho_snow_L", NHRU, "density of snowfall", "(kg/m^2)", &rho_snow);
    decllocal("T_pp_L", NHRU, "precip temp", "(Â°C)", &T_pp);

    decllocal("P_a", NHRU, "air pressure", "(Pa)", &P_a);

    decllocal("m_precip_cum", NHRU, "cumulative specific mass of total precip", "(kg/m^2)", &m_precip_cum);
    decllocal("m_rain_cum", NHRU, "cumulative specific mass of total rain", "(kg/m^2)", &m_rain_cum);
    decllocal("m_snow_cum", NHRU, "cumulative specific mass of total snow", "(kg/m^2)", &m_snow_cum);
    decllocal("m_drift_cum", NHRU, "cumulative specific mass of total drifting snow", "(kg/m^2)", &m_drift_cum);
    decllocal("m_subl_cum", NHRU, "cumulative specific mass of total sublimation", "(kg/m^2)", &m_subl_cum);
    decllocal("E_s_cum", NHRU, "cumulative mass flux by evap into air from active layer", "(kg/m^2)", &E_s_cum);
    decllocal("melt_direct_cum", NHRU, "cumulative melt when SWE < threshold melt", "(kg/m^2)", &melt_direct_cum);

    decllocal("stop_no_snow", NHRU, "snow flag", "()", &stop_no_snow);

    decldiagparam("relative_hts", NHRU, "[0]", "0", "1", "1 - measurements heights, z_T and z_u, are relative to snow, i.e. 0 -> use (z_T), 1 -> use (z_T - z_s)", "()", &relative_hts);

    declparam("z_g", NHRU, "[0.01]", "0.1", "1.0", "depth of soil temp meas", "(m)", &z_g);
    declparam("z_u", NHRU, "[1.0]", "0.0", "10.0", "height of wind measurement", "(m)", &z_u);
    declparam("z_T", NHRU, "[1.0]", "0.0", "10.0", "height of air temp & vapor pressure measurement", "(m)", &z_T);
    declparam("z_0", NHRU, "[0.001]", "0.0001", "0.1", "roughness length", "(m)", &z_0);

    declparam("max_z_s_0", NHRU, "[0.1]", "0.0", "0.35", "maximum active layer thickness", "(m)", &max_z_s_0);
    declparam("max_h2o_vol", NHRU, "[0.0001]", "0.0", "0.2", "max liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &max_h2o_vol);

    declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);
    declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);
    declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

    declparam("KT_sand", NHRU, "[0.08]", "0.01", "3.0", "thermal conductivity of wet sand (J/(m sec K)(from Oke, 1978, pg. 38)", "()", &KT_sand);

    declgetvar("*", "hru_S_n", "(W/m^2)", &S_n_X);
    declgetvar("*", "hru_I_lw", "(W/m^2)", &I_lw_X);
    declgetvar("*", "hru_t", "(Â°C)", &T_a_X);
    declgetvar("*", "hru_ea", "(kPa)", &e_a_X);
    declgetvar("*", "hru_u", "(m/s)", &u_X);
    declgetvar("*", "hru_T_g", "(Â°C)", &T_g_X);

    declgetvar("*", "net_p", "(kg/m^2)", &m_precip_X);
    declgetvar("*", "net_rain", "(kg/m^2)", &m_rain_X);
    declgetvar("*", "net_snow", "(kg/m^2)", &m_snow_X);
    declgetvar("*", "hru_drift", "(kg/m^2)", &m_drift_X);
    declgetvar("*", "hru_subl", "(kg/m^2)", &m_subl_X);
    declgetvar("*", "hru_rho_snow", "(kg/m^3)", &rho_snow_X);
    declgetvar("*", "hru_T_pp", "(Â°C)", &T_pp_X);
}


void ClassSnobalX::init(void) {
  ClassSnobalBase::init();
}

void ClassSnobalX::run(void) { // executed every interval

  if(getstep() == 1){ // beginning of model run. Handle initial state file problems
    for (hh = 0; chkStruct(); ++hh) {
      if(m_s[hh] <= 0)
        layer_count[hh] = 0;
      else{
        rho[hh] = m_s[hh]/z_s[hh];
        if(layer_count[hh] <= 0)
          layer_count[hh] = 1;
      }
    }
  }

  for (hh = 0; chkStruct(); ++hh) {

    T_s[hh]    += CRHM_constants::Tm; // temperatures inside Snobal model are Â°K
    T_s_0[hh]  += CRHM_constants::Tm;
    T_s_l[hh]  += CRHM_constants::Tm;

    T_snow[hh] += CRHM_constants::Tm;
    T_rain[hh] += CRHM_constants::Tm;

    input_rec2[hh].S_n  = S_n_X[hh];
    input_rec2[hh].I_lw = I_lw_X[hh];
    input_rec2[hh].T_a  = T_a_X[hh] + CRHM_constants::Tm;
    input_rec2[hh].e_a  = e_a_X[hh]*1000;
    input_rec2[hh].u    = u_X[hh];
    input_rec2[hh].T_g  = T_g_X[hh] + CRHM_constants::Tm;

    m_precip[hh] = m_precip_X[hh];
    m_snow[hh]   = m_snow_X[hh];
    m_drift[hh]  = m_drift_X[hh];
    m_subl[hh]  = m_subl_X[hh];
    m_rain[hh]   = m_rain_X[hh];
    rho_snow[hh] = rho_snow_X[hh];

    m_precip_cum[hh] += m_precip[hh];
    m_rain_cum[hh] += m_rain[hh];
    m_snow_cum[hh] += m_snow[hh];
    m_drift_cum[hh] += m_drift[hh];
    m_subl_cum[hh] += m_subl[hh];

    if(m_snow[hh] > 0.0){
      if (rho_snow[hh] <= 0.0){
        CRHMException TExcept("Snobal: rho_snow is <= 0.0 with snow > 0.0", TERMINATE);
        LogError(TExcept);
      }
      z_snow[hh]   = m_snow[hh] / rho_snow[hh];
    }
    else
      z_snow[hh]   = 0.0;

    T_pp[hh]     = T_pp_X[hh] + CRHM_constants::Tm;

// clear interval values

    snowmelt_int[hh] = 0.0;
    melt_direct_int[hh] = 0.0;
    sum[hh] = 0.0;
    E_s_int[hh] = 0.0;
    E_int[hh] = 0.0;
    E_s_0_int[hh] = 0.0;
    E_s_l_int[hh] = 0.0;
    ro_predict[hh] = 0.0;

    long Step = getstep();
    if(getstep() > 1){ // Not first step

      if(m_precip[hh] > 0.0){
        stop_no_snow[hh] = 0;
        precip_now[hh]= true;
      }
      else{
        if(layer_count[hh] == 0)
          stop_no_snow[hh] = 1;
        precip_now[hh]= false;
      }

// process blowing snow event
  _drift();

      do_data_tstep(); // executes Snobal code
    }
    else if(m_precip[hh] > 0.0) {
         CRHMException TExcept("Snobal - cannot handle precipitation during first day of model run", WARNING);
         LogError(TExcept);
    }

    if(Step % Global::Freq == 1)
       snowmeltD[hh] = snowmelt_int[hh];
    else
       snowmeltD[hh] += snowmelt_int[hh];

    input_rec1[hh].S_n  = input_rec2[hh].S_n;
    input_rec1[hh].I_lw = input_rec2[hh].I_lw;
    input_rec1[hh].T_a  = input_rec2[hh].T_a;
    input_rec1[hh].e_a  = input_rec2[hh].e_a;
    input_rec1[hh].u    = input_rec2[hh].u;
    input_rec1[hh].T_g  = input_rec2[hh].T_g;

    E_s_cum[hh] += E_s_int[hh];
    sum[hh] = m_s[hh] + m_drift_cum[hh] + m_subl_cum[hh] + cumsnowmelt[hh] + E_s_cum[hh];
    cumsnowmelt[hh] += snowmelt_int[hh];
    melt_direct_cum[hh] += melt_direct_int[hh];

    T_s[hh]   -= CRHM_constants::Tm; // temperatures outside Snobal model are Â°C
    T_s_0[hh] -= CRHM_constants::Tm;
    T_s_l[hh] -= CRHM_constants::Tm;

    T_snow[hh] -= CRHM_constants::Tm;
    T_rain[hh] -= CRHM_constants::Tm;
  }
}


void ClassSnobalX::finish(bool good) { // only required for local storage and final output

  ClassSnobalBase::finish(good);
}

ClassSnobalCRHM* ClassSnobalCRHM::klone(string name) const{
  return new ClassSnobalCRHM(name);
}

void ClassSnobalCRHM::decl(void) {

    Description = "'A model using the energy balance to calculate snowmelt (Marks, et. al (1997)). Standard CRHM module.' \
                 'use Qsi (W/m^2) and Qli (W/m^2) observations,' \
                 'use variables Qsisn_Var (W/m^2) and Qlisn_Var (W/m^2) from module CanopyClearing.' \
                 'use observation Qsi (W/m^2) and QliVt_Var (W/m^2) from module longVt.' \
                 'use variables QsiS_Var (W/m^2) from Annandale and QliVt_Var (W/m^2) from module longVt.'";

    declstatvar("layer_count", NHRU, "number of layers in snowcover: 0, 1, or 2", "()", &layer_count);
    declstatvar("isothermal", NHRU, "melting: 0/1", "()", &isothermal);
    declstatvar("snowcover", NHRU, "snow on gnd at start of current timestep: 0/1", "()", &snowcover);

    declvar("R_n", NHRU, "net allwave radiation", "(W/m^2)", &R_n);
    declvar("H", NHRU, "sensible heat xfr", "(W/m^2)", &H);
    declvar("L_v_E", NHRU, "latent heat xfr", "(W/m^2)", &L_v_E);
    declvar("G", NHRU, "heat xfr by conduction & diffusion from soil to snowcover", "(W/m^2)", &G);
    declvar("M", NHRU, "advected heat from precip", "(W/m^2)", &M);
    declvar("delta_Q", NHRU, "change in snowcover's energy", "(W/m^2)", &delta_Q);
    declvar("G_0", NHRU, "heat xfr by conduction & diffusion from soil or lower layer to active layer", "(W/m^2)", &G_0);
    declvar("delta_Q_0", NHRU, "change in active layer's energy", "(W/m^2)", &delta_Q_0);

    declstatvar("cc_s_0", NHRU, "active layer cold content", "(J/m^2)", &cc_s_0);
    declstatvar("cc_s_l", NHRU, "lower layer cold content", "(J/m^2)", &cc_s_l);
    declstatvar("cc_s", NHRU, "snowcover's cold content", "(J/m^2)", &cc_s);
    declstatvar("h2o", NHRU, "liquid h2o content as specific mass", "(kg/m^2)", &h2o);

    decllocal("E_s", NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2)", &E_s);
    decllocal("E", NHRU, "mass flux by evap into air from active layer", "(kg/m^2*s)", &E);
    decllocal("E_s_0", NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0);
    decllocal("E_s_l", NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l);
    decllocal("melt", NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2)", &melt);
    declvar("ro_predict", NHRU, "predicted specific runoff", "(m/s)", &ro_predict);
    declvar("h2o_total", NHRU, "total liquid h2o: includes h2o in snowcover, melt, and rainfall", "(kg/m^2)", &h2o_total);

    decldiag("E_s_int", NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2*int)", &E_s_int);
    decldiag("E_int", NHRU, "mass flux by evap into air from active layer", "(kg/m^2*int)", &E_int);
    decldiag("E_s_0_int", NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0_int);
    decldiag("E_s_l_int", NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l_int);
    declvar("melt_direct_int", NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2*int)", &melt_direct_int);
    declvar("sum", NHRU, "sum of SWE, snowmelt, drift, subl", "(mm)", &sum);
    declvar("SWE_change", NHRU, "interval change in SWE", "(mm)", &SWE_change);
    declvar("snowmelt_int", NHRU, "snow melt", "(kg/m^2*int)", &snowmelt_int);
    declvar("snowmeltD", NHRU, "daily snow melt", "(mm/d)", &snowmeltD);
    decllocal("snowmeltD_acc", NHRU, "daily snow melt accumulator", "(mm/d)", &snowmeltD_acc);
    declvar("cumsnowmelt", NHRU, "cumulative melt", "(mm)", &cumsnowmelt);


    declstatvar("z_s_0", NHRU, "active layer depth", "(m)", &z_s_0);
    declstatvar("z_s_l", NHRU, "lower layer depth", "(m)", &z_s_l);
    declstatvar("z_s", NHRU, "total snowcover thickness", "(m)", &z_s);

    declstatvar("rho", NHRU, "average snowcover density", "(kg/m^3)", &rho);

    declstatvar("m_s_0", NHRU, "active layer specific mass", "(kg/m^2)", &m_s_0);
    declstatvar("m_s_l", NHRU, "lower layer specific mass", "(kg/m^2)", &m_s_l);
    declstatvar("SWE", NHRU, "snowcover's specific mass", "(kg/m^2)", &m_s);

    declstatvar("T_s_0", NHRU, "active snow layer temp", "(Â°C)", &T_s_0);
    declstatvar("T_s_l", NHRU, "lower layer temp", "(Â°C)", &T_s_l);
    declstatvar("T_s", NHRU, "average snowcover temp", "(Â°C)", &T_s);

    declstatvar("h2o_sat", NHRU, "fraction of liquid H2O saturation (0 to 1.0)", "()", &h2o_sat);
    declvar("h2o_vol", NHRU, "liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &h2o_vol);
    declvar("h2o_max", NHRU, "max liquid h2o content as specific mass", "(kg/m^2)", &h2o_max);

    declvar("z_snow", NHRU, "depth of snow in precip", "(m)", &z_snow);
    declvar("h2o_sat_snow", NHRU, "snowfall's % of liquid H2O saturation", "()", &h2o_sat_snow);

    declvar("precip_now", NHRU, "precipitation occur for current timestep - 0/1", "()", &precip_now);
    declvar("T_rain", NHRU, "rain's temp", "(Â°C)", &T_rain);
    declvar("T_snow", NHRU, "snowfall's temp", "(Â°C)", &T_snow);

    decllocal("S_n_L",  NHRU, "net solar radiation", "(W/m^2)", &S_n);
    decllocal("I_lw_L", NHRU, "incoming longwave (thermal) rad ", "(W/m^2)", &I_lw);
    decllocal("T_a_L",  NHRU, "air temp", "(Â°C)", &T_a);
    decllocal("e_a_L",  NHRU, "vapor pressure", "(Pa)", &e_a);
    decllocal("u_L",    NHRU, "wind speed", "(m/s)", &u);
    decllocal("T_g_L",  NHRU, "soil temp at depth z_g", "(Â°C)", &T_g);
    decllocal("F_g_L",  NHRU, "soil flux at depth z_g", "(W/m^2)", &F_g);

    decllocal("m_precip_L", NHRU, "specific mass of total precip", "(kg/m^2)", &m_precip);
    declvar  ("rain_on_snow", NHRU, "specific mass of rain in precip", "(kg/m^2)", &m_rain);
    decllocal("m_snow_L", NHRU, "specific mass in snow in precip", "(kg/m^2)", &m_snow);
    decllocal("m_drift_L", NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_drift);
    decllocal("m_subl_L", NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_subl);
    decllocal("rho_snow_L", NHRU, "density of snowfall", "(kg/m^2)", &rho_snow);
    decllocal("T_pp_L", NHRU, "precip temp", "(Â°C)", &T_pp);

    decllocal("P_a", NHRU, "air pressure", "(Pa)", &P_a);

    decllocal("m_precip_cum", NHRU, "cumulative specific mass of total precip", "(kg/m^2)", &m_precip_cum);
    decllocal("m_rain_cum", NHRU, "cumulative specific mass of total rain", "(kg/m^2)", &m_rain_cum);
    decllocal("m_snow_cum", NHRU, "cumulative specific mass of total snow", "(kg/m^2)", &m_snow_cum);
    decllocal("m_drift_cum", NHRU, "cumulative specific mass of total drifting snow", "(kg/m^2)", &m_drift_cum);
    decllocal("m_subl_cum", NHRU, "cumulative specific mass of total sublimation", "(kg/m^2)", &m_subl_cum);
    decllocal("E_s_cum", NHRU, "cumulative mass flux by evap into air from active layer", "(kg/m^2)", &E_s_cum);
    decllocal("melt_direct_cum", NHRU, "cumulative melt when SWE < threshold melt", "(kg/m^2)", &melt_direct_cum);

    decllocal("stop_no_snow", NHRU, "snow flag", "()", &stop_no_snow);
    decllocal("snow_store", NHRU, "accumulates snow till significant", "()", &snow_store);

    decldiagparam("relative_hts", NHRU, "[0]", "0", "1", "1 - measurements heights, z_T and z_u, are relative to snow, i.e. 0 -> use (z_T), 1 -> use (z_T - z_s)", "()", &relative_hts);

    declparam("z_g", NHRU, "[0.01]", "0.1", "1.0", "depth of soil temp meas", "(m)", &z_g);
    declparam("z_u", NHRU, "[1.0]", "0.0", "10.0", "height of wind measurement", "(m)", &z_u);
    declparam("z_T", NHRU, "[1.0]", "0.0", "10.0", "height of air temp & vapor pressure measurement", "(m)", &z_T);
    declparam("z_0", NHRU, "[0.001]", "0.0001", "0.1", "roughness length", "(m)", &z_0);

    declparam("max_z_s_0", NHRU, "[0.1]", "0.0", "0.35", "maximum active layer thickness", "(m)", &max_z_s_0);
    declparam("max_h2o_vol", NHRU, "[0.0001]", "0.0001", "0.2", "max liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &max_h2o_vol);

    declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);
    declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);
    declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);
    declparam("hru_rho_snow", NHRU, "[100]", "50", "1000", "rho of falling snow", "(kg/m^3)", &rho_snow_X);
    declparam("hru_T_g", NHRU, "[-4]", "-50", "50", "ground temperature used when observation T_g not available", "(Â°C)", &T_g_X);
    declparam("hru_F_g", NHRU, "[0]", "-50", "50", "ground flux used when observation F_g not available", "(W/m^2)", &F_g_X);
    declparam("T_g_or_G_flux", NHRU, "[0]", "0", "1", "0 - calculate ground flux from ground temperature, 1 - use ground flux value", "()", &T_g_or_G_flux);

    decldiagparam("rain_soil_snow", NHRU, "[0]", "0", "1", "0 - handle only snow (module Soil handles rain), 1 - handle snow and rain in this module (when SWE > 0.02mm).", "()", &rain_soil_snow);

    declparam("KT_sand", NHRU, "[0.08]", "0.01", "3.0", "thermal conductivity of wet sand (J/(m sec K)(from Oke, 1978, pg. 38)", "()", &KT_sand);

    declgetvar("*", "hru_t", "(Â°C)", &T_a_X);
    declgetvar("*", "hru_t", "(Â°C)", &T_pp_X); // default precipitation temperature to air
    declgetvar("*", "hru_ea", "(kPa)", &e_a_X);
    declgetvar("*", "hru_u", "(m/s)", &u_X);

    declgetvar("*", "net_p", "(kg/m^2)", &m_precip_X);
    declgetvar("*", "net_snow", "(kg/m^2)", &m_snow_X);
    declgetvar("*", "hru_drift", "(kg/m^2)", &m_drift_X);
    declgetvar("*", "hru_subl", "(kg/m^2)", &m_subl_X);
    declgetvar("*", "Albedo", "()", &Albedo);

    declputvar("*", "net_rain", "(kg/m^2)", &m_rain_X);

    declreadobs("T_g", NHRU, "ground temperature", "(Â°C)", &T_g_Obs, HRU_OBS_misc, true);

    declreadobs("F_g", NHRU, "ground flux", "(W/m^2)", &F_g_Obs, HRU_OBS_misc, true);

    variation_set = VARIATION_0 + VARIATION_2;

    declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

    variation_set = VARIATION_0;

    declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);

    variation_set = VARIATION_1;

    declgetvar("*", "Qsisn_Var", "(W/m^2)", &Qsisn_Var);

    declgetvar("*", "Qlisn_Var", "(W/m^2)", &Qlisn_Var);

    variation_set = VARIATION_2 + VARIATION_3;

    declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);

    variation_set = VARIATION_3;

    declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);

    variation_set = VARIATION_ORG;
}

void ClassSnobalCRHM::init(void) {

  ClassSnobalBase::init();
  if(!T_g_Obs){
    CRHMException TExcept(string("'" + Name + " (SnobalCRHM)' ground temperature T_g observation not available using parameter hru_T_g.").c_str(), WARNING);
    LogError(TExcept);
  }

  if(!F_g_Obs){
    CRHMException TExcept(string("'" + Name + " (SnobalCRHM)' ground flux F_g observation not available using parameter hru_F_g.").c_str(), WARNING);
    LogError(TExcept);
  }

  for (hh = 0; chkStruct(); ++hh) {
    snow_store[hh] = 0.0;
    snowmeltD[hh] = 0.0;
  }
}

void ClassSnobalCRHM::run(void) { // executed every interval

  long nstep = getstep() % Global::Freq;

  if(getstep() == 1){ // beginning of model run. Handle initial state file problems
    for (hh = 0; chkStruct(); ++hh) {
      if(m_s[hh] <= 0)
        layer_count[hh] = 0;
      else{
        if(z_s[hh] <= 0.0)
          rho[hh] = 0.0;
        else
          rho[hh] = m_s[hh]/z_s[hh];
          
        if(layer_count[hh] <= 0)
          layer_count[hh] = 1;
      }
    }
  }

  for (hh = 0; chkStruct(); ++hh) {

    T_s[hh]    += CRHM_constants::Tm; // temperatures inside Snobal model are Â°K
    T_s_0[hh]  += CRHM_constants::Tm;
    T_s_l[hh]  += CRHM_constants::Tm;

    T_snow[hh] += CRHM_constants::Tm;
    T_rain[hh] += CRHM_constants::Tm;

    SWE_change[hh] = -m_s[hh];

    switch (variation){
      case VARIATION_ORG:
        input_rec2[hh].S_n  = Qsi[hh]*(1.0 - Albedo[hh]);
        input_rec2[hh].I_lw = Qli[hh];
      break;
      case VARIATION_1:
        input_rec2[hh].S_n  = Qsisn_Var[hh]*(1.0 - Albedo[hh]);
        input_rec2[hh].I_lw = Qlisn_Var[hh];
      break;
      case VARIATION_2:
        input_rec2[hh].S_n  = Qsi[hh]*(1.0 - Albedo[hh]);
        input_rec2[hh].I_lw = QliVt_Var[hh];
      break;
      case VARIATION_3:
        input_rec2[hh].S_n  = QsiS_Var[hh]*(1.0 - Albedo[hh]);
        input_rec2[hh].I_lw = QliVt_Var[hh];
      break;
    }


    input_rec2[hh].T_a  = T_a_X[hh] + CRHM_constants::Tm;
    input_rec2[hh].e_a  = e_a_X[hh]*1000;
    input_rec2[hh].u    = u_X[hh];

    if(F_g_Obs)
      input_rec2[hh].F_g  = F_g_Obs[hh];
    else
      input_rec2[hh].F_g  = F_g_X[hh];

    if(T_g_Obs) // only convert degrees not fluxes
      input_rec2[hh].T_g  = T_g_Obs[hh] + CRHM_constants::Tm;
    else
      input_rec2[hh].T_g  = T_g_X[hh] + CRHM_constants::Tm;

    if(m_snow_X[hh] == 0)
      m_snow[hh] = 0.0;

    if(snowcover[hh]){
      m_snow[hh]  = m_snow_X[hh];
    }
    else {
      if(m_snow_X[hh] > 0.0)
        snow_store[hh] += m_snow_X[hh];
      m_snow[hh] = 0.0;
    }

    if((nstep == 1 && snow_store[hh] > 0.0) || snow_store[hh] > 1.0){
      m_snow[hh]  = snow_store[hh];
      snow_store[hh] = 0.0;
    }

    if(rain_soil_snow[hh] && snowcover[hh]){ // handle snow and rain over snow cover
      m_precip[hh] = m_precip_X[hh];
      m_rain[hh]   = m_rain_X[hh];
      m_rain_X[hh] = 0.0;
    }
    else{ // handle only snow. Infitration routine handles rain
      m_precip[hh] = m_snow_X[hh];
      m_rain[hh]   = 0.0;
    }

    m_drift[hh]  = m_drift_X[hh];
    m_subl[hh]  = m_subl_X[hh];
    rho_snow[hh] = rho_snow_X[hh];

    m_precip_cum[hh] += m_precip[hh]; // change
    m_rain_cum[hh] += m_rain[hh];
    m_snow_cum[hh] += m_snow[hh];
    m_drift_cum[hh] += m_drift[hh];
    m_subl_cum[hh] += m_subl[hh];

    if(m_snow[hh] > 0.0){
      if (rho_snow[hh] <= 0.0){
        CRHMException TExcept("Snobal: rho_snow is <= 0.0 with snow > 0.0", TERMINATE);
        LogError(TExcept);
      }
      z_snow[hh]   = m_snow[hh] / rho_snow[hh];
    }
    else
      z_snow[hh]   = 0.0;

    T_pp[hh]     = T_pp_X[hh] + CRHM_constants::Tm;

// clear interval values

    snowmelt_int[hh] = 0.0;
    melt_direct_int[hh] = 0.0;
    sum[hh] = 0.0;
    E_s_int[hh] = 0.0;
    E_int[hh] = 0.0;
    E_s_0_int[hh] = 0.0;
    E_s_l_int[hh] = 0.0;
    ro_predict[hh] = 0.0;

    long Step = getstep();
    if(getstep() > 1){ // Not first step

      if(m_precip[hh] > 0.0){
        stop_no_snow[hh] = 0;
        precip_now[hh]= true;
      }
      else{
        if(layer_count[hh] == 0)
          stop_no_snow[hh] = 1;
        precip_now[hh]= false;
      }

// process blowing snow event
      _drift();

      do_data_tstep(); // executes Snobal code

    }
    else if(m_precip[hh] > 0.0) {
         CRHMException TExcept("Snobal - cannot handle precipitation during first day of model run", WARNING);
         LogError(TExcept);
    }

    Step = Step % Global::Freq;
    if(Step == 1)
       snowmeltD_acc[hh] = snowmelt_int[hh];
    else
       snowmeltD_acc[hh] += snowmelt_int[hh];

    if(Step == 0){
      snowmeltD[hh] = snowmeltD_acc[hh];
      snowmeltD_acc[hh] = 0.0;
    }

    input_rec1[hh].S_n  = input_rec2[hh].S_n;
    input_rec1[hh].I_lw = input_rec2[hh].I_lw;
    input_rec1[hh].T_a  = input_rec2[hh].T_a;
    input_rec1[hh].e_a  = input_rec2[hh].e_a;
    input_rec1[hh].u    = input_rec2[hh].u;
    input_rec1[hh].T_g  = input_rec2[hh].T_g;
    input_rec1[hh].F_g  = input_rec2[hh].F_g;

    E_s_cum[hh] += E_s_int[hh];
    sum[hh] = m_s[hh] + m_drift_cum[hh] + m_subl_cum[hh] + cumsnowmelt[hh] + E_s_cum[hh];
    SWE_change[hh] += m_s[hh];
    cumsnowmelt[hh] += snowmelt_int[hh];
    melt_direct_cum[hh] += melt_direct_int[hh];

    T_s[hh]   -= CRHM_constants::Tm; // temperatures outside Snobal model are Â°C
    T_s_0[hh] -= CRHM_constants::Tm;
    T_s_l[hh] -= CRHM_constants::Tm;

    T_snow[hh] -= CRHM_constants::Tm;
    T_rain[hh] -= CRHM_constants::Tm;
  }
}

void ClassSnobalCRHM::finish(bool good) { // only required for local storage and final output

  ClassSnobalBase::finish(good);
}

/*
** DESCRIPTION
**      This routine initializes the properties for the snowcover.  It
**	determines the number of layers, their individual properties,
**	the cold content for the snowcover and its layers, and the
**	snowcover's water content.  The following global variables
**	should be initialized before invoking this routine:
**
**		z_s	depth of snowcover (m)
**		rho	density of snowcover (kg/m^3)
**		T_s	average temperature of snowcover (K)
**		T_s_0	temperature of surface layer of snowcover (K)
**		T_s_l	temperature of lower layer of snowcover (K)
**		h2o_sat	% of liquid h2o saturation (0 to 1.0)
**
**		max_h2o_vol	maximum liquid h2o[hh] content as volume ratio:
**				    V_water/(V_snow - V_ice) (unitless)
**
** GLOBAL VARIABLES READ
**	h2o_sat
**	layer_count
**	m_s_0
**	m_s_l
**	max_h2o_vol
**	rho
**	T_s
**	T_s_0
**	T_s_l
**	z_s
**
** GLOBAL VARIABLES MODIFIED
**	cc_s
**	cc_s_0
**	cc_s_l
**	h2o
**	h2o_max
**	h2o_total
**	h2o_vol
**	m_s
**	m_s_0
**	m_s_l
**	rho
**	T_s
**	T_s_0
**	T_s_l
**	(and those variables modified by "_calc_layer", "_layer_mass" and cold_content)
*/