#include "../Classfilter.h"
#include "Classmul.h"

using namespace std;

Classmul::Classmul(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classmul::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] * (double)Constants[0];
}