// 11/21/19
//---------------------------------------------------------------------------

//#include "vcl.h"
#pragma hdrstop

#include <cmath>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "NewModules.h"
#include "../waterquality/WQ_CRHM.h"
#include "../waterquality/WQ_Soil_NPCcycling.h"
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM.h"
#include "SnobalDefines.h"



#include "../ClassBasin.h" //added by Manishankar Mondal
#include "../ClassGlobal.h" //added by Manishankar Mondal
#include "../ClassObs.h" //added by Manishankar Mondal
#include "../ClassIntcp.h" //added by Manishankar Mondal
#include "../Classpbsm.h" //added by Manishankar Mondal
#include "../ClassNO_pbsm.h" //added by Manishankar Mondal
#include "../Classtsurface.h" //added by Manishankar Mondal
#include "../Classalbedo.h" //added by Manishankar Mondal
#include "../Classnetall.h" //added by Manishankar Mondal
#include "../Classebsm.h" //added by Manishankar Mondal
#include "../ClassTs.h" //added by Manishankar Mondal
#include "../ClassNeedle.h" //added by Manishankar Mondal
#include "../ClassSimpleRichard.h" //added by Manishankar Mondal
#include "../Classevap.h" //added by Manishankar Mondal
#include "../ClassevapD.h" //added by Manishankar Mondal
#include "../Classsbsm.h" //added by Manishankar Mondal
#include "../Classcrack.h" //added by Manishankar Mondal
#include "../ClassKevin.h" //added by Manishankar Mondal
#include "../ClassGreencrack.h" //added by Manishankar Mondal
#include "../Classfrostdepth.h" //added by Manishankar Mondal
#include "../Classfrozen.h" //added by Manishankar Mondal
#include "../ClassNetroute.h" //added by Manishankar Mondal
#include "../Classinterception.h" //added by Manishankar Mondal
#include "../ClassGreenAmpt.h" //added by Manishankar Mondal
#include "../Classalbedoparam.h" //added by Manishankar Mondal
#include "../Classalbedoobs.h" //added by Manishankar Mondal
#include "../ClassHtobs.h" //added by Manishankar Mondal
#include "../ClasspbsmSnobal.h" //added by Manishankar Mondal
#include "../ClassalbedoRichard.h" //added by Manishankar Mondal
#include "../ClassalbedoBaker.h" //added by Manishankar Mondal
#include "../ClassHMSA.h" //added by Manishankar Mondal
#include "../Classwalmsley_wind.h" //added by Manishankar Mondal
#include "../ClassNetroute_M.h" //added by Manishankar Mondal
#include "../ClassREWroute2.h" //added by Manishankar Mondal
#include "../ClassLongVt.h" //added by Manishankar Mondal
#include "../Classpbsm_M.h" //added by Manishankar Mondal
#include "../ClassNetroute_D.h" //added by Manishankar Mondal
#include "../ClassNetroute_M_D.h" //added by Manishankar Mondal
#include "../ClassSetSoil.h" //added by Manishankar Mondal
#include "../ClassVolumetric.h" //added by Manishankar Mondal
#include "../ClassAnnan.h" //added by Manishankar Mondal
#include "../Classcalcsun.h" //added by Manishankar Mondal
#include "../ClassObstoPar.h" //added by Manishankar Mondal
#include "../ClassPrairieInfil.h" //added by Manishankar Mondal
#include "../ClassCRHMCanopy.h" //added by Manishankar Mondal
#include "../ClassPSPnew.h" //added by Manishankar Mondal
#include "../Classbrushintcp.h" //added by Manishankar Mondal
#include "../ClassAyers.h" //added by Manishankar Mondal
#include "../ClassSlope_Qsi.h" //added by Manishankar Mondal
#include "../ClassfrozenAyers.h" //added by Manishankar Mondal
#include "../ClassSoil.h" //added by Manishankar Mondal
#include "../Classevap_Resist.h" //added by Manishankar Mondal
#include "../ClassevapD_Resist.h" //added by Manishankar Mondal
#include "../ClassShutWall.h" //added by Manishankar Mondal
#include "../ClassShutWallD.h" //added by Manishankar Mondal
#include "../ClassIceBulb.h" //added by Manishankar Mondal
#include "../Classlake.h" //added by Manishankar Mondal
#include "../ClassalbedoWinstral.h" //added by Manishankar Mondal
#include "../ClassK_Estimate.h" //added by Manishankar Mondal
#include "../ClassevapX.h" //added by Manishankar Mondal
#include "../Class3D_param.h" //added by Manishankar Mondal
#include "../ClassMeltRunoff_Lag.h" //added by Manishankar Mondal
#include "../ClassMeltRunoff_Kstorage.h" //added by Manishankar Mondal
#include "../ClassREWroute.h" //added by Manishankar Mondal
#include "../ClassXG.h" //added by Manishankar Mondal
#include "../Classcontribution.h" //added by Manishankar Mondal
#include "../ClassSoilX.h" //added by Manishankar Mondal
#include "../ClassMod_Exec.h" //added by Manishankar Mondal
#include "../ClassFlowInSnow.h" //added by Manishankar Mondal
#include "../ClassSoilDS.h" //added by Manishankar Mondal
#include "../Classalbedoobs2.h" //added by Manishankar Mondal
#include "../Classwinter_meltflag.h" //added by Manishankar Mondal
#include "../Class_z_s_rho.h" //added by Manishankar Mondal
#include "../Classqmelt.h" //added by Manishankar Mondal
#include "../Classquinton.h" //added by Manishankar Mondal
#include "../Classqdrift.h" //added by Manishankar Mondal
#include "../ClassXGAyers.h" //added by Manishankar Mondal
#include "../ClassCRHMCanopyClearing.h" //added by Manishankar Mondal
#include "../ClassCRHMCanopyClearingGap.h" //added by Manishankar Mondal
#include "../ClassREWroute_stream.h" //added by Manishankar Mondal
#include "../ClassICEflow.h" //added by Manishankar Mondal
#include "../Classglacier.h" //added by Manishankar Mondal
#include "../Classglacier_debris.h" //added by Manishankar Mondal
#include "../ClassSWEslope.h" //added by Manishankar Mondal
#include "../ClassTestSparse.h" //added by Manishankar Mondal
#include "../ClassGrow_Crop.h" //added by Manishankar Mondal
#include "../ClassSnobalBase.h"  //added by Manishankar Mondal
#include "../ClassSnobalX.h"  //added by Manishankar Mondal
#include "../ClassSnobalCRHM.h" //added by Manishankar Mondal
#include "../Classshared.h" //added by Manishankar Mondal
#include "../ClassNOP.h" //added by Manishankar Mondal


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

