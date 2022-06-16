#include "CRHMmainDlg.h"

//create a tracking variable for the current project file name
//a varaible with higher scope is used to avoid unnecessarilly confusing parameter passing - Matt
CString globFileName;

IMPLEMENT_DYNAMIC(CRHMmainDlg, CDialogEx)


CRHMmainDlg::CRHMmainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(CRHMmainDialog, pParent)
{
	CRHMmain* test = CRHMmain::getInstance();
	//test->FormCreate();
	this->openObsFiles = new std::map< UINT, std::pair<std::string, std::string>>();
}


CRHMmainDlg::~CRHMmainDlg()
{
}

CRHMmainDlg::CRHMmainDlg(string argumentfile)
{
	CRHMmain* test = CRHMmain::getInstance();
	test->FormCreate();
	this->openObsFiles = new std::map< UINT, std::pair<std::string, std::string>>();
}


void CRHMmainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_ALL_VAR_LIST_BOX, listbox_all_variables);
	listbox_all_variables.setMessageCode(UWM_OPEN_CTX_ALL_VAR);
	DDX_Control(pDX, ID_SEL_VAR_LIST_BOX, listbox_sel_variables);
	listbox_sel_variables.setMessageCode(UWM_OPEN_CTX_SEL_VAR);
	DDX_Control(pDX, ID_ALL_OBS_LIST_BOX, listbox_all_observations);
	listbox_all_observations.setMessageCode(UWM_OPEN_CTX_ALL_OBS);
	DDX_Control(pDX, ID_SEL_OBS_LIST_BOX, listbox_sel_observations);
	listbox_sel_observations.setMessageCode(UWM_OPEN_CTX_SEL_OBS);
	DDX_Control(pDX, IDC_TCHART1, tchart);
	DDX_Control(pDX, ID_START_DATE_PICKER, StartDatePicker);
	DDX_Control(pDX, ID_END_DATE_PICKER, EndDatePicker);
	DDX_Control(pDX, ID_FLIP_TICKS, FlipTicks);
	FlipTicks.setMessageCodeLeft(UWM_FLIP_TICKS_LEFT);
	FlipTicks.setMessageCodeRight(UWM_FLIP_TICKS_RIGHT);
	DDX_Control(pDX, ID_FUNCTION_DROP_DOWN, function_drop_down);
	DDX_Control(pDX, ID_TIMEBASE_DROP_DOWN, timebase_drop_down);
	DDX_Control(pDX, ID_WATER_YEAR_DROP_DOWN, water_year_drop_down);
}


BEGIN_MESSAGE_MAP(CRHMmainDlg, CDialogEx)
	//Project menu items
	ON_COMMAND(ID_FILE_OPEN, &CRHMmainDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CRHMmainDlg::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CRHMmainDlg::OnFileSaveAs)
	ON_COMMAND(ID_FILE_CLOSE, &CRHMmainDlg::OnFileClose)
	ON_COMMAND(ID_AUTO_RUN, &CRHMmainDlg::OnAutoRun)
	ON_COMMAND(ID_AUTO_EXIT, &CRHMmainDlg::OnAutoExit)
	ON_COMMAND(ID_MENU_EXIT, &CRHMmainDlg::OnExit)
	
	//Project->Log submenu
	ON_COMMAND(ID_MAIN_LOG_ALL, &CRHMmainDlg::OnLogAll)
	ON_COMMAND(ID_MAIN_LOG_LAST, &CRHMmainDlg::OnLogLast)

	//Project->Reports submenu
	ON_COMMAND(ID_EXTRACT_GROUP, &CRHMmainDlg::OnExtractGroup)
	ON_COMMAND(ID_VIEW_HIERARCHY, &CRHMmainDlg::OnViewHierarchy)

	//Observation menu items
	ON_COMMAND(ID_OPEN_OBS, &CRHMmainDlg::OnOpenObservation)
	ON_COMMAND_RANGE(ID_OPEN_OBS_FILE_FIRST, ID_OPEN_OBS_FILE_LAST, &CRHMmainDlg::OnClickOnOpenFile)
	ON_COMMAND(ID_CLOSE_ALL_OBS, &CRHMmainDlg::OnCloseAllObservations)
	
	//Build menu items
	ON_COMMAND(ID_BUILD_CONSTRUCT, &CRHMmainDlg::OnBuildConstruct)
	ON_COMMAND(ID_CLEAR_MODULES, &CRHMmainDlg::OnClearModules)
	ON_COMMAND(ID_BUILD_MACRO, &CRHMmainDlg::OnBuildMacro)
	
	//Parameters menu items
		//Parameter menu items are missing
	
	//State menu items
	ON_COMMAND(ID_STATE_OPEN_INIT_STATE, &CRHMmainDlg::OnClickOnOpenInitState)
	ON_COMMAND(ID_OPEN_INIT_FILE, &CRHMmainDlg::CloseOpenInitFile)
	ON_COMMAND(ID_STATE_SAVE_STATE, &CRHMmainDlg::OnSaveState)
	ON_COMMAND(ID_STATE_SAVE_TO, &CRHMmainDlg::OnSaveStateTo)
	ON_COMMAND(ID_STATE_SAVE_STATE_AS, &CRHMmainDlg::OnSaveStateAs)
	
	//Run menu items
	ON_COMMAND(ID_RUN_RUNMODEL, &CRHMmainDlg::OnRunRunmodel)
	
	//Export menu item 
	ON_COMMAND(ID_EXPORT, &CRHMmainDlg::OnExport)
	
	//Flow diagrams menu items
	ON_COMMAND(ID_FLOWDIAGRAMS_SHOWDIAGRAM, &CRHMmainDlg::OnFlowdiagramsShowdiagram)
	
	//Help menu item
		//CRHM Help not implemented
		//New Modules help not implemented
	ON_COMMAND(ID_HELP_ABOUT, &CRHMmainDlg::OnHelpAbout)

	//HRU Dimension Selector
	ON_BN_CLICKED(ID_HRU_DIM_DECREASE, &CRHMmainDlg::DecreaseHRUDimension)
	ON_BN_CLICKED(ID_HRU_DIM_INCREASE, &CRHMmainDlg::IncreaseHRUDimension)
	
	//OBS Dimension Selector
	ON_BN_CLICKED(ID_OBS_DIM_DECREASE, &CRHMmainDlg::DecreaseObsDimension)
	ON_BN_CLICKED(ID_OBS_DIM_INCREASE, &CRHMmainDlg::IncreaseObsDimension)
	
	//Variables list boxes
	ON_LBN_DBLCLK(ID_ALL_VAR_LIST_BOX, &CRHMmainDlg::OnDblClkAllVarListBox)
	ON_LBN_DBLCLK(ID_SEL_VAR_LIST_BOX, &CRHMmainDlg::OnDblClkSelVarListBox)
	ON_LBN_SELCHANGE(ID_ALL_VAR_LIST_BOX, &CRHMmainDlg::OnVariableSelectChange)
	ON_MESSAGE(UWM_OPEN_CTX_ALL_VAR, &CRHMmainDlg::OpenAllVarCtxMenu)
	ON_MESSAGE(UWM_OPEN_CTX_SEL_VAR, &CRHMmainDlg::OpenSelVarCtxMenu)
	
	//Observation list boxes
	ON_LBN_DBLCLK(ID_ALL_OBS_LIST_BOX, &CRHMmainDlg::OnDblClkAllObsListBox)
	ON_LBN_DBLCLK(ID_SEL_OBS_LIST_BOX, &CRHMmainDlg::OnDblClkSelObsListBox)
	ON_LBN_SELCHANGE(ID_ALL_OBS_LIST_BOX, &CRHMmainDlg::OnObservationSelectChange)
	ON_MESSAGE(UWM_OPEN_CTX_ALL_OBS, &CRHMmainDlg::OpenAllObsCtxMenu)
	ON_MESSAGE(UWM_OPEN_CTX_SEL_OBS, &CRHMmainDlg::OpenSelObsCtxMenu)

	//Function and Timebase drop down selectors
	ON_CBN_SELCHANGE(ID_TIMEBASE_DROP_DOWN, &CRHMmainDlg::OnTimebaseChange)
	ON_CBN_SELCHANGE(ID_WATER_YEAR_DROP_DOWN, &CRHMmainDlg::OnWaterYearChange)

	//Date Pickers
	ON_NOTIFY(DTN_DATETIMECHANGE, ID_START_DATE_PICKER, &CRHMmainDlg::OnStartDateChange)
	ON_NOTIFY(DTN_DATETIMECHANGE, ID_END_DATE_PICKER, &CRHMmainDlg::OnEndDateChange)

	//Flip ticks button
	ON_MESSAGE(UWM_FLIP_TICKS_LEFT, &CRHMmainDlg::OnLeftClickFlipTicks)
	ON_MESSAGE(UWM_FLIP_TICKS_RIGHT, &CRHMmainDlg::OnRightClickFlipTicks)

	ON_MESSAGE(UWM_AUTO_RUN, &CRHMmainDlg::OnAutoRunMessage)
END_MESSAGE_MAP()


BOOL CRHMmainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here

	//State the name of the program in the window title - Matt
	std::string str1 = "The Cold Regions Hydrological Model";
	CString cStr(str1.c_str());

	SetDlgItemText(ID_OBS_LAY_DIM_LABEL, L"OBS");
	SetDlgItemText(ID_HRU_DIM_DISPLAY, _T("1"));
	SetDlgItemText(ID_OBS_DIM_DISPLAY, _T("1"));
	SetDlgItemText(ID_OBS_HELP_DISPLAY, _T(""));
	SetDlgItemText(ID_VAR_HELP_DISPLAY, _T(""));
	CFont* varHelpFont = new CFont();
	varHelpFont->CreatePointFont(96, _T("Ariel"));
	GetDlgItem(ID_VAR_HELP_DISPLAY)->SetFont(varHelpFont);
	CFont* obsHelpFont = new CFont();
	obsHelpFont->CreatePointFont(96, _T("Ariel"));
	GetDlgItem(ID_OBS_HELP_DISPLAY)->SetFont(obsHelpFont);

	loadGuiComponents();

	delete varHelpFont;
	delete obsHelpFont;

	/** 
	* Set options for the function_drop_down
	*/
	function_drop_down.AddString(L"Observation");
	function_drop_down.AddString(L"Total");
	function_drop_down.AddString(L"Minimum");
	function_drop_down.AddString(L"Maximum");
	function_drop_down.AddString(L"Average");
	function_drop_down.SetCurSel(0);

	/**
	* Set options for the timebase_drop_down
	*/
	timebase_drop_down.AddString(L"Daily");
	timebase_drop_down.AddString(L"Monthly");
	timebase_drop_down.AddString(L"Calendar Year");
	timebase_drop_down.AddString(L"Water Year");
	timebase_drop_down.AddString(L"All");
	timebase_drop_down.SetCurSel(3);

	/**
	* Set options for the water_year_drop_down
	*/
	water_year_drop_down.AddString(L"January");
	water_year_drop_down.AddString(L"Febuary");
	water_year_drop_down.AddString(L"March");
	water_year_drop_down.AddString(L"April");
	water_year_drop_down.AddString(L"May");
	water_year_drop_down.AddString(L"June");
	water_year_drop_down.AddString(L"July");
	water_year_drop_down.AddString(L"August");
	water_year_drop_down.AddString(L"September");
	water_year_drop_down.AddString(L"October");
	water_year_drop_down.AddString(L"November");
	water_year_drop_down.AddString(L"December");
	water_year_drop_down.SetCurSel(9);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CRHMmainDlg::ProcessCommandLineArgument()
{
	CRHMmain *test = CRHMmain::getInstance();
	test->FormCreate();
	test->DoPrjOpen(ProjectFileArgument, "");
}


