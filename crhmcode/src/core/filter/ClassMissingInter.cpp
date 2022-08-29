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
#include "ClassMissingInter.h"

using namespace std;

ClassMissingInter::ClassMissingInter(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes), GoodData(NULL)
{
	readargs();
	GoodData = new double[ObsCnt];
	LastGoodData = new long[ObsCnt];
}

void ClassMissingInter::doFunc(long Obs, long Line) {
	static bool Warned = false;

	if (FirstTime) {
		if ((Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1]) && !Warned) {
			////Application->MessageBox(MyObs->DataFileName.c_str(), "Missing data in first interval of filter 'missinginter'", MB_OK);
			LogError("Missing data in first interval of " + MyObs->DataFileName, TExcept::WARNING);
			Warned = true;
			LastGoodData[Obs] = -1;
			return;
		}

		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
		GoodData[Obs] = Data[0][Obs][Line];
		LastGoodData[Obs] = Line;

		if (Obs + 1 >= ObsCnt)  FirstTime = false;
		return;
	}

	if (Data[0][Obs][Line] > Constants[0] && Data[0][Obs][Line] < Constants[1]) {
		if (Line - 1 > LastGoodData[Obs] && LastGoodData[Obs] != -1) {
			double dif = (Data[0][Obs][Line] - GoodData[Obs]) / (static_cast<long long>(Line) - static_cast<long long>(LastGoodData[Obs]));
			for (int ii = LastGoodData[Obs] + 1; ii < Line; ++ii)
				Data[Vs - 1][Obs][ii] = Data[Vs - 1][Obs][ii - 1] + dif;
		}

		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];

		GoodData[Obs] = Data[0][Obs][Line];
		LastGoodData[Obs] = Line;
	}
}

ClassMissingInter::~ClassMissingInter() {
	delete[] GoodData;
	delete[] LastGoodData;
}