#pragma once

#ifndef CLASSREFWIND
#define CLASSREFWIND

#include "../Classfilter.h"

class Classrefwind : Classfilter {
public:
	double Const{ 0.0 }; // result log((Z2 - d)/Z)/log((Zm - d)/Z)

	Classrefwind(ClassData* MyObs, string ToVar, string args, string argtypes = "VCCC");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSREFWIND
