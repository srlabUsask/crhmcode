#include "../Classfilter.h"
#include "ClassFtoC.h"

using namespace std;

Classadd::Classadd(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classadd::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] + (double)Constants[0];
}