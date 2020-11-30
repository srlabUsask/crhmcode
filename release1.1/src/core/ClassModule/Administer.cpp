#include "Administer.h"

//---------------------------------------------------------------------------
Administer::Administer(string Version, string _HelpFile) : Version(Version), HelpFile(_HelpFile) {

	DLLModuleList = new TStringList;
	DLLModelList = new TStringList;
	DLLModelModuleList = new TStringList;

	if (Global::PendingDLLModuleList != NULL)
		Global::PendingDLLModuleList->Clear(); // clear
}

//---------------------------------------------------------------------------
Administer::~Administer() {

	for (int ii = 0; ii < DLLModuleList->Count; ++ii)
		delete ((ClassModule*)DLLModuleList->array[ii].Object); // delete modules

	delete DLLModuleList;
	delete DLLModelList;
	delete DLLModelModuleList;
}

//---------------------------------------------------------------------------
void Administer::MacroClear() {

	for (int ii = 0; ii < DLLModuleList->Count; ++ii) {

		/*int jj = Global::AllModulesList->IndexOf(DLLModuleList->strings[ii]);
		if (jj > -1)
		Global::AllModulesList->Delete(jj);*/

		ClassModule* thisModule = (ClassModule*)DLLModuleList->array[ii].Object;
		delete thisModule;
	}

	if (Global::OurHelpList) {
		int indx = Global::OurHelpList->IndexOf(HelpFile);
		if (indx > -1) // delete Macro help file.
			Global::OurHelpList->Delete(indx);
	}

	DLLModuleList->Clear();
	DLLModelList->Clear();
	DLLModelModuleList->Clear();
}

//---------------------------------------------------------------------------
void Administer::MacroUpdate() {
	for (int ii = 0; ii < DLLModuleList->Count; ++ii) {
		int jj = Global::OurModulesList->IndexOf(DLLModuleList->Strings[ii]);

		if (jj > -1) // Update Macro Module address
			Global::OurModulesList->Objects[jj] = DLLModuleList->Objects[ii];
	}
}

//---------------------------------------------------------------------------
void Administer::AddModule(ClassModule* Module) {

	Module->OurAdmin = this;
	DLLModuleList->AddObject((Module)->Name.c_str(), (TObject*)Module);
	Global::PendingDLLModuleList->AddObject((Module)->Name.c_str(), (TObject*)Module);
}

//---------------------------------------------------------------------------
void Administer::AddModel(string ModelName, string ModelModules) {

	DLLModelModuleList->Add(ModelModules);
	//DLLModelList->AddObject(ModelName, (TObject*)(DLLModelModuleList->Count - 1)); // removed this line and added the following two for resolving a warning.
	long _object = DLLModelModuleList->Count - 1;
	DLLModelList->AddObject(ModelName, (TObject*)_object);
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

	for (int ii = 0; ii < DLLModuleList->Count; ++ii) { // All modules in DLL

		if (Global::PendingDLLModuleList->Count > 0  // Do not load unless requested.  Count == 0 means all!
			&& Global::PendingDLLModuleList->IndexOf(DLLModuleList->Strings[ii]) == -1)
			continue;

		int jj = Global::AllModulesList->IndexOf(DLLModuleList->Strings[ii]);
		if (jj != -1) {
			Exists = "Over-write existing module \"";
			//      MsgDlgType = mtWarning;
		}
		else {
			Exists = "Load Module \"";
			//      MsgDlgType = mtInformation;
		}

		if (Global::AllModulesList->IndexOf(DLLModuleList->Strings[ii]) == -1 // Needed to be put back!
			&& Global::OurModulesList->IndexOf(DLLModuleList->Strings[ii]) != -1)
			Result = mbYes;
		//    else if(Result != mbYesToAll && Result != mbNoToAll){ // optional
		//      Result = MessageDlg(Exists + DLLModuleList->Strings[ii] + "\" ?",
		//      MsgDlgType,
		//      TMsgDlgButtons() << mbYes << mbNo << mbYesToAll << mbNoToAll, 0);
		//      }

		switch (Result) {
		case mbYes:
		case mbYesToAll:
			if (jj != -1) {
				LogError(CRHMException((DLLModuleList->Strings[ii] + " module being replaced").c_str(), TExcept::WARNING));
				Global::AllModulesList->Delete(jj);
			}

			thisModule = (ClassModule*)DLLModuleList->Objects[ii];
			thisModule->DLLName = DLLName;
			if (thisModule->DLLName != "Macro")
				thisModule->ID = typeid(*thisModule).name();

			Global::AllModulesList->AddObject(DLLModuleList->Strings[ii],
				(TObject*)DLLModuleList->Objects[ii]);
			break;

		case mbNo:
		case mbNoToAll:
			continue;
		default:
			break;
		}
	}

	for (int ii = 0; ii < DLLModelList->Count; ++ii) {

		// when sorted index used to access ModelModulesList		
		long _object = ii;
		Global::AllModelsList->AddObject(DLLModelList->Strings[ii], (TObject*)_object);

		// Administer object used to find which DLL loaded model
		Global::ModelModulesList->AddObject(DLLModelModuleList->Strings[ii], (TObject*)this);
	}

	if (Global::OurHelpList)
	{
		if (Global::OurHelpList->IndexOf(HelpFile) < 0)  // No duplicates
		{
			Global::OurHelpList->AddObject(HelpFile, (TObject*)1);
		}
		else
		{
			Global::OurHelpList->AddObject(HelpFile, (TObject*)0);
		}
	}

	Global::PendingDLLModuleList->Clear(); // clear
}
