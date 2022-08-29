/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
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
