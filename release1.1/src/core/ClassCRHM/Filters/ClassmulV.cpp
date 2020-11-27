#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassmulV.h"

using namespace std;

ClassmulV::ClassmulV(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassmulV::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] * Data[1][Obs][Line];
}