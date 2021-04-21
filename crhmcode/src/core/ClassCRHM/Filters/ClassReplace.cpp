#include "../Classfilter.h"
#include "ClassReplace.h"

using namespace std;

ClassReplace::ClassReplace(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassReplace::doFunc(long Obs, long Line) {

	long shift = thisVar->FileData->IndxMin;
	for (int Obs = 0; Obs < ObsCnt; ++Obs)
		outVar->FileData->Data[Obs + DataIndx[Vs - 1]][Line + shift] = Data[0][Obs][Line];
	//    outVar->FileData->Data[Obs][Line  + shift] = thisVar->FileData->Data[Obs][Line];

}