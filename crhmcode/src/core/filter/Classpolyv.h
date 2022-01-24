#pragma once

#ifndef CLASSPOLYV
#define CLASSPOLYV

#include "../Classfilter.h"

class Classpolyv : Classfilter {
public:
	Classpolyv(ClassData* MyObs, string ToVar, string args, string argtypes = "VCCCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSPOLYV
