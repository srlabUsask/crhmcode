#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classjulian.h"

using namespace std;

Classjulian::Classjulian(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error)
		option = (int)Constants[0];
}

void Classjulian::doFunc(long Obs, long Line) {

	switch (option) {
	case 0: Data[Vs - 1][Obs][Line] = (double)julian("now"); break;
	case 1: Data[Vs - 1][Obs][Line] = (double)julian("start"); break;
	case 2: Data[Vs - 1][Obs][Line] = (double)julian("end"); break;
	default:
		break;
	}
}