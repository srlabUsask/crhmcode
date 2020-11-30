#include "snowcover.h"


snowcover::snowcover(double SWEmean, double cv) {  //Manishankar: this is only being used in NewModules.cpp
	double x;
	//double sca; variable is unreferenced commenting out for now - jhs507

	const long N = 150;
	data = new double[N];

	for (int ii = 0; ii < N; ii++) {
		x = SWEmean * 2.0 * ((long long)ii + 1ll) / N;
		double K = (x - SWEmean) / (SWEmean * cv);

		double Sy = sqrt(log(cv * cv + 1.0));

		double Ky = (log(K * sqrt(exp(Sy * Sy) - 1.0) + 1.0) + Sy * Sy / 2.0) / Sy;

		double t = 1 / (1 + little_p * Ky);

		double P = (exp(-Ky * Ky / 2) / sqrt(2 * M_PI)) * (a1 * t + a2 * pow(t, 2) + a3 * pow(t, 3));

		data[ii] = P;
	}

};