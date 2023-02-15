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
#include "Classcos.h"

Classcos::Classcos(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classcos::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			period = (long)(Constants[0] * MyObs->Freq);
			phase = (long)(Constants[1] * MyObs->Freq);

			if (Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
				delay = (long)((Constants[2] - MyObs->Dt1) * MyObs->Freq);
			else
				delay = 0;

			if (Constants[3] > 0.0) {
				duration = (long)((Constants[3] - MyObs->Dt1) * MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = (double)cos((double(Line) / period - double(phase) / period) * 2 * M_PI);
	}
}

using namespace std;