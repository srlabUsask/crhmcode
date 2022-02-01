#pragma once

class FileDialog
{
public:
	std::string filepath, filename;

	bool Open(std::string exten)
	{
		CString extension(exten.c_str());
		CString extension2("*.");
		extension2 = extension2 + extension;

		CString filter1("Files(*.");
		CString filter2(") | *.");
		CString filter3("|All Files (*.*)|*.*||");
		CString filter;
		filter = filter1 + extension + filter2 + extension + filter3;

		CFileDialog fileDlg(TRUE, extension, extension2, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter);

		if (fileDlg.DoModal() == IDOK)
		{
			CString filepath1 = fileDlg.GetPathName();
			CString filename1 = fileDlg.GetFileName();
			filepath = CT2A(filepath1);
			filename = CT2A(filename1);
			return true;
		}
		return false;
	}

	bool Save(std::string exten)
	{
		CString extension(exten.c_str());
		CString extension2("*.");
		extension2 = extension2 + extension;

		CString filter1("Files(*.");
		CString filter2(") | *.");
		CString filter3("|All Files (*.*)|*.*||");
		CString filter;
		filter = filter1 + extension + filter2 + extension + filter3;

		CFileDialog fileDlg(FALSE, extension, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);

		if (fileDlg.DoModal() == IDOK)
		{
			CString filepath1 = fileDlg.GetPathName();
			CString filename1 = fileDlg.GetFileName();
			filepath = CT2A(filepath1);
			filename = CT2A(filename1);
			return true;
		}
		return false;
	}
};