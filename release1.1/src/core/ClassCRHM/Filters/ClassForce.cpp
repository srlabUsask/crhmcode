#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassForce.h"

using namespace std;

void ClassForce::doFunc(long Obs, long Line) {
	// do nothing
}

ClassForce::ClassForce(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();

	if (MyObs->FilterCnt > 0)
		error("ForceFilter filter must be the first filter.");

	if (Constants[0] > 288)
		error("ForceFilter filter interval cannot be less than 5 minutes ");

	if (Constants[0] < 1)
		error("ForceFilter filter interval cannot be greater than daily ");

	MyObs->ForceInterval = (long)Constants[0];
}