#pragma once

#ifndef CLASSREPLACE
#define CLASSREPLACE

#include "../Classfilter.h"

class ClassReplace : Classfilter {
public:
	ClassReplace(ClassData* MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSREPLACE
