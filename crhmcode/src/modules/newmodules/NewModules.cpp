// 11/21/19
//---------------------------------------------------------------------------

//#include "vcl.h"
#pragma hdrstop

#include "NewModules.h"
#include "../waterquality/WQ_CRHM.h"
#include "../waterquality/WQ_Soil_NPCcycling.h"
#include "../../core/GlobalDll.h"
#include <algorithm>
#include "../../core/ClassCRHM/ClassCRHM.h"

#include "SnobalDefines.h"
#include <cmath>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

#include "../coremodules/ClassBasin.h" //added by Manishankar Mondal
#include "../coremodules/ClassGlobal.h" //added by Manishankar Mondal
#include "../coremodules/ClassObs.h" //added by Manishankar Mondal
#include "../coremodules/ClassIntcp.h" //added by Manishankar Mondal
#include "../coremodules/Classpbsm.h" //added by Manishankar Mondal
#include "../coremodules/ClassNO_pbsm.h" //added by Manishankar Mondal
#include "../coremodules/Classtsurface.h" //added by Manishankar Mondal 
#include "../coremodules/Classalbedo.h" //added by Manishankar Mondal 
#include "../coremodules/Classnetall.h" //added by Manishankar Mondal 
#include "../coremodules/Classebsm.h" //added by Manishankar Mondal
#include "../coremodules/ClassTs.h" //added by Manishankar Mondal
#include "../coremodules/ClassNeedle.h" //added by Manishankar Mondal
#include "../coremodules/ClassSimpleRichard.h" //added by Manishankar Mondal
#include "../coremodules/Classevap.h" //added by Manishankar Mondal
#include "../coremodules/ClassevapD.h" //added by Manishankar Mondal
#include "../coremodules/Classsbsm.h" //added by Manishankar Mondal
#include "../coremodules/Classcrack.h" //added by Manishankar Mondal
#include "../coremodules/ClassKevin.h" //added by Manishankar Mondal
#include "../coremodules/ClassGreencrack.h" //added by Manishankar Mondal
#include "../coremodules/Classfrostdepth.h" //added by Manishankar Mondal
#include "../coremodules/Classfrozen.h" //added by Manishankar Mondal
#include "../coremodules/ClassNetroute.h" //added by Manishankar Mondal
#include "../coremodules/Classinterception.h" //added by Manishankar Mondal
#include "../coremodules/ClassGreenAmpt.h" //added by Manishankar Mondal
#include "../coremodules/Classalbedoparam.h" //added by Manishankar Mondal
#include "../coremodules/Classalbedoobs.h" //added by Manishankar Mondal
#include "../coremodules/ClassHtobs.h" //added by Manishankar Mondal
#include "../coremodules/ClasspbsmSnobal.h" //added by Manishankar Mondal
#include "../coremodules/ClassalbedoRichard.h" //added by Manishankar Mondal
#include "../coremodules/ClassalbedoBaker.h" //added by Manishankar Mondal
#include "../coremodules/ClassHMSA.h" //added by Manishankar Mondal
#include "../coremodules/Classwalmsley_wind.h" //added by Manishankar Mondal
#include "../coremodules/ClassNetroute_M.h" //added by Manishankar Mondal
#include "../coremodules/ClassREWroute2.h" //added by Manishankar Mondal
#include "../coremodules/ClassLongVt.h" //added by Manishankar Mondal
#include "../coremodules/Classpbsm_M.h" //added by Manishankar Mondal
#include "../coremodules/ClassNetroute_D.h" //added by Manishankar Mondal
#include "../coremodules/ClassNetroute_M_D.h" //added by Manishankar Mondal
#include "../coremodules/ClassSetSoil.h" //added by Manishankar Mondal
#include "../coremodules/ClassVolumetric.h" //added by Manishankar Mondal
#include "../coremodules/ClassAnnan.h" //added by Manishankar Mondal
#include "../coremodules/Classcalcsun.h" //added by Manishankar Mondal
#include "../coremodules/ClassObstoPar.h" //added by Manishankar Mondal
#include "../coremodules/ClassPrairieInfil.h" //added by Manishankar Mondal
#include "../coremodules/ClassCRHMCanopy.h" //added by Manishankar Mondal
#include "../coremodules/ClassPSPnew.h" //added by Manishankar Mondal
#include "../coremodules/Classbrushintcp.h" //added by Manishankar Mondal
#include "../coremodules/ClassAyers.h" //added by Manishankar Mondal
#include "../coremodules/ClassSlope_Qsi.h" //added by Manishankar Mondal
#include "../coremodules/ClassfrozenAyers.h" //added by Manishankar Mondal
#include "../coremodules/ClassSoil.h" //added by Manishankar Mondal
#include "../coremodules/Classevap_Resist.h" //added by Manishankar Mondal
#include "../coremodules/ClassevapD_Resist.h" //added by Manishankar Mondal
#include "../coremodules/ClassShutWall.h" //added by Manishankar Mondal
#include "../coremodules/ClassShutWallD.h" //added by Manishankar Mondal
#include "../coremodules/ClassIceBulb.h" //added by Manishankar Mondal
#include "../coremodules/Classlake.h" //added by Manishankar Mondal
#include "../coremodules/ClassalbedoWinstral.h" //added by Manishankar Mondal
#include "../coremodules/ClassK_Estimate.h" //added by Manishankar Mondal
#include "../coremodules/ClassevapX.h" //added by Manishankar Mondal
#include "../coremodules/Class3D_param.h" //added by Manishankar Mondal
#include "../coremodules/ClassMeltRunoff_Lag.h" //added by Manishankar Mondal
#include "../coremodules/ClassMeltRunoff_Kstorage.h" //added by Manishankar Mondal
#include "../coremodules/ClassREWroute.h" //added by Manishankar Mondal
#include "../coremodules/ClassXG.h" //added by Manishankar Mondal
#include "../coremodules/Classcontribution.h" //added by Manishankar Mondal
#include "../coremodules/ClassSoilX.h" //added by Manishankar Mondal
#include "../coremodules/ClassMod_Exec.h" //added by Manishankar Mondal
#include "../coremodules/ClassFlowInSnow.h" //added by Manishankar Mondal
#include "../coremodules/ClassSoilDS.h" //added by Manishankar Mondal
#include "../coremodules/Classalbedoobs2.h" //added by Manishankar Mondal
#include "../coremodules/Classwinter_meltflag.h" //added by Manishankar Mondal
#include "../coremodules/Class_z_s_rho.h" //added by Manishankar Mondal
#include "../coremodules/Classqmelt.h" //added by Manishankar Mondal
#include "../coremodules/Classquinton.h" //added by Manishankar Mondal
#include "../coremodules/Classqdrift.h" //added by Manishankar Mondal
#include "../coremodules/ClassXGAyers.h" //added by Manishankar Mondal
#include "../coremodules/ClassCRHMCanopyClearing.h" //added by Manishankar Mondal
#include "../coremodules/ClassCRHMCanopyClearingGap.h" //added by Manishankar Mondal
#include "../coremodules/ClassREWroute_stream.h" //added by Manishankar Mondal
#include "../coremodules/ClassICEflow.h" //added by Manishankar Mondal
#include "../coremodules/Classglacier.h" //added by Manishankar Mondal
#include "../coremodules/Classglacier_debris.h" //added by Manishankar Mondal
#include "../coremodules/ClassSWEslope.h" //added by Manishankar Mondal
#include "../coremodules/ClassTestSparse.h" //added by Manishankar Mondal
#include "../coremodules/ClassGrow_Crop.h" //added by Manishankar Mondal
#include "../coremodules/ClassSnobalBase.h"  //added by Manishankar Mondal
#include "../coremodules/ClassSnobalX.h"  //added by Manishankar Mondal
#include "../coremodules/ClassSnobalCRHM.h" //added by Manishankar Mondal
#include "../coremodules/Classshared.h" //added by Manishankar Mondal
#include "../coremodules/ClassNOP.h" //added by Manishankar Mondal


