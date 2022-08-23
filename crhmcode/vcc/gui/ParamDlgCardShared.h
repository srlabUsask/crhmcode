#pragma once

#include "ParamDlgCard.h"

/**
* Displays the information for a shared parameter and allows it to be made local
*/
class ParamDlgCardShared : public ParamDlgCard
{
private:

	/*
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = PARAMETERS_CARD_SHARED };

	/**
	* Handles the pressing of the "Manage Parameter Localy" button
	* 
	* Passes a message up to the ParamDlgScrollablePane
	*/
	afx_msg void OnMakeLocal();

public:

	/**
	* Standard constructor
	*/
	ParamDlgCardShared(ClassPar* param, FontsContainer* fonts, CWnd* pParent);

	/**
	* Creates the dialog object and attaches it to this object.
	* 
	* Must be called directly after the constructor.
	* 
	* @return bool - true if successful false otherwise
	*/
	virtual bool call_create(CWnd* pParent) override;
	
	/**
	* Renders the value grid for the parameter
	* 
	* @return bool - true if successful false otherwise
	*/
	virtual bool RenderGrid() override;

	DECLARE_MESSAGE_MAP()
};

