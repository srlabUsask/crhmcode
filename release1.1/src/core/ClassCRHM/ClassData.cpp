#if defined(_WIN32)
#include "stdafx.h"
#endif

#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <cmath>

#include "ClassData.h"
#include "ClassCRHM.h"
#include "NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"

using namespace std;

ClassData::ClassData(const ClassData& Cl) { //

	DataFileName = Cl.DataFileName;
	Description = Cl.Description;
	Dt1 = Cl.Dt1;
	Dt2 = Cl.Dt2;
	Interval = Cl.Interval;
	Lines = Cl.Lines;
	Freq = Cl.Freq;
	IndxMin = Cl.IndxMin;
	IndxMax = Cl.IndxMax;
	ModN = Cl.ModN;
	HdrLen = Cl.HdrLen;
	Position = Cl.Position;
	DataCnt = Cl.DataCnt;
	FilterCnt = Cl.FilterCnt;

	myMacro = Cl.myMacro;

	Simulation = Cl.Simulation;
	ForceInterval = Cl.ForceInterval;
	GoodInterval = Cl.GoodInterval;
	GoodDay = Cl.GoodDay;
	RunUsed = Cl.RunUsed;
	Success = Cl.Success;
	TimeIndx = Cl.TimeIndx;
	FirstFile = Cl.FirstFile;

	Data = new double* [DataCnt + FilterCnt];   // Data [Cnt] [Lines]

	for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
		Data[jj] = new double[Lines];

	//for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)  //warning resolved by Manishankar
	//	for (int kk = 0; kk < Lines; ++kk)
	//		Data[jj][kk];

	if (Cl.Times) {
		Times = new double[Lines];
		for (long ii = 0; ii < Lines; ++ii)
			Times[ii] = Cl.Times[ii];
	}
	else
		Times = NULL;
}

//---------------------------------------------------------------------------
ClassData& ClassData::operator=(const ClassData& Cl) { //

	if (this == &Cl) return *this;
	DataFileName = Cl.DataFileName;
	Description = Cl.Description;
	Dt1 = Cl.Dt1;
	Dt2 = Cl.Dt2;
	Interval = Cl.Interval;
	Lines = Cl.Lines;
	Freq = Cl.Freq;
	IndxMin = Cl.IndxMin;
	IndxMax = Cl.IndxMax;
	ModN = Cl.ModN;
	HdrLen = Cl.HdrLen;
	Position = Cl.Position;
	DataCnt = Cl.DataCnt;
	FilterCnt = Cl.FilterCnt;

	myMacro = Cl.myMacro;

	Simulation = Cl.Simulation;
	ForceInterval = Cl.ForceInterval;
	GoodInterval = Cl.GoodInterval;
	GoodDay = Cl.GoodDay;
	RunUsed = Cl.RunUsed;
	Success = Cl.Success;
	TimeIndx = Cl.TimeIndx;
	FirstFile = Cl.FirstFile;

	Data = new double* [DataCnt + FilterCnt];   // Data [Cnt] [Lines]

	for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
		Data[jj] = new double[Lines];

	//for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)  //warning resolved by Manishankar
	//	for (int kk = 0; kk < Lines; ++kk)
	//		Data[jj][kk];

	if (Cl.Times) {
		Times = new double[Lines];
		for (long ii = 0; ii < Lines; ++ii)
			Times[ii] = Cl.Times[ii];
	}
	else
		Times = NULL;

	return *this;
}

