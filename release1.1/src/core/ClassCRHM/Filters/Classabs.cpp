#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classabs.h"

using namespace std;

Classabs::Classabs(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classabs::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = abs(Data[0][Obs][Line]);
}