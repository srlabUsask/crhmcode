#pragma once

#ifndef CLASSEA
#define CLASSEA

class Classea : Classfilter {
public:
	Classea(ClassData* MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSEA
