#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classrefwind.h"

using namespace std;

Classrefwind::Classrefwind(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {

	readargs();
	if (!Error) {
		double d = (double)(Constants[2] * 2.0 / 3.0);  // zero plane
		double Z = (double)(Constants[2] * 0.123);    // roughness
		Const = (double)(log((Constants[1] - d) / Z) / log((Constants[0] - d) / Z));
	}
}

void Classrefwind::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] * Const;
}