void CRHMmainDlg::loadGuiComponents()
{
	listbox_all_variables.ResetContent();
	listbox_sel_variables.ResetContent();
	listbox_all_observations.ResetContent();
	listbox_sel_observations.ResetContent();

	CRHMmain* crhm_core = CRHMmain::getInstance();

	std::map<std::string, ClassVar*>* variables = CRHMmain::getInstance()->getVariables();
	std::map<std::string, ClassVar*>::iterator it;
	for (it = variables->begin(); it != variables->end(); it++) 
	{

		//string s = variables->Strings[ii];


		std::string s = it->first;

		CString cvariables(s.c_str());

		/*if (s == "t0_inhibit##")
		{
			string s2 = "t0_inhibit#";
			CString cs2(s2.c_str());
			listbox_varaiables_all.AddString(cs2);
			continue;
		}*/
		if (s != "t")
		{
			listbox_all_variables.AddString(cvariables);
		}
	}


	std::map<std::string, ClassVar*>* observations = CRHMmain::getInstance()->getObservations();
	std::map<std::string, ClassVar*>::iterator observationIt;


	for (observationIt = observations->begin(); observationIt != observations->end(); observationIt++)
	{
		std::string s = observationIt->first;
		CString observations(s.c_str());
		listbox_all_observations.AddString(observations);
	}

	std::list<std::pair<std::string, ClassVar*>>* sel_variables = CRHMmain::getInstance()->getSelectedVariables();

	for (std::list<std::pair<std::string, ClassVar*>>::iterator it = sel_variables->begin();
		it != sel_variables->end();
		it++)
	{
		std::string s = it->first;
		CString observations(s.c_str());
		listbox_sel_variables.AddString(observations);
	}

	std::list<std::pair<std::string, TSeries*>>* sel_observations = CRHMmain::getInstance()->getSelectedObservations();

	for (
		std::list<std::pair<std::string, TSeries*>>::iterator it = sel_observations->begin();
		it != sel_observations->end();
		it++
		)
	{
		std::string s = it->first;
		CString observations(s.c_str());
		listbox_sel_observations.AddString(observations);
	}

	CRHMmain* main = CRHMmain::getInstance();
	SetTime(main->GetStartDate(), main->GetEndDate());

	if (main->getAutoRun())
	{
		CMenu* menu = GetMenu();
		menu->CheckMenuItem(ID_AUTO_RUN, MF_CHECKED);
	}
	else
	{
		CMenu* menu = GetMenu();
		menu->CheckMenuItem(ID_AUTO_RUN, MF_UNCHECKED);
	}

	if (main->getAutoExit())
	{
		CMenu* menu = GetMenu();
		menu->CheckMenuItem(ID_AUTO_EXIT, MF_CHECKED);
	}
	else
	{
		CMenu* menu = GetMenu();
		menu->CheckMenuItem(ID_AUTO_RUN, MF_UNCHECKED);
	}

	if (main->getReportAll())
	{
		CMenu* menu = GetMenu();
		menu->CheckMenuItem(ID_MAIN_LOG_ALL, MF_CHECKED);
		menu->CheckMenuItem(ID_MAIN_LOG_LAST, MF_UNCHECKED);
	}
	else
	{
		CMenu* menu = GetMenu();
		menu->CheckMenuItem(ID_MAIN_LOG_ALL, MF_UNCHECKED);
		menu->CheckMenuItem(ID_MAIN_LOG_LAST, MF_CHECKED);
	}

	if (crhm_core->getAutoRun())
	{
		ShowWindow(1);
		CenterWindow();
		UpdateWindow();
		PostMessage(UWM_AUTO_RUN, 0, 0);
	}

}


void CRHMmainDlg::InitModules()
{

	Global::BuildFlag = TBuild::DECL;

	Box1Disply = (int)TVISIBLE::OUTPUT;

	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt != Global::OurModulesList->end();
		modIt++
		)
	{
		modIt->second->nhru = Global::nhru;
		modIt->second->decl();
	}
	Global::CurrentModuleRun = Global::OurModulesList->rbegin()->first;

	GetAllVariables();
}

void CRHMmainDlg::GetAllVariables()
{
	CRHMmain* model = CRHMmain::getInstance();
	CConstruct* buildform = new CConstruct();

	ClassVar* thisVar;
	MapVar::iterator itVar;

	string Labels[] = { "Variables", "Variables by Module", "Diagnostic Variables", "Private Variables" };
	string Newname;

	++Box1Disply;
	if (Box1Disply > (int)TVISIBLE::PRIVATE)
	{
		Box1Disply = (int)TVISIBLE::OUTPUT;
	}

	model->AllVariables->clear();

	if (Box1Disply == (int)TVISIBLE::OUTPUT)
	{

		for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) 
		{
			thisVar = (*itVar).second;
			if (thisVar->varType < TVar::Read && thisVar->visibility == TVISIBLE::USUAL &&
				thisVar->dimen != TDim::NREB &&
				(thisVar->values || thisVar->ivalues) && !thisVar->FileData) {
				Newname = DeclObsName(thisVar);
				if (model->AllVariables->count(Newname) == 0)
				{
					model->AllVariables->insert(std::pair<std::string, ClassVar*>(Newname, thisVar));
				}
			}
		}
	}
	else
	{

		string S0;

		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
			modIt != Global::OurModulesList->end();
			modIt++
			)
		{
			string S = modIt->first;
			ClassModule* thisModule = modIt->second;
			if (S0 != S) {
				if (!(S0.length() == 0))
				{
					//test->AllVariables->Add(" "); Now that AllVariables is a map this line doesnt make sense.
				}

				S0 = S;
				if (thisModule->variation != 0) {
					string AA("#0");
					AA[1] += (char)(log(thisModule->variation) / log(2) + 1);
					S0 += AA;
				}

				S0 = "   --- " + S0;
				//model->AllVariables->insert(std::pair<std::string, ClassVar*>(S0 + " ---", (ClassVar*)modIt->second));
				//if (S0.Length() > Max_Name_Width1)
					//Max_Name_Width1 = S0.Length();
			}

			switch (Box1Disply) { // display in module/group
			case (int)TVISIBLE::USUAL:
				for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
					thisVar = (*itVar).second;
					if (S == thisVar->module.c_str() && thisVar->visibility == TVISIBLE::USUAL &&
						Variation_Decide(thisVar->variation_set, thisModule->variation) &&
						thisVar->dimen != TDim::NREB &&
						(thisVar->values || thisVar->ivalues) && !thisVar->FileData) {

						//if (UpDownOBSIndx->Max < thisVar->lay && thisVar->dimen == CRHM::NDEF)
							//UpDownOBSIndx->Max = thisVar->lay;
						Newname = DeclObsName(thisVar);
						if (model->AllVariables->count(Newname) == 0) {
							model->AllVariables->insert(std::pair<std::string, ClassVar*>(Newname, thisVar));
							//if (Newname.length() > Max_Name_Width2)
								//Max_Name_Width2 = Newname.Length();
						}
					}
				}
				break;

			case (int)TVISIBLE::DIAGNOSTIC: // display diagnostic variables
				for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
					thisVar = (*itVar).second;
					if (S == thisVar->module.c_str() && thisVar->visibility == TVISIBLE::DIAGNOSTIC &&
						thisVar->dimen != TDim::NREB &&
						(thisVar->values || thisVar->ivalues) && !thisVar->FileData) {
						Newname = DeclObsName(thisVar);
						if (model->AllVariables->count(Newname) == 0) {
							model->AllVariables->insert(std::pair<std::string, ClassVar*>(Newname, thisVar));
							//if (Newname.Length() > Max_Name_Width2)
								//Max_Name_Width2 = Newname.Length();
						}
					}
				}
				break;

			case (int)TVISIBLE::PRIVATE: // display Local variables
				for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
					thisVar = (*itVar).second;
					if (S == thisVar->module.c_str() && thisVar->visibility == TVISIBLE::PRIVATE &&
						thisVar->dimen != TDim::NREB &&
						(thisVar->values || thisVar->ivalues) && !thisVar->FileData) {
						Newname = DeclObsName(thisVar);
						if (model->AllVariables->count(Newname) == 0) {
							model->AllVariables->insert(std::pair<std::string, ClassVar*>(Newname, thisVar));
							//if (Newname.Length() > Max_Name_Width2)
								//Max_Name_Width2 = Newname.Length();
						}
					}
				}
				break;
			default:
				break;
			}
		} // for
	} // else

	//if (Max_Name_Width2 > Max_Name_Width1) // Max_Name_Width1 only title, Max_Name_Width2 handles other names
		//Max_Name_Width1 = Max_Name_Width2;

	//if (Max_Name_Width1 * 6 > AllVariables->Width)
		//AllVariables->ScrollWidth = Max_Name_Width1 * 6;

	//Max_Name_Width1 += 5; // handles array element

	//if (Max_Name_Width2 * 6 > ListBox3->Width)
		//ListBox3->ScrollWidth = Max_Name_Width1 * 6;

	//if (Max_Name_Width2 * 6 > AllObservations->Width)
		//AllObservations->ScrollWidth = Max_Name_Width2 * 6;

	//Max_Name_Width2 += 5; // handles array element

	//if (Max_Name_Width2 * 6 > SelectedObservations->Width)
		//SelectedObservations->ScrollWidth = Max_Name_Width2 * 6;

}


