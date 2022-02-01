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
