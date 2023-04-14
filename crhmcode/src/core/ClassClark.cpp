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
#include "ClassClark.h"

ClassClark::ClassClark(const double* inVar, double* outVar, const double* kstorage, const double* lag, const long nhru, const long setlag)
	: inVar(inVar), outVar(outVar), kstorage(kstorage), nhru(nhru) {

	// kstorage (days)
	// lag (hours)

	LastIn = new double[nhru];
	LastOut = new double[nhru];

	c01 = new double[nhru];
	c2 = new double[nhru];
	NO_lag_release = new double[nhru];


	/*
	* ilag  for routing water along a stream, it is used to simulate the delay caused by the travel time of water.
	* ilag is the length of the stream (the number of elements or letters).
	* If on every cycle the water moves one step then the number of elements determines how many steps
	* are required to get to the end of the stream.
	*/
	ilag = new long[nhru];
	maxlag = new long[nhru];
	ulag = new long[nhru];

	for (long hh = 0; hh < nhru; hh++) {

		if (kstorage[hh] == 0.0) {
			c01[hh] = 0.0;
			c2[hh] = 0.0;
		} else {
			c01[hh] = Global::Interval * 0.5 / (kstorage[hh] + Global::Interval * 0.5);  // units of Global::Interval (days)
			c2[hh] = (kstorage[hh] - Global::Interval * 0.5) / (kstorage[hh] + Global::Interval * 0.5); // units of kstorage (days)
		}

        if ( (c01[hh] < 0.0) || (c2[hh] < 0.0) ) {
            string S = string("'") + " (Clark)' constants out of range (do not set Kstorage <- 0): " +
						to_string(c01[hh]).c_str() + "  " +
						to_string(c2[hh]).c_str() + "  " +
						to_string(kstorage[hh]).c_str() + "  ";
			// Raising an exception here would put the module into an undefined state maybe					
//            CRHMException TExcept(S.c_str(), TExcept::WARNING);
//            LogError(TExcept);
			printf(S.c_str());

//            CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
//            LogError(TExcept);
//            throw TExcept;
        }

		ilag[hh] = (long)(max<double>(lag[hh], 0.0) / 24.0 * Global::Freq + 1.1); // =1 for lag of zero

		if (setlag == -1 || ilag[hh] > setlag)
			maxlag[hh] = ilag[hh] + 1; // Quick fix
		else
			maxlag[hh] = setlag + 1; // Quick fix

		ulag[hh] = 0;

		LastIn[hh] = 0.0; // zero initial conditions
		LastOut[hh] = 0.0; // zero initial conditions
		NO_lag_release[hh] = 0.0; // released from storage
	}

	LagArray = new double* [nhru];   // create lag array

	for (long hh = 0; hh < nhru; hh++) {
		LagArray[hh] = new double[maxlag[hh]];
		for (long jj = 0; jj < maxlag[hh]; jj++)
			LagArray[hh][jj] = 0.0;
	}
}

ClassClark::~ClassClark() {
	delete[] LastIn;
	delete[] LastOut;
	delete[] c01;
	delete[] c2;
	delete[] NO_lag_release;
	delete[] ilag;
	delete[] maxlag;
	delete[] ulag;

	for (long hh = 0; hh < nhru; hh++)
		delete[] LagArray[hh];
	delete[] LagArray;
}

double ClassClark::ChangeStorage(const double* kstorage, const long hh)
{
	double Last_c01 = c01[hh];
	double Last_c2 = c2[hh];

	if (c2[hh] >= 1.0) // handles case of NO delay
		return 0.0;

	double Sstorage = (1.0 / (1.0 - c2[hh])) * (c01[hh] * LastIn[hh] + c2[hh] * outVar[hh]);

	if (kstorage[hh] == 0.0) {
		c01[hh] = 0.0;
		c2[hh] = 0.0;
	} else {
		c01[hh] = Global::Interval * 0.5 / (kstorage[hh] + Global::Interval * 0.5);  // units of Global::Interval (days)
		c2[hh] = (kstorage[hh] - Global::Interval * 0.5) / (kstorage[hh] + Global::Interval * 0.5); // units of kstorage (days)
	}

	if (Sstorage <= 0.0 || Last_c01 == c01[hh]) return 0.0;

	LastOut[hh] = (Sstorage * (1.0 - c2[hh]) - c01[hh] * LastIn[hh]) / c2[hh];

	//    Sstorage = (1.0/(1.0 - c2[hh]))*(c01[hh]*LastIn[hh] + c2[hh]*LastOut[hh]); // debug line

	return Sstorage;
}

