#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassFtoC.h"

using namespace std;

ClassFtoC::ClassFtoC(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassFtoC::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (double)((Data[0][Obs][Line] - 32.0) * 5.0 / 9.0);
}