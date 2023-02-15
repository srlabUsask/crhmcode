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
#include "ClassSmear.h"

using namespace std;

ClassSmear::ClassSmear(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes), Minus(false) {
	readargs();
}

void ClassSmear::doFunc(long Obs, long Line) {

	if (FirstTime) {

		if (Constants[0] < 0.0)
			Minus = true;

		if (Constants[0] <= 0.0)
			Constants[0] = MyObs->Dt1;

		if (Constants[1] <= 0.0) Constants[1] = MyObs->Dt2;

		Constants[0] = MyObs->Dt1 - MyObs->Interval / 2.0;
		Constants[1] = MyObs->Dt2 + MyObs->Interval / 2.0;
		FirstTime = false;
	}

	double now = MyObs->Dt1 + Line * MyObs->Interval;
	double delta = MyObs->Interval / 2.0;


	double now0 = fmod(now, 1.0);

	if (now0 > -delta && now0 < delta) {  // end of day
		double value = Data[0][Obs][Line - MyObs->Freq + 1] / MyObs->Freq;

		if (now > Constants[0] && now < Constants[1] && ((Minus && value < 0.0) || !Minus)) {   //warning resolved by Manishankar.

			if (value < 0.0)
				value = -value;

			for (long ii = 0; ii < MyObs->Freq; ++ii) {
				if (Line - ii < 0) break; // incomplete first day
				Data[Vs - 1][Obs][Line - ii] = value;
			}
		}
		else {
			for (long ii = 0; ii < MyObs->Freq; ++ii) {
				if (Line - ii < 0) break; // incomplete first day
				Data[Vs - 1][Obs][Line - ii] = Data[0][Obs][Line - ii];
			}
		}
	}
}