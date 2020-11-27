#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassMissingFlagAfter.h"

using namespace std;

void ClassMissingFlagAfter::doFunc(long Obs, long Line) {

	if (FirstTime) {
		First = Line;
		FirstTime = false;
	}
	else
		Last = Line;
}

ClassMissingFlagAfter::~ClassMissingFlagAfter() {

	for (int Obs = 0; Obs < ObsCnt; ++Obs)
		for (int Line = First; Line <= Last; ++Line) {
			if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
				Data[Vs - 1][Obs][Line] = 1.0;
			else
				Data[Vs - 1][Obs][Line] = 0.0;
		}
}