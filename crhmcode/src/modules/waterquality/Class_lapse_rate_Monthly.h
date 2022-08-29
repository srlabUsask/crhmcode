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

#ifndef CLASS_LAPSE_RATE_MONTHLY
#define CLASS_LAPSE_RATE_MONTHLY

#include "WQ_CRHM.h"

class Class_lapse_rate_Monthly : public ClassModule {
public:

	Class_lapse_rate_Monthly(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared variables
	double* lapse_rate{ NULL };
	double* lapse_rate_Mthly{ NULL };

	void decl(void);
	void init(void);
	void run(void);

	Class_lapse_rate_Monthly* klone(string name) const;
};

#endif // !CLASS_LAPSE_RATE_MONTHLY
