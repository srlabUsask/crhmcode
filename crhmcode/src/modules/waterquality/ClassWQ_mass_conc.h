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

#ifndef CLASSWQ_MASS_CONC
#define CLASSWQ_MASS_CONC

#include "WQ_CRHM.h"


class ClassWQ_mass_conc : public ClassModule {
public:

	ClassWQ_mass_conc(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared variables
	double* inflow_conc{ NULL };
	double** inflow_conc_lay{ NULL };
	double* outflow_conc{ NULL };
	double** outflow_conc_lay{ NULL };
	double* runoutflow_conc{ NULL };
	double** runoutflow_conc_lay{ NULL };
	double* ssroutflow_conc{ NULL };
	double** ssroutflow_conc_lay{ NULL };
	double* gwoutflow_conc{ NULL };
	double** gwoutflow_conc_lay{ NULL };

	// declared parameters

	// variable inputs
	const double* inflow{ NULL };
	const double* inflow_mWQ{ NULL };
	const double** inflow_mWQ_lay{ NULL };
	const double* outflow{ NULL };
	const double* outflow_mWQ{ NULL };
	const double** outflow_mWQ_lay{ NULL };
	const double* outflow_cWQ{ NULL };
	const double** outflow_cWQ_lay{ NULL };
	const double* runoutflow{ NULL };
	const double* runoutflow_mWQ{ NULL };
	const double** runoutflow_mWQ_lay{ NULL };
	const double* ssroutflow{ NULL };
	const double* ssroutflow_mWQ{ NULL };
	const double** ssroutflow_mWQ_lay{ NULL };
	const double* gwoutflow{ NULL };
	const double* gwoutflow_mWQ{ NULL };
	const double** gwoutflow_mWQ_lay{ NULL };

	void decl(void);
	void init(void);
	void run(void);

	void Reset_WQ(double** var_lay);
	void mass_to_conc(const double* var, const double** var_mWQ, double** var_conc);

	ClassWQ_mass_conc* klone(string name) const;
};


#endif // !CLASSWQ_MASS_CONC
