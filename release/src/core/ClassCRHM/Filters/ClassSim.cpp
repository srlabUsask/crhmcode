#include "../Classfilter.h"
#include "ClassSim.h"
#include <GlobalDll.h>


using namespace std;

ClassSim::ClassSim(ClassData* MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();

	MyObs->Simulation = true;
	MyObs->Dt1 = Constants[0];
	MyObs->Dt2 = Constants[1];
	MyObs->Interval = Constants[2] / 24.0;
	MyObs->Freq = (long)(1.0 / MyObs->Interval + 1.0 / 192.0);
	MyObs->Lines = (long)(ceil(MyObs->Dt2 - MyObs->Dt1) * MyObs->Freq);
	MyObs->IndxMin = 0;
	MyObs->IndxMax = (long)(floor((MyObs->Dt2 - MyObs->Dt1) * MyObs->Freq + MyObs->Interval / 2.0) - 1);

	// first data file?  Following necessary for use by filters
	if (Global::DTstart == 0.0) {
		Global::DTstart = floor(MyObs->Dt1);
		Global::DTend = floor(MyObs->Dt2);
		Global::DTnow = Global::DTstart;
		Global::Freq = MyObs->Freq;
		Global::Interval = MyObs->Interval;
	}

	if (Global::DTend == 0.0) Global::DTend = MyObs->Dt2;
	if (Global::DTend != 0.0 && Global::DTend < MyObs->Dt2) MyObs->Dt2 = Global::DTend;
}

void ClassSim::doFunc(long Obs, long Line) {
	// do nothing
}