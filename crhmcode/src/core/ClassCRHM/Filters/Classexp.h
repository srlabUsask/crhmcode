#pragma once

#ifndef CLASSEXP
#define CLASSEXP

#include "../Classfilter.h"

class Classexp : Classfilter {
public:
	long delay{ 0 };
	long duration{ 0 };
	double A{ 0.0 };
	double B{ 0.0 };
	Classexp(ClassData* MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSEXP
