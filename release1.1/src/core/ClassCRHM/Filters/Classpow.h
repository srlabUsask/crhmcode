#pragma once

#ifndef CLASSPOW
#define CLASSPOW

#include "../Classfilter.h"

class Classpow : Classfilter {
public:
	long delay{ 0 };
	long duration{ 0 };
	double A{ 0.0 };
	double B{ 0.0 };
	Classpow(ClassData* MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSPOW
