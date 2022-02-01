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