bool CRHMmainDlg::Variation_Decide(int Variation_set, long Variation)
{
	VandP V; 
	V.Set(Variation);

	long variations = V.GetV(); // & 2047;

	if ((Variation_set & 2048) != 0 && variations == 0 || // handles VARIATION_0
		(Variation_set & 4096) != 0 ||                        // handles VARIATION_0
		(Variation_set == 0) ||                               // handles VARIATION_ORG
		(variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
		return true;
	else
		return false;
}


std::string CRHMmainDlg::DeclObsName(ClassVar* thisVar)
{
	std::string Newname = thisVar->name.c_str();

	std::list<std::pair<std::string, ClassModule*>>::iterator pos = Global::OurModulesList->end();
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
		it != Global::OurModulesList->end();
		it++
		)
	{
		if (it->first == thisVar->module.c_str())
		{
			pos = it;
			break;
		}
	}

	int found = Newname.find("#");
	if (pos != Global::OurModulesList->end() && found > 0) // -1 for "obs" and "#" for declared "obs"
	{
		ClassModule* thisModule = pos->second;
		if (thisModule->isGroup) // if group add suffix
		{
			string AA;
			Common::GroupEnding(AA, thisModule->GroupCnt);
			Newname += AA;
		}
	}
	return Newname;
}


void CRHMmainDlg::RunClickFunction()
{
	CRHMmain* test = CRHMmain::getInstance();

	if (test->ObsFilesList->size() == 0)
	{
		MessageBox(_T("Please open an observation file."));
		return;
	}

	MMSData* mmsdata = test->RunClick2Start();


	int seriesCount = test->SeriesCnt;

	if (seriesCount == 0)
	{
		return;
	}



	CSeries series[1000];

	std::list<std::pair<std::string, ClassVar*>>::iterator selectedVariableIt = test->SelectedVariables->begin();
	for (int i = 0; i < seriesCount; i++)
	{

		string s = selectedVariableIt->first;
		CString cs(s.c_str());

		int removed = 0;

		//if a variable is preexisting, we need to delete that variable.
		int cnt = tchart.get_SeriesCount();
		for (int j = 0; j < cnt; j++)
		{
			if (tchart.SeriesTitleLegend(j) == cs)
			{
				tchart.RemoveSeries(j);
				removed = 1;
				break;
			}
		}

		tchart.AddSeries(0);
		if (removed == 1) { series[i] = tchart.Series(cnt - 1); }
		else { series[i] = tchart.Series(cnt); }

		series[i].put_LegendTitle(cs);

		selectedVariableIt++;
	}

	string values = "";
	int seriesIndex = 0;
	int TotalCount = 0;

	int pcount = 0;
	int n = 0;
	for (int indx = Global::DTmin; indx < Global::DTmax; indx = indx + 500)
	{

		int next = indx + 500;
		if (next >= Global::DTmax)
		{
			test->RunClick2Middle(mmsdata, indx, Global::DTmax);
		}
		else
		{
			test->RunClick2Middle(mmsdata, indx, indx + 500);
		}

		//test->RunClick2Middle(mmsdata, Global::DTmin, Global::DTmax);

		TotalCount = test->cdSeries[0]->Count();

		for (int i = pcount; i < TotalCount; i++)
		{
			for (int j = 0; j < seriesCount; j++)
			{
				int y, m, d, h, mi;
				StandardConverterUtility::GetDateTimeElements(test->cdSeries[j]->XValues.at(i), &y, &m, &d, &h, &mi);
				string dt = to_string(m) + "/" + to_string(d) + "/" + to_string(y);
				CString str(dt.c_str());
				LPCTSTR dtstr = (LPCTSTR)str;
				series[j].AddXY(test->cdSeries[j]->XValues.at(i), test->cdSeries[j]->YValues.at(i), dtstr, series[j].get_Color());
			}
			n++;
			if (n % 500 == 0) { tchart.Repaint(); }
			//tchart.Repaint();
		}
		pcount = TotalCount;
		//tchart.Repaint();
	}
	tchart.Repaint();

	test->RunClick2End(mmsdata);

	if (test->getAutoExit())
	{
		GetActiveWindow()->PostMessageW(WM_QUIT);
	}
}


void CRHMmainDlg::AddSeriesToTChart(TSeries* tseries)
{
	//CRHMmain * test = CRHMmain::getInstance();

	CSeries series;
	tchart.AddSeries(0);
	int count = tchart.get_SeriesCount();
	series = tchart.Series(count - 1);

	CString cstr(tseries->Title.c_str());
	//CString extension("(1)");
	//cstr.Append(extension);

	series.put_LegendTitle(cstr);

	for (size_t i = 0; i < tseries->XValues.size(); i++)
	{
		int y, m, d, h, mi;
		StandardConverterUtility::GetDateTimeElements(tseries->XValues.at(i), &y, &m, &d, &h, &mi);
		string dt = to_string(m) + "/" + to_string(d) + "/" + to_string(y);
		CString str(dt.c_str());
		LPCTSTR dtstr = (LPCTSTR)str;
		series.AddXY(tseries->XValues.at(i), tseries->YValues.at(i), dtstr, series.get_Color());

		//if (i % 500 == 0) { tchart.Repaint(); }		
	}
	tchart.Repaint();
}


void CRHMmainDlg::AddObsPlot(ClassVar* thisVar, TSeries* cdSeries, string S, TFun Funct) {

	CRHMmain* test = CRHMmain::getInstance();

	ClassVar* newVar;
	Global::HRU_OBS = Global::HRU_OBS_DIRECT; // always correct?

	double** Data = thisVar->FileData->Data;
	double xx;
	double DTstartR = test->GetStartDate();
	double DTendR = test->GetEndDate();

	if (DTstartR >= DTendR) return;

	TDateTime Save_DTnow = Global::DTnow; // Save

	double MyInterval = thisVar->FileData->Interval;
	long DTmin = INT((DTstartR - Global::DTstart) * thisVar->FileData->Freq) * Global::Freq / thisVar->FileData->Freq;
	long DTmax = INT((DTendR - Global::DTstart) * thisVar->FileData->Freq) * Global::Freq / thisVar->FileData->Freq;

	long jj1 = S.rfind("(");
	long jj2 = S.rfind(")");

	long Indx;
	string::size_type pp;
	pp = thisVar->name.rfind('(');
	bool AlreadyIndex = (pp != string::npos); // handles exported variables in Obs files

	if (test->ListHruNames && thisVar->varType < TVar::Read) // using names
	{

		string sub = S.substr(jj1 + 1, jj2 - jj1 - 1);
		bool found = false;
		int n;
		for (size_t i = 0; i < test->ListHruNames->size(); i++)
		{
			if (test->ListHruNames->at(i) == sub)
			{
				n = i;
				found = true;
			}
		}

		if (found == false)
		{
			n = -1;
		}

		Indx = n - 1; //Subtraction of 1 to match historic code jhs507

	}
	else {
		if (thisVar->root != "" || AlreadyIndex)
			Indx = 0; // (non observations always 0
		else
			Indx = stoi(S.substr(jj1 + 1, jj2 - jj1 - 1)) - 1;
	}

	long IndxMin = thisVar->FileData->IndxMin;
	long IndxMax = thisVar->FileData->IndxMax;

	if (thisVar->FileData->Times != NULL) { // display sparse data
		if (Global::Freq == 1)
			--DTendR;

		double Sum = 0.0;

		for (long ii = 0; ii < thisVar->FileData->Lines; ++ii) {
			if (thisVar->FileData->Times[ii] < DTstartR) continue;
			if (thisVar->FileData->Times[ii] > DTendR) continue;

			xx = Data[thisVar->offset + Indx][ii];

			if (Funct == TFun::TOT) {
				Sum += xx;
				xx = Sum;
			}

			cdSeries->AddXY(thisVar->FileData->Times[ii], xx);
		}
	}

	else if (Funct <= TFun::MJ_W) // display simple observations
	{ 

		for (Global::DTindx = DTmin; Global::DTindx < DTmax; Global::DTindx++) 
		{
			Global::DTnow = Global::DTstart + Global::Interval * Global::DTindx + Global::Interval;

			if (MyInterval >= 1)
			{
				--Global::DTnow;
			}

			if (Global::DTindx * thisVar->FileData->Freq / Global::Freq >= IndxMin
				&& Global::DTindx * thisVar->FileData->Freq / Global::Freq <= IndxMax) 
			{
				xx = Data[thisVar->offset + Indx][(Global::DTindx * thisVar->FileData->Freq / Global::Freq - IndxMin)];

				if (Funct == TFun::FOBS)
				{
					//No function to apply.
				}
				else if (Funct == TFun::VP_SAT) 
				{
					if (xx > 0.0)
					{
						xx = 0.611 * exp(17.27 * xx / (xx + 237.3));
					}
					else
					{
						xx = 0.611 * exp(21.88 * xx / (xx + 265.5));
					}
				}
				else if (Funct == TFun::W_MJ)
				{
					xx *= thisVar->FileData->Interval * 86400 / 1.0E6;
				}
				else if (Funct == TFun::MJ_W)
				{
					xx *= 1.0E6 / 86400 / thisVar->FileData->Interval;
				}

				cdSeries->AddXY(Global::DTnow, xx);
			}
		}
	}
	else { // display observations functions
		//cdSeries->Stairs = true;
		// N.B. object FileData copied. If Obs function - Obs deletes else if VarObsFunct SelectedObservations deletes.
		newVar = new ClassVar(*thisVar);

		newVar->name = S.c_str();

		newVar->FileData->DataFileName = "Copy";


		string::size_type pp = thisVar->units.find_last_of(")");

		if (thisVar->FileData->Freq > 1 && (thisVar->units[pp - 1] == 'd'))   //  || TBase == 0
			thisVar->Daily = TRUE;
		else
			thisVar->Daily = FALSE;

		if (newVar->root == "") { // Observation
			if (thisVar->FileData->Freq == 1)
				newVar->LoopFunct = &ClassVar::LoopFirst;
			else if (thisVar->Daily)
				newVar->LoopFunct = &ClassVar::LoopFirst;
			else
				newVar->LoopFunct = &ClassVar::LoopRange;
		}
		else { // Variable
			if (thisVar->Daily)
				newVar->LoopFunct = &ClassVar::LoopLast;
			else
				newVar->LoopFunct = &ClassVar::LoopRange;
		}

		newVar->FunctVar = thisVar;

		switch (Funct) {
		case TFun::AVG:
			newVar->UserFunct_ = &ClassVar::Tot_;
			newVar->FunKind = TFun::AVG;
			break;
		case TFun::MIN:
			newVar->UserFunct_ = &ClassVar::Min_;
			newVar->FunKind = TFun::MIN;
			break;
		case TFun::MAX:
			newVar->UserFunct_ = &ClassVar::Max_;
			newVar->FunKind = TFun::MAX;
			break;
		case TFun::TOT:
			newVar->UserFunct_ = &ClassVar::Tot_;
			newVar->FunKind = TFun::TOT;
			break;
		case TFun::POS:
			newVar->UserFunct_ = &ClassVar::Pos_;
			newVar->FunKind = TFun::POS;
			break;
		case TFun::FIRST:
			newVar->UserFunct_ = &ClassVar::First_;
			newVar->FunKind = TFun::FIRST;
			newVar->LoopFunct = &ClassVar::LoopFirst;
			break;
		case TFun::LAST:
			newVar->UserFunct_ = &ClassVar::Last_;
			newVar->FunKind = TFun::LAST;
			newVar->LoopFunct = &ClassVar::LoopLast;
			break;
		case TFun::CNT:
			newVar->UserFunct_ = &ClassVar::Count_;
			newVar->FunKind = TFun::CNT;
			break;
		case TFun::CNT0:
			newVar->UserFunct_ = &ClassVar::Count0_;
			newVar->FunKind = TFun::CNT0;
			break;
		case TFun::DLTA:
			newVar->UserFunct_ = &ClassVar::First_;
			newVar->LoopFunct = &ClassVar::LoopFirst;
			newVar->FunKind = TFun::DLTA;
			break;
		default:
			break;
		} // switch

		bool First = false;
		long Next = -1;
		long Days = 0;
		long LastDays = 0;
		long Lastkk = 0;
		long CurrentIndx = -1;
		long LastIndex = -1;
		long itime[6];
		long Greatest;
		long DTminX = DTmin;
		if (IndxMin > 0)
			DTminX = IndxMin;
		double Delta0 = 0.0;
		double First0;
		double Temp;
		dattim("now", itime);

		for (Global::DTindx = DTmin; Global::DTindx < DTmax; Global::DTindx += Global::Freq) {
			Global::DTnow = Global::DTstart + Global::Interval * Global::DTindx + Global::Interval;

			if (Global::DTindx * Global::Freq / thisVar->FileData->Freq >= IndxMin)
				if (Global::DTindx * thisVar->FileData->Freq / Global::Freq > IndxMax)
					break;
				else {
					if (Global::Interval >= 1) --Global::DTnow;

					dattim("now", itime);

					switch (TBase) {

					case TimeBase::DAILY: // daily
						if (Next == -1 || Next != itime[2]) {
							Next = itime[2];
							First = TRUE;
						}
						break;
					case TimeBase::WATER_YEAR: // water annual
						if (Next == -1 || itime[0] == Next && itime[1] == water_year_month) {
							if (Next == -1 && itime[1] < water_year_month)
								Next = itime[0];
							else
								Next = itime[0] + 1;
							First = TRUE;
						}
						break;
					case TimeBase::CALENDAR_YEAR: // annual
						if (Next == -1 || itime[0] == Next && itime[1] == 1) {
							Next = itime[0] + 1;
							First = TRUE;
						}
						break;
					case TimeBase::MONTHLY: // monthly
						if (Next == -1 || Next == itime[1]) {
							Next = (itime[1]) % 12 + 1;
							First = TRUE;
						}
						break;
					case TimeBase::ALL: // All - do nothing
						if (Next == -1) {
							Next = 0;
							First = TRUE; // do nothing
						}
					default:
						break;
					} // switch

					CurrentIndx = (Global::DTindx - DTminX) / thisVar->FileData->Freq - 1;

					if (First) {
						if (Global::DTindx > DTmin && Global::DTindx > IndxMin) { // Handle RUN starting after beginning of primary obs file and secondary obs file later
							switch (Funct) {
							case TFun::DLTA:
								Temp = cdSeries->YValue((Global::DTindx - DTmin) / thisVar->FileData->Freq - 1);
								cdSeries->YValues.at(CurrentIndx) -= Delta0;
								Delta0 = Temp; // fall through
							case TFun::AVG:
							case TFun::MIN: // duplicate last
							case TFun::MAX: // duplicate last
							case TFun::TOT: // duplicate last
							case TFun::POS: // duplicate last
							case TFun::LAST: // duplicate last
							case TFun::CNT:  // duplicate last
							case TFun::CNT0: // duplicate last
								if (ObsFunct_Toggle == 1) // show final value
									for (long jj = LastIndex + 1; jj <= CurrentIndx; ++jj)
										cdSeries->YValues[jj] = cdSeries->YValues[CurrentIndx];
								break;
							case TFun::FIRST: // duplicate first
								for (long jj = LastIndex + 1; jj <= CurrentIndx; ++jj)
									cdSeries->YValues.at(jj) = First0;
								break;
							default:
								break;
							} // switch
						}
						else if (Funct == TFun::DLTA && TBase != TimeBase::DAILY) { // only very first time
							(newVar->*(newVar->LoopFunct))(Indx);
							Delta0 = newVar->values[Indx];

							newVar->UserFunct_ = &ClassVar::Last_; // change from First interval to Last interval
							newVar->FunKind = TFun::LAST;
							newVar->LoopFunct = &ClassVar::LoopLast;
						}

						Lastkk = Global::DTindx;
						if (CurrentIndx > -1) // skip first time
							LastIndex = CurrentIndx;

						switch (Funct) { // beginning of period reset
						case TFun::MAX:
							newVar->values[Indx] = -1000000.0;
							break;
						case TFun::MIN:
							newVar->values[Indx] = 1000000.0;
							break;
						case TFun::AVG:
						case TFun::TOT:
						case TFun::CNT:
						case TFun::CNT0:
						case TFun::DLTA:
						case TFun::POS:
							newVar->values[Indx] = 0.0;
						default:
							break;
						} // switch

						LastDays = Days;
						Days = 0;
					} // if First

					(newVar->*(newVar->LoopFunct))(Indx);

					xx = newVar->values[Indx];
					cdSeries->AddXY(Global::DTnow, xx);
					//AddDataToSeries(series, Global::DTnow, xx);

					if (First)
						First0 = xx;

					if (Global::DTindx > DTmin && Global::DTindx > IndxMin) {
						switch (Funct) {
						case TFun::AVG:
							Greatest = Days;
							if (LastDays > Days)
								Greatest = LastDays;
							cdSeries->YValues.at(CurrentIndx) /= ((long long)Global::Freq * (long long)Greatest);
							LastDays = 0;
							break;
						case TFun::DLTA:
							if (!First)
								cdSeries->YValues.at(CurrentIndx) -= Delta0;
							break;
						default:
							break;
						} // switch
					}

					++Days;

					First = FALSE;
				} // if
		} // for

		if (Global::DTindx > DTmin && Global::DTindx > IndxMin) { // Handle RUN starting after beginning of primary obs file and secondary obs file later
			CurrentIndx = (Global::DTindx - DTminX) / thisVar->FileData->Freq - 1;
			switch (Funct) {
			case TFun::AVG:
				Greatest = Days;
				if (LastDays > Days)
					Greatest = LastDays;
				cdSeries->YValues.at(CurrentIndx) /= ((long long)Global::Freq * (long long)Greatest);
				if (ObsFunct_Toggle == 1) // show final value
					for (long jj = LastIndex + 1; jj <= CurrentIndx; ++jj)
						cdSeries->YValues[jj] = cdSeries->YValues[CurrentIndx];
				break;
			case TFun::DLTA:
				cdSeries->YValues.at(CurrentIndx) -= Delta0;
			case TFun::MIN: // duplicate last
			case TFun::MAX: // duplicate last
			case TFun::TOT: // duplicate last
			case TFun::POS: // duplicate last
			case TFun::LAST: // duplicate last
			case TFun::CNT:  // duplicate last
			case TFun::CNT0: // duplicate last
				if (ObsFunct_Toggle == 1) // show final value
					for (long jj = LastIndex + 1; jj <= CurrentIndx; ++jj)
						cdSeries->YValues[jj] = cdSeries->YValues[CurrentIndx];
				break;
			case TFun::FIRST: // duplicate first
				for (long jj = LastIndex + 1; jj <= CurrentIndx; ++jj)
					cdSeries->YValues.at(jj) = First0;
				break;
			default:
				break;
			} // switch
		}

		delete newVar->FileData; // created in this routine
		delete newVar; // created in this routine

		cdSeries->Tag = NULL;
	} // else

	Global::DTnow = Save_DTnow; // restore

	//if (!CommandLine)  // do not repaint
	//tchart.Repaint();

	AddSeriesToTChart(cdSeries);

}


void CRHMmainDlg::SetTime(double startDate, double endDate)
{
	COleDateTime oletimeTime(startDate);
	VERIFY(StartDatePicker.SetTime(oletimeTime));

	COleDateTime oletimeTime2(endDate);
	VERIFY(EndDatePicker.SetTime(oletimeTime2));
}


void CRHMmainDlg::OpenProject(std::string filepath, std::string filename)
{
	CRHMmain* model = CRHMmain::getInstance();
	bool errorOpening = !model->DoPrjOpen(filepath, filename);
	std::string errorString = "Cannot open open observation file: \n" + filename + "\n\nCheck that it is correctly specified in the project file and located at: \n"+ filepath;
	if (errorOpening)
	{
		MessageBox(
			(LPCWSTR) CString(errorString.c_str()),
			(LPCWSTR) L"Error opening observation file.",
			MB_OK
		);
		return;
	}
	model->OpenProjectPath = filepath;
	loadGuiComponents();

	//when the user opens a project, make sure that the file path is portrayed at the top of the window - Matt
	//convert string so setwindowtext can use the string
	std::string str1 = "The Cold Regions Hydrological Model - ";
	str1.append(filepath);
	CString cFilePath(str1.c_str());

	//if the default project name is present, do not present it
	if (filepath == defaultprojectpath)
	{
		SetWindowText(L"The Cold Regions Hydrological Model");
	}
	else
	{
		SetWindowText(cFilePath);
	}

	if (model->getAutoRun())
	{
		UpdateWindow();
		this->RunClickFunction();
	}
}


void CRHMmainDlg::ReopenProject()
{
	CRHMmain* t = CRHMmain::getInstance();
	if (t->OpenProjectPath.length() == 0)
	{
		OpenProject(defaultprojectpath, defaultprojectname);
	}
	else
	{
		OpenProject(t->OpenProjectPath, t->OpenProjectPath);
	}
}


void CRHMmainDlg::SaveProject()
{
	CRHMmain* crhmmain = CRHMmain::getInstance();

	//setting the dialog contents to CRHMmain.

	std::list<std::pair<std::string, ClassVar*>>* selected_variables = GetSelectedVariables();
	std::list<std::pair<std::string, TSeries*>>* selected_observations = GetSelectedObservations();
	crhmmain->setSelectedVariables(selected_variables);
	crhmmain->setSelectedObservatoions(selected_observations);

	if (crhmmain->OpenProjectPath.length() == 0)
	{
		crhmmain->OpenProjectPath = defaultprojectpath;
	}

	crhmmain->SaveProject("Description - to be added", crhmmain->OpenProjectPath);
}


void CRHMmainDlg::CloseProject()
{
	CRHMmain* model = CRHMmain::getInstance();

	listbox_all_variables.ResetContent();
	ASSERT(listbox_all_variables.GetCount() == 0);
	model->AllVariables->clear();

	listbox_sel_variables.ResetContent();
	ASSERT(listbox_sel_variables.GetCount() == 0);
	model->SelectedVariables->clear();

	listbox_all_observations.ResetContent();
	ASSERT(listbox_all_observations.GetCount() == 0);
	model->AllObservations->clear();

	listbox_sel_observations.ResetContent();
	ASSERT(listbox_sel_observations.GetCount() == 0);
	model->SelectedObservations->clear();

	COleDateTime oletimeTime(StandardConverterUtility::GetCurrentDateTime());
	VERIFY(StartDatePicker.SetTime(oletimeTime));
	VERIFY(EndDatePicker.SetTime(oletimeTime));

	model->FormDestroy();
	model->FormCreate();

	//Close any open observation files.
	model->ObsCloseClick();
	updateOpenObsFileMenu();

	//Close any open state file.
	model->OpenNameState = "";
	model->OpenStateFlag = false;
	model->SaveStateFileName = "";
	model->SaveStateFlag = false;
	updateOpenStateFileMenu();

	//reset the current file name - Matt
	globFileName = "";
	model->OpenProjectPath = "";

	//Reset the window text
	SetWindowText(L"The Cold Regions Hydrological Model");
}


void CRHMmainDlg::AddDataToSeries(CSeries series, double xvalue, double yvalue)
{
	int y, m, d, h, mi;
	StandardConverterUtility::GetDateTimeElements(xvalue, &y, &m, &d, &h, &mi);
	string dt = to_string(m) + "/" + to_string(d) + "/" + to_string(y);
	CString str(dt.c_str());
	LPCTSTR dtstr = (LPCTSTR)str;

	series.AddXY(xvalue, yvalue, dtstr, series.get_Color());
}


void CRHMmainDlg::OpenObservation(std::string obsfilepath)
{
	CRHMmain* model = CRHMmain::getInstance();
	model->OpenObsFile(obsfilepath);

	std::map<std::string, ClassVar*>* observations = model->getObservations();
	std::map<std::string, ClassVar*>::iterator it;

	for (it = observations->begin(); it != observations->end(); it++)
	{
		CString cstr(it->first.c_str());
		listbox_all_observations.AddString(cstr);
	}

	SetTime(model->GetStartDate(), model->GetEndDate());
}


void CRHMmainDlg::AddOpenObsFile(std::string filepath, std::string filename)
{
	CString obsFileName = CString(filename.c_str());
	CMenu* menu = GetActiveWindow()->GetMenu();
	CMenu* submenu = menu->GetSubMenu(1);

	//Find first ID not in use
	UINT OPEN_ID = BEGIN_OPEN_OBS_FILE_ID;
	for (UINT ID = ID_OPEN_OBS_FILE_FIRST; ID < END_OPEN_OBS_FILE_ID; ID++)
	{
		if (!this->openObsFiles->count(ID))
		{
			OPEN_ID = ID;
			break;
		}
	}

	if (OPEN_ID == BEGIN_OPEN_OBS_FILE_ID || OPEN_ID == END_OPEN_OBS_FILE_ID)
	{
		//Cannot open a new obs file send error message. 
	}
	else
	{
		//Add newly opened file to openObsFile Map
		this->openObsFiles->insert(std::pair<UINT, std::pair<std::string, std::string>>(OPEN_ID, std::pair<std::string, std::string>(filepath, filename)));
		submenu->AppendMenu(MF_STRING, OPEN_ID, (LPCTSTR)obsFileName);
	}

}


void CRHMmainDlg::updateGuiMenuItems()
{
	updateOpenObsFileMenu();
	updateOpenStateFileMenu();
}


void CRHMmainDlg::updateOpenObsFileMenu()
{
	/*
	* Remove all observations from the list boxes and plot area
	*/
	listbox_all_observations.ResetContent();
	listbox_sel_observations.ResetContent();
	tchart.RemoveAllSeries();

	/*
	* Remove all open obsFiles from the obs submenu.
	*/
	CMenu* menu = GetActiveWindow()->GetMenu();
	CMenu* submenu = menu->GetSubMenu(1);

	for (
		std::map<UINT, std::pair<std::string, std::string>>::iterator it = this->openObsFiles->begin();
		it != this->openObsFiles->end();
		it++
		)
	{
		submenu->RemoveMenu(it->first, MF_BYCOMMAND);
	}
	this->openObsFiles->clear();

	/*
	* The observation gui items are now reset. Now we can rebuild them.
	*/

	/*
	* Check the model for what obs files are open and what obs exist.
	*/
	CRHMmain* main = CRHMmain::getInstance();
	std::map<std::string, ClassVar*>* observations = main->getObservations();
	std::list<std::pair<std::string, TSeries*>>* selectedObservations = main->getSelectedObservations();
	std::list<std::pair<std::string, ClassData*>>* listOfObsFiles = main->ObsFilesList;

	/*
	* For each open observation create a new menu item in the obs submenu.
	*/
	for (
		std::list<std::pair<std::string, ClassData*>>::iterator it = listOfObsFiles->begin();
		it != listOfObsFiles->end();
		it++
		)
	{
		CString obsFileName = CString(it->second->DataFileName.c_str());

		/* Find the first open ID number. */
		UINT OPEN_ID = BEGIN_OPEN_OBS_FILE_ID;
		for (UINT ID = ID_OPEN_OBS_FILE_FIRST; ID < END_OPEN_OBS_FILE_ID; ID++)
		{
			if (!this->openObsFiles->count(ID))
			{
				OPEN_ID = ID;
				break;
			}
		}

		if (OPEN_ID == BEGIN_OPEN_OBS_FILE_ID || OPEN_ID == END_OPEN_OBS_FILE_ID)
		{
			//Cannot open a new obs file send error message. 
			//TODO
		}
		else
		{
			/* Add this observation file to the map.*/
			this->openObsFiles->insert(std::pair<UINT, std::pair<std::string, std::string>>(OPEN_ID, std::pair<std::string, std::string>(it->second->DataFileName, it->second->DataFileName)));
			/* Create a menu item in the submenu for the observation file. */
			submenu->AppendMenu(MF_STRING, OPEN_ID, (LPCTSTR)obsFileName);
		}
	}

	/*
	* For each observation add the name to the listbox of observations
	*/
	for (
		std::map<std::string, ClassVar*>::iterator it = observations->begin();
		it != observations->end();
		it++
		)
	{
		CString cstr(it->first.c_str());
		listbox_all_observations.AddString(cstr);
	}


	std::vector<std::list<std::pair<std::string, TSeries*>>::iterator> toErase;

	/*
	* For each selected observation add the name to the listbox of selected observations
	* and add the TSeries to the plot
	*/
	for (
		std::list<std::pair<std::string, TSeries*>>::iterator it = selectedObservations->begin();
		it != selectedObservations->end();
		it++
		)
	{
		//remove suffix
		std::string withoutSuffix = it->first.substr(0, it->first.find_last_of('('));
	
		int found = main->AllObservations->count(withoutSuffix);

		if (!found)
		{
			toErase.push_back(it);
		}

	}

	for (size_t i = 0; i < toErase.size(); i++)
	{
		selectedObservations->erase(toErase.at(i));
	}

	updateSelectedObservationListBox();
}


void CRHMmainDlg::updateOpenStateFileMenu()
{
	/* Get the handle for the intital state submenu */
	CMenu* menu = GetActiveWindow()->GetMenu()->GetSubMenu(4);

	/* Get the model instance */
	CRHMmain* model = CRHMmain::getInstance();

	/* Check to see if a menu item exists for an open state file. */
	if (menu->GetMenuItemCount() > 6)
	{
		/* Remove whatever item was in the submenu for the open file. */
		menu->RemoveMenu(ID_OPEN_INIT_FILE, MF_BYCOMMAND);
	}


	/* Check the model to see if a inital state file is open*/
	if (model->OpenStateFlag)
	{
		/* If a state file is open in the model create a menu item for it*/

		std::string stateFileMenuItemName = "Open State File: ";
		stateFileMenuItemName += model->OpenNameState.c_str();

		CString stateFileName = CString(stateFileMenuItemName.c_str());

		//menu->AppendMenu(MF_STRING, ID_OPEN_INIT_FILE, (LPCTSTR)stateFileName);
		menu->InsertMenu(0, MF_STRING, ID_OPEN_INIT_FILE, (LPCTSTR)stateFileName);
	}

	/* Enable or disable the save state as button*/

	if (model->getFinishedRun())
	{
		menu->EnableMenuItem(ID_STATE_SAVE_STATE_AS, MF_ENABLED);
	}
	else
	{
		menu->EnableMenuItem(ID_STATE_SAVE_STATE_AS, MF_DISABLED);
	}

	if (model->SaveStateFlag == true)
	{
		menu->CheckMenuItem(ID_STATE_SAVE_STATE, MF_CHECKED);

		std::string saveTo = "Save State To: ";
		saveTo += model->SaveStateFileName;
		CString saveTo_CString = CString(saveTo.c_str());
		menu->ModifyMenu(ID_STATE_SAVE_TO, MF_BYCOMMAND, ID_STATE_SAVE_TO, (LPCTSTR)saveTo_CString);

		menu->EnableMenuItem(ID_STATE_SAVE_TO, MF_ENABLED);
	}
	else
	{
		menu->CheckMenuItem(ID_STATE_SAVE_STATE, MF_UNCHECKED);

		std::string saveTo = "Save State To:";
		CString saveTo_CString = CString(saveTo.c_str());
		menu->ModifyMenu(ID_STATE_SAVE_TO, MF_BYCOMMAND, ID_STATE_SAVE_TO, (LPCTSTR)saveTo_CString);

		menu->EnableMenuItem(ID_STATE_SAVE_TO, MF_DISABLED);
	}

}

void CRHMmainDlg::updateSelectedVariablesListBox()
{
	CWaitCursor wait;

	CRHMmain* model = CRHMmain::getInstance();

	/*Anything in the model needs to be displayed*/
	std::list<std::pair<std::string, ClassVar*>>* listOfSelectedVariables = model->getSelectedVariables();

	for (
		std::list<std::pair<std::string, ClassVar*>>::iterator it = listOfSelectedVariables->begin();
		it != listOfSelectedVariables->end();
		it++
		)
	{
		int found = listbox_sel_variables.FindString(-1, CString(it->first.c_str()));

		//If it is found it is already displayed if not then display it. 
		if (found == LB_ERR)
		{
			CString selectedVariable = CString(it->first.c_str());

			listbox_sel_variables.AddString(selectedVariable);
		}

	}

	/*Anything not in the model needs to be removed from the display*/
	for (int i = 0; i < listbox_sel_variables.GetCount(); i++)
	{
		CString text;
		listbox_sel_variables.GetText(i, text);
		std::string str = CT2A(text.GetString());

		bool found = false;
		std::list<std::pair<std::string, ClassVar*>>* listOfSelectedVariables = model->getSelectedVariables();

		for (
			std::list<std::pair<std::string, ClassVar*>>::iterator it = listOfSelectedVariables->begin();
			it != listOfSelectedVariables->end();
			it++
			)
		{
			if (it->first == str)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			//Remove from the list box
			listbox_sel_variables.DeleteString(i);
			//Restart outer itteration
			i = -1;
		}

	}
}

void CRHMmainDlg::updateSelectedObservationListBox()
{
	CWaitCursor wait;

	CRHMmain* model = CRHMmain::getInstance();

	/*Anything in the model needs to be displayed*/
	std::list<std::pair<std::string, TSeries*>>* listOfSelectedObs = model->SelectedObservations;

	for (
		std::list<std::pair<std::string, TSeries*>>::iterator it = listOfSelectedObs->begin();
		it != listOfSelectedObs->end();
		it++
		)
	{
		int found = listbox_sel_observations.FindStringExact(-1, CString(it->first.c_str()));

		//If it is found it is already displayed if not then display it. 
		if (found == LB_ERR)
		{
			//Reset the used to zero so that it doesn't "double write"
			it->second->XValues.clear();
			it->second->YValues.clear();

			/* Look for a suffix and set function to the correct value. */
			TFun funct = TFun::FOBS;
			size_t suffixStart = it->first.rfind('_');
			std::string suffix;
			if (suffixStart == std::string::npos)
			{
				suffix = "";
			}
			else
			{
				suffix = it->first.substr(suffixStart, std::string::npos);
			}

			if (suffix == "")
			{
				funct = TFun::FOBS;
			}
			else if (suffix == "_Tot")
			{
				funct = TFun::TOT;
			}
			else if (suffix == "_Min")
			{
				funct = TFun::MIN;
			}
			else if (suffix == "_Max")
			{
				funct = TFun::MAX;
			}
			else if (suffix == "_Avg")
			{
				funct = TFun::AVG;
			}

			AddObsPlot(it->second->Tag, it->second, it->first, funct);

			CString selectedObservation = CString(it->first.c_str());

			listbox_sel_observations.AddString(selectedObservation);
		}

	}

	/*Anything not in the model needs to be removed from the display*/
	for (int i = 0; i < listbox_sel_observations.GetCount(); i++)
	{
		CString text;
		listbox_sel_observations.GetText(i, text);
		std::string str = CT2A(text.GetString());

		bool found = false;
		std::list<std::pair<std::string, TSeries*>>* listOfSelectedObs = model->SelectedObservations;

		for (
			std::list<std::pair<std::string, TSeries*>>::iterator it = listOfSelectedObs->begin();
			it != listOfSelectedObs->end();
			it++
			)
		{
			if (it->first == str)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			//Remove from the Chart
			for (int j = 0; j < tchart.get_SeriesCount(); j++)
			{
				CString title = tchart.SeriesTitleLegend(j);
				if (title == text)
				{
					tchart.RemoveSeries(j);
					break;
				}
			}

			//Remove from the list box
			listbox_sel_observations.DeleteString(i);
			//Restart outer itteration
			i = -1;
		}

	}
}


void CRHMmainDlg::OnFileOpen()
{

	CWaitCursor wait;

	CFile theFile;
	TCHAR szFilters[] = _T("MyType Files (*.prj)|*.prj|All Files (*.*)|*.*||");
	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);

	CFileDialog fileDlg(TRUE, _T("prj"), _T("*.prj"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);


	// Display the file dialog. When user clicks OK, fileDlg.DoModal()
	// returns IDOK.
	if (fileDlg.DoModal() == IDOK)
	{
		this->CloseProject();

		CString filepath = fileDlg.GetPathName();

		CString filename = fileDlg.GetFileName();

		//update file name tracking variable - Matt
		globFileName = filename;

		string file_p = CT2A(filepath.GetString());
		string file_n = CT2A(filename.GetString());

		OpenProject(file_p, file_n);

		updateGuiMenuItems();
	}

}


void CRHMmainDlg::OnFileSave()
{
	SaveProject();
}


void CRHMmainDlg::OnFileSaveAs()
{
	TCHAR szFilters[] = _T("MyType Files (*.prj)|*.prj|All Files (*.*)|*.*||");

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);

	CFileDialog fileDlg(FALSE, _T("prj"), _T("*.prj"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	INT_PTR result = fileDlg.DoModal();

	if (result == IDOK)
	{
		CRHMmain* crhmmain = CRHMmain::getInstance();

		//setting the dialog contents to CRHMmain.

		std::list<std::pair<std::string, ClassVar*>>* selected_variables = GetSelectedVariables();
		std::list<std::pair<std::string, TSeries*>>* selected_observations = GetSelectedObservations();
		crhmmain->setSelectedVariables(selected_variables);
		crhmmain->setSelectedObservatoions(selected_observations);

		fileName = fileDlg.GetPathName();
		string filepath = CT2A(fileName.GetString());
		crhmmain->SaveProject("Description - to be added", filepath);
		if (result == IDOK) {
			MessageBox(_T("Your project has been saved."));
		}
		
		CRHMmain* model = CRHMmain::getInstance();
		model->OpenProjectPath = filepath;

		std::string str1 = "The Cold Regions Hydrological Model - ";
		str1.append(filepath);
		CString cFilePath(str1.c_str());
		SetWindowText(cFilePath);

	}
}


void CRHMmainDlg::OnFileClose()
{
	CWaitCursor wait;

	CString filename = globFileName;

	CRHMmain* model = CRHMmain::getInstance();

	//If the open project is a temp file then ask if they want to save.
	if (model->OpenProjectPath == defaultprojectname)
	{
		//If there is nothing to save close the project.
		if (listbox_all_variables.GetCount() == 0
			&& listbox_sel_variables.GetCount() == 0
			&& listbox_all_observations.GetCount() == 0
			&& listbox_sel_observations.GetCount() == 0)
		{
			this->CloseProject();
		}
		else 
		{
			const int result = MessageBox(L"Do you want to save this project?", L"CRHM_GUI", MB_YESNOCANCEL);

			if (result == IDYES) 
			{ 
				//Save and then close.
				OnFileSaveAs();
				this->CloseProject();
			}
			if (result == IDCANCEL) 
			{ 
				//Don't save and don't close.
				return;
			}
			if (result == IDNO)
			{
				//Close without saving.
				this->CloseProject();
			}
		}
	}
	else 
	{
		this->CloseProject();
	}

}


void CRHMmainDlg::OnExtractGroup()
{
	CReport report;
	report.DoModal();
}


void CRHMmainDlg::OnViewHierarchy()
{
	HierarchyDlg hierarchy;
	hierarchy.DoModal();
}

void CRHMmainDlg::OnAutoRun()
{
	CRHMmain* main = CRHMmain::getInstance();

	CMenu* menu = GetActiveWindow()->GetMenu();

	main->setAutoRun(true);
	if (menu->CheckMenuItem(ID_AUTO_RUN, MF_CHECKED) == MF_CHECKED)
	{
		main->setAutoRun(false);
		menu->CheckMenuItem(ID_AUTO_RUN, MF_UNCHECKED);
	};

}


void CRHMmainDlg::OnAutoExit()
{
	CRHMmain* main = CRHMmain::getInstance();

	CMenu* menu = GetActiveWindow()->GetMenu();

	main->setAutoExit(true);
	if (menu->CheckMenuItem(ID_AUTO_EXIT, MF_CHECKED) == MF_CHECKED)
	{
		main->setAutoExit(false);
		menu->CheckMenuItem(ID_AUTO_EXIT, MF_UNCHECKED);
	};
}


void CRHMmainDlg::OnExit()
{
	CString filename = globFileName;

	CRHMmain* t = CRHMmain::getInstance();

	if (listbox_all_variables.GetCount() == 0
		&& listbox_sel_variables.GetCount() == 0
		&& listbox_all_observations.GetCount() == 0
		&& listbox_sel_observations.GetCount() == 0)
	{
	}
	else
	{
		if (t->OpenProjectPath == defaultprojectname)
		{
			//const int result = MessageBox(NULL, L"Do you want to save this project?", MB_YESNOCANCEL);
			const int result = MessageBox(L"Do you want to save this project?", L"CRHM_GUI", MB_YESNOCANCEL);

			if (result == IDYES) { OnFileSaveAs(); }
			if (result == IDCANCEL) { return; } // if cancel is pressed, nothing should happen to the new project.
		}
	}
	exit(0);
}

void CRHMmainDlg::OnLogAll()
{
	CRHMmain* model = CRHMmain::getInstance();
	model->setReportAll(true);

	CMenu* menu = GetActiveWindow()->GetMenu();

	menu->CheckMenuItem(ID_MAIN_LOG_LAST, MF_UNCHECKED);
	if (menu->CheckMenuItem(ID_MAIN_LOG_ALL, MF_CHECKED) == MF_CHECKED)
	{
		menu->CheckMenuItem(ID_MAIN_LOG_ALL, MF_UNCHECKED);
	};
}

void CRHMmainDlg::OnLogLast()
{
	CRHMmain* model = CRHMmain::getInstance();
	model->setReportAll(false);

	CMenu* menu = GetActiveWindow()->GetMenu();

	menu->CheckMenuItem(ID_MAIN_LOG_ALL, MF_UNCHECKED);
	if (menu->CheckMenuItem(ID_MAIN_LOG_LAST, MF_CHECKED) == MF_CHECKED)
	{
		menu->CheckMenuItem(ID_MAIN_LOG_LAST, MF_UNCHECKED);
	};
}

void CRHMmainDlg::OnOpenObservation()
{
	// TODO: Add your command handler code here
	CFile theFile;
	TCHAR szFilters[] = _T("MyType Files (*.obs)|*.obs|All Files (*.*)|*.*||");

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);

	CFileDialog fileDlg(TRUE, _T("obs"), _T("*.obs"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	if (fileDlg.DoModal() == IDOK)
	{
		CString filepath = fileDlg.GetPathName();

		CString filename = fileDlg.GetFileName();


		std::string file_p = CT2A(filepath.GetString());
		std::string file_n = CT2A(filename.GetString());

		Box1Disply = (int)TVISIBLE::PRIVATE;
		GetAllVariables();
		OpenObservation(file_p);

		//Add a menu item for the newly opened file.
		updateOpenObsFileMenu();


	}

	Box1Disply = (int)TVISIBLE::OUTPUT;
	GetAllVariables();




}


void CRHMmainDlg::OnClickOnOpenFile(UINT ID)
{
	/* Use the map to find the name of the observation file that was clicked on */
	std::map<UINT, std::pair<std::string, std::string>>::iterator pos = this->openObsFiles->find(ID);

	/* Remove that observation file from the model. */
	CRHMmain* main = CRHMmain::getInstance();
	main->ObsFileClose(pos->second.first);

	/* Call the update method to rebuild the GUI */
	updateOpenObsFileMenu();
}


void CRHMmainDlg::OnCloseAllObservations()
{
	// TODO: Add your command handler code here
	CRHMmain* main = CRHMmain::getInstance();
	main->ObsCloseClick();

	updateOpenObsFileMenu();
}


void CRHMmainDlg::OnBuildConstruct()
{
	// TODO: Add your command handler code here


	CConstruct* build_form;
	std::map<std::string, ClassModule*>* all_module_list = CRHMmain::getInstance()->getAllmodules();

	build_form = new CConstruct();
	//build_form->UpdateData();

	//	build_form.listbox_all_modules
	//	build_form->listbox_all_modules = new CListBox();

	//build_form->listbox_all_modules.AddString(_T("test"));


	//CListBox *test = &build_form->listbox_all_modules;
	//AddStringListToListBox(test, all_module_list);

	INT_PTR nRet = build_form->DoModal();

	if (build_form->Execute) {
		InitModules();
		build_form->ReadBuildParameters(); // restore original parameters


		loadGuiComponents();

		//ReopenProject();
		//ReopenProject();
		//OpenObservation(defaultobservationpath);
	}

	//CRHMmain *test = CRHMmain::getInstance();
	//int c = test->AllVariables->Count;

	//update the tracking variable for the file name - Matt
	globFileName = defaultprojectpath.c_str();
}


void CRHMmainDlg::OnClearModules()
{
	CRHMmain * model = CRHMmain::getInstance();

	Global::OurModulesList->clear();
	model->SelectedVariables->clear();
	model->AllVariables->clear();
	Global::MapPars.clear();

	loadGuiComponents();
	updateSelectedVariablesListBox();
	

}


void CRHMmainDlg::OnBuildMacro()
{
	MacroEntryDlg* macroEntry;
	macroEntry = new MacroEntryDlg();

	if (macroEntry->DoModal() == IDOK)
	{
		CRHMmain* t = CRHMmain::getInstance();
		t->MacroClick();
		tchart.RemoveAllSeries();
	}
}


void CRHMmainDlg::OnClickOnOpenInitState()
{
	CRHMmain* main = CRHMmain::getInstance();

	CFile theFile;
	TCHAR szFilters[] = _T("MyType Files (*.int)|*.int |All Files (*.*)|*.*||");

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);

	CFileDialog fileDlg(TRUE, _T("int"), _T("*.int"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	if (fileDlg.DoModal() == IDOK)
	{
		CString folderPath = fileDlg.GetFolderPath();

		CString filename = fileDlg.GetFileName();

		main->OpenNameState = CT2A(folderPath);
		main->OpenStateFlag = true;

		updateOpenStateFileMenu();
	}

}


void CRHMmainDlg::CloseOpenInitFile()
{
	CRHMmain* main = CRHMmain::getInstance();

	main->OpenNameState = "";
	main->OpenStateFlag = false;

	updateOpenStateFileMenu();
}


void CRHMmainDlg::OnSaveState()
{
	CRHMmain* model = CRHMmain::getInstance();

	if (model->SaveStateFlag == true)
	{
		model->SaveStateFlag = false;
	}
	else
	{
		model->SaveStateFlag = true;

		if (model->SaveStateFileName == "")
		{
			std::string defaultSaveStateFile = GetCurrentDir();
			defaultSaveStateFile += "\\Final_State.int";
			model->SaveStateFileName = defaultSaveStateFile;
		}
	}

	updateOpenStateFileMenu();
}


void CRHMmainDlg::OnSaveStateTo()
{
	TCHAR szFilters[] = _T("MyType Files (*.int)|*.int|All Files (*.*)|*.*||");

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);

	CFileDialog fileDlg(FALSE, _T("int"), _T("*.int"),
		OFN_HIDEREADONLY, szFilters);

	if (fileDlg.DoModal() == IDOK)
	{
		CRHMmain* model = CRHMmain::getInstance();

		fileName = fileDlg.GetPathName();
		string filepath = CT2A(fileName.GetString());

		model->SaveStateFileName = filepath;

		model->SaveStateFlag = true;

		updateOpenStateFileMenu();
	}
}


void CRHMmainDlg::OnSaveStateAs()
{
	TCHAR szFilters[] = _T("MyType Files (*.int)|*.int|All Files (*.*)|*.*||");

	CRHMAboutBox* test;
	test = new CRHMAboutBox();

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);

	CFileDialog fileDlg(FALSE, _T("int"), _T("*.int"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	if (fileDlg.DoModal() == IDOK)
	{
		CRHMmain* model = CRHMmain::getInstance();

		fileName = fileDlg.GetPathName();
		string filepath = CT2A(fileName.GetString());

		model->SaveStateFileName = filepath;

		model->SaveStateFlag = true;

		model->SaveState();

		updateOpenStateFileMenu();
	}

}


void CRHMmainDlg::OnRunRunmodel()
{
	RunClickFunction();
	updateOpenStateFileMenu();
}

void CRHMmainDlg::OnExport()
{
	CRHMmain* model = CRHMmain::getInstance();

	if (model->getFinishedRun())
	{
		CExport exportDlg;
		exportDlg.DoModal();
	}
	else
	{
		CString text(L"Run must be completed before export can be performed.");
		MessageBox(text, MB_OK);
	}


	
}

void CRHMmainDlg::OnFlowdiagramsShowdiagram()
{
	// TODO: Add your command handler code here

	FlowDiagramDlg flowdiagram;
	flowdiagram.DoModal();

}


void CRHMmainDlg::OnHelpAbout()
{
	CRHMAboutBox aboutbox;
	aboutbox.DoModal();
}


void CRHMmainDlg::DecreaseHRUDimension()
{
	CString currentValue;
	CString newValue;
	int dimension = 0;

	GetDlgItemText(ID_HRU_DIM_DISPLAY, currentValue);
	dimension = _ttoi(currentValue);
	if (currentValue.Trim().GetLength() > 0)
	{
		if (dimension > 1)
		{
			dimension = _ttoi(currentValue) - 1;
			newValue.Format(_T("%d"), dimension);
			SetDlgItemText(ID_HRU_DIM_DISPLAY, newValue);
		}
	}
}


void CRHMmainDlg::IncreaseHRUDimension()
{
	CString currentValue;
	CString newValue;
	int dimension = 0;
	GetDlgItemText(ID_HRU_DIM_DISPLAY, currentValue);
	dimension = _ttoi(currentValue);
	if (currentValue.Trim().GetLength() > 0)
	{
		if (dimension < Global::maxhru)
		{
			dimension = _ttoi(currentValue) + 1;
			newValue.Format(_T("%d"), dimension);
			SetDlgItemText(ID_HRU_DIM_DISPLAY, newValue);
		}
	}
}


void CRHMmainDlg::DecreaseObsDimension()
{
	CString currentValue;
	CString newValue;
	int dimension = 0;

	GetDlgItemText(ID_OBS_DIM_DISPLAY, currentValue);
	dimension = _ttoi(currentValue);
	if (currentValue.Trim().GetLength() > 0)
	{
		if (dimension > 1)
		{
			dimension = _ttoi(currentValue) - 1;
			newValue.Format(_T("%d"), dimension);
			SetDlgItemText(ID_OBS_DIM_DISPLAY, newValue);
		}
	}
}


void CRHMmainDlg::IncreaseObsDimension()
{

	CString mode;
	GetDlgItemText(ID_OBS_LAY_DIM_LABEL, mode);

	if (mode == L"OBS")
	{
		CString currentValue;
		CString newValue;
		int dimension = 0;
		GetDlgItemText(ID_OBS_DIM_DISPLAY, currentValue);
		dimension = _ttoi(currentValue);
		if (currentValue.Trim().GetLength() > 0)
		{
			if (dimension < Global::maxobs)
			{
				dimension = _ttoi(currentValue) + 1;
				newValue.Format(_T("%d"), dimension);
				SetDlgItemText(ID_OBS_DIM_DISPLAY, newValue);
			}
		}
	}
	else if (mode == L"LAY")
	{
		int maxLayerInSelection = getMaxLayofSelection();

		CString currentValue;
		CString newValue;
		int dimension = 0;
		GetDlgItemText(ID_OBS_DIM_DISPLAY, currentValue);
		dimension = _ttoi(currentValue);
		if (currentValue.Trim().GetLength() > 0)
		{
			if (dimension < maxLayerInSelection)
			{
				dimension = _ttoi(currentValue) + 1;
				newValue.Format(_T("%d"), dimension);
				SetDlgItemText(ID_OBS_DIM_DISPLAY, newValue);
			}
		}
	}

}

void CRHMmainDlg::OnDblClkAllVarListBox()
{
	addVariablesToSelected();
	updateSelectedVariablesListBox();
}


void CRHMmainDlg::OnDblClkSelVarListBox()
{
	removeVariablesFromSelected();
	updateSelectedVariablesListBox();
}

void CRHMmainDlg::OnVariableSelectChange()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedIndex = listbox_all_variables.GetCurSel();
	CString selectedText;
	listbox_all_variables.GetText(selectedIndex, selectedText);
	CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
	std::string selectedString(pszConvertedAnsiString);

	std::map<std::string, ClassVar*>::iterator selectedVariable = model->AllVariables->find(selectedString);

	std::string helpString = selectedVariable->second->help;
	std::string unitsString = selectedVariable->second->units;
	std::string nameString = selectedVariable->second->name;

	std::string infoString = nameString + "  Units: " + unitsString + " Help: " + helpString;

	CString infoText(infoString.c_str());

	SetDlgItemText(ID_VAR_HELP_DISPLAY, (LPCTSTR)infoText);

	setDimensionSelectorToLay();
}


void CRHMmainDlg::OnDblClkAllObsListBox()
{
	addObservationsToSelected();
	updateSelectedObservationListBox();
}


void CRHMmainDlg::OnDblClkSelObsListBox()
{
	removeObservationsFromSelected();
	updateSelectedObservationListBox();
}


void CRHMmainDlg::OnObservationSelectChange()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedIndex = listbox_all_observations.GetCurSel();
	CString selectedText;
	listbox_all_observations.GetText(selectedIndex, selectedText);
	CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
	std::string selectedString(pszConvertedAnsiString);

	std::map<std::string, ClassVar*>::iterator selectedObservation = model->AllObservations->find(selectedString);

	std::string helpString = selectedObservation->second->help;
	std::string unitsString = selectedObservation->second->units;
	std::string nameString = selectedObservation->second->name;

	std::string infoString = nameString + "  Units: " + unitsString + " Help: " + helpString;

	CString infoText(infoString.c_str());

	SetDlgItemText(ID_OBS_HELP_DISPLAY, (LPCTSTR)infoText);
	
	setDimensionSelectorToObs();
}


LRESULT CRHMmainDlg::OpenAllVarCtxMenu(WPARAM, LPARAM)
{
	CMenu ctxMenu;
	ctxMenu.CreatePopupMenu();

	CString addText("Add");
	CString addArrayText("Add All HRUs");
	CString addLayersText("Add All Layers");
	CString addHRULayersText("Add All HRUs and Layers");

	ctxMenu.InsertMenu(0,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_ALL_VAR_ADD,
		(LPCTSTR)addText);

	ctxMenu.InsertMenu(1,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_ALL_VAR_ADD_ARRAY,
		(LPCTSTR)addArrayText);

	ctxMenu.InsertMenu(2,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_ALL_VAR_ADD_LAY_ARRAY,
		(LPCTSTR)addLayersText);

	ctxMenu.InsertMenu(3,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_ALL_VAR_ADD_HRU_LAY_ARRAY,
		(LPCTSTR)addHRULayersText);

	CWnd* wind = AfxGetMainWnd();
	POINT p;

	if (GetCursorPos(&p))
	{
		UINT result;

		if (result = ctxMenu.TrackPopupMenuEx(
			TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
			p.x, p.y, wind, 0))
		{
			if (result == ID_CTX_ALL_VAR_ADD)
			{
				addVariablesToSelected();
				updateSelectedVariablesListBox();
			}
			else if (result == ID_CTX_ALL_VAR_ADD_ARRAY)
			{
				addVariablesArrayToSelected();
				updateSelectedVariablesListBox();
			}
			else if (result == ID_CTX_ALL_VAR_ADD_LAY_ARRAY)
			{
				addVariablesLayerArrayToSelected();
				updateSelectedVariablesListBox();
			}
			else if (result == ID_CTX_ALL_VAR_ADD_HRU_LAY_ARRAY)
			{
				addVariablesHRULayerArrayToSelected();
				updateSelectedVariablesListBox();
			}
		}

	}

	return 0;
}


LRESULT CRHMmainDlg::OpenSelVarCtxMenu(WPARAM, LPARAM)
{
	CMenu ctxMenu;
	ctxMenu.CreatePopupMenu();

	CString removeText("Remove");

	ctxMenu.InsertMenu(0,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_SEL_VAR_REMOVE,
		(LPCTSTR)removeText);

	CWnd* wind = AfxGetMainWnd();
	POINT p;

	if (GetCursorPos(&p))
	{
		UINT result;

		if (result = ctxMenu.TrackPopupMenuEx(
			TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
			p.x, p.y, wind, 0))
		{
			if (result == ID_CTX_SEL_VAR_REMOVE)
			{
				removeVariablesFromSelected();
				updateSelectedVariablesListBox();
			}

		}

	}

	return 0;
}

LRESULT CRHMmainDlg::OpenAllObsCtxMenu(WPARAM, LPARAM)
{
	CMenu ctxMenu;
	ctxMenu.CreatePopupMenu();

	CString addText("Add");
	CString addArrayText("Add Array");
	CString applyFunctionText("Apply Function");

	ctxMenu.InsertMenu(0,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_ALL_OBS_ADD,
		(LPCTSTR)addText);

	ctxMenu.InsertMenu(1,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_ALL_OBS_ADD_ARRAY,
		(LPCTSTR)addArrayText);

	CMenu functionSubMenu;
	functionSubMenu.CreatePopupMenu();

	ctxMenu.InsertMenu(2,
		MF_BYPOSITION | MF_STRING | MF_POPUP,
		(UINT_PTR) functionSubMenu.GetSafeHmenu(),
		(LPCTSTR)applyFunctionText);

	CString totalText("Total");
	CString minText("Minimum");
	CString maxText("Maximum");
	CString avgText("Average");

	functionSubMenu.InsertMenu(0,
		MF_BYPOSITION | MF_STRING,
		ID_TOTAL_FUNCT,
		(LPCTSTR)totalText
	);

	functionSubMenu.InsertMenu(1,
		MF_BYPOSITION | MF_STRING,
		ID_MIN_FUNCT,
		(LPCTSTR)minText
	);

	functionSubMenu.InsertMenu(2,
		MF_BYPOSITION | MF_STRING,
		ID_MAX_FUNCT,
		(LPCTSTR)maxText
	);

	functionSubMenu.InsertMenu(3,
		MF_BYPOSITION | MF_STRING,
		ID_AVG_FUCNT,
		(LPCTSTR)avgText
	);


	CWnd* wind = AfxGetMainWnd();
	POINT p;

	if (GetCursorPos(&p))
	{
		UINT result;

		if (result = ctxMenu.TrackPopupMenuEx(
			TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
			p.x, p.y, wind, 0))
		{
			int savedSelection = this->function_drop_down.GetCurSel();

			switch (result)
			{
			case (ID_CTX_ALL_OBS_ADD):
				addObservationsToSelected();
				updateSelectedObservationListBox();
				break;
			case (ID_CTX_ALL_OBS_ADD_ARRAY):
				addObservationsArrayToSelected();
				updateSelectedObservationListBox();
				break;
			case (ID_TOTAL_FUNCT):
				this->function_drop_down.SetCurSel(1);
				addObservationsToSelected();
				updateSelectedObservationListBox();
				this->function_drop_down.SetCurSel(savedSelection);
				break;
			case (ID_MIN_FUNCT):
				this->function_drop_down.SetCurSel(2);
				addObservationsToSelected();
				updateSelectedObservationListBox();
				this->function_drop_down.SetCurSel(savedSelection);
				break;
			case (ID_MAX_FUNCT):
				this->function_drop_down.SetCurSel(3);
				addObservationsToSelected();
				updateSelectedObservationListBox();
				this->function_drop_down.SetCurSel(savedSelection);
				break;
			case (ID_AVG_FUCNT):
				this->function_drop_down.SetCurSel(4);
				addObservationsToSelected();
				updateSelectedObservationListBox();
				this->function_drop_down.SetCurSel(savedSelection);
				break;
			default:
				break;
			}
			
		}

	}

	return 0;
}


LRESULT CRHMmainDlg::OpenSelObsCtxMenu(WPARAM, LPARAM)
{
	CMenu ctxMenu;
	ctxMenu.CreatePopupMenu();

	CString removeText("Remove");

	ctxMenu.InsertMenu(0,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_SEL_OBS_REMOVE,
		(LPCTSTR)removeText);

	CWnd* wind = AfxGetMainWnd();
	POINT p;

	if (GetCursorPos(&p))
	{
		UINT result;

		if (result = ctxMenu.TrackPopupMenuEx(
			TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
			p.x, p.y, wind, 0))
		{
			if (result == ID_CTX_SEL_OBS_REMOVE)
			{
				removeObservationsFromSelected();
				updateSelectedObservationListBox();
			}

		}

	}

	return 0;
}


void CRHMmainDlg::OnTimebaseChange()
{
	int currentSelection = timebase_drop_down.GetCurSel();

	/* If the current selection is water year (3) */
	if (currentSelection == 3)
	{
		GetDlgItem(ID_WATER_YEAR_LABEL)->ShowWindow(SW_SHOW);
		GetDlgItem(ID_WATER_YEAR_DROP_DOWN)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(ID_WATER_YEAR_LABEL)->ShowWindow(SW_HIDE);
		GetDlgItem(ID_WATER_YEAR_DROP_DOWN)->ShowWindow(SW_HIDE);
	}

	switch (currentSelection)
	{
	case (0):
		this->TBase = TimeBase::DAILY;
		break;
	case (1):
		this->TBase = TimeBase::MONTHLY;
		break;
	case (2):
		this->TBase = TimeBase::CALENDAR_YEAR;
		break;
	case (3):
		this->TBase = TimeBase::WATER_YEAR;
		break;
	case (4):
		this->TBase = TimeBase::ALL;
		break;
	default:
		break;
	}

}


void CRHMmainDlg::OnWaterYearChange()
{
	int currentSelection = this->water_year_drop_down.GetCurSel();
	this->water_year_month = currentSelection + 1;
}


void CRHMmainDlg::OnStartDateChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	COleDateTime dateTime;

	StartDatePicker.GetTime(dateTime);

	CRHMmain::getInstance()->setStartDate(dateTime.m_dt);
}

void CRHMmainDlg::OnEndDateChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	COleDateTime dateTime;

	EndDatePicker.GetTime(dateTime);

	CRHMmain::getInstance()->setEndDate(dateTime.m_dt);
}


void CRHMmainDlg::OnClickFlipTicks()
{
	CSeries series;
	bool active;

	int count = tchart.get_SeriesCount();

	for (int i = 0; i < count; i++)
	{
		series = tchart.Series(i);
		active = series.get_Active();
		series.put_Active(!active);
	}
}

LRESULT CRHMmainDlg::OnLeftClickFlipTicks(WPARAM, LPARAM)
{
	CRHMmain* model = CRHMmain::getInstance();
	CSeries series;
	bool active;

	int count = tchart.get_SeriesCount();

	for (int i = 0; i < count; i++)
	{
		series = tchart.Series(i);
		CString title = series.get_LegendTitle();
		CT2CA convert(title); //Intermediary to convert CString to std::string
		std::string titleString(convert);
		
		std::list<std::pair<std::string, TSeries*>> * selectedObservations = model->getSelectedObservations();
		for (
			std::list<std::pair<std::string, TSeries*>>::iterator it = selectedObservations->begin();
			it != selectedObservations->end();
			it++
			)
		{
			if (it->first == titleString)
			{
				active = series.get_Active();
				series.put_Active(!active);
				break;
			}
		}

	}

	return 0;
}

LRESULT CRHMmainDlg::OnRightClickFlipTicks(WPARAM, LPARAM)
{
	CRHMmain* model = CRHMmain::getInstance();
	CSeries series;
	bool active;

	int count = tchart.get_SeriesCount();

	for (int i = 0; i < count; i++)
	{
		series = tchart.Series(i);
		CString title = series.get_LegendTitle();
		CT2CA convert(title); //Intermediary to convert CString to std::string
		std::string titleString(convert);

		std::list<std::pair<std::string, ClassVar*>>* selectedVariables = model->getSelectedVariables();
		for (
			std::list<std::pair<std::string, ClassVar*>>::iterator it = selectedVariables->begin();
			it != selectedVariables->end();
			it++
			)
		{
			if (it->first == titleString)
			{
				active = series.get_Active();
				series.put_Active(!active);
				break;
			}
		}

	}

	return 0;
}

