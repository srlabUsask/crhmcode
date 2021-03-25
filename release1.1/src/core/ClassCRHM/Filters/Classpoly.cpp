#include "../Classfilter.h"
#include "Classpoly.h"

using namespace std;

Classpoly::Classpoly(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classpoly::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {

			if (Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
				delay = (long)((Constants[0] - MyObs->Dt1) * MyObs->Freq - 1);
			else
				delay = -1;

			if (Constants[1] > 0.0) {
				duration = (long)((Constants[1] - MyObs->Dt1) * MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else {
			double x = (static_cast<long long>(Line) - static_cast<long long>(delay) - 1) / double(MyObs->Freq);
			Data[Vs - 1][Obs][Line] = (double)(Constants[2] + Constants[3] * x + Constants[4] * x * x
				+ Constants[5] * x * x * x + Constants[6] * x * x * x * x);
		}
	}
}