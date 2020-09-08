
#pragma once
// 12/19/16

//---------------------------------------------------------------------------

#ifndef GlobalDllH
#define GlobalDllH
//---------------------------------------------------------------------------

#include "GlobalCommon.h"
#include <ctime>
#include "Common.h"
#include "StandardConverterUtility.h"
#include "TStringList.h"

#include <map>
//#include "ClassCRHM.h"

using namespace std;

//newly added
typedef double TDateTime;

class   Global {
public:

	//newly added by Banani
	typedef unsigned short Word;

	static bool NaNcheck;
	static bool LOGVARLOAD;

	static long GroupCntTrk;
	static long StructCntTrk;

	static long Freq;

	static long DTindx;
	static long DTmin;
	static long DTmax;
	static long IndxMin;
	static long IndxMax;

	static long maxobs;
	static long maxlay;
	static long maxhru;

	static long nobs;
	static long nlay;
	static long nhru;

	static long CRHMStatus;
	static long CurrentModuleRun;
	static long CRHMControlSaveCnt;

	static BitSet RunUpBitSet; // determines modules executed during looping.
	static BitSet ModuleBitSet; // determines modules executed during calculating ahead.

	static double Interval;
	static double DTstart;
	static double DTend;

	static TDateTime DTnow;

	static TDateTime RapidAdvanceTo;
	static TDateTime LoopTo;
	static long LoopCnt;
	static long LoopCntDown;

	static CRHM::TBuild BuildFlag;
	static CRHM::TIMEFORMAT TimeFormat;

	static MapVar MapVars;     // DECL
	static MapVar MapVarsGet;  // INIT
	static MapVar MapVarsPut;  // INIT
	static MapVar MapObsGet;   // INIT
	static MapPar MapPars;     // DECL
	static MapPar SharedMapPars; // DECL

	static Mapstr Mapgetvar;   // BUILD
	static Mapstr Mapputvar;   // BUILD
	static Mapstr Mapreadvar;  // BUILD
	static Mapstr Mapdeclvar;  // BUILD
	static Mapstr Mapdeclpar;  // BUILD
	static Mapstr Mapdeclobs;  // BUILD
	static Mapstr Mapdeclstat; // BUILD, state variable list
	static Mapstr2 MapAKA;

	static TStringList *AllModulesList;       // modules defined in CRHM
	static TStringList *OurModulesList;       // modules defined in current model
	static TStringList *MacroModulesList;     // custom modules defined in current model
	static TStringList *AllModelsList;        // models defined in CRHM
	static TStringList *ModelModulesList;     // modules used in above models in CommaText
	static TStringList *OurHelpList;          // help files defined in current modules
	static TStringList *PendingDLLModuleList; // current DLL modules
	static TStringList *ReportList;           //
	static TStringList *DeclRootList;         //
	static TStringList *OldModuleName;        // used to upgrade module names
	static TStringList *NewModuleName;        // used to upgrade module names

											  //static HWND crhmMain;
											  //static HWND crhmLog;

	static float * lapse_rate; // used for array observations adjustments
	static float * ppt_adj; // used for array observations adjustments
	static float * hru_elev; // used for array observations adjustments
	static float * obs_elev;
	static float ** OBS_ELEV; // used for array observations adjustments

	static float * Warming_t; // used for climate warming
	static float * Warming_p; // used for climate warming
	static long  * RH_VP_flag; // used for elevation change. -> 0 maintain rh, 1 -> maintain ea
	static long  * RH_VP_flag2; // used for climate warming. -> 0 maintain rh, 1 -> maintain ea
	static long   RH_EA_flag; // used for climate warming
	static long    RH_EA_obs; // 0 -> rh obs, 1 -> ea obs
	static long    OBS_AS_IS; // 0 -> process obs, 1 -> no processing
	static long    WQ_prj; // true -> processing WQ modules

	static long  ** HRU_OBS; // used for array observations
	static long  ** HRU_OBS_DIRECT; // used for array observations
	static float ** obs_t; // used for array observations adjustments
	static float ** obs_ea; // used for array observations adjustments
	static float ** obs_rh; // used for array observations adjustments
	static float ** obs_t_obs; // used for array observations adjustments

	static TObject *thisVar;
};


//Mani added this from TStringList.

string static FloatToStrF(float value, string format, int precision, int digits) {
	stringstream stream;

	//float minVal = 3000.14159265359;

	if (strcmp(format.c_str(), "ffFixed"))
		format = "fixed";
	stream << format << setprecision(precision) << value;
	return stream.str();
};

string static FloatToStrF(float X, TFloatFormat Format, int Prec, int Digits) {
	ostringstream temp;
	if (Format == ffFixed) {
		temp.precision(Prec);
		temp.width(Digits);
		temp << X;
	}
	else { // assume ffGeneral
		temp.precision(Prec);
		temp.width(Digits);
		temp << X;
	}
	return temp.str();
}

string static FloatToStrF(double X, TFloatFormat Format, int Prec, int Digits) {
	ostringstream temp;
	if (Format == ffFixed) {
		temp.precision(Prec);
		temp.width(Digits);
		temp << X;
	}
	else { // assume ffGeneral
		temp.precision(Prec);
		temp.width(Digits);
		temp << X;
	}
	return temp.str();
}

string static FloatToStrF(long L, TFloatFormat Format, int Prec, int Digits) {
	ostringstream temp;
	if (Format == ffFixed) {
		temp.precision(Prec);
		temp.width(Digits);
		temp << L;
	}
	else { // assume ffGeneral
		temp.precision(Prec);
		temp.width(Digits);
		temp << L;
	}
	return temp.str();
}

//Mani added this here.
int static  Pos(string str, char ch)
{
	return str.find(ch);
};

