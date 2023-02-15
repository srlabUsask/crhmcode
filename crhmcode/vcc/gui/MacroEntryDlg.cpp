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
#include "MacroEntryDlg.h"

IMPLEMENT_DYNAMIC(MacroEntryDlg, CDialogEx)

void MacroEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_MACRO_EDIT_BOX, macroEditBox);
}


BEGIN_MESSAGE_MAP(MacroEntryDlg, CDialogEx)
	//Buttons
	ON_BN_CLICKED(ID_MACRO_SAVE, &MacroEntryDlg::OnMacroSaveChanges)
	ON_BN_CLICKED(ID_MACRO_CANCEL, &MacroEntryDlg::OnMacroCancelChanges)
	//Menu Items
	ON_COMMAND(ID_MACRO_FILE_OPEN, &MacroEntryDlg::OnMacroFileOpen)
	ON_COMMAND(ID_MACRO_FILE_SAVE, &MacroEntryDlg::OnMacroFileSave)
	ON_COMMAND(ID_MACRO_FILE_SAVE_AS, &MacroEntryDlg::OnMacroFileSaveAs)
	ON_COMMAND(ID_MACRO_FILE_CREATE_GROUP, &MacroEntryDlg::OnMacroFileCreateGroup)
	ON_COMMAND(ID_MACRO_FILE_CLEAR, &MacroEntryDlg::OnMacroFileClear)
	ON_COMMAND(ID_MACRO_FILE_EXIT, &MacroEntryDlg::OnMacroFileExit)
END_MESSAGE_MAP()


MacroEntryDlg::MacroEntryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(MacroEntry_DLG, pParent)
{
}

MacroEntryDlg::~MacroEntryDlg()
{
}

BOOL MacroEntryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString newline("\r\n");
	CString cstr("");
	macroEditBox.SetWindowText(cstr);

	for (size_t ii = 0; ii < Global::MacroModulesList->size(); ++ii)
	{
		CString cstr1(Global::MacroModulesList->at(ii).c_str());
		cstr += cstr1 + newline;
	}
	macroEditBox.SetWindowText(cstr);

	ParaList = NULL;
	AKAList = NULL;

	GlobalModule.GrpCnt = 0;
	GlobalModule.StructCnt = 0;

	return TRUE;
}


void MacroEntryDlg::OnMacroSaveChanges()
{
	std::vector<std::string>* Lines = new std::vector<std::string>();
	Lines = GetLinesFromEditBox();
	Global::MacroModulesList->clear();

	for (size_t ii = 0; ii < Lines->size(); ++ii)
	{
		string S;
		if (Lines->at(ii).length() == 0)
		{
			S = " ";
		}
		else
		{
			S = Common::trimright(Lines->at(ii));
		}
		Global::MacroModulesList->push_back(S);
	}

	this->OnOK();
}


void MacroEntryDlg::OnMacroCancelChanges()
{
	this->OnCancel();
}


void MacroEntryDlg::OnMacroFileOpen()
{
	FileDialog * openfile = new FileDialog();
	bool opened = openfile->Open("mcr");

	if (opened) 
	{ 
		std::string filepath = openfile->filepath;
		std::vector<std::string>* slist = new std::vector<std::string>();

		/*Load vector from file.*/
		ifstream infile(filepath.c_str());
		string line;
		while (std::getline(infile, line))
		{
			slist->push_back(line);
		}

		macroEditBox.SetWindowText(_T(""));
		AddStringsToEditBox(slist);

		this->macrofile = openfile;

	}
}


void MacroEntryDlg::OnMacroFileSave()
{
	
	if (macrofile != NULL)
	{
		if (macrofile->filepath.length() > 0)
		{
			DoSave();
		}
		else
		{
			SaveAsClick();
		}
	}
	else
	{
		SaveAsClick();
	}

}


void MacroEntryDlg::OnMacroFileSaveAs()
{
	SaveAsClick();
}


void MacroEntryDlg::OnMacroFileCreateGroup()
{
	CreateGroupClick();
}


