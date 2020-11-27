#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classtime.h"
#include "../../GlobalDll.h"

using namespace std;

Classtime::Classtime(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classtime::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			option = (int)Constants[0];
			if (option)
				start = 0.0;
			else
				start = floor(Global::DTstart);

			FirstTime = false;
		}

		Data[Vs - 1][Obs][Line] = double(start + Line / double(MyObs->Freq));
	}
}