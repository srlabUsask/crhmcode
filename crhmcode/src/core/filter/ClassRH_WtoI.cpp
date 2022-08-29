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
#include "ClassRH_WtoI.h"

using namespace std;

ClassRH_WtoI::ClassRH_WtoI(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassRH_WtoI::doFunc(long Obs, long Line) {

	double T = Data[0][Obs][Line];
	double RH = Data[1][Obs][Line];

	if (T < 0.0)
		Data[Vs - 1][Obs][Line] = (double)(RH * 0.9995 * exp(22.452 * T / (272.55 + T)) / exp(17.502 * T / (240.97 + T)));
	else
		Data[Vs - 1][Obs][Line] = RH;
}