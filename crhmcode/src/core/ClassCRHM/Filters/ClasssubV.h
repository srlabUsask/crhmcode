#pragma once

#ifndef CLASSSUBV
#define CLASSSUBV

#include "../Classfilter.h"

class ClasssubV : Classfilter {
public:

	ClasssubV(ClassData* MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSSUBV
