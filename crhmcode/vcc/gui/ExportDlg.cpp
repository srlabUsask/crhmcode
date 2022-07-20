#include "ExportDlg.h"


IMPLEMENT_DYNAMIC(ExportDlg, CDialog)


ExportDlg::ExportDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(EXPORT_DLG, pParent)
{
	this->next_line = 0;
}


ExportDlg::~ExportDlg()
{

}


void ExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EXPORT_CHOICES_LIST_BOX, outputs_list_box);
	DDX_Control(pDX, ID_EXPORT_SELECTED_LIST_BOX, selected_list_box);
	DDX_Control(pDX, ID_EXPORT_PREVIEW_MORE, preview_button);
	DDX_Control(pDX, ID_EXPORT_FORMAT_BTN, format_toggle);
	DDX_Control(pDX, ID_EXPORT_PREVIEW_EDIT_BOX, preview_list_box);
}


BEGIN_MESSAGE_MAP(ExportDlg, CDialog)
	ON_LBN_SELCHANGE(ID_EXPORT_CHOICES_LIST_BOX, &ExportDlg::OnOutputsSelectionChange)
	ON_LBN_SELCHANGE(ID_EXPORT_SELECTED_LIST_BOX, &ExportDlg::OnSelectedSelectionChange)
	ON_BN_CLICKED(ID_EXPORT_PREVIEW_MORE, &ExportDlg::OnPreviewPressed)
	ON_COMMAND(ID_EXPORT_SAVE, &ExportDlg::OnSave)
	ON_COMMAND(ID_EXPORT_SAVE_AS, &ExportDlg::OnSaveAs)
	ON_COMMAND(ID_EXPORT_EXIT, &ExportDlg::OnExit)
END_MESSAGE_MAP()


BOOL ExportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	format_toggle.AddString(L"Standard");
	format_toggle.AddString(L"OBS");
	format_toggle.AddString(L"STD w/ MS dates");
	format_toggle.AddString(L"STD w/ YYYYMMDD dates");
	format_toggle.SetCurSel(0);

	outputs_list_box.ResetContent();
	selected_list_box.ResetContent();

	CRHMmain* model = CRHMmain::getInstance();
	
	if (model->getFinishedRun())
	{
		for (size_t i = 0; i < model->SelectedVariables->size(); i++)
		{
			std::string varName = model->cdSeries[i]->getTitle();
			outputs_list_box.AddString(CString(varName.c_str()));
		}
	}

	for (
		std::list<std::pair<std::string, TSeries*>>::iterator it = model->SelectedObservations->begin();
		it != model->SelectedObservations->end();
		it++
		)
	{
		if (it->second->Count() > 0)
		{
		std::string obsName = it->first;
		outputs_list_box.AddString(CString(obsName.c_str()));
		}
	}

	return true;
}


void ExportDlg::OnOutputsSelectionChange()
{
	int selectedCount = outputs_list_box.GetSelCount();
	int * selectedIndicies = new int[selectedCount];
	outputs_list_box.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		outputs_list_box.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		int found = selected_list_box.FindStringExact(-1, selectedText);
		if (found == LB_ERR)
		{
			selected_list_box.AddString(selectedText);
		}

	}

	this->next_line = 0;

	delete[] selectedIndicies;
}


void ExportDlg::OnSelectedSelectionChange()
{
	int selectedCount = selected_list_box.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	selected_list_box.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		selected_list_box.DeleteString(selectedIndicies[i]);
	}

	this->next_line = 0;

	delete[] selectedIndicies;
}


void ExportDlg::OnPreviewPressed()
{
	CWaitCursor wait;

	preview_list_box.ResetContent();

	CRHMmain* model = CRHMmain::getInstance();

	std::string Sx;
	std::string Sy;

	std::vector<TSeries*>* data = this->PrepareDataForExport();

	//Output the header

	int formatIndex = format_toggle.GetCurSel();

	int charsInLongestLine = 0;

	if (formatIndex == 1)
	{
		preview_list_box.AddString(L"Future File Description");
		for (size_t i = 0; i < data->size(); i++)
		{
			ClassVar* thisVar = data->at(i)->getTag();
			Sx = data->at(i)->getTitle();
			Sx += std::string(" 1 ");
			Sx += thisVar->units;

			if (Sx.length() > charsInLongestLine)
			{
				charsInLongestLine = Sx.length();
			}

			preview_list_box.AddString(CString(Sx.c_str()));
		}

		Sx = "###### time";
		for (size_t i = 0; i < data->size(); i++)
		{
			std::string S = data->at(i)->getTitle();
			Sx.append("\t");
			Sx.append(S);
		}

		if (Sx.length() > charsInLongestLine)
		{
			charsInLongestLine = Sx.length();
		}

		preview_list_box.AddString(CString(Sx.c_str()));

	}
	else
	{
		Sx = "time";
		for (size_t i = 0; i < data->size(); i++)
		{
			std::string S = data->at(i)->getTitle();
			Sx.append("\t");
			Sx.append(S);
		}

		if (Sx.length() > charsInLongestLine)
		{
			charsInLongestLine = Sx.length();
		}

		preview_list_box.AddString(CString(Sx.c_str()));

		Sx = "units";
		for (size_t i = 0; i < data->size(); i++)
		{
			ClassVar* thisVar = data->at(i)->getTag();
			std::string S = thisVar->units;
			Sx.append("\t");
			Sx.append(S);
		}

		if (Sx.length() > charsInLongestLine)
		{
			charsInLongestLine = Sx.length();
		}

		preview_list_box.AddString(CString(Sx.c_str()));
	}

	
	if (data->size() > 0)
	{

		for (long index = 0 + this->next_line; (index < this->next_line + 1000) && (index < data->at(0)->Count()); index++)
		{
			std::string Sx = FloatToStrF(data->at(0)->XValue(index), TFloatFormat::ffGeneral, 10, 0);
			Sx = StandardConverterUtility::GetDateTimeInStringForOutput(data->at(0)->XValue(index));

			switch (formatIndex)
			{
			case 0: //:ISO date
				Sx = StandardConverterUtility::FormatDateTime("ISO", data->at(0)->XValue(index));
				break;
			case 1: //MS date
				Sx = FloatToStrF(data->at(0)->XValue(index), TFloatFormat::ffGeneral, 10, 0);
				break;
			case 2: //MS date
				Sx = FloatToStrF(data->at(0)->XValue(index), TFloatFormat::ffGeneral, 10, 0);
				break;
			case 3: //yyyy-mm-dd hh:mm date
				Sx = StandardConverterUtility::FormatDateTime("yyyy-mm-dd hh:mm ", data->at(0)->XValue(index));
				break;
			}

			for (size_t i = 0; i < data->size(); i++)
			{

				ClassVar* thisVar = data->at(i)->getTag();
				int prec = 7;
				//Manishankar did this, because GCC is showing segmentation fault here. thisVar remains null.

				if (thisVar->varType == TVar::Int || thisVar->varType == TVar::ReadI)
				{
					prec = 7;
				}

				std::string Sy = FloatToStrF(data->at(i)->YValue(index), TFloatFormat::ffGeneral, prec, 10);
				Sx = Sx + "\t" + Sy;

			}

			if (Sx.length() > charsInLongestLine)
			{
				charsInLongestLine = Sx.length();
			}

			preview_list_box.AddString(CString(Sx.c_str()));
		}

	}

	preview_list_box.SetHorizontalExtent(charsInLongestLine * 12);

	this->next_line += 1000;
	if (this->next_line > Global::DTmax)
	{
		this->next_line = 0;
	}

	for (size_t i = 0; i < data->size(); i++)
	{
		delete data->at(i);
	}

	delete data;
}


void ExportDlg::OnSave()
{
	CWaitCursor wait;

	CRHMmain* model = CRHMmain::getInstance();

	std::string exportFileName = model->OpenNameReport;

	size_t extStart = exportFileName.find_last_of(".");
	std::string extension = exportFileName.substr(extStart, std::string::npos);
	exportFileName = exportFileName.substr(0, extStart);

	if (this->format_toggle.GetCurSel() == 1)
	{
		extension = ".obs";
	}
	else
	{
		extension = ".txt";
	}

	exportFileName.append(extension);

	std::vector<TSeries*>* processedData = this->PrepareDataForExport();

	exportToFile(exportFileName, processedData);

	for (size_t i = 0; i < processedData->size(); i++)
	{
		delete processedData->at(i);
	}

	delete processedData;
}


void ExportDlg::OnSaveAs()
{
	TCHAR * szFilters;
	CString fileType1;
	CString fileType2;

	if (this->format_toggle.GetCurSel() == 1)
	{
		szFilters = _T("MyType Files (*.obs)|*.obs|All Files (*.*)|*.*||");
		fileType1 = _T("obs");
		fileType2 = _T("*.obs");
	}
	else
	{
		szFilters = _T("MyType Files (*.txt)|*.txt|All Files (*.*)|*.*||");
		fileType1 = _T("txt");
		fileType2 = _T("*.txt");
	}

	CFileDialog fileDlg(FALSE, fileType1, fileType2,
		OFN_HIDEREADONLY, szFilters);

	if (fileDlg.DoModal() == IDOK)
	{
		CWaitCursor wait;

		CString fileName = fileDlg.GetPathName();
		std::string filePath = CT2A(fileName.GetString());

		std::vector<TSeries*>* processedData = this->PrepareDataForExport();

		exportToFile(filePath, processedData);

		for (size_t i = 0; i < processedData->size(); i++)
		{
			delete processedData->at(i);
		}

		delete processedData;
	}
}


void ExportDlg::OnExit()
{
	this->OnCancel();
}


void ExportDlg::exportToFile(std::string filePath, std::vector<TSeries*>* data)
{
	std::basic_ofstream<char, std::char_traits<char>> exportStream = std::basic_ofstream<char, std::char_traits<char>>();
	exportStream.open(filePath);

	if (!exportStream.is_open())
	{
		CRHMException e = CRHMException("Cannot open file " + filePath + " to save report.", TExcept::ERR);
		CRHMLogger::instance()->log_run_error(e);
	}

	CRHMmain* model = CRHMmain::getInstance();

	std::string Sx;
	std::string Sy;

	int formatIndex = format_toggle.GetCurSel();

	if (formatIndex == 1)
	{
		exportStream << "Future File Description" << endl;
		for (size_t i = 0; i < data->size(); i++)
		{
			ClassVar* thisVar = data->at(i)->getTag();
			Sx = data->at(i)->getTitle();
			Sx += std::string(" 1 ");
			Sx += thisVar->units;
			exportStream << Sx.c_str() << endl;
		}

		Sx = "###### time";
		for (size_t i = 0; i < data->size(); i++)
		{
			std::string S = data->at(i)->getTitle();
			Sx.append("\t");
			Sx.append(S);
		}

		exportStream << Sx.c_str() << endl;

	}
	else
	{
		Sx = "time";
		for (size_t i = 0; i < data->size(); i++)
		{
			std::string S = data->at(i)->getTitle();
			Sx.append("\t");
			Sx.append(S);
		}
		exportStream << Sx.c_str() << endl;


		Sx = "units";
		for (size_t i = 0; i < data->size(); i++)
		{
			ClassVar* thisVar = data->at(i)->getTag();
			std::string S = thisVar->units;
			Sx.append("\t");
			Sx.append(S);
		}
		exportStream << Sx.c_str() << endl;
	}

	if (data->size() > 0)
	{

		for (long index = 0; index < data->at(0)->Count(); index++)
		{
			std::string Sx = FloatToStrF(data->at(0)->XValue(index), TFloatFormat::ffGeneral, 10, 0);
			Sx = StandardConverterUtility::GetDateTimeInStringForOutput(data->at(0)->XValue(index));

			switch (formatIndex)
			{
			case 0: //:ISO date
				Sx = StandardConverterUtility::FormatDateTime("ISO", data->at(0)->XValue(index));
				break;
			case 1: //MS date
				Sx = FloatToStrF(data->at(0)->XValue(index), TFloatFormat::ffGeneral, 10, 0);
				break;
			case 2: //MS date
				Sx = FloatToStrF(data->at(0)->XValue(index), TFloatFormat::ffGeneral, 10, 0);
				break;
			case 3: //yyyy-mm-dd hh:mm date
				Sx = StandardConverterUtility::FormatDateTime("yyyy-mm-dd hh:mm ", data->at(0)->XValue(index));
				break;
			}

			for (size_t i = 0; i < data->size(); i++)
			{

				ClassVar* thisVar = data->at(i)->getTag();
				int prec = 7;
				//Manishankar did this, because GCC is showing segmentation fault here. thisVar remains null.

				if (thisVar->varType == TVar::Int || thisVar->varType == TVar::ReadI)
				{
					prec = 7;
				}

				std::string Sy = FloatToStrF(data->at(i)->YValue(index), TFloatFormat::ffGeneral, prec, 10);
				Sx = Sx + "\t" + Sy;

			}

			exportStream << Sx.c_str() << endl;
		}

	}

	exportStream.close();

}


std::vector<TSeries*>* ExportDlg::PrepareDataForExport()
{
	CRHMmain* model = CRHMmain::getInstance();
	
	std::vector<TSeries*>* selectedSeries = new std::vector<TSeries*>();

	for (int i = 0; i < this->selected_list_box.GetCount(); i++)
	{
		CString labelText;
		std::string labelString;
		this->selected_list_box.GetText(i, labelText);
		CT2CA pszConvertedAnsiString(labelText);
		labelString.assign(pszConvertedAnsiString);

		size_t suffixStartPos = labelString.rfind('_');

		bool validSuffix = false;
		if (suffixStartPos != std::string::npos)
		{
			validSuffix = IsValidSuffix(labelString.substr(suffixStartPos, std::string::npos));
		}

		if (suffixStartPos != std::string::npos && validSuffix)
		{
			/* Has a suffix look for label in selected observations */
			for (
				std::list<std::pair<std::string, TSeries*>>::iterator selObsIt = model->SelectedObservations->begin();
				selObsIt != model->SelectedObservations->end();
				selObsIt++
				)
			{
				if (selObsIt->first == labelString)
				{
					selectedSeries->push_back(new TSeries(selObsIt->second));
					break;
				}
			}
		}
		else
		{
			bool found = false;

			if (model->getFinishedRun())
			{
				/* Does not have a suffix look for it in variables first */
				for (size_t i = 0; i < model->SelectedVariables->size(); i++)
				{
					if (model->cdSeries[i]->getTitle() == labelString)
					{
						selectedSeries->push_back(new TSeries(model->cdSeries[i]));
						found = true;
						break;
					}
				}
			}

			/* If it was not found in variables look for it in selected observations */
			if (!found)
			{
				for (
					std::list<std::pair<std::string, TSeries*>>::iterator selObsIt = model->SelectedObservations->begin();
					selObsIt != model->SelectedObservations->end();
					selObsIt++
					)
				{
					if (selObsIt->first == labelString)
					{
						selectedSeries->push_back(new TSeries(selObsIt->second));
						break;
					}
				}
			}

		}

	}

	/* Find a the series with the most points */
	long maxPoints = 0;
	TSeries* longSeries = NULL;
	for (
		std::vector<TSeries*>::iterator seriesIt = selectedSeries->begin();
		seriesIt != selectedSeries->end();
		seriesIt++
		)
	{
		if (maxPoints < (*seriesIt)->Count())
		{
			maxPoints = (*seriesIt)->Count();
			longSeries = (*seriesIt);
		}
	}

	std::vector<double> lastValue;
	for (size_t i = 0; i < selectedSeries->size(); i++)
	{
		lastValue.push_back(0.0);
	}

	for (long i = 0; i < maxPoints; i++)
	{
		double timeValue = longSeries->XValue(i);
		std::string Sx = StandardConverterUtility::GetDateTimeInStringForOutput(timeValue);

		for (size_t j = 0; j < selectedSeries->size(); j++)
		{

			long pointIndex = selectedSeries->at(j)->findPointOnXAxis(timeValue);
			
			if (pointIndex != -1)
			{
				lastValue[j] = selectedSeries->at(j)->YValue(i);
			}
			else 
			{
				selectedSeries->at(j)->InsertXY(i, timeValue, lastValue.at(j));
			}

		}

	}

	return selectedSeries;
}


bool ExportDlg::IsValidSuffix(std::string suffix)
{
	bool valid = false;

	if (suffix == "_Tot")
	{
		valid = true;
	}
	else if (suffix == "_Min")
	{
		valid = true;
	}
	else if (suffix == "_Max")
	{
		valid = true;
	}
	else if (suffix == "_Avg")
	{
		valid = true;
	}
	else if (suffix == "_Dlta")
	{
		valid = true;
	}
	else if (suffix == "_Pos")
	{
		valid = true;
	}
	else if (suffix == "_First")
	{
		valid = true;
	}
	else if (suffix == "_Last")
	{
		valid = true;
	}
	else if (suffix == "_Cnt")
	{
		valid = true;
	}
	else if (suffix == "_Cnt0")
	{
		valid = true;
	}
	else if (suffix == "_VPsat")
	{
		valid = true;
	}
	else if (suffix == "_WtoMJ")
	{
		valid = true;
	}
	else if (suffix == "_MJtoW")
	{
		valid = true;
	}

	return valid;
}