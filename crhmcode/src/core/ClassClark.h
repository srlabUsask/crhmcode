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

#ifndef CLASSCLARK
#define CLASSCLARK

#include "ClassModule.h"

class   ClassClark {

public:
	ClassClark(const double* inVar, double* outVar, const double* kstorage, const double* lag, const long nhru, const long setlag = -1);
	~ClassClark();
	void DoClark();
	void DoClark(const long hh);
	double ChangeStorage(const double* kstorage, const long hh);
	double ChangeLag(const double* newlag, const long hh);
	double Left(int hh);

private:
	const double* kstorage;
	const  double* inVar;
	double* outVar;

	double** LagArray;

	double* LastIn; //
	double* LastOut; //

	double* c01; // storage constant from K
	double* c2;  // storage constant from K
	double* NO_lag_release;  // released from storage when lag set to zero

	long nhru;
	long* maxlag; // maximum lag - i.e. storage

	long* ilag; // lag interval (hours)
	long* ulag; // lag interval (#intervals)

};

#endif // !CLASSCLARK