void MacroEntryDlg::OnMacroFileClear()
{
	macroEditBox.SetSel(0, -1);
	macroEditBox.Clear();
	macroEditBox.RedrawWindow();
}


void MacroEntryDlg::OnMacroFileExit()
{
	this->OnCancel();
}


void MacroEntryDlg::DoSave()
{
	std::vector<std::string>* Lines = new std::vector<std::string>();
	int start;
	int end;

	macroEditBox.GetSel(start, end);

	if (start == end)
	{
		Lines = GetLinesFromEditBox();

		ofstream file;
		file.open(macrofile->filepath.c_str());

		for (size_t it = 0; it < Lines->size(); it++)
		{
			file << Lines->at(it).c_str() << endl;
		}

		file.close();

	}
	else
	{
		Lines = GetSelectedLinesFromEditBox();

		ofstream file;
		file.open(macrofile->filepath.c_str());

		for (size_t it = 0; it < Lines->size(); it++)
		{
			file << Lines->at(it).c_str() << endl;
		}

		file.close();
	}

}


void MacroEntryDlg::SaveAsClick()
{
	macrofile = new FileDialog();
	bool opened = macrofile->Save("mcr");

	if (opened)
	{
		DoSave();
	}
}


void MacroEntryDlg::AddStringsToEditBox(std::vector<std::string> * tstr)
{
	CString cstr1;
	macroEditBox.GetWindowText(cstr1);
	CString newline("\r\n");

	CString cstr2, cstr;
	for (size_t i = 0; i < tstr->size(); i++)
	{
		cstr = tstr->at(i).c_str();
		if (tstr->at(i).length() != 0)
		{
			cstr2 += cstr + newline;
		}
	}

	CString finalcstr;


	//Getting rid of extra new lines in the macro box. Manishankar

	if (cstr1.GetLength() > 0)
	{
		finalcstr = cstr1 + newline + cstr2;
	}
	else
	{
		finalcstr = cstr2;
	}
	
	macroEditBox.SetWindowTextW(finalcstr);
}


void MacroEntryDlg::AddStringsToEditBox(string tstr)
{
	CString cstr1;
	macroEditBox.GetWindowText(cstr1);
	CString newline("\r\n");

	CString cstr2 (tstr.c_str());
	CString finalcstr;


	//Getting rid of extra new lines in the macro box. Manishankar

	if (cstr1.GetLength() > 0)
	{
		finalcstr = cstr1 + newline + cstr2;
	}
	else
	{
		finalcstr = cstr2;
	}

	//finalcstr = cstr1 + newline + cstr2;
	macroEditBox.SetWindowTextW(finalcstr);
}


std::vector<std::string> * MacroEntryDlg::GetLinesFromEditBox()
{
	std::vector<std::string> * tstring = new std::vector<std::string> ();

	CString cstr1;
	macroEditBox.GetWindowText(cstr1);
	string str = CT2A(cstr1);

	int l = str.length();
	string temp = "";

	for (int i = 0; i < l; i++)
	{
		if (str[i] != '\r' && str[i] != '\n') { temp += str[i]; }
		else 
		{  
			if (temp.length() > 0) 
			{ 
				tstring->push_back(temp); 
				temp = ""; 
			}
		}
	}
	if (temp.length() > 0) 
	{ 
		tstring->push_back(temp); 
	}

	return tstring;
}


std::vector<std::string> * MacroEntryDlg::GetSelectedLinesFromEditBox()
{
	std::vector<std::string> * tstring = new std::vector<std::string>();

	CString cstr1;
	macroEditBox.GetWindowText(cstr1);
	//string str = CT2A(cstr1);

	int start, end;
	CString cstr2;
	macroEditBox.GetSel(start, end);
	cstr2 = cstr1.Mid(start, end - start);
	string str = CT2A(cstr2);


	int l = str.length();
	string temp = "";

	for (int i = 0; i < l; i++)
	{
		if (str[i] != '\r' && str[i] != '\n') { temp += str[i]; }
		else
		{
			if (temp.length() > 0)
			{
				tstring->push_back(temp); 
				temp = "";
			}
		}
	}
	if (temp.length() > 0) 
	{ 
		tstring->push_back(temp); 
	}

	return tstring;
}