//Mani added this here.
bool static IsDelimiter(string str, string delimiter, int pos)
{
	bool result = false;

	int l = delimiter.length();
	for (int i = 0; i < l; i++)
	{
		if (delimiter[i] == str[pos]) { result = true; break; }
	}

	return result;
};

//Mani added this here.
string static Trim(string str)
{
	string result = "";

	int l = str.length();
	int pos1 = 0, pos2 = 0;
	for (int i = 0; i < l; i++)
	{
		if (str[i] != ' ') { pos1 = i; break; }
	}
	for (int i = l - 1; i >= 0; i--)
	{
		if (str[i] != ' ') { pos2 = i; break; }
	}
	for (int i = pos1; i <= pos2; i++)
	{
		result = result + str[i];
	}
	return result;
};

//---------------------------------------------------------------------------

long static Strtolong(string s) {

	istringstream instr;
	instr.str(s);

	long I;
	instr >> I;
	return I;
};

double static StrToDate(string date) {
	int Month = Strtolong(date.substr(0, 2));
	int Day = Strtolong(date.substr(3, 2));
	int Year = Strtolong(date.substr(6, 4));

	return StandardConverterUtility::EncodeDateTime(Year, Month, Day, 0, 0);
};

double static StrToTime(string time) {

	int hour = Strtolong(time.substr(0, 2));
	int min = Strtolong(time.substr(3, 2));

	return StandardConverterUtility::EncodeDateTime(0, 0, 0, hour + 24, min);
};

string static FormatString(double DT, string) {
	ostringstream temp;
	temp.width(2);
	int Y = 0, M = 0, D = 0, H = 0, Min = 0;

	StandardConverterUtility::DecodeDateTime(DT, &Y, &M, &D, &H, &Min);
	temp << Y << " " << M << " " << D;

	return temp.str();
};


//void static LogDebug(const string S) {

//	string SS = S;
//	cout << SS << endl;
//}


//taken from NewModules.cpp file.
static float SWEfromDepth(float Snow_Depth) { // 3/5/98 Calculates SWE(mm) from Snow Depth(m)

	float SWE;

	if (Snow_Depth > 0.6)
		SWE = 4.5608 * Snow_Depth * 100.0 - 128.06;
	else if (Snow_Depth > 0.0205)
		SWE = 2.39 * Snow_Depth * 100.0 + 2.05;
	else
		SWE = Snow_Depth;

	return SWE;
} // SWEfromDepth


//taken from NewModules.cpp file.
static void infil_index(float Theta, float SWE, float& Index, float& Pot) {

	Pot = 5 * (1 - Theta) * pow(SWE, 0.584f);
	Index = Pot / SWE;
	if (Index > 1.0) Index = 1;
	Pot = Pot / 6;
}


static float soilproperties[][9] = {
  { 0.0,  999.9, 0.000, 0.00, 1.100,  1.000,	0.000,	0.0,  4},  //      0  water
  { 49.5, 117.8, 0.020, 0.10, 0.437,  0.395,	0.121,	4.05, 1},  //      1  sand
  { 61.3,  29.9, 0.036, 0.16, 0.437,  0.41 ,	0.09,	4.38, 4},  //      2  loamsand
  {110.1,  10.9, 0.041, 0.23, 0.453,  0.435,	0.218,	4.9,  2},  //      3  sandloam
  { 88.9,   3.4, 0.029, 0.26, 0.463,  0.451,	0.478,	5.39, 2},  //      4  loam
  {166.8,   6.5, 0.045, 0.38, 0.501,  0.485,	0.786,	5.3,  2},  //      5  siltloam
  {218.5,   1.5, 0.068, 0.38, 0.398,  0.420,	0.299,	7.12, 3},  //      6  saclloam
  {208.8,   1.0, 0.155, 0.39, 0.464,  0.476,	0.63,	8.52, 2},  //      7  clayloam
  {273.3,   1.0, 0.039, 0.40, 0.471,  0.477,	0.356,	7.75, 2},  //      8  siclloam
  {239.0,   0.6, 0.110, 0.41, 0.430,  0.426,	0.153,	10.4, 3},  //      9  sandclay
  {292.2,   0.5, 0.056, 0.43, 0.479,  0.492,	0.49,	10.4, 3},  //      10 siltclay
  {316.3,   0.3, 0.090, 0.46, 0.475,  0.482,	0.405,	11.4, 3},  //      11 clay
  {  0.0,   0.0, 0.000, 0.00, 0.000,  0.000,	0.0,	 0.0, 4}   //      12 pavement. Values not used
};

static float SetSoilproperties[][4] = {
	//  avail       wilt    field   pore
	  {1000.0,	  0.0, 1000.0,  1000.0},          //      0  water
	  {  84.0,	 40.0,	124.0,  395.0 },	  //      1  sand
	  {  80.0,	 60.0,	140.0,  410.0 },	  //      2  loamsand
	  { 130.0,	100.0,	230.0,  435.0 },	  //      3  sandloam
	  { 157.0,	110.0,	267.0,  451.0 },	  //      4  loam
	  { 162.0,	130.0,	292.0,  485.0 },	  //      5  siltloam
	  { 170.0,	140.0,	310.0,  420.0 },	  //      6  saclloam
	  { 167.0,	150.0,	317.0,  476.0 },	  //      7  clayloam
	  { 150.0,	190.0,	340.0,  477.0 },	  //      8  siclloam
	  { 150.0,	200.0,	350.0,  426.0 },	  //      9  sandclay
	  { 150.0,	210.0,	360.0,  492.0 },	  //      10 siltclay
	  { 145.0,	215.0,	360.0,  482.0 }, 	  //      11 clay
	  {   0.0,     1000.0, 1000.0,    0.0 }           //      12 pavement
};



#endif
