/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
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