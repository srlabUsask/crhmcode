

#pragma once
// 10/03/16
//---------------------------------------------------------------------------

#ifndef CommonH
#define CommonH
//---------------------------------------------------------------------------

//#include <vcl.h>
#include <string>
#include <math.h>
#include <direct.h>
#define GetCurrentDir _getcwd
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




//double xLimit = numeric_limits<float>::max();
//long lLimit = numeric_limits<long>::max();

static double xLimit = 3.14E20;
static long lLimit = 2147483647;




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

#define MAXHRU 101;
#define MAXLAY 101;
#define WtoMJ_D 86400/1E6
#define MJ_DtoW 1E6/86400


const float M_PI = 3.14;
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

	snowcover(float SWEmean, float cv) {  //Manishankar: this is only being used in NewModules.cpp
		float x, sca;

		const long N = 150;
		data = new float[N];

		for (int ii = 0; ii < N; ii++) {
			x = SWEmean * 2.0*(ii + 1) / N;
			float K = (x - SWEmean) / (SWEmean*cv);

			float Sy = sqrt(log(cv*cv + 1.0));

			float Ky = (log(K*sqrt(exp(Sy*Sy) - 1.0) + 1.0) + Sy * Sy / 2.0) / Sy;

			float t = 1 / (1 + little_p * Ky);

			float P = (exp(-Ky * Ky / 2) / sqrt(2 * M_PI)) * (a1*t + a2 * pow(t, 2) + a3 * pow(t, 3));

			data[ii] = P;
		}
	
	};

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
	const float tca = 0.024;              //typical thermal conductivity of air (at 25�C) [J m-1 K-1]
	const float DTOR = 3.1416 / 180.0;
}


//===========================================================================================================================================


long static Decade_Offsets[][4] = { // Year, abs(value), calc wrt to this year, offset.
	{ 80, -3652,  29219,     2 }, // 1900 moved to 1980
{ 60,  3654,  21915,  3654 }, // 1910 moved to 1970
{ 60,  3654,  21915,  7306 }, // 1920 moved to 1980
{ 40,  10959, 14610, 10959 }, // 1930 moved to 1970
{ 40,  10959, 14610, 14611 }, // 1940 moved to 1980
{ 20,  18264,  7305, 18264 }, // 1950 moved to 1970
{ 20,  18264,  7305, 21916 }, // 1960 moved to 1980
{ 0,  25569,     0, 25569 }, // 1970 not moved
{ 0,  29221,     0 }, // 1980 (not used)
};

string static GetCurrentDir(void) {
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}


class Common
{
public:
	// Saturation vapour pressure (kPa)
	// Saturation humidity (kg/kg) Over ice and water
	double static estar(float t) /* Saturation vapour pressure kPa*/
	{
		if (t > 0.0)
			return 0.611 * exp(17.27*t / (t + 237.3));
		else
			return 0.611 * exp(21.88*t / (t + 265.5));
	}
	static float Qs(float P, float tc) { // P (KPa)  //Manishankar: this function is only being used in NewModules.cpp.

		float es; // Vapour pressure (Pa)

		if (tc >= 0)
			es = 0.611213*exp(17.5043*tc / (241.3 + tc));
		else
			es = 0.611213*exp(22.4422*tc / (272.186 + tc));

		return(0.622*es / P);
	}

	
	// Saturation humidity (kg/kg) Over water
	float static Qswater(float P, float tc) { // P (KPa)

		float es; // Vapour pressure (KPa)

		es = 0.611213*exp(17.5043*tc / (241.3 + tc));

		return(0.622*es / P);
	}

	float static DepthofSnow(float SWE)
	{
		/* 3/5/98
		Calculates Snow Depth(m) from SWE(mm) */
		float Snow_Depth;

		if (SWE > 2.05) {
			if (SWE <= 145.45) /* SWE 145.45 mm equivalent to 60 cm*/
				Snow_Depth = (SWE - 2.05) / 2.39;
			else
				Snow_Depth = (SWE + 128.06) / 4.5608;
		}
		else
			Snow_Depth = 0;

		return Snow_Depth / 100.0;
	} /* DepthofSnow*/



	float static SWE_prob(float SWEmean, float SWE, float CV) { //Manishankar: This function is only being used in NewModules.cpp

		if (SWE <= 0.01) return 0.0; // handle log(0) error
		if (SWE >= SWEmean) return 1.0; // 

		float K = -SWE / (SWEmean*CV);

		float Sy = sqrt(log(1.0 + CV * CV));

		float Ky = log(1.0 + K * CV) / Sy + Sy / 2.0;

		float t = 1 / (1 + little_p * Ky);

		float P = (exp(-Ky * Ky / 2) / sqrt(2 * M_PI)) * (a1*t + a2 * t*t + a3 * t*t*t);

		if (P > 1.0 || P < 0.001) // handle discontinuity
			P = 1.0;

		return P;
	}

