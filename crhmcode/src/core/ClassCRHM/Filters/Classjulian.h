#pragma once

#ifndef CLASSJULIAN
#define CLASSJULIAN

#include "../Classfilter.h"

class Classjulian : Classfilter {
public:
	int option{ 0 };
	Classjulian(ClassData* MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSJULIAN
