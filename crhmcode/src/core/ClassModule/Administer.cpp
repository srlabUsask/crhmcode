#include "Administer.h"

//---------------------------------------------------------------------------
Administer::Administer(string Version, string _HelpFile) : Version(Version), HelpFile(_HelpFile) {

	DLLModuleList = new std::vector<std::pair<std::string, ClassModule *>>();
	DLLModelList = new std::vector<std::pair<std::string, int>>();
	DLLModelModuleList = new std::vector<std::string>();

	if (Global::PendingDLLModuleList != NULL)
	{
		Global::PendingDLLModuleList->clear(); // clear
	}
		
}

//---------------------------------------------------------------------------
Administer::~Administer() {

	for (size_t ii = 0; ii < DLLModuleList->size(); ++ii)
	{
		delete DLLModuleList->at(ii).second; // delete modules
	}
		

	delete DLLModuleList;
	delete DLLModelList;
	delete DLLModelModuleList;
}

//---------------------------------------------------------------------------
void Administer::MacroClear() {

	for (size_t ii = 0; ii < DLLModuleList->size(); ++ii) {

		/*int jj = Global::AllModulesList->IndexOf(DLLModuleList->strings[ii]);
		if (jj > -1)
		Global::AllModulesList->Delete(jj);*/

		ClassModule * thisModule = DLLModuleList->at(ii).second;
		delete thisModule;
	}

	if (Global::OurHelpList) {
		std::map<std::string, int>::iterator indx = Global::OurHelpList->find(HelpFile);
		if (indx != Global::OurHelpList->end()) // delete Macro help file.
		{
			Global::OurHelpList->erase(indx);
		}
	}

	DLLModuleList->clear();
	DLLModelList->clear();
	DLLModelModuleList->clear();
}

//---------------------------------------------------------------------------
void Administer::MacroUpdate() {
	for (size_t ii = 0; ii < DLLModuleList->size(); ++ii) 
	{
		std::list<std::pair<std::string, ClassModule*>>::iterator pos;
		bool moduleFound = false;
		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
			it != Global::OurModulesList->end();
			it++
			)
		{
			if (it->first == DLLModelList->at(ii).first)
			{
				moduleFound = true;
				pos = it;
			}
		}

		if (moduleFound) // Update Macro Module address
		{
			pos->second = DLLModuleList->at(ii).second;
		}
			
	}
}

//---------------------------------------------------------------------------
void Administer::AddModule(ClassModule* Module) {

	Module->OurAdmin = this;
	DLLModuleList->push_back(std::pair<std::string, ClassModule *>(Module->Name.c_str(), Module));
	Global::PendingDLLModuleList->push_back(std::pair<std::string, ClassModule *>((Module)->Name.c_str(), Module));
}

//---------------------------------------------------------------------------
void Administer::AddModel(string ModelName, string ModelModules) {

	DLLModelModuleList->push_back(ModelModules);
	//DLLModelList->AddObject(ModelName, (TObject*)(DLLModelModuleList->Count - 1)); // removed this line and added the following two for resolving a warning.
	int _object = DLLModelModuleList->size() - 1;
	DLLModelList->push_back(std::pair<std::string, int>(ModelName, _object));
}

//---------------------------------------------------------------------------
void Administer::LoadCRHM(string DllName) {

	DLLName = DllName;
}

//---------------------------------------------------------------------------
void Administer::Accept(int Result) {

	string Exists;
	//  TMsgDlgType MsgDlgType;
	ClassModule* thisModule;

	for (size_t ii = 0; ii < DLLModuleList->size(); ++ii) { // All modules in DLL

		bool foundInPending = false;
		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::PendingDLLModuleList->begin();
			it != Global::PendingDLLModuleList->end();
			it++
			)
		{
			if (it->first == DLLModuleList->at(ii).first)
			{
				foundInPending = true;
			}
		}


		if (Global::PendingDLLModuleList->size() != 0  // Do not load unless requested.  Count == 0 means all!
			&& foundInPending == false)
		{
			continue;
		}
			

		int jj = Global::AllModulesList->count(DLLModuleList->at(ii).first);
		if (jj != 0) 
		{
			Exists = "Over-write existing module \"";
			//      MsgDlgType = mtWarning;
		}
		else 
		{
			Exists = "Load Module \"";
			//      MsgDlgType = mtInformation;
		}

		bool inOurModulesList = false;
		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
			it != Global::OurModulesList->end();
			it++
			)
		{
			if (it->first == DLLModelList->at(ii).first)
			{
				inOurModulesList = true;
				
			}
		}		

		if (Global::AllModulesList->count(DLLModuleList->at(ii).first) == 0 // Needed to be put back!
			&& inOurModulesList)
			Result = mbYes;
		//    else if(Result != mbYesToAll && Result != mbNoToAll){ // optional
		//      Result = MessageDlg(Exists + DLLModuleList->Strings[ii] + "\" ?",
		//      MsgDlgType,
		//      TMsgDlgButtons() << mbYes << mbNo << mbYesToAll << mbNoToAll, 0);
		//      }

		switch (Result) {
		case mbYes:
		case mbYesToAll:
			if (jj != 0) 
			{
				LogError(CRHMException((DLLModuleList->at(ii).first + " module being replaced").c_str(), TExcept::WARNING));
				Global::AllModulesList->erase(DLLModuleList->at(ii).first);
			}

			thisModule = DLLModuleList->at(ii).second;
			thisModule->DLLName = DLLName;
			if (thisModule->DLLName != "Macro")
			{
				thisModule->ID = typeid(*thisModule).name();
			}
				

			Global::AllModulesList->insert(std::pair<std::string, ClassModule*>(DLLModuleList->at(ii).first,
				DLLModuleList->at(ii).second));
			break;

		case mbNo:
		case mbNoToAll:
			continue;
		default:
			break;
		}
	}

	for (size_t ii = 0; ii < DLLModelList->size() ; ++ii) {

		// when sorted index used to access ModelModulesList		
		int _object = ii;
		Global::AllModelsList->push_back(std::pair<std::string, int>(DLLModelList->at(ii).first, _object));

		// Administer object used to find which DLL loaded model
		Global::ModelModulesList->push_back(std::pair<std::string, Administer *>(DLLModelModuleList->at(ii), this));
	}

	if (Global::OurHelpList)
	{
		if (Global::OurHelpList->count(HelpFile) != 0)  // No duplicates
		{
			Global::OurHelpList->insert(std::pair<std::string, int>(HelpFile, 1));
		}
		else
		{
			Global::OurHelpList->insert(std::pair<std::string, int>(HelpFile, 0));
		}
	}

	Global::PendingDLLModuleList->clear(); // clear
}
