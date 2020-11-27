#pragma once

#ifndef CLASSMISSINGREPL
#define CLASSMISSINGREPL

#include "../Classfilter.h"

class ClassMissingrepl : Classfilter {
public:

	ClassMissingrepl(ClassData* MyObs, string ToVar, string args, string argtypes = "VCCV") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSMISSINGREPL
