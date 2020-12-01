#pragma once

#ifndef TSERIES
#define TSERIES

class TSeries {
public:
	double* XValues;
	double* YValues;
	ClassVar* Tag{ NULL };
	int MaxCnt;
	int Used;
	string Title;
	TSeries(int Cnt) { MaxCnt = Cnt; XValues = new double[MaxCnt]; YValues = new double[MaxCnt]; Used = 0; };
	~TSeries() { delete[] XValues; delete[] YValues; };
	void AddXY(double X, double Y)
	{
		XValues[Used] = X;
		YValues[Used++] = Y;
	};
	int Count(void) { return Used; };
	double XValue(int nn) { return XValues[nn]; };
	double YValue(int nn) { return YValues[nn]; };
};

#endif // !TSERIES