void CRHMmainDlg::addVariablesToSelected()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_all_variables.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_all_variables.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		bool dimensionSelected = true;
		std::string seriesTitle = "";

		CString selectedText;
		listbox_all_variables.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		CString hruDimensionText;
		int hruDimension = 1;
		GetDlgItemText(ID_HRU_DIM_DISPLAY, hruDimensionText);
		hruDimension = _ttoi(hruDimensionText);

		CString layDimensionText;
		int layDimension = 0;
		GetDlgItemText(ID_OBS_DIM_DISPLAY, layDimensionText);
		layDimension = _ttoi(layDimensionText);

		/*Get the variable from the model*/
		ClassVar* varVar = model->AllVariables->find(selectedString)->second;

		if (varVar->lay == 0)
		{
			seriesTitle = selectedString + "(" + to_string(hruDimension) + ")";

			dimensionSelected = variableIsSelected(seriesTitle);

			while (dimensionSelected && hruDimension < Global::maxhru)
			{
				hruDimension++;
				seriesTitle = selectedString + "(" + to_string(hruDimension) + ")";
				dimensionSelected = variableIsSelected(seriesTitle);
			}
		}
		else if (varVar->lay > 0)
		{
			if (layDimension <= varVar->lay)
			{
				seriesTitle = selectedString + "(" + to_string(hruDimension) +"," + to_string(layDimension)+ ")";

				dimensionSelected = variableIsSelected(seriesTitle);

				while (dimensionSelected && hruDimension < Global::maxhru)
				{
					hruDimension++;
					seriesTitle = selectedString + "(" + to_string(hruDimension) + "," + to_string(layDimension) + ")";
					dimensionSelected = variableIsSelected(seriesTitle);
				}
			}
		}

		/*Add the observation to the selected observations*/
		if (dimensionSelected == false)
		{
			model->SelectedVariables->push_back(std::pair<std::string, ClassVar*>(seriesTitle, varVar));
		}

	}

	delete[] selectedIndicies;
}


