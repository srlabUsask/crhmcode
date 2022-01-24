#include "../Classfilter.h"
#include "Classsquare.h"

using namespace std;

Classsquare::Classsquare(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classsquare::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			period = (long)(Constants[0] * MyObs->Freq);
			phase = (long)(Constants[1] * MyObs->Freq);

			if (Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
				delay = (long)((Constants[2] - MyObs->Dt1) * MyObs->Freq - 1);
			else
				delay = -1;

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
		else {
			if (((Line + phase) % period) >= period / 2)
				Data[Vs - 1][Obs][Line] = 0.0;
			else
				Data[Vs - 1][Obs][Line] = 1.0;
		}
	}
}