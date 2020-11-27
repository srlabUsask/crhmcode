#pragma once

#ifndef CLASSMISSINGINTER
#define CLASSMISSINGINTER

#include "../Classfilter.h"

class ClassMissingInter : Classfilter {
public:

	ClassMissingInter(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC");
	~ClassMissingInter();

	bool FirstTime{ true };
	double* GoodData;
	long* LastGoodData;

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSMISSINGINTER
