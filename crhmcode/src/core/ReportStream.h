/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
#pragma once

#include <fstream>
#include <string>

#include "CRHMException.h"
#include "CRHMmain.h"
#include "CRHMLogger.h"
#include "GlobalDll.h"

class CRHMmain;

class ReportStream
{
private:
	std::basic_ofstream<char, std::char_traits<char>> * reportFileStream;

public:
	ReportStream(std::string reportName);
	void OutputHeaders(CRHMmain * instance);
	void OutputSummaryHeaders(std::list<std::pair<std::string, TSeries*>>* series);
	void OutputSummaryLines(std::list<std::pair<std::string, TSeries*>>* series);
	void SendTimeStepToReport(CRHMmain* instance);
	void CloseStream();
	std::list<std::string> * RprtHeader(CRHMmain * instance);
	std::list<std::string> * RprtHeaderObs(CRHMmain* instance);



};