void MacroEntryDlg::CreateGroupClick()
{
	std::string Txt;
	std::string S; 
	std::string MacroName;
	std::string GrpName;
	size_t Indx;

	FileDialog * openfile = new FileDialog();
	bool opened = openfile->Open("prj");

	if (opened == false) 
	{ 
		return; 
	}

	MacroName = openfile->filename;
	Indx = MacroName.rfind("\\");

	// handle directories
	if (Indx != std::string::npos) 
	{
		MacroName = MacroName.substr(Indx + 1, MacroName.length());
	}

	// handle extensions
	Indx = MacroName.rfind(".");
	if (Indx != std::string::npos) 
	{ 
		std::string AA;
		GlobalModule.GrpCnt++;
		Common::GroupEnding(AA, GlobalModule.GrpCnt);
		MacroName = MacroName.substr(0, Indx) + "_Grp" + AA;
	}

	// must be a proper variable name
	if (!isalpha(MacroName[0])) 
	{ 
		MessageBox(_T("Alpha characters are upper-/lowercase characters from A through Z. Project file name must begin with an alpha character."), MB_OK);
		return;
	}
	
	GrpName = MacroName;
	
	if (GlobalModule.GrpCnt > 1)
	{
	//	GlobalModule.GrpCnt = 1;
	}

	std::vector<std::string> * ProjectFile = new std::vector<std::string>(); // hold project file
	ModuleList = new std::vector<std::string>();  // list of modules in group
	MacroList = new std::vector<std::pair<std::string, Module *>>();   // macros in project file
	DefinedList = new std::vector<std::pair<std::string, Module *>>(); // macros already defined

	if (!ParaList) 
	{
		ParaList = new std::vector<std::string>; // macros already defined
		ParaList->push_back("Parameters for created Group Macro");
		ParaList->push_back("#####");
	}

	if (!AKAList) { AKAList = new std::vector<std::string>(); } // macros already defined

	/*load the project file into a vector line by line.*/
	ifstream infile(openfile->filepath.c_str());
	string line;
	while (std::getline(infile, line))
	{
		ProjectFile->push_back(line);
	}

	size_t ThisEnd = 0;
	Module *ThisModule;

	std::vector<std::string> * Lines = new std::vector<std::string>();
	Lines = GetLinesFromEditBox();

	while (ThisEnd < Lines->size())
	{
		if (Lines->at(ThisEnd).length() == 0)
		{
			continue;
		}
		while (ThisEnd < Lines->size() && (Txt = Common::trimleft(Lines->at(ThisEnd)),
			Txt[0] == '/'))
		{
			++ThisEnd;
		}

		Indx = Txt.find(" ");
		if (Indx)
		{
			Txt = Txt.substr(0, Indx);
		}

		ThisModule = new Module;
		ThisModule->head = ThisEnd;
		do
			S = Common::trim(Lines->at(++ThisEnd));
		while (S[0] == '/');
		if (S.find("declgroup") != std::string::npos)
		{
			++ThisModule->GrpCnt;
			ThisModule->isGroup = true;
		}
		if (S.find("declstruct") != std::string::npos)
		{
			++ThisModule->StructCnt;
			ThisModule->isStruct = true;
		}
		while (ThisEnd < Lines->size() && !(S = Common::trim(Lines->at(ThisEnd)),
			S.substr(0, 3) == "end" && (S.length() == 3 || S[3] == ' ' || S[3] == '/')))
		{
			++ThisEnd;
		}
		ThisModule->tail = ThisEnd++;
		DefinedList->push_back(std::pair<std::string, Module *>(Txt, ThisModule));
	}

	for (size_t ii = 0; ii < ProjectFile->size(); ++ii)
	{
		Txt = ProjectFile->at(ii);
		if (Txt == "Dimensions:")
		{
			std::string numHRU = ProjectFile->at(ii + 2).substr(4, 10);
			Global::nhru = std::stoi(numHRU);

			if (Global::nhru > Global::maxhru)
			{
				Global::maxhru = Global::nhru;
			}

			std::string numLay = ProjectFile->at(ii + 3).substr(4, 10);
			Global::nlay = std::stoi(numLay);

			if (Global::nlay > Global::maxlay)
			{
				Global::maxlay = Global::nlay;
			}
		}
		if (Txt == "Parameters:")
		{
			++ii;
			++ii;
			while (ProjectFile->at(ii)[0] != '#')
			{
				if (ProjectFile->at(ii)[0] == '\'' || ProjectFile->at(ii)[0] == '-' || iswdigit(ProjectFile->at(ii)[0]))
					ParaList->push_back(ProjectFile->at(ii));
				else
				{
					Indx = ProjectFile->at(ii).find(" ");
					S = ProjectFile->at(ii).substr(Indx + 1, ProjectFile->at(ii).length() - Indx-1);
					ParaList->push_back(GrpName + " " + S);
				}
				++ii;
			}
			continue;
		}
		if (Txt == "Macros:")
		{
			++ii;
			++ii;
			ThisModule = NULL;
			while (ProjectFile->at(ii)[0] != '#')
			{

				while (ii < ProjectFile->size() && (S = Common::trimleft(ProjectFile->at(ii)), S[0] == '/'))
					++ii;
				S = S.substr(0, S.length() - 2);
				if (!ThisModule)
				{
					if (Indx = S.find(" "))
						S = S.substr(0, Indx);
					ThisModule = new Module;
					ThisModule->head = MacroList->size();
					MacroList->push_back(std::pair<std::string, Module *>(S, NULL));
				}
				else
				{
					if (S.find("declgroup"))
					{
						++ThisModule->GrpCnt;
						ThisModule->isGroup = true;
					}
					if (S.find("declstruct"))
					{
						++ThisModule->StructCnt;
						ThisModule->isStruct = true;
					}
					MacroList->push_back(std::pair<std::string, Module *>(S, NULL));
					if (S.substr(0, 3) == "end" && (S.length() == 3 || S[3] == ' ' || S[3] == '/'))
					{
						ThisModule->tail = MacroList->size();
						MacroList->at(ThisModule->head).second = ThisModule;
						ThisModule = NULL;
					}
				}
				++ii;
			}
			continue;
		}
	}
	for (size_t ii = 0; ii < ProjectFile->size(); ++ii)
	{
		Txt = ProjectFile->at(ii);
		if (Txt == "AKAs:")
		{
			++ii;
			++ii;
			while (ProjectFile->at(ii)[0] != '#')
			{
				string S = Common::trim(ProjectFile->at(ii));
				int Indx = S.find(" ");
				string type = S.substr(0, Indx);
				S = S.substr(Indx + 1, S.length() - Indx-1);
				Indx = S.find(" ");
				string module = S.substr(0, Indx);
				S = S.substr(Indx + 1, S.length() - Indx-1);
				Indx = S.find(" ");
				string name = S.substr(0, Indx);
				S = S.substr(Indx + 1, S.length() - Indx-1);
				string alias;
				Indx = S.find(" ");
				if (Indx == -1)
				{
					alias = S;
					ParaList->push_back(type + " " + GrpName + " " + name + " " + alias);
				}
				else
				{
					alias = S.substr(0, Indx);
					string source = S.substr(Indx + 1, S.length() - Indx-1);
					
					bool sourceInMacroList = false;
					for (size_t it = 0; it < MacroList->size(); it++)
					{
						if (MacroList->at(it).first == source)
						{
							sourceInMacroList = true;
							break;
						}
					}
					
					if (sourceInMacroList)
					{
						AKAList->push_back(type + " " + GrpName + " " + name + " " + alias + " " + source);
					}
					else
					{
						AKAList->push_back(type + " " + GrpName + " " + name + " " + alias + " " + GrpName);
					}
				}
				++ii;
			}
		}
		if (Txt == "Modules:")
		{
			++ii;
			++ii;

			int indxOfS = -1;
			for (size_t it = 0; it < DefinedList->size(); it++)
			{
				if (DefinedList->at(it).first == S)
				{
					indxOfS = it;
					break;
				}
			}

			while (indxOfS > -1)
			{
				++S[S.length()-1];

				indxOfS = -1;
				for (size_t it = 0; it < DefinedList->size(); it++)
				{
					if (DefinedList->at(it).first == S)
					{
						indxOfS = it;
						break;
					}
				}
			}
			ModuleList->push_back(GrpName);
			ModuleList->push_back("declgroup " + to_string(Global::nhru));
			while (ProjectFile->at(ii)[0] != '#')
			{
				S = Common::trim(ProjectFile->at(ii));
				if (S.find("+") > -1)
				{
					++ii;
					continue;
				}
				if (S.find(" "))
					S = S.substr(0, S.find(" "));
				ModuleList->push_back(S);
				++ii;
			}
			ModuleList->push_back("command");
			ModuleList->push_back("end");
			break;
		}
	}

	ProjectFile->clear();
	int EndList = (int) ModuleList->size() - 2;
	for (int ii = 2; ii < EndList; ++ii)
	{
		AddGroup(ii);
	}
	
	AddStringsToEditBox(ModuleList);

	delete ProjectFile;
	delete ModuleList;
	for (size_t ii = 0; ii < MacroList->size(); ++ii)
	{
		delete MacroList->at(ii).second;
	}
	delete MacroList;
	
	for (size_t ii = 0; ii < DefinedList->size(); ++ii)
	{
		delete DefinedList->at(ii).second;
	}
	delete DefinedList;
}


