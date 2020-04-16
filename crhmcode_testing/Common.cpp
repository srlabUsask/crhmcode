#include "stdafx.h"

// 11/20/17
//---------------------------------------------------------------------------

#include "Common.h"

#include <math.h>
#include <algorithm>
#include <limits>

//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace std;



/*
void GroupEnding(string &AA, int Cnt) {
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

*/

//---------------------------------------------------------------------------
//float static sqr(float X) { return X * X; }

//---------------------------------------------------------------------------






//---------------------------------------------------------------------------


  //---------------------------------------------------------------------------




/*
const float a1          =   0.31938;     //constants of approximation
const float a2          =  -0.35656;
const float a3          =   1.78147;
const float a4          =  -1.82125;
const float a5          =   1.33027;
const float little_p    =   0.23164; */

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//snowcover::snowcover(float SWEmean, float cv) {
//
//	float x, sca;
//
//	const long N = 150;
//	data = new float[N];
//
//	for (int ii = 0; ii < N; ii++) {
//		x = SWEmean * 2.0*(ii + 1) / N;
//		float K = (x - SWEmean) / (SWEmean*cv);
//
//		float Sy = sqrt(log(cv*cv + 1.0));
//
//		float Ky = (log(K*sqrt(exp(Sy*Sy) - 1.0) + 1.0) + Sy * Sy / 2.0) / Sy;
//
//		float t = 1 / (1 + little_p * Ky);
//
//		float P = (exp(-Ky * Ky / 2) / sqrt(2 * M_PI)) * (a1*t + a2 * pow(t, 2) + a3 * pow(t, 3));
//
//		data[ii] = P;
//	}
//}

//---------------------------------------------------------------------------
//snowcover::~snowcover() {
//	delete[] data;
//}

//---------------------------------------------------------------------------
//float  snowcover::lookup(float melt) {
//	return 0;
//}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//float static SVDens(float Temp) /* outputs sat. vapor density, kg/m^3 */
//{
//	return 1.324*exp(22.452*Temp / (Temp + 273.15)) / (Temp + 273.15);
//}

//---------------------------------------------------------------------------
/*float Ice_Bulb(float Tc, float RH, float Pa) // returns ice bulb temperature, Pa (kPa), RH(%).
{
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
}*/