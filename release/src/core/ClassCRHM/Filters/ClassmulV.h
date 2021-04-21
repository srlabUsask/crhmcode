#pragma once

#ifndef CLASSMULV
#define CLASSMULV

#include "../Classfilter.h"

class ClassmulV : Classfilter {
public:

	ClassmulV(ClassData* MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSMULV
