#pragma once
#include <afxwin.h>
#include <string>

#include "../src/core/GlobalDll.h"
#include "../src/core/ClassMacro.h"
#include "resource.h"


class HierarchyDlg : public CDialog
{
	DECLARE_DYNAMIC(HierarchyDlg)

public:
	HierarchyDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~HierarchyDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_HIERARCHY_DLG};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CListBox hierarchyCheck;
	CListBox hierarchyList;

	BOOL OnInitDialog();

	void Hierarchy1Click();
	void HierarchyList();
	void Expand_Grp_to_OurModuleList(std::string moduleName, ClassModule* module);
	std::pair<std::string, ClassModule*> * findvar(std::string who, std::string what, bool& Self);
	std::pair<std::string, ClassModule*> * findstatvar(std::string who, std::string what, bool& Self);
};