	float static SVDens(float Temp)

	{
		return 1.324*exp(22.452*Temp / (Temp + 273.15)) / (Temp + 273.15);
	}
	// outputs sat. vapor density, kg/m^3


	void static GroupEnding(string &AA, int Cnt) {

		int alphas = Cnt / 26;
		int letter = Cnt % 26;
		if (!letter) { // 26th letter is 'Z' not "@@"
			letter = 26;
			alphas = 0;
		}
		AA = "@@";
		AA[1] += letter;
		if (alphas > 0) {
			string B = "@";
			B[0] += alphas;
			AA.insert(1, B);
		}
	}

	float static Ice_Bulb(float Tc, float RH, float Pa) {

		float Tk = Tc + CRHM_constants::Tm;

		float D = 0.0000206*pow(Tk / CRHM_constants::Tm, 1.75);

		float RHO = Pa * 1000.0 / (CRHM_constants::Rgas*Tk);

		float qt = CRHM_constants::em / (Pa*1000.0)*611.213*exp(22.4422*Tc / (CRHM_constants::Tm + Tc));

		float lamda = 0.000076843*Tk + 0.003130762;

		float L;
		if (Tc > 0.0)
			L = CRHM_constants::Lv;
		else
			L = CRHM_constants::Ls;

		float delta = CRHM_constants::em*L*qt / (CRHM_constants::Rgas*sqr(Tk));

		return Tc - L * (1.0 - RH / 100.0)*qt / (CRHM_constants::Cp + L * delta) *(RHO*CRHM_constants::Cp*D / lamda);
	} // returns ice bulb temperature, Pa (kPa), RH(%).


	void static  Message(const char *s1, const char *s2) {

		cout << s1 << ", " << s2 << endl;
	}

	void static Message(const string s1, const string s2) {

		cout << s1 << ", " << s2 << endl;
	}

	string static lowercase(string &s) {  //Manishankar: in CRHMmain.cpp, utils.cpp, CRHMmainDlg.cpp

		transform(s.begin(), s.end(), s.begin(), (int(*)(int)) tolower);
		return s;
	}

	double static Calculate_TdateTime_Offset(void) {  //Manishankar: It is only being used here.

		tm timeinfo;

		timeinfo.tm_sec = 0;
		timeinfo.tm_min = 0;
		timeinfo.tm_hour = 0;
		timeinfo.tm_mday = 1;
		timeinfo.tm_mon = 0;
		timeinfo.tm_year = 70;

		time_t Current = mktime(&timeinfo); // determine ???

		return double(Current) / 86400.0;
	}

	double static EncodeDateTime(int Year, int Month, int Day, int hour, int min) {  //Manishankar: in ClassCRHM.cpp, GlobalDll.h, CRHMmain.cpp

		tm timeinfo;

		long indx = (Year - 1900) / 10;
		if (indx > 7)indx = 7;

		timeinfo.tm_sec = 0;
		timeinfo.tm_min = min;
		timeinfo.tm_hour = hour;
		timeinfo.tm_mday = Day;
		timeinfo.tm_mon = Month - 1;

		timeinfo.tm_isdst = 0;

		timeinfo.tm_year = Year + Decade_Offsets[indx][0] - 1900;

		time_t Current = mktime(&timeinfo);

		return double(Current) / 86400.0 + Decade_Offsets[indx][1] - Calculate_TdateTime_Offset(); //Global::TdateTime_Offset; // correction from
	}

	void static DecodeDateTime(double Dttime, int *Year, int *Month, int *Day, int *Hour, int *Min) { //Manishankar: in ClassCRHM.cpp, GlobalDll.h, Hype_routines.cpp, MacroUnit.cpp

		long indx = 7;
		if (Dttime < 25569)
			for (indx = 6; indx >= 0; --indx) {
				if (!(Dttime < Decade_Offsets[indx][3]))
					break;
			}

		long Fix = roundl((Dttime - Decade_Offsets[indx][1])*86400.0);
		time_t rawtime = (time_t)Fix;

		tm *timeinfo = gmtime(&rawtime);

		*Year = timeinfo->tm_year - Decade_Offsets[indx][0] + 1900;
		*Month = timeinfo->tm_mon + 1;
		*Day = timeinfo->tm_mday;
		*Hour = timeinfo->tm_hour;
		*Min = timeinfo->tm_min;
	}

	double static DateTimeDt(void) {  //Manishankar: in CRHMmain.cpp and NewModules.cpp.
		time_t Currently;

		time(&Currently);

		return double(Currently) / 86400.0 + Decade_Offsets[7][1] - Calculate_TdateTime_Offset(); //Global::TdateTime_Offset; //  TdateTime_Offset less local time offset
	}


