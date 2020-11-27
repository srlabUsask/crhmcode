#pragma once

#ifndef CLASSRANDOM
#define CLASSRANDOM

#include "../Classfilter.h"

class Classrandom : Classfilter {
public:
	Classrandom(ClassData* MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSRANDOM
