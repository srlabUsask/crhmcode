#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassTimeshift.h"

using namespace std;

ClassTimeshift::ClassTimeshift(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();

	MyObs->TimeShiftFilter = (double)Constants[0];
}