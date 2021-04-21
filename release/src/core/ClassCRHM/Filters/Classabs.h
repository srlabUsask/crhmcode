#pragma once

#ifndef CLASSABS
#define CLASSABS

#include "../Classfilter.h"

class Classabs : Classfilter {
public:
	Classabs(ClassData* MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSABS
