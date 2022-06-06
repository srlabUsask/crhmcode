#include "ParametersDlg.h"

IMPLEMENT_DYNAMIC(ParametersDlg, CDialog)


ParametersDlg::ParametersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(PARAMETERS_DLG, pParent)
{
	this->prameters_scroll_pane = NULL;
}


ParametersDlg::~ParametersDlg()
{
}


void ParametersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PARAM_DLG_MODULES_LIST_BOX, this->modules_list_box);
	DDX_Control(pDX, ID_PARAM_DLG_PARAM_LIST_BOX, this->parameters_list_box);
}


BEGIN_MESSAGE_MAP(ParametersDlg, CDialog)
	ON_LBN_SELCHANGE(ID_PARAM_DLG_MODULES_LIST_BOX, &ParametersDlg::OnSelectModule)
	ON_LBN_SELCHANGE(ID_PARAM_DLG_PARAM_LIST_BOX, &ParametersDlg::OnSelectParam)
	ON_BN_CLICKED(ID_PARAM_DLG_TOGGLE_BASIC_BTN, &ParametersDlg::OnToggleBasic)
	ON_BN_CLICKED(ID_PARAM_DLG_TOGGLE_ADVANCE_BTN, &ParametersDlg::OnToggleAdvance)
	ON_BN_CLICKED(ID_PARAM_DLG_TOGGLE_PRIVATE_BTN, &ParametersDlg::OnTogglePrivate)
	ON_BN_CLICKED(ID_PARAM_DLG_TOGGLE_ALL_BTN, &ParametersDlg::OnToggleAll)
	ON_BN_CLICKED(ID_PARAM_RESET_ALL, &ParametersDlg::OnResetAll)
	ON_BN_CLICKED(ID_PARAM_SAVE_ALL, &ParametersDlg::OnSaveAll)
	ON_MESSAGE(UWM_MAKE_LOCAL, &ParametersDlg::OnMakeLocalMsg)
	ON_MESSAGE(UWM_UNSELECT_PARAMS, &ParametersDlg::OnUnselectParamsMsg)
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL ParametersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRHMmain * main = CRHMmain::getInstance();
	this->initalizeModulesListBox(main);

	/**
	* Replace the placeholder pane with the parameters scroll pane.
	*/
	this->prameters_scroll_pane = new ParamDlgScrollablePane(this);
	CRect rectangle;
	GetDlgItem(ID_PARAM_PANE_PLACEHOLDER)->GetWindowRect(rectangle);
	ScreenToClient(&rectangle);
	this->prameters_scroll_pane->MoveWindow(rectangle);

	return TRUE;
}


