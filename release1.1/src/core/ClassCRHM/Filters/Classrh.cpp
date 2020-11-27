#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classrh.h"

using namespace std;

Classrh::Classrh(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classrh::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (double)(Data[1][Obs][Line] / estar(Data[0][Obs][Line]) * 100.0);
}