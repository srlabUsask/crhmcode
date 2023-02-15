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
#include "DefCRHM.h"

Defdeclparam::Defdeclparam(ClassMacro* Macro_) : DefCRHM(Macro_) 
{

	if (DefStringList->at(0) == "decldiagparam")
	{
		visibility = TVISIBLE::DIAGNOSTIC;
	}
	else
	{
		visibility = TVISIBLE::USUAL;
	}

	name = DefStringList->at(1);
	Dim = getTDim(DefStringList->at(2));
	Default = DefStringList->at(3);
	Min = DefStringList->at(4);
	Max = DefStringList->at(5);
	Description = DefStringList->at(6);
	Units = DefStringList->at(7);

	if (DefCRHM::DefStringList->size() > 8 && DefStringList->at(8) == "Int")
	{
		Int = true;
	}
	else
	{
		Int = false;
	}

	nlay = -1;
	if (DefCRHM::DefStringList->size() > 9)
	{
		nlay = Strtolong(DefStringList->at(9));
	}
}


void Defdeclparam::CallDecl() {

	if (Int) {
		if (nlay > 0) {
			Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_long_const, &fix2_long_const, nlay, visibility);
		} else {
			Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_long_const, &fix2_long_const, Macro->nhru, visibility);
		}
	} else {
		Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_const, &fix2_const, Macro->nhru, visibility);
	}

	if (Global::BuildFlag == TBuild::INIT) {
		FP = Macro->vars.find(name);
		if (FP == Macro->vars.end()) {
			Macro->vars.insert(make_pair(name, VarCHRM()));
			FP = Macro->vars.find(name);
		}

		FP->second.name = name;
		FP->second.Ihh = 0;
		FP->second.IndexMax = Macro->nhru - 1;
		FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
		FP->second.Me = Macro;

		if (Int) {
			if (Dim == TDim::NDEF || Dim == TDim::NDEFN) {
				FP->second.kind = TV::CRHMint2;
				FP->second.ivalue2 = const_cast<long**> (fix2_long_const);
			}
			else {
				FP->second.kind = TV::CRHMint;
				FP->second.ivalue = const_cast<long*> (fix_long_const);
			}
		}
		else {
			if (Dim == TDim::NDEF || Dim == TDim::NDEFN) {
				FP->second.kind = TV::CRHM2;
				FP->second.value2 = const_cast<double**> (fix2_const);
			}
			else {
				FP->second.kind = TV::CRHM;
				FP->second.value = const_cast<double*> (fix_const);
			}
		}
	}
}

void Defdeclparam::CallInit(long nhru, long nlay) {
}