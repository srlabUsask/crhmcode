#pragma once

#ifndef CLASSPULSE
#define CLASSPULSE

#include "../Classfilter.h"

class Classpulse : Classfilter {
public:
	long delay{ 0 };
	long duration{ 0 };
	Classpulse(ClassData* MyObs, string ToVar, string args, string argtypes = "CC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSPULSE
