#include "../Classfilter.h"
#include "ClassFtoC.h"

using namespace std;

Classlog::Classlog(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classlog::doFunc(long Obs, long Line) {

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

			A = (double)Constants[2];
			B = (double)fabs(Constants[3]);

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = A * log(B * double(static_cast<long long>(Line) - static_cast<long long>(delay)) / MyObs->Freq);
	}
}