#pragma once

#ifndef MMSDATA
#define MMSDATA

class MMSData
{
public:
	double** mmsData{ NULL };
	long** mmsDataL{ NULL };
	bool GoodRun{ false };
	ClassModule* obs_preset{ NULL };
	string S;
};

#endif // !MMSDATA
