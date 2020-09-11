#if defined(_WIN32)
#include "stdafx.h"
#endif

// 11/20/17
//---------------------------------------------------------------------------

#include "Common.h"

#include <cmath>
#include <algorithm>
#include <limits>

//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace std;

snowcover::snowcover(double SWEmean, double cv) {  //Manishankar: this is only being used in NewModules.cpp
	double x;
 	//double sca; (unreferenced commented out for now (jsh507)
	N = 150;
	//const long N = 150; (removed in favor of member variable N - jhs507)
	data = new double[N];

	for (int ii = 0; ii < N; ii++) {
		x = SWEmean * 2.0*(ii + 1) / N;
		double K = (x - SWEmean) / (SWEmean*cv);

		double Sy = sqrt(log(cv*cv + 1.0));

		double Ky = (log(K*sqrt(exp(Sy*Sy) - 1.0) + 1.0) + Sy * Sy / 2.0) / Sy;

		double t = 1 / (1 + little_p * Ky);

		double P = (exp(-Ky * Ky / 2) / sqrt(2 * M_PI)) * (a1*t + a2 * pow(t, 2) + a3 * pow(t, 3));

		data[ii] = P;
	}

};

// Saturation vapour pressure (kPa)
// Saturation humidity (kg/kg) Over ice and water
double Common::estar(double t) /* Saturation vapour pressure kPa*/
{
	if (t > 0.0)
		return 0.611 * exp(17.27*t / (t + 237.3));
	else
		return 0.611 * exp(21.88*t / (t + 265.5));
}

double Common::Qs(double P, double tc) { // P (KPa)  //Manishankar: this function is only being used in NewModules.cpp.

	double es; // Vapour pressure (Pa)

	if (tc >= 0)
		es = 0.611213*exp(17.5043*tc / (241.3 + tc));
	else
		es = 0.611213*exp(22.4422*tc / (272.186 + tc));

	return(0.622*es / P);
}

// Saturation humidity (kg/kg) Over water
double Common::Qswater(double P, double tc) { // P (KPa)

	double es; // Vapour pressure (KPa)

	es = 0.611213*exp(17.5043*tc / (241.3 + tc));

	return(0.622*es / P);
}

