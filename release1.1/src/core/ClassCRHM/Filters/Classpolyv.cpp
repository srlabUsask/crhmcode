#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassFtoC.h"

using namespace std;

Classpolyv::Classpolyv(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classpolyv::doFunc(long Obs, long Line) {

	double x = Data[0][Obs][Line];
	Data[Vs - 1][Obs][Line] = (double)(Constants[0] + Constants[1] * x +
		Constants[2] * x * x +
		Constants[3] * x * x * x +
		Constants[4] * x * x * x * x);
}