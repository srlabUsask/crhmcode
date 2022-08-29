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

#ifndef CLASSMUSKINGUM
#define CLASSMUSKINGUM

#include "ClassModule.h"


class   ClassMuskingum {

public:
	ClassMuskingum(const double* inVar, double* outVar, const double* kstorage, const double* route_X_M, const double* lag, const long nhru, const long setlag = -1);
	~ClassMuskingum();
	void DoMuskingum();
	void DoMuskingum(const long hh);
	void ChangeLag(const double* newlag, const long hh);
	double Left(int hh);


	double* c0; // storage constant from K
	double* c1; // storage constant from K
	double* c2; // storage constant from K
	double prevdate{ 0.0 };

private:
	const double* kstorage{ NULL };
	const  double* inVar;
	double* outVar;

	double** LagArray;

	double* LastIn; //
	double* LastOut; //

	long nhru;
	long* maxlag; // maximum lag - i.e. storage

	long* ilag; // lag interval (hours)
	long* ulag; // lag interval (#intervals)
};

#endif // !CLASSMUSKINGUM
