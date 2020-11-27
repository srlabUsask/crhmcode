#pragma once

#ifndef CLASSADD
#define CLASSADD

#include "../Classfilter.h"

class Classadd : Classfilter {
public:

	Classadd(ClassData* MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSADD
