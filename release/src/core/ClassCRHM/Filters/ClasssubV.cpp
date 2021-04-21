#include "../Classfilter.h"
#include "ClasssubV.h"

using namespace std;

ClasssubV::ClasssubV(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClasssubV::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] - Data[1][Obs][Line];
}