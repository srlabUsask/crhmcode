#include "../Classfilter.h"
#include "Classconst.h"

using namespace std;

Classconst::Classconst(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classconst::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (double)Constants[0];
}