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
#pragma once

#ifndef CLASSGLACIER_MELT_DEBRIS_COVER_ESTIMATE
#define CLASSGLACIER_MELT_DEBRIS_COVER_ESTIMATE

#include "WQ_CRHM.h"


class ClassGlacier_melt_debris_cover_estimate_Mod : public ClassModule {
public:

	ClassGlacier_melt_debris_cover_estimate_Mod(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared parameters

	const double* debris_h{ NULL };
	const double* T_threshold{ NULL };

	// declared variables

	double* lagT{ NULL };
	double* lagSW{ NULL };
	double* Gmelt_energy{ NULL };
	double* den_air{ NULL };
	double* K_kat{ NULL };
	double* Cp_water{ NULL };
	double* Xmelt{ NULL };
	double* Xmelt_int{ NULL };
	double* Xmelt_acc{ NULL };
	double* Xmelt_V5{ NULL };

	// put variables

	double* Gn_ebsm{ NULL };
	double* Gh_ebsm{ NULL };
	double* Ge_ebsm{ NULL };
	double* Gp_ebsm{ NULL };

	// get variables

	const double* Albedo{ NULL };
	const double* T_rain{ NULL };
	const double* hru_t{ NULL };
	const double* hru_ea{ NULL };
	const double* net_rain{ NULL };
	const double* Pa{ NULL };
	const double* Qnsn_Var{ NULL };

	// observations

	const double* lagT1{ NULL };
	const double* lagT2{ NULL };
	const double* lagT3{ NULL };
	const double* lagT4{ NULL };
	const double* lagSW1{ NULL };
	const double* lagSW2{ NULL };
	const double* lagSW3{ NULL };
	const double* lagSW4{ NULL };
	const double* lagSW5{ NULL };
	const double* lagSW6{ NULL };

	void decl(void);
	void init(void);
	void run(void);

	ClassGlacier_melt_debris_cover_estimate_Mod* klone(string name) const;
};


#endif // !CLASSGLACIER_MELT_DEBRIS_COVER_ESTIMATE
