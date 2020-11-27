#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassMissingrepl.h"

using namespace std;

void ClassMissingrepl::doFunc(long Obs, long Line) {

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = Data[1][Obs][Line];
	else
		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
}