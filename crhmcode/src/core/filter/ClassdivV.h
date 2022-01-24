#pragma once

#ifndef CLASSDIVV
#define CLASSDIVV

#include "../Classfilter.h"

class ClassdivV : Classfilter {
public:

	ClassdivV(ClassData* MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSDIVV
