#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classea.h"

using namespace std;

Classea::Classea(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classea::doFunc(long Obs, long Line) {

	if (Line == MyObs->IndxMax) // wait till last
		for (int Obs = 0; Obs < ObsCnt; ++Obs)
			for (long Line = MyObs->IndxMin; Line <= MyObs->IndxMax; ++Line)
				Data[Vs - 1][Obs][Line] = (double)(estar(Data[0][Obs][Line]) * Data[1][Obs][Line] / 100.0);
}