double ClassClark::ChangeLag(const double* newlag, const long hh) {

	double LastValue;
	double Lag_storage = 0.0;

	long newilag = (long)(max<double>(newlag[hh], 0.0) / 24.0 * Global::Freq + 1.1); // =1 for lag of zero

	for (int ii = 1; ii < ilag[hh]; ++ii)
		Lag_storage += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];

	if (newilag == ilag[hh]) {
		return Lag_storage;
	}

	double* AccArray = new double[ilag[hh]]; // work area for ChangeLag
	AccArray[0] = 0.0;
	for (int ii = 1; ii < ilag[hh]; ++ii)
		AccArray[ii] = AccArray[ii - 1] + LagArray[hh][(ulag[hh] + ii) % ilag[hh]]; // accumulate storage

	NO_lag_release[hh] = 0.0;

	delete[] LagArray[hh]; // delete previous length

	LagArray[hh] = new double[newilag]; // create new length

	ulag[hh] = 0; // next input value save here.
	LagArray[hh][ulag[hh]] = 0; //

	for (int ii = 1; ii < newilag; ++ii) // clear remainder
		LagArray[hh][ii] = 0.0;

	if (newilag == 1) { // all storage is released
		NO_lag_release[hh] = AccArray[ilag[hh] - 1];
	}
	else if (ilag[hh] > 1 && AccArray[ilag[hh] - 1] > 0.0) {
		LastValue = 0.0;

		for (int mm = 1; mm < newilag - 1; ++mm) {
			double Y = double(mm) / ((long long)newilag - 1ll) * ((long long)ilag[hh] - 1ll);
			int Yint = (int)(Y + 0.0001);
			double Ydif = Y - Yint;
			double NewValue = AccArray[Yint] + Ydif * (AccArray[Yint + 1] - AccArray[Yint]);

			LagArray[hh][(ulag[hh] + mm) % newilag] = NewValue - LastValue;

			LastValue = NewValue;
		}

		LagArray[hh][(ulag[hh] + newilag - 1) % newilag] = AccArray[ilag[hh] - 1] - LastValue; // final values
	}
	// ilag == 1 and newilag > 1
	// if ilag == 1 or nothing in storage -> nothing to be done

	delete[] AccArray; // work area for ChangeLag

	ilag[hh] = newilag; // assign new lag

	return Lag_storage;
}

void ClassClark::DoClark() {

	for (long hh = 0; hh < nhru; hh++) {
		DoClark(hh);
	}
}

void ClassClark::DoClark(const long hh) {

	LagArray[hh][ulag[hh]] = inVar[hh] + NO_lag_release[hh];
	NO_lag_release[hh] = 0.0;

	ulag[hh] = ++ulag[hh] % ilag[hh];  // now points to fully delayed value

	if (c01[hh] == 0.0) {
		outVar[hh] = LagArray[hh][ulag[hh]];
	} else {
		outVar[hh] = c01[hh] * (LagArray[hh][ulag[hh]] + LastIn[hh]) + c2[hh] * LastOut[hh];
	}

	LastIn[hh] = LagArray[hh][ulag[hh]];

	LastOut[hh] = outVar[hh];
}

double ClassClark::Left(int hh) {

	double Slag = 0;

	for (int ii = 1; ii < ilag[hh]; ++ii)
		Slag += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];

	if (c2[hh] >= 1.0) return 0.0; // handles case of NO delay

	double Sstorage = (1.0 / (1.0 - c2[hh])) * (c01[hh] * LastIn[hh] + c2[hh] * outVar[hh]);

	return Slag + Sstorage;
}
