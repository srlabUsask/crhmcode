#pragma once

#ifndef CLASSEXPV
#define CLASSEXPV

#include "../Classfilter.h"

class Classexpv : Classfilter {
public:
	double A{ 0.0 };
	double B{ 0.0 };
	Classexpv(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSEXPV
