#pragma once
#ifndef CLASSRH_WTOI
#define CLASSRH_WTOI

#include "../Classfilter.h"

class ClassRH_WtoI : Classfilter {
public:
	ClassRH_WtoI(ClassData* MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

#endif // !CLASSRH_WTOI
