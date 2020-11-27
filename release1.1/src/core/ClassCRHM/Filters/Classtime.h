#pragma once

#ifndef CLASSTIME
#define CLASSTIME

#include "../Classfilter.h"

class Classtime : Classfilter {
public:
	double start{ 0.0 };
	int option{ 0 };
	Classtime(ClassData* MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSTIME
