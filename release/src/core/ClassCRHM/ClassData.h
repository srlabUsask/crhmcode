#pragma once

#ifndef CLASSDATA
#define CLASSDATA

using namespace std;

class MacroClass;

class ClassData 
{
public:
	string DataFileName;
	string Description;
	double** Data;
	double* Times; // holds sparse times
	double Dt1{ 0.0 };
	double Dt2{ 0.0 };
	double Interval{ 0.0 }; // days
	long Lines{ 0 };
	long Freq{ 0 };
	long IndxMin{ 0 };   // range of data available
	long IndxMax{ 0 };   // range of data available
	long ModN;      // divisor for data less frequent than basic interval
	long HdrLen{ 0 };    // length of file header
	long Position{ 0 };  // current line in file
	long DataCnt;
	long FilterCnt;  // filter count

	MacroClass* myMacro;
	bool Simulation;
	long ForceInterval;
	bool GoodInterval{ false };
	bool GoodDay{ false };
	bool RunUsed{ false };
	bool Success{ false };
	long TimeIndx{ 0 }; // sparse file ??
	bool FirstFile;

	double TimeShiftFilter; // used by Time shift filter

	/**
	* Default constructor that defines default values.
	*/
	ClassData() :
		DataFileName(""),
		Data(NULL),
		myMacro(NULL),
		DataCnt(0),
		FilterCnt(0),
		Simulation(false),
		FirstFile(false),
		ForceInterval(0),
		ModN(0),
		Times(NULL),
		TimeShiftFilter(0.0)
	{};

	/**
	* Constructor with default values. Sets ClassData::Success to true if DataReadFile() returns true.
	*/
	ClassData(string DataFileName) : 
		DataFileName(DataFileName), 
		Data(NULL), 
		myMacro(NULL),
		DataCnt(0), 
		FilterCnt(0), 
		Simulation(false), 
		FirstFile(false),
		ForceInterval(0), 
		ModN(0), 
		Times(NULL), 
		TimeShiftFilter(0.0) 
	{
		Success = DataReadFile();
	}


	/**
	* Clone constructor creates a new ClassData object with all the same internal values as the provided refference.
	* 
	* @param cl		reference to the ClassData object to be cloned.
	*/
	ClassData(const ClassData& Cl);

	/**
	* Overide of the '=' operator allowing for assignment from one ClassData object to another.
	*/
	ClassData& operator=(const ClassData& Cl);


	bool DataReadFile(void); //{ return true; };

	long Veto_Freq(long Freq);


	virtual ~ClassData(); //{ ; };

	double Encode24(int D[]);
};


#endif // !CLASSDATA