void MoveModulesToGlobal(string DLLName)
{

  DLLModules.AddModule(new Classshared("Shared", "10/25/10", LMODULE::CUSTOM)); // essential for parameter screen
  DLLModules.AddModule(new ClassNOP("NOP", "05/20/16", LMODULE::ADVANCE)); // essential for parameter screen
  DLLModules.AddModule(new Classbasin("basin", "02/24/12", LMODULE::BASIC));
  DLLModules.AddModule(new Classglobal("global", "12/19/19", LMODULE::BASIC));
  DLLModules.AddModule(new Classobs("obs", "04/17/18", LMODULE::BASIC));
  DLLModules.AddModule(new Classintcp("intcp", "02/24/15", LMODULE::BASIC));
  DLLModules.AddModule(new ClassGrow_Crop("Grow_Crop", "04/04/15", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classcalcsun("calcsun", "10/01/13", LMODULE::BASIC));
  DLLModules.AddModule(new ClassNO_pbsm("NO_pbsm", "11/15/06", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classpbsm("pbsm", "11/20/17", LMODULE::BASIC));
  DLLModules.AddModule(new Classsbsm("sbsm", "10/21/09", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassAnnan("Annandale", "07/14/11", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classebsm("ebsm", "01/18/16", LMODULE::BASIC));
  DLLModules.AddModule(new ClassLongVt("longVt", "04/04/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSlope_Qsi("Slope_Qsi", "07/14/11", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classalbedo("albedo", "08/11/11", LMODULE::BASIC));
  DLLModules.AddModule(new Classnetall("netall", "04/04/22", LMODULE::BASIC));
  DLLModules.AddModule(new Classevap("evap", "03/18/22", LMODULE::BASIC));
  DLLModules.AddModule(new ClassevapD("evapD", "11/04/09", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classevap_Resist("evap_Resist", "04/04/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassevapD_Resist("evapD_Resist", "04/04/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassShutWall("ShuttleWallace", "04/04/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassShutWallD("ShuttleWallaceD", "04/04/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classcrack("crack", "04/04/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassPrairieInfil("PrairieInfiltration", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassAyers("Ayers", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassGreencrack("Greencrack", "04/04/22", LMODULE::BASIC));
  DLLModules.AddModule(new ClassGreenAmpt("GreenAmpt", "04/04/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classfrozen("frozen", "04/04/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassfrozenAyers("frozenAyers", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSoil("Soil", "04/05/22", LMODULE::BASIC));
  DLLModules.AddModule(new ClassevapX("evapX", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSoilX("SoilX", "04/05/22", LMODULE::ADVANCE)); // nlay >= 2 check added
  DLLModules.AddModule(new ClassSoilDS("SoilDetention", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSoilPrairie("SoilPrairie", "04/05/22", LMODULE::PROTO)); // prototype wetlands
  DLLModules.AddModule(new Classglacier("glacier", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classglacier_debris("glacier_debris", "11/22/19", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassGlacier_debris_cover("Glacier_debris_cover", "10/17/19", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSWEslope("SWESlope", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassICEflow("ICEflow", "12/31/18", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassNetroute("Netroute", "04/05/22", LMODULE::BASIC));
  DLLModules.AddModule(new ClassNetroute_D("Netroute_D", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassNetroute_M("Netroute_M", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassNetroute_M_D("Netroute_M_D", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassREWroute("REW_route", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassREWroute_stream("REW_route_stream", "07/09/18", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassREWroute2("REW_route2", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassSnobalCRHM("SnobalCRHM", "11/21/16", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClasspbsmSnobal("pbsmSnobal", "01/05/17", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassCRHMCanopy("Canopy", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassCRHMCanopyClearing("CanopyClearing", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassCRHMCanopyClearingGap("CanopyClearingGap", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassNeedle("NeedleLeaf", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classwalmsley_wind("walmsley_wind", "07/30/08", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassXG("XG", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassXGAyers("XGAyers", "05/19/17", LMODULE::PROTO));
  DLLModules.AddModule(new ClassSetSoil("SetSoil", "10/21/09", LMODULE::ADVANCE));
  DLLModules.AddModule(new ClassVolumetric("Volumetric", "04/05/22", LMODULE::ADVANCE));
  DLLModules.AddModule(new Classtsurface("tsurface", "04/05/22", LMODULE::PROTO));
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
  DLLModules.AddModule(new ClassK_Estimate("K_Estimate", "04/06/22", LMODULE::ADVANCE)); // fixed 'put' descriptions
  DLLModules.AddModule(new ClassSnobalX("Snobal", "02/03/16", LMODULE::OBSOL));
  DLLModules.AddModule(new Classinterception("interception", "04/05/22", LMODULE::OBSOL));
  DLLModules.AddModule(new Classlake("lake_evap", "04/05/22", LMODULE::ADVANCE));

  if(!RELEASE)
  {
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
    DLLModules.AddModule(new ClassWQ_Soil("WQ_Soil", "05/08/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_Netroute("WQ_Netroute", "11/29/18", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_Netroute_M_D("WQ_Netroute_M_D", "03/22/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_pbsm("WQ_pbsm", "01/21/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_pbsmSnobal("WQ_pbsmSnobal", "04/26/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_SoilBGC("WQ_Soil_BGC", "11/01/19", LMODULE::PROTO));
    DLLModules.AddModule(new ClassWQ_mass_conc("WQ_mass_to_conc", "12/01/18", LMODULE::PROTO));
    DLLModules.AddModule(new ClassGrow_crops_annually("Grow_crops_annually", "05/08/19", LMODULE::PROTO));
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
