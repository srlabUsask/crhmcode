#pragma once

#ifndef CLASSLOG
#define CLASSLOG

#include "../Classfilter.h"

class Classlog : Classfilter {
public:
	long delay{ 0 };
	long duration{ 0 };
	double A{ 0.0 };
	double B{ 0.0 };
	Classlog(ClassData* MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSLOG
