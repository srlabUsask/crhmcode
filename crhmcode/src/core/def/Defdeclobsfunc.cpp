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
#include "Defdeclobsfunc.h"

Defdeclobsfunc::Defdeclobsfunc(ClassMacro* Macro_) : DefCRHM(Macro_) 
{
	obs = DefStringList->at(1);
	name = DefStringList->at(2);
	typeFun = getTFunc(DefStringList->at(3));
}



void Defdeclobsfunc::CallDecl() {

	long cnt = Macro->declobsfunc(obs, name, &fix, typeFun);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.kind = TV::CRHM;
	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.IndexMax = cnt;
	//  FP->second.value = const_cast<double *> (fix);
	FP->second.value = fix;
	FP->second.Me = Macro;
}