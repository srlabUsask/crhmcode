
#pragma once
// 12/19/16

//---------------------------------------------------------------------------

#ifndef GlobalDllH
#define GlobalDllH
//---------------------------------------------------------------------------

#include "GlobalCommon.h"
#include <ctime>
#include "Common/Common.h"
#include "StandardConverterUtility.h"
#include "TStringList/TStringList.h"
#include "ClassModule/ClassModule.h"

#include <map>
#include <set>
//#include "ClassCRHM.h"

using namespace std;

//newly added
typedef double TDateTime;

class ClassModule;

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
	static std::string CurrentModuleRun;
	static long CRHMControlSaveCnt;

	static BitSet RunUpBitSet; // determines modules executed during looping.
	static std::set<std::string> * ModuleBitSet; // determines modules executed during calculating ahead.

	static double Interval;
	static double DTstart;
	static double DTend;

	static TDateTime DTnow;

	static TDateTime RapidAdvanceTo;
	static TDateTime LoopTo;
	static long LoopCnt;
	static long LoopCntDown;

	static TBuild BuildFlag;
	static TIMEFORMAT TimeFormat;

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

	static std::map<std::string, ClassModule* > * AllModulesList;       // modules defined in CRHM
	static std::list<std::pair<std::string, ClassModule*>> * OurModulesList;       // modules defined in current model
	static std::list<std::pair<std::string, unsigned short>> * OurModulesVariation;
	static std::vector<std::string> * MacroModulesList;     // custom modules defined in current model
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

	static double * lapse_rate; // used for array observations adjustments
	static double * ppt_adj; // used for array observations adjustments
	static double * hru_elev; // used for array observations adjustments
	static double * obs_elev;
	static double ** OBS_ELEV; // used for array observations adjustments

	static double * Warming_t; // used for climate warming
	static double * Warming_p; // used for climate warming
	static long  * RH_VP_flag; // used for elevation change. -> 0 maintain rh, 1 -> maintain ea
	static long  * RH_VP_flag2; // used for climate warming. -> 0 maintain rh, 1 -> maintain ea
	static long   RH_EA_flag; // used for climate warming
	static long    RH_EA_obs; // 0 -> rh obs, 1 -> ea obs
	static long    OBS_AS_IS; // 0 -> process obs, 1 -> no processing
	static long    WQ_prj; // true -> processing WQ modules

	static long  ** HRU_OBS; // used for array observations
	static long  ** HRU_OBS_DIRECT; // used for array observations
	static double ** obs_t; // used for array observations adjustments
	static double ** obs_ea; // used for array observations adjustments
	static double ** obs_rh; // used for array observations adjustments
	static double ** obs_t_obs; // used for array observations adjustments

	static TObject *thisVar;
};


//Mani added this from TStringList.

string static FloatToStrF(double value, string format, int precision, int digits) {
	stringstream stream;

	//double minVal = 3000.14159265359;

	if (strcmp(format.c_str(), "ffFixed"))
	{
		stream << std::fixed << std::setprecision(precision) << value;
	}
	else
	{
		stream << std::setprecision(precision) << value;
	}

	
	return stream.str();
};

/** removed function overload due to Float to Double conversion jhs507
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
**/
string static FloatToStrF(double X, TFloatFormat Format, int Prec, int Digits) {
	ostringstream temp;
	if (Format == TFloatFormat::ffFixed) {
		temp.precision(Prec);
		temp << X;
	}
	else { // assume ffGeneral
		temp.precision(Prec);
		temp << X;
	}
	return temp.str();
}

