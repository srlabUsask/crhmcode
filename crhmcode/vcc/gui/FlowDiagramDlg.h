#include "afxdialogex.h"
#include "../../src/core/GlobalDll.h"
#include "CRHM_GUI.h"
#include "../../src/core/MacroUnit.h"


#pragma once

class TStringGrid;
class TGridOptions;
class StringGrid2;
class Box;
class FDModule //flow diagram module
{
public:
	std::string modulename;
	std::vector<std::string> observations;
	std::vector<std::string> modules;
	std::vector<std::string> inputs;
	std::vector<std::string> outputs;
	std::vector<std::string> parameters;
	std::vector<std::string> newobservations;
	std::vector<std::string> inputlist; 
	std::vector<std::string> outputlist;
	int count{0};
	int x1{0};
	int y1{0};
	int x2{0};
	int y2{0};
	int ilength{0};
	int olength{0};

	void FindInputList()
	{
		for (size_t i = 0; i < this->inputs.size(); i++)
		{
			if (inputs[i] != "" && InputPresent(inputs[i]) == 0)
			{ 
				inputlist.push_back(inputs[i]); 
				ilength++; 
			}
		}
		for (size_t i = 0; i < this->parameters.size(); i++)
		{
			if (parameters[i] != "" && InputPresent(parameters[i]) == 0) 
			{ 
				inputlist.push_back(parameters[i]); 
				ilength++; 
			}
		}
	}

	void FindOutputList()
	{
		int ii = 0;
		for (size_t i = 0; i < this->outputs.size(); i++)
		{
			if (outputs[i] != "" && OutputPresent (outputs[i]) == 0)
			{ 
				outputlist.push_back(outputs[i]); 
				olength++; 
			}
		}
	}

	int GetInputSerial(string input)
	{
		for (int i = 0; i < ilength; i++)
		{
			if (inputlist[i] == input) 
			{ 
				return i; 
			}
		}
		return -1;
	}
	int GetOutputSerial(string input)
	{
		for (int i = 0; i < olength; i++)
		{
			if (outputlist[i] == input) 
			{ 
				return i; 
			}
		}
		return -1;
	}

	int InputPresent(string input)
	{
		for (int i = 0; i < ilength; i++)
		{
			if (inputlist[i] == input) 
			{ 
				return 1; 
			}
		}
		return 0;
	}

	int OutputPresent(string output)
	{
		for (int i = 0; i < olength; i++)
		{
			if (outputlist[i] == output) 
			{ 
				return 1; 
			}
		}
		return 0;
	}

};

// FlowDiagramDlg dialog

class FlowDiagramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FlowDiagramDlg)

public:
	FlowDiagramDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~FlowDiagramDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FlowDiagram_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	bool OurCntrl{false};
	std::vector<std::pair<std::string, ClassModule*>> * LocalModulesList{ NULL };
	TStringGrid *StringGrid1{ NULL };



	void FormActivate();
	void DrawGrid();
	int MatchDecl_Obs(string module, string Obs);
	//FDModule * fdmodules;
	//int fdmoduleCount;
	
	/*
	void FormDestroy();
	void Exit1Click();
	void FormResize();
	void FormPaint();
	void FormCreate();
	void Print1Click();
	void PrinterSetUp1Click();
	void Selection1Click();
	void BitFile1Click();
	void MetaFile1Click();
	void FormKeyDown(WORD &Key, TShiftState Shift);
	void FormKeyUp(WORD &Key, TShiftState Shift);

private:	// User declarations
	void DeleteCol(TStringGrid *Grid, int Column);
	void DeleteBlankRows(TStringGrid *Grid);
	void DeleteRow(TStringGrid *Grid, int Row);

	TMetafile *pMetafile;
	TMetafileCanvas *pFlow;
	TMetafileCanvas *zFlow;
	String Title;

public:		// User declarations
	FlowDiagramDlg(TComponent* Owner);	
	void __fastcall DrawGridO(TObject *Sender);

	friend class Diagram;
	Diagram *OurDiagram;

	//  TStringList *VarList;
	bool DisplyPar;
	int __fastcall GetNumVar(int Mod, int &First, int &Last);
	void SetTitle(String Text);
		
	bool Variation_Decide(int indx, long variation_set);
	*/
	CListCtrl listcontrol;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	void GetModuleDetails(string S, ClassModule* thisModule, FDModule * m);
	bool Variation_Decide(int Variation_set, long Variation);
	bool Visible_Decide(long Variation);
	bool Not_Obs(string Mod, string Var);
	afx_msg void OnPaint();
	int FindPreviousModule(string input, int mcount, FDModule mods[]);
	void DrawDiagram();
	string GetLineString(int x1, int y1, int x2, int y2);
	string GetRectangleString(int x1, int y1, int x2, int y2);
	string GetDrawString(string str, int x1, int y1);
	void DrawModules();
	void GetModulesInputsAndOutputs(FDModule * mods);
	void LoadAllModules();
};



