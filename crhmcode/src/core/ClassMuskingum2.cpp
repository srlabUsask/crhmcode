#include "ClassMuskingum2.h"
#include <algorithm>    // std::max
#include <exception>    // std::exception


//---------------------------------------------------------------------------
ClassMuskingum2::ClassMuskingum2(const double* inVar, double* outVar, 
                                const double* k, const double* X_M, const long nhru)
	: inVar(inVar), outVar(outVar), nhru(nhru) {

	// !!! UNITS !!!

	// kstorage (days)
	// lag (hours)

	c0 = new double[nhru];
	c1 = new double[nhru];
	c2 = new double[nhru];

	/*
	* If on every cycle the water moves one step then the number of elements determines how many steps
	* are required to get to the end of the stream.
	*/

	buff_sz = new long[nhru];
	K_sub = new double[nhru];
	x_atten = new double[nhru];


	for (long hh = 0; hh < nhru; hh++) {

// Add 1 to buff_sz because the first buffer location just holds the inflow values
// actual outflow values start from the second buffer location
        buff_sz[hh] = 1 + std::max(1l, lround(k[hh]/Global::Interval));
        K_sub[hh] = k[hh] / ( buff_sz[hh] - 1);  // The 1 additional should not be included here
        x_atten[hh] = X_M[hh];


		c0[hh] = (Global::Interval - 2.0 * K_sub[hh] * X_M[hh]) /
			(2.0 * K_sub[hh] * (1.0 - X_M[hh]) + Global::Interval);  // units of Global::Interval (days)

		c1[hh] = (Global::Interval + 2.0 * K_sub[hh] * X_M[hh]) /
			(2.0 * K_sub[hh] * (1.0 - X_M[hh]) + Global::Interval); // units of kstorage (days)

		c2[hh] = (2.0 * K_sub[hh] * (1.0 - X_M[hh]) - Global::Interval) /
			(2.0 * K_sub[hh] * (1.0 - X_M[hh]) + Global::Interval); // units of kstorage (days)

	}

	buff_q = new double* [nhru];   // create mem storage for segment discharge

	for (long hh = 0; hh < nhru; hh++) {
		buff_q[hh] = new double[buff_sz[hh]];
		for (long jj = 0; jj < buff_sz[hh]; jj++)
			buff_q[hh][jj] = 0.0;
	}
}

ClassMuskingum2::~ClassMuskingum2() {
	delete[] c0;
	delete[] c1;
	delete[] c2;
	delete[] buff_sz;
	delete[] K_sub;
	delete[] x_atten;

	for (long hh = 0; hh < nhru; hh++)
		delete[] buff_q[hh];
	delete[] buff_q;
}

void ClassMuskingum2::ChangeLag(const double* newlag, const long hh)
{
    // This is only ever used by ClassMeltRunoff_Lag
    throw std::runtime_error("Not Implemented");
}

void ClassMuskingum2::DoMuskingum() {

	for (long hh = 0; hh < nhru; hh++) {
        DoMuskingum(hh);
	}
}

void ClassMuskingum2::DoMuskingum(const long hh) {

    double q_prev = buff_q[hh][0];
    buff_q[hh][0] = inVar[hh];
    for (int i=1; i<buff_sz[hh]; i++) {
        const double q_tmp = buff_q[hh][i];   
    // Qout1 = C0 * Qin1 + C1 * Qin0 + C2 * Qout0 
        buff_q[hh][i] = c0[hh] * buff_q[hh][i-1] + c1[hh] * q_prev + c2[hh] * buff_q[hh][i];
        q_prev = q_tmp;
    }
    outVar[hh] = buff_q[hh][buff_sz[hh]-1];
}

double ClassMuskingum2::Left(int hh) {

	double Sstorage = 0;

	for (int ii = 1; ii < buff_sz[hh]; ++ii) {
        Sstorage += K_sub[hh] * ( x_atten[hh] * buff_q[hh][ii-1] + (1-x_atten[hh])*buff_q[hh][ii] );
    }

	return Sstorage;
}

//---------------------------------------------------------------------------
