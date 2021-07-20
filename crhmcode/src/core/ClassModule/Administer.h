#pragma once

#ifndef ADMINISTER
#define ADMINISTER

#include "ClassModule.h"

class ClassModule;

class   Administer {

public:
	std::vector<std::pair<std::string, ClassModule *>> * DLLModuleList;       // modules defined in DLL
	std::vector<std::pair<std::string, int>> * DLLModelList;        // models defined in DLL
	TStringList* DLLModelModuleList;  // modules used in DLL models in CommaText
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
