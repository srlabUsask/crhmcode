#pragma once

#ifndef CLASSSIM
#define CLASSSIM

#include "../Classfilter.h"

class ClassSim : Classfilter {
public:

	ClassSim(ClassData* MyObs, string ToVar, string args, string argtypes = "CCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSSIM
