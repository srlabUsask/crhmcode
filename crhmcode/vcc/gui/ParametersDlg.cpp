// ParametersDlg.cpp : implementation file
//

#include "../stdafx.h"
#include "CRHM_GUI.h"
#include "ParametersDlg.h"
#include "afxdialogex.h"


// ParametersDlg dialog

IMPLEMENT_DYNAMIC(ParametersDlg, CDialog)

ParametersDlg::ParametersDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(PARAMETERS_DLG, pParent)
{

}

ParametersDlg::~ParametersDlg()
{
}

void ParametersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(ParametersDlg, CDialog)
END_MESSAGE_MAP()


