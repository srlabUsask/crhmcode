#pragma once

#ifndef SNOWCOVER
#define SNOWCOVER

#include "Common.h"

class snowcover {
public:
	double* data{ NULL };
	long  N{ 0 };
	snowcover(double SWEmean, double cv);
	double lookup(double melt) { return 0; };
	~snowcover() { delete[] data; };
};

#endif // !SNOWCOVER
