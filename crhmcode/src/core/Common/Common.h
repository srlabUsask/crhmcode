#pragma once
// 10/03/16
//---------------------------------------------------------------------------
#ifndef CommonH
#define CommonH
//---------------------------------------------------------------------------

//#include <vcl.h>
#include <string>
#include <cmath>

#if defined(_WIN32)
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include "string.h"
#include<iostream>
#include "TStringList/TStringList.h"

#include "time.h"
#include "CRHM_namespace.h"
#include "snowcover.h"
#include "CRHMException.h"
#include "VandP.h"
#include "CRHM_constants.h"
#include "PBSM_constants.h"
#include "CHAD_constants.h"

#define WM_CRHM_LOG_EXCEPTION  (WM_APP + 900)
#define WM_CRHM_LOG_EXCEPTION1 (WM_APP + 901)
#define WM_CRHM_LOG_DEBUG      (WM_APP + 902)

#define WM_CRHM_Main_DIM    (WM_APP + 903)
#define WM_CRHM_Main_STATUS (WM_APP + 904)
#define WM_CRHM_Main_DIRTY  (WM_APP + 905)

#define VARIATION_ORG 0        // module - i.e. #0 implied. Included in all modules
#define VARIATION_1 1        // module#1
#define VARIATION_2 2        // module#2
#define VARIATION_3 4        // module#3
#define VARIATION_4 8        // module#4
#define VARIATION_5 16       // module#5
#define VARIATION_6 32       // module#6
#define VARIATION_7 64       // module#7
#define VARIATION_8 128      // module#8
#define VARIATION_9 256      // module#9
#define VARIATION_10 512     // module#10
#define VARIATION_11 1024    // module#11
#define VARIATION_0  2048    // include in basic module
#define VARIATION_WQ 4096    // include for WQ

#define MAXHRU 101
#define MAXLAY 101
#define WtoMJ_D 86400/1E6
#define MJ_DtoW 1E6/86400

#ifndef M_PI
#define M_PI	3.14159265358979323846  /* pi */
#endif

using namespace std;

enum class TMemoSel { LOG, DEBUG };
enum class TExtra { BLANK, DD, TT, DT };
enum class TAKA { AKAERROR = -1, VARG, OBSR, VARD, OBSD, PARD, OBSF, AKAEND };
enum TMsgDlgBtn { mbYes, mbNo, mbOK, mbCancel, mbAbort, mbRetry, mbIgnore, mbAll, mbNoToAll, mbYesToAll, mbHelp };
enum class TBuild { BUILD, DECL, INIT, RUN };
enum class TIMEFORMAT { MS, YYYYMMDD, ISO};
enum class LMODULE { BASIC, MACRO, ADVANCE, SUPPORT, CUSTOM, PROTO, OBSOL };
enum class TFun { FOBS, VP_SAT, W_MJ, MJ_W, AVG, MIN, MAX, TOT, POS, FIRST, LAST, CNT, CNT0, DLTA, INTVL, DAY, DTOT };
enum class TVISIBLE { OUTPUT, USUAL, DIAGNOSTIC, PRIVATE }; // OUTPUT infers all variables/parameters
enum class TVar { none, Int, Float, Txt, Read, ReadI, ReadF };

// NREB only applies to variables. NDEFNZ only applies to parameters
enum class TDim { BASIN, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE, NHRU, NOBS, NLAY, NDEF, NFREQ, NREB, NDEFN, NDEFNZ };
enum class TFloatFormat { ffGeneral, ffExponent, ffFixed, ffNumber, ffCurrency };

static double xLimit = (numeric_limits<double>::max)();
static long lLimit = (numeric_limits<long>::max)();

const double a1 = 0.4361836;   //constants of approximation
const double a2 = -0.1201676;
const double a3 = 0.937298;
const double little_p = 0.33267;

//void GroupEnding(string &AA, int Cnt);
//static double xLimit = 3.14E20;
//static long lLimit = 2147483647;
//double sqr(double X);
double static sqr(double X) { return X * X; }
//bool static EqualUpper(std::string s1, std::string s2);

string static GetCurrentDir(void) {
	char buff[FILENAME_MAX];
	char* cwd;
	cwd = GetCurrentDir(buff, FILENAME_MAX);
	if (cwd == NULL) {
		CRHMException Except("Failed to return the current working directory", TExcept::TERMINATE);
		throw (Except);
	}
	else {
		std::string current_working_dir(buff);
		return current_working_dir;
	}
}

class Common
{
public:
	double static estar(double t);
	static double Qs(double P, double tc);
	double static Qswater(double P, double tc);
	double static DepthofSnow(double SWE);

	double static SWE_prob(double SWEmean, double SWE, double CV);
	double static SVDens(double Temp);
	void static GroupEnding(string &AA, int Cnt);
	double static Ice_Bulb(double Tc, double RH, double Pa);
	void static  Message(const char *s1, const char *s2);
	void static Message(const string s1, const string s2);
	string static lowercase(string &s);
	int static IndexOf(TStringList *Box, const string S);
	string static longtoStr(long L);

	/*
	* Trim all whitespace from the start of a string to
	*  the first non-whitepsace character in place
	*/
	static void ltrim(std::string& s);

	/*
	* Trim all whitespace from the end of a string to
	*  the last non-whitepsace character in place
	*/
	static void rtrim(std::string& s);

	/**
	* Trim all whitespace from the start of a string to
	*  the first non-whitepsace character
	*
	* @param str - a string to trim.
	* @return the string with its beginning trimmed of white space characters.
	**/
	string static trimleft(string& str);

	/**
	* Trim all whitespace from the end of a string to
	*  the last non-whitepsace character
	*
	* @param str - a string to trim.
	* @return The string with its end trimmed of white space characters.
	**/
	string static trimright(string& str);

	/**
	* Trim all the whitespace from the begining and end of of a string.
	*
	* @param str - a string to trim.
	* @return The string with its beginning and ending whitespace removed.
	**/
	string static trim(string& str);

	double static StrtoDt(string s);
	bool static EqualUpper(string s1, string s2);
	double static KyValue(double probability, double guess);
	double static K(double Ky, double LogStDev);
	string static GetCurrentPath(void);
	bool static Variation_Decide(int Variation_set, long Variation);
	void static writefile(string filepath, string content);
	
	
	/*
	* Takes a string of comma seperated values and places each value as a entry in a 
	* vector of strings. Values are surounded by single quote characters before being 
	* placed into the vector. 
	* 
	* ex. input of "Red,Green,Blue" yeilds a vector with "'Red'", "'Green'", and "'Blue'"
	* as its values.
	* 
	* @param std::string css - the incomming string of comma spererated values.
	* @param std::vector<std::string> * pointer to the vector in which to save the parsed values.
	*/
	void static parseCommaSeperatedString(std::string css, std::vector<std::string>* stringVector);
};

#endif
