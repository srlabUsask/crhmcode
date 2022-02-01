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
