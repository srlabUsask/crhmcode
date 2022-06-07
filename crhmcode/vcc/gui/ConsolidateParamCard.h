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

	/**
	* Initalizes the help information for the parameter card
	*/
	virtual void InitalizeValues();

private:

	/**
	* The CEdit component that holds the name of the module this version of the parameter is from
	*/
	CEdit module_name;

	/**
	* Connect data layer to the view.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	* Handles the use for all button being clicked. Sends a message up to the CardScrollPane. 
	*/
	afx_msg void ConsolidateParamCard::OnUseForAll();

	/*
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = CONSOLIDATE_PARAM_CARD };

	DECLARE_MESSAGE_MAP()

};

