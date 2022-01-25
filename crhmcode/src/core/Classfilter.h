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


#include "Filters/ClassFtoC.h"
#include "Filters/ClassCtoK.h"
#include "Filters/ClassReplace.h"
#include "Filters/ClassKtoC.h"
#include "Filters/ClassTimeshift.h"
#include "Filters/ClassRH_WtoI.h"
#include "Filters/Classea.h"
#include "Filters/Classrh.h"
#include "Filters/Classsin.h"
#include "Filters/Classcos.h"
#include "Filters/Classabs.h"
#include "Filters/Classpulse.h"
#include "Filters/Classexp.h"
#include "Filters/Classexpv.h"
#include "Filters/Classpoly.h"
#include "Filters/Classpolyv.h"
#include "Filters/Classlog.h"
#include "Filters/Classlogv.h"
#include "Filters/Classpow.h"
#include "Filters/Classpowv.h"
#include "Filters/Classtime.h"
#include "Filters/Classjulian.h"
#include "Filters/Classrandom.h"
#include "Filters/Classrefwind.h"
#include "Filters/Classsquare.h"
#include "Filters/Classramp.h"
#include "Filters/Classadd.h"
#include "Filters/Classsub.h"
#include "Filters/Classmul.h"
#include "Filters/Classdiv.h"
#include "Filters/ClassaddV.h"
#include "Filters/ClasssubV.h"
#include "Filters/ClassmulV.h"
#include "Filters/ClassdivV.h"
#include "Filters/Classconst.h"
#include "Filters/ClassSim.h"
#include "Filters/ClassSmear.h"
#include "Filters/ClassMissing.h"
#include "Filters/ClassMissingInter.h"
#include "Filters/ClassMissing0.h"
#include "Filters/ClassMissingC.h"
#include "Filters/ClassMissingFlag.h"
#include "Filters/ClassMissingFlagAfter.h"
#include "Filters/ClassMissingrepl.h"
#include "Filters/ClassForce.h"


#endif // !CLASSFILTER