void ParametersDlg::OnSelectModule()
{
	// Reset the parameters list box
	this->parameters_list_box.ResetContent();

	// Get the selected CString
	CString selectedText;
	int selectedIndex = this->modules_list_box.GetCurSel();
	this->modules_list_box.GetText(selectedIndex, selectedText);

	// Convert the CString to std::string
	CT2CA pszConvertedAnsiString(selectedText);
	std::string selectedString(pszConvertedAnsiString);

	// Used to track the length of the longest string
	size_t longestStringCount = 0;
	
	if (selectedString == "Shared")
	{
		/*
		* If selected module is the shared module iterate
		* through all shared parameters and add to list box.
		*/
		for (
			std::map<std::string, ClassPar*, Classless<std::string>>::iterator sharedIt = Global::SharedMapPars.begin();
			sharedIt != Global::SharedMapPars.end(); 
			sharedIt++
			)
		{
			std::string trimedString = sharedIt->first.substr(7, std::string::npos);
			CString paramName(trimedString.c_str());
			this->parameters_list_box.AddString(paramName);

			// Check if it is the longest string
			if (trimedString.size() > longestStringCount)
			{
				longestStringCount = trimedString.size();
			}
		}

	}
	else
	{
		// Remove module variation suffix from selected string
		int suffPos;
		if (suffPos = selectedString.find("#"), suffPos > -1)
		{
			selectedString = selectedString.substr(0, selectedString.length() - 2);
		}

		// Retrive the module from the model
		CRHMmain* model = CRHMmain::getInstance();
		std::map<std::string, ClassModule*>* modulesMap = model->getAllmodules();
		std::map<std::string, ClassModule*>::iterator selectedModuleIt = modulesMap->find(selectedString);

		if (!selectedModuleIt->second->isGroup)
		{
			// Module is not a group macro

			//Copy the parameters list and sort
			std::list<std::pair<std::string, ClassPar*>> parametersList = *selectedModuleIt->second->getParametersList();
			parametersList.sort(&ParametersDlg::compareParametersAlphabeticallyNoCase);

			// Add '*' to the begining of the shared parameters.
			for (
				std::list<std::pair<std::string, ClassPar*>>::iterator it = parametersList.begin();
				it != parametersList.end();
				it++
				)
			{
				if (it->second->module == "Shared")
				{
					it->first = "*" + it->first;
				}
			}

			// Add the parameter names to the list box
			for (
				std::list<std::pair<std::string, ClassPar*>>::iterator it = parametersList.begin();
				it != parametersList.end();
				it++
				)
			{
				CString paramName(it->first.c_str());
				this->parameters_list_box.AddString(paramName);

				// Check if it is the longest string
				if (it->first.size() > longestStringCount)
				{
					longestStringCount = it->first.size();
				}
			}

		}
		else
		{
			// Module is a group macro
			ClassMacro * groupModule = (ClassMacro *) selectedModuleIt->second;

			// Retrive list of modules that make up the group macro
			std::list<std::pair<std::string, ClassPar*>> allParametersList;
			groupModule->RetrieveAllParameters(&allParametersList);

			// Sort the list of parameters
			allParametersList.sort(&ParametersDlg::compareParametersAlphabeticallyNoCase);

			// Add '*' to the begining of the shared parameters.
			for (
				std::list<std::pair<std::string, ClassPar*>>::iterator it = allParametersList.begin();
				it != allParametersList.end();
				it++
				)
			{
				if (it->second->module == "Shared")
				{
					it->first = "*" + it->first;
				}
			}

			// Add the parameter names to the list box
			for (
				std::list<std::pair<std::string, ClassPar*>>::iterator it = allParametersList.begin();
				it != allParametersList.end();
				it++
				)
			{
				CString paramName(it->first.c_str());
				this->parameters_list_box.AddString(paramName);

				// Check if it is the longest string
				if (it->first.size() > longestStringCount)
				{
					longestStringCount = it->first.size();
				}
			}

		}

	}

	// Set horizontal extent based on the longest string
	this->parameters_list_box.SetHorizontalExtent(7 * longestStringCount);

	this->OnSelectParam();
}


void ParametersDlg::OnSelectParam()
{
	CWaitCursor wait;

	// Declare list to store parameter information in.
	std::list<std::pair<std::string, ClassPar*>> * parametersList = new std::list<std::pair<std::string, ClassPar*>>();

	// Iterate through the selected parameters
	int selectedCount = this->parameters_list_box.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	this->parameters_list_box.GetSelItems(selectedCount, selectedIndicies);
	for (int i = 0; i < selectedCount; i++)
	{
		// Extract the string of the parameter
		CString selectedParamText;
		this->parameters_list_box.GetText(selectedIndicies[i], selectedParamText);
		CT2CA pszConvertedAnsiString(selectedParamText); //Intermediary to convert CString to std::string
		std::string selectedParameterRaw(pszConvertedAnsiString);
		std::string selectedParameter;

		// Remove the * from a shared parameter
		if (selectedParameterRaw.find("*") != std::string::npos)
		{
			selectedParameter = selectedParameterRaw.substr(1, std::string::npos);
			selectedParameter = "Shared " + selectedParameter;
		}
		else
		{
			// Get the selected module CString
			CString moduleText;
			int moduleIndex = this->modules_list_box.GetCurSel();
			this->modules_list_box.GetText(moduleIndex, moduleText);

			// Convert the CString to std::string 
			CT2CA pszConvertedAnsiString(moduleText);
			std::string moduleString(pszConvertedAnsiString);

			// Remove module variation suffix from moduleString
			int suffPos;
			if (suffPos = moduleString.find("#"), suffPos > -1)
			{
				moduleString = moduleString.substr(0, moduleString.length() - 2);
			}

			selectedParameter = moduleString + " " + selectedParameterRaw;
		}

		std::map<std::string, ClassPar*>::iterator parameterIt = Global::MapPars.find(selectedParameter);
		
		parametersList->push_back(std::pair<std::string, ClassPar*>(selectedParameterRaw, parameterIt->second));

	}

	// Create the parameters cards to match the selected parameters.
	this->prameters_scroll_pane->SetParameterCards(parametersList);

	delete[] selectedIndicies;
	delete parametersList;
}


void ParametersDlg::OnToggleBasic()
{
	// Create a array of bools the size of the number 
	//     of parameters in the list box all set to false.
	int itemCount = this->parameters_list_box.GetCount();
	bool* toggles = new bool[itemCount];
	for (int i = 0; i < itemCount; i++)
	{
		toggles[i] = false;
	}

	// Set the toggles of the selected parameters to true.
	int selectedCount = this->parameters_list_box.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	this->parameters_list_box.GetSelItems(selectedCount, selectedIndicies);
	for (int i = 0; i < selectedCount; i++)
	{
		toggles[selectedIndicies[i]] = true;
	}

	// Reverse all the toggles that corrispond to basic parameters.
	for (int i = 0; i < itemCount; i++)
	{
		CString selectedText;
		this->parameters_list_box.GetText(i, selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedParameter(pszConvertedAnsiString);

		
		if (selectedParameter.find("*") != std::string::npos)
		{
			// Shared Parameter: remove shared asterix and add Shared prefix
			selectedParameter = selectedParameter.substr(1, std::string::npos);
			selectedParameter = "Shared " + selectedParameter;
		}
		else
		{
			// Get the selected module CString
			CString moduleText;
			int moduleIndex = this->modules_list_box.GetCurSel();
			this->modules_list_box.GetText(moduleIndex, moduleText);

			// Convert the CString to std::string 
			CT2CA pszConvertedAnsiString(moduleText);
			std::string moduleString(pszConvertedAnsiString);

			// Remove module variation suffix from moduleString
			int suffPos;
			if (suffPos = moduleString.find("#"), suffPos > -1)
			{
				moduleString = moduleString.substr(0, moduleString.length() - 2);
			}

			selectedParameter = moduleString + " " + selectedParameter;
		}

		std::map<std::string, ClassPar*>::iterator parameterIt = Global::MapPars.find(selectedParameter);

		if (parameterIt->second->visibility == TVISIBLE::USUAL)
		{
			if (toggles[i])
			{
				toggles[i] = false;
			}
			else
			{
				toggles[i] = true;
			}
		}

	}

	// Set the parameters list box based on the toggles array.
	for (int i = 0; i < itemCount; i++)
	{
		this->parameters_list_box.SetSel(i, toggles[i]);
	}

	// Remove the temporary arrays.
	delete[] selectedIndicies;
	delete[] toggles;

	// Call to update the parameter cards.
	this->OnSelectParam();
}


void ParametersDlg::OnToggleAdvance()
{
	// Create a array of bools the size of the number 
	//     of parameters in the list box all set to false.
	int itemCount = this->parameters_list_box.GetCount();
	bool* toggles = new bool[itemCount];
	for (int i = 0; i < itemCount; i++)
	{
		toggles[i] = false;
	}

	// Set the toggles of the selected parameters to true.
	int selectedCount = this->parameters_list_box.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	this->parameters_list_box.GetSelItems(selectedCount, selectedIndicies);
	for (int i = 0; i < selectedCount; i++)
	{
		toggles[selectedIndicies[i]] = true;
	}

	// Reverse all the toggles that corrispond to advance parameters.
	for (int i = 0; i < itemCount; i++)
	{
		CString selectedText;
		this->parameters_list_box.GetText(i, selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedParameter(pszConvertedAnsiString);


		if (selectedParameter.find("*") != std::string::npos)
		{
			// Shared Parameter: remove shared asterix and add Shared prefix
			selectedParameter = selectedParameter.substr(1, std::string::npos);
			selectedParameter = "Shared " + selectedParameter;
		}
		else
		{
			// Get the selected module CString
			CString moduleText;
			int moduleIndex = this->modules_list_box.GetCurSel();
			this->modules_list_box.GetText(moduleIndex, moduleText);

			// Convert the CString to std::string 
			CT2CA pszConvertedAnsiString(moduleText);
			std::string moduleString(pszConvertedAnsiString);

			// Remove module variation suffix from moduleString
			int suffPos;
			if (suffPos = moduleString.find("#"), suffPos > -1)
			{
				moduleString = moduleString.substr(0, moduleString.length() - 2);
			}

			selectedParameter = moduleString + " " + selectedParameter;
		}

		std::map<std::string, ClassPar*>::iterator parameterIt = Global::MapPars.find(selectedParameter);

		if (parameterIt->second->visibility == TVISIBLE::DIAGNOSTIC)
		{
			if (toggles[i])
			{
				toggles[i] = false;
			}
			else
			{
				toggles[i] = true;
			}
		}

	}

	// Set the parameters list box based on the toggles array.
	for (int i = 0; i < itemCount; i++)
	{
		this->parameters_list_box.SetSel(i, toggles[i]);
	}

	// Remove the temporary arrays.
	delete[] selectedIndicies;
	delete[] toggles;

	// Call to update the parameter cards.
	this->OnSelectParam();
}


void ParametersDlg::OnTogglePrivate()
{
	// Create a array of bools the size of the number 
	//     of parameters in the list box all set to false.
	int itemCount = this->parameters_list_box.GetCount();
	bool* toggles = new bool[itemCount];
	for (int i = 0; i < itemCount; i++)
	{
		toggles[i] = false;
	}

	// Set the toggles of the selected parameters to true.
	int selectedCount = this->parameters_list_box.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	this->parameters_list_box.GetSelItems(selectedCount, selectedIndicies);
	for (int i = 0; i < selectedCount; i++)
	{
		toggles[selectedIndicies[i]] = true;
	}

	// Reverse all the toggles that corrispond to advance parameters.
	for (int i = 0; i < itemCount; i++)
	{
		CString selectedText;
		this->parameters_list_box.GetText(i, selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedParameter(pszConvertedAnsiString);


		if (selectedParameter.find("*") != std::string::npos)
		{
			// Shared Parameter: remove shared asterix and add Shared prefix
			selectedParameter = selectedParameter.substr(1, std::string::npos);
			selectedParameter = "Shared " + selectedParameter;
		}
		else
		{
			// Get the selected module CString
			CString moduleText;
			int moduleIndex = this->modules_list_box.GetCurSel();
			this->modules_list_box.GetText(moduleIndex, moduleText);

			// Convert the CString to std::string 
			CT2CA pszConvertedAnsiString(moduleText);
			std::string moduleString(pszConvertedAnsiString);

			// Remove module variation suffix from moduleString
			int suffPos;
			if (suffPos = moduleString.find("#"), suffPos > -1)
			{
				moduleString = moduleString.substr(0, moduleString.length() - 2);
			}

			selectedParameter = moduleString + " " + selectedParameter;
		}

		std::map<std::string, ClassPar*>::iterator parameterIt = Global::MapPars.find(selectedParameter);

		if (parameterIt->second->visibility == TVISIBLE::PRIVATE)
		{
			if (toggles[i])
			{
				toggles[i] = false;
			}
			else
			{
				toggles[i] = true;
			}
		}

	}

	// Set the parameters list box based on the toggles array.
	for (int i = 0; i < itemCount; i++)
	{
		this->parameters_list_box.SetSel(i, toggles[i]);
	}

	// Remove the temporary arrays.
	delete[] selectedIndicies;
	delete[] toggles;

	// Call to update the parameter cards.
	this->OnSelectParam();
}


void ParametersDlg::OnToggleAll()
{
	// Create a array of bools the size of the number 
	//     of parameters in the list box all set to false.
	int itemCount =	this->parameters_list_box.GetCount();
	bool* toggles = new bool[itemCount];
	for (int i = 0; i < itemCount; i++)
	{
		toggles[i] = false;
	}

	// Set the toggles of the selected parameters to true.
	int selectedCount = this->parameters_list_box.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	this->parameters_list_box.GetSelItems(selectedCount, selectedIndicies);
	for (int i = 0; i < selectedCount; i++)
	{
		toggles[selectedIndicies[i]] = true;
	}

	// Reverse all the toggles.
	for (int i = 0; i < itemCount; i++)
	{
		if (toggles[i])
		{
			toggles[i] = false;
		}
		else
		{
			toggles[i] = true;
		}
	}

	// Set the parameters list box based on the toggles array.
	for (int i = 0; i < itemCount; i++)
	{
		this->parameters_list_box.SetSel(i, toggles[i]);
	}

	// Remove the temporary arrays.
	delete[] selectedIndicies;
	delete[] toggles;

	// Call to update the parameter cards.
	this->OnSelectParam();
}


void ParametersDlg::OnResetAll()
{
	this->prameters_scroll_pane->ResetAllCards();
}


void ParametersDlg::OnSaveAll()
{
	this->prameters_scroll_pane->SaveAllCards();
}


void ParametersDlg::initalizeModulesListBox(CRHMmain* main)
{
	//Add the "Shared" module to the list box
	this->modules_list_box.AddString(L"Shared");

	//Get the list of used modules and copy into a seccond list for sorting.
	std::list<std::pair<std::string, ClassModule*>>* modules_list = main->getOurModules();
	std::list<std::pair<std::string, ClassModule*>> sorted_modules_list = *modules_list;

	// Sort the list of modules alphabeticaly ignoring case.
	sorted_modules_list.sort(&ParametersDlg::compareModulesAlphabeticallyNoCase);

	//Keep track of the longest string and use to set horizontal extent
	size_t longStringCount = 0;

	// Place each of the modules into the list box
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator moduleIteratior = sorted_modules_list.begin();
		moduleIteratior != sorted_modules_list.end();
		moduleIteratior++
		)
	{
		// If the module has a varaition append the apropreate suffix
		if (moduleIteratior->second->variation != 0)
		{
			std::string varSuffix("#0");
			varSuffix[1] += (char)(log(moduleIteratior->second->variation) / log(2) + 1);
			std::string moduleStringWithVariation = moduleIteratior->first + varSuffix;
			
			// Add the module to the list box if it has parameters or it is a group module
			CString moduleName(moduleStringWithVariation.c_str());

			if (!moduleIteratior->second->getParametersList()->empty() || moduleIteratior->second->isGroup)
			{
				this->modules_list_box.AddString(moduleName);

				// Check the length of the string
				if (moduleStringWithVariation.size() > longStringCount)
				{
					longStringCount = moduleStringWithVariation.size();
				}
			}

		}
		else
		{
			// Add the module to the list box
			CString moduleName(moduleIteratior->first.c_str());
			
			if (!moduleIteratior->second->getParametersList()->empty() || moduleIteratior->second->isGroup)
			{
				this->modules_list_box.AddString(moduleName);

				// Check the length of the string
				if (moduleIteratior->first.size() > longStringCount)
				{
					longStringCount = moduleIteratior->first.size();
				}
			}

		}
		
	}

	// Set horizontal extent based on the longest string 
	this->modules_list_box.SetHorizontalExtent(7 * longStringCount);
}


BOOL ParametersDlg::compareModulesAlphabeticallyNoCase(std::pair<std::string, ClassModule*> item_a, std::pair<std::string, ClassModule*> item_b)
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


BOOL ParametersDlg::compareParametersAlphabeticallyNoCase(std::pair<std::string, ClassPar*> item_a, std::pair<std::string, ClassPar*> item_b)
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


LRESULT ParametersDlg::OnMakeLocalMsg(WPARAM wParam, LPARAM lParam)
{
	// Get the selected 
	CString selectedText;
	int selectedIndex = this->modules_list_box.GetCurSel();
	this->modules_list_box.GetText(selectedIndex, selectedText);

	// Convert the CString to std::string
	CT2CA pszConvertedAnsiString(selectedText);
	std::string selectedString(pszConvertedAnsiString);

	std::map<std::string, ClassModule* >::iterator module = Global::AllModulesList->find(selectedString);

	if (!module->second->isGroup)
	{
		std::list<std::pair<std::string, ClassPar*>>* parametersList = module->second->getParametersList();

		ClassPar* par = (ClassPar*)wParam;

		for (
			std::list<std::pair<std::string, ClassPar*>>::iterator it = parametersList->begin();
			it != parametersList->end();
			it++
			)
		{
			if (it->first == par->param)
			{
				parametersList->erase(it);
				break;
			}
		}


		ClassPar* newPar = new ClassPar(*par);
		newPar->module = selectedString.c_str();

		parametersList->push_back(std::pair<std::string, ClassPar*>(newPar->param, newPar));

		PairPar Item = PairPar(newPar->module + ' ' + newPar->param, newPar);
		Global::MapPars.insert(Item);

		/* Preserve the selected parameters */
		int selectedCount = this->parameters_list_box.GetSelCount();
		int* selectedIndicies = new int[selectedCount];
		this->parameters_list_box.GetSelItems(selectedCount, selectedIndicies);

		this->OnSelectModule();

		/* Re-select the preserved parameters */
		for (int i = 0; i < selectedCount; i++)
		{
			this->parameters_list_box.SetSel(selectedIndicies[i], true);
		}

		this->OnSelectParam();
	}
	else
	{
		// Module is a group macro
		ClassMacro* groupModule = (ClassMacro*)module->second;

		// Retrive list of modules that make up the group macro 
		std::vector<std::pair<std::string, ClassModule*>>* modulesVector = groupModule->GrpStringList;
		// Declare a list to hold the parameters
		std::list<std::pair<std::string, ClassPar*>> allParametersList;

		ClassPar* par = (ClassPar*)wParam;

		std::list<std::pair<std::string, ClassPar*>>* parametersList = NULL;

		bool found = false;

		// For each module add the assoicated parameters to the list. 
		for (
			std::vector<std::pair<std::string, ClassModule*>>::iterator modulesIt = modulesVector->begin();
			modulesIt != modulesVector->end();
			modulesIt++
			)
		{
			if (found)
			{
				break;
			}

			parametersList = modulesIt->second->getParametersList();

			for (
				std::list<std::pair<std::string, ClassPar*>>::iterator it = parametersList->begin();
				it != parametersList->end();
				it++
				)
			{
				if (it->first == par->param)
				{
					parametersList->erase(it);
					found = true;
					break;
				}
			}

		}

		ClassPar* newPar = new ClassPar(*par);
		newPar->module = selectedString.c_str();

		parametersList->push_back(std::pair<std::string, ClassPar*>(newPar->param, newPar));

		PairPar Item = PairPar(newPar->module + ' ' + newPar->param, newPar);
		Global::MapPars.insert(Item);

		/* Preserve the selected parameters */
		int selectedCount = this->parameters_list_box.GetSelCount();
		int* selectedIndicies = new int[selectedCount];
		this->parameters_list_box.GetSelItems(selectedCount, selectedIndicies);

		this->OnSelectModule();

		/* Re-select the preserved parameters */
		for (int i = 0; i < selectedCount; i++)
		{
			this->parameters_list_box.SetSel(selectedIndicies[i], true);
		}

		this->OnSelectParam();

	}

	return 0;
}


LRESULT ParametersDlg::OnUnselectParamsMsg(WPARAM wParam, LPARAM lParam)
{
	std::list<std::pair<std::string, ClassPar*>>* unselectList = (std::list<std::pair<std::string, ClassPar*>>*) wParam;

	for (
		std::list<std::pair<std::string, ClassPar*>>::iterator it = unselectList->begin();
		it != unselectList->end();
		it++
		)
	{
		int itemCount = this->parameters_list_box.GetCount();
		for (int i = 0; i < itemCount; i++)
		{
			CString itemText;
			this->parameters_list_box.GetText(i, itemText);

			// Convert the CString to std::string
			CT2CA pszConvertedAnsiString(itemText);
			std::string itemString(pszConvertedAnsiString);

			if (itemString == it->first)
			{
				this->parameters_list_box.SetSel(i, false);
				break;
			}

		}


	}

	return 0;
}


void ParametersDlg::OnSize(UINT nType, int cx, int cy)
{
	CWnd * wnd = GetDlgItem(ID_PARAM_PANE_PLACEHOLDER);

	if (wnd != NULL)
	{
		CRect rectangle;
		GetDlgItem(ID_PARAM_PANE_PLACEHOLDER)->GetWindowRect(rectangle);
		ScreenToClient(&rectangle);
		this->prameters_scroll_pane->MoveWindow(rectangle);
	}

}


void ParametersDlg::OnCancel()
{
	std::map<std::string, std::list<ClassPar*>*>* candidates = RetrieveConsolidationCandidates();

	if (candidates->size() > 0)
	{
		ConsolidateParamDlg * consolidateParamDlg = new ConsolidateParamDlg(candidates);

		consolidateParamDlg->DoModal();

		delete consolidateParamDlg;
	}

	/* Delete lists in candidates */
	for (
		std::map<std::string, std::list<ClassPar*>*>::iterator it = candidates->begin();
		it != candidates->end();
		it++
		)
	{
		delete it->second;
	}
	delete candidates;

	CDialogEx::OnCancel();
}


std::map<std::string, std::list<ClassPar*>*>* ParametersDlg::RetrieveConsolidationCandidates()
{
	/* Make a list of all the parameters */
	std::list<std::pair<std::string, ClassPar*>> allParametersList =  std::list<std::pair<std::string, ClassPar*>>();

	CRHMmain* main = CRHMmain::getInstance();
	std::list<std::pair<std::string, ClassModule*>> * modulesList = main->getOurModules();

	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modulesListIt = modulesList->begin();
		modulesListIt != modulesList->end();
		modulesListIt++
		)
	{
		if (!modulesListIt->second->isGroup)
		{
			// Not a group module
			std::list<std::pair<std::string, ClassPar*>>* parametersList = modulesListIt->second->getParametersList();

			for (
				std::list<std::pair<std::string, ClassPar*>>::iterator parametersListIt = parametersList->begin();
				parametersListIt != parametersList->end();
				parametersListIt++
				)
			{
				allParametersList.push_back(std::pair<std::string, ClassPar*>(parametersListIt->first, parametersListIt->second));
			}

		}
		else
		{
			// Is a group module
			ClassMacro* groupModule = (ClassMacro*)modulesListIt->second;

			groupModule->RetrieveAllParameters(&allParametersList);

		}

	}

	/* Sort the list alphabetically */
	allParametersList.sort(&ParametersDlg::compareParametersAlphabeticallyNoCase);

	/* Walk through the list looking for segments where parametrs have the same name */
	
	std::list<std::pair<std::string, ClassPar*>>::iterator leftCursor = allParametersList.begin();
	std::list<std::pair<std::string, ClassPar*>>::iterator rightCursor = allParametersList.begin();
	
	std::map<std::string, std::list<ClassPar*>*>* candidates = new std::map<std::string, std::list<ClassPar*>*>();

	while (rightCursor != allParametersList.end())
	{
		while (rightCursor != allParametersList.end() && leftCursor->first == rightCursor->first  )
		{
			rightCursor++;

			if (rightCursor != allParametersList.end())
			{
				if (ClassPar::ConsolidationCandidates(leftCursor->second, rightCursor->second))
				{
					
					if (candidates->find(leftCursor->first) != candidates->end())
					{
						/* A parameter with this name is already in the candidate map*/
						std::map<std::string, std::list<ClassPar*>*>::iterator entry = candidates->find(leftCursor->first);

						std::list<ClassPar*>* entryList = entry->second;

						/* Check if leftCursor can be added ie it is consoladatable with all*/
						


						/* Check if rightCursor can be added*/

					}
					else
					{
						/* Need to add this parameter name to the candidate map */
						
						/* Compose a list of all of the unique paramters with this name */
						std::list<ClassPar*>* entryList = new std::list<ClassPar*>();

						/* Add the inital two to the list */
						entryList->push_back(leftCursor->second);
						entryList->push_back(rightCursor->second);

						/* 
						* Look for more parameters that are candidates for consolidation with every 
						* other candidate and not yet added.
						*/
						do
						{
							bool unique = true;
							for (
								std::list<ClassPar*>::iterator it = entryList->begin();
								it != entryList->end();
								it++
								)
							{
								if (*it == rightCursor->second)
								{
									unique = false;
								}
							}

							if (unique && ClassPar::ConsolidationCandidates(leftCursor->second, rightCursor->second))
							{
								entryList->push_back(rightCursor->second);
							}

							rightCursor++;
						} while (rightCursor != allParametersList.end() && leftCursor->first == rightCursor->first);

						candidates->insert(std::pair<std::string, std::list<ClassPar*>*>(leftCursor->first, entryList));
					}


				}
			}

			
		}

		leftCursor = rightCursor;
		
	}

	return candidates;
}