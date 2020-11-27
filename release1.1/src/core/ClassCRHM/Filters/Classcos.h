#pragma once

#ifndef CLASSCOS
#define CLASSCOS

#include "../Classfilter.h"

class Classcos : Classfilter {
public:
	long period{ 0 };
	long phase{ 0 };
	long delay{ 0 };
	long duration{ 0 };
	Classcos(ClassData* MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSCOS
