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
}


BEGIN_MESSAGE_MAP(ParametersDlg, CDialog)
END_MESSAGE_MAP()


BOOL ParametersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRHMmain * main = CRHMmain::getInstance();
	this->initalizeModulesListBox(main);
	

	return TRUE;
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