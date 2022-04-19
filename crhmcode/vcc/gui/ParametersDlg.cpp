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
	
	this->modules_list_box.AddString(L"Shared");
	std::list<std::pair<std::string, ClassModule*>> * modules_list = main->getOurModules();
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator module_iterator = modules_list->begin();
		module_iterator != modules_list->end();
		module_iterator++
		)
	{
		CString module_name(module_iterator->first.c_str());
		this->modules_list_box.AddString(module_name);
	}

	return TRUE;
}