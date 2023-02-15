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

#ifndef VARCHRM
#define VARCHRM

#include "CRHM_parse.h"

enum class TV { CRHM, CRHMint, LOCAL, FUNget, FUNobs, CRHM2, CRHMint2, NOP };

class ClassModule;

class VarCHRM {
public:

	TV kind;          // enum TV {CRHM, CRHMint, LOCAL, FUNget, FUNobs, CRHM2, CRHMint2, NOP}
	double val;        // const value

	double* value;     // CRHM array
	long* ivalue;     // CRHM array
	double** value2;     // CRHM array
	long** ivalue2;     // CRHM array

	long Ihh;         // CRHM array element 0-based
	long Ill;         // CRHM array element 0-based
	long IndexMax;    // Max index - (#HRUs - 1)
	long IndexMaxLay; // Max index - (#HRUs - 1)
	string name;      // identifier
	double(*pget) (void) { NULL };
	ClassModule* Me;

	VarCHRM() : kind(TV::LOCAL), val(0.0), value(NULL), ivalue(NULL), value2(NULL), ivalue2(NULL),
		Ihh(0), Ill(0), IndexMax(0), IndexMaxLay(0), name("Undefined"), Me(NULL) {};
	VarCHRM(const VarCHRM& Cl); // copy constructor
	VarCHRM& operator=(const VarCHRM& Cl);
	~VarCHRM();

	void put(double val_);
	double get(void);



	
};


#endif // !VARCHRM
