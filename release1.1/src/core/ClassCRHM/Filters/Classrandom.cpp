#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassFtoC.h"

using namespace std;

Classrandom::Classrandom(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error)
		srand((unsigned)Constants[0]);
}

void Classrandom::doFunc(long Obs, long Line) {
	Data[Vs - 1][Obs][Line] = (double)rand() / RAND_MAX;
}