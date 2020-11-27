#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classsub.h"

using namespace std;

Classsub::Classsub(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classsub::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] - (double)Constants[0];
}