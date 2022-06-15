#include "ClassMuskingum.h"


//---------------------------------------------------------------------------
ClassMuskingum::ClassMuskingum(const double* inVar, double* outVar, const double* k, const double* X_M, const double* lag, const long nhru, const long setlag)
	: inVar(inVar), outVar(outVar), nhru(nhru) {

	// !!! UNITS !!!

	// kstorage (days)
	// lag (hours)

	LastIn = new double[nhru];
	LastOut = new double[nhru];

	c0 = new double[nhru];
	c1 = new double[nhru];
	c2 = new double[nhru];

	/*
	* ilag  for routing water along a stream, it is used to simulate the delay caused by the travel time of water.
	* ilag is the length of the stream (the number of elements or letters).
	* If on every cycle the water moves one step then the number of elements determines how many steps
	* are required to get to the end of the stream.
	*/
	ilag = new long[nhru];
	maxlag = new long[nhru];
	ulag = new long[nhru];
	long Biggest = 0;

	for (long hh = 0; hh < nhru; hh++) {

		c0[hh] = (Global::Interval - 2.0 * k[hh] * X_M[hh]) /
			(2.0 * k[hh] * (1.0 - X_M[hh]) + Global::Interval);  // units of Global::Interval (days)

		c1[hh] = (Global::Interval + 2.0 * k[hh] * X_M[hh]) /
			(2.0 * k[hh] * (1.0 - X_M[hh]) + Global::Interval); // units of kstorage (days)

		c2[hh] = (2.0 * k[hh] * (1.0 - X_M[hh]) - Global::Interval) /
			(2.0 * k[hh] * (1.0 - X_M[hh]) + Global::Interval); // units of kstorage (days)

        if ( (c0[hh] < 0.0) || (c1[hh] < 0.0) || (c2[hh] < 0.0) ) {
            string S = string("'") + " (Muskingum)' constants out of range: " +
						to_string(c0[hh]).c_str() + "  " +
						to_string(c1[hh]).c_str() + "  " +
						to_string(c2[hh]).c_str() + "  " + 
						to_string(k[hh]).c_str() + "  " + 
						to_string(X_M[hh]).c_str() + "  ";
            CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
            LogError(TExcept);
            throw TExcept;
        }

		ilag[hh] = (long)(max<double>(lag[hh], 0.0) / 24.0 * Global::Freq + 1.1); // =1 for lag of zero

		if (setlag == -1 || ilag[hh] > setlag)
			maxlag[hh] = ilag[hh];
		else
			maxlag[hh] = setlag;

		ulag[hh] = 0;

		LastIn[hh] = 0.0; // zero initial conditions

		LastOut[hh] = 0.0; // zero initial conditions

		if (maxlag[hh] > Biggest) Biggest = maxlag[hh];
	}

	LagArray = new double* [nhru];   // create lag array

	for (long hh = 0; hh < nhru; hh++) {
		LagArray[hh] = new double[maxlag[hh]];
		for (long jj = 0; jj < maxlag[hh]; jj++)
			LagArray[hh][jj] = 0.0;
	}
}

ClassMuskingum::~ClassMuskingum() {
	delete[] LastIn;
	delete[] LastOut;
	delete[] c0;
	delete[] c1;
	delete[] c2;
	delete[] ilag;
	delete[] maxlag;
	delete[] ulag;

	for (long hh = 0; hh < nhru; hh++)
		delete[] LagArray[hh];
	delete[] LagArray;
}

void ClassMuskingum::ChangeLag(const double* newlag, const long hh)
{

	long newilag = (long)(max<double>(newlag[hh], 0.0) / 24.0 * Global::Freq + 1.1); // =1 for lag of zero

	if (newilag == ilag[hh]) {
		return;
	}

	double* AccArray = new double[ilag[hh]]; // work area for ChangeLag

	AccArray[0] = 0.0;

	for (int ii = 1; ii < ilag[hh]; ++ii)
	{
		AccArray[ii] = AccArray[ii - 1] + LagArray[hh][(ulag[hh] + ii) % ilag[hh]]; // accumulate storage
	}

	delete[] LagArray[hh]; // delete previous length

	LagArray[hh] = new double[newilag]; // create new length

	ulag[hh] = 0; // next input value save here.
	LagArray[hh][0] = 0.0; // looks better

	double LastValue = 0.0;

	for (int mm = 1; mm < newilag - 1; ++mm)
	{
		double Y = double(mm) / ((long long)newilag - 1ll) * ((long long)ilag[hh] - 1ll);
		int Yint = (int)(Y + 0.0001);
		if ((Yint + 1) > ilag[hh] - 1)
		{
			CRHMException Except("Attempting to read out of bounds array address", TExcept::TERMINATE);
			LogError(Except);
			throw(Except);
		}
		double Ydif = Y - Yint;


		double NewValue = AccArray[Yint] + Ydif * (AccArray[Yint + 1] - AccArray[Yint]);




		LagArray[hh][(ulag[hh] + mm) % newilag] = NewValue - LastValue;

		LastValue = NewValue;
	}

	LagArray[hh][(ulag[hh] + newilag - 1) % newilag] = AccArray[ilag[hh] - 1] - LastValue; // final values

	delete[] AccArray; // work area for ChangeLag

	ilag[hh] = newilag; // assign new lag
}

void ClassMuskingum::DoMuskingum() {

	for (long hh = 0; hh < nhru; hh++) {

		LagArray[hh][ulag[hh]] = inVar[hh];

		ulag[hh] = ++ulag[hh] % ilag[hh];

		outVar[hh] = c0[hh] * LagArray[hh][ulag[hh]] + c1[hh] * LastIn[hh] + c2[hh] * LastOut[hh];

		LastIn[hh] = LagArray[hh][ulag[hh]];

		LastOut[hh] = outVar[hh];
	}
}

void ClassMuskingum::DoMuskingum(const long hh) {

	LagArray[hh][ulag[hh]] = inVar[hh];

	ulag[hh] = ++ulag[hh] % ilag[hh];  // now points to fully delayed value

	outVar[hh] = c0[hh] * LagArray[hh][ulag[hh]] + c1[hh] * LastIn[hh] + c2[hh] * LastOut[hh];

	LastIn[hh] = LagArray[hh][ulag[hh]];

	LastOut[hh] = outVar[hh];
}

double ClassMuskingum::Left(int hh) {

	double Slag = 0;

	for (int ii = 1; ii < ilag[hh]; ++ii)
		Slag += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];

	double Sstorage = (1.0 / (1.0 - c2[hh])) * (c1[hh] * LastIn[hh] + c2[hh] * outVar[hh]);

	return Slag + Sstorage;
}

//---------------------------------------------------------------------------
