#pragma once

#include "ParamDlgCardShared.h"

class ConsolidateParamCard : public ParamDlgCardShared
{
public:
	
	/**
	* Standard constructor
	*/
	ConsolidateParamCard(ClassPar* param, CWnd* pParent);

	/**
	* Creates the dialog object and attaches it to this object.
	*
	* Must be called directly after the constructor.
	*
	* @return bool - true if successful false otherwise
	*/
	virtual bool call_create(CWnd* pParent) override;

private:

	/*
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = CONSOLIDATE_PARAM_CARD };

	DECLARE_MESSAGE_MAP()

};

