#pragma once

#include <fstream>
#include <string>

#include "../Common/CRHMException.h"
#include "CRHMmain.h"
#include "CRHMLogger.h"
#include "../GlobalDll.h"

class CRHMmain;

class ReportStream
{
private:
	std::basic_ofstream<char, std::char_traits<char>> * reportFileStream;

public:
	ReportStream(std::string reportName);
	void OutputHeaders(CRHMmain * instance);
	void SendTimeStepToReport(CRHMmain* instance);
	void CloseStream();
	std::list<std::string> * RprtHeader(CRHMmain * instance);
	std::list<std::string> * RprtHeaderObs(CRHMmain* instance);



};

