

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




static double xLimit = (numeric_limits<double>::max)();
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

const double a1 = (double)0.4361836;   //constants of approximation
const double a2 = (double)-0.1201676;
const double a3 = (double)0.937298;
const double little_p = (double)0.33267;


enum TFloatFormat { ffGeneral, ffExponent, ffFixed, ffNumber, ffCurrency };

//void GroupEnding(string &AA, int Cnt);

class snowcover {
public:
	double *data;
	long  N;
	snowcover(double SWEmean, double cv);
	double lookup(double melt) { return 0; };
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

//double sqr(double X);
double static sqr(double X) { return X * X; }


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

	const double Cs = 1.28E+06; // (J/m3/K) volumetric heat capacity of soil
	const double Cp = 1005;     // (J/kg/K) volumetric heat capacity of dry air
	const double Rgas = 287.0;  // Gas constant for dry air (J/kg/K)
	const double Tm = (double)273.15;   // Melting point (K)

	const double Ls = 2.845e6;  // Latent heat of sublimation (J/kg)
	const double Lv = 2.50e6;  // Latent heat of vaporization (J/kg)
	const double Lf = 0.334e6;  // Latent heat of fusion (J/kg)
	const double kappa = (double)0.4;

	const double sbc = (double)5.67E-8; // Stephan-Boltzmann constant W/m^2/k4
	const double SB = (double)4.899e-09; // Stephan-Boltzmann constant MJ/m^2-d

	const double emiss = (double)0.985; // emissivity of the atmosphere and snowpack
	const double emiss_c = (double)0.96; // emissivity of the canopy
	const double em = (double)0.622;     //
}

//     define constants for equations

namespace PBSM_constants {

	const double rho = (double)1.23;     // (kg/m3) density of dry air
	const double Qstar = 120;    //{Solar Radiation Input}
	const double M = (double)18.01;      //{molecular weight of water (kg/kmole)}
	const double R = 8313;       //{universal gas constant (J/(kmole K))}
	const double LATH = 2.838E6; //{latent heat of sublimation (J/kg) List 1949}
	const double DICE = 900;     //{density of ice, assumed equal to blowing snow part (kg/m3)}
	const double ZD = (double)0.3;       //{height of boundary-layer at xd (m) Takeuchi (1980)}
	const double XD = 300;       //{Fetch to develop b-l to ZD (m)}
	const double g = (double)9.80;       //{m/s2}
	const double Beta = 170;     // Beta ratio of element to surface drag for vegetation Cr/Cs
	const double C1 = (double)2.8;       //{2.3}
	const double C2 = (double)1.6;
	const double C3 = (double)4.2;       //{3.25} {e = 1/(C3*Ustar)}
	const double KARMAN = (double)0.4;
	const double KARMAN2 = (double)0.16;
}

namespace CHAD_constants {
	// Constants:
	const double emm = (double)0.985; 		// emissivity [ ]
	const double sbc = (double)5.67e-8; 		//Stephan-Boltzmann constant [W m-2 K-4]
	const double solarconst = 1367; 	// solar constant [W m-2]
	const double ca = 1013;  		//specific heat of air [J kg-1 K-1]
	const double cf = 2470;  		//specific heat of forest biomass [J kg-1 K-1]
	const double pa = (double)1.22;  		//typical air density [kg m-3]
	const double pf = 686;   		//typical forest biomass density [kg m-3]
	const double kf = (double)0.17;		//typical thermal conductivity of wood biomass [J m-1 K-1]
	const double dv = (double)1.983e-5;  		//dynamic viscosity of air (typical value for 300K) [kg m-1 s-1]
	const double kv = (double)1.88e-5;  		//kinematic viscosity of air (typical value for Sask.) [m2 s-1]
	const double dh = (double)2.216e-5; 		//thermal diffusivity of air (1 atm; 300 K) [m2 s-1]
	const double tca = (double)0.024;              //typical thermal conductivity of air (at 25ï¿½C) [J m-1 K-1]
	const double DTOR = (double)3.1416 / (double)180.0;
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
	string static trimleft(string& str);
	string static trimright(string& str);
	string static trim(string& str);
	double static StrtoDt(string s);
	bool static EqualUpper(string s1, string s2);
	double static KyValue(double probability, double guess);
	double static K(double Ky, double LogStDev);
	string static GetCurrentPath(void);
	bool static Variation_Decide(int Variation_set, long Variation);
	void static writefile(string filepath, string content);
};



















#endif
