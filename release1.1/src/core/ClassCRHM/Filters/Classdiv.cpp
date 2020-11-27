#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classdiv.h"

using namespace std;

Classdiv::Classdiv(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classdiv::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] / (double)Constants[0];
}