	int static IndexOf(TStringList *Box, const string S) { //Manishankar: being used in different places in different ways.
		for (int ii = 0; ii < Box->Count; ++ii) {
			if (Box->Strings[ii] == S)
				return ii;
		}
		return -1;
	}

	string static longtoStr(long L) { //Manishankar: in two or more files.
		ostringstream temp;
		temp << L;
		return temp.str();
	}


	string static trimleft(string& str) {

		string::size_type pos = str.find_first_not_of(" \t");

		if (pos != string::npos)
			if (pos > 0)
				str.erase(0, pos);

		return str;
	}

	string static trimright(string& str) //
	{
		if (!str.empty()) {

			string::size_type pos = str.find_last_not_of(" \t");

			if (pos != string::npos)
				if (pos < str.length() - 1)
					str.erase(++pos);
		}

		return str;
	}


	string static trim(string& str) { //Manishankar: in two or more files.

		trimleft(str);
		trimright(str);

		return str;
	}

	double static StrtoDt(string s) {  //Manishankar: this is being used in ClassCRHM.cpp only.

		istringstream instr;
		instr.str(s);

		double D;
		instr >> D;
		return D;
	}

	bool static EqualUpper(string s1, string s2) {
		transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
		transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
		return (bool)(s1 == s2);
	}

	float static KyValue(float probability, float guess) {
		// finds location of probability, using polynomial approx to normal dist
		//   from "Handbook of Mathematical Functions" by Abramowitz and Stegun}

		float Ky, TempP, t;
		bool  done = false;
		float direction = -1;       // increasing
		float tolerance = 0.0001;
		float dKy = 0.1;      // increment
		long  iterations = 0;

		Ky = guess;        // start value

		while (!done) {
			iterations++;
			t = 1 / (1 + little_p * Ky);
			TempP = (exp(-Ky * Ky / 2) / sqrt(2 * M_PI)) * (a1*t + a2 * t*t + a3 * t*t*t);

			if (fabs(TempP - probability) <= tolerance)
				done = true;
			else {
				if (TempP > (probability + tolerance))
					if (direction == -1) {
						dKy = dKy / 2;
						direction = 1;
					}
					else {
						dKy = dKy / 2;
						direction = -1;
					}

					Ky = Ky + dKy * direction;
			}
		} // while

		return Ky;
	}

	float static K(float Ky, float LogStDev) {

		return (exp(LogStDev*Ky - (sqr(LogStDev) / 2)) - 1) / (sqrt(exp(sqr(LogStDev)) - 1));
	}


	string static GetCurrentPath(void) {

		const char *buffer;

		//getcwd(buffer, _MAX_PATH);
		/*
		if ((buffer = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd error(get current directory error");
		else
		{
		puts(buffer);
		free(buffer);
		}
		*/

		buffer = _getcwd(NULL, 0);
		printf("Current path is %s", buffer);
		return buffer;
	}

	bool static Variation_Decide(int Variation_set, long Variation) {

		VandP V; V.Set(Variation);

		long variations = V.GetV(); // & 2047;

		if ((variations & 2048) != 0 && Variation_set == 0 || // handles VARIATION_0
			(variations & 4096) != 0 ||                        // handles VARIATION_0
			(variations == 0) ||                               // handles VARIATION_ORG
			(variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
			return true;
		else
			return false;
	}

	void static writefile(string content)
	{
		ofstream myfile; 
		myfile.open("d:/testfile2.txt", ios::app); 
		myfile << "\n" << content; 
		myfile.close();
	}

	void static addTime(string mname, float t, string filepath)
	{
		ofstream myfile;
		myfile.open(filepath, ios::app);
		myfile << "\n" << mname << " " << t;
		myfile.close();
	}

};

class TimingStatistics
{
	string modulenames[100];
	float times[100];
	int frequencies[100];
	int modulecount=0;

public: 
	void addTime(string mname, float t, string filepath)
	{
		ofstream myfile;
		myfile.open(filepath, ios::app);
		myfile << "\n" << mname << " " << t;
		myfile.close();
	}
	void addTime(string mname, float t)
	{
		int indx = -1;
		for (int i = 0; i < modulecount; i++)
		{
			if (modulenames[i] == mname) { indx = i; break; }
		}
		if (indx == -1)
		{
			modulenames[modulecount] = mname;
			times[modulecount] = t;
			frequencies[modulecount] = 1;
			modulecount++;
		}
		else
		{
			times[indx] += t;
			frequencies[indx]++;
		}
	}

	void writeStatistics()
	{
		string mdata = "";
		for (int i = 0; i < modulecount; i++)
		{
			mdata = modulenames[i] + "\t" + to_string(frequencies[i]) + "\t" + to_string(times[i]);
			Common::writefile(mdata+"\n");
		}
	}
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