//---------------------------------------------------------------------------

//#pragma package(smart_init) removed uneeded pragma - jhs507

//#define numsubstances 5 removed macro redefinition - jhs507



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

  DLLModules.AddModule(new Classshared("Shared", "10/25/10", LMODULE::CUSTOM)); // essential for parameter screen
  DLLModules.AddModule(new ClassNOP("NOP", "05/20/16", LMODULE::ADVANCE)); // essential for parameter screen
  DLLModules.AddModule(new Classbasin("basin", "02/24/12", LMODULE::BASIC));
  DLLModules.AddModule(new Classglobal("global", "04/19/13", LMODULE::BASIC));
  DLLModules.AddModule(new Classobs("obs", "04/17/18", LMODULE::BASIC));
  DLLModules.AddModule(new Classintcp("intcp", "02/24/15", LMODULE::BASIC));
  DLLModules.AddModule(new ClassGrow_Crop("Grow_Crop", "04/04/15", LMODULE::ADVANCE));

  DLLModules.AddModule(new Classcalcsun("calcsun", "10/01/13", LMODULE::BASIC));

  DLLModules.AddModule(new ClassNO_pbsm("NO_pbsm", "11/15/06", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classpbsm("pbsm", "11/20/17", LMODULE::BASIC));
  DLLModules.AddModule(new Classsbsm("sbsm", "10/21/09", LMODULE::ADVANCE));

  DLLModules.AddModule(new ClassAnnan("Annandale", "07/14/11", LMODULE::ADVANCE));

  DLLModules.AddModule(new Classebsm("ebsm", "01/18/16", LMODULE::BASIC));

  DLLModules.AddModule(new ClassLongVt("longVt", "02/10/16", LMODULE::ADVANCE));

  DLLModules.AddModule(new ClassSlope_Qsi("Slope_Qsi", "07/14/11", LMODULE::ADVANCE));

  DLLModules.AddModule(new Classalbedo("albedo", "08/11/11", LMODULE::BASIC));
  DLLModules.AddModule(new Classnetall("netall", "03/22/16", LMODULE::BASIC));
  DLLModules.AddModule(new Classevap("evap", "07/17/19", LMODULE::BASIC));
  DLLModules.AddModule(new ClassevapD("evapD", "11/04/09", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classevap_Resist("evap_Resist", "11/21/16", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassevapD_Resist("evapD_Resist", "09/08/09", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassShutWall("ShuttleWallace", "10/05/06", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassShutWallD("ShuttleWallaceD", "10/05/06", LMODULE::ADVANCE));

  DLLModules.AddModule(new Classcrack("crack", "09/03/08", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassPrairieInfil("PrairieInfiltration", "03/22/13", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassAyers("Ayers", "01/11/17", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassGreencrack("Greencrack", "03/22/13", LMODULE::BASIC));
  DLLModules.AddModule(new ClassGreenAmpt("GreenAmpt", "03/29/10", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classfrozen("frozen", "08/03/17", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassfrozenAyers("frozenAyers", "08/02/16", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSoil("Soil", "02/01/19", LMODULE::BASIC));
  DLLModules.AddModule(new ClassevapX("evapX", "12/18/12", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSoilX("SoilX", "11/28/17", LMODULE::ADVANCE)); // nlay >= 2 check added
  DLLModules.AddModule(new ClassSoilDS("SoilDetention", "11/28/17", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSoilPrairie("SoilPrairie", "11/29/19", LMODULE::PROTO)); // prototype wetlands
  DLLModules.AddModule(new Classglacier("glacier", "03/12/19", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classglacier_debris("glacier_debris", "11/22/19", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassGlacier_debris_cover("Glacier_debris_cover", "10/17/19", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSWEslope("SWESlope", "11/01/17", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassICEflow("ICEflow", "12/31/18", LMODULE::ADVANCE));

  DLLModules.AddModule(new ClassNetroute("Netroute", "06/20/18", LMODULE::BASIC));
  DLLModules.AddModule(new ClassNetroute_D("Netroute_D", "06/20/18", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassNetroute_M("Netroute_M", "06/20/18", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassNetroute_M_D("Netroute_M_D", "10/26/18", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassREWroute("REW_route", "06/19/18", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassREWroute_stream("REW_route_stream", "07/09/18", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassREWroute2("REW_route2", "06/19/18", LMODULE::ADVANCE));

  DLLModules.AddModule(new ClassSnobalCRHM("SnobalCRHM", "11/21/16", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClasspbsmSnobal("pbsmSnobal", "01/05/17", LMODULE::ADVANCE));

  DLLModules.AddModule(new ClassCRHMCanopy("Canopy", "06/14/17", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassCRHMCanopyClearing("CanopyClearing", "04/05/19", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassCRHMCanopyClearingGap("CanopyClearingGap", "04/05/19", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassNeedle("NeedleLeaf", "07/19/11", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classwalmsley_wind("walmsley_wind", "07/30/08", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassXG("XG", "10/03/17", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassXGAyers("XGAyers", "05/19/17", LMODULE::PROTO));

  DLLModules.AddModule(new ClassSetSoil("SetSoil", "10/21/09", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassVolumetric("Volumetric", "05/30/19", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classtsurface("tsurface", "01/15/19", LMODULE::PROTO));

  DLLModules.AddModule(new Classalbedoparam("albedo_param", "11/22/05", LMODULE::SUPPORT));
  DLLModules.AddModule(new Classalbedoobs("albedo_obs", "11/22/05", LMODULE::SUPPORT));
  DLLModules.AddModule(new ClassalbedoRichard("albedo_Richard", "03/19/15", LMODULE::SUPPORT));
  DLLModules.AddModule(new ClassalbedoBaker("albedo_Baker", "03/19/15", LMODULE::SUPPORT));
  DLLModules.AddModule(new ClassalbedoWinstral("albedo_Winstral", "03/19/15", LMODULE::SUPPORT));
  DLLModules.AddModule(new ClassHtobs("Ht_obs", "12/02/09", LMODULE::SUPPORT));
  DLLModules.AddModule(new ClassObstoPar("obs_par", "07/19/10", LMODULE::SUPPORT));

  DLLModules.AddModule(new Classfrostdepth("frostdepth", "08/11/11", LMODULE::CUSTOM));

  DLLModules.AddModule(new Classqmelt("Qmelt", "03/31/16", LMODULE::CUSTOM));
  DLLModules.AddModule(new Classquinton("Quinton", "03/31/16", LMODULE::CUSTOM));
  DLLModules.AddModule(new Classqdrift("Qdrift", "03/31/16", LMODULE::CUSTOM));

  DLLModules.AddModule(new ClassSimpleRichard("SimpleSnow", "03/24/06", LMODULE::CUSTOM));
  DLLModules.AddModule(new ClassKevin("Kevin", "08/11/11", LMODULE::OBSOL));
  DLLModules.AddModule(new ClassTs("Tsnow", "01/15/13", LMODULE::CUSTOM));
  DLLModules.AddModule(new ClassK_Estimate("K_Estimate", "01/16/18", LMODULE::ADVANCE)); // fixed 'put' descriptions

  DLLModules.AddModule(new ClassSnobalX("Snobal", "02/03/16", LMODULE::OBSOL));
  DLLModules.AddModule(new Classinterception("interception", "11/03/06", LMODULE::OBSOL));
  DLLModules.AddModule(new Classlake("lake_evap", "07/04/12", LMODULE::ADVANCE));

  if(!RELEASE){
    DLLModules.AddModule(new ClassTestSparse("TestSparse", "05/29/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassHMSA("HMSA", "01/16/13", LMODULE::PROTO));
    DLLModules.AddModule(new ClassIceBulb("IceBulb", "11/20/17", LMODULE::PROTO));
    DLLModules.AddModule(new Class3D_param("3D_param", "03/18/13", LMODULE::PROTO));
    DLLModules.AddModule(new ClassMeltRunoff_Lag("MeltRunoff_Lag", "09/03/13", LMODULE::PROTO));
    DLLModules.AddModule(new ClassMeltRunoff_Kstorage("MeltRunoff_Kstorage", "09/03/13", LMODULE::PROTO));
    DLLModules.AddModule(new ClassFlowInSnow("FlowInSnow", "08/19/14", LMODULE::PROTO));
    DLLModules.AddModule(new ClassMod_Exec("Exec", "02/26/14", LMODULE::PROTO));
    DLLModules.AddModule(new Classcontribution("contribution", "01/29/14", LMODULE::PROTO));
    DLLModules.AddModule(new Classalbedoobs2("albedo_obs2", "11/18/14", LMODULE::PROTO));
    DLLModules.AddModule(new Classwinter_meltflag("winter_meltflag", "02/12/15", LMODULE::PROTO));
    DLLModules.AddModule(new Class_z_s_rho("z_s_and_rho", "04/09/15", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_Test_Hype("WQ_Test", "05/01/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_Substitute_Hype("WQ_Soil_BGC_substitute", "12/11/18", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_Soil("WQ_Soil", "10/17/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_Netroute("WQ_Netroute", "08/26/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_Netroute_M_D("WQ_Netroute_M_D", "09/11/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_pbsm("WQ_pbsm", "01/21/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_pbsmSnobal("WQ_pbsmSnobal", "04/26/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_SoilBGC("WQ_Soil_BGC", "11/01/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_mass_conc("WQ_mass_to_conc", "12/01/18", LMODULE::PROTO));
    DLLModules.AddModule(new ClassGrow_crops_annually("Grow_crops_annually", "06/05/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_Gen_Mass_Var_Netroute("WQ_Gen_Mass_Var_Netroute", "06/20/19", LMODULE::ADVANCE));
    DLLModules.AddModule(new ClassWQ_Gen_Mass_Var_Soil("WQ_Gen_Mass_Var_Soil", "06/20/19", LMODULE::ADVANCE));
    DLLModules.AddModule(new Classlapse_rate_Monthly_Mod("lapse_rate_Monthly_Mod", "11/22/19", LMODULE::ADVANCE));
    DLLModules.AddModule(new ClassGlacier_melt_debris_cover_estimate_Mod("Glacier_melt_debris_cover_estimate_Mod", "11/22/19", LMODULE::ADVANCE));
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