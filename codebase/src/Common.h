

#pragma once
// 10/03/16
//---------------------------------------------------------------------------

#ifndef CommonH
#define CommonH
//---------------------------------------------------------------------------

//#include <vcl.h>
#include <string>
#include <math.h>

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
#include "TStringList.h"

#include "time.h"


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

using namespace std;

enum TMemoSel { LOG, DEBUG };
enum TExcept { NONE, ERR, DECLERR, WARNING, USER, TERMINATE };
enum TExtra { BLANK, DD, TT, DT };
enum TAKA { AKAERROR = -1, VARG, OBSR, VARD, OBSD, PARD, OBSF, AKAEND };
enum TMsgDlgBtn { mbYes, mbNo, mbOK, mbCancel, mbAbort, mbRetry, mbIgnore, mbAll, mbNoToAll, mbYesToAll, mbHelp };




static double xLimit = (numeric_limits<float>::max)();
static long lLimit = (numeric_limits<long>::max)();

//static double xLimit = 3.14E20;
//static long lLimit = 2147483647;




namespace CRHM {
	enum TVISIBLE { OUTPUT, USUAL, DIAGNOSTIC, PRIVATE }; // OUTPUT infers all variables/parameters

	enum TVar { none, Int, Float, Txt, Read, ReadI, ReadF };

	enum TFitType { POLY, FOURIER, POWER, EXPO, LOGARITHM, MLR };
	enum TAgainst { myTIME, VARIABLE };
	enum TDsply { FRACT, OBS, BOTH, MDY, XY };

	// NREB only applies to variables. NDEFNZ only applies to parameters
	enum TDim { BASIN, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE, NHRU, NOBS, NLAY, NDEF, NFREQ, NREB, NDEFN, NDEFNZ };
	enum TBuild { BUILD, DECL, INIT, RUN };

	enum TTiming { IDLE, EARLY, MELT, MELT2, MATURE, HOLD };
	enum TFun { FOBS, VP_SAT, W_MJ, MJ_W, AVG, MIN, MAX, TOT, POS, FIRST, LAST, CNT, CNT0, DLTA, INTVL, DAY, DTOT };

	enum TValue { PSI, KSAT, WILT, FCAP, PORG, PORE, AIRENT, PORESZ, AVAIL };

	enum TFrozen { PREMELT, RESTRICTED, LIMITED, UNLIMITED, SATURATED };

	enum TSANDCLAY { LOAM1, LOAM2, LOAM3, SAND, CLAY };

	enum { NOTUSED, DRIFT, HUMMOCK };

	enum TCONDITION { FROZEN, ICEWATER, WATER, DRAINING };

	enum LMODULE { BASIC, MACRO, ADVANCE, SUPPORT, CUSTOM, PROTO, OBSOL };

	enum CONTROLSTATES { SAVE, LOAD };

	enum HRUOBSTYPES { HRU_OBS_t_rh_ea = 1, HRU_OBS_p_ppt, HRU_OBS_u, HRU_OBS_Q, HRU_OBS_misc };

	enum TIMEFORMAT { MS, MMDDYYYY, YYYYMMDD };
}

#define MAXHRU 101
#define MAXLAY 101
#define WtoMJ_D 86400/1E6
#define MJ_DtoW 1E6/86400

#ifndef M_PI
#define M_PI	3.14159265358979323846  /* pi */
#endif

const float a1 = 0.4361836;   //constants of approximation
const float a2 = -0.1201676;
const float a3 = 0.937298;
const float little_p = 0.33267;


enum TFloatFormat { ffGeneral, ffExponent, ffFixed, ffNumber, ffCurrency };

//void GroupEnding(string &AA, int Cnt);

class snowcover {
public:
	float *data;
	long  N;
	snowcover(float SWEmean, float cv);
	float lookup(float melt) { return 0; };
	~snowcover() { delete[] data; };
};

class CRHMException {
public:
	std::string Message;
	TExcept Kind;
	CRHMException() : Message(""), Kind(NONE) {};
	CRHMException(std::string Message, TExcept Kind) :
		Message(Message), Kind(Kind) {};
};

//float sqr(float X);
float static sqr(float X) { return X * X; }


//bool static EqualUpper(std::string s1, std::string s2);

union VandP {

public:
	VandP(long Long) : both(Long) {}; // constructor
	VandP(void) : both(0) {}; // constructor

	unsigned long both;
	unsigned short int Module[2];
	unsigned short int GetV(void) { return Module[0]; };
	void PutV(unsigned short int V) { Module[0] = V; };
	unsigned short int GetP(void) { return Module[1]; };
	void PutP(unsigned short int P) { Module[1] = P; };
	void Set(long Long) { both = Long; };
};

namespace CRHM_constants {

	const float Cs = 1.28E+06; // (J/m3/K) volumetric heat capacity of soil
	const float Cp = 1005;     // (J/kg/K) volumetric heat capacity of dry air
	const float Rgas = 287.0;  // Gas constant for dry air (J/kg/K)
	const float Tm = 273.15;   // Melting point (K)

	const float Ls = 2.845e6;  // Latent heat of sublimation (J/kg)
	const float Lv = 2.50e6;  // Latent heat of vaporization (J/kg)
	const float Lf = 0.334e6;  // Latent heat of fusion (J/kg)
	const float kappa = 0.4;

	const float sbc = 5.67E-8; // Stephan-Boltzmann constant W/m^2/k4
	const float SB = 4.899e-09; // Stephan-Boltzmann constant MJ/m^2-d

	const float emiss = 0.985; // emissivity of the atmosphere and snowpack
	const float emiss_c = 0.96; // emissivity of the canopy
	const float em = 0.622;     //
}

//     define constants for equations

namespace PBSM_constants {

	const float rho = 1.23;     // (kg/m3) density of dry air
	const float Qstar = 120;    //{Solar Radiation Input}
	const float M = 18.01;      //{molecular weight of water (kg/kmole)}
	const float R = 8313;       //{universal gas constant (J/(kmole K))}
	const float LATH = 2.838E6; //{latent heat of sublimation (J/kg) List 1949}
	const float DICE = 900;     //{density of ice, assumed equal to blowing snow part (kg/m3)}
	const float ZD = 0.3;       //{height of boundary-layer at xd (m) Takeuchi (1980)}
	const float XD = 300;       //{Fetch to develop b-l to ZD (m)}
	const float g = 9.80;       //{m/s2}
	const float Beta = 170;     // Beta ratio of element to surface drag for vegetation Cr/Cs
	const float C1 = 2.8;       //{2.3}
	const float C2 = 1.6;
	const float C3 = 4.2;       //{3.25} {e = 1/(C3*Ustar)}
	const float KARMAN = 0.4;
	const float KARMAN2 = 0.16;
}

namespace CHAD_constants {
	// Constants:
	const float emm = 0.985; 		// emissivity [ ]
	const float sbc = 5.67e-8; 		//Stephan-Boltzmann constant [W m-2 K-4]
	const float solarconst = 1367; 	// solar constant [W m-2]
	const float ca = 1013;  		//specific heat of air [J kg-1 K-1]
	const float cf = 2470;  		//specific heat of forest biomass [J kg-1 K-1]
	const float pa = 1.22;  		//typical air density [kg m-3]
	const float pf = 686;   		//typical forest biomass density [kg m-3]
	const float kf = 0.17;		//typical thermal conductivity of wood biomass [J m-1 K-1]
	const float dv = 1.983e-5;  		//dynamic viscosity of air (typical value for 300K) [kg m-1 s-1]
	const float kv = 1.88e-5;  		//kinematic viscosity of air (typical value for Sask.) [m2 s-1]
	const float dh = 2.216e-5; 		//thermal diffusivity of air (1 atm; 300 K) [m2 s-1]
	const float tca = 0.024;              //typical thermal conductivity of air (at 25ï¿½C) [J m-1 K-1]
	const float DTOR = 3.1416 / 180.0;
}


//===========================================================================================================================================

string static GetCurrentDir(void) {
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}



class Common
{
public:
	double static estar(float t);
	static float Qs(float P, float tc);
	float static Qswater(float P, float tc);
	float static DepthofSnow(float SWE);

	float static SWE_prob(float SWEmean, float SWE, float CV);
	float static SVDens(float Temp);
	void static GroupEnding(string &AA, int Cnt);
	float static Ice_Bulb(float Tc, float RH, float Pa);
	void static  Message(const char *s1, const char *s2);
	void static Message(const string s1, const string s2);
	string static lowercase(string &s);
	int static IndexOf(TStringList *Box, const string S);
	string static longtoStr(long L);
	string static trimleft(string& str);
	string static trimright(string& str);
	string static trim(string& str);
	double static StrtoDt(string s);
	bool static EqualUpper(string s1, string s2);
	float static KyValue(float probability, float guess);
	float static K(float Ky, float LogStDev);
	string static GetCurrentPath(void);
	bool static Variation_Decide(int Variation_set, long Variation);
	void static writefile(string content);
};

class MMSData
{
public:
	float ** mmsData;
	long ** mmsDataL;
	bool GoodRun;
	string S;
};



















#endif
