#pragma once

#ifndef CLASSMISSINGC
#define CLASSMISSINGC

#include "../Classfilter.h"

class ClassMissingC : Classfilter {
public:

	ClassMissingC(ClassData* MyObs, string ToVar, string args, string argtypes = "VCCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSMISSINGC
