#pragma once

#ifndef CLASSMISSING0
#define CLASSMISSING0

#include "../Classfilter.h"

class ClassMissing0 : Classfilter {
public:

	ClassMissing0(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSMISSING0
