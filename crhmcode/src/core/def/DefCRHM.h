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
