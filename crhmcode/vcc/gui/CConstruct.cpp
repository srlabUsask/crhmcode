#include "CConstruct.h"
#include "CConstructCore.h"

IMPLEMENT_DYNAMIC(CConstruct, CDialog)

CConstruct::CConstruct(CWnd* pParent /*=nullptr*/)
	: CDialog(CONSTRUCT_DLG, pParent)
{

}

CConstruct::~CConstruct()
{
}

void CConstruct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_ALL_MODS_LIST_BOX, listbox_available_modules);
	listbox_available_modules.setMessageCode(UWM_OPEN_CTX_AVAILABLE_MODS);
	DDX_Control(pDX, ID_SEL_MODS_LIST_BOX, listbox_selected_modules);
	listbox_selected_modules.setMessageCode(UWM_OPEN_CTX_SELECTED_MODS);
	DDX_Control(pDX, ID_MODULE_FILTER_BASIC, module_filter_basic);
	DDX_Control(pDX, ID_MODULE_FILTER_MACRO, module_filter_macro);
	DDX_Control(pDX, ID_MODULE_FILTER_ADVANCED, module_filter_advanced);
	DDX_Control(pDX, ID_MODULE_FILTER_SUPPORT, module_filter_support);
	DDX_Control(pDX, ID_MODULE_FILTER_CUSTOM, module_filter_custom);
	DDX_Control(pDX, ID_MODULE_FILTER_PROTOTYPE, module_filter_prototype);
	DDX_Control(pDX, ID_MODULE_FILTER_OBSOLETE, module_filter_obsolete);
	DDX_Control(pDX, IDC_LIST3, listcontrol);
	DDX_Control(pDX, ID_MAX_HRU_SPIN, max_HRU_spin);
	DDX_Control(pDX, ID_MAX_LAYER_SPIN, max_layer_spin);
}


BEGIN_MESSAGE_MAP(CConstruct, CDialog)
	//Buttons
	ON_BN_CLICKED(ID_CONSTRUCT_CHECK_BUTTON, &CConstruct::OnClkCheckButton)
	ON_BN_CLICKED(ID_CONSTRUCT_BUILD_BUTTON, &CConstruct::OnClkBuildButton)
	ON_BN_CLICKED(ID_CONSTRUCT_CANCEL_BUTTON, &CConstruct::OnClkCancelButton)
	//List Boxes
	ON_LBN_SELCHANGE(ID_ALL_MODS_LIST_BOX, &CConstruct::OnSelChangeAllModsListBox)
	ON_MESSAGE(UWM_OPEN_CTX_AVAILABLE_MODS, &CConstruct::OpenAvailableModsCtxMenu)
	ON_LBN_SELCHANGE(ID_SEL_MODS_LIST_BOX, &CConstruct::OnSelChangeSelModsListBox)
	ON_MESSAGE(UWM_OPEN_CTX_SELECTED_MODS, &CConstruct::OpenSelectedModsCtxMenu)
	//Module Filters
	ON_BN_CLICKED(ID_MODULE_FILTER_BASIC, &CConstruct::OnClkModuleFilterBasic)
	ON_BN_CLICKED(ID_MODULE_FILTER_MACRO, &CConstruct::OnClkModuleFilterMacro)
	ON_BN_CLICKED(ID_MODULE_FILTER_ADVANCED, &CConstruct::OnClkModuleFilterAdvanced)
	ON_BN_CLICKED(ID_MODULE_FILTER_SUPPORT, &CConstruct::OnClkModuleFilterSupport)
	ON_BN_CLICKED(ID_MODULE_FILTER_CUSTOM, &CConstruct::OnClkModuleFilterCustom)
	ON_BN_CLICKED(ID_MODULE_FILTER_PROTOTYPE, &CConstruct::OnClkModuleFilterPrototype)
	ON_BN_CLICKED(ID_MODULE_FILTER_OBSOLETE, &CConstruct::OnClkModuleFilterObsolete)




	//ON_NOTIFY(UDN_DELTAPOS, ID_MAX_HRU_SPIN, &CConstruct::OnMaxHRUSpinClick)


	ON_BN_CLICKED(IDC_BUTTON8, &CConstruct::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON1, &CConstruct::OnBnClickedButton1)
	
END_MESSAGE_MAP()


// CConstruct message handlers



BOOL CConstruct::OnInitDialog()
{
	CDialog::OnInitDialog();

	max_HRU_spin.SetRange(1, SHORT_MAX);
	if (Global::maxhru > 0)
	{
		max_HRU_spin.SetPos(Global::maxhru);
	}
	else 
	{
		max_HRU_spin.SetPos(1);
	}
	max_layer_spin.SetRange(1, SHORT_MAX);
	if (Global::maxlay > 0)
	{
		max_layer_spin.SetPos(Global::maxlay);
	}
	else
	{
		max_layer_spin.SetPos(1);
	}
	

	LoadAllModules();
	FormActivate();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CConstruct::LoadAllModules()
{
	listbox_available_modules.ResetContent();
	std::map<std::string, ClassModule *> * all_modules = CRHMmain::getInstance()->getAllmodules();

	for (
		std::map<std::string, ClassModule *>::iterator modIt = all_modules->begin(); 
		modIt != all_modules->end();
		modIt++
		) 
	{
		//string s = variables->Strings[ii];
		std::string s = modIt->first;
		CString c_all_modules(s.c_str());
		listbox_available_modules.AddString(c_all_modules);
	}
}



bool CConstruct::ModuleIsSelected(CString cstr)
{
	CString cstr1;
	for (int i = 0; i < listbox_selected_modules.GetCount(); i++)
	{
		listbox_selected_modules.GetText(i, cstr1);
		if (cstr == cstr1) 
		{ 
			return true; 
		}
	}

	return false;
}


void CConstruct::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here

	CString cstr;

	int sel = 0;// = listbox_all_modules.GetCurSel();

	//listbox_all_modules.GetText(index, cstr);
	//listbox_selected_modules.AddString(cstr);

	
	for (size_t i = 0; i < AvailableModules->size(); i++)
	{
		sel = listbox_available_modules.GetSel(i);
		if (sel == 1)
		{
			listbox_available_modules.GetText(i, cstr);

			if (ModuleIsSelected(cstr) == 0)
			{
				listbox_selected_modules.AddString(cstr);
				SelectedModules->push_back(std::pair<std::string, ClassModule *>(AvailableModules->at(i).first, AvailableModules->at(i).second));				
			}
			listbox_available_modules.SetSel(i, false);
		}
	}
}



void CConstruct::RemoveSelectedModule()
{
	CString cstr;

	int c = SelectedModules->size();
	for (int i = 0; i < c; i++)
	{
		int sel = listbox_selected_modules.GetSel(i);
		if (sel == 1)
		{
			listbox_selected_modules.GetText(i, cstr);

			listbox_selected_modules.DeleteString(i);
			CT2A s(cstr);
			string str = s;

			
			for (size_t SelectedModit = 0; SelectedModit < SelectedModules->size(); SelectedModit++)
			{
				if (SelectedModules->at(SelectedModit).first == str)
				{
					SelectedModules->erase(SelectedModules->begin() + SelectedModit);
					break; //Need to break out to ensure only the first instance is removed to emulate pervious behavior
				}
			}

		}
	}
}


void CConstruct::AddToAvailableModules(string str, ClassModule * obj)
{
	AvailableModules->push_back(std::pair<std::string, ClassModule *>(str, obj));
	CString cstr(str.c_str());
	listbox_available_modules.AddString((LPCTSTR)cstr);
}


void CConstruct::AddToSelectedModules(string str, ClassModule * obj)
{
	
	SelectedModules->push_back(std::pair<std::string, ClassModule*>(str, obj));

	//Check if module has a variation selected.
	if (obj->variation != 0)
	{
		unsigned short variationChar = (unsigned short) (log(obj->variation) / log(2) + 1);
		str = str + "#" + std::to_string(variationChar);
	}
	

	
	CString cstr(str.c_str());
	listbox_selected_modules.AddString((LPCTSTR)cstr);
	string S = str;
}


//core functionality
void CConstruct::FormActivate()
{
	//StatusBar1->SimpleText = "";
	//StatusBar1->SimplePanel = true;

	listbox_available_modules.ResetContent();

	//for (int ii = 0; ii < CheckListBox1->Count; ++ii)
		//CheckListBox1->Checked[ii] = false;
	module_filter_basic.SetCheck(0);
	module_filter_macro.SetCheck(0);
	module_filter_advanced.SetCheck(0);
	module_filter_custom.SetCheck(0);
	module_filter_obsolete.SetCheck(0);
	module_filter_prototype.SetCheck(0);
	module_filter_support.SetCheck(0);

	//Label3->Caption = "";

	Mapstr2 MapAKACopy;
	MapAKACopy = Global::MapAKA; // save AKA to restore if no rebuild

	AKAselectiveDelete(); // deletes all AKAs but "OBSR" and "OBSF"

	Global::Mapgetvar.clear();
	Global::Mapputvar.clear();
	Global::Mapreadvar.clear();
	Global::Mapdeclvar.clear();
	Global::Mapdeclstat.clear();
	Global::Mapdeclpar.clear();
	Global::Mapdeclobs.clear();

	TBuild TempB = Global::BuildFlag;
	Global::BuildFlag = TBuild::BUILD; // default value


	for (
		std::map<std::string, ClassModule * >::iterator modIt = Global::AllModulesList->begin(); 
		modIt != Global::AllModulesList->end(); 
		modIt++
		) 
	{ 

		ClassModule * thisModule = modIt->second;
		thisModule->variation_max = 0;

		unsigned short Temp = thisModule->variation;
		unsigned short Temp2 = thisModule->variation_set;
		thisModule->variation_set = 0;
		thisModule->variation = 0;
		thisModule->decl();
		thisModule->variation = Temp;
		thisModule->variation_set = Temp2;

		if (thisModule->variation > 0)
			thisModule->hh = (long) (log(thisModule->variation) / log(2) + 1); // set to current variation
		else
			thisModule->hh = 0;
	}

	Global::OBS_AS_IS = 0; // Quinton module sets it
	Global::WQ_prj = false; // Set for WQ project
	listbox_selected_modules.ResetContent();

	if (Global::OurModulesList->size())
	{
		ModifyBuild = true;
	}
	else {
		ModifyBuild = false;
		module_filter_basic.SetCheck(1);
	}


	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt != Global::OurModulesList->end(); 
		modIt++
		) // fill ListBox2
	{ 
		//CheckListBox1->Checked[((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl] = true;

		if (modIt->second->Lvl == LMODULE::BASIC )
		{
			module_filter_basic.SetCheck(1);
		}
		if (modIt->second->Lvl == LMODULE::MACRO)
		{ 
			module_filter_macro.SetCheck(1); 
		}
		if (modIt->second->Lvl == LMODULE::ADVANCE)
		{
			module_filter_advanced.SetCheck(1); 
		}
		if (modIt->second->Lvl == LMODULE::SUPPORT)
		{ 
			module_filter_support.SetCheck(1); 
		}
		if (modIt->second->Lvl == LMODULE::CUSTOM)
		{ 
			module_filter_custom.SetCheck(1); 
		}
		if (modIt->second->Lvl == LMODULE::PROTO)
		{ 
			module_filter_prototype.SetCheck(1); 
		}
		if (modIt->second->Lvl == LMODULE::OBSOL)
		{ 
			module_filter_obsolete.SetCheck(1); 
		}

		AddToSelectedModules(modIt->first, modIt->second );
		//ListBox2->AddObject(Global::OurModulesList->Strings[ii], (TObject *)Global::OurModulesList->Objects[ii]);
		//listbox_selected_modules.AddString((LPCTSTR)Global::OurModulesList->Strings[ii].c_str());
		std::list<std::pair<std::string, ClassModule*>>::iterator pos = modIt;
		//SetSuffix(pos);
		string S = modIt->first;
		//if (S.length() > 33 && S.length() > Max_Name_Width2) // 198 pixels roughly 33 caharacters
	//		Max_Name_Width2 = S.Length();
	}
	//ListBox2->ScrollWidth = Max_Name_Width2 * 6;

	Execute = false;

	UpdateAvailableModules();
}


void CConstruct::SetSuffix(std::list<std::pair<std::string, ClassModule*>>::iterator pos) 
{

	ClassModule* thisModule = pos->second;
	string AA;
	if (thisModule->hh > 0) {
		AA = "#0";
		AA[1] += (char) thisModule->hh;
	}

	int found = pos->first.find("#");
	if (found > -1) // remove earlier suffix
	{
		//SelectedModules->Strings[Row] = SelectedModules->Strings[Row].Delete(SelectedModules->Strings[Row].length() - 1, 2);
		for (size_t it = 0; it < SelectedModules->size(); it++)
		{
			if (SelectedModules->at(it).first == pos->first)
			{
				SelectedModules->at(it).first = SelectedModules->at(it).first.substr(0, SelectedModules->at(it).first.length() - 2);
				break;
			}
		}
	}

	for (size_t it = 0; SelectedModules->size(); it++)
	{
		if (SelectedModules->at(it).first == pos->first)
		{
			SelectedModules->at(it).first = SelectedModules->at(it).first + AA;
			break;
		}
	}
}



void CConstruct::AKAselectiveDelete()
{
	if(!Global::MapAKA.empty()) 
	{ // separate out AKA commands
		Mapstr2::iterator it;

		for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); )
		{
			string Var = (*it).first; // module, type and name

			string::size_type idx = Var.find(' ');
			string type = Var.substr(0, idx);
			TAKA Type = AKAtype(type);

			switch (Type) 
			{
				case TAKA::OBSR :
				case TAKA::OBSF :
				++it;
				break;

				default :
				Global::MapAKA.erase(it++);
			} // end switch
		} // for
	}
}


void CConstruct:: AddLineToConstructConsole(std::string str)
{
	CListBox * listbox = (CListBox*)GetDlgItem(ID_CONSTRUCT_CONSOLE);
	CString cstr(str.c_str());
	listbox->AddString(cstr);
}


void CConstruct::DisplayModule(std::string moduleName, ClassModule* module, bool LBox1) 
{
	long variation = 0;
	long variationIndex = 0;

	//Store the full moduleName
	std::string fullModuleName = moduleName;

	// remove variation suffix
	int suffPos;
	if ( suffPos = moduleName.find("#"), suffPos > -1) 
	{ 
		variationIndex = moduleName[suffPos + 1] - char('0');
		variation = (long) (pow(2, moduleName[suffPos + 1] - char('1')));
		moduleName = moduleName.substr(0, moduleName.length() - 2);
	}
	else
	{
		variation = 0;
	}

	if (!module->Description.empty()) 
	{
		std::vector<std::string> * descriptionVector = new std::vector<std::string>();
	
		Common::tokenizeString(module->Description, descriptionVector);

		// if variation skip overview //I don't understand this comment yet jhs507
		if (module->variation_max > 0) 
		{
			++variationIndex;
		}

		// write out the description to the console like list box
		if (LBox1) 
		{ 
			for (size_t ii = 0; ii < descriptionVector->size(); ++ii) 
			{
				std::string consoleLine = moduleName;
				if (ii == 0)
					consoleLine += " Function summary";
				else if (ii > 1)
					consoleLine += "#" + to_string(ii - 1);
				else
					consoleLine += "  ";

				consoleLine += " -> " + descriptionVector->at(ii);
				AddLineToConstructConsole(consoleLine);
			}
		}
		else 
		{
			//Memo1->Lines->Add(SS + " -> " + Fred->Strings[Vindx]);
			AddLineToConstructConsole(fullModuleName + " -> " + descriptionVector->at(variationIndex));
			if (module->DLLName == "Macro") 
			{
				ClassMacro *thisMacro = dynamic_cast<ClassMacro *> (module);

				if (thisMacro->isGroup) 
				{
					AddLineToConstructConsole("Group with modules:");
					std::string consoleLine;
					for (size_t ii = 0; ii < thisMacro->GrpStringList->size(); ++ii)
					{
						if (ii == 0)
						{
							consoleLine = "  " + thisMacro->GrpStringList->at(ii).first;
						}
						else
						{
							consoleLine += ", " + thisMacro->GrpStringList->at(ii).first;
						}
					}
					AddLineToConstructConsole(consoleLine);
				}
				else if (thisMacro->isStruct) 
				{
					AddLineToConstructConsole("Struct with modules:");
					std::string consoleLine;
					for (size_t ii = 0; ii < thisMacro->GrpStringList->size(); ++ii)
					{
						if (ii == 0)
						{
							consoleLine = "  " + thisMacro->GrpStringList->at(ii).first;
						}
						else
						{
							consoleLine += ", " + thisMacro->GrpStringList->at(ii).first;
						}
					}
					AddLineToConstructConsole(consoleLine);
				}
				else 
				{
					AddLineToConstructConsole("Macro: ");
					AddLineToConstructConsole("declarations:");

					int macroFoundAt;
					for (size_t i = 0; i < Global::MacroModulesList->size(); i++)
					{
						if (Global::MacroModulesList->at(i) == thisMacro->Name.c_str())
						{
							macroFoundAt = i;
							break;
						}
					}

					for (int ii = macroFoundAt + 1; ii < thisMacro->Begin - 1; ++ii)
					{
						AddLineToConstructConsole(" " + Global::MacroModulesList->at(ii));
					}

					AddLineToConstructConsole("code:");
					for (int ii = thisMacro->Begin; ii < thisMacro->End; ++ii)
					{
						AddLineToConstructConsole(" " + Global::MacroModulesList->at(ii));
					}
				}
			}
		}
		AddLineToConstructConsole(" ");
		delete descriptionVector;
	}
 
	CListBox* console = (CListBox*)GetDlgItem(ID_CONSTRUCT_CONSOLE);
	console->SetTopIndex(console->GetCount() - 1);


	StringGrid1 = new StringGrid();
		
	StringGrid1->ColCount = 6;
	StringGrid1->FixedRows = 0;
	StringGrid1->RowCount = 1;

	StringGrid1->Cells[0][0] = "Observations";
	StringGrid1->Cells[1][0] = "Modules";
	StringGrid1->Cells[2][0] = "Inputs";
	StringGrid1->Cells[3][0] = "Outputs";
	StringGrid1->Cells[4][0] = "Parameters";
	StringGrid1->Cells[5][0] = "New Observations";
	
	// insert observations into string grid.
	pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(moduleName);
	int ii = 0;
	for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap)
	{
		std::string observationName = (itMap->second).first;
		if (StringGrid1->RowCount < ii + 3)
		{
			StringGrid1->RowCount = ii + 3;
		}
		
		int Indx = StringGrid1->Cols[0].find(observationName);
		if (Indx == -1 && Variation_Decide(variation, (itMap->second).second)) 
		{
			StringGrid1->Cells[0][ii + 2] = observationName;
			++ii;
		}
	}

	// insert put variables used into string grid.
	range = Global::Mapputvar.equal_range(moduleName);
	ii = 0;
	for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap)
	{
		std::string putVarName = itMap->second.first;
		int jj = putVarName.find(" ");
		std::string mod = putVarName.substr(0, jj); // module
		std::string var = putVarName.substr(jj + 1, putVarName.length() - jj-1); // variable
		if (mod != moduleName && Variation_Decide(variation, (itMap->second).second)) 
		{
			if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
			StringGrid1->Cells[1][ii + 2] = mod;
			StringGrid1->Cells[2][ii + 2] = var;
			++ii;
		}
	}

	// insert get variables used into string grid.
	range = Global::Mapgetvar.equal_range(moduleName);
	ii = 0;
	for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap)
	{
		std::string getVarName = itMap->second.first;
		int jj = getVarName.find(" ");
		std::string mod = getVarName.substr(0, jj); // module
		std::string var = getVarName.substr(jj + 1, getVarName.length() - jj-1); // variable
		if (mod != moduleName && Variation_Decide(variation, (itMap->second).second)) 
		{
			int Indx = StringGrid1->Cols[2].find(var);
			if (Indx == -1) 
			{
				if (StringGrid1->RowCount < ii + 3)
				{
					StringGrid1->RowCount = ii + 3;
				}
				StringGrid1->Cells[1][ii + 2] = mod;
				StringGrid1->Cells[2][ii + 2] = var;
				++ii;
			}
		}
	}

	// insert variables declared into string grid.
	range = Global::Mapdeclvar.equal_range(moduleName);
	ii = 0;
	for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap)
	{
		std::string varDeclaredName = itMap->second.first;

		Mapstr::iterator itMapInner;
		for (itMapInner = Global::Mapreadvar.begin(); itMapInner != Global::Mapreadvar.end(); ++itMapInner)
		{
			if (itMapInner->second.first == varDeclaredName)
			{
				break;				
			}
		}
		Mapstr::iterator pos = itMapInner;

		for (itMapInner = Global::Mapdeclobs.begin(); itMapInner != Global::Mapdeclobs.end(); ++itMapInner)
		{
			if (itMapInner->second.first == varDeclaredName)
			{
				break;				
			}
		}
		Mapstr::iterator pos2 = itMapInner;

		if ((pos == Global::Mapreadvar.end() || Not_Obs(moduleName, varDeclaredName)) && pos2 == Global::Mapdeclobs.end()) 
		{
			int Indx = StringGrid1->Cols[3].find(varDeclaredName);
			if (Indx == -1 && Variation_Decide(variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) 
			{
				if (StringGrid1->RowCount < ii + 3)
				{
					StringGrid1->RowCount = ii + 3;
				}
				StringGrid1->Cells[3][ii + 2] = varDeclaredName;
				++ii;
			}
		}
	}

	// insert parameters declared into string grid.
	range = Global::Mapdeclpar.equal_range(moduleName);
	ii = 0;
	for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap)
	{
		if (Variation_Decide(variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) 
		{
			std::string paramName = itMap->second.first;
			if (StringGrid1->RowCount < ii + 3)
			{
				StringGrid1->RowCount = ii + 3;
			}
			StringGrid1->Cells[4][ii + 2] = paramName;
			++ii;
		}
	}

	// insert observations declared into string grid.
	range = Global::Mapdeclobs.equal_range(moduleName);
	ii = 0;
	for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap)
	{
		if (Variation_Decide(variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) 
		{
			std::string obsName = itMap->second.first;
			if (StringGrid1->RowCount < ii + 3)
			{
				StringGrid1->RowCount = ii + 3;
			}
			StringGrid1->Cells[5][ii + 2] = obsName;
			++ii;
		}
	}

	if (StringGrid1->RowCount > 1)
	{
		StringGrid1->FixedRows = 1;
	}

	while (listcontrol.DeleteColumn(0));

	listcontrol.DeleteAllItems();

	listcontrol.InsertColumn(0, _T("Observations"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(1, _T("Modules"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(2, _T("Inputs"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(3, _T("Outputs"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(4, _T("Parameters"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(5, _T("New Observations"), LVCFMT_LEFT, 95);

	for (int i = 1; i < StringGrid1->RowCount; i++)
	{
		CString cstr0(StringGrid1->Cells[0][i].c_str());
		CString cstr1(StringGrid1->Cells[1][i].c_str());
		CString cstr2(StringGrid1->Cells[2][i].c_str());
		CString cstr3(StringGrid1->Cells[3][i].c_str());
		CString cstr4(StringGrid1->Cells[4][i].c_str());
		CString cstr5(StringGrid1->Cells[5][i].c_str());

		int nIndex = listcontrol.InsertItem(i-1, cstr0);
		listcontrol.SetItemText(nIndex, 1, cstr1);
		listcontrol.SetItemText(nIndex, 2, cstr2);
		listcontrol.SetItemText(nIndex, 3, cstr3);
		listcontrol.SetItemText(nIndex, 4, cstr4);
		listcontrol.SetItemText(nIndex, 5, cstr5);
	}
}


bool CConstruct::Variation_Decide(int Variation_set, long Variation) {

	VandP V; V.Set(Variation);

	long variations = V.GetV(); // & 2047;

	if ((variations & 2048) != 0 && Variation_set == 0 || // handles VARIATION_0
		(variations & 4096) != 0 ||                        // handles VARIATION_0
		(variations == 0) ||                               // handles VARIATION_ORG
		(variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
		return true;
	else
		return false;
}

bool CConstruct::Visible_Decide(long Variation) {

	VandP V; V.Set(Variation);
	long Visible = V.GetP();
	return Visible == 1;
}

bool CConstruct::Not_Obs(string Mod, string Var) {

	pair<Mapstr::iterator, Mapstr::iterator> rangeIobs = Global::Mapreadvar.equal_range(Mod);
	for (Mapstr::iterator itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap)
		if (Var == itMap->second.first)
			return false;

	return true;
}


void CConstruct::OnSelChangeAllModsListBox()
{
	int selection = listbox_available_modules.GetCurSel();
	CString cstr;
	listbox_available_modules.GetText(selection, cstr);
	CT2A moduleText(cstr);
	std::string moduleName= moduleText;
	std::map<std::string, ClassModule*>::iterator modPos = Global::AllModulesList->find(moduleName);
	DisplayModule(modPos->first, modPos->second, true);
}


void CConstruct::OnSelChangeSelModsListBox()
{
	int selection = listbox_selected_modules.GetCurSel();
	CString cstr;
	listbox_selected_modules.GetText(selection, cstr);
	CT2A moduleText(cstr);
	std::string moduleName = moduleText;

	//Remove suffix
	std::string trimmedModuleName;
	int pos = moduleName.find_first_of('#', 0);

	if (pos == std::string::npos)
	{
		trimmedModuleName = moduleName;
	}
	else
	{
		trimmedModuleName = moduleName.substr(0, pos);
	}

	std::map<std::string, ClassModule*>::iterator modPos = Global::AllModulesList->find(trimmedModuleName);
	DisplayModule(moduleName, modPos->second, false);
}


void CConstruct::OnClkCheckButton()
{
	CheckModel();	
	UpdateSelectedModulesListBox();
}

string CConstruct::StringOfChar(char c, int n)
{
	string result = "";
	for (int i = 0; i < n; i++)
	{
		result += c;
	}
	return result;
}

long CConstruct::CheckModel() 
{

	size_t Showing = SelectedModules->size();
	if (Showing == 0)
	{
		return 0;
	}

	Mapstr::iterator itMap, pos, pos2, itMap2;
	pair<Mapstr::iterator, Mapstr::iterator> rangeO;
	pair<Mapstr::iterator, Mapstr::iterator> rangeOobs;
	pair<Mapstr::iterator, Mapstr::iterator> rangeI;
	pair<Mapstr::iterator, Mapstr::iterator> rangeIobs;

	List = new std::vector<std::pair<std::string, int>>();
	ListAll = new std::vector<std::string>;
	ListUsed = new std::vector<std::pair<std::string, int>>(); // Object SelectedModules pos index, neg -(index+1)
	ListPuts = new std::vector<std::pair<std::string, int>>();
	ListStats = new std::vector<std::string>();

	string S, SS, S1, S2;
	int indx, Error = 0, Wild = 0;
	
	MapAKAVar.clear();

	//StatusBar1->SimpleText = "";
	//Memo1->Lines->Clear();
	CListBox * listbox = (CListBox*)GetDlgItem(ID_CONSTRUCT_CONSOLE);
	listbox->ResetContent();

	long Variation = 0;
	long Vindx = 0;
	

Again:

	// Add any modules not in SelectedModules but defined as source modules.
	// Wild modules must be explicitly added.
	for (size_t ii = 0; ii < SelectedModules->size(); ++ii) 
	{
		S = SelectedModules->at(ii).first;

		Variation = SelectedModules->at(ii).second->variation;
		if (Variation)
		{
			Vindx = (long)(log(Variation) / log(2) + 1);
		}
		else
		{
			Vindx = 0;
		}

		rangeI = Global::Mapgetvar.equal_range(S);
		for (itMap = rangeI.first; itMap != rangeI.second; ++itMap) 
		{
			SS = itMap->second.first;
			if (Variation_Decide(Variation, (itMap->second).second)) 
			{
				int jj = SS.find(" ");
				S1 = SS.substr(0, jj);
				S2 = SS.substr(jj + 1, SS.length() - jj-1); // variable

				if (S1[0] != '*') // handle specified variables
				{ 
					rangeO = Global::Mapdeclvar.equal_range(S);
					bool Found = false;
					for (pos = rangeO.first; pos != rangeO.second; ++pos) 
					{
						if (S2 == pos->second.first) // variable
						{ 
							Found = true;
							break;
						}
					}
					if (!Found)  // not a group! 
					{
						// module in model?
						indx = -1;
						for (size_t selectedModit = 0; selectedModit < SelectedModules->size(); selectedModit++)
						{
							if (SelectedModules->at(selectedModit).first == S1)
							{
								indx = selectedModit;
							}
						}


						if (indx == -1) // module not loaded
						{ 

							// module available?
							for (size_t AllModit = 0; AllModit < AvailableModules->size(); AllModit++)
							{
								if (AvailableModules->at(AllModit).first == S1)
								{
									indx = AllModit;
								}
							}

							if (indx == -1) { // module does not exist
								LogError("module not found: " + S1, TExcept::ERR); // should not return
								//Memo1->Lines->Add("module not found: " + S1);
								AddLineToConstructConsole("module not found: " + S1);
							}
							else {
								int result = IDYES;

								string temp = "To satisfy module " + S + " input " + SS;
								CString cstr (temp.c_str());
								string temp2 = "Add module " + S1 + " ?";
								CString cstr2(temp2.c_str());
								result = MessageBox(cstr, cstr2, MB_YESNO);
								if (result == IDYES)
								{
									SelectedModules->push_back(std::pair<std::string, ClassModule *>(S1, AvailableModules->at(indx).second));
								}
							}
						}
					} // if
				} // if
			} // handle variation
		} // for
	} // for

	for (int ii = 0; ii < (int) SelectedModules->size(); ++ii) 
	{
		S = SelectedModules->at(ii).first;

		Variation = SelectedModules->at(ii).second->variation;
		if (Variation)
		{
			Vindx = (long)(log(Variation) / log(2) + 1);
		}
		else
		{
			Vindx = 0;
		}

		// make stats list
		rangeI = Global::Mapdeclstat.equal_range(S);

		for (itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
			SS = itMap->second.first; // module + variable
			if (Variation_Decide(Variation, (itMap->second).second))
			{
				ListStats->push_back(SS);
			}
		} // for

		rangeO = Global::Mapdeclvar.equal_range(S);
		rangeOobs = Global::Mapdeclobs.equal_range(S);
		rangeI = Global::Mapgetvar.equal_range(S);
		rangeIobs = Global::Mapreadvar.equal_range(S);

		// add current modules declared observations to 'list'
		for (itMap = rangeOobs.first; itMap != rangeOobs.second; ++itMap) 
		{
			SS = itMap->second.first; // variable
			if (Variation_Decide(Variation, (itMap->second).second))
			{
				List->push_back(std::pair<std::string, int>(S + " " + SS, 0));
			}
		} 

		  // add current modules declared variables to 'list'
		for (itMap = rangeO.first; itMap != rangeO.second; ++itMap) {
			SS = itMap->second.first; // variable
			if (Variation_Decide(Variation, (itMap->second).second)) {


				//previous code.
				//pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
					//value_equals<KeyType2, KeyType2, Pairstr>(SS));

				//pos2 = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
					//value_equals<KeyType2, KeyType2, Pairstr>(SS));



				for (itMap2 = Global::Mapreadvar.begin(); itMap2 != Global::Mapreadvar.end(); ++itMap2)
				{
					if (itMap2->second.first == SS)
					{
						break;
					}
				}
				pos = itMap2;

				for (itMap2 = Global::Mapdeclobs.begin(); itMap2 != Global::Mapdeclobs.end(); ++itMap2)
				{
					if (itMap2->second.first == SS)
					{
						break;
					}
				}
				pos2 = itMap2;


				//new code. need to change.		
				//pos = Global::Mapreadvar.end();
				//pos2 = Global::Mapdeclobs.end();


				if ((pos == Global::Mapreadvar.end() || Not_Obs(S, SS)) && pos2 == Global::Mapdeclobs.end()) {
					S2 = SelectedModules->at(ii).first + " " + SS;
					string S3;
					string M3;
					bool Twice = false;
					size_t tt;

					for (tt = 0; tt < ListAll->size(); tt++) 
					{
						int jj = ListAll->at(tt).find(" ");
						S3 = ListAll->at(tt).substr(jj + 1, ListAll->at(tt).length() - jj-1); // variable
						M3 = ListAll->at(tt).substr(0, jj); // module
						if (S3 == SS && S != M3 && S != "obs") {
							if (S3[S3.length()-1] != '#') {
								Twice = true;
								break;
							}
						}
					}

					if (Twice) {
						int result = IDYES;

						string temp = string("YES to remove '" + S + "' or NO to remove '" + M3 + "'");
						CString cstr(temp.c_str());
						string temp2 = string("Module output generated twice: '" + S2 + "' defined earlier as '" + ListAll->at(tt) + "'");
						CString cstr2(temp2.c_str());

						result = MessageBox(cstr, cstr2, MB_YESNO);

						if (result == IDYES)
						{
							// module in model?
							for (size_t it = 0; it < SelectedModules->size(); it++)
							{
								if (SelectedModules->at(it).first == S)
								{
									tt = it;
								}
							}
						}
						else if (result == IDNO)
						{
							// module in model?
							for (size_t it = 0; it < SelectedModules->size(); it++)
							{
								if (SelectedModules->at(it).first == M3)
								{
									tt = it;
								}
							}
						}
							

						SelectedModules->erase(SelectedModules->begin() + tt);
						
						Entries.clear();
						List->clear();
						ListAll->clear();
						ListUsed->clear();
						ListPuts->clear();
						ListStats->clear();

						goto Again;
					}

					ListAll->push_back(S2);

					int indx = -1;
					for (size_t it = 0; it < List->size(); it++)
					{
						if (List->at(it).first == S2)
						{
							indx = it;
						}
					}
					if (indx == -1)
					{
						List->push_back(std::pair<std::string, int>(S2, 0));
					}

				} // if
			} // handle variation
		} // for

		  // add needed get variables to ListUsed
		for (itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
			SS = itMap->second.first; // module + variable
			if (Variation_Decide(Variation, (itMap->second).second)) 
			{
				
				int indx = -1;
				for (size_t it = 0; it < List->size(); it++)
				{
					if (List->at(it).first == SS)
					{
						indx = it;
						break;
					}
				}

				if (indx == -1 && SS[0] != '*') // handle groups and ignore wild 
				{ 
					int jj = SS.find(" ");
					S2 = SS.substr(jj + 1, SS.length() - jj-1); // variable
					S1 = S + ' ' + S2; // check if in the same group
					
					indx = -1;
					for (size_t it = 0; it < List->size(); it++)
					{
						if (List->at(it).first == S1) 
						{
							indx = it;
							break;
						}
					}

					// check if available as root variable
					if (indx == -1 && S1[S1.length() - 2] == '@')
					{
						// check if available as root variable
						indx = -1;
						for (size_t it = 0; it < List->size(); it++)
						{
							if (List->at(it).first == SS.substr(0, SS.find("@")))
							{
								indx = it;
								break;
							}
						}

					}

				}
				if (indx == -1) 
				{
					ListUsed->push_back(std::pair<std::string, int>(SS, -(ii + 1))); // wild variable or undefined
				}
				else 
				{
					int Cnt = List->at(indx).second; // increment count of useage
					List->at(indx).second = ++Cnt;
					ListUsed->push_back(std::pair<std::string, int>(SS, ii));
				}
			} // neccessary
		} // for

		  // add needed put variables to ListUsed
		rangeI = Global::Mapputvar.equal_range(S);

		for (itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
			SS = itMap->second.first; // module + variable
			if (Variation_Decide(Variation, (itMap->second).second)) 
			{
			
				indx = -1;
				for (size_t it = 0; it < List->size(); it++)
				{
					if (List->at(it).first == SS)
					{
						indx = it;
						break;
					}
				}

				if (indx == -1) 
				{
					ListPuts->push_back(std::pair<std::string, int>(SS, (int) ListUsed->size())); // wild variable or undefined
					ListUsed->push_back(std::pair<std::string, int>(SS, -(ii + 1))); // wild variable or undefined
				}
				else 
				{
					int Cnt = List->at(indx).second; // increment count of useage
					List->at(indx).second = ++Cnt;
					ListPuts->push_back(std::pair<std::string, int>(SS, (int) ListUsed->size()));
					ListUsed->push_back(std::pair<std::string, int>(SS, ii));
				}
			} // handle variation
		} // for

		  // add needed macro observations to ListUsed
		for (itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap) {
			SS = itMap->second.first; // variable
			if (Variation_Decide(Variation, (itMap->second).second)) {
				
				//previous code.
				//pos = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
					//value_equals<KeyType2, KeyType2, Pairstr>(SS));

				for (itMap2 = Global::Mapdeclobs.begin(); itMap2 != Global::Mapdeclobs.end(); ++itMap2)
				{
					if (itMap2->second.first == SS)
					{
						break;
					}
				}
				pos = itMap2;



				//new code. need to change
				//pos = Global::Mapdeclobs.end();


				if (pos == Global::Mapdeclobs.end())
				{
					continue; // not available or met observation
				}
				
				// module available?
				indx = -1;
				for (size_t it = 0; it < SelectedModules->size(); it++)
				{
					if (SelectedModules->at(it).first == pos->first)
					{
						indx = it;
					}
				}


				if (indx != ii && indx > -1) // cannot be its self 
				{ 
					S1 = pos->first;
					SS = pos->second.first;
					S2 = S1 + " " + SS;

					indx = -1;
					for (size_t it = 0; it < List->size(); it++)
					{
						if (List->at(it).first == S2)
						{
							indx = it;
							break;
						}
					}

					if (indx == -1) // used but not declared 
					{ 
						ListUsed->push_back(std::pair<std::string, int>(S2, -(ii + 1)));
					}
					else 
					{
						int Cnt = List->at(indx).second; // increment count of useage
						List->at(indx).second = ++Cnt;
						ListUsed->push_back(std::pair<std::string, int>(S2, ii));
					}
				} // if
			} // handle variation
		} // for
	} // for - long loop

	for (int ii = 0; ii < (int) SelectedModules->size(); ++ii) 
	{
		S = SelectedModules->at(ii).first;

		Variation = SelectedModules->at(ii).second->variation;
		if (Variation)
		{
			Vindx = (long)(log(Variation) / log(2) + 1);
		}
		else
		{
			Vindx = 0;
		}

		// Add module PeerVar to 'ListUsed' to force module to desired rank.
		ClassModule * Module = SelectedModules->at(ii).second;

		std::vector<std::string> * Choices = new std::vector<std::string>();
		Common::tokenizeString(Module->PeerVar, Choices);

		if ((long)Choices->size() > Vindx)
		{
			SS = Choices->at(Vindx);
		}
		else if (Choices->size())
		{
			SS = Choices->at(Choices->size() - 1);
		}
		else
		{
			SS = "";
		}

		if (SS != "") 
		{
			for (size_t jj = 0; jj < List->size(); ++jj) 
			{
				string Entry = List->at(jj).first;
				long kk = Entry.find(' ');
				S1 = Entry.substr(kk + 1, Entry.length());
				if (S1 == SS)
				{
					break;
				}
			}

			if (S1 == SS) 
			{
				SS = "* " + SS;
				ListUsed->push_back(std::pair<std::string, int>(SS, -(ii + 1))); // wild variable
				string SSS = "Ranking module '" + S + "' to '" + SS + "'";
				//Memo1->Lines->Add(SSS);
				AddLineToConstructConsole(SSS);
			}
			else {
				S2 = "Ranking module '" + S + "' to an inaccessible variable '" + SS + "'";
				//Memo1->Lines->Add(S2);
				AddLineToConstructConsole(S2);
			}
		} // if
	} // for

	for (size_t ii = 0; ii < ListUsed->size(); ++ii) 
	{

		// if wild see if exists anywhere
		if (ListUsed->at(ii).first[0] == '*') 
		{
			string Var = ListUsed->at(ii).first;
			Var = Var.substr(2, Var.length());

			int jj = Best_Match(Var, List);
			if (jj > -1) // match 
			{ 
				++Wild;
				int thisModule = ListUsed->at(ii).second;
				thisModule = -(thisModule + 1);
				string Module = SelectedModules->at(thisModule).first;
				//        LogError("wild variable: '" + Module + " " + ListUsed->Strings[ii] + "' associated with '" + List->Strings[jj] + "'", WARNING);

				//        Memo1->Lines->Add("wild variable: '" + Module + " " + ListUsed->Strings[ii] + "' associated with '" + List->Strings[jj] + "'");

				ListUsed->at(ii).first = List->at(jj).first;
				ListUsed->at(ii).second = abs((int)ListUsed->at(ii).second + 1); // make positive
			} // if
		} // if 'wild'

		else // declared module source 
		{ 
			int NotFoundIndx = ListUsed->at(ii).second;
			if (NotFoundIndx < 0) // variable declared after use in current order? 
			{ 
				int indx = -1;
				for (size_t it = 0; List->size(); it++)
				{
					if (List->at(it).first == ListUsed->at(ii).first)
					{
						indx = it;
						break;
					}
				}

				int ListPutsIndx = -1;
				for (size_t it = 0; it < ListPuts->size(); it++)
				{
					if (ListPuts->at(it).first == ListUsed->at(ii).first)
					{
						ListPutsIndx = it;
						break;
					}
				}
				if (ListPutsIndx == -1 && indx == -1)
				{
					++Error;
				}
				if (indx > -1) 
				{
					ListUsed->at(ii).second = abs(ListUsed->at(ii).second + 1); // make positive
					continue;
				}
			}
			else 
			{
				continue; // OK
			}
		} // declared module source

		int NotFoundIndx = ListUsed->at(ii).second;
		if (NotFoundIndx < 0 && ListUsed->at(ii).first[0] == '*') // not found after wild variable search 
		{ 

																   // make suggestions
			string Message;
			string Message2(" Suggestions: ");
			++Error;
			LogError("wild variable not found: " + ListUsed->at(ii).first, TExcept::WARNING);

			int kk = abs(ListUsed->at(ii).second + 1); // make positive

			string Sroot = ListUsed->at(ii).first;
			if (Sroot.find("@") != -1)
				Sroot = Sroot.substr(0, Sroot.find("@"));
			Message = "wild variable not found: \" " + Sroot + "\" used by " + SelectedModules->at(kk).first + ".";
			string SW = ListUsed->at(ii).first;
			SW = SW.substr(2, ListUsed->at(ii).first.length());
			bool Once = false;
			bool rootVar = (SW.find("@") == -1); // note !root == group
			if (!rootVar)
				SW = SW.substr(0, SW.find("@"));
			for (itMap = Global::Mapdeclvar.begin(); itMap != Global::Mapdeclvar.end(); ++itMap) {
				SS = itMap->second.first;
				bool rootVar1 = (SS.find("@") == -1); // note !root == group
				if (!rootVar1)
					SS = SS.substr(0, SS.find("@"));
				if (SW == SS) {
					Once = true;
					string S = itMap->first;
					VandP V; V.Set((itMap->second).second);
					long Variation = V.GetV() & 2047;
					if (Variation > 0) {
						long NN = (long) (log(Variation) / log(2) + 1);
						string  AA = "#0";
						AA[1] += (char) NN;
						S += AA;
					}
					Message2 += S + ", ";
				}
			} // for

			if (!Once)
				//Memo1->Lines->Add(Message + " No " + Message2);
				AddLineToConstructConsole(Message + " No " + Message2);
			else
				//Memo1->Lines->Add(Message + Message2);
				AddLineToConstructConsole(Message + Message2);

		} // if
	} // for - long loop

	if (Error) {
		string temp = "" + Error;
		S = "Errors: " + temp + ';';
		string Line = StringOfChar('*', 80);;
		//Memo1->Lines->Add(Line);
		AddLineToConstructConsole(Line);
	}
	else {
		bool Loop = true;
		int Loops = 0;
		std::vector<std::pair<std::string, int>> * OrgList = new std::vector<std::pair<std::string, int>>(); // source module + varName, original SelectedModules index

		for (size_t ii = 0; ii < SelectedModules->size(); ++ii) 
		{
			OrgList->push_back(std::pair<std::string, int>(SelectedModules->at(ii).first, ii));
			Entries.push_back(ClassEntry()); // create entries
		}

		while (Loop) 
		{

			Loop = false; 
			++Loops;

			// set up ClassEntry vector
			for (size_t ii = 0; ii < SelectedModules->size(); ++ii) 
			{
				Entries[ii].module = SelectedModules->at(ii).second;
				Entries[ii].Name = SelectedModules->at(ii).first; // (Entries[ii].module)->Name.c_str(); //
				Entries[ii].rank = 0; // clear to highest rank
				Entries[ii].used = false; // set to not used

				size_t index = -1;
				for (size_t it = 0; it < OrgList->size(); it++)
				{
					if (OrgList->at(it).first == SelectedModules->at(ii).first)
					{
						index = it;
						break;
					}
				}


				if (index < 0 || index > Entries.size() - 1) 
				{
					LogError("Build error: outside range", TExcept::ERR);  // should not return
				}
				Entries[ii].OrigPos = index;
			} // for

			for (size_t ii = 0; ii < ListPuts->size(); ++ii) // handle wild cards in Puts list 
			{ 
				ListPuts->at(ii).first = ListUsed->at(ListPuts->at(ii).second).first;
			}

			// assign each module its current rank based upon the modules it uses
			for (size_t ii = 0; ii < ListUsed->size(); ++ii) 
			{
				unsigned long thisModule = ListUsed->at(ii).second; // original postion

				for (unsigned long nn = 0; nn < Entries.size(); ++nn) 
				{
					if (Entries[nn].OrigPos == thisModule) 
					{
						thisModule = nn; // current position
						if (thisModule < 0 || thisModule > Entries.size() - 1) 
						{
							LogError("Build error: outside range", TExcept::ERR);  // should not return
						}
						break;
					}
				}

				string Entry = ListUsed->at(ii).first;
				long kk = Entry.find(' ');
				string UsesModule = Entry.substr(0, kk); // extract module name
				string Var_only = Entry.substr(kk + 1, Entry.length() - kk-1); // extract variable name

				unsigned long index;
				ClassModule* checkModule = NULL;

				for (index = 0; index < Entries.size(); ++index) { // find modules position
					string Root = Entries[index].Name;
					if (Root == UsesModule) {
						checkModule = Entries[index].module;
						break;
					}
				}

				if (checkModule && checkModule->isGroup) { // resides in group
					Entries[index].used = true;
					continue;
				}
				if (index >= Entries.size())
					continue; // ignore

				Entries[index].used = true;

				if (UsesModule == Entries[thisModule].Name) // ignore if self
					continue;

				// assume if put or stat, module does not matter
				int jj = Best_Match(Var_only, ListPuts);
				if (jj > -1 && ii == (ListPuts->at(jj).second))
				{
					continue; // ignore Puts
				}

				jj = Best_Match(Var_only, ListStats);
				if (jj > -1)
					continue; // ignore Stats

				long B = (long) powl(2, index); // calculate weight
				Entries[thisModule].rank |= B; // OR - done more than once

			} // for

			  // sort by descending rank (ie ascending value)
			for (unsigned long ii = 0; ii < Entries.size() - 1; ++ii) {
				for (unsigned long jj = ii + 1; jj < Entries.size(); ++jj) {

					if (Entries[jj].rank < Entries[ii].rank) {
						MoveDown(Entries, ii, jj);
						Loop = true;
					}
				} // for
			} // for

			  // move entries with equal rank together in alphabetic order or peer rank
			for (long ii = 0; ii < (long)Entries.size() - 1; ++ii) {
				ClassModule * E2 = (ClassModule*)Entries[ii].module;
				if (E2->PeerRank < 0)
					Entries[ii].used = true;
				for (long jj = ii + 1; jj < (long) Entries.size(); ++jj) {
					if (Entries[jj].rank == Entries[ii].rank) {
						ClassModule * E1 = (ClassModule*)Entries[jj].module;

						if (labs(E1->PeerRank) < labs(E2->PeerRank)) {
							MoveDown(Entries, ii, jj);
							Loop = true;
						}
					} // if
				} // for
			} // for

			SelectedModules->clear();

			// update SelectedModules
			for (unsigned long ii = 0; ii < Entries.size(); ++ii)
			{
				SelectedModules->push_back(std::pair<std::string, ClassModule*>(Entries[ii].Name, Entries[ii].module));
			}

			if (Loops > 20) { // too many - something funny
				Loop = false;
				Loops = -Loops;
			}
		} // while

		bool Removed = false;
		for (unsigned long ii = 0; ii < Entries.size() - 1; ++ii) {
			if (!Entries[ii].used && Entries[ii].Name != "basin") {  // never remove basin
				int result = IDYES;

				CString temp(Entries[ii].Name.c_str());
				result = MessageBox(temp, _T("Module not used!  Remove module?"), MB_YESNO);
				if (result != IDYES)
				{
					continue;
				}

				int indx;
				for (size_t it = 0; it < SelectedModules->size(); it++)
				{
					if (SelectedModules->at(it).first == Entries[ii].Name) 
					{
						indx = it;
						SelectedModules->erase(SelectedModules->begin() + indx);
						Removed = true;
						break; //need to break out to ensure that only the first instance is deleted to emulate previous behavior
					}
				}				
			}
		}

		Entries.clear();
		List->clear();
		ListAll->clear();
		ListUsed->clear();
		ListPuts->clear();
		ListStats->clear();

		if (Removed) goto Again;

		int moves = 0;

		for (unsigned long ii = 0; ii < Entries.size(); ++ii)
			if (Entries[ii].OrigPos != ii) ++moves; // final number of modules moved

		if (Loops) {
			//Memo1->Lines->Add(" ");
			AddLineToConstructConsole(" ");
			LogError("Number of loops to build: " + to_string(Loops) + " and modules moved: " + to_string(moves), TExcept::WARNING);
			//Memo1->Lines->Add("Number of loops to build: " + to_string(Loops) + " and modules moved: " + to_string(moves));
			AddLineToConstructConsole("Number of loops to build: " + to_string(Loops) + " and modules moved: " + to_string(moves));
		}
		else {
			LogError("Problem with modules in build. Possibly modules referencing one another!", TExcept::WARNING);
			//Memo1->Lines->Add("Problem with modules in build. Possibly modules referencing one another!");
			AddLineToConstructConsole("Problem with modules in build. Possibly modules referencing one another!");
			MessageBox(_T("Problem with modules in build."), _T("Possibly modules referencing one another!"), MB_OK);
		}

		Entries.clear();
		delete OrgList;
		S = "";
	} // else


	//need to change
	/*
	if (Global::nlay != UpDownMAXLAY->Position || Global::nhru != UpDownMAXHRU->Position) {
		LogError("# of HRUs changed: *** edit parameters ***", WARNING);
		Memo1->Lines->Add(" ");
		Memo1->Lines->Add("# of HRUs changed: *** edit parameters ***");
	}

	if (Wild) S += "  Wild references: " + string(Wild) + ';';

	StatusBar1->SimpleText = S;
	StatusBar1->Repaint();
	*/

	delete List;
	delete ListAll;
	delete ListUsed;

	return Error;
}

long CConstruct::Best_Match(string Var, std::vector<std::pair<std::string, int>> * List) {

	long found = 10;
	long Indx = -1;

	for (size_t jj = 0; jj < List->size(); ++jj) 
	{
		string Entry = List->at(jj).first;
		long kk = Entry.find(' ');
		string Var1 = Entry.substr(kk + 1, Entry.length()); // root or group

		bool rootVar = (Var.find("@") == -1); // note !root == group
		bool rootVar1 = (Var1.find("@") == -1);

		if (Var1 == Var) { // exact match
			found = 0;
			Indx = jj;
			break;
		}
		else if (rootVar && !rootVar1 && Var == Var1.substr(0, Var1.find("@")) && found > 1) { // root variable to GRP match to root variable
			found = 1;
			Indx = jj;
		}
		else if (!rootVar && rootVar1 && Var.substr(0, Var.find("@")) == Var1 && found > 2) {  // GRP to root variable match to variable
			found = 2;
			Indx = jj;
		}
		else if (!rootVar && !rootVar1 && Var.substr(0, Var.find("@")) == Var1.substr(0, Var1.find("@")) && found > 3) { // GRP variable root to GRP variable root
			found = 3;
			Indx = jj;
		}
	} // for
	return Indx;
}

long CConstruct::Best_Match(string Var, std::vector<std::string>* List) {

	long found = 10;
	long Indx = -1;

	for (size_t jj = 0; jj < List->size(); ++jj)
	{
		string Entry = List->at(jj).c_str();
		long kk = Entry.find(' ');
		string Var1 = Entry.substr(kk + 1, Entry.length()); // root or group

		bool rootVar = (Var.find("@") == -1); // note !root == group
		bool rootVar1 = (Var1.find("@") == -1);

		if (Var1 == Var) { // exact match
			found = 0;
			Indx = jj;
			break;
		}
		else if (rootVar && !rootVar1 && Var == Var1.substr(0, Var1.find("@")) && found > 1) { // root variable to GRP match to root variable
			found = 1;
			Indx = jj;
		}
		else if (!rootVar && rootVar1 && Var.substr(0, Var.find("@")) == Var1 && found > 2) {  // GRP to root variable match to variable
			found = 2;
			Indx = jj;
		}
		else if (!rootVar && !rootVar1 && Var.substr(0, Var.find("@")) == Var1.substr(0, Var1.find("@")) && found > 3) { // GRP variable root to GRP variable root
			found = 3;
			Indx = jj;
		}
	} // for
	return Indx;
}


void CConstruct::UpdateAvailableModules()
{
	AvailableModules->clear();
	listbox_available_modules.ResetContent();
	
	for (
		std::map<std::string, ClassModule*>::iterator modIt = Global::AllModulesList->begin(); 
		modIt != Global::AllModulesList->end(); 
		modIt++
		) 
	{
		LMODULE level = modIt->second->Lvl;
		switch (level)
		{
		case (LMODULE::BASIC):
			if (module_filter_basic.GetCheck() == 1)
			{
				AddToAvailableModules(modIt->first, modIt->second);
			}
			break;
		case (LMODULE::ADVANCE):
			if (module_filter_advanced.GetCheck() == 1)
			{
				AddToAvailableModules(modIt->first, modIt->second);
			}
			break;
		case (LMODULE::CUSTOM):
			if (module_filter_custom.GetCheck() == 1)
			{
				AddToAvailableModules(modIt->first, modIt->second);
			}
			break;
		case (LMODULE::MACRO):
			if (module_filter_macro.GetCheck() == 1)
			{
				AddToAvailableModules(modIt->first, modIt->second);
			}
			break;
		case (LMODULE::OBSOL):
			if (module_filter_obsolete.GetCheck() == 1)
			{
				AddToAvailableModules(modIt->first, modIt->second);
			}
			break;
		case (LMODULE::PROTO):
			if (module_filter_prototype.GetCheck() == 1)
			{
				AddToAvailableModules(modIt->first, modIt->second);
			}
			break;
		case (LMODULE::SUPPORT):
			if (module_filter_support.GetCheck() == 1)
			{
				AddToAvailableModules(modIt->first, modIt->second);
			}
			break;
		default:
			break;
		}

	}

}


void CConstruct::OnClkModuleFilterBasic()
{
	// TODO: Add your control notification handler code here

	UpdateAvailableModules();
}


void CConstruct::OnClkModuleFilterMacro()
{
	// TODO: Add your control notification handler code here

	UpdateAvailableModules();
}


void CConstruct::OnClkModuleFilterAdvanced()
{
	// TODO: Add your control notification handler code here

	UpdateAvailableModules();
}


void CConstruct::OnClkModuleFilterSupport()
{
	// TODO: Add your control notification handler code here

	UpdateAvailableModules();
}


void CConstruct::OnClkModuleFilterCustom()
{
	// TODO: Add your control notification handler code here

	UpdateAvailableModules();
}


void CConstruct::OnClkModuleFilterPrototype()
{
	// TODO: Add your control notification handler code here

	UpdateAvailableModules();
}


void CConstruct::OnClkModuleFilterObsolete()
{
	// TODO: Add your control notification handler code here

	UpdateAvailableModules();
}


long CConstruct::BuildClick()
{
	int test = AvailableModules->size();
	long Showing = SelectedModules->size();
	if (Showing == 0) 
	{
		Global::nlay = max_layer_spin.GetPos();
		Global::nhru = max_HRU_spin.GetPos();
		return 1;
	}

	long Errors = CheckModel();
	UpdateSelectedModulesListBox();

	if (Errors) 
	{
		string str = "Errors: " + to_string(Errors);
		CString cstr(str.c_str());
		MessageBox(L"Model has unsatisfied module inputs or multiple definitions", cstr, MB_OK);
		return Errors;
	}

	if (ModifyBuild) 
	{
		SaveBuildParameters();
		RemoveParameter();
	}

	MapAKACopy = Global::MapAKA; // keep any renamed OUTPUTs

	CRHMmain * crhmmain = CRHMmain::getInstance();
	crhmmain->ClearModules(false); // resets Global::MapAKA

	Global::nlay = max_layer_spin.GetPos();
	Global::nhru = max_HRU_spin.GetPos();

	Global::maxlay = max_layer_spin.GetPos();
	Global::maxhru = max_HRU_spin.GetPos();

	COleDateTime timeNow;
	timeNow = COleDateTime::GetCurrentTime();
	timeNow.m_dt;

	crhmmain->setStartDate(timeNow.m_dt);
	crhmmain->setEndDate(timeNow.m_dt);

	Global::OurModulesList->clear();
	for (size_t i = 0; i < SelectedModules->size(); i++)
	{
		std::string selectedString = SelectedModules->at(i).first;
		int suffix = 0;

		//remove suffix and make place variation in the module object.
		std::string trimmedString;
		int pos = selectedString.find_first_of('#', 0);

		if (pos == std::string::npos)
		{
			trimmedString = selectedString;
		}
		else
		{
			trimmedString = selectedString.substr(0, pos);
			suffix = std::stoi(selectedString.substr(pos + 1, std::string::npos));
		}

		if (SelectedModules->at(i).second->variation == 0)
		{
			SelectedModules->at(i).second->variation = (unsigned short)pow(2, suffix - 1);
		}

		Global::OurModulesList->push_back(std::pair<std::string, ClassModule*>(trimmedString, SelectedModules->at(i).second));
	}

	Execute = true;

	Global::BuildFlag = TBuild::BUILD; // model loaded  was DECL

	if (!MapAKAVar.empty()) {
		Mapstr2::iterator it;

		for (it = MapAKAVar.begin(); it != MapAKAVar.end(); ++it)
			MapAKACopy.insert(*it);
	}
	//Close();
	return Errors;
}

void CConstruct::SaveBuildParameters() {

	ClassPar *thisPar;

	if (ModifyBuild) {

		RemoveSharedParams(); // change shared parameters to module parameters

		ParaList = new std::vector<std::pair<std::string, ClassPar *>>();

		// make map: keyed by parameter name holding pointer to parameter
		MapPar::iterator itPar;
		itPar = Global::MapPars.begin();
		while (itPar != Global::MapPars.end()) {
			thisPar = (*itPar).second;
			string S = string(((*itPar).second)->module.c_str()) + " " + ((*itPar).second)->param.c_str();
			
			int parFound = -1;
			for (size_t it = 0; it < ParaList->size(); it++)
			{
				if (ParaList->at(it).first == S)
				{
					parFound = it;
					break;
				}
			}
			if (parFound == -1) 
			{
				ClassPar* par(new ClassPar(*thisPar));
				ParaList->push_back(std::pair<std::string, ClassPar *>(S, par));
			}
			++itPar;
		} // while
	} // if(ModifyBuild)
}


void CConstruct::ReadBuildParameters() {

	MapPar::iterator itPar;
	ClassPar *thisPar;

	if (ModifyBuild) {

		itPar = Global::MapPars.begin();
		while (itPar != Global::MapPars.end()) {
			thisPar = (*itPar).second;

			string S = string(((*itPar).second)->module.c_str()) + " " + ((*itPar).second)->param.c_str();

			int ii = -1;
			for (size_t it = 0; it < ParaList->size(); it++)
			{
				if (ParaList->at(it).first == S)
				{
					ii = it;
					break;
				}
			}
			if (ii != -1) 
			{
				ClassPar *OldPar = ParaList->at(ii).second;
				thisPar->Change(*OldPar);  // restore old value
			}
			++itPar;
		} // while

		for (size_t ii = 0; ii < ParaList->size(); ++ii)
		{
			delete ParaList->at(ii).second; // delete Objects
		}

		delete ParaList;
		ParaList = NULL;

		CRHMmain * crhmmain = CRHMmain::getInstance();
		crhmmain->SqueezeParams();  // converts identical parameters to shared parameters
	} // if(ModifyBuild)
}


void CConstruct::RemoveSharedParams() { // pseudo shared parameters

	Global::Mapgetvar.clear();
	Global::Mapputvar.clear();
	Global::Mapreadvar.clear();
	Global::Mapdeclvar.clear();
	Global::Mapdeclstat.clear();
	Global::Mapdeclpar.clear();
	Global::Mapdeclobs.clear();

	Global::DeclRootList->clear(); // used by AKA to stop looping

	Global::BuildFlag = TBuild::BUILD; // default value

	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt != Global::OurModulesList->end(); 
		modIt++
		)
	{
		modIt->second->decl();
	}
		


	Global::BuildFlag = TBuild::DECL; // model loaded

	ClassPar *thisPar;
	MapPar::iterator itPar;
	long count;
	// restore original module parameters from pseudo Shared parameters if they do not already exist

	itPar = Global::SharedMapPars.begin();
	while (itPar != Global::SharedMapPars.end()) {
		thisPar = (*itPar).second;
		count = ClassParFindParBld(thisPar);
		Global::MapPars.erase("Shared " + thisPar->param);
		delete thisPar; // parameter no longer needed
		++itPar;
	}
	Global::SharedMapPars.clear();
}

void CConstruct::RemoveParameter() {

	MapPar::iterator itPar;
	ClassPar *thisPar;

	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end();) {
		thisPar = (*itPar).second;

		int kk = -1;
		for (size_t it = 0; it < SelectedModules->size(); it++)
		{
			if (SelectedModules->at(it).first.c_str() == thisPar->module.c_str())
			{
				kk = it;
				break;
			}
		}

		if (kk == -1 && thisPar->module != "shared") {  // was basin
			Global::MapPars.erase(itPar++);
			delete thisPar;
		}
		else {
			++itPar;
		}
	}

}

long CConstruct::FormatMax(long M)
{
	M = M & 2047;
	if (M == 0) return 0;
	for (int ii = 1; ii < 8; ++ii) {
		M = (M >> 1);
		if (M == 0) return ii;
	}
	return -1; // should never get here
}

void CConstruct::OnClkBuildButton()
{
	// TODO: Add your control notification handler code here

	long Errors = BuildClick();

	if (!Errors) { CDialog::OnOK(); }

	//CDialog::OnOK();
}


void CConstruct::OnClkCancelButton()
{
	// TODO: Add your control notification handler code here
	
	CDialog::OnCancel();
}





void CConstruct::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here


	RemoveSelectedModule();

}


LRESULT CConstruct::OpenAvailableModsCtxMenu(WPARAM, LPARAM)
{
	CMenu ctxMenu;
	ctxMenu.CreatePopupMenu();

	CString addText("Add");

	ctxMenu.InsertMenu(0,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_AVAILABLE_MOD_ADD,
		(LPCTSTR)addText);

	CWnd* wind = AfxGetMainWnd();
	POINT p;

	if (GetCursorPos(&p))
	{
		UINT result;

		if (result = ctxMenu.TrackPopupMenuEx(
			TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
			p.x, p.y, wind, 0))
		{
			if (result == ID_CTX_AVAILABLE_MOD_ADD)
			{
				AddAvailableModsToSelected();
				UpdateSelectedModulesListBox();
			}
		}

	}

	return 0;
}


LRESULT CConstruct::OpenSelectedModsCtxMenu(WPARAM, LPARAM)
{
	CMenu ctxMenu;
	ctxMenu.CreatePopupMenu();

	CString removeText("Remove");

	ctxMenu.InsertMenu(0,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_SEL_MODS_REMOVE,
		(LPCTSTR)removeText);

	CString NextVarText("Next Variation");

	ctxMenu.InsertMenu(1,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_SEL_MODS_NEXT,
		(LPCTSTR)NextVarText);

	CString PrevVariationText("Previous Variation");

	ctxMenu.InsertMenu(2,
		MF_BYPOSITION | MF_STRING,
		ID_CTX_SEL_MODS_PREV,
		(LPCTSTR)PrevVariationText);


	CWnd* wind = AfxGetMainWnd();
	POINT p;

	if (GetCursorPos(&p))
	{
		UINT result;

		if (result = ctxMenu.TrackPopupMenuEx(
			TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON,
			p.x, p.y, wind, 0))
		{
			if (result == ID_CTX_SEL_MODS_REMOVE)
			{
				RemoveModulesFromSelected();
				UpdateSelectedModulesListBox();
			}
			else if (result == ID_CTX_SEL_MODS_NEXT)
			{
				SetNextVariation();
			}
			else if (result == ID_CTX_SEL_MODS_PREV)
			{
				SetPrevVariation();
			}
		}

	}

	return 0;
}

void CConstruct::AddAvailableModsToSelected()
{
	int selectedCount = listbox_available_modules.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_available_modules.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_available_modules.GetText(selectedIndicies[i], selectedText);

		if (!ModuleIsSelected(selectedText))
		{
			SelectedModules->push_back(std::pair<std::string, ClassModule*>(this->AvailableModules->at(selectedIndicies[i]).first, AvailableModules->at(selectedIndicies[i]).second));
		}

	}

	delete[] selectedIndicies;
}

void CConstruct::RemoveModulesFromSelected()
{
	int selectedCount = listbox_selected_modules.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	listbox_selected_modules.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		listbox_selected_modules.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText);
		std::string selectedString(pszConvertedAnsiString);

		//Remove the suffixbefore comparison
		std::string trimmedString;
		int pos = selectedString.find_first_of('#', 0);

		if (pos == std::string::npos)
		{
			trimmedString = selectedString;
		}
		else
		{
			trimmedString = selectedString.substr(0, pos);
		}

		//Remove from SelectedModules vector.
		for (
			std::vector<std::pair<std::string, ClassModule*>>::iterator it = this->SelectedModules->begin();
			it != this->SelectedModules->end();
			it++
			)
		{
			if (it->first == trimmedString)
			{
				this->SelectedModules->erase(it);
				break;
			}
		}

	}

	delete[] selectedIndicies;
}


void CConstruct::UpdateSelectedModulesListBox()
{
	//Remove any elements that are no longer in the vector
	for (int i = 0; i < listbox_selected_modules.GetCount(); i++)
	{
		CString moduleText;
		listbox_selected_modules.GetText(i, moduleText);
		CT2CA pszConvertedAnsiString(moduleText);
		std::string moduleString(pszConvertedAnsiString);

		//Remove the suffixbefore comparison
		std::string trimmedModuleString;
		int pos = moduleString.find_first_of('#', 0);

		if (pos == std::string::npos)
		{
			trimmedModuleString = moduleString;
		}
		else
		{
			trimmedModuleString = moduleString.substr(0, pos);
		}

		bool found = false;

		for (
			std::vector<std::pair<std::string, ClassModule*>>::iterator it = SelectedModules->begin();
			it != SelectedModules->end();
			it++
			)
		{
			if (it->first == trimmedModuleString)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			listbox_selected_modules.DeleteString(i);
			i = -1;
		}
	}

	//Add any elements that are no present
	for (
		std::vector<std::pair<std::string, ClassModule*>>::iterator it = SelectedModules->begin();
		it != SelectedModules->end();
		it++
		)
	{

		bool found = false;

		for (int i = 0; i < listbox_selected_modules.GetCount(); i++)
		{
			CString moduleText;
			listbox_selected_modules.GetText(i, moduleText);
			CT2CA pszConvertedAnsiString(moduleText);
			std::string moduleString(pszConvertedAnsiString);

			//Remove the suffixbefore comparison
			std::string trimmedModuleString;
			int pos = moduleString.find_first_of('#', 0);

			if (pos == std::string::npos)
			{
				trimmedModuleString = moduleString;
			}
			else
			{
				trimmedModuleString = moduleString.substr(0, pos);
			}


			if (it->first == trimmedModuleString)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			listbox_selected_modules.AddString(CString(it->first.c_str()));
		}

	}

}

void CConstruct::SetNextVariation()
{
	CString selectedText;
	int selIndex = listbox_selected_modules.GetCurSel();
	listbox_selected_modules.GetText(selIndex, selectedText);
	CT2A text(selectedText);
	std::string selectedString = text;


	//Remove the suffix and find the current variation.
	int currentVariation;
	std::string trimmedModuleName;
	int pos = selectedString.find_first_of('#', 0);

	if (pos == std::string::npos)
	{
		currentVariation = 0;
		trimmedModuleName = selectedString;
	}
	else 
	{
		currentVariation = atoi(selectedString.substr(pos + 1, selectedString.length()).c_str());
		trimmedModuleName = selectedString.substr(0, pos);
	}

	std::map<std::string, ClassModule*>::iterator modPos = Global::AllModulesList->find(trimmedModuleName);
	std::bitset<11> bits = modPos->second->variation_max;
	int numberOfVariations = bits.count();//One for each set bit 

	if (currentVariation + 1 <= numberOfVariations)
	{
		currentVariation++;
		std::string updatedModuleName = trimmedModuleName + "#" + std::to_string(currentVariation);

		listbox_selected_modules.DeleteString(selIndex);
		listbox_selected_modules.InsertString(selIndex, CString(updatedModuleName.c_str()));
		
	}
	else 
	{
		currentVariation = 0;

		listbox_selected_modules.DeleteString(selIndex);
		listbox_selected_modules.InsertString(selIndex, CString(trimmedModuleName.c_str()));
	}

	//Update the varation in the ClassModule Object
	for (
		std::vector<std::pair<std::string, ClassModule*>>::iterator it = this->SelectedModules->begin();
		it != this->SelectedModules->end();
		it++
		)
	{
		if (it->first == trimmedModuleName)
		{
			it->second->variation = (unsigned short)pow(2, currentVariation - 1);
		}
	}
	
	
}

void CConstruct::SetPrevVariation()
{
	CString selectedText;
	int selIndex = listbox_selected_modules.GetCurSel();
	listbox_selected_modules.GetText(selIndex, selectedText);
	CT2A text(selectedText);
	std::string selectedString = text;


	//Remove the suffix and find the current variation.
	int currentVariation;
	std::string trimmedModuleName;
	int pos = selectedString.find_first_of('#', 0);

	if (pos == std::string::npos)
	{
		currentVariation = 0;
		trimmedModuleName = selectedString;
	}
	else
	{
		currentVariation = atoi(selectedString.substr(pos + 1, selectedString.length()).c_str());
		trimmedModuleName = selectedString.substr(0, pos);
	}

	std::map<std::string, ClassModule*>::iterator modPos = Global::AllModulesList->find(trimmedModuleName);
	std::bitset<11> bits = modPos->second->variation_max;
	int numberOfVariations = bits.count();//One for each set bit 

	if (numberOfVariations == 0)
	{
		currentVariation = 0;

		listbox_selected_modules.DeleteString(selIndex);
		listbox_selected_modules.InsertString(selIndex, CString(trimmedModuleName.c_str()));
	}
	else if (currentVariation - 1 >= 0)
	{
		currentVariation--;

		if (currentVariation == 0)
		{
			currentVariation = 0;

			listbox_selected_modules.DeleteString(selIndex);
			listbox_selected_modules.InsertString(selIndex, CString(trimmedModuleName.c_str()));
		}
		else 
		{
			std::string updatedModuleName = trimmedModuleName + "#" + std::to_string(currentVariation);

			listbox_selected_modules.DeleteString(selIndex);
			listbox_selected_modules.InsertString(selIndex, CString(updatedModuleName.c_str()));
		}

	}
	else
	{
		currentVariation = numberOfVariations;

		std::string updatedModuleName = trimmedModuleName + "#" + std::to_string(currentVariation);

		listbox_selected_modules.DeleteString(selIndex);
		listbox_selected_modules.InsertString(selIndex, CString(updatedModuleName.c_str()));
	}

	//Update the varation in the ClassModule Object
	for (
		std::vector<std::pair<std::string, ClassModule*>>::iterator it = this->SelectedModules->begin();
		it != this->SelectedModules->end();
		it++
		)
	{
		if (it->first == trimmedModuleName)
		{
			it->second->variation = (unsigned short)pow(2, currentVariation - 1);
		}
	}
	

}