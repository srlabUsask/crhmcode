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
// CReport.cpp : implementation file
//

#include "../stdafx.h"
#include "CRHM_GUI.h"
#include "CReport.h"
#include "afxdialogex.h"
#include "MacroEntryDlg.h"
#include "../../src/core/CRHMmain.h"


// CReport dialog

IMPLEMENT_DYNAMIC(CReport, CDialog)

CReport::CReport(CWnd* pParent /*=nullptr*/)
	: CDialog(REPORT_DLG, pParent)
{

}

CReport::~CReport()
{
}

void CReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_GROUP_LIST, groupsListBox);
	DDX_Control(pDX, ID_EXTRACTED_GROUP_TEXT, extractedGroupText);
	DDX_Control(pDX, ID_STATIC_EXTRACT_TEXT, staticText);
}


BEGIN_MESSAGE_MAP(CReport, CDialog)
	ON_COMMAND(ID_EXTRACT_GROUP_SAVE, &CReport::OnSave)
	ON_COMMAND(ID_EXTRACT_GROUP_EXIT, &CReport::OnExit)
	ON_LBN_DBLCLK(ID_GROUP_LIST, &CReport::SelectGroup)
END_MESSAGE_MAP()



BOOL CReport::OnInitDialog()
{
	CDialog::OnInitDialog();

	ClassModule *thisMod;

	groupsListBox.ResetContent();
	extractedGroupText.SetWindowText(_T(""));
	staticText.SetWindowTextW(_T("Macros Used"));
	
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt != Global::OurModulesList->end(); 
		modIt++
		) 
	{
		string S = modIt->first;
		std::map<std::string, ClassModule*>::iterator pos = Global::AllModulesList->find(S);
		thisMod = pos->second;
		if (thisMod->isGroup)
		{
			CString cstr(S.c_str());
			groupsListBox.AddString(cstr);
		}
	} 

	return true;

}


void CReport::SelectGroup()
{
	//getting the group name.
	CString cstr;
	int index = groupsListBox.GetCurSel();
	groupsListBox.GetText(index, cstr);
	CT2A str(cstr);
	string groupname = str;

	//getting the group object and class module.
	ClassModule *thisMod;
	std::map<std::string, ClassModule*>::iterator pos = Global::AllModulesList->find(groupname);
	thisMod = pos->second;

	ExtractGroupFile(thisMod);

}

void CReport::ExtractGroupFile(ClassModule *thisModule) 
{

	CString newline("\r\n");
	CString cstr("");
	//editbox.SetWindowText(cstr);

	ClassMacro *thisMacro;
	string S, SS;
	//long Variation; varible is unreferenced commenting out for now - jhs507
	MapPar::iterator itPar;
	ClassPar *thisPar;

	if (thisModule->isGroup)
		thisMacro = dynamic_cast<ClassMacro *> (thisModule);
	else
		return;

	extractedGroupText.SetWindowTextW(_T(""));
	
	std::vector<std::string> * stringlist;
	stringlist = new std::vector<std::string>();
	
	
	CRHMmain * model = CRHMmain::getInstance();
	
	S = thisMacro->Name.c_str();
	
	stringlist->push_back("*** extracted group: '" + S + "' from '" + model->OpenProjectPath + "' ***");
	
	stringlist->push_back("######");
	stringlist->push_back("Dimensions:");
	stringlist->push_back("######");
	stringlist->push_back(string("nhru " + Common::longtoStr(Add_NHRU(S, Global::MacroModulesList))));
	stringlist->push_back(string("nlay " + Common::longtoStr(Global::nlay)));
	stringlist->push_back(string("nobs " + Common::longtoStr(1)));
	stringlist->push_back("######");

	stringlist->push_back("Macros:");
	stringlist->push_back("######");

	long MacroPos = stringlist->size();
	stringlist->push_back("######");

	stringlist->push_back("Modules:");
	stringlist->push_back("######");

	list<ModulePtr> ::iterator iterM;
	iterM = ((ClassMacro *)thisModule)->Modules.begin();
	while (iterM != ((ClassMacro *)thisModule)->Modules.end()) {
		std::weak_ptr<ClassModule> MP((*iterM));
		S = (*iterM)->NameRoot.c_str();

		if ((*iterM)->DLLName == "Macro")
		{
			AddMacroCode(S, Global::MacroModulesList, stringlist, MacroPos);
		}
			

		if ((*iterM)->variation > 0) {
			string AA("#0 ");
			AA[1] += (char) (log((*iterM)->variation) / log(2) + 1);
			S = S + AA.c_str();
		}
		else
			S = S + " ";

		S = S + (*iterM)->DLLName + " ";
		S = S + (*iterM)->Version;
		stringlist->push_back(S);
		++iterM;
	} // while

	stringlist->push_back("######");

	//model->RemoveSharedParams();

	stringlist->push_back("Parameters:");
	stringlist->push_back("######");

	S = thisMacro->Name.c_str();

	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) 
	{
		thisPar = (*itPar).second;
		if (S == thisPar->module.c_str() || thisPar->module == "Shared")
		{
			if (thisPar->param == "HRU_group")
			{
				continue;
			}

			string S = string("Shared " + string(thisPar->param.c_str()));

			if (thisPar->varType != TVar::Txt)
			{
				S += "\t<\t" + FloatToStrF(thisPar->minVal, TFloatFormat::ffGeneral, 4, 0) + "\t" + FloatToStrF(thisPar->maxVal, TFloatFormat::ffGeneral, 4, 0) + "\t>";
			}

			stringlist->push_back(S);

			for (size_t jj = 0;  jj < (size_t) thisPar->lay; jj++) 
			{
				S = "";
				for (int ii = 0; ii < thisPar->dim; ii++) {
					if (thisPar->varType == TVar::Float)
						S = S + FloatToStrF(thisPar->layvalues[jj][ii], TFloatFormat::ffGeneral, 4, 0) + "\t";
					else if (thisPar->varType == TVar::Int)
						S = S + FloatToStrF(thisPar->ilayvalues[jj][ii], TFloatFormat::ffFixed, 8, 0) + "\t";
					else if (thisPar->varType == TVar::Txt)
						if (thisPar->Strings->size() > (size_t) ii)
							S = S + "'" + thisPar->Strings->at(ii) + "'\t";
						else
							S = "''\t"; // handle null string

					if (ii % 16 == 15) {
						stringlist->push_back(S);
						S = "";
					}
				} // for dim
				if (S.length() > 0) { stringlist->push_back(S); S = ""; }
			} // for layers
			if (S.length() > 0) stringlist->push_back(S);
		}
	} // for MapPars

	stringlist->push_back("######");

	CString cstrtemp, text;
	for (size_t i = 0; i < stringlist->size(); i++)
	{
		string strtemp = stringlist->at(i);
		cstrtemp = strtemp.c_str();
		
		text += newline + cstrtemp;
	}

	extractedGroupText.SetWindowTextW(text);

	//Main->SqueezeParams(Sender);  // converts identical parameters to shared parameters
}

long CReport::Add_NHRU(string S, std::vector<std::string> * MacroModulesList) {

	for (size_t ii = 0; ii < MacroModulesList->size(); ++ii) {
		int found = MacroModulesList->at(ii).find(S);
		if (found >= 0) {
			string Trim = Common::trimleft(MacroModulesList->at(++ii));
			long len = Trim.length();
			if (len < 11)
				return Global::nhru;
			else {
				string temp = Trim.substr(10, len - 10);
				CString ctemp(temp.c_str());
				long n = StrToInt(ctemp);
				if (n <= 0)
					return Global::nhru;
				else
					return n;
			}
		}
	}
	return 0; //added fall through case if the module is not found - jhs507
}

void CReport::AddMacroCode(string S, std::vector<std::string> * MacroModulesList, std::vector<std::string> * Memo1, long &MacroPos) {

	int endpos=0;

	for (size_t ii = 0; ii < MacroModulesList->size(); ++ii) {
		int found = MacroModulesList->at(ii).find(S);
		if (found >= 0) {
			Memo1->push_back("'" + MacroModulesList->at(ii) + "'");
			MacroPos++;
			do {
				++ii;
				Memo1->push_back("'" + MacroModulesList->at(ii) + "'");
				MacroPos++;

				endpos = MacroModulesList->at(ii).find("end");
			} while (!(endpos >= 0 && MacroModulesList->at(ii).length() == 3) && ii < MacroModulesList->size() - 1);
			break;
		}
	}
}


void CReport::OnSave()
{
	// TODO: Add your command handler code here

	//if (!SaveDialog1->FileName.IsEmpty())
	//	Memo1->Lines->SaveToFile(SaveDialog1->FileName);
	//else SaveAs1Click(Sender);

	CString cstr;
	extractedGroupText.GetWindowText(cstr);
	CT2A str(cstr);
	std::vector<std::string> * strings = new std::vector<std::string>();
	string temp = str;	

	int l = temp.length();
	for (int i = 0; i < l; i++)
	{
		if (i < l - 1)
		{
			if (temp[i] == '\r') { temp[i] = ' '; }
		}
	}

	strings->push_back(temp);


	FileDialog * filedialog;
	filedialog = new FileDialog();
	if (filedialog->Save("prj") == true)
	{
		ofstream file;
		file.open(filedialog->filepath.c_str());

		for (size_t it = 0; it < strings->size(); it++)
		{
			file << strings->at(it).c_str() << endl;
		}

		file.close();

		MessageBox(_T("Group Saved"));
	}
}

void CReport::OnExit()
{
	this->OnCancel();
}


