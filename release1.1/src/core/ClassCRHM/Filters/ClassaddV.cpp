#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassaddV.h"

using namespace std;

ClassaddV::ClassaddV(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassaddV::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] + Data[1][Obs][Line];
}