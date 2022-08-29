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

#include <sstream>
//#include <math.h>
#include <cmath>
#include <stdlib.h>

#include "WQ_CRHM.h"
#include "../newmodules/NewModules.h"
#include "../../core/GlobalDll.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init) removed uneeded pragma - jhs507

//---------------------------------------------------------------------------

//using namespace std;
//using namespace CRHM;

//static double fLimit;

//const double minFlow_WQ = 0.001f;

//---------------------------------------------------------------------------

// NOTES about CRHM-WQ

// const long i_no3n = 0; // inorganic nitrogen
// const long i_don = 1; // organic nitrogen
// const long i_srp = 2; // soluble (reactive) phosphorus, i.e. phosphate
// const long i_pp = 3; // particulate phosphorus
// const long i_oc = 4; // (dissolved) organic carbon

// kg/km2 = (mg/l)*mm = mg/m2
// Kg == mm
// mg/l == Kg/Km2 = 1/mm
// l/m2 == mm = Kg/m2

//==============================================================================