void CRHMmainDlg::addVariablesArrayToSelected()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_all_variables.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_all_variables.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_all_variables.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		CString layDimensionText;
		int layDimension = 0;
		GetDlgItemText(ID_OBS_DIM_DISPLAY, layDimensionText);
		layDimension = _ttoi(layDimensionText);

		/*Get the variable from the model*/
		ClassVar* varVar = model->AllVariables->find(selectedString)->second;


		if (varVar->lay == 0)
		{
			for (int i = 1; i <= Global::maxhru; i++)
			{
				std::string varTitle = selectedString + "(" + to_string(i) + ")";

				bool dimensionSelected = variableIsSelected(varTitle);

				/*Add the variable to the selected variables*/
				if (dimensionSelected == false)
				{
					model->SelectedVariables->push_back(std::pair<std::string, ClassVar*>(varTitle, varVar));
				}
			}
		}
		else
		{
			for (int i = 1; i <= Global::maxhru; i++)
			{
				std::string varTitle = selectedString + "(" + to_string(i) + "," + to_string(layDimension) + ")";

				bool dimensionSelected = variableIsSelected(varTitle);

				/*Add the variable to the selected variables*/
				if (dimensionSelected == false)
				{
					model->SelectedVariables->push_back(std::pair<std::string, ClassVar*>(varTitle, varVar));
				}
			}
		}

		
	}

	delete[] selectedIndicies;
}

