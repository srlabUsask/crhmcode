#pragma once

#ifndef CLASSSMEAR
#define CLASSSMEAR

#include "../Classfilter.h"

class  ClassSmear : Classfilter {
public:

	ClassSmear(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC");

	bool Minus;

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSSMEAR
