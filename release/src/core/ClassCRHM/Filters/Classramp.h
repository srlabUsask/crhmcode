#pragma once

#ifndef CLASSRAMP
#define CLASSRAMP

#include "../Classfilter.h"

class Classramp : Classfilter {
public:
	long period{ 0 };
	long phase{ 0 };
	long delay{ 0 };
	long duration{ 0 };
	Classramp(ClassData* MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSRAMP
