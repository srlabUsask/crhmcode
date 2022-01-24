#include "../Classfilter.h"
#include "Classpowv.h"

using namespace std;

Classpowv::Classpowv(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error) {
		A = (double)Constants[0];
		B = (double)Constants[1];
	}
}

void Classpowv::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = A * pow(Data[0][Obs][Line], B);
}