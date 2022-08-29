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

#ifndef CLASSWQ_GEN_MASS_VAR_NETROUTE
#define CLASSWQ_GEN_MASS_VAR_NETROUTE

#include "WQ_CRHM.h"


class ClassWQ_Gen_Mass_Var_Netroute : public ClassModule {
public:

	ClassWQ_Gen_Mass_Var_Netroute(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared parameters

	double* basinflow_change_mWQ{ NULL };
	double** basinflow_change_mWQ_lay{ NULL };
	double* basinflow_mWQ_last{ NULL };
	double** basinflow_mWQ_lay_last{ NULL };

	double* basingw_change_mWQ{ NULL };
	double** basingw_change_mWQ_lay{ NULL };
	double* basingw_mWQ_last{ NULL };
	double** basingw_mWQ_lay_last{ NULL };

	double* outflow_diverted_change_mWQ{ NULL };
	double** outflow_diverted_change_mWQ_lay{ NULL };
	double* outflow_diverted_mWQ_last{ NULL };
	double** outflow_diverted_mWQ_lay_last{ NULL };

	double* gwoutflow_diverted_change_mWQ{ NULL };
	double** gwoutflow_diverted_change_mWQ_lay{ NULL };
	double* gwoutflow_diverted_mWQ_last{ NULL };
	double** gwoutflow_diverted_mWQ_lay_last{ NULL };

	// variable get inputs
	double* basinflow{ NULL };
	double* basingw{ NULL };
	double* outflow_diverted{ NULL };
	double* gwoutflow_diverted{ NULL };

	double* basinflow_conc{ NULL };
	double** basinflow_conc_lay{ NULL };
	double* basingw_conc{ NULL };
	double** basingw_conc_lay{ NULL };
	double* outflow_diverted_conc{ NULL };
	double** outflow_diverted_conc_lay{ NULL };
	double* gwoutflow_diverted_conc{ NULL };
	double** gwoutflow_diverted_conc_lay{ NULL };

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	ClassWQ_Gen_Mass_Var_Netroute* klone(string name) const;
};


#endif // !CLASSWQ_GEN_MASS_VAR_NETROUTE