// Create a derived TPanel which has a Canvas property
class TBackPanel //: public CPanel
{
public:
	//TBackPanel(TComponent *Owner) : TPanel(Owner) { }
	//__property Canvas;
};


class Box {
public:
	int Xul;
	int Yul;
	int Xlr;
	int Ylr;
	int InCnt;   // number of variable inputs
	int OutCnt;  // number of used outputs
	int ObsCnt;  // number of input parameters or observations
	int ObsCntX; // number of input parameters or observations used more than once
	int Height{0};
	int CSpacing{0}; // used to sync components
	int *OutXs;   // updated by GetXY
	int *OutYs;   // updated by GetXY
	int PadjX;    // make space for parameters or observations
	int PadjY;    // future space for Put inputs
	int MaxOutNameLen; // longest output variable name length locked to CSpacing

	Box() : Xul(0), Yul(0), Xlr(0), Ylr(0), InCnt(0), OutCnt(0), ObsCnt(0), ObsCntX(0),
		OutXs(NULL), OutYs(NULL), PadjX(0), PadjY(0), MaxOutNameLen(0) {};
	//~Box();
	//void GetXY(int Out_Var, int InX, int &ToX, int &ToY);
};

class Diagram {

	FlowDiagramDlg *FlowForm;

	Box *Boxes;

	int Width;
	int Height;
	int HSpacing;
	int VSpacing;
	int CSpacing;

public:
	int Xmax;
	int Ymax;

public:
	//Diagram(FlowDiagramDlg *FlowForm);
	//~Diagram();
	//void DrawModules();

};

union ModandVar {

	int both;
	short int Module[2];
	int GetMod(void) { return Module[0]; };
	void PutMod(int M) { Module[0] = M; };
	int GetVar(void) { return Module[1]; };
	void PutVar(int V) { Module[1] = V; };

	int GetX(void) { return Module[0]; };
	void PutX(int M) { Module[0] = M; };
	int GetY(void) { return Module[1]; };
	void PutY(int V) { Module[1] = V; };
};



class TStringGrid
{
public:
	string Cells[500][500];
	int ColCount = 0;
	int RowCount = 0;
	int FixedRows = 0;
	int FixedCols = 0;
	string Cols[500];
	string Rows[500];
	bool Visible = false;

	//TGridOptions Options;

	int ColPos(int row, string data)
	{
		int index = -1;
		for (int i = 0; i < ColCount; i++)
		{
			if (Cells[i][row] == data) { return i; }
		}
		return index;
	}

	int RowPos(int col, string data)
	{
		int index = -1;
		for (int i = 0; i < RowCount; i++)
		{
			if (Cells[col][i] == data) { return i; }
		}
		return index;
	}

	void DeleteRow(int row)
	{

	}
};

class TGridOptions
{
public:
	int option;
};

class StringGrid2
{
public:
	string Cells[500][500];
	int ColCount = 0;
	int RowCount = 0;
	int FixedRows = 0;
	string Cols[500];
};

