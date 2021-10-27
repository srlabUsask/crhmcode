#pragma once

#ifndef TSERIES
#define TSERIES

class TSeries {
public:
	std::vector<double> XValues;
	std::vector<double> YValues;
	ClassVar* Tag{ NULL };
	//int MaxCnt;
	string Title;
	
	TSeries() 
	{ 
		//MaxCnt = Cnt; 
		XValues = vector<double>(); 
		YValues = vector<double>();
	};
	
	~TSeries() 
	{ 
	};

	void AddXY(double X, double Y)
	{
		XValues.insert(XValues.end(), X);
		YValues.insert(YValues.end(), Y);
	};
	
	int Count(void) 
	{ 
		return XValues.size(); 
	};
	
	double XValue(int nn) 
	{ 
		return XValues.at(nn);
	};
	
	double YValue(int nn) 
	{ 
		return YValues.at(nn);
	};
};

#endif // !TSERIES
