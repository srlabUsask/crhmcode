#pragma once

#include "TStringList.h"

class utils
{
public:
	utils();
	~utils();

	long SeriesCnt;
	long CurChartPage;
	bool dirty; // changes made to project
	bool cancel; // handles cancel from open new project with current dirty project

	TStringList *ObsFilesList;

	TStringList *ProjectList;
	TStringList SaveProject();

};