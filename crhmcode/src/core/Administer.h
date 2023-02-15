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

#ifndef ADMINISTER
#define ADMINISTER

#include "ClassModule.h"

class ClassModule;

class   Administer {

public:
	std::vector<std::pair<std::string, ClassModule *>> * DLLModuleList;       // modules defined in DLL
	std::vector<std::pair<std::string, int>> * DLLModelList;        // models defined in DLL
	std::vector<std::string> * DLLModelModuleList;  // modules used in DLL models in CommaText
	string Version;
	string DLLName;
	string HelpFile;

	Administer(string Version, string _HelpFile);
	~Administer();

	void   MacroClear();
	void   MacroUpdate();
	void   AddModule(ClassModule* Module);
	void   AddModel(string ModelName, string ModelModules);
	void   LoadCRHM(string DllName);



	//void   Accept(int Result = mbYes);
	void   Accept(int Result = 0);



};

#endif // !ADMINISTER
