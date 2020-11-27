#if defined(_WIN32)
#include "stdafx.h"
#endif

#include "../Classfilter.h"
#include "ClassMissing.h"

using namespace std;

ClassMissing::ClassMissing(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes), GoodData(NULL) {
	readargs();
	GoodData = new double[ObsCnt];
}


void ClassMissing::doFunc(long Obs, long Line) {
	static bool Warned = false;

	if (FirstTime) {
		if ((Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1]) && !Warned) {
			////Application->MessageBox(MyObs->DataFileName.c_str(), "Missing data in first interval of filter 'missing'", MB_OK);
			LogError("Missing data in first interval of " + MyObs->DataFileName, TExcept::WARNING);
			Warned = true;
		}

		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
		GoodData[Obs] = Data[0][Obs][Line];
		if (Obs + 1 >= ObsCnt)  FirstTime = false;
		return;
	}

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = GoodData[Obs];
	else {
		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
		GoodData[Obs] = Data[0][Obs][Line];
	}
}

ClassMissing::~ClassMissing() {
	delete[] GoodData;
}
