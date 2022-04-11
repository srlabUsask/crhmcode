#pragma once

#ifndef CLASSMUSKINGUM2
#define CLASSMUSKINGUM2

#include "ClassModule.h"


class   ClassMuskingum2 {

public:
	ClassMuskingum2(const double* inVar, double* outVar, 
                    const double* k, const double* X_M, const long nhru);
	~ClassMuskingum2();
	void DoMuskingum();
	void DoMuskingum(const long hh);
	void ChangeLag(const double* newlag, const long hh);
	double Left(int hh);


	double* c0; // storage constant from K
	double* c1; // storage constant from K
	double* c2; // storage constant from K
	double prevdate{ 0.0 };

private:
	const  double* inVar;
	double* outVar;

	double** buff_q;

	double* K_sub; //
	double* x_atten; //

	long nhru;
	long* buff_sz; // number of segments (buckets) 

};

#endif // !ClassMuskingum2