bool ClassData::DataReadFile(void) {

	ifstream DataFile;
	ifstream::pos_type Here, Here2;
	string Header, Var, Comment;
	istringstream instr;
	bool DecimalTime;
	FirstFile = !Global::DTstart;

	int D[5];
	long jj;
	long MaxLines = 0;
	bool SparseFlag = false;
	bool LineError = false;
	bool OneLine = false;

	ModN = 1;

	bitset <128> MyBitSet;

	DataFile.open(DataFileName, ios_base::in);
	if (!DataFile) {
		/*
		CRHMException Except("Missing observation " + DataFileName, ERR);
		Message(Except.Message.c_str(),
		"Project observation file", mbOK);
		LogError(Except);*/
		DataFile.close();
		return false;
	}

	getline(DataFile, Description);
	HdrLen = 1;
	myMacro = new Classmacro(this);
	while (!DataFile.eof()) {
		char c = DataFile.peek();

		if (DataFile.fail()) {
			/*       CRHMException Except("Errors in observation file header" + DataFileName, ERR);
			Message(Except.Message.c_str(),
			"Project observation file", mbOK);
			LogError(Except);*/
			DataFile.close();
			return false;
		}

		++HdrLen;

		if (c == '#') {
			getline(DataFile, Comment);
			break;
		}

		if (c == '/')
			getline(DataFile, Comment); // lose
		else if (c == '$') {
			getline(DataFile, Comment);
			myMacro->addfilter(Comment);
		}
		else { // observation
			if (FilterCnt != 0) {
				/*          CRHMException Except("Filters must follow observations in file header " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				"Project observation file", mbOK);
				LogError(Except);*/
				DataFile.close();
				return false;
			}
			DataFile >> Var; // observation name
			DataFile >> jj; // number of columns

			getline(DataFile, Comment);
			bool negative = false; // defines integral/instantaneous data
			if (jj < 0) {
				jj = labs(jj);
				negative = true;
			}

			ClassVar* ThisVar = declread("obs", Var, jj, DataCnt, this, Comment);

			if (!ThisVar) { // NULL if already defined
				string S = string("Observation '") + Var + "' defined in earlier observation file";
				/*          CRHMException Except("Observation variable already defined " + DataFileName, ERR);
				Message(S.c_str(), Except.Message.c_str(), mbOK);*/
				DataFile.close();
				return false;
			}

			ThisVar->review_HRU_OBS();

			for (int ii = 0; ii < jj; ++ii)
				if (negative)
					MyBitSet.set(DataCnt + jj - 1);

			DataCnt = DataCnt + jj;
		}
	} // while

	if (!Simulation) {

		do {
			Here = DataFile.tellg();
			DataFile >> Dt1;
			if (Dt1 > 3000.0)
				DecimalTime = true;
			else {
				DecimalTime = false;
				D[0] = (int)Dt1;
				//DataFile.seekg(Here - 1);  // go back to beginning of data
				for (int ii = 1; ii < 5; ii++)
					DataFile >> D[ii];
				Position = HdrLen;
				Dt1 = Encode24(D);
			}

			Dt1 += TimeShiftFilter;

			if (DataFile.eof()) {
				/*          CRHMException Except("Error in observation file header " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				"File observations end early!", mbOK);
				LogError(Except);*/
				DataFile.close();
				return false;
			}

			if (Global::DTstart != 0.0 && Dt1 >= Global::DTend) {
				/*         CRHMException Except("Error in observation file " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				"File observations begin after period!", mbOK);
				LogError(Except);*/
				DataFile.close();
				return false;
			}

			getline(DataFile, Var);  // eat up remainder of line

			instr.clear(); // check for sufficient data
			instr.str(Var);
			double V;
			long Cols = 0;
			for (;;) {
				instr >> V;
				if (instr.fail()) break;
				++Cols;
			}

			if (Cols < DataCnt) {
				/*          CRHMException Except("Observation file header Error " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				string("Header of file defines more observations than data columns (" + string(Cols) + ")").c_str(), mbOK);
				LogError(Except);*/
				DataFile.close();
				return false;
			}
			else if (Cols > DataCnt) {
				/*          CRHMException Except("Observation file header Warning - Column count > Data count " + DataFileName, WARNING);
				Message(Except.Message.c_str(),
				string("Header of file defines fewer observations than data columns (" + string(Cols) + ")").c_str(), mbOK);
				LogError(Except);*/
			}

			char c = DataFile.peek();

			if (DataFile.eof()) { // one line file
				DataFile.clear();
				/*          CRHMException Except("Observation file warning " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				"ONE line observation file!", mbOK);
				LogError(Except);*/
				OneLine = true;
				Dt2 = Dt1 + 1.0;
				Freq = 1;
				SparseFlag = true;
				Interval = 0.0;
				break;
			}
		} while (Global::DTstart != 0.0 && Global::DTstart > Dt1);

		if (Global::DTstart == 0.0) Global::DTstart = floor(Dt1);

		if (!OneLine) {
			if (DecimalTime)
				DataFile >> Dt2;
			else {
				for (int ii = 0; ii < 5; ii++)
					DataFile >> D[ii];
				Position = HdrLen + 1;
				Dt2 = Encode24(D);
			}

			Dt2 += TimeShiftFilter;

			Interval = Dt2 - Dt1;
			if (Interval > 1.0) {
				Interval = 1.0;
				SparseFlag = true;
			}

			Freq = (long)(1.0 / Interval + 0.8 * Interval);
			Freq = Veto_Freq(Freq);

			Interval = (double)1.0 / Freq;
			if (FirstFile)
				IndxMin = 0;
			else {
				IndxMin = (long)floor((Dt1 - Global::DTstart) * Freq + Interval / 2.0);
				if (Interval != 1) // Oct 30
					--IndxMin;
			}
			double mid = floor(Dt1) + Interval;
			double range = 0.00002;
			if (Dt1 > mid + range || (Dt1 < mid - range && Interval < 1.0)) { // ensure data starts at first interval  //warning resolved by Manishankar
																			/*          CRHMException Except("Observation file WARNING " + DataFileName, ERR);
																			Message(Except.Message.c_str(),
																			"First interval must start at midnight + interval! ", mbOK);
																			LogError(Except);*/

				if (IndxMin == 0)
					IndxMin = (long)((Dt1 - floor(Dt1)) / Interval - 1);
			}

			DataFile.seekg(0, ios_base::end);
			ifstream::pos_type Back = DataFile.tellg();// -3;
			char c;

			bool white = true;
			long Fix = -3;
			do {
				DataFile.seekg(Fix, ios::end);  // find last line in file
				--Fix;
				c = DataFile.get();
				if (white)
					white = isspace(c);
			} while (c != '\n' || white);

			if (DecimalTime)
				DataFile >> Dt2;
			else {
				for (int ii = 0; ii < 5; ii++)  // read last date and time
					DataFile >> D[ii];
				Position = 99998;
				Dt2 = Encode24(D);
			}
		} // not one line

		Dt2 += TimeShiftFilter;

		if (Global::DTend == 0.0) Global::DTend = Dt2;  // first data file

		if (Global::DTend != 0.0 && Global::DTend < Dt2) Dt2 = Global::DTend;

		Lines = (long)ceil((Dt2 - Dt1 + 1.0 / (static_cast<long long>(Freq) * 2)) * static_cast<long long>(Freq));

		if (SparseFlag && Lines < Global::Freq) // handle short interval with lots of sparse points
			Lines = Global::Freq;

		IndxMax = IndxMin + Lines - 1;

		DataFile.seekg(0, ios_base::beg);  // go back to beginning of data

		getline(DataFile, Comment);
		while (Comment[0] != '#') // space by header
			getline(DataFile, Comment);

	} // !Simulation

	try
	{
		//Data = new double*[DataCnt + FilterCnt];   // Data [Cnt] [Lines]
		//for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
		//	Data[jj] = new double[Lines];
		//Times = new double[Lines];

		Data = new double* [DataCnt + FilterCnt];   // Data [Cnt] [Lines]
		MaxLines = Lines;
		if (fmodl(Lines, Freq) > 0) // if missing data in last day - pad to midnight
			MaxLines = (Lines / Freq + 1) * Freq;
		for (int jj = 0; jj < DataCnt + FilterCnt; jj++)
		{
			Data[jj] = new double[MaxLines];
		}
		Times = new double[MaxLines];
	}

	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate for observations file: " +
			DataFileName, TExcept::TERMINATE);
		LogError(Except);
		throw(Except);
	}





	//Mani look at this
	//trying to initialize data[][].
	for (int i = 0; i < Lines; i++)
	{
		for (int j = 0; j < DataCnt + FilterCnt; j++)
		{
			//Data[j][i] = 35.93;//-999999; //Changed by Manishankar to make it look like the original graph.
			Data[j][i] = -999999;
		}
	}



	myMacro->fixup(); // required by myMacro->execute(Position)

					  /*    TCursor OriginalCursor = Screen->Cursor;
					  Screen->Cursor = crHourGlass;*/
	Dt1 = floor(Dt1);

	//    try{
	//char c;
	double DeltaH = Interval * 1.5;


	for (Position = 0; Position < Lines; ++Position)
	{
		/*        if(Position%100 == 0) {
		if(!Simulation)
		Update_Main_Status("Observation Line " + string(Position+1));
		else
		Update_Main_Status("Simulation Line " + string(Position+1));

		Application->ProcessMessages();
		}*/



		if (!Simulation)
		{
			if (DecimalTime)
				DataFile >> Times[Position];
			else
			{
				for (int ii = 0; ii < 5; ++ii)
					DataFile >> D[ii];
				Times[Position] = Encode24(D);
			}

			if (DataFile.eof()) // handles sparse files
			{
				Lines = Position;
				break;
			}

			if (!DecimalTime) Times[Position] = Encode24(D);

			Times[Position] += TimeShiftFilter;

			Global::DTnow = Times[Position];

			if (Position != 0 && Times[Position] <= Times[Position - 1]) {
				string S;
				//S.sprintf("Earlier Date at line: %u+, %5u %3u %3u %3u %3u in observation file ", Position, D[0], D[1], D[2], D[3], D[4]);

				//CRHMException Except(S + DataFileName, ERR);
				//Message(S.c_str(), "Error in Observation File", mbOK);
				//LogError(Except);
				LineError = true;
				break;
			}

			for (int ii = 0; ii < DataCnt; ++ii) {
				char c;
				while (c = DataFile.peek(), c == ' ' || c == '\t') DataFile.get();

				if (DataFile.peek() == '\n') { // handles short line

											   //String S = String("Check line ") + String(HdrLen + Position + 1) + String(" for missing columns in ");
											   //CRHMException Except(S.c_str() + DataFileName, ERR);
					if (!SparseFlag) {
						//Application->MessageBox(Except.Message.c_str(),
						//"Project observation file - too few columns", MB_OK);
					}

					if (FirstFile) { // definitely error
									 //LogError(Except);
						LineError = true; // will break out of loop
					}
					else if (ii == 0) { // assume sparse in first column
						SparseFlag = true;
						--Position;
						continue;
					}
					else // any column but the first - assume missing
						Data[ii][Position] = 35.93;//Data[ii][Position] = -999999;

				}
				else
					DataFile >> Data[ii][Position];

				if (DataFile.fail()) { // handles faulty data
									   //String S = String("Faulty data at line ") + String(HdrLen + Position + 1)
									   //+ String(" in observation file ");
									   //CRHMException Except(S.c_str() + DataFileName, ERR);
									   //Application->MessageBox(Except.Message.c_str(),
									   //"Project observation file", MB_OK);
									   //LogError(Except);
					Lines = Position - 1;
					LineError = true;
					break;
				} // DataFile.fail
			} // for data loop


			if (LineError) break;

			if (DataFile.peek() != '\n') // gobbles up rest of line
				DataFile.ignore(256, '\n');

			//manishankar. The condition "Times[Position] >= Times[Position - 1] + DeltaH" was being true and thus the SparseFlag was being set.
			//However, I checked the data and saw that the date entries are not really sparse although this condition was being true.
			//I have thus commented this out.
			/*
			if (Position != 0 && Times[Position] >= Times[Position - 1] + DeltaH)
			{
				if (!SparseFlag)
				{
					SparseFlag = true;
					if (FirstFile)
					{
						//string S;
						//if(DecimalTime)
						//S.sprintf("Discontinuous Date: \"%5f\" at line: %u", Times[Position], Position + HdrLen + 1);
						//else
						//S.sprintf("Discontinuous Date: \"%5u %3u %3u %3u %3u\" at line: %u", D[0], D[1], D[2], D[3], D[4], HdrLen + Position + 1);

						//Message(S.c_str(), string("Warning Sparse Observation File: " + DataFileName).c_str(), mbOK);
					}
					}

				} // if !Simulation
			}*/

			myMacro->execute(Position);
		} //end if

	} //end for

	  /*    __finally
	  {
	  Screen->Cursor = OriginalCursor;
	  }*/


	if (!Simulation && Dt2 > Times[Position - 1] + Interval / 2.0 && !SparseFlag) {
		/*     string S = string("Interval frequency increases ") + string(" in observation file ");
		CRHMException Except(S + DataFileName, ERR);
		Message(Except.Message.c_str(), "Project observation file", mbOK);
		LogError(Except);*/
		SparseFlag = true;
	}

	if (Freq > 1 && fmodl(Lines, Freq) > 0 && !SparseFlag) {

		CRHMException Except("Last day is incomplete and is padded with 0.0 " + DataFileName, TExcept::WARNING);
		LogError(Except);

		IndxMax = IndxMin + MaxLines - 1;

		for (long ll = Position; ll <= MaxLines - 1; ++ll) {
			Times[ll] = Times[ll - 1] + 1.0 / Freq;
			Dt2 = Times[ll];

			for (long dd = 0; dd < DataCnt; ++dd)
				Data[dd][ll] = 0.0;
		}
	}


	if (LineError) { // clean up and flag error
		for (int ii = 0; ii < DataCnt + FilterCnt; ii++)
			if (Data[ii]) { // may already have been deleted if not used by the filter
				delete[] Data[ii];
				Data[ii] = NULL;
			}
		delete[] Data;
		Data = NULL;
		delete[] Times;
		Times = NULL;
	}
	else {
		if (Lines < Freq)  // Handle less than one day
			SparseFlag = true;

		if (!SparseFlag)
		{
			delete[] Times;
			Times = NULL;

			if ((ForceInterval == 96 && Freq == 144) || (ForceInterval == 144 && Freq == 96)) { // cannot convert 10 minute to 15 minute or vice versa  //warning resolved by Manishankar.
																							/*          string S = string("cannot convert 10 minute interval to 15 minute or vice versa") + string(" in observation file ");
																							CRHMException Except(S + DataFileName, ERR);
																							Message(Except.Message.c_str(), "Project observation file", mbOK);
																							LogError(Except);*/
				ForceInterval = 0;
			}

			if (ForceInterval != Freq && ForceInterval) {
				double Result = 0.0;

				for (int jj = 0; jj < DataCnt + FilterCnt; ++jj) { // convert all observations

					if (!Data[jj]) {
						continue;
					}

					double Divisor = 1.0;
					long NCnt;
					double Delta;

					if (ForceInterval > Freq) { // expand data
						NCnt = ForceInterval / Freq;
						double* NewData = new double[Lines * NCnt];
						if (!MyBitSet[jj]) {
							for (long ii = 0; ii < Lines * NCnt; ++ii) {
								long kk = ii % NCnt;
								if (kk == 0) {
									if (ii == 0) {
										Result = Data[jj][ii / NCnt] * Divisor;
										Delta = 0.0;
									}
									else if (ii + NCnt >= Lines * NCnt) {
										Result = Data[jj][ii / NCnt] * Divisor;
										Delta = 0.0;
									}
									else {
										Result = Data[jj][ii / NCnt - 1] * Divisor;
										Delta = (Data[jj][ii / NCnt] - Data[jj][ii / NCnt - 1]) * Divisor;
									}
								}
								NewData[ii] = Result + Delta * (static_cast<long long>(ii % NCnt) + 1) / NCnt;
							}
						}
						else {
							Divisor = (double)1.0 / NCnt;
							for (long ii = 0; ii < Lines * NCnt; ++ii) {
								long kk = ii % NCnt;
								if (kk == 0)
									Result = Data[jj][ii / NCnt] * Divisor;
								NewData[ii] = Result;
							}
						}

						delete[] Data[jj];
						Data[jj] = NewData;

						if (jj + 1 == DataCnt + FilterCnt) {
							Lines = Lines * NCnt;
							Freq = Freq * NCnt;
							Interval = Interval / NCnt;
							IndxMin *= (long)TimeShiftFilter; //Assumes that timezones are ints and time is in hours -jhs507
							IndxMax = IndxMin + Lines - 1;
						}
					} // expand data
					else { // shrink data
						long NCnt = Freq / ForceInterval;
						double* NewData = new double[Lines / NCnt];
						if (!MyBitSet[jj])
							Divisor = (double)NCnt;
						Result = 0.0;
						for (long ii = 0; ii < Lines; ++ii) {
							Result += Data[jj][ii];
							long kk = ii % NCnt;
							if (kk == NCnt - 1) {
								NewData[ii / NCnt] = Result / Divisor;
								Result = 0.0;
							}
						}
						delete[] Data[jj];
						Data[jj] = NewData;
					} // shrink data
				} // convert all observations

				if (ForceInterval < Freq) { // shrink data
					long NCnt = Freq / ForceInterval;
					Lines = Lines / NCnt;
					Freq = Freq / NCnt;
					Interval = Interval * NCnt;
					IndxMax = IndxMin + Lines - 1;
				}
				myMacro->fixup(); // required by myMacro->execute(Position)
			}
		}
		else
		{ //allocate space required


			if (SparseFlag && Simulation)
			{
				//If SparseFlag and Simulation are both true then something unintended has happened.
				//Simulation data is not intended to have gaps.
				CRHMException Except("File " + DataFileName + " contains simulation data with gaps. Discontinuous times in simulation data files is not currently supported.", TExcept::TERMINATE);
				LogError(Except);
				throw(Except);
			}
			else {
				double* Temp = new double[Lines];

				for (long ii = 0; ii < Lines; ++ii)
				{
					Temp[ii] = Times[ii];
				}
				delete[] Times;
				Times = Temp;
			}


		}
	}

	delete myMacro;
	myMacro = NULL;
	DataFile.close();
	return true;
}


