#pragma once

#ifndef CLASSMUL
#define CLASSMUL

#include "../Classfilter.h"

class Classmul : Classfilter {
public:

	Classmul(ClassData* MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSMUL
