#pragma once

#ifndef DEFCRHM
#define DEFCRHM

#include "../MacroUnit.h"

string Add_Quote(string s);

class ClassMacro;

class DefCRHM {
public:
	DefCRHM(ClassMacro* Macro_) : Macro(Macro_), fix(NULL), fix2(NULL)
	{
		if (!DefStringList) DefStringList = new std::vector<std::string>();
	};

	static std::vector<std::string> * DefStringList;
	virtual void CallDecl() {};
	virtual void CallInit(long nhru, long nlay) {};

protected:
	TDim getTDim(string D);
	TFun getTFunc(string D);
	ClassMacro* Macro;
	symtab_t::iterator FP;
	double* fix;
	long* fix_long{ NULL };
	double** fix2{ NULL };
	const double* fix_const{ NULL };
	const double** fix2_const{ NULL };
	const long* fix_long_const{ NULL };
	const long** fix2_long_const{ NULL };
};

#include "Defcommand.h"
#include "Defdeclparam.h"
#include "Defdeclvar.h"
#include "Defdecldiag.h"
#include "Defdeclstatvar.h"
#include "Defdecllocal.h"
#include "Defdeclobs.h"
#include "Defdeclgetvar.h"
#include "Defdeclputvar.h"
#include "Defdeclputparam.h"
#include "Defdeclreadobs.h"
#include "Defdeclobsfunc.h"

#endif // !DEFCRHM