void MacroEntryDlg::AddGroup(int ii)
{
	int Indx;

	bool foundInDefinedList = false;

	for (size_t it = 0; it < DefinedList->size(); it++)
	{
		if (DefinedList->at(it).first == ModuleList->at(ii))
		{
			foundInDefinedList = true;
			break;
		}
	}

	if (foundInDefinedList == false)
	{
		Indx = -1;
		for (size_t it = 0; it < MacroList->size(); it++)
		{
			if (MacroList->at(it).first == ModuleList->at(ii))
			{
				Indx = it;
				break;
			}
		}

		if (Indx > -1)
		{
			Module * ThisModule = MacroList->at(Indx).second;
			AddSupport(ThisModule);
			for (int jj = ThisModule->head; jj < ThisModule->tail; ++jj)
			{
				AddStringsToEditBox(MacroList->at(jj).first);
			}

			ThisModule->avail = true;
		}
	}
}


void MacroEntryDlg::AddSupport(Module* ThisModule)
{
	int Indx;
	for (int ii = ThisModule->head + 2; ii < ThisModule->tail - 2; ++ii)
	{
		bool foundInDefinedList = false;
		for (size_t it = 0; it < DefinedList->size(); it++)
		{
			if (DefinedList->at(it).first == MacroList->at(it).first)
			{
				foundInDefinedList = true;
				break;
			}
		}

		if (foundInDefinedList)
		{			
			return;
		}

		Indx = ii;

		if (MacroList->at(Indx).second != NULL)
		{
			Module* ThisModule = MacroList->at(Indx).second;
			if (ThisModule->avail)
			{
				continue;
			}
			if (ThisModule->isGroup || ThisModule->isStruct)
			{
				AddSupport(ThisModule);
				ThisModule->avail = true;
			}
			for (int jj = Indx; jj < ThisModule->tail; ++jj)
			{
				//Memo->Lines->Add(MacroList->Strings[jj]);
				AddStringsToEditBox(MacroList->at(jj).first);
			}
			ThisModule->avail = true;
		}
	}
}