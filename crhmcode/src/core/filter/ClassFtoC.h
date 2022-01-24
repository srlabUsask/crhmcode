#pragma once

#ifndef CLASSFTOC
#define CLASSFTOC

#include "../Classfilter.h"

class ClassFtoC : Classfilter {
public:
	ClassFtoC(ClassData* MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSFTOC
