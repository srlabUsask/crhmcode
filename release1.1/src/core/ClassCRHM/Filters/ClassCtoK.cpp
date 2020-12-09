#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassCtoK.h"

using namespace std;

ClassCtoK::ClassCtoK(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassCtoK::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (double)((Data[0][Obs][Line] + 273.15));
}