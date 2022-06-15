// 11/30/19
//---------------------------------------------------------------------------
#ifndef WQ_CRHMH
#define WQ_CRHMH
//---------------------------------------------------------------------------

#include "../../core/ClassModule.h"
#include "ClassWQ_Soil.h"
#include "ClassWQ_Netroute.h"
#include "ClassWQ_pbsm.h"
#include "ClassWQ_Netroute_M_D.h"
#include "ClassWQ_REWroute.h"
#include "ClassWQ_Test_Hype.h"
#include "ClassWQ_pbsmSnobal.h"
#include "ClassWQ_Substitute_Hype.h"
#include "ClassWQ_Gen_Mass_Var_Soil.h"
#include "ClassGrow_crops_annually.h"
#include "ClassWQ_Gen_Mass_Var_Netroute.h"
#include "Classlapse_rate_Monthly_Mod.h"
#include "ClassGlacier_melt_debris_cover_estimate_Mod.h"
#include "ClassSoilPrairie.h"
#include "ClassGlacier_debris_cover.h"
#include "Class_lapse_rate_Monthly.h"
#include "ClassWQ_mass_conc.h"

#define numsubstances 7
#define maxsoillayers 2

using namespace std;
using namespace CRHM;

const double minFlow_WQ = 0.001f;

#endif
