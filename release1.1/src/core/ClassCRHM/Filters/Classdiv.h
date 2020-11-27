#pragma once

#ifndef CLASSDIV
#define CLASSDIV

#include "../Classfilter.h"

class Classdiv : Classfilter {
public:

	Classdiv(ClassData* MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSDIV
