#pragma once

#ifndef CLASSPOWV
#define CLASSPOWV

#include "../Classfilter.h"

class Classpowv : Classfilter {
public:
	double A{ 0.0 };
	double B{ 0.0 };
	Classpowv(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSPOWV
