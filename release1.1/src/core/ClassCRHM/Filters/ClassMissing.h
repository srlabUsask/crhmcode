#pragma once

#ifndef CLASSMISSING
#define CLASSMISSING

#include "../Classfilter.h"

class ClassMissing : Classfilter {
public:

	ClassMissing(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC");
	~ClassMissing();

	double* GoodData;

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSMISSING
