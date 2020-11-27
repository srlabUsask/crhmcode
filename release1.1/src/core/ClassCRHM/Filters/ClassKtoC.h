#pragma once

#ifndef CLASSKTOC
#define CLASSKTOC

#include "../Classfilter.h"

class ClassKtoC : Classfilter {
public:
	ClassKtoC(ClassData* MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSKTOC
