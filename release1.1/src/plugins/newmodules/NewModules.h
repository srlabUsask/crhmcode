// 11/28/19
//---------------------------------------------------------------------------

#ifndef OurModulesH
#define OurModulesH
//---------------------------------------------------------------------------

//#include "ClassModule.h"
//#include "ClassSnobalBase.h"

#include <string>


#include <stack>
#include <queue>

using namespace std;

extern "C" void  MoveModulesToGlobal(string DLLName = "CRHM");

float DepthofSnow(float SWE);
float SWEfromDepth(float Snow_Depth);
void ProbabilityThresholdNew(float SWE, float t, float Uten_Prob, float & Probability, float & Threshold, long Snow, float & SnowAge, long & DrySnow);
void Sum(float TQsalt, float TQsusp, float SBsum, float SBsalt, float & DriftH, float & SublH);
void Pbsm (float E_StubHt, float Uthr, float & DriftH, float & SublH,
           float t, float u, float rh, float Fetch, long N_S, float A_S);



#endif
