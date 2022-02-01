#pragma once

#ifndef CLASSFILTER
#define CLASSFILTER

#include "ClassCRHM.h"

using namespace std;

class Classfilter {
public:
	ClassData* MyObs;

	string ToVar;
	string argtypes;
	string args;

	long Vs;
	long Cs;
	bool Error;
	long ObsCnt;
	long TotalCnt; // when created;
	bool FirstTime;

	long* DataIndx{ NULL };    // Vs offsets
	long* DataObsCnt{ NULL };  // maximum number of observations
	double*** Data{ NULL };     // Data[Vs selection][Obs][line]
	double* Constants{ NULL }; // constant data

	ClassVar* thisVar{ NULL }; // last arg accessed
	ClassVar* outVar{ NULL }; // ToVar

	Classfilter(ClassData* MyObs, string ToVar, string args, string argtypes);

	virtual ~Classfilter();

	virtual void readargs();
	virtual void error(string Mess);
	void fixup(void);
	virtual void doFunc(long Obs, long Line) { Data[0][Obs][Line] = 0.0; }
	virtual void doFunctions(long Line);
};

double estar(double t);


#include "filter/ClassFtoC.h"
#include "filter/ClassCtoK.h"
#include "filter/ClassReplace.h"
#include "filter/ClassKtoC.h"
#include "filter/ClassTimeshift.h"
#include "filter/ClassRH_WtoI.h"
#include "filter/Classea.h"
#include "filter/Classrh.h"
#include "filter/Classsin.h"
#include "filter/Classcos.h"
#include "filter/Classabs.h"
#include "filter/Classpulse.h"
#include "filter/Classexp.h"
#include "filter/Classexpv.h"
#include "filter/Classpoly.h"
#include "filter/Classpolyv.h"
#include "filter/Classlog.h"
#include "filter/Classlogv.h"
#include "filter/Classpow.h"
#include "filter/Classpowv.h"
#include "filter/Classtime.h"
#include "filter/Classjulian.h"
#include "filter/Classrandom.h"
#include "filter/Classrefwind.h"
#include "filter/Classsquare.h"
#include "filter/Classramp.h"
#include "filter/Classadd.h"
#include "filter/Classsub.h"
#include "filter/Classmul.h"
#include "filter/Classdiv.h"
#include "filter/ClassaddV.h"
#include "filter/ClasssubV.h"
#include "filter/ClassmulV.h"
#include "filter/ClassdivV.h"
#include "filter/Classconst.h"
#include "filter/ClassSim.h"
#include "filter/ClassSmear.h"
#include "filter/ClassMissing.h"
#include "filter/ClassMissingInter.h"
#include "filter/ClassMissing0.h"
#include "filter/ClassMissingC.h"
#include "filter/ClassMissingFlag.h"
#include "filter/ClassMissingFlagAfter.h"
#include "filter/ClassMissingrepl.h"
#include "filter/ClassForce.h"


#endif // !CLASSFILTER
