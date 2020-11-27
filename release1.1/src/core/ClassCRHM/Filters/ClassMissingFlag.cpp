#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassMissingFlag.h"

using namespace std;

void ClassMissingFlag::doFunc(long Obs, long Line) {

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = 1.0;
	else
		Data[Vs - 1][Obs][Line] = 0.0;
}