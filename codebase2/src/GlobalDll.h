
#pragma once
// 12/19/16

//---------------------------------------------------------------------------

#ifndef GlobalDllH
#define GlobalDllH
//---------------------------------------------------------------------------

#include "GlobalCommon.h"
#include <ctime>
//#include <atltime.h>
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


	//manishankar. this is used for resolving the address related issue.
	static float ** t_layvalues; 
	static float ** rh_layvalues;
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

#endif
