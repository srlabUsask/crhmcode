#pragma once

#ifndef CLASSMISSINGFLAGAFTER
#define CLASSMISSINGFLAGAFTER

#include "../Classfilter.h"

class ClassMissingFlagAfter : Classfilter {
public:

	ClassMissingFlagAfter(ClassData* MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};
	~ClassMissingFlagAfter();

	long First{ 0 };
	long Last{ 0 };

	virtual void doFunc(long Obs, long Line);
};


#endif // !CLASSMISSINGFLAGAFTER
