#pragma once

#ifndef CLASSSQUARE
#define CLASSSQUARE

#include "../Classfilter.h"

class Classsquare : Classfilter {
public:
	long period{ 0 };
	long phase{ 0 };
	long delay{ 0 };
	long duration{ 0 };
	Classsquare(ClassData* MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSSQUARE
