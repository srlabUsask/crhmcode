#pragma once

#ifndef CLASSFORCE
#define CLASSFORCE

#include "../Classfilter.h"

class ClassForce : Classfilter {
public:

	ClassForce(ClassData* MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSFORCE
