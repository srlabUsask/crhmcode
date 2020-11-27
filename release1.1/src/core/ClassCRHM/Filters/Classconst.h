#pragma once

#ifndef CLASSCONST
#define CLASSCONST

#include "../Classfilter.h"

class Classconst : Classfilter {
public:

	Classconst(ClassData* MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSCONST
