#pragma once

#ifndef CLASSSUB
#define CLASSSUB

#include "../Classfilter.h"

class Classsub : Classfilter {
public:

	Classsub(ClassData* MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSSUB
