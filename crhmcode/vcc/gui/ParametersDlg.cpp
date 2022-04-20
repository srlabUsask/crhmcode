// ParametersDlg.cpp : implementation file
//

#include "../stdafx.h"
#include "CRHM_GUI.h"
#include "ParametersDlg.h"
#include "afxdialogex.h"


// ParametersDlg dialog

IMPLEMENT_DYNAMIC(ParametersDlg, CDialog)

ParametersDlg::ParametersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(PARAMETERS_DLG, pParent)
{

}

ParametersDlg::~ParametersDlg()
{
}

void ParametersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PARAM_DLG_MODULES_LIST_BOX, this->modules_list_box);
	DDX_Control(pDX, ID_PARAM_DLG_PARAM_LIST_BOX, this->parameters_list_box);
}


BEGIN_MESSAGE_MAP(ParametersDlg, CDialog)
	ON_LBN_SELCHANGE(ID_PARAM_DLG_MODULES_LIST_BOX, &ParametersDlg::OnSelectModule)
END_MESSAGE_MAP()


BOOL ParametersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRHMmain * main = CRHMmain::getInstance();
	this->initalizeModulesListBox(main);
	

	return TRUE;
}

void ParametersDlg::OnSelectModule()
{
	CString selectedText;
	int selectedIndex = this->modules_list_box.GetCurSel();
	this->modules_list_box.GetText(selectedIndex, selectedText);

	CT2CA pszConvertedAnsiString(selectedText);
	std::string selectedString(pszConvertedAnsiString);

	this->parameters_list_box.ResetContent();

	if (selectedString == "Shared")
	{
		std::map<std::string, ClassPar*, Classless<std::string>>::iterator sharedIt = Global::SharedMapPars.begin();

		for (sharedIt; sharedIt != Global::SharedMapPars.end(); sharedIt++)
		{
			std::string trimedString = sharedIt->first.substr(7, std::string::npos);
			CString paramName(trimedString.c_str());
			this->parameters_list_box.AddString(paramName);
		}
	}
	else
	{
		CRHMmain* model = CRHMmain::getInstance();
		std::map<std::string, ClassModule*>* modulesMap = model->getAllmodules();

		std::map<std::string, ClassModule*>::iterator selectedModuleIt = modulesMap->find(selectedString);

		std::list<std::pair<std::string, ClassPar*>> parametersList = *selectedModuleIt->second->getParametersList();

		parametersList.sort(
			[](std::pair<std::string, ClassPar*> item_a, std::pair<std::string, ClassPar*> item_b)
			{
				std::string lower_a;
				for (std::string::iterator c = item_a.first.begin(); c != item_a.first.end(); c++)
				{
					lower_a.push_back(std::tolower(*c));
				}

				std::string lower_b;
				for (std::string::iterator c = item_b.first.begin(); c != item_b.first.end(); c++)
				{
					lower_b.push_back(std::tolower(*c));
				}

				return lower_a < lower_b;

			}
		);

		for (
			std::list<std::pair<std::string, ClassPar*>>::iterator it = parametersList.begin();
			it != parametersList.end();
			it++
			)
		{
			CString paramName(it->first.c_str());
			this->parameters_list_box.AddString(paramName);
		}
	}

}


void ParametersDlg::initalizeModulesListBox(CRHMmain* main)
{
	//Add the "Shared" module to the list box
	this->modules_list_box.AddString(L"Shared");

	//Get the list of used modules and copy into a seccond list for sorting.
	std::list<std::pair<std::string, ClassModule*>>* modules_list = main->getOurModules();
	std::list<std::pair<std::string, ClassModule*>> sorted_modules_list = *modules_list;

	// Sort the list of modules alphabeticaly ignoring case.
	sorted_modules_list.sort(
		[](std::pair<std::string, ClassModule*> item_a, std::pair<std::string, ClassModule*> item_b)
		{
			std::string lower_a;
			for (std::string::iterator c = item_a.first.begin(); c != item_a.first.end(); c++)
			{
				lower_a.push_back(std::tolower(*c));
			}

			std::string lower_b;
			for (std::string::iterator c = item_b.first.begin(); c != item_b.first.end(); c++)
			{
				lower_b.push_back(std::tolower(*c));
			}

			return lower_a < lower_b;

		}
	);

	// Place each of the modules into the list box
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator module_iterator = sorted_modules_list.begin();
		module_iterator != sorted_modules_list.end();
		module_iterator++
		)
	{
		CString module_name(module_iterator->first.c_str());
		this->modules_list_box.AddString(module_name);
	}
}