//---------------------------------------------------------------------------
long ClassData::Veto_Freq(long Freq) {
	const long OK_Values[14] = { 1, 2, 3, 4, 6, 8, 12, 24, 48, 72, 96, 144, 192, 288 };
	if (Freq <= 1)
		return 1;
	if (Freq >= OK_Values[13])
		return OK_Values[13];
	for (int ii = 1; ii < 14; ++ii) {
		if (Freq <= OK_Values[ii]) {
			if ((Freq - OK_Values[ii - 1]) < (OK_Values[ii] - Freq))
				return OK_Values[ii - 1];
			else
				return OK_Values[ii];
		}
	}
	return(-1);
}

ClassData::~ClassData() {

	if (Times != NULL) {
		delete[] Times;
		Times = NULL;
	}

	if (Data != NULL) {
		for (int ii = 0; ii < DataCnt + FilterCnt; ii++)
			if (Data[ii]) { // may already have been deleted if not used by the filter
				delete[] Data[ii];
				Data[ii] = NULL;
			}
		delete[] Data;
		Data = NULL;
	}
	if (HdrLen == 0)
		return; // not actual observation but Obs function

	if (myMacro) {
		delete myMacro;
		myMacro = NULL;
	}

	// Remove completely any observations never used by any module

	MapVar::iterator itVar;
	ClassVar* thisVar;


	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end();) {
		thisVar = (*itVar).second;
		if (thisVar->varType == TVar::Read && thisVar->FileData == this) {
			delete thisVar;
			Global::MapVars.erase(itVar++);
		}
		else
			++itVar;
	}

	// Demote observations used by currently loaded modules

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		if (thisVar->FileData == this && (thisVar->varType == TVar::ReadF || thisVar->varType == TVar::ReadI || thisVar->varType == TVar::Float)) {
			thisVar->FileData = NULL;

			if (thisVar->varType == TVar::Float) { // handles TDay, RHDay and EADay
				thisVar->FunctVar = NULL;
				thisVar->CustomFunct = NULL;
				thisVar->CustomFunctName = "";
				continue;
			}

			thisVar->ReleaseM();
			thisVar->dim = 1;
			thisVar->dimMax = 1;
			if (thisVar->DLLName.empty())
				thisVar->cnt = 0;
			thisVar->offset = 0;

			if (thisVar->varType == TVar::ReadI) thisVar->varType = TVar::Int;
			if (thisVar->varType == TVar::ReadF) thisVar->varType = TVar::Float;
		}
	}
}

double ClassData::Encode24(int D[]) {

	try {
		if (D[3] == 24) // handle 24:00
			return  StandardConverterUtility::EncodeDateTime(D[0], D[1], D[2], 0, D[4]) + 1;
		else
			return  StandardConverterUtility::EncodeDateTime(D[0], D[1], D[2], D[3], D[4]);
	}
	catch (...)
	{
		//    string S;
		//    S.sprintf("Invalid Date: \"%5u %3u %3u %3u %3u\" at line: %u", D[0], D[1], D[2], D[3], D[4], Position+1);

		//    Message(S.c_str(), string("Observation File: " + DataFileName).c_str(), mbOK);
		//    throw;
		return 0.0;
	}
}
