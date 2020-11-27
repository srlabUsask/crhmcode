#pragma once

#ifndef CLASSSIN
#define CLASSSIN

#include "../Classfilter.h"

class Classsin : Classfilter {
public:
	long period{ 0 };
	long phase{ 0 };
	long delay{ 0 };
	long duration{ 0 };
	Classsin(ClassData* MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSSIN
