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
#include "../Classfilter.h"
#include "ClassReplace.h"

using namespace std;

ClassReplace::ClassReplace(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassReplace::doFunc(long Obs, long Line) {

	long shift = thisVar->FileData->IndxMin;
	for (int Obs = 0; Obs < ObsCnt; ++Obs)
		outVar->FileData->Data[Obs + DataIndx[Vs - 1]][Line + shift] = Data[0][Obs][Line];
	//    outVar->FileData->Data[Obs][Line  + shift] = thisVar->FileData->Data[Obs][Line];

}