double Common::DepthofSnow(double SWE)
{
	/* 3/5/98
	Calculates Snow Depth(m) from SWE(mm) */
	double Snow_Depth;

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

double Common::SWE_prob(double SWEmean, double SWE, double CV) { //Manishankar: This function is only being used in NewModules.cpp

	if (SWE <= 0.01) return 0.0; // handle log(0) error
	if (SWE >= SWEmean) return 1.0; //

	double K = -SWE / (SWEmean*CV);

	double Sy = sqrt(log(1.0 + CV * CV));

	double Ky = log(1.0 + K * CV) / Sy + Sy / 2.0;

	double t = 1 / (1 + little_p * Ky);

	double P = (exp(-Ky * Ky / 2) / sqrt(2 * M_PI)) * (a1*t + a2 * t*t + a3 * t*t*t);

	if (P > 1.0 || P < 0.001) // handle discontinuity
		P = 1.0;

	return P;
}

double Common::SVDens(double Temp)

{
	return 1.324*exp(22.452*Temp / (Temp + 273.15)) / (Temp + 273.15);
}
// outputs sat. vapor density, kg/m^3


void Common::GroupEnding(string &AA, int Cnt) {

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

double Common::Ice_Bulb(double Tc, double RH, double Pa) {

	double Tk = Tc + CRHM_constants::Tm;

	double D = 0.0000206*pow(Tk / CRHM_constants::Tm, 1.75);

	double RHO = Pa * 1000.0 / (CRHM_constants::Rgas*Tk);

	double qt = CRHM_constants::em / (Pa*1000.0)*611.213*exp(22.4422*Tc / (CRHM_constants::Tm + Tc));

	double lamda = 0.000076843*Tk + 0.003130762;

	double L;
	if (Tc > 0.0)
		L = CRHM_constants::Lv;
	else
		L = CRHM_constants::Ls;

	double delta = CRHM_constants::em*L*qt / (CRHM_constants::Rgas*sqr(Tk));

	return Tc - L * (1.0 - RH / 100.0)*qt / (CRHM_constants::Cp + L * delta) *(RHO*CRHM_constants::Cp*D / lamda);
} // returns ice bulb temperature, Pa (kPa), RH(%).


void Common::Message(const char *s1, const char *s2) {

	cout << s1 << ", " << s2 << endl;
}

void Common::Message(const string s1, const string s2) {

	cout << s1 << ", " << s2 << endl;
}

string Common::lowercase(string &s) {  //Manishankar: in CRHMmain.cpp, utils.cpp, CRHMmainDlg.cpp

	transform(s.begin(), s.end(), s.begin(), (int(*)(int)) tolower);
	return s;
}



int Common::IndexOf(TStringList *Box, const string S) { //Manishankar: being used in different places in different ways.
	for (int ii = 0; ii < Box->Count; ++ii) {
		if (Box->Strings[ii] == S)
			return ii;
	}
	return -1;
}

string Common::longtoStr(long L) { //Manishankar: in two or more files.
	ostringstream temp;
	temp << L;
	return temp.str();
}


string Common::trimleft(string& str) {

	string::size_type pos = str.find_first_not_of(" \t");

	if (pos != string::npos)
		if (pos > 0)
			str.erase(0, pos);

	return str;
}

string Common::trimright(string& str) //
{
	if (!str.empty()) {

		string::size_type pos = str.find_last_not_of(" \t");

		if (pos != string::npos)
			if (pos < str.length() - 1)
				str.erase(++pos);
	}

	if (!str.empty())
	{
		int l = str.length();
		if (str[l - 1] == '\'') { str.erase(l - 1); }
	}

	return str;
}


string Common::trim(string& str) { //Manishankar: in two or more files.

	trimleft(str);
	trimright(str);

	return str;
}

double Common::StrtoDt(string s) {  //Manishankar: this is being used in ClassCRHM.cpp only.

	istringstream instr;
	instr.str(s);

	double D;
	instr >> D;
	return D;
}

bool Common::EqualUpper(string s1, string s2) {
	transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
	transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
	return (bool)(s1 == s2);
}

double Common::KyValue(double probability, double guess) {
	// finds location of probability, using polynomial approx to normal dist
	//   from "Handbook of Mathematical Functions" by Abramowitz and Stegun}

	double Ky, TempP, t;
	bool  done = false;
	double direction = -1;       // increasing
	double tolerance = 0.0001;
	double dKy = 0.1;      // increment
	long  iterations = 0;

	Ky = guess;        // start value

	while (!done) {
		iterations++;
		t = 1 / (1 + little_p * Ky);
		TempP = (exp(-Ky * Ky / 2) / sqrt(2 * M_PI)) * (a1*t + a2 * t*t + a3 * t*t*t);

		if (fabs(TempP - probability) <= tolerance)
		{
			done = true;
		}
		else {
			if (TempP > (probability + tolerance))
			{
				if (direction == -1) {
					dKy = dKy / 2;
					direction = 1;
				}
				else {
					dKy = dKy / 2;
					direction = -1;
				}
			}

			Ky = Ky + dKy * direction;
		}
	} // while

	return Ky;
}

double Common::K(double Ky, double LogStDev) {

	return (exp(LogStDev*Ky - (sqr(LogStDev) / 2)) - 1) / (sqrt(exp(sqr(LogStDev)) - 1));
}


string Common::GetCurrentPath(void) {

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

	buffer = getcwd(NULL, 0);
	printf("Current path is %s", buffer);
	return buffer;
}

bool Common::Variation_Decide(int Variation_set, long Variation) {

	VandP V; V.Set(Variation);

	long variations = V.GetV(); // & 2047;

	if (((variations & 2048) != 0 && Variation_set == 0) || // handles VARIATION_0   //warning resolved by Manishankar
		(variations & 4096) != 0 ||                        // handles VARIATION_0
		(variations == 0) ||                               // handles VARIATION_ORG
		(variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
		return true;
	else
		return false;
}

void Common::writefile(string filepath, string content)
{
	ofstream myfile;
	myfile.open(filepath, ios::app);
	myfile << "\n" << content;
	myfile.close();
}

/////////////////////////////////////////

bool static isdigit(char ch)
{
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9') { return true; }
	return false;
}

/////////////////////////////////////////