void CRHMmainDlg::addVariablesLayerArrayToSelected()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_all_variables.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_all_variables.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_all_variables.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		CString hruDimensionText;
		int hruDimension = 1;
		GetDlgItemText(ID_HRU_DIM_DISPLAY, hruDimensionText);
		hruDimension = _ttoi(hruDimensionText);

		/*Get the variable from the model*/
		ClassVar* varVar = model->AllVariables->find(selectedString)->second;

		if (varVar->lay == 0)
		{
			std::string varTitle = selectedString + "(" + to_string(hruDimension) + ")";

			bool dimensionSelected = variableIsSelected(varTitle);

			/*Add the variable to the selected variables*/
			if (dimensionSelected == false)
			{
				model->SelectedVariables->push_back(std::pair<std::string, ClassVar*>(varTitle, varVar));
			}
			
		}
		else
		{
			for (int j = 1; j <= varVar->lay; j++)
			{
				std::string varTitle = selectedString + "(" + to_string(hruDimension) + "," + to_string(j) + ")";

				bool dimensionSelected = variableIsSelected(varTitle);

				/*Add the variable to the selected variables*/
				if (dimensionSelected == false)
				{
					model->SelectedVariables->push_back(std::pair<std::string, ClassVar*>(varTitle, varVar));
				}
			}
		}

	}

	delete[] selectedIndicies;
}

void CRHMmainDlg::addVariablesHRULayerArrayToSelected()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_all_variables.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_all_variables.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		bool dimensionSelected = true;
		std::string seriesTitle = "";

		CString selectedText;
		listbox_all_variables.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		/*Get the variable from the model*/
		ClassVar* varVar = model->AllVariables->find(selectedString)->second;

		if (varVar->lay == 0)
		{
			for (int j = 1; j <= Global::maxhru; j++)
			{
				seriesTitle = selectedString + "(" + to_string(j) + ")";

				dimensionSelected = variableIsSelected(seriesTitle);
				
				if (dimensionSelected == false)
				{
					model->SelectedVariables->push_back(std::pair<std::string, ClassVar*>(seriesTitle, varVar));
				}

			}

		}
		else if (varVar->lay > 0)
		{

			for (int j = 1; j <= Global::maxhru; j++)
			{
				for (int k = 1; k <= varVar->lay; k++)
				{
					seriesTitle = selectedString + "(" + to_string(j) + "," + to_string(k) + ")";

					dimensionSelected = variableIsSelected(seriesTitle);

					if (dimensionSelected == false)
					{
						model->SelectedVariables->push_back(std::pair<std::string, ClassVar*>(seriesTitle, varVar));
					}
				}
			}

		}

	}

	delete[] selectedIndicies;
}

void CRHMmainDlg::addObservationsToSelected()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_all_observations.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_all_observations.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_all_observations.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		CString currentValue;
		int dimension = 1;
		GetDlgItemText(ID_OBS_DIM_DISPLAY, currentValue);
		dimension = _ttoi(currentValue);

		/*Get the variable from the model*/
		ClassVar* obsVar = model->AllObservations->find(selectedString)->second;

		/* Retreive the value of the function selector to determine the suffix */
		int functValue = function_drop_down.GetCurSel();
		std::string suffix;

		switch (functValue)
		{
		case (0):
			// Observation;
			suffix = "";
			break;
		case (1):
			// Total
			suffix = "_Tot";
			break;
		case (2):
			// Minimum
			suffix = "_Min";
			break;
		case (3):
			// Maximum
			suffix = "_Max";
			break;
		case (4):
			// Average
			suffix = "_Avg";
			break;
		default:
			suffix = "";
			break;
		}

		std::string seriesTitle = selectedString + "(" + to_string(dimension) + ")" + suffix;

		bool dimensionSelected = observationIsSelected(seriesTitle);

		while (dimensionSelected && dimension < Global::maxobs)
		{
			dimension++;
			seriesTitle = selectedString + "(" + to_string(dimension) + ")";
			dimensionSelected = observationIsSelected(seriesTitle);
		}

		/*Add the observation to the selected observations*/
		if (dimensionSelected == false)
		{
			TSeries* cdSeries = NULL;

			if (obsVar->FileData->Times == NULL)
			{
				cdSeries = new TSeries();
			}
			else
			{
				cdSeries = new TSeries();
			}
			cdSeries->Tag = obsVar;
			cdSeries->Title = seriesTitle;
			model->SelectedObservations->push_back(std::pair<std::string, TSeries*>(seriesTitle, cdSeries));
		}

	}

	delete[] selectedIndicies;
}


void CRHMmainDlg::addObservationsArrayToSelected()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_all_observations.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_all_observations.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_all_observations.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		/*Get the variable from the model*/
		ClassVar* obsVar = model->AllObservations->find(selectedString)->second;

		for (int i = 1; i <= Global::maxobs; i++)
		{
			std::string seriesTitle = selectedString + "(" + to_string(i) + ")";

			bool dimensionSelected = observationIsSelected(seriesTitle);

			/*Add the observation to the selected observations*/
			if (dimensionSelected == false)
			{
				TSeries* cdSeries = NULL;

				if (obsVar->FileData->Times == NULL)
				{
					cdSeries = new TSeries();
				}
				else
				{
					cdSeries = new TSeries();
				}
				cdSeries->Tag = obsVar;
				cdSeries->Title = seriesTitle;
				model->SelectedObservations->push_back(std::pair<std::string, TSeries*>(seriesTitle, cdSeries));
			}
		}
	}

	delete[] selectedIndicies;
}


void CRHMmainDlg::removeVariablesFromSelected()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_sel_variables.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_sel_variables.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_sel_variables.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		/*Remove observation from the model*/
		std::list<std::pair<std::string, ClassVar*>>* listOfSelectedVariables = model->SelectedVariables;
		for (
			std::list<std::pair<std::string, ClassVar*>>::iterator it = listOfSelectedVariables->begin();
			it != listOfSelectedVariables->end();
			it++
			)
		{
			if (it->first == selectedString)
			{
				listOfSelectedVariables->erase(it);
				break;
			}
		}

	}

	delete[] selectedIndicies;
}


void CRHMmainDlg::removeObservationsFromSelected()
{
	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_sel_observations.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_sel_observations.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_sel_observations.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		/*Remove observation from the model*/
		std::list<std::pair<std::string, TSeries*>>* selectedObservations = model->SelectedObservations;
		for (
			std::list<std::pair<std::string, TSeries*>>::iterator it = selectedObservations->begin();
			it != selectedObservations->end();
			it++
			)
		{
			if (it->first == selectedString)
			{
				delete(it->second);
				selectedObservations->erase(it);
				break;
			}
		}

	}

	delete[] selectedIndicies;
}


bool CRHMmainDlg::variableIsSelected(std::string seriesTitle)
{
	CRHMmain* model = CRHMmain::getInstance();

	/*Check that the model doesn't already have this variable selected*/
	bool alreadyInModel = false;
	for (
		std::list<std::pair<std::string, ClassVar*>>::iterator it = model->SelectedVariables->begin();
		it != model->SelectedVariables->end();
		it++
		)
	{
		if (it->first == seriesTitle)
		{
			alreadyInModel = true;
		}
	}

	return alreadyInModel;
}


bool CRHMmainDlg::observationIsSelected(std::string seriesTitle)
{
	CRHMmain* model = CRHMmain::getInstance();

	/*Check that the model doesn't already have this observation selected*/
	bool alreadyInModel = false;
	for (
		std::list<std::pair<std::string, TSeries*>>::iterator it = model->SelectedObservations->begin();
		it != model->SelectedObservations->end();
		it++
		)
	{
		if (it->first == seriesTitle)
		{
			alreadyInModel = true;
		}
	}

	return alreadyInModel;
}



void CRHMmainDlg::SetItemsToListBox(int listboxid, std::vector<std::string>* list)
{
	CListBox* listbox = (CListBox*)GetDlgItem(listboxid);
	size_t count = list->size();

	for (size_t i = 0; i < count; i++)
	{
		string str = list->at(i);
		CString cstr(str.c_str());
		listbox->AddString(cstr);
	}
}


std::list<std::pair<std::string, ClassVar*>>* CRHMmainDlg::GetSelectedVariables()
{
	CRHMmain* t = CRHMmain::getInstance();
	std::list<std::pair<std::string, ClassVar*>>* list = new std::list<std::pair<std::string, ClassVar*>>();
	CListBox* listbox = (CListBox*)GetDlgItem(ID_SEL_VAR_LIST_BOX);

	int itemcount = listbox->GetCount();
	for (int i = 0; i < itemcount; i++)
	{
		CString cstr;
		listbox->GetText(i, cstr);
		CT2A str(cstr);
		string s = str;

		ClassVar* obj = t->GetObjectOfVariable(s);
		list->push_back(std::pair<std::string, ClassVar*>(s, obj));
	}
	return list;
}


std::list<std::pair<std::string, TSeries*>>* CRHMmainDlg::GetSelectedObservations()
{
	CRHMmain* t = CRHMmain::getInstance();
	std::list<std::pair<std::string, TSeries*>>* list = new std::list<std::pair<std::string, TSeries*>>();
	CListBox* listbox = (CListBox*)GetDlgItem(ID_SEL_OBS_LIST_BOX);

	int itemcount = listbox->GetCount();
	for (int i = 0; i < itemcount; i++)
	{
		CString cstr;
		listbox->GetText(i, cstr);
		CT2A str(cstr);
		string s = str;

		//list->Add(s);
		ClassVar* var = t->GetObjectOfObservation(s);
		TSeries* obj = new TSeries();
		obj->Tag = var;
		obj->Title = s;

		list->push_back(std::pair<std::string, TSeries*>(s, obj));
	}
	return list;
}


void HruNameClick() {

	CRHMmain * test = CRHMmain::getInstance();

	MapPar::iterator itPar;
	ClassPar *newPar;
	int Hru; 
	int Lay;

	if (!test->ListHruNames) {

		test->ListHruNames = new std::vector<std::string>;
		test->MapGrpNames = new MapstrSS;

		if ((itPar = Global::MapPars.find("basin basin_name")) != Global::MapPars.end()) 
		{
			newPar = (*itPar).second;
			test->ListHruNames->push_back(newPar->Strings->at(0));
		}
		else
			test->ListHruNames->push_back("Basin");

		if ((itPar = Global::MapPars.find("basin hru_names")) != Global::MapPars.end()) {
			newPar = (*itPar).second;

			for (size_t ii = 0; ii < newPar->Strings->size(); ++ii)
			{
				test->ListHruNames->push_back(newPar->Strings->at(ii));
			}
		}
		else {
			for (int ii = 0; ii < Global::nhru; ++ii)
				test->ListHruNames->push_back("hru" + to_string(ii));
		}

		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
			modIt != Global::OurModulesList->end(); 
			modIt++
			) 
		{
			ClassModule* Mod = modIt->second;
			string S = modIt->first;

			if (Mod->GroupCnt > 0 || Mod->StructCnt > 0) {

				if (Mod->GroupCnt > 0) {
					string AA;
					Common::GroupEnding(AA, Mod->GroupCnt);
					Pairstr Item = Pairstr(AA.c_str(), ('@' + Mod->Name).c_str());
					test->MapGrpNames->insert(Item);
				}
				else if (Mod->StructCnt > 0) {
					string AA;
					Common::GroupEnding(AA, Mod->GroupCnt);
					Pairstr Item = Pairstr(AA.c_str(), ('@' + Mod->Name).c_str());
					test->MapGrpNames->insert(Item);
				}
			}
		}

		/*
		* Iterate through the map of selected varablesand calculate what their keys should be updated to
		* map these keys to the same ClassVar* and then replace SelectedVariables with the new Map.
		*/
		std::list<std::pair<std::string, ClassVar*>> * SelectedVariablesUpdated = new std::list<std::pair<std::string, ClassVar*>>();
		for (std::list<std::pair<std::string, ClassVar*>>::iterator selectedVariablesIt = test->SelectedVariables->begin();
			selectedVariablesIt != test->SelectedVariables->end();
			selectedVariablesIt++) 
		{
			string S = selectedVariablesIt->first;
			ClassVar *thisVar = selectedVariablesIt->second;

			test->HruNames = false;
			S = test->ExtractHruLay(S, Hru, Lay);

			test->HruNames = true;
			S = test->BuildHru(S, Hru, thisVar->dimen);

			if (Lay)
			{
				S = test->BuildLay(S, Lay);
			}

			int Indx = S.find("@"); // Insert Group & Struct names
			if (Indx) 
			{
				MapstrSS::iterator it;
				if ((it = test->MapGrpNames->find(S.substr(Indx, 2))) != test->MapGrpNames->end()) {
					string NewName = (*it).second;
					S.replace(Indx, 2, "");
					S.insert(Indx, NewName);
				}
			}

			SelectedVariablesUpdated->push_back(std::pair<std::string, ClassVar*>(S, thisVar));
		}
		delete test->SelectedVariables;
		test->setSelectedVariables(SelectedVariablesUpdated);


	}
	else { // currently using HRU names

		/*
		* Iterate through the map of selected varablesand calculate what their keys should be updated to
		* map these keys to the same ClassVar* and then replace SelectedVariables with the new Map.
		*/
		std::list<std::pair<std::string, ClassVar*>> * SelectedVariablesUpdated = new std::list<std::pair<std::string, ClassVar*>>();
		for (std::list<std::pair<std::string, ClassVar*>>::iterator selectedVariableIt = test->SelectedVariables->begin();
			selectedVariableIt != test->SelectedVariables->end();
			selectedVariableIt++) 
		{

			string S = selectedVariableIt->first;

			test->HruNames = true;
			S = test->ExtractHruLay(S, Hru, Lay);

			test->HruNames = false;
			S = test->BuildHru(S, Hru, TDim::NHRU);  // fill parameter

			if (Lay)
				S = test->BuildLay(S, Lay);

			int Indx = S.find("@");
			if (Indx) { // group or structure name
				MapstrSS::iterator it;
				for (it = test->MapGrpNames->begin(); it != test->MapGrpNames->end(); ++it) {
					int pos = S.find((*it).second);
					if (pos) { // found name
						string NewName = (*it).first;
						string Name = (*it).second;
						int Len = Name.length();
						int End = S.find("(");
						if (End - pos == Len) { // correct length
							S.replace(pos, Len, "");
							S.insert(pos, NewName);
							break;
						}
					}
				}
			}
			SelectedVariablesUpdated->push_back(std::pair<std::string, ClassVar*>(S, selectedVariableIt->second));
		}
		delete test->SelectedVariables;
		test->setSelectedVariables(SelectedVariablesUpdated);

		delete test->ListHruNames;
		test->ListHruNames = NULL;
		delete test->MapGrpNames;
		test->MapGrpNames = NULL;
	}

}


LRESULT CRHMmainDlg::OnAutoRunMessage(WPARAM, LPARAM)
{
	this->RunClickFunction();
	return 0;
}

void CRHMmainDlg::setDimensionSelectorToObs()
{
	SetDlgItemText(ID_OBS_LAY_DIM_LABEL, L"OBS");
	CString currentValue;
	int dimension = 0;
	GetDlgItemText(ID_OBS_DIM_DISPLAY, currentValue);
	dimension = _ttoi(currentValue);
	if (currentValue.Trim().GetLength() > 0)
	{
		if (dimension > Global::maxobs)
		{
			SetDlgItemText(ID_OBS_DIM_DISPLAY, L"1");
		}
	}
}


void CRHMmainDlg::setDimensionSelectorToLay()
{
	int maxLayInSelection = getMaxLayofSelection();

	SetDlgItemText(ID_OBS_LAY_DIM_LABEL, L"LAY");
	CString currentValue;
	int dimension = 0;
	GetDlgItemText(ID_OBS_DIM_DISPLAY, currentValue);
	dimension = _ttoi(currentValue);
	if (currentValue.Trim().GetLength() > 0)
	{
		if (dimension > maxLayInSelection)
		{
			SetDlgItemText(ID_OBS_DIM_DISPLAY, L"1");
		}
	}

}


int CRHMmainDlg::getMaxLayofSelection()
{
	int maxLayInSelection = 0;

	CRHMmain* model = CRHMmain::getInstance();

	int selectedCount = listbox_all_variables.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_all_variables.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_all_variables.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		std::map<std::string, ClassVar*>::iterator selected = model->AllVariables->find(selectedString);

		int layers = selected->second->lay;

		if (layers > maxLayInSelection)
		{
			maxLayInSelection = layers;
		}
	}

	return maxLayInSelection;
}