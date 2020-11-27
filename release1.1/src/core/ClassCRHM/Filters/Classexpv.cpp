#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classexpv.h"

using namespace std;

Classexpv::Classexpv(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error) {
		A = (double)Constants[0];
		B = (double)Constants[0];
	}
}

void Classexpv::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = A * exp(B * Data[0][Obs][Line]);
}