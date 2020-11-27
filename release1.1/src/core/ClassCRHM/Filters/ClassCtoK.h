#pragma once

#ifndef CLASSCTOK
#define CLASSTOK

#include "../Classfilter.h"

class ClassCtoK : Classfilter {
public:
	ClassCtoK(ClassData* MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSCTOK


