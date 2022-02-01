#include "../Classfilter.h"
#include "Classlogv.h"

using namespace std;

Classlogv::Classlogv(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error) {
		A = (double)fabs(Constants[0]);
		B = (double)fabs(Constants[1]);
	}
}

void Classlogv::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = A * log(B * Data[0][Obs][Line]);
}