
// CRHM_GUI.cpp : Defines the class behaviors for the application.
//

#include "../stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CRHM_GUI.h"
#include "MainFrm.h"

#include "CRHM_GUIDoc.h"
#include "CRHM_GUIView.h"
#include "CTChart.h"
#include "CRHMmainDlg.h"
#include "CWebBrowser.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCRHMGUIApp

BEGIN_MESSAGE_MAP(CCRHMGUIApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CCRHMGUIApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	
	
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CCRHMGUIApp construction

CCRHMGUIApp::CCRHMGUIApp()
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CRHMGUI.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CCRHMGUIApp object

CCRHMGUIApp theApp;


// CCRHMGUIApp initialization

BOOL CCRHMGUIApp::InitInstance()
{
	try
	{
		// InitCommonControlsEx() is required on Windows XP if an application
		// manifest specifies use of ComCtl32.dll version 6 or later to enable
		// visual styles.  Otherwise, any window creation will fail.
		INITCOMMONCONTROLSEX InitCtrls;
		InitCtrls.dwSize = sizeof(InitCtrls);
		// Set this to include all the common control classes you want to use
		// in your application.
		InitCtrls.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&InitCtrls);

		CWinAppEx::InitInstance();

		// Initialize OLE libraries
		if (!AfxOleInit())
		{
			AfxMessageBox(IDP_OLE_INIT_FAILED);
			return FALSE;
		}

		AfxEnableControlContainer();

		EnableTaskbarInteraction(TRUE);

		// AfxInitRichEdit2() is required to use RichEdit control
		// AfxInitRichEdit2();

		// Standard initialization
		// If you are not using these features and wish to reduce the size
		// of your final executable, you should remove from the following
		// the specific initialization routines you do not need
		// Change the registry key under which our settings are stored
		// TODO: You should modify this string to be something appropriate
		// such as the name of your company or organization
		SetRegistryKey(_T("Local AppWizard-Generated Applications"));
		LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

		InitKeyboardManager();

		InitTooltipManager();
		CMFCToolTipInfo ttParams;
		ttParams.m_bVislManagerTheme = TRUE;
		theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
			RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

		// Register the application's document templates.  Document templates
		//  serve as the connection between documents, frame windows and views
		CSingleDocTemplate* pDocTemplate;
		pDocTemplate = new CSingleDocTemplate(
			IDR_MAINFRAME,
			RUNTIME_CLASS(CCRHMGUIDoc),
			RUNTIME_CLASS(CMainFrame),       // main SDI frame window
			RUNTIME_CLASS(CCRHMGUIView));
		if (!pDocTemplate)
			return FALSE;
		AddDocTemplate(pDocTemplate);


		CString commandText = GetCommandLine();
		std::string commandString = CT2A(commandText.GetString());
		char* cmdLine = new char[commandString.length() + 1];
		strcpy(cmdLine, commandString.c_str());
		
		static int numberOfArgs = __argc;
		int argc = 0;
		char ** argv;

		argv = (char**) malloc(sizeof(char*) * numberOfArgs);

		char * pos = strtok(cmdLine, " ");
		while (pos != NULL)
		{
			argv[argc] = pos;
			pos = strtok(NULL, " ");
			argc++;
		}

		CRHMArguments* args = new CRHMArguments();

		if (argc > 1)
		{
			EnablePrintfAtMFC();
			args->readCommandLine(argc, argv);
			args->validate();
		}

		delete[] cmdLine;
		free(argv);
	
		if (args->get_project_name() != "")
		{
			CRHMmain* model = new CRHMmain(args);
			std::string projectArgument = args->get_project_name();
			model->OpenNamePrj = projectArgument;
			model->DoPrjOpen(projectArgument, "");
			model->RunClick();
			delete model;
		}
		else
		{
			CRHMmainDlg dlgOptions; 
			dlgOptions.DoModal();
		}

		delete args;

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}


void CCRHMGUIApp::EnablePrintfAtMFC()
{
	if (AttachConsole(ATTACH_PARENT_PROCESS))
	{
		FILE* pCout;
		freopen_s(&pCout, "CONOUT$", "w", stdout);
		std::cout.clear();
		std::wcout.clear();
	}
}


int CCRHMGUIApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CCRHMGUIApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:

public:
	CButton ok;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, ok);	
}



// App command to run the dialog
void CCRHMGUIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCRHMGUIApp customization load/save methods

void CCRHMGUIApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CCRHMGUIApp::LoadCustomState()
{
}

void CCRHMGUIApp::SaveCustomState()
{
}

// CCRHMGUIApp message handlers






