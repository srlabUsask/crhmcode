#pragma once

#ifndef CLASSADDV
#define CLASSADDV

#include "../Classfilter.h"

class ClassaddV : Classfilter {
public:

	ClassaddV(ClassData* MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSADDV
