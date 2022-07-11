#include "CExport.h"

IMPLEMENT_DYNAMIC(CExport, CDialog)

CExport::CExport(CWnd* pParent /*=nullptr*/)
	: CDialog(EXPORT_DLG, pParent)
{

}

CExport::~CExport()
{

}

void CExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EXPORT_CHOICES_LIST_BOX, choicesListBox);
	DDX_Control(pDX, ID_EXPORT_SELECTED_LIST_BOX, selectedListBox);
	DDX_Control(pDX, ID_EXPORT_PREVIEW_MORE, previewMoreButton);
	DDX_Control(pDX, ID_EXPORT_FORMAT_BTN, formatToggle);
	DDX_Control(pDX, ID_EXPORT_PREVIEW_EDIT_BOX, previewEditBox);
}


BEGIN_MESSAGE_MAP(CExport, CDialog)
	ON_LBN_SELCHANGE(ID_EXPORT_CHOICES_LIST_BOX, &CExport::OnChoicesSelectionChange)
	ON_LBN_SELCHANGE(ID_EXPORT_SELECTED_LIST_BOX, &CExport::OnSelectedSelectionChange)
	ON_BN_CLICKED(ID_EXPORT_PREVIEW_MORE, &CExport::OnPreviewMorePressed)
	ON_COMMAND(ID_EXPORT_SAVE, &CExport::OnSave)
	ON_COMMAND(ID_EXPORT_SAVE_AS, &CExport::OnSaveAs)
	ON_COMMAND(ID_EXPORT_EXIT, &CExport::OnExit)
END_MESSAGE_MAP()


BOOL CExport::OnInitDialog()
{
	CDialog::OnInitDialog();

	formatToggle.AddString(L"Standard");
	formatToggle.AddString(L"OBS");
	formatToggle.AddString(L"STD w/ MS dates");
	formatToggle.AddString(L"STD w/ YYYYMMDD dates");

	formatToggle.SetCurSel(0);

	choicesListBox.ResetContent();
	selectedListBox.ResetContent();

	CRHMmain* model = CRHMmain::getInstance();
	
	for (size_t i = 0; i < model->SelectedVariables->size(); i++)
	{
		std::string varName = model->cdSeries[i]->Title;
		choicesListBox.AddString(CString(varName.c_str()));
	}

	return true;
}

void CExport::OnChoicesSelectionChange()
{
	int selectedCount = choicesListBox.GetSelCount();
	int * selectedIndicies = new int[selectedCount];
	choicesListBox.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		choicesListBox.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		int found = selectedListBox.FindString(-1, selectedText);
		if (found == LB_ERR)
		{
			selectedListBox.AddString(selectedText);
		}

	}

	delete[] selectedIndicies;
}

void CExport::OnSelectedSelectionChange()
{
	int selectedCount = selectedListBox.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	selectedListBox.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		selectedListBox.DeleteString(selectedIndicies[i]);
	}

	delete[] selectedIndicies;
}

void CExport::OnPreviewMorePressed()
{

	previewEditBox.ResetContent();

	CRHMmain* model = CRHMmain::getInstance();

	std::string Sx;
	std::string Sy;

	std::vector<int> * exportIndex = getExportIndex();

	//Output the header

	int formatIndex = formatToggle.GetCurSel();

	if (formatIndex == 1)
	{
		previewEditBox.AddString(L"Future File Description");
		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			ClassVar* thisVar = model->cdSeries[exportIndex->at(i)]->Tag;
			Sx = model->cdSeries[exportIndex->at(i)]->Title;
			Sx += std::string(" 1 ");
			Sx += thisVar->units;
			previewEditBox.AddString(CString(Sx.c_str()));
		}

		Sx = "###### time";
		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			std::string S = model->cdSeries[exportIndex->at(i)]->Title;
			Sx.append("\t");
			Sx.append(S);
		}

		previewEditBox.AddString(CString(Sx.c_str()));

	}
	else
	{
		Sx = "time";
		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			std::string S = model->cdSeries[exportIndex->at(i)]->Title;
			Sx.append("\t");
			Sx.append(S);
		}
		previewEditBox.AddString(CString(Sx.c_str()));

		Sx = "units";
		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			ClassVar* thisVar = model->cdSeries[exportIndex->at(i)]->Tag;
			std::string S = thisVar->units;
			Sx.append("\t");
			Sx.append(S);
		}
		previewEditBox.AddString(CString(Sx.c_str()));
	}

	//Output the data preview
	for (long index = Global::DTmin + this->nextLine; (index < Global::DTmin + this->nextLine + 1000) && (index < Global::DTmax); index++)
	{
		std::string Sx = FloatToStrF(model->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
		Sx = StandardConverterUtility::GetDateTimeInStringForOutput(model->cdSeries[0]->XValue(index));

		switch (formatIndex)
		{
		case 0: //:ISO date
			Sx = StandardConverterUtility::FormatDateTime("ISO", model->cdSeries[0]->XValue(index));
			break;
		case 1: //MS date
			Sx = FloatToStrF(model->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
			break;
		case 2: //MS date
			Sx = FloatToStrF(model->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
			break;
		case 3: //yyyy-mm-dd hh:mm date
			Sx = StandardConverterUtility::FormatDateTime("yyyy-mm-dd hh:mm ", model->cdSeries[0]->XValue(index));
			break;
		}

		

		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			// has to equal first series length
			if (model->cdSeries[0]->Count() == model->cdSeries[exportIndex->at(i)]->Count())
			{
				ClassVar* thisVar = model->cdSeries[exportIndex->at(i)]->Tag;
				int prec = 7;
				//Manishankar did this, because GCC is showing segmentation fault here. thisVar remains null.

				if (thisVar->varType == TVar::Int || thisVar->varType == TVar::ReadI)
				{
					prec = 7;
				}

				std::string Sy = FloatToStrF(model->cdSeries[exportIndex->at(i)]->YValue(index), TFloatFormat::ffGeneral, prec, 10);
				Sx = Sx + "\t" + Sy;
			}
		}

		previewEditBox.AddString(CString(Sx.c_str()));
	}

	this->nextLine += 1000;
	if (this->nextLine > Global::DTmax)
	{
		this->nextLine = 0;
	}
}

std::vector<int> * CExport::getExportIndex()
{
	std::vector<int> * index = new std::vector<int>();
	CRHMmain* model = CRHMmain::getInstance();
	CString text;
	std::string name;

	int selectedCount = this->selectedListBox.GetCount();

	for (int i = 0; i < selectedCount; i++)
	{
		this->selectedListBox.GetText(i, text);
		CT2CA pszConvertedAnsiString(text); 
		name.assign(pszConvertedAnsiString);

		for (size_t j = 0; j < model->SelectedVariables->size(); j++)
		{
			if (model->cdSeries[j]->Title == name)
			{
				index->push_back(j);
				break;
			}
		}
	}

	return index;

}

void CExport::OnSave()
{
	CRHMmain* model = CRHMmain::getInstance();

	std::string exportFileName = model->OpenNameReport;

	size_t extStart = exportFileName.find_last_of(".");
	std::string extension = exportFileName.substr(extStart, std::string::npos);
	exportFileName = exportFileName.substr(0, extStart);

	if (this->formatToggle.GetCurSel() == 1)
	{
		extension = ".obs";
	}
	else
	{
		extension = ".txt";
	}

	exportFileName.append(extension);

	exportToFile(exportFileName);
}

void CExport::OnSaveAs()
{

	TCHAR * szFilters;
	CString fileType1;
	CString fileType2;


	if (this->formatToggle.GetCurSel() == 1)
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
		CString fileName = fileDlg.GetPathName();
		std::string filePath = CT2A(fileName.GetString());

		exportToFile(filePath);
	}
}

void CExport::OnExit()
{
	this->OnCancel();
}

void CExport::exportToFile(std::string filePath)
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

	std::vector<int>* exportIndex = getExportIndex();

	//Output the header

	int formatIndex = formatToggle.GetCurSel();

	if (formatIndex == 1)
	{
		exportStream << "Future File Description" << endl;
		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			ClassVar* thisVar = model->cdSeries[exportIndex->at(i)]->Tag;
			Sx = model->cdSeries[exportIndex->at(i)]->Title;
			Sx += std::string(" 1 ");
			Sx += thisVar->units;
			exportStream << Sx.c_str() << endl;
		}

		Sx = "###### time";
		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			std::string S = model->cdSeries[exportIndex->at(i)]->Title;
			Sx.append("\t");
			Sx.append(S);
		}

		exportStream << Sx.c_str() << endl;

	}
	else
	{
		Sx = "time";
		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			std::string S = model->cdSeries[exportIndex->at(i)]->Title;
			Sx.append("\t");
			Sx.append(S);
		}
		exportStream << Sx.c_str() << endl;


		Sx = "units";
		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			ClassVar* thisVar = model->cdSeries[exportIndex->at(i)]->Tag;
			std::string S = thisVar->units;
			Sx.append("\t");
			Sx.append(S);
		}
		exportStream << Sx.c_str() << endl;
	}

	//Output the data preview
	for (long index = Global::DTmin; index < Global::DTmax; index++)
	{
		std::string Sx = FloatToStrF(model->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
		Sx = StandardConverterUtility::GetDateTimeInStringForOutput(model->cdSeries[0]->XValue(index));

		switch (formatIndex)
		{
		case 0: //:ISO date
			Sx = StandardConverterUtility::FormatDateTime("ISO", model->cdSeries[0]->XValue(index));
			break;
		case 1: //MS date
			Sx = FloatToStrF(model->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
			break;
		case 2: //MS date
			Sx = FloatToStrF(model->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
			break;
		case 3: //yyyy-mm-dd hh:mm date
			Sx = StandardConverterUtility::FormatDateTime("yyyy-mm-dd hh:mm ", model->cdSeries[0]->XValue(index));
			break;
		}



		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			// has to equal first series length
			if (model->cdSeries[0]->Count() == model->cdSeries[exportIndex->at(i)]->Count())
			{
				ClassVar* thisVar = model->cdSeries[exportIndex->at(i)]->Tag;
				int prec = 7;
				//Manishankar did this, because GCC is showing segmentation fault here. thisVar remains null.

				if (thisVar->varType == TVar::Int || thisVar->varType == TVar::ReadI)
				{
					prec = 7;
				}

				std::string Sy = FloatToStrF(model->cdSeries[exportIndex->at(i)]->YValue(index), TFloatFormat::ffGeneral, prec, 10);
				Sx = Sx + "\t" + Sy;
			}
		}

		exportStream << Sx.c_str() << endl;
	}

	exportStream.close();

}