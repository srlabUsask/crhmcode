#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "Classsin.h"

using namespace std;

Classsin::Classsin(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classsin::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			period = (long)(Constants[0] * MyObs->Freq);
			phase = (long)(Constants[1] * MyObs->Freq);

			if (Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
				delay = (long)((Constants[2] - MyObs->Dt1) * MyObs->Freq);
			else
				delay = 0;

			if (Constants[3] > 0.0) {
				duration = (long)((Constants[3] - MyObs->Dt1) * MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = (double)sin((double(Line) / period - double(phase) / period) * 2 * M_PI);
	}
}