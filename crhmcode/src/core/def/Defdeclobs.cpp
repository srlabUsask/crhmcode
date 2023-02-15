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
#include "Defdeclobs.h"

Defdeclobs::Defdeclobs(ClassMacro* Macro_) : DefCRHM(Macro_) 
{
	string S = DefStringList->at(1);
	string::size_type Pos = S.find("#");
	if (Pos == string::npos) //Updated by Manishankar on 2019-09-14. This previously was ------------- if (Pos != string::npos)
		S += "#"; // no # symbol
	else
		S = S.substr(0, Pos + 1); // use just one # //Updated by Manishankar on 2019-09-14. This previously was ------------- S.substr(1, Pos)

	name = S;
	Dim = getTDim(DefStringList->at(2));
	Description = DefStringList->at(3);
	Units = DefStringList->at(4);
}

void Defdeclobs::CallDecl() {

	long cnt = Macro->declobs(Macro->Name, name, Dim, Description, Units, &fix);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	if (fix)
		FP->second.kind = TV::CRHM;
	else
		FP->second.kind = TV::NOP;

	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.IndexMax = cnt;
	FP->second.value = fix;
	FP->second.Me = Macro;
}

void Defdeclobs::CallInit(long nhru, long nlay) {
	for (int hh = 0; hh <= FP->second.IndexMax; ++hh) {
		FP->second.Ihh = hh;
		FP->second.put(0.0);
	}
}