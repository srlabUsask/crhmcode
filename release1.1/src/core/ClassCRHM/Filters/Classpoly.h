#pragma once

#ifndef CLASSPOLY
#define CLASSPOLY

#include "../Classfilter.h"

class Classpoly : Classfilter {
public:
	long delay{ 0 };
	long duration{ 0 };
	Classpoly(ClassData* MyObs, string ToVar, string args, string argtypes = "CCCCCCC");

	virtual void doFunc(long Obs, long Line);
	virtual string GetFilterName(void) { return typeid(*this).name(); }
};

#endif // !CLASSPOLY