string static FloatToStrF(long L, TFloatFormat Format, int Prec, int Digits) {
	ostringstream temp;
	if (Format == TFloatFormat::ffFixed) {
		temp.precision(Prec);
		temp << L;
	}
	else { // assume ffGeneral
		temp.precision(Prec);
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
static double SWEfromDepth(double Snow_Depth) { // 3/5/98 Calculates SWE(mm) from Snow Depth(m)

	double SWE;

	if (Snow_Depth > 0.6)
		SWE = 4.5608 * Snow_Depth * 100.0 - 128.06;
	else if (Snow_Depth > 0.0205)
		SWE = 2.39 * Snow_Depth * 100.0 + 2.05;
	else
		SWE = Snow_Depth;

	return SWE;
} // SWEfromDepth


//taken from NewModules.cpp file.
static void infil_index(double Theta, double SWE, double& Index, double& Pot, const double infDays) {

	Pot = 5 * (1 - Theta) * pow(SWE, 0.584f);
	Index = Pot / SWE;
	if (Index > 1.0) Index = 1;
	Pot = Pot / infDays;
}


static double soilproperties[][9] = {
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

static double SetSoilproperties[][4] = {
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

//taken from NewModules.cpp file.
static void ProbabilityThresholdNew(double SWE, double t, double Uten_Prob, double & Probability, double & Threshold,
                             long Snow, double & SnowAge, long & DrySnow){

//Probability of blowing snow occurrence and threshold wind speeds determined by ambient air temperature and snow age

   double Wind, Mean, Variance, c;

        Wind = 0.0;
        Probability = 0.0;

   if(SWE <= 0.0) {   //no snow available
        DrySnow = false;
        SnowAge = 0.0;
        Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); // (m/s)
   }

   else if( (Snow != 0) && ( t < 0.0) )
   {
// with concurrent snowfall: new dry snow
        DrySnow = true;
        SnowAge = 24.0/Global::Freq;

        Mean = 0.365 * t + 0.00706 * sqr(t)
              + 0.91 * log((double)SnowAge) + 11.0;
        Variance = 0.145 * t + 0.00196 * sqr(t) + 4.23;

        while ((Wind <= Uten_Prob) && (Uten_Prob >= 3.0)) {
// Wind < 3 m/s too weak for dry snow transport

           Wind = Wind + 0.1;

           c = (-sqr(Wind - Mean))/(2.0*sqr(Variance));

           Probability = Probability + (1.0/(Variance * 2.5055)) * (exp(c)) * 0.1;
        } // {while do}
        Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); // (m/s)
   } // {if}

   else if((t < 0.0) && DrySnow)
   {
// {without concurrent snowfall: old dry snow}
        SnowAge = SnowAge + 24.0/Global::Freq;

        Mean = 0.365 * t + 0.00706 * sqr(t)
              + 0.91 * log((double)SnowAge) + 11.0;
        Variance = 0.145 * t + 0.00196 * sqr(t) + 4.23;

        while ((Wind <= Uten_Prob) && (Uten_Prob >= 3.0)) {
// Wind < 3 m/s too weak for dry snow transport
           Wind = Wind + 0.1;

           c = (-sqr(Wind - Mean))/(2.0*sqr(Variance));

           Probability = Probability + (1.0/(Variance * 2.5055)) * (exp(c)) * 0.1;
         } // while do

       Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); //(m/s)
   } // if
   else if ((t >= 0.0)  || !DrySnow)
   {
        DrySnow = false;             // or wet snow remains on the ground
        SnowAge = 0.0;
        Mean = 21.0;
        Variance = 7.0;

        while ((Wind <= Uten_Prob) && (Uten_Prob >7.0)) {    // loop to calculate P.
// wind < 7 m/s too weak for wet snow transport
            Wind = Wind + 0.1;
            c = (-sqr(Wind - Mean))/(2.0*sqr(Variance));
            Probability = Probability + (1.0/(Variance * 2.5055)) * (exp(c)) * 0.1;
        } // while do
        Threshold = 9.9;     // (m/s)
   } //if

} // Probability_threshold procedure


//taken from NewModules.cpp file.
static void Sum(double TQsalt, double TQsusp, double SBsum, double SBsalt, double& DriftH, double& SublH) {

	// total sublimation

	if ((SBsum + SBsalt) >= 0.0)
		SublH = 0.0;
	else
		SublH = (SBsum + SBsalt) * (-1E+3); // -mgmm2s to mg/m^2/s to g/m^2/s

	DriftH = (TQsalt + TQsusp); // kg/m-width/s
 // Convert to interval values

	SublH = SublH * Global::Interval * 3600 * 24 / 1000.0; // g/m^2/s to mm/m^2/interval
	DriftH = DriftH * Global::Interval * 3600 * 24;      // kg/m-width/s to kg/m-width/interval

} // sum procedure


//taken from NewModules.cpp file.
static void Pbsm(double E_StubHt, double Uthr, double& DriftH, double& SublH,
	double t, double u, double rh, double Fetch, long N_S, double A_S)
{

	/*   Modified Calculations for Mean Particle Mass in this version
		 program to calculate blowing snow horizontal flux, sublimation rate
		 and latent heat flux due to snow sublimation for a variety of windspeeds,
		 boundary layers and surface conditions.

		 All variable and constants entered into the programme are in SI and
		 use Canadian Atmospheric Environement Service Meteorological data
		 format.  Snow transport is in kg per square meter per half hour
		 from the surface to 5 metres height.  Sublimation is totaled to the top
		 of the boundary layer for diffusion, based on the meteorological
		 Fetch and is expressed in millimeters of blowing snow lost over
		 a square meter of snow surface per half hour  */

	double   A, Alpha, B, Bd, Bound, C,
		Diff, DmDt, Es, H,
		Htran, Hsalt, Inc, Lamb, Lambda, Lb,
		Mpm, Mpr, Nh, Nsalt,
		Nz, Nuss, Omega, TQsalt,
		TQsum, Qz, RauTerm, Temp,
		Reyn, SBsalt, Sbz, SBsum,
		SigmaZ, Sigma2, SvDens, Usthr, Ustar,
		UstarZ, Uz, Vs, Vsalt, Sigma,
		Vsusp, Z, Zr, Zstb;

	//Compute stubble coefficients

	Zstb = 0.005 * N_S * A_S * E_StubHt * 100.0;      // Lettau, used for susp Z0''
	Lambda = N_S * A_S * E_StubHt;         // Raupach Eq. 1
	Sigma = (M_PI * A_S) / (4.0 * E_StubHt); // Raupach Eq. 4

 // Calculate the flux for interval
	TQsalt = 0.0;                      // Total saltation flux
	TQsum = 0.0;                       // Total Suspension
	SBsalt = 0.0;
	SBsum = 0.0;
	DriftH = 0.0;
	SublH = 0.0;

	Temp = t + 273.0;                 // Convert to Deg. K

 // Check for data errors    Fluxes set to zero for the interval
	if ((Temp < 0.0) || (u < 1.0) || (rh < 0.01)) { return; }

	if (rh >= 1.0) rh = rh / 100.0;       // handle %rh

	Lamb = 0.000076843 * Temp + 0.003130762;   // therm. cond. of atm. (J/(msK))
	Diff = 2.06e-5f * pow(Temp / 273.0f, 1.75f); // diffus. of w.vap. atmos. (m^2/s
	B = PBSM_constants::LATH * PBSM_constants::M / (PBSM_constants::R * Temp) - 1.0;

	// find undersaturation of w. vapour at 2 metres
	Es = 611.15f * exp(22.452f * (Temp - 273.0f) / Temp);  //{sat pressure}
	SvDens = (Es * PBSM_constants::M) / (PBSM_constants::R * Temp);                       //{sat density}
	Sigma2 = rh - 1.0;                              //{undersaturation at 2 m}

	if (u > Uthr) {

		// define saltation parameters and calculate saltation
		//    rate using 10/1987 MODEL OF BLOWING SNOW EQUATIONS

		Usthr = 0.03697f * Uthr;                                  //{Eq. 6.3}
		Ustar = 0.02264f * pow(u, 1.295f);
		if (E_StubHt > 0.0001)                         //{Eq. 6.2 rev}
			RauTerm = 1.0 / ((1.0 - Sigma * Lambda) * (1.0 + PBSM_constants::Beta * Lambda)); //{Raupach}
		else
			RauTerm = 1.0;

		Hsalt = PBSM_constants::C2 / (2.0f * PBSM_constants::g) * sqr(Ustar);                         //{Eq. 4.13}
		Nsalt = 2.0 * PBSM_constants::rho / (PBSM_constants::C2 * PBSM_constants::C3 * Ustar) * (RauTerm - sqr(Usthr) / sqr(Ustar)); //{Eq. 4.14 updated}

		if (Nsalt <= 0.0) {
			Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
			return;
		}

		TQsalt = PBSM_constants::C1 * PBSM_constants::rho * Usthr / (PBSM_constants::g * PBSM_constants::C3 * Ustar) * (sqr(Ustar) * RauTerm - sqr(Usthr)); // Eq. 4.20

  // calculate sublimation rate in the saltation layer

		Mpr = 100E-6;
		Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
		Alpha = 5.0;

		SigmaZ = Sigma2 * (1.019 + 0.027 * log(Hsalt)); // Eq. 6.20, Revised in May. 1997
		if (SigmaZ > -0.01) { SigmaZ = -0.01; }
		Vsalt = 0.6325 * Ustar + 2.3 * Usthr;          // Eq. 6.25
		Reyn = (2.0 * Mpr * Vsalt) / 1.88E-5;            // Eq. 6.22
		Nuss = 1.79 + 0.606 * sqrt(Reyn);              // Eq. 6.21
		A = Lamb * Temp * Nuss;
		C = 1.0 / (Diff * SvDens * Nuss);
		DmDt = ((2.0 * M_PI * Mpr * SigmaZ) - (Htran * B / A)) / ((PBSM_constants::LATH * B / A) + C);

		//{Eq. 6.16} {Gamma Dist. Corr.}
		Mpm = 4.0 / 3.0 * M_PI * PBSM_constants::DICE * Mpr * sqr(Mpr) * (1.0 + 3.0 / Alpha + 2.0 / sqr(Alpha));

		Vs = DmDt / Mpm;                // Sublimation rate coefficient Eq. 6.13
		SBsalt = Vs * Nsalt * Hsalt;  // Eq. 6.11

  // calculate mass flux in the suspended layers and the sublimation
  //     rate for layers of height Inc from height r to b

		Zr = 0.05628 * Ustar;         // Eq. 5.27
		Alpha = 15.0;
		Inc = 0.0001;

		// Loop to find the first suspended drift density level, r
		//     from the reference level Zr
		//     To preserve continuity with saltation the first suspended
		//     level drift density is less than or equal to Nsalt.

		TQsum = 0;
		SBsum = 0;

		Z = Zr + Inc;
		while (Z <= 0.15) {
			Nz = 0.8 * exp(-1.55 * (pow(0.05628f * Ustar, -0.544f) - pow(Z, -0.544f)));

			// Eq. 5.26, Revised in Dec. 1995
			if (Nz <= Nsalt) { goto Ten; }
			Z = Z + Inc;
		} //while
	Ten:  Lb = Z + Inc;
		Z = Lb;
		Inc = 0.001;

		// find height of fully-developed boundary layer for turbulent
		//     diffusion using a form of Pasquills plume dispersion eq.
		//     iterate towards Bound

		Bd = 1.0;
		Bound = PBSM_constants::ZD + (PBSM_constants::KARMAN2 * (Fetch - PBSM_constants::XD) * pow(log(Bd * 162.926f /
			sqr(Ustar)) * log(PBSM_constants::ZD * 162.926f / sqr(Ustar)), -0.5f));          // Eq. 6.9
		while (fabs(Bound - Bd) > 0.001) {
			Bd = Bound;
			Bound = PBSM_constants::ZD + (PBSM_constants::KARMAN2 * (Fetch - PBSM_constants::XD) * pow(log(Bd * 162.926f /
				sqr(Ustar)) * log(PBSM_constants::ZD * 162.926f / sqr(Ustar)), -0.5f));      // Eq. 6.9
		} //while


  // Loop to calculate the suspended mass flux up to 5 metres
  //     and the total sublimation rate to the top of the boundary layer
  //   at increments of 1 mm to 50cm & increments of 10 cm to  b

	Twenty: H = Z + Inc;
		while (H <= Bound) {
			Nh = 0.8 * exp(-1.55f * (pow(0.05628f * Ustar, -0.544f) - pow(H, -0.544f)));
			Nz = Nh;
			UstarZ = Ustar * pow(1.2f / (1.2f + Nz), 0.5f);                  // Eq. 5.17a
			Uz = (UstarZ / PBSM_constants::KARMAN) * log(H / ((0.00613f * sqr(Ustar)) + Zstb));// Eq. 4.17r
			if (Uz > 0) {
				Mpr = 4.6e-5 * pow(H, -0.258f);                            // Eq. 6.15
				if (H >= 5.0) { Mpr = 30E-6f; }

				Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
				Alpha = 4.08 + 12.6 * H;                                  // Eq. 6.14
				if (H >= 1.5) { Alpha = 25.0; }

				SigmaZ = Sigma2 * (1.019 + 0.027 * log(H));  // Eq. 6.20, Revised in May. 1997
				if (SigmaZ > -0.01) { SigmaZ = -0.01; }
				Omega = 1.1e7f * pow(Mpr, 1.8f);               // Eq. 5.18
				Vsusp = Omega + 0.0106f * pow(Uz, 1.36f);
				Reyn = (2.0f * Mpr * Vsusp) / 1.88e-5f;          // Eq. 6.22
				Nuss = 1.79f + 0.606f * sqrt(Reyn);            // Eq. 6.21
				A = Lamb * Temp * Nuss;
				C = 1.0 / (Diff * SvDens * Nuss);
				DmDt = ((2.0f * M_PI * Mpr * SigmaZ) - (Htran * B / A)) / ((PBSM_constants::LATH * B / A) + C);
				Mpm = 1.333f * M_PI * PBSM_constants::DICE * sqr(Mpr) * Mpr *   // Eq. 6.16
					(1.0f + 3.0f / Alpha + 2.0f / sqr(Alpha));       // Gamma Dist. Corr.
				Vs = DmDt / Mpm;                               // Eq. 6.13
				Sbz = Vs * Nz * Inc;                         // mg
				SBsum = SBsum + Sbz;                         // Eq. 6.12
				Qz = Nz * Uz * Inc;                          // Eq. 5.4
				if (H >= 5.0) { Qz = 0.0; }
				TQsum = TQsum + Qz;                          // Eq. 5.5
				if (Nz >= 1e-5) {
					if (((H - Inc) >= 0.5) && (H < 0.6)) {
						Inc = 0.1;
						Z = 0.5;
						goto Twenty;                            // re start the loop
					} //{if}
				}
				else {
					Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
					return;
				} // if
			}
			else {
				TQsalt = 0.0;
				TQsum = 0.0;
				SBsalt = 0.0;
				SBsum = 0.0;
				Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
				return;
			} // if
			H = H + Inc;
		} // while
	} // if
	Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
} //PBSM procedure}

//taken from NewModules.cpp
static double Farouki_a(double fract_por) {

	double a = 0.0;
	double nnew = 0.0;

	while (fabs(fract_por - nnew) > 0.001) {
		a += (fract_por - nnew) * 0.25;
		nnew = 3 * a * a - 2 * a * a * a;
	}
	return a;
}


//Define HMSA constants:

static const double rho_a = 1.2; // (kg/m3) air
static const double rho_i = 920.0; // (kg/m3) ice

static const double c_a = 1010.0; // (J/kg/K) air
static const double c_i = 2120.0; // (J/kg/K) ice

static const double Cv_a = 1212.0; // (J/m3/K) air
static const double Cv_i = 1950400.0; // (J/m3/K) ice
static const double Cv_w = 4185000.0; // (J/m3/K) water

static const double lam_a = 0.025; // (W/m/K) air
static const double lam_i = 2.24;  // (W/m/K) ice
static const double lam_w = 0.57;  // (W/m/K) water

static const double Rho_Organic = 1300.0; // (kg m-3)
static const double Rho_Minerals = 2650.0; // (kg m-3)
static const double Rho_Water = 1000.0; // (kg m-3)
static const double Rho_Ice = 920.0; // (note: 890.0 on Hayashi's paper) (kg m-3)
static const double Rho_Snow = 200.0; // (kg m-3)
static const double Rho_Air = 1.2;  // (kg m-3)

//K_x: heat conductivity
static const double K_Organic = 0.21;  // W/(m K)  //0.25
static const double K_Minerals = 2.50;  // W/(m K)  //2.9
static const double K_Air = 0.025; // W/(m K)
static const double K_Ice = 2.24;  // W/(m K)
static const double K_Water = 0.57;  // W/(m K)

//HC_x: specific heat capacity
static const double HC_Minerals = 890.0; //745.1 // J/(kg.K)
static const double HC_Water = 4185.0; // J/(kg.K)
static const double HC_Air = 1010.0; // J/(kg.K)
static const double HC_Organic = 1920.0; // J/(kg.K)
static const double HC_Ice = 2120.0; // J/(kg.K)
static const double Water_Ice = 334.0e3; // latent heat for fusion of water (J kg-1)
static const double Max_Layers = 20;  // maximum layers allowed

static const double DEGtoRAD = M_PI / 180.0;
static const double DEGtoRAD365 = 2 * M_PI / 365.0;
static const long CalcFreq = 288;
static const double RADxxMIN = 2.0 * M_PI / CalcFreq;
static const double MINS_int = 24.0 * 60.0 / CalcFreq;


static double textureproperties[][6] = { // mm/hour
  {7.6, 12.7, 15.2, 17.8, 25.4, 76.2},  // coarse over coarse
  {2.5,  5.1,  7.6, 10.2, 12.7,  15.2}, // medium over medium
  {1.3,  1.8,  2.5,  3.8,  5.1,  6.4},  // medium/fine over fine
  {0.5,  0.5,  0.5,  0.5,  0.5,  0.5}   // soil over shallow bedrock
};

#ifndef M_PI
#define M_PI   3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

static const double rho_s[] = { 41.1, 75.2, 91.4, 1300.0, 1300.0 }; // (kg/m3) solids
static const double c_s[] = { 1920.0, 1920.0, 1920.0, 890.0, 890.0 }; // (J/m3/K) solids
static const double Cv_s[] = { 78912.0, 144384.0, 175392.0, 1157000.0, 1157000.0 }; // (J/m3/K) solids
static const double lam_s[] = { 0.21, 0.21, 0.21, 2.50, 2.50 };  // (W/m/K) solids
static const double ks_s[] = { 450.0, 154.0, 13.0, 5.0, 3.0 }; // (m/day)  solids
static const double por_s[] = { 0.96, 0.9, 0.87, 0.43, 0.43 }; // ()  solids

#define Hf  334.4E3    // Latent heat of fusion, J/kg
#define majorMelt 5.0      // threshold for major melt event(5 mm/d)


static double fLimit;

#define AH		1.0	// ratio sensible/momentum phi func
#define AV		1.0	// ratio latent/momentum phi func
#define ITMAX		50	// max # iterations allowed
#define PAESCHKE	7.35	// Paeschke's const (eq. 5.3)
#define THRESH		1.e-5	// convergence threshold

#define SM		0
#define SH		1
#define SV		2
#define BETA_S		5.2
#define BETA_U		16

#endif
