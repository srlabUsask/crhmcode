#include "../Classfilter.h"
#include "ClassdivV.h"

using namespace std;

ClassdivV::ClassdivV(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassdivV::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] / Data[1][Obs][Line];
}
