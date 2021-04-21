#pragma once

#ifndef CLASSMISSINGFLAG
#define CLASSMISSINGFLAG

#include "../Classfilter.h"

class ClassMissingFlag : Classfilter {
public:

	ClassMissingFlag(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSMISSINGFLAG
