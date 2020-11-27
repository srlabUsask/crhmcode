#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassMissingC.h"

using namespace std;

void ClassMissingC::doFunc(long Obs, long Line) {

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = (double)Constants[2];
	else
		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
}