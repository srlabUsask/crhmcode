#pragma once

#ifndef CLASSRH
#define CLASSRH

#include "../Classfilter.h"

class Classrh : Classfilter {
public:
	Classrh(ClassData* MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSRH
