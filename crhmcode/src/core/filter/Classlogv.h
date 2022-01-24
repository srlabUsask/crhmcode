#pragma once

#ifndef CLASSLOGV
#define CLASSLOGV

#include "../Classfilter.h"

class Classlogv : Classfilter {
public:
	double A{ 0.0 };
	double B{ 0.0 };
	Classlogv(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSLOGV
