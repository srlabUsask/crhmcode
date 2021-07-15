#if defined(_WIN32) && !defined(__MINGW32__)
#include "stdafx.h"
#endif

#include "CRHMmain.h"

#if defined(VS_GUI)
#include "CRHMAboutBox.h"
#endif

#include <list>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
//#include "boost/shared_ptr.hpp"
#include "GlobalDll.h"
//#include "ClassCRHM/ClassCRHM.h"
#include "ClassModule/ClassModule.h"
#include "NewModules.h"
#include "../MacroUnit/MacroUnit.h"
#include "Common/Common.h"
#include "StandardConverterUtility.h"

#include <time.h>

#include "CRHMLogger.h"


//string ApplicationDir = ExtractFilePath(AnsiReplaceStr(Application->ExeName, "/", "\\"));



Administer AdminMacro("03/24/06", "Macro");

using namespace std;
using namespace CRHM;

//extern double xLimit;
//extern long lLimit;

bool ReportAll = true;



extern string AKAstrings[];

typedef pair<string, string>  PairDllModule;
typedef multimap<string, string>  TDllModule;

typedef std::shared_ptr<Classinfo> Pinfo; //std now contains the shared_ptr. Thus, getting rid of boost.
typedef pair<string, Pinfo>  Pairinfo;
typedef multimap<string, Pinfo>  paras;

typedef pair<string, ClassPar*>  PairPar;
typedef multimap<string, ClassPar*>  GrpParas;


ClassVar *VarFind(string name);
ClassPar *ParFind(string name);

//CRHM::TFun  FindObservationType(string Kind);

string Version = "Version: 4.7_16";

CRHMmain* CRHMmain::instance = 0;

CRHMmain* CRHMmain::getInstance()
{
	if (instance == 0)
	{
		instance = new CRHMmain(NULL);
	}

	return instance;
}


CRHMmain::CRHMmain(struct crhm_arguments * arguments)
{
	if (arguments == NULL)
	{
		//Use default values
		Global::TimeFormat = TIMEFORMAT::ISO;
		this->OutputFormat = OUTPUT_FORMAT::STD;
		this->OutputName = "";
		this->Delimiter = '\t';
		this->ObsFileDirectory = "";
		this->ShowProgress = false;
		this->UpdateProgress = 7;
	}
	else
	{
		//Recive the arguments from the passed struct.
		Global::TimeFormat = arguments->time_format;
		this->OutputFormat = arguments->output_format;
		this->OutputName = arguments->output_name;
		this->Delimiter = arguments->delimiter;
		this->ObsFileDirectory = arguments->obs_file_directory;
		this->ShowProgress = arguments->show_progress;
		this->UpdateProgress = arguments->update_progress;

	}

	FormCreate();
}


CRHMmain::~CRHMmain()
{
}

double CRHMmain::GetStartDate()
{
	return StartDatePicker;
}

void CRHMmain::setStartDate(double sdate)
{
	StartDatePicker = sdate;
}


double CRHMmain::GetEndDate()
{
	return EndDatePicker;
}

void CRHMmain::setEndDate(double edate)
{
	EndDatePicker = edate;
}


std::list<std::pair<std::string, ClassVar*>> * CRHMmain::getSelectedVariables()
{
	return SelectedVariables;
}

void CRHMmain::setSelectedVariables(std::list<std::pair<std::string, ClassVar*>>* t)
{
	SelectedVariables = t;
}

std::list<std::pair<std::string, TSeries *>> * CRHMmain::getSelectedObservations()
{
	return SelectedObservations;
}

void CRHMmain::setSelectedObservatoions(std::list<std::pair<std::string, TSeries*>>* t)
{
	SelectedObservations = t;
}


//manishankar added this function from CRHMmainDlg.cpp file.
/*
* Returns a reference to the ClassVar object with variable name related to the passed in string. 
*	The hru specifier of the variable will be stripped away before looking for the variable object
*	ie. Albedo(1) and Albedo(2) will return the same object.
* 
* @param vname - std::string with the name of the variable for which a reference to will be returned.
* @return Reference to the ClassVar object specified by the string parameter
*/
ClassVar * CRHMmain::GetObjectOfVariable(string vname)
{

	int pos = vname.find_first_of('(');

	std::string name = vname.substr(0,pos);

	std::map<std::string, ClassVar*>::iterator it = this->AllVariables->find(name);
	
	if (it != this->AllVariables->end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
	
}

//manishankar added this function from CRHMmainDlg.cpp file.
ClassVar * CRHMmain::GetObjectOfObservation(string vname)
{

	int pos = vname.find_first_of('(');

	std::string name = vname.substr(0, pos);

	std::map<std::string, ClassVar*>::iterator it = this->AllObservations->find(name);

	if (it != this->AllObservations->end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}

}




void CRHMmain::BldModelClick()
{
	//int Index = (int)Global::AllModelsList->Objects[thisMenu->MenuIndex - 6]; // Global::AllModelsList is sorted

	//Global::OurModulesList->CommaText = Global::ModelModulesList->Strings[Index]; // Global::ModelModulesList is not sorted
	//string DescripPrj = Global::AllModelsList->Strings[thisMenu->MenuIndex - 6].c_str();

	//Chart->SubTitle->Text->Clear(); // put in plot for information
	//Chart->SubTitle->Text->Add(DescripPrj.c_str());

	/*for (int ii = 0; ii < Global::OurModulesList->Count; ii++) {
	long Variation = 0;
	int P;
	if (P = Global::OurModulesList->Strings[ii].Pos("#"), P > 0) { // remove any suffix
	Variation = pow(2, Global::OurModulesList->Strings[ii][P + 1] - char('1'));
	Global::OurModulesList->Strings[ii] = Global::OurModulesList->Strings[ii].Delete(Global::OurModulesList->Strings[ii].length() - 1, 2);
	}
	int jj = Global::AllModulesList->IndexOf(Global::OurModulesList->Strings[ii]);
	if (jj < 0) {
	CRHMException Except((Global::OurModulesList->Strings[ii] + " Module not defined in CRHM model").c_str(), ERR);
	Global::OurModulesList->Clear();
	//Application->MessageBox(Except.Message.c_str(), "Missing module", MB_OK);
	LogError(Except);
	return;
	}

	((ClassModule*)Global::AllModulesList->Objects[jj])->variation = Variation;

	Global::OurModulesList->Objects[ii] = Global::AllModulesList->Objects[jj];
	}*/

	ProjectOpen = true;

	InitModules();

	SqueezeParams();  // converts all parameters to shared parameters

					  //dirty = true;
}

void CRHMmain::DoPrjOpen(string OpenNamePrj, string PD) {


	//saving the project file path. added by Manishankar.
	OpenProjectPath = OpenNamePrj;

	MapPar::iterator itPar;
	ClassPar *thisPar = NULL;
	ClassVar *thisVar;
	ifstream DataFile;
	unsigned short Variation;

	string module, param, Descrip, Line, name;
	//string module, param, Descrip, Line, name;
	string S, s;
	string SS;


	//system("java -jar -min d:/javadatabaseaccess/DatabaseAccess.jar");


	//  string Default = GetCurrentDir();
	/*
	int iFileHandle = FileOpen(OpenNamePrj, fmOpenRead);
	if(iFileHandle > -1){ // not file error
	int T = FileGetDate(iFileHandle);
	ProjectFileDate = FileDateToDateTime(T);
	FileClose(iFileHandle);
	}*/

	DataFile.open(OpenNamePrj.c_str());
	if (!DataFile) {
		Common::Message("cannot open file", "File Error");
		return;
	}



	ProjectDirectory = GetCurrentDir();

	Dt0 = time(NULL); // used to calculate project load time

	bool Prj = Common::lowercase(OpenNamePrj).find(".prj") != string::npos;

	//DataFile.getline(Descrip, CharLength);
	getline(DataFile, Descrip);

	DataFile.ignore((numeric_limits<streamsize>::max)(), '#');
	//DataFile.getline(Line, CharLength);
	getline(DataFile, Line);

	Global::MacroModulesList->clear();

	try {

		/*
		//get project id
		makeQuery("query", "select projectid, projectname from project where projectname = 'test4.prj'", "projectid projectname", 2);
		string res = queryResult->Strings[0];
		std::istringstream iss(res);

		*/



		//reading the macros


		//reading the dates


		//reading the observations





		do {
			DataFile >> S;
			if (DataFile.eof()) break;

			DataFile.ignore((numeric_limits<streamsize>::max)(), '#');
			//DataFile.getline(Line, CharLength);
			getline(DataFile, Line);

			if (S == "AKAs:") {
				string module, type, name, alias, source;

				while (!DataFile.eof()) {
					DataFile >> type;
					if (type[1] == '#') break;
					DataFile >> module >> name >> alias;

					TAKA Type = AKAtype(type);

					if (Type == TAKA::VARG || Type == TAKA::OBSR || Type == TAKA::OBSF) {
						DataFile >> source;
						alias += ' ' + source;
					}

					if (Type != TAKA::AKAERROR) {
						Pairstr2 Item = Pairstr2(type + " " + module + " " + name, alias);
						Global::MapAKA.insert(Item);
					}

					if (DataFile.eof()) return; // final exit

				}
			}
			else if (S == "Macros:") {
				getline(DataFile, S);

				while (S[0] != '#') {
					//string sub = S.substr(1, S.length() - 2);
					string sub = "";
					size_t pos = 1; // start at 1 since first character on macro line should be a single quote
					while (pos<S.length() && S[pos] != '\'') sub.push_back(S[pos++]); // build token until next single quote

					Global::MacroModulesList->push_back(sub);
					getline(DataFile, S);
				}
				MacroLoad();
			}
			else if (S == "Observations:") {
				getline(DataFile, S);
				while (S[0] != '#') {

					if (this->ObsFileDirectory == "")
					{
						SS = S;
					}
					else
					{
						SS = this->ObsFileDirectory + S;
					}
					int l = SS.length();
					if (SS[l-1] == '\r') { SS[l-1]='\0'; }
					if (FindFileName(SS)) {
						OpenNameObs = SS;

						bool test = OpenObsFile(SS);
						//if (!OpenObsFile(SS))
						//{

						//				      }   // was return
					}
					else {
						Common::Message(SS.c_str(), "Cannot find observation file. Exiting.");
						exit(1);
					}
					getline(DataFile, S);
				}
			}
			else if (S == "Dates:") {
				int D[3]{};
				double DT;

				for (int ii = 0; ii < 3; ii++)
					DataFile >> D[ii];

				DT = StandardConverterUtility::EncodeDateTime((int)D[0], (int)D[1], (int)D[2], 0, 0); // check
				StartDatePicker = DT;

				int c;
				while ((c = DataFile.peek(), c == 32)) {
					DataFile.get();
					c = DataFile.peek();
				}

				if (iswdigit(c) && ObsFilesList->size() == 0) {
					DataFile >> Global::Freq;
					Global::Interval = 1.0 / Global::Freq;
				}
				else
					DataFile.ignore(256, '\n');

				for (int ii = 0; ii < 3; ii++)
					DataFile >> D[ii];

				DT = StandardConverterUtility::EncodeDateTime((int)D[0], (int)D[1], (int)D[2], 0, 0);
				EndDatePicker = DT;

				DataFile >> S;
			}
			else if (S == "Modules:") {
				Global::OurModulesList->clear();

				for (;;) {
					getline(DataFile, S);
					if (S[0] == '#') break;

					bool InGrp = false;
					long idx = S.find('+');
					if (idx != -1) {
						S = S.substr(idx + 1);
						InGrp = true;
					}
					idx = S.find(' ');
					s = S.substr(0, idx);

					idx = S.find('#');
					if (idx != -1) {
						Variation = (unsigned short) pow(2, S[idx + 1] - char('1'));
						s = S.substr(0, idx);
					}
					else
						Variation = 0;


					if (!InGrp)
					{
						Global::OurModulesVariation->push_back(std::pair<std::string, unsigned short>(s, Variation));
					}
						
					idx = S.find(' ');
					S = S.substr(idx + 1);
					idx = S.rfind(' ');
					S = S.substr(0, idx);

					transform(S.begin(), S.end(), S.begin(), ::toupper);
					idx = S.rfind(".DLL");
				}

				for (
					std::list<std::pair<std::string, unsigned short>>::iterator it = Global::OurModulesVariation->begin(); 
					it != Global::OurModulesVariation->end(); 
					it++
					) 
				{
					string Name = it->first;
					int jj = Global::AllModulesList->count(Name);
					if (jj == 0) 
					{
						CRHMException Except("Unknown Module: " + string(Name.c_str()), TExcept::ERR);
						Common::Message(Except.Message.c_str(),
							"Unknown Module: incorrect CRHM version or DLL not loaded");
						LogError(Except);
						
						for (
							std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
							it != Global::OurModulesList->end();
							it++
							)
						{
							if (it->first == Name)
							{
								Global::OurModulesList->erase(it);
								break;
							}
						}

						Global::OurModulesVariation->erase(it);

						DataFile.seekg(0, ios_base::end);  // cause break out
					}
					else 
					{
						Variation = it->second;
						Global::AllModulesList->find(Name)->second->variation = Variation;
						Global::OurModulesList->push_back(std::pair<std::string, ClassModule*>(Name, Global::AllModulesList->find(Name)->second));
					}
				}

				InitModules();
			}
			else if (S == "Dimensions:") {
				DataFile >> S;
				long dim;
				while (S[0] != '#') {
					DataFile >> dim;

					if (S == "nhru") {
						Global::nhru = dim;
						Global::maxhru = dim;
					}
					else if (S == "nobs") {
						Global::nobs = dim;
						Global::maxobs = dim;
					}
					else if (S == "nlay") {
						Global::nlay = dim;
						Global::maxlay = dim;
					}
					DataFile >> S;
				}
			}


			else if (S == "Parameters:") {

				int c;
				long Cols, Rows;
				bool TooFewHRUs = false;
				string ss;

				while (!DataFile.eof()) {
					DataFile >> module;
					if (module[1] == '#') break;
					DataFile >> param;

					if (DataFile.eof()) return; // final exit

					DataFile.ignore((numeric_limits<streamsize>::max)(), '\n'); // need for character input, why?

					S = "";

					do { // determine # columns
						getline(DataFile, ss);
						S += ss + ' ';
						while (c = DataFile.peek(), iscntrl(c) || isspace(c))
							DataFile.get();

					} while (c = DataFile.peek(), !isalpha(c) && c != '#');

					string Sc = S; // use copy
					string::iterator pos; // first handle single quotes
					bool inField = false;

					for (pos = Sc.begin(); pos != Sc.end(); ++pos) { // change spaces to '_' to keep form
						if (*pos == '\'')
							inField = !inField;
						if (inField && *pos == ' ')
							*pos = '_';
					}

					istringstream instr; // count columns
					instr.clear();
					instr.str(Sc);
					Cols = 0;
					for (;;) {
						instr >> s;
						if (instr.fail()) break;
						++Cols; // # of HRU's in Basin
					}

					if ( module ==  "Shared") {
						// write Shared parameters to module parameters
						// all parameter values are set to basin values.  If re-defined in a module will be changed.
						MapPar::iterator itPar;
						for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar) {
							thisPar = (*itPar).second;
							if (thisPar->param == param) {
								if (thisPar->dim == Cols / thisPar->lay) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
									break;
								//                else if(Cols > 0 && Cols%thisPar->lay == 0) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
								//                  break;
								else if (thisPar->varType == TVar::Txt && thisPar->dimen < TDim::NHRU) // text can have variable length
									break;
								else if (thisPar->param == "obs_elev" || thisPar->param == "soil_withdrawal")
									break;
								else { // Added to handle 2D parameters
									if ((thisPar->param == param) && (thisPar->dim == Cols / thisPar->dim))
									{
										break;
									}
									else
									{
										thisPar = NULL;
									}
										
								}
							}
							else
								thisPar = NULL; // required for last loop when parameter not found
						}
					}
					else {
						thisPar = ClassParFind(module, param); // find module parameter for template
						if (thisPar)
							module = thisPar->module.c_str(); // set it to found name
					}

					if (thisPar) {
						ClassPar *newPar = new ClassPar(*thisPar);
						newPar->module = module; // set module name
						if (thisPar->varType == TVar::Txt) {
							//newPar->Strings->DelimitedText = S.c_str();
							newPar->Strings->DelimitedText(S.c_str());
							//int a = 10;
						}
						else {
							Rows = 0;
							istringstream instr; // count columns
							instr.clear();
							instr.str(S);
							for (int jj = 0; jj <thisPar->lay; ++jj) {
								Cols = 0;
								for (int ii = 0; ii < newPar->dim; ++ii) {
									if (newPar->varType == TVar::Float) {
										double x;
										instr >> x;
										if (instr.fail())
											break;
										newPar->layvalues[jj][ii] = x;
									}
									else if (newPar->varType == TVar::Int) {
										long x;
										instr >> x;
										if (instr.fail())
											break;
										newPar->ilayvalues[jj][ii] = x;
									}
									++Cols;
								} // for ii (Cols)

								if (instr.fail()) { // parameter data shortage

									if (!TooFewHRUs && newPar->module != "Shared") {
										//Application->MessageBox(string("parameter \"" + thisPar->param + "\" in module \"" + newPar->module + "\" only some parameter values or layers are available.").c_str(),
										//"Too few parameter values or layers. Duplicating last HRU values.", MB_OK);
										if (newPar->lay > Global::nlay)
											Global::nlay = newPar->lay;

										TooFewHRUs = true;
									}

									if (!(Cols == 0 && newPar->lay > Rows)) { // always handle rows before filling columns

										for (int ii = Cols; ii < newPar->dim; ++ii) { // fills columns
											if (newPar->varType == TVar::Float)
												newPar->layvalues[Rows][ii] = newPar->layvalues[Rows][ii - 1];
											else
												newPar->ilayvalues[Rows][ii] = newPar->ilayvalues[Rows][ii - 1];
										}
									} // if
									else {
										for (int jjj = Rows; jjj <thisPar->lay; ++jjj) {
											for (int ii = 0; ii < newPar->dim; ++ii) {
												if (newPar->varType == TVar::Float)
												{
													//manishankar. commented to run the macro code. need to activate.
													newPar->layvalues[jjj][ii] = newPar->layvalues[jjj - 1][ii];
												}
												else
												{
													//manishankar. commented to run the macro code. need to activate.
													newPar->ilayvalues[jjj][ii] = newPar->ilayvalues[jjj - 1][ii];
												}
											} // for
										} // for
									} // else
								}
								++Rows;
							} // for jj (Rows)
						} // else

						if (module == "Shared") {// Shared parameters first - initially over-write all others
							SetSharedParams(newPar); // copy template parameter to basin module
							delete newPar;
						}
						else
						{
							ClassParSet(newPar);  // can delete newPar!
						}
							
					}
					else {
						if (param != "Use_Observations_As_Supplied") {
							CRHMException Except("Unknown Module Parameter: " + module + " -> " + param +
								" in " + OpenNamePrj, TExcept::ERR);
							//Application->MessageBox(Except.Message.c_str(), "Unknown Parameter in project file", MB_OK);
							LogError(Except);
						}

						while (c = DataFile.peek(), !isalpha(c) && c != '#')
							DataFile.ignore(256, '\n');
					}
					long cnt = Global::MapPars.size();
					DataFile.clear();
				} // while
				SqueezeParams();  // converts identical parameters to shared parameters
			}

			else if (S == "Display_Variable:") {
				while (!DataFile.eof()) {
					DataFile >> module;
					if (module[1] == '#') break;
					DataFile >> name;
					if (DataFile.eof()) return; // final exit

					S = string(module) + ' ' + string(name);
					long Index;
					string comma;
					thisVar = ClassVarFind(S);
					if (thisVar) {

						for (; ; ) {
							DataFile >> Index;
							if (DataFile.fail()) break;

							if (Index < 0) {
								Index = labs(Index);
								thisVar->TchrtOpt = 1;
							}
							if (DataFile.peek() != ',')
								SS = thisVar->name + "(" + Common::longtoStr(Index) + ")";
							else {
								DataFile >> comma;
								SS = thisVar->name + "(" + Common::longtoStr(Index) + comma + ")";
							}

							bool listContainsSS = false;
							for (std::list<std::pair<std::string, ClassVar*>>::iterator listIt = SelectedVariables->begin();
								listIt != SelectedVariables->end();
								listIt++)
							{
								if (listIt->first == SS) 
								{
									listContainsSS = true;
								}
							}

							//int index = IndexOf(ListBox3, SS);
							if (listContainsSS == false  && Index <= thisVar->dim)
							{
								SelectedVariables->push_back(std::pair<std::string, ClassVar*>(SS, thisVar));
							}
								
						} // for
					}
					else {
						CRHMException Except("Unknown Variable " + S +
							" in " + string(OpenNamePrj.c_str()), TExcept::ERR);
						Common::Message(Except.Message.c_str(),
							"Unknown Variable in project file");
						LogError(Except);

						DataFile.ignore(256, '\n');
					}
					DataFile.clear();
				} // while
			}
			else if (S == "Display_Observation:") {

				while (!DataFile.eof()) {
					DataFile >> module;
					if (module[1] == '#') break;
					DataFile >> name;
					if (DataFile.eof()) return; // final exit

					string Kind;
					long Index;

					S = string(module) + ' ' + string(name);
					thisVar = ClassVarFind(S);

					if (thisVar && thisVar->FileData != NULL) {

						for (int ii = 0; ii < 100; ii++) {
							DataFile >> Index >> Kind;
							if (DataFile.fail()) break;

							if (Kind == "_obs") Kind = "";
							SS = thisVar->name + "(" + Common::longtoStr(labs(Index)) + ")" + Kind;
							
							
							bool selectedObservationsContainsSS = false;
							for ( 
								std::list<std::pair<std::string, TSeries*>>::iterator it = SelectedObservations->begin();
								it != SelectedObservations->end();
								it++
								)
							{
								if (it->first == SS)
								{
									selectedObservationsContainsSS = true;
								}
							}

							if (selectedObservationsContainsSS != true) 
							{

								TSeries *cdSeries = NULL;
								if (thisVar->FileData->Times == NULL) {
									//                  cdSeries = new TSeries(Global::DTmax - Global::DTmin);
									double Dif = EndDatePicker - StartDatePicker;
									TSeries * cdSeries = new TSeries(((int)(Dif * thisVar->FileData->Freq))*thisVar->FileData->ModN);

									//move inside to avoid null ptr exception - Matt
									cdSeries->Tag = thisVar;

									cdSeries->Title = SS;
								}

								SelectedObservations->push_back(std::pair<std::string, TSeries *>( SS, cdSeries));
								//                AddObsPlot((ClassVar *) thisVar, cdSeries, SS,
								//                FindObservationType(Kind.c_str()));
							}
						}
					}
					else {
						CRHMException Except("Unknown Variable " + S +
							" in " + string(OpenNamePrj.c_str()), TExcept::ERR);
						Common::Message(Except.Message.c_str(),
							"Unknown Variable in project file");
						LogError(Except);

						DataFile.ignore(256, '\n');
					}
					DataFile.clear();
				}
			}
			else if (S == "Initial_State") {
				getline(DataFile, S);
				if (S[0] != '#') {
					SS = S;
					int l = SS.length();
					if (SS[l - 1] == '\r') { SS[l - 1] = '\0'; }
					if (FindFileName(SS)) {
						OpenNameState = SS;
						OpenStateFlag = true;

					}
					else
						OpenNameState = "";

					DataFile.ignore((numeric_limits<streamsize>::max)(), '#');
					DataFile >> S;
				}
			}
			else if (S == "Final_State") {
				getline(DataFile, S);
				if (S[1] != '#') {
					SS = S;
					int l = SS.length();
					if (SS[l - 1] == '\r') { SS[l - 1] = '\0'; }
					SaveStateFileName = SS;
					SaveStateFlag = true;
					DataFile >> S;
				}
				else
					SaveStateFileName = "";
				}
			else if (S == "Log_Last") {
				ReportAll = false;
			}
			else if (S == "Log_All") {
				ReportAll = true;
			}
			else if (S == "Auto_Run") {
				;
			}
			else if (S == "Auto_Exit") {
				;
			}
			else if (S == "TChart:") {

				while (!DataFile.eof()) {
					getline(DataFile, S);
					if (DataFile.eof()) break;
					if (S[0] == '#') break;
				}
			}
		} while (!DataFile.eof());
	}

	catch (CRHMException Except) {
		Common::Message(Except.Message.c_str(), "Loading project Error");
		DataFile.close();
		return;
	}

	DataFile.close();
}


void CRHMmain::SetSharedParams(ClassPar *basinPar) {

	// copy basin parameter to all module parameters

	ClassPar *thisPar;
	MapPar::iterator itPar;

	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar) {
		thisPar = (*itPar).second;
		if (basinPar == thisPar) // skip itself
			continue;
		if (thisPar->param == basinPar->param && thisPar->dim == basinPar->dim)
			thisPar->Change(*basinPar);
	}
}


void CRHMmain::FormCreate() {

	Global::BuildFlag = TBuild::BUILD;

	Global::maxhru = 1;
	Global::maxlay = 1;
	Global::maxobs = 1;

	Global::Freq = 48;
	Global::Interval = 1.0 / Global::Freq;

	cdSeries = NULL;

	time_t Dt = time(NULL);
	OpenStateFlag = false;

	Global::nhru = Global::maxhru;
	Global::nobs = Global::maxobs;
	Global::nlay = Global::maxlay;

	Global::OBS_AS_IS = false;

	ObsFilesList = new std::list<std::pair<std::string, ClassData*>>();

	ProjectList = new std::list<std::string>;

	
	Global::AllModulesList = new std::map<std::string, ClassModule * >;
	Global::OurModulesList = new std::list<std::pair<std::string, ClassModule*>>;
	Global::OurModulesVariation = new std::list<std::pair<std::string, unsigned short>>;
	Global::ModuleBitSet = new std::set<std::string>;

	Global::MacroModulesList = new std::vector<std::string>;
	

	Global::AllModelsList = new TStringList;
	Global::AllModelsList->Sorted = true;

	Global::ModelModulesList = new TStringList;
	Global::ModelModulesList->Sorted = false;

	Global::OurHelpList = NULL;   // DLL help files
	Global::PendingDLLModuleList = new TStringList; // current DLL modules

	Global::ReportList = NULL; //

	Global::DeclRootList = new TStringList;

	AllVariables = new std::map<std::string, ClassVar*>();
	AllObservations = new std::map<std::string, ClassVar*>();
	SelectedVariables = new std::list<std::pair<std::string, ClassVar*>>();
	SelectedObservations = new std::list<std::pair<std::string, TSeries*>>();

	MoveModulesToGlobal();
	((ClassModule*)Global::PendingDLLModuleList->Objects[0])->OurAdmin->Accept(mbYesToAll);
	++InitModCnt;

	//ApplicationDir = "C:\CRHM_Borland\bin\CRHM";

	Global::OldModuleName = new TStringList;
	Global::NewModuleName = new TStringList;
	Global::OldModuleName->CommaText("long, CanopyClearingGap2, pbsm_WQ, Soil_WQ, Netroute_WQ, Netroute_M_D_WQ");
	Global::NewModuleName->CommaText("longVt, CanopyClearingGap, WQ_pbsm, WQ_Soil, WQ_Netroute, WQ_Netroute_M_D");

#if !defined NO_MODULES
	for (int ii = 0; ii < Global::NewModuleName->Count; ++ii) 
	{
		size_t jj = Global::AllModulesList->count(Global::NewModuleName->Strings[ii]);
		assert(jj != 0);
		Global::OldModuleName->Objects[ii] = (TObject*)jj;
	}
#endif

	Global::CRHMStatus = 0;  // Status
	Global::CurrentModuleRun = -1;  // currently executing module
	Global::CRHMControlSaveCnt = 0; // NewModules input

	Global::HRU_OBS_DIRECT = new long*[5];
	for (int jj = 0; jj < 5; ++jj) {
		Global::HRU_OBS_DIRECT[jj] = new long[500];

		for (long ii = 0; ii < 500; ++ii)
			Global::HRU_OBS_DIRECT[jj][ii] = ii + 1;
	}

	Global::HRU_OBS = Global::HRU_OBS_DIRECT;

	Global::NaNcheck = false;
	Global::LOGVARLOAD = false;
	

}

void  CRHMmain::InitModules(void) {

	//ClassVar *thisVar; variable is unreferenced commenting out for now - jhs507

	Global::BuildFlag = TBuild::DECL;

	// executes the DECL portion of the declvar/declparam etc. routines
	for (
		std::list<std::pair<std::string, ClassModule *>>::iterator it = Global::OurModulesList->begin(); 
		it != Global::OurModulesList->end(); 
		it++
		) 
	{
		it->second->nhru = Global::nhru;
		it->second->decl();
	}

	Label4Click();
}


void  CRHMmain::Label4Click(void) {

	ClassVar *thisVar;
	MapVar::iterator itVar;
	string Newname;

	AllVariables->clear();

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		if (thisVar->varType < TVar::Read && thisVar->visibility == TVISIBLE::USUAL && thisVar->dimen != TDim::NREB) {
			Newname = DeclObsName(thisVar);
			if (this->AllVariables->count(Newname) == 0)
			{
				this->AllVariables->insert(std::pair<std::string, ClassVar*>(Newname, thisVar));
			}
		}
	}
}
//---------------------------------------------------------------------------

TFun  CRHMmain::FindObservationType(string Kind) {

	if (Kind == "_obs") Kind = "";
	for (int ii = (int)TFun::FOBS; ii <= (int)TFun::LAST; ii++)
		if (Kind == Sstrings[ii]) return (TFun)ii;
	return (TFun::FOBS);
}
//---------------------------------------------------------------------------

void  CRHMmain::SqueezeParams(void) {

	paras MapInfo; // holds all parameters - used for processing
	ClassPar *thisPar, *thisPar2;

	// make multimap: keyed by parameter name holding pointer to parameter
	MapPar::iterator itPar; // iterator for Global::MapPars
	itPar = Global::MapPars.begin();
	while (itPar != Global::MapPars.end()) {
		thisPar = (*itPar).second;
		string S = ((*itPar).second)->param;
		Pairinfo Item = Pairinfo(S, Pinfo(new Classinfo(thisPar)));
		MapInfo.insert(Item);
		++itPar;
	} // while

	paras::iterator itPar2, itPar3, itPar4;
	itPar2 = MapInfo.begin();
	pair<paras::iterator, paras::iterator> range;
	GrpParas Matched; // working matched parametrs multimap
	string Key; // key for eventual basin parameters
	MapPar MapParsNew; // holds final processed parameters

					   // process multimap by parameter name
	while (itPar2 != MapInfo.end()) {
		string S = (*itPar2).first;
		long thiscnt = MapInfo.count(S); // # of occurrences of string S

										 // if duplicate parameter name from other module
		if (thiscnt > 1) {
			range = MapInfo.equal_range(S);
			long greatestCnt = 0;
			bool first = true;

			ClassPar *SharedPar = NULL; // set if Simple actual Basin parameter

										// proceed through duplicate list
			for (itPar3 = range.first; itPar3 != range.second; itPar3++) {
				Classinfo *info3 = ((*itPar3).second).get();

				if (info3->rootinfo == NULL)
					info3->rootinfo = info3;

				thisPar = info3->thisPar;

				range.first++;

				if (info3->matched) // handled by earlier pass
					continue;

				PairPar Item = PairPar(thisPar->module, thisPar);
				Matched.insert(Item);

				// compare with following duplicate entries
				for (itPar4 = range.first; itPar4 != range.second; itPar4++) {
					Classinfo *info4 = ((*itPar4).second).get();

					if (info4->matched) // skip if already matched
						continue;

					thisPar2 = info4->thisPar;

					// check for duplicate values
					bool match = thisPar->Same(*thisPar2);

					// if same values indicate could be merged
					if (match) {
						PairPar Item = PairPar(thisPar->module, thisPar2);
						Matched.insert(Item);
						info4->matched = true;
						if (++info3->rootinfo->cnt > greatestCnt) {
							greatestCnt = info3->rootinfo->cnt;
							Key = info3->rootinfo->thisPar->module;
						} // update Key
					} // if(match)

				} // for(compare successively with first in range
			} // for(range of S)

			GrpParas::iterator itPar5;
			if (Matched.count(Key) > 1) {
				pair<GrpParas::iterator, GrpParas::iterator> range2;
				range2 = Matched.equal_range(Key);
				bool first = true;
				for (itPar5 = range2.first; itPar5 != range2.second; itPar5++) {
					thisPar = (*itPar5).second;
					// save module as shared parameters in MapPars and SharedMapPars
					if (first) {
						thisPar->module = "Shared";
						PairPar Item = PairPar("Shared " + thisPar->param, thisPar);
						MapParsNew.insert(Item);
						Global::SharedMapPars.insert(Item);
						first = false;
					} // first
					else  // remove module parameters so as basin parameters visible
						delete thisPar;
					(*itPar5).second = NULL; // Indicate has been handled
				} // for(range of S)
			} // if(greatestCnt > 0)

			for (itPar5 = Matched.begin(); itPar5 != Matched.end(); itPar5++) {
				thisPar = (*itPar5).second;
				if (!thisPar) // already handled
					continue;
				PairPar Item = PairPar(thisPar->module + ' ' + thisPar->param, thisPar);
				MapParsNew.insert(Item);
			}
			Matched.clear();
		} // if(thiscnt > 1)
		else {
			Classinfo *info = ((*itPar2).second).get();
			thisPar = info->thisPar;
			PairPar Item = PairPar(thisPar->module + ' ' + thisPar->param, thisPar);
			MapParsNew.insert(Item);
		}
		MapInfo.erase(S);
		itPar2 = MapInfo.begin();
	} // while

	Global::MapPars.clear();
	Global::MapPars = MapParsNew;
}
//---------------------------------------------------------------------------

void  CRHMmain::SetBasinParams(ClassPar *basinPar) {

	// copy basin parameter to all module parameters

	ClassPar *thisPar;
	MapPar::iterator itPar;

	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar) {
		thisPar = (*itPar).second;
		if (basinPar == thisPar) // skip itself
			continue;
		if (thisPar->param == basinPar->param && thisPar->dim == basinPar->dim)
			thisPar->Change(*basinPar);
	}
}


//-------------------------------------------------------------------------------------

void CRHMmain::MacroClick(void)
{
	if (InitMacroCnt && InitModCnt) {
		--InitModCnt;
		InitMacroCnt = 0;
	}

	//need to activate this line.
	ListBoxMacroClear(); // clears AllVariables & AllObservations

	AdminMacro.MacroClear();

	MacroLoad();

	AdminMacro.MacroUpdate();

	InitModules();
}


void CRHMmain::ListBoxMacroClear() { // used by Macro

	ClassVar * thisVar;


	if (SeriesCnt <= 0)
	{
		SelectedVariables->clear();
	}
	else {
		
		string serTitle;
		int jj;

		//Initialize the cdSeries variable in case it has not been yet - Matt
		SeriesCnt = SelectedVariables->size();
		cdSeries = new TSeries*[SeriesCnt];
		int Cnt = Global::DTmax - Global::DTmin;
		for (int ii = 0; ii < SeriesCnt; ++ii)
			cdSeries[ii] = new TSeries(Cnt);

		for (jj = 0; jj < SeriesCnt; jj++)
		{
			serTitle = cdSeries[jj]->Title;
		}



		bool listContainsSerTitle = false;
		std::list<std::pair<std::string, ClassVar*>>::iterator positionOfSerTitle;
		for (std::list<std::pair<std::string, ClassVar*>>::iterator listIt = SelectedVariables->begin();
			listIt != SelectedVariables->end();
			listIt++)
		{
			if (listIt->first == serTitle)
			{
				listContainsSerTitle = true;
				positionOfSerTitle = listIt;
			}
		}

		if (listContainsSerTitle == true)
		{

			thisVar = positionOfSerTitle->second;
			if (thisVar->DLLName == "Macro") 
			{ 
				// delete only macros
				//cdSeries[jj]->ParentChart = NULL;
				//cdSeries[jj]->Clear();

				for (int kk = jj + 1; kk < SeriesCnt; ++kk)
				{
					cdSeries[kk - 1] = cdSeries[kk];
				}
					
				SelectedVariables->erase(positionOfSerTitle);
				SeriesCnt--; // no need to increment
			}
			//else
			//++jj; // increment
		}
	}

	map<string, ClassVar*>::iterator it;

	for (it = AllVariables->begin(); it != AllVariables->end(); it++)
	{
		if (it->second->DLLName == "Macro")
		{
			AllVariables->erase(it->first);
			it = AllVariables->begin(); //This line included to match pervious code only. 
		}
	}

}






//--------------------------------------------------------------------------------------
void CRHMmain::MacroLoad(void)
{
	Global::GroupCntTrk = 0;
	Global::StructCntTrk = 0;

	ClearModules(false);



	if (Global::MacroModulesList->size() > 0) 
	{
		int Macro = 0;

		//while (Global::MacroModulesList->Count - 1 > Macro) {
		while (Macro < Global::MacroModulesList->size()) 
		{

			string s = Global::MacroModulesList->operator[](Macro);
			string::size_type ppp = s.find_last_not_of(' ');
			if (s.empty() || ppp == string::npos || s[0] == '/') 
			{
				++Macro;
				continue;
			}
			string Desc;
			string::size_type pp = s.find_first_of(" /");
			if (pp != string::npos) {
				Desc = s.substr(pp);
				s = s.substr(0, pp);
				pp = Desc.find_first_not_of(" /");
				Desc = Desc.substr(pp);
				Desc = '\'' + Desc + '\''; // Bld handles as block
			}
			else
			{
				Desc = "'no description given'"; // Bld handles as block
			}
				

			ClassMacro *Custom = new ClassMacro(s, Macro, "04/20/06", Desc);
			AdminMacro.AddModule(Custom);

			string S, SS;

			while (S = Common::trim(Global::MacroModulesList->operator[](Macro)), SS = S.substr(0, 3),
				!(SS == "end" &&
				(S.length() == 3 || S.find_first_of(" /") != string::npos)) &&
				Global::MacroModulesList->size() > Macro
				)

				++Macro;

			++Macro;
		}

		AdminMacro.LoadCRHM("Macro");
		AdminMacro.Accept(mbYesToAll);

		if (InitMacroCnt == 0) {
			InitMacroCnt = 1;
			++InitModCnt;
		}

		if (SeriesCnt > 0) {
			SeriesCnt = 0;
		}
	}
}

//---------------------------------------------------------------------------
string CRHMmain::DeclObsName(ClassVar *thisVar) 
{
	string Newname = thisVar->name;
	
	//std::map<std::string, ClassModule*>::iterator pos = Global::OurModulesList->find(thisVar->module); // find module
	
	std::list<std::pair<std::string, ClassModule*>>::iterator pos;
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
		it != Global::OurModulesList->end();
		it++
		)
	{
		if (it->first == thisVar->module)
		{
			pos = it;
		}
	}

	if (pos != Global::OurModulesList->end() && Newname.rfind("#") != string::npos) // -1 for "obs" and "#" for declared "obs"
	{ 
		ClassModule* thisModule = pos->second;
		if (thisModule->isGroup) { // if group add suffix
			string AA("@@");
			AA[1] += (char) thisModule->GroupCnt;
			Newname += AA;
		}
	}
	return Newname;
}




//---------------------------------------------------------------------------

bool  CRHMmain::OpenObsFile(string FileName)
{
	ClassData  * FileData;

	  // already open

	bool fileAlreadyOpen = false;
	for (
		std::list<std::pair<std::string, ClassData*>>::iterator it = ObsFilesList->begin();
		it != ObsFilesList->end();
		it++
		)
	{
		if (it->first == FileName)
		{
			fileAlreadyOpen = true;
		}
	}

	if (fileAlreadyOpen == true)
	{
		return false;
	}
		
	if (ObsFilesList->size() == 0) {
		Global::DTstart = 0; // used to flag first data file
		Global::DTend = 0; // used to flag first data file
	}

	FileData = new ClassData(FileName);

	if (FileData->Success) {

		if (ObsFilesList->size() == 0) {


			//look at this.
			if (FileData->Times != NULL) { // handle sparse data
										   //Message("Sparse file cannot be first to be opened", "File order Error");
				delete FileData;
				return false;
			}

			setStartDate(FileData->Dt1);
			setEndDate(FileData->Dt2);

			OpenNameObs = FileName;

			Global::Interval = FileData->Interval;
			Global::Freq = FileData->Freq;

			Global::IndxMin = FileData->IndxMin;
			Global::IndxMax = FileData->IndxMax;
		}

		FileData->ModN = Global::Freq / FileData->Freq;

		
		ClassVar * thisVar;

		// always starts with this display
		// remove entries that are in observation AllVariables
		std::map<std::string, ClassVar*>::iterator it;

		for (it = AllVariables->begin(); it != AllVariables->end(); it++)
		{
			if (it->second->varType >= TVar::Read)
			{
				AllVariables->erase(it->first);
				it = AllVariables->begin(); //This included to match pervious code only.
			}
		}

		// remove entries that are in observation ListBox3
		for (std::list<std::pair<std::string, ClassVar*>>::iterator selectedVarIt = SelectedVariables->begin();
			selectedVarIt != SelectedVariables->end();
			selectedVarIt++)
		{
			thisVar = selectedVarIt->second;
			if (thisVar && thisVar->varType >= TVar::Read) 
			{
				SelectedVariables->erase(selectedVarIt);
			}
		}

		AllObservations->clear();

		MapVar::iterator itVar;
		for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
			thisVar = (*itVar).second;
			if (thisVar && thisVar->varType >= TVar::Read)
			{
				if (AllObservations->count(thisVar->name) == 0)
				{
					AllObservations->insert(std::pair<std::string, ClassVar*>(thisVar->name, thisVar));
				}
			}
		}

		ObsFilesList->push_back(std::pair<std::string, ClassData*>(OpenNameObs, FileData));

		return true;
	}
	else {
		if (ObsFilesList->size() == 0) 
		{
			Global::DTstart = 0; // used to flag first data file
			Global::DTend = 0; // used to flag first data file
		}

		delete FileData;
		return false;
	}
}
//---------------------------------------------------------------------------

void  CRHMmain::ObsCloseClick(void) {

	AllObservations->clear();

	for (
		std::list<std::pair<std::string, ClassData*>>::iterator it = ObsFilesList->begin();
		it != ObsFilesList->end();
		it++
		) 
	{
		ClassData * FileData = it->second;
		delete FileData;   // delete ClassData instance
	}

	ObsFilesList->clear();  // clear list

	Global::nobs = 1;  // reset to 1

}
//---------------------------------------------------------------------------

void  CRHMmain::ObsFileClose(void)
{
	MapVar::iterator itVar;
	ClassVar * thisVar;

	string S;  // Fix ???

	std::list<std::pair<std::string, ClassData*>>::iterator position;
	for (
		std::list<std::pair<std::string, ClassData*>>::iterator it = ObsFilesList->begin();
		it != ObsFilesList->end();
		it++
		)
	{
		if (it->first == S)
		{
			position = it;
		}
	}


	if (position == ObsFilesList->begin() && ObsFilesList->size() > 1) 
	{
		ObsCloseClick();
		return;
	}

	AllObservations->clear();

	ClassData * FileData = position->second;
	delete FileData;   // delete ClassData instance
	ObsFilesList->erase(position);  // delete entry in list

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		if (thisVar->varType >= TVar::Read)
		{
			if (AllObservations->count(itVar->second->name) == 0)
			{
				AllObservations->insert(std::pair<std::string, ClassVar*>(itVar->second->name, itVar->second));
			}
		}
	}

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) 
	{
		thisVar = (*itVar).second;
		//if (thisVar->varType < CRHM::Read && thisVar->visibility == CRHM::VARIABLE) //changed by Manishankar.
		if (thisVar->varType < TVar::Read && thisVar->visibility == TVISIBLE::USUAL)
		{
			if (AllVariables->count((*itVar).second->name) == 0)
			{
				AllVariables->insert(std::pair<std::string, ClassVar*>((*itVar).second->name, (*itVar).second));
			}	
		}
	}

	delete cdSeries;
}
//---------------------------------------------------------------------------

void  CRHMmain::FormDestroy(void)
{

	for (
		std::list<std::pair<std::string, ClassData*>>::iterator it = ObsFilesList->begin();
		it != ObsFilesList->end();
		it++
		) 
	{
		ClassData * FileData = it->second;
		delete FileData;   // delete ClassData instance
	}

	delete ObsFilesList;

	ModVarRemove(Global::MapVars);
	Global::SharedMapPars.clear();

	delete ProjectList;

	delete AllVariables;
	delete AllObservations;
	delete SelectedVariables;
	delete SelectedObservations;

	delete Global::OurModulesList;

	delete Global::ModelModulesList;

	delete Global::DeclRootList;

	delete Global::PendingDLLModuleList;
}
//---------------------------------------------------------------------------

void   CRHMmain::FreeChart1(void)
{
	if (SeriesCnt > 0) {
		for (int ii = 0; ii < SeriesCnt; ii++) {

			ClassVar* thisVar = (ClassVar *)cdSeries[ii]->Tag;
			if (thisVar->FunKind > TFun::FOBS && !thisVar->values && !thisVar->ivalues)
				delete thisVar;

		}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

bool  CRHMmain::FileExistsSp(string FileName) {

	ifstream DataFile;

	DataFile.open(FileName.c_str());
	if (DataFile) {
		DataFile.close();
		return true;
	}
	else
		return false;
}
//---------------------------------------------------------------------------

bool  CRHMmain::FindFileName(string &FileName) {

	string FilePart;

	//ApplicationDir =   ExtractFilePath(AnsiReplaceStr(Application->ExeName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples

	//ApplicationDir =   "C:/CH/CRHM/Examples

	//ProjectDirectory = ExtractFilePath(AnsiReplaceStr(OpenNamePrj, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples

	if (FileExistsSp(FileName)) // file path directory
		return true;

	string::size_type Pos = FileName.find_last_of("\\/");
	if (Pos) {
		FilePart = FileName.substr(Pos + 1, FileName.length());

		if (FileExistsSp(FilePart)) { // current directory
			FileName = FilePart;
			return true;
		}
	}
	else
		FilePart = FileName;

	// original file may now be in project directory
	string NewFileName = ProjectDirectory + FilePart;
	if (FileExistsSp(NewFileName)) {
		FileName = NewFileName;
		return true;
	}

	// original file may now be in Application directory
	NewFileName = ApplicationDir + FilePart;
	if (FileExistsSp(NewFileName)) {
		FileName = NewFileName;
		return true;
	}

	return false;
}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

string  CRHMmain::ExtractHruLay(string S, long &Hru, long &Lay) {

	long jj = S.find("(");
	long jj1 = S.find(",");
	long jj2 = S.find(")");

	Lay = 0;
	if (jj1 > -1)
		Lay = Strtolong(S.substr(jj1 + 1, jj2 - jj1 - 1));
	else
		jj1 = jj2;

	Hru = Strtolong((S.substr(jj + 1, jj1 - jj - 1)));

	return S.substr(0, jj);
}

MMSData *  CRHMmain::RunClick2Start()
{
	ClassVar *thisVar;
	double **mmsData;
	long **mmsDataL;
	bool GoodRun = true;
	MMSData * mmsdata = new MMSData();

	//TimingStatistics * ts = new TimingStatistics();

	//clock_t begintime2 = clock();


	//Classobs test("obs","undefined", CRHM::PROTO);
	//test.decl();

	MapVar::iterator itVar;
	//PlotControl->IntervalControl = 0;
	//PlotControl->IntervalLength = 3; // make default
	Global::ModuleBitSet->clear();

	Global::HRU_OBS = Global::HRU_OBS_DIRECT; // always correct? Not set by macro project?
	Global::OBS_AS_IS = false;
	Global::WQ_prj = false;


	if (Global::IndxMin != 0) { Global::IndxMin = 0; }


	if (Global::IndxMin != 0) {
#if defined(VS_GUI)
		AfxMessageBox(_T("First observation day - not an entire day"));
#endif
#if defined(COMMAND_LINE)
		string message = "First observation day - not an entire day";
		LogMessageX(message.c_str());
#endif

		return mmsdata;  // do not run
	}

	if (SelectedVariables->size() == 0) 
	{
#if defined(VS_GUI)
		AfxMessageBox(_T("No model output selected"));
#endif
#if defined(COMMAND_LINE)
		string message = "No model output selected";
		LogMessageX(message.c_str());
#endif
		return mmsdata;  // nothing selected
	}

	string Message = "Project file: " + OpenNamePrj;
	LogMessageX(Message.c_str());
	LogMessageX(" ");

	for (
		std::list<std::pair<std::string, ClassData*>>::iterator it = ObsFilesList->begin(); 
		it != ObsFilesList->end(); 
		it++
		) 
	{
		Message = "Observation file: " + it->first;
		LogMessageX(Message.c_str());
	}
	LogMessageX(" ");

	if (OpenStateFlag) {
		Message = "State file: " + OpenNameState;
		LogMessageX(Message.c_str());
		LogMessageX(" ");
	}

	double Dt = StandardConverterUtility::DateTimeDt();
	Message = string("Time of model run: ") + DttoStr(Dt) + " " + FormatString(Dt, "yy mm dd ") + ". Program " + Version;
	LogMessageX(Message.c_str());

	string S = string("Module List \"");
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
		it != Global::OurModulesList->end(); 
		it++
		) 
	{
		ClassModule* thisModule = it->second;
		S += it->first;
		if (thisModule->variation != 0) 
		{
			string AA("#0");
			AA[1] += (char) (log(thisModule->variation) / log(2) + 1);
			S += AA;
		}
		
		std::list<std::pair<std::string, ClassModule*>>::iterator pos = it;

		if (pos++ == Global::OurModulesList->end())
		{
			S += ".\"";
		}
		else
		{
			S += ", ";
		}
			
	}

	if (!Global::MapAKA.empty()) {
		Mapstr2::iterator it;
		LogMessageX("Linkage modifications (AKAs)");
		for (it = Global::MapAKA.begin(); it != Global::MapAKA.end(); ++it) {

			Message = string((*it).first.c_str()) + " " + string((*it).second.c_str());
			LogMessageX(Message.c_str());
		}
		LogMessageX(" ");
	}

	Global::DeclRootList->Clear(); // used by AKA to stop looping

								   // clears storage for observation read and function lists
	Global::OurModulesList->begin()->second->InitReadObs();

	double DTstartR = StartDatePicker;
	double DTendR = EndDatePicker;

	ClassPar *thisPar;


	double P;
	thisPar = ParFind("basin RUN_START");
	if (thisPar) {
		if (thisPar->ivalues[0] > 0)
			P = thisPar->ivalues[0];
	}
	else {
		MapPar::iterator itPar;

		for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
			thisPar = (*itPar).second;
			if (thisPar->param == "RUN_START" && thisPar->ivalues[0] > 0) {
				P = thisPar->ivalues[0];
				break;
			}
		}
	}

	thisPar = ParFind("basin RUN_END");
	if (thisPar) {
		if (thisPar->ivalues[0] > 0)
			P = thisPar->ivalues[0];
	}
	else {
		MapPar::iterator itPar;

		for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
			thisPar = (*itPar).second;
			if (thisPar->param == "RUN_END" && thisPar->ivalues[0] > 0) {
				P = thisPar->ivalues[0];
				break;
			}
		}
	}


	Global::DTmin = (int)((DTstartR - Global::DTstart)* Global::Freq);
	Global::DTindx = Global::DTmin;
	Global::DTnow = Global::DTstart + Global::Interval*((long long)Global::DTindx + 1ll);

	int Modii = 0;
	Global::MapVarsGet.clear();
	Global::MapVarsPut.clear();
	Global::MapObsGet.clear();

	try {
		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator moduleIt = Global::OurModulesList->begin();
			moduleIt != Global::OurModulesList->end();
			moduleIt++
			)
		{
			moduleIt->second->initbase();
		}
	}

	catch (CRHMException Except) { // serious error - program had to stop immediately
		LogMessageX(Except.Message.c_str()); // , "Initialisation of module - "); // + string((ClassModule*) Global::OurModulesList->Objects[Modii])->Name)
		GoodRun = false;
		//GoodRun = true;
	}

	catch (exception &E) {
		//ShowMessage(E.Message + " in Initialisation of " + ((ClassModule*) Global::OurModulesList->Objects[Modii])->Name);
		LogMessageX(E.what());
		GoodRun = false;
	}

	catch (...) {
		LogMessageX("Unknown error");
		GoodRun = false;
	}

	if (DTstartR >= DTendR) {
		LogMessageX("Start Time >= EndTime");
		GoodRun = false;
	}


	ClassData * FileData = NULL;
	if (ObsFilesList->size() > 0)
	{
		FileData = ObsFilesList->begin()->second;

		if (DTstartR < FileData->Dt1) {
			LogMessageX("Start Time before first Observation");
			GoodRun = false;
		}

		if (DTendR > FileData->Dt2) {
			LogMessageX("End Time after last Observation");
			GoodRun = false;
		}
	}

	
	

	if (GoodRun) {
		if (!OpenStateFlag) {
			thisPar = ParFind("basin INIT_STATE");
			if (thisPar && thisPar->Strings->Count && !thisPar->Strings->Strings[0].empty()) {
				OpenNameState = thisPar->Strings->Strings[0];
				OpenStateFlag = true;
			}
			else {
				MapPar::iterator itPar;

				for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
					thisPar = (*itPar).second;
					if (thisPar->param == "INIT_STATE" && thisPar->Strings->Count && !thisPar->Strings->Strings[0].empty()) {
						OpenNameState = thisPar->Strings->Strings[0];
						OpenStateFlag = true;
						break;
					}
				}
			}
		}
	}

	if (OpenStateFlag)
		ReadStateFile(GoodRun);

	if (!GoodRun) { //cleanup memory before returning

		// deletes storage for observation read list
		Global::OurModulesList->begin()->second->InitReadObs();

		// deletes module allocated storage
		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
			modIt != Global::OurModulesList->end(); 
			modIt++
			)
		{
			modIt->second->finish(false);
		}
			
		Global::BuildFlag = TBuild::DECL;
		return mmsdata;
	}

	Global::BuildFlag = TBuild::RUN;
	Global::DTmax = (int)((DTendR - Global::DTstart)* Global::Freq);

	SeriesCnt = SelectedVariables->size();

	int Cnt = Global::DTmax - Global::DTmin;
	cdSeries = new TSeries*[SeriesCnt];

	for (int ii = 0; ii < SeriesCnt; ++ii)
	{
		cdSeries[ii] = new TSeries(Cnt);
	}

	mmsData = new double*[SeriesCnt];
	mmsDataL = new long*[SeriesCnt];

	std::list<std::pair<std::string, ClassVar*>>::iterator selectedVarIterator = SelectedVariables->begin();
	for (int ii = 0; ii < SeriesCnt; ii++)
	{
		

		thisVar = selectedVarIterator->second;

		cdSeries[ii]->Tag = thisVar;

		string S = selectedVarIterator->first;
		cdSeries[ii]->Title = S;

		long lay, dim;

		S = ExtractHruLay(S, dim, lay);

		if (thisVar->varType == TVar::Float) {
			mmsDataL[ii] = NULL;
			if (thisVar->lay == 0) {
				mmsData[ii] = thisVar->values + (dim - 1);
			}
			else {
				mmsData[ii] = (thisVar->layvalues[lay - 1]) + (dim - 1);
			}
		}
		else if (thisVar->varType == TVar::Int) {
			mmsData[ii] = NULL;
			if (thisVar->lay == 0) {
				mmsDataL[ii] = thisVar->ivalues + (dim - 1);
			}
			else {
				mmsDataL[ii] = (thisVar->ilayvalues[lay - 1]) + (dim - 1);
			}
		}

		selectedVarIterator++;
	}

	LogMessageX(" ");
	S = string("timestep ") + DttoStr(Global::Interval * 24) + " hr.";
	LogDebug(S.c_str());

	LogDebugT("\"start of run\".");
	LogMessageX(" ");

	Global::CRHMControlSaveCnt = 0; // set by module
	Global::CRHMStatus = 0; // module status; module control = 1 , main control = 2 and Finished = 4. Both inhibit output.
	Global::LoopCntDown = -1;
	StatePar = NULL;
	Global::ModuleBitSet->clear();


	/////////////////// Manishankar added this from Diogo's code.
	ClassModule* Obs_preset; // used to call preset for simple projects

	std::list<std::pair<std::string, ClassModule*>>::iterator pos;
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
		it != Global::OurModulesList->end();
		it++
		)
	{
		if (it->first == "obs")
		{
			pos = it;
		}
	}

	if (pos == Global::OurModulesList->end())
	{
		Obs_preset = NULL;
	}
	else
	{
		Obs_preset = pos->second;
	}

	if (Global::LoopCnt && ((double)Global::RapidAdvanceTo == 0.0 || (double)Global::RapidAdvanceTo <= DTstartR))
		Global::RapidAdvanceTo = DTstartR + 1;
	////////////////////

	mmsdata->mmsData = mmsData;
	mmsdata->mmsDataL = mmsDataL;
	mmsdata->GoodRun = GoodRun;
	mmsdata->obs_preset = Obs_preset;
	mmsdata->S = S;
	return mmsdata;
}

void  CRHMmain::RunClick2Middle(MMSData * mmsdata, long startdate, long enddate)
{
	double **mmsData = mmsdata->mmsData;
	long ** mmsDataL = mmsdata->mmsDataL;
	bool GoodRun = mmsdata->GoodRun;
	string S = mmsdata->S;
	ClassModule* Obs_preset = mmsdata->obs_preset;

	bool First = true;
	try
	{
		if (this->ShowProgress)
		{
			print_progress_start();
		}
		

		int iter = 0;
		//for (Global::DTindx = Global::DTmin; Global::DTindx < Global::DTmax; Global::DTindx++)
		for (Global::DTindx = startdate; Global::DTindx < enddate; Global::DTindx++)
		{
			if (this->ShowProgress)
			{
				print_progress(Global::DTindx, enddate, this->UpdateProgress);
			}
			
			//CRHMLogger::instance()->log_to_console(to_string(((float)Global::DTindx / (float)enddate) * 100.0f));

			iter++;


			if (Global::Freq == 1)
				Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx);
			else
				Global::DTnow = Global::DTstart + Global::Interval*((long long)Global::DTindx + 1ll);

			if ((double)Global::RapidAdvanceTo > 0.0 && !(Global::CRHMStatus & 4)) {
				if (Global::DTnow < Global::RapidAdvanceTo)
					Global::CRHMStatus |= 2; // set module control and inhibit display

				else if (Global::DTnow == Global::RapidAdvanceTo + Global::Interval && !Global::LoopCnt) { // reached RapidAdvanceTo and NO looping.
					Global::CRHMStatus &= 125; // clear status == 2 (main control) and resume display
					LogMessage("Terminate fast loop aheadMain", TExtra::DD);
				}
				else if (Global::DTnow == Global::RapidAdvanceTo && Global::LoopCnt) { // reached RapidAdvanceTo with looping.
					if (Global::LoopCntDown == -1) { // first time
						Global::LoopCntDown = Global::LoopCnt;
						StatePar = ParFind("basin StateVars_to_Update");
						ControlSaveState(true, StatePar); // save this position
						LogMessage("Initialise LoopTo Main", TExtra::DD);
					}
				}
				else if (Global::DTnow == Global::LoopTo && Global::LoopCnt) { // reached LoopTo position
					ControlReadState(true, StatePar); // return to earlier position
					--Global::LoopCntDown; // after above ReadState
					LogMessage("Reached loop Main", TExtra::DD);
					if (Global::LoopCntDown <= 0) {
						ResetLoopList();
						Global::CRHMStatus &= 125; // remove status == 2 (inhibit display)
						Global::CRHMStatus |= 4; // flag done
						Global::LoopCntDown = -1;
						LogMessage("Terminate LoopTo Main", TExtra::DD);
						continue;
					}
				}
			} // end of RapidAdvanceTo logic

			  // determine which obervation files have good data
			DoObsStatus(First);
			// reads observations for current interval


			//--------------------------------------------------------------------------------------------------
			bool Reset = true;

			if (Obs_preset) // for simple prj, set up elev etc.
				Obs_preset->pre_run();

			for (
				std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
				modIt != Global::OurModulesList->end();
				modIt++
				) 
			{
				Global::CurrentModuleRun = modIt->first;

				long Last = Global::CRHMControlSaveCnt;

				ClassModule* p = modIt->second;
				// Simple project for module obs. For group always when !CRHMStatus otherwise only selected groups


				//clock_t btime = clock(); //////////////////////////////////////////////////////////////////////////////////////////////

				if (p->GroupCnt && ((ClassMacro*)p)->ObsModule) // only execute if group has an obs module
					((ClassMacro*)p)->ObsModule->pre_run();

				p->ReadObs(Reset);
				Reset = false;

				//double tdiff = double(clock() - btime) / CLOCKS_PER_SEC; ///////////////////////////////////////////////////////////////
				//ts->addTime("ReadObs", tdiff);

				CheckBlankModule();

				if (!p->isGroup || !Global::CRHMStatus || (Global::CRHMStatus & 1 && Global::ModuleBitSet->count(Global::CurrentModuleRun))) {
					//try
					//{
					//Common::writefile("d:/test.txt","p = "+p->Name+", p nameroot = "+p->NameRoot);
					//if (!(p->Name == "WQ_Soil_BGC"))

					p->run();
					//}
					//catch (...)
					//{
					//
					//	std::exception_ptr eptr;
					//	eptr = std::current_exception(); // capture
					//	Common::writefile("d:/test.txt", "error in p = " + p->Name + ", p nameroot = " + p->NameRoot+" ");
					//}
				}

				CheckBlankModule();

				// module flag loop

				if (Last != Global::CRHMControlSaveCnt) // means last module/group
				{
					Global::ModuleBitSet->insert(Global::CurrentModuleRun);
				}
					
			} // end for
			  //--------------------------------------------------------------------------------------------------

			  // module loop control


			if (Global::CRHMControlSaveCnt && !(Global::CRHMStatus & 1)) { // Set module mode. Save current position.
				ControlSaveState(false, StatePar);
				Global::CRHMStatus |= 1; // set module control bit and inhibit display.
				LogMessage("Start save Main", TExtra::DD);
			}

			// module loop control reset
			bool DoOutput = true;
			if ((Global::CRHMStatus & 1) && (!Global::CRHMControlSaveCnt || Global::DTindx >= Global::DTmax - 1)) { // handles daily + last day of run
				ControlReadState(false, NULL); // restore all
				Global::CRHMStatus &= 126; // reset module mode.
				Global::CRHMControlSaveCnt = 0; // required for Global::DTindx >= Global::DTmax-1 condition
				LogMessage("End save Main", TExtra::DD);
				LogDebug(" ");

				if (Global::Freq == 1) {
					Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx);
					Global::DTindx -= 1;
				}
				else {
					Global::DTnow = Global::DTstart + Global::Interval*((long long)Global::DTindx + 1ll);
					Global::DTindx -= 1;
				}

				DoOutput = false;
			}


			if (!(Global::CRHMStatus & 7) && !(Global::CRHMControlSaveCnt) && DoOutput) { // display if not module or main controlled. why?

				double xx;
				for (int ii = 0; ii < SeriesCnt; ii++) {
					if (mmsData[ii] != NULL) {
						xx = *mmsData[ii];

						if (xx < xLimit)
						{
							cdSeries[ii]->AddXY(Global::DTnow, xx);
						}
						else
						{
							cdSeries[ii]->AddXY(Global::DTnow, -9999);
						}
					}
					else {
						xx = (*mmsDataL[ii]);
						if (xx < lLimit)
						{
							cdSeries[ii]->AddXY(Global::DTnow, xx);
						}
						else
						{
							cdSeries[ii]->AddXY(Global::DTnow, -9999);
						}
					}

				}
			}

		} // end for

		if (this->ShowProgress)
		{
			print_progress_end();
		}

		int d = iter;
		Global::BuildFlag = TBuild::DECL;


	}

	catch (exception &E) {
		//string S = E.Message + " at " + FormatString(Global::DTnow, "yyyy'/'m'/'d hh':'nn") + " in '" + Global::OurModulesList->Strings[Modii] + "'";
		//    ShowMessage(S);
		string errorMessage = E.what();
		LogError(errorMessage + " (" + FloatToStrF(Global::DTnow, TFloatFormat::ffGeneral, 10, 0) + ")", TExcept::ERR);
		GoodRun = false;
	}
}

void CRHMmain::RunClick2End(MMSData * mmsdata)
{
	double ** mmsData = mmsdata->mmsData;
	long ** mmsDataL = mmsdata->mmsDataL;
	bool GoodRun = mmsdata->GoodRun;

	double Dt = StandardConverterUtility::DateTimeDt();
	string Message = string("End of model run: ") + DttoStr(Dt) + " " + FormatString(Dt, "yy mm dd ") + ". Program " + Version;
	LogMessageX(Message.c_str());

	delete[] mmsData;
	delete[] mmsDataL;

	// deletes storage for observation read list
	Global::OurModulesList->begin()->second->InitReadObs();

	// deletes module allocated storage
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt !=Global::OurModulesList->end();
		modIt++
		)
	{
		modIt->second->finish(true);
	}
		

	if (GoodRun) {
		
		/*Either print the whole report or just the last time step.*/
		if (ReportAll)
		{
			AllRprt();
		}
		else
		{
			LastRprt();
		}

		if (SaveStateFlag)
		{
			SaveState();
		}
			
	}

	//double timediff2 = double(clock() - begintime2) / CLOCKS_PER_SEC; /////////////////////////////////////////////////////
	//ts->addTime("totaltime", timediff2);

	//ts->writeStatistics();

	CRHMLogger::instance()->get_run_logger()->flush();

}


void CRHMmain::CheckBlankModule() {

	MapVar::iterator itVar;
	ClassVar * thisVar;

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		string s = thisVar->name;
	}
}


void  CRHMmain::RunClick(void) {	
	MMSData * mmsdata = CRHMmain::RunClick2Start();
	CRHMmain::RunClick2Middle(mmsdata, Global::DTmin, Global::DTmax);
	CRHMmain::RunClick2End(mmsdata);
}


//---------------------------------------------------------------------------

void CRHMmain::ControlSaveState(bool MainLoop, ClassPar * VarPar)
{
	TStringList *StateList;
	MapVar::iterator itVar;
	ClassVar * thisVar;
	StateList = new TStringList;
	string S;
	bool Needed;

	Global::RunUpBitSet.reset();

	bool Wild = false;
	if (VarPar && !VarPar->Strings->Strings[0].empty()) // first parameter determines the type
		Wild = VarPar->Strings->Strings[0].find("@") == string::npos;

	if (MainLoop)
		StateList->Add("Starting main run-up loop");
	else
		StateList->Add("starting module run-ahead to determine future variables");

	StateList->Add("######");

	StateList->Add("Time:");
	S = FormatString(Global::DTnow, "yyyy m d");
	StateList->Add(S);
	StateList->Add("######");

	StateList->Add("DTindx:");
	StateList->Add(DttoStr(Global::DTindx));
	StateList->Add("######");

	StateList->Add("CurrentModuleRun:");
	StateList->Add(Global::CurrentModuleRun);
	StateList->Add("######");

	StateList->Add("Dimension:");
	StateList->Add(Common::longtoStr(Global::nhru) + " " + Common::longtoStr(Global::nlay));
	StateList->Add("######");

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		Needed = false;

		if (thisVar->varType < TVar::Read && thisVar->StatVar) { // Is state variable!

			if (!thisVar->InGroup || Global::ModuleBitSet->count(thisVar->module))  // All variables in simple projects and module requested group projects
				Needed = true;
			else if (MainLoop) {
				string namebasic = thisVar->name;
				if (VarPar && (VarPar->Strings->IndexOf(namebasic) > -1))
					Needed = true;
				else if (Wild) { // if Wild reduce parameter to root
					string::size_type Idx = namebasic.find("@");
					if (Idx != string::npos) {
						namebasic = namebasic.substr(1, Idx - 1);
						if (VarPar && (VarPar->Strings->IndexOf(namebasic) > -1))
							Needed = true;
					}
				} // wild!
				Global::RunUpBitSet[thisVar->InGroup - 1] = true;
			} // MainLoop!
		} // state variable!

		if (Needed) {
			S = thisVar->module + " " + thisVar->name;
			StateList->Add(S);
			S = "";
			if (thisVar->lay == 0)
				for (int ii = 0; ii < thisVar->dim; ii++) {
					if (thisVar->values != NULL)
						S = S + FloatToStrF(thisVar->values[ii], TFloatFormat::ffGeneral, 7, 0) + " ";
					else if (thisVar->ivalues != NULL)
						S = S + FloatToStrF(thisVar->ivalues[ii], TFloatFormat::ffGeneral, 7, 0) + " ";
					else
						S = S + "-0 ";

					if (ii % 10 == 9) {
						StateList->Add(S);
						S = "";
					}
				}
			else
				for (int ll = 0; ll < thisVar->lay; ll++) {
					for (int ii = 0; ii < thisVar->dim; ii++) {
						if (thisVar->layvalues != NULL)
							S = S + FloatToStrF(thisVar->layvalues[ll][ii], TFloatFormat::ffGeneral, 4, 0) + " ";
						else if (thisVar->ivalues != NULL)
							S = S + FloatToStrF(thisVar->ilayvalues[ll][ii], TFloatFormat::ffGeneral, 4, 0) + " ";
						else
							S = S + "-0 ";

						if (ii % 10 == 9) {
							StateList->Add(S);
							S = "";
						}
					}
					if (!S.empty()) StateList->Add(S);
					S = "";
				}
			if (!S.empty()) StateList->Add(S);
			StateList->Add("######");
		}
	}

	if (MainLoop)
		StateList->SaveToFile(ProjectDirectory + "\\" + "ControlStateFile.tmp1");
	else
		StateList->SaveToFile(ProjectDirectory + "\\" + "ControlStateFile.tmp2");

	delete StateList;
}


void CRHMmain::ReadStateFile(bool & GoodRun)
{
	MapPar::iterator itVar;
	ClassVar *thisVar;

	//  ifstream DataFile;
	std::string module, name, Descrip, Line;
	string S;
	ifstream DataFile(OpenNameState.c_str());
	if (!DataFile) {
		Common::Message("cannot open file", "File Error");
		return;
	}

	getline(DataFile, Descrip);
	DataFile.ignore((numeric_limits<streamsize>::max)(), '#');
	getline(DataFile, Line);

	getline(DataFile, Line); // read "TIME:"
	int D[3]{};
	DataFile >> D[0] >> D[1] >> D[2];
	double DT = StandardConverterUtility::EncodeDateTime(D[0], D[1], D[2], 0, 0); // ????

	getline(DataFile, Descrip);
	DataFile.ignore((numeric_limits<streamsize>::max)(), '#');
	getline(DataFile, Line);

	getline(DataFile, Line); // read "Dimension:"
	long filehru, filelay;
	DataFile >> filehru >> filelay;
	if (filehru != Global::nhru || filelay != Global::nlay) {
		Common::Message("State File and Model #HRU's or #LAY's are not equal", "File Error");
		GoodRun = false;
		return;
	}

	DataFile.ignore((numeric_limits<streamsize>::max)(), '#');
	getline(DataFile, Line);

	while (!DataFile.eof()) {
		DataFile >> module >> name;
		if (DataFile.fail()) break;

		DataFile.ignore();
		S = string(module) + ' ' + string(name);
		thisVar = ClassVarFind(S);

		if (!thisVar) thisVar = ClassVarFind("#" + S);  // could be local variable

		if (thisVar) {
			if (thisVar->lay == 0) {
				for (int ii = 0; ii < thisVar->dim; ii++)
					if (thisVar->values != NULL)
						DataFile >> thisVar->values[ii];
					else if (thisVar->ivalues != NULL)
						DataFile >> thisVar->ivalues[ii];
			}
			else {
				for (int ll = 0; ll < thisVar->lay; ll++)
					for (int ii = 0; ii < thisVar->dim; ii++)
						if (thisVar->layvalues != NULL)
							DataFile >> thisVar->layvalues[ll][ii];
						else  if (thisVar->ivalues != NULL)
							DataFile >> thisVar->ilayvalues[ll][ii];
			}
			DataFile.ignore((numeric_limits<streamsize>::max)(), '#');
			getline(DataFile, Line);
		}
		else {
			Common::Message((string("State File variable ") + S.c_str()).c_str(), "Unknown variable");
			DataFile.ignore((numeric_limits<streamsize>::max)(), '#');
			getline(DataFile, Line);
		}
	}
}

//---------------------------------------------------------------------------

ClassVar *VarFind(string name) {
	MapVar::iterator itVar;

	if ((itVar = Global::MapVars.find(name)) == Global::MapVars.end())
		return NULL;
	else
		return ((*itVar).second);
}
//---------------------------------------------------------------------------

ClassPar *ParFind(string name) { // where name is concatenation of MODULE and NAME
	MapPar::iterator itPar;

	if ((itPar = Global::MapPars.find(name)) == Global::MapPars.end()) {
		return NULL;
	}
	return ((*itPar).second);
}
//---------------------------------------------------------------------------


void  CRHMmain::AllRprt(void)
{
	TStringList *LogList = new TStringList;

	if (this->OutputFormat == OUTPUT_FORMAT::STD) 
	{
		//standard output header
		RprtHeader(LogList, SeriesCnt);
	}
	else if (this->OutputFormat == OUTPUT_FORMAT::OBS)
	{
		//.obs file output header
		RprtHeaderObs(LogList, SeriesCnt);
	}
	else 
	{
		CRHMException e = CRHMException("No output format was specified defaulting to STD.", TExcept::WARNING);
		CRHMLogger::instance()->log_run_error(e);
		//standard output header
		RprtHeader(LogList, SeriesCnt);
	}
	
	string Sx, Sy;

	for (int nn = 0; nn < cdSeries[0]->Count(); ++nn) {

		Sx = FloatToStrF(cdSeries[0]->XValue(nn), TFloatFormat::ffGeneral, 10, 0);
		Sx = StandardConverterUtility::GetDateTimeInStringForOutput(cdSeries[0]->XValue(nn));

		//added this switch statement according to Peter's code.
		switch (Global::TimeFormat) {
		case TIMEFORMAT::MS:
			Sx = FloatToStrF(cdSeries[0]->XValue(nn), TFloatFormat::ffGeneral, 10, 0);
			break;
		case TIMEFORMAT::YYYYMMDD:
			Sx = StandardConverterUtility::FormatDateTime("yyyy-mm-dd hh:mm ", cdSeries[0]->XValue(nn));
			break;
		case TIMEFORMAT::ISO:
			Sx = StandardConverterUtility::FormatDateTime("ISO", cdSeries[0]->XValue(nn));
			break;
		default:
			break;
		}



		for (int vv = 0; vv < SeriesCnt; ++vv) {
			if (cdSeries[0]->Count() == cdSeries[vv]->Count()) { // has to equal first series length
				ClassVar *thisVar = (ClassVar *)cdSeries[vv]->Tag;
				int prec = 7;
				//Manishankar did this, because GCC is showing segmentation fault here. thisVar remains null.
				
				if (thisVar->varType == TVar::Int || thisVar->varType == TVar::ReadI)
					prec = 7;
				
				Sy = FloatToStrF(cdSeries[vv]->YValue(nn), TFloatFormat::ffGeneral, prec, 10);
				Sx = Sx + this->Delimiter + Sy;
			}
		}

		LogList->Add(Sx);
	}

	LogList->SaveToFile(OpenNameReport);

	LogList->Clear();
}
void  CRHMmain::LastRprt(void)
{
	TStringList *LogList = new TStringList;

	RprtHeader(LogList, SeriesCnt);

	string Sx, Sy;

	int nn = cdSeries[0]->Count();

	Sx = FloatToStrF(cdSeries[0]->XValue(nn - 1), TFloatFormat::ffGeneral, 10, 0);
	Sx = StandardConverterUtility::GetDateTimeInStringForOutput(cdSeries[0]->XValue(nn-1));

	//added this switch statement according to Peter's code.
	switch (Global::TimeFormat) {
	case TIMEFORMAT::MS:
		Sx = FloatToStrF(cdSeries[0]->XValue(nn-1), TFloatFormat::ffGeneral, 10, 0);
		break;
	case TIMEFORMAT::YYYYMMDD:
		Sx = StandardConverterUtility::FormatDateTime("yyyy-mm-dd hh:mm ", cdSeries[0]->XValue(nn-1));
		break;
	case TIMEFORMAT::ISO:
		Sx = StandardConverterUtility::FormatDateTime("ISO", cdSeries[0]->XValue(nn));
		break;
	default:
		break;
	}

	for (int vv = 0; vv < SeriesCnt; ++vv) {
		ClassVar *thisVar = (ClassVar *)cdSeries[vv]->Tag;
		int prec = 6;
		if (thisVar->varType == TVar::Int || thisVar->varType == TVar::ReadI)
			prec = 4;

		Sy = FloatToStrF(cdSeries[vv]->YValue(nn - 1), TFloatFormat::ffGeneral, prec, 0);

		Sx = Sx + this->Delimiter + Sy;
	}

	LogList->Add(Sx);

	LogList->SaveToFile(OpenNameReport);
	LogList->Clear();
}




void CRHMmain::DoObsStatus(bool &First)
{
	if (First) {
		for (
			std::list<std::pair<std::string, ClassData*>>::iterator it = ObsFilesList->begin(); 
			it != ObsFilesList->end(); 
			it++
			) 
		{
			ClassData * FileData = it->second;
			FileData->TimeIndx = 0;
		}
		First = false;
	}

	for (
		std::list<std::pair<std::string, ClassData*>>::iterator it = ObsFilesList->begin(); 
		it != ObsFilesList->end(); 
		it++
		) 
	{
		ClassData * FileData = it->second;

		FileData->GoodInterval = true;

		// first observation file always good
		if (it == ObsFilesList->begin())  
		{  
			FileData->GoodDay = true;
			continue;
		}

		FileData->GoodInterval = true;

		// sparse data
		if (FileData->Times != NULL) 
		{ 
			FileData->GoodDay = false;

			while (FileData->Times[FileData->TimeIndx] < Global::DTnow
				&& FileData->TimeIndx < FileData->Lines - 1)
				++FileData->TimeIndx;

			if (FileData->Times[FileData->TimeIndx] != Global::DTnow)
				FileData->GoodInterval = false;
		}
		else { // normal observation file

			if (FileData->ModN == 0)
			{
				CRHMException e = CRHMException("Observation files are in a incompatible order. "
					"Make sure the first observation file has the shorter interval.", TExcept::TERMINATE);
				LogError(e);
			}

			long Index = Global::DTindx / FileData->ModN;

			if (Index < FileData->IndxMin || Index > FileData->IndxMax) {
				FileData->GoodInterval = false;
				FileData->GoodDay = false;
				continue;
			}

			if (Index%FileData->Freq == 0) { // beginning of day
				FileData->GoodDay = true;
				if (FileData->Freq <= 1) continue; // handle daily data
				Index += FileData->Freq / FileData->ModN - 1; // add day
				if (Index < FileData->IndxMin || Index > FileData->IndxMax) {
					FileData->GoodDay = false;
					continue;
				}
				continue;
			}
			else {
				if (FileData->GoodDay)
					FileData->GoodInterval = true;
				else if (Index < FileData->IndxMin || Index > FileData->IndxMax)
					// day at end of file missing data
					FileData->GoodInterval = false;
			}
		}
	} // for
}


void CRHMmain::ResetLoopList(void) { // writes to "CRHM_loop_output" and cleans up

	if (LoopList == NULL)
		return;

	ClassPar *thisPar = ParFind("basin RUN_ID");

	long ID = 0;

	if (!thisPar) {
		MapPar::iterator itPar;

		for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
			thisPar = (*itPar).second;
			if (thisPar->param == "RUN_ID" && thisPar->ivalues[0] > 0) {
				ID = thisPar->ivalues[0];
				break;
			}
		}
	}
	else
		ID = thisPar->ivalues[0];

	string FileName = "CRHM_loop_output";
	if (ID > 0)
	{
		FileName += string("_"); //??? + ID;
	}
		
	ofstream file(ProjectDirectory + "\\" + FileName + ".txt");
	
	if (file)
	{
		for (
			std::list<std::string>::iterator it = LoopList->begin();
			it != LoopList->end();
			it++
			)
		{
			file << it->c_str() << endl;
		}

		file.close();
	}
	else
	{
		CRHMException e = CRHMException("Cannot open file to write out loop list."+ ProjectDirectory + "\\" + FileName + ".txt", TExcept::ERR);
		CRHMLogger::instance()->log_run_error(e);
	}

	delete LoopList;
	LoopList = NULL;
}


void  CRHMmain::ControlReadState(bool MainLoop, ClassPar * VarPar) {

	MapPar::iterator itVar;
	ClassVar *thisVar;

	string Sy;
	string Sx;
	bool first = true;
	bool Wild = false;

	if (VarPar && !VarPar->Strings->Strings[0].empty()) // first parameter determines the type
		Wild = VarPar->Strings->Strings[0].find("@") == string::npos;

	ifstream DataFile;

	char module[80], name[80];
	string S, Descrip, Line;
	if (MainLoop)
		DataFile.open((ProjectDirectory + "\\" + "ControlStateFile.tmp1").c_str());
	else
		DataFile.open((ProjectDirectory + "\\" + "ControlStateFile.tmp2").c_str());

	if (!DataFile) {
		Common::Message("cannot open file", "File Error");
		return;
	}

	getline(DataFile, Descrip);
	DataFile.ignore(180, '#');
	getline(DataFile, Line);

	getline(DataFile, Line); // read "TIME:"
	int D[3]{};
	DataFile >> D[0] >> D[1] >> D[2];

	DataFile.ignore(180, '#'); // not working?
	getline(DataFile, Line); // reads "#####"
	getline(DataFile, Line); // read "DTindx:"
	DataFile >> Global::DTindx;

	DataFile.ignore(180, '#'); // not working?
	getline(DataFile, Line); // reads "#####"
	getline(DataFile, Line); // read "CurrentModuleRun:"
	DataFile >> Global::CurrentModuleRun;

	getline(DataFile, Descrip);
	DataFile.ignore(180, '#');
	getline(DataFile, Line);

	getline(DataFile, Line); // read "Dimension:"
	long filehru, filelay;
	DataFile >> filehru >> filelay;

	DataFile.ignore(180, '#');
	getline(DataFile, Line);

	while (!DataFile.eof()) {
		DataFile >> module >> name;
		if (DataFile.fail()) break;

		DataFile.ignore();

		std::list<std::pair<std::string, ClassModule*>>::iterator pos;
		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
			it != Global::OurModulesList->end();
			it++
			)
		{
			if (it->first == module)
			{
				pos = it;
			}
		}

		ClassModule*  mod;
		if (pos != Global::OurModulesList->end())
		{
			mod = pos->second;
		}
		else 
		{
			Common::Message((string("State File module ") + module), "Unknown module");
			DataFile.ignore(180, '#');
			getline(DataFile, Line);
			continue;
		}

		S = string(module) + ' ' + string(name);
		thisVar = ClassVarFind(S);

		if (!thisVar)
			thisVar = ClassVarFind("#" + S);  // could be local variable

		if (!thisVar && mod->isGroup) {
			string::size_type idx = S.find('@');
			if (idx == string::npos) {
				string A;
				Common::GroupEnding(A, mod->GroupCnt);
				S += A;
				thisVar = ClassVarFind(S);
			}
		}

		string namebasic = name;
		if (Wild) { // if Wild reduce parameter to root
			string::size_type Idx = namebasic.find("@");
			if (Idx != string::npos)
				namebasic = namebasic.substr(1, Idx - 1);
		}

		if (thisVar) {

			if (VarPar && VarPar->Strings->IndexOf(namebasic) > -1) {
				if (LoopList == NULL) {
					LoopList = new std::list<std::string>();
					Sx = DttoStr(Global::DTnow);
					LoopList->push_back(Sx);
				}
				if (first) {
					Sx = "loop " + inttoStr(Global::LoopCnt - Global::LoopCntDown + 1) + "\t" + name;
					first = false;
				}
				else
					Sx += ("\t" + string(name));

				// write data

				Sy = "";
				if (thisVar->lay == 0) {
					for (int ii = 0; ii < thisVar->dim; ii++)
						if (thisVar->values != NULL) {
							Sy += FloatToStrF(thisVar->values[ii], TFloatFormat::ffGeneral, 4, 0) + " ";
						}
						else if (thisVar->ivalues != NULL) {
							Sy += FloatToStrF(thisVar->ivalues[ii], TFloatFormat::ffFixed, 0, 0) + " ";
						}
				}
				else {
					for (int ll = 0; ll < thisVar->lay; ll++)
						for (int ii = 0; ii < thisVar->dim; ii++)
							if (thisVar->layvalues != NULL) {
								Sy += FloatToStrF(thisVar->layvalues[ll][ii], TFloatFormat::ffGeneral, 4, 0) + " ";
							}
							else  if (thisVar->ivalues != NULL) {
								Sy += FloatToStrF(thisVar->ilayvalues[ll][ii], TFloatFormat::ffGeneral, 0, 0) + " ";
							}
				}

				Sx = Sx + "\t" + Sy;
			}
			else {
				if (thisVar->lay == 0) {
					for (int ii = 0; ii < thisVar->dim; ii++)
						if (thisVar->values != NULL)
							DataFile >> thisVar->values[ii];
						else if (thisVar->ivalues != NULL)
							DataFile >> thisVar->ivalues[ii];
				}
				else {
					for (int ll = 0; ll < thisVar->lay; ll++)
						for (int ii = 0; ii < thisVar->dim; ii++)
							if (thisVar->layvalues != NULL)
								DataFile >> thisVar->layvalues[ll][ii];
							else  if (thisVar->ivalues != NULL)
								DataFile >> thisVar->ilayvalues[ll][ii];
				}
			}

			DataFile.ignore(180, '#');
			getline(DataFile, Line);
		}
		else {
			Common::Message((string("State File variable ") + S), "Unknown variable");
			DataFile.ignore(180, '#');
			getline(DataFile, Line);
		}

	} // while

	if (MainLoop) {
		bool Wild2 = false;
		ClassPar * TraceVarPar = ParFind("basin TraceVars");

		if (TraceVarPar && !TraceVarPar->Strings->Strings[0].empty()) // first parameter determines the type
			Wild2 = TraceVarPar->Strings->Strings[0].find("@") == string::npos;

		for (int ii = 0; ii < TraceVarPar->Strings->Count; ++ii) {
			string Trimmed = Common::trim(TraceVarPar->Strings->Strings[ii]);
			if (!Trimmed.empty()) {

				if (AllVariables->count(Trimmed)) 
				{
					for (
						std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
						modIt  != Global::OurModulesList->end(); 
						modIt++
						) 
					{
						ClassVar * thisVar = VarFind(string(modIt->first) + ' ' + TraceVarPar->Strings->Strings[0]);
						if (thisVar) 
						{
							break;
						}
					} // for

					thisVar = AllVariables->find(Trimmed)->second;
					if (thisVar) {
						Sx += ("\t" + string(Trimmed));
						Sy = "";
						if (thisVar->lay == 0) {
							for (int ii = 0; ii < thisVar->dim; ii++)
								if (thisVar->values != NULL) {
									Sy += FloatToStrF(thisVar->values[ii], TFloatFormat::ffGeneral, 4, 0) + " ";
								}
								else if (thisVar->ivalues != NULL) {
									Sy += FloatToStrF(thisVar->ivalues[ii], TFloatFormat::ffFixed, 0, 0) + " ";
								}
						}
						else {
							for (int ll = 0; ll < thisVar->lay; ll++)
								for (int ii = 0; ii < thisVar->dim; ii++)
									if (thisVar->layvalues != NULL) {
										Sy += FloatToStrF(thisVar->layvalues[ll][ii], TFloatFormat::ffGeneral, 4, 0) + " ";
									}
									else  if (thisVar->ivalues != NULL) {
										Sy += FloatToStrF(thisVar->ilayvalues[ll][ii], TFloatFormat::ffGeneral, 0, 0) + " ";
									}
						}

						Sx = Sx + "\t" + Sy;
					}
				} // if
			}
		}
	}

	if (!Sx.empty())
	{
		LoopList->push_back(Sx);
	}
		
}


//---------------------------------------------------------------------------



std::map<std::string, ClassVar *> * CRHMmain::getObservations()
{
	return AllObservations;
}


std::map<std::string, ClassModule*> * CRHMmain::getAllmodules()
{
	return Global::AllModulesList;
}


std::map<std::string, ClassVar*> * CRHMmain::getVariables()
{
	return this->AllVariables;
}

void CRHMmain::calculateOutputFileName()
{
	if (this->OutputName == "")
	{
		ClassPar* thisPar;
		thisPar = ParFind("basin RUN_ID");

		long ID = 0;

		std::string ext;

		if (this->OutputFormat == OUTPUT_FORMAT::STD)
		{
			ext = ".txt";
		}
		else
		{
			ext = ".obs";
		}

		if (!thisPar) {
			MapPar::iterator itPar;

			for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
				thisPar = (*itPar).second;
				if (thisPar->param == "RUN_ID") {
					ID = thisPar->ivalues[0];
					break;
				}
			}
		}
		else
			ID = thisPar->ivalues[0];

		OpenNameReport = ProjectDirectory + "/CRHM_output"; //manishankar updated this line to make it suitable for both windows and linux.s
		if (ID >= 0) {
			if (ID > 0) {
				OpenNameReport += "_";
				OpenNameReport += inttoStr(ID);
			}
			OpenNameReport += ext;
		}
		else if (ID < 0) {
			ID = -ID;
			OpenNameReport = OpenNamePrj.substr(0, OpenNamePrj.length() - 4) + "_" + Common::longtoStr(ID) + ext;
		}
	}
	else
	{
		OpenNameReport = this->OutputName;
	}
	
}


void CRHMmain::RprtHeader(TStringList *LogList, int LocalCnt)
{

	string Sx, Sy;

	calculateOutputFileName();

	Sx = "time";
	for (int vv = 0; vv < LocalCnt; ++vv) {
		string S = cdSeries[vv]->Title;
		Sx += this->Delimiter + S;
	}
	LogList->Add(Sx);

	Sx = "units";
	for (int vv = 0; vv < LocalCnt; ++vv) {
		ClassVar* thisVar = (ClassVar*)cdSeries[vv]->Tag;
		string S = thisVar->units;
		Sx += this->Delimiter + S;
	}
	LogList->Add(Sx);
}

void CRHMmain::RprtHeaderObs(TStringList* LogList, int LocalCnt)
{

	string Sx, Sy;

	calculateOutputFileName();

	LogList->Add("Future File Description");
	
	for (int vv = 0; vv < LocalCnt; ++vv) {
		ClassVar *thisVar = (ClassVar *)cdSeries[vv]->Tag;
		Sx = cdSeries[vv]->Title;
		Sx += string(" 1 ");
		Sx += thisVar->units;
		LogList->Add(Sx);
	}
	
	Sx = "###### time";
	for (int vv = 0; vv < LocalCnt; ++vv) {
		string S = cdSeries[vv]->Title;
		Sx += this->Delimiter + S;
	}
	LogList->Add(Sx);
}

string CRHMmain::DttoStr(double D) {
	ostringstream temp;
	temp << D;
	return temp.str();
}

string CRHMmain::inttoStr(int I) {
	ostringstream temp;
	temp << I;
	return temp.str();
}

void  CRHMmain::LogMessageX(const char *S)
{
	CRHMLogger::instance()->log_to_console(S);
	CRHMLogger::instance()->log_run_message(S);
}


string CRHMmain::GetCaptionFromAboutBox()
{
#if defined(VS_GUI)
	CRHMAboutBox aboutbox;
	return aboutbox.versionstring;
#endif
#if defined(COMMAND_LINE)
	return "";
#endif
}



void  CRHMmain::SaveProject(string prj_description, string filepath) {
	MapPar::iterator itPar;
	MapDim::iterator itDim;
	ClassPar *thisPar;
	ClassVar *lastVar = NULL;
	string Output;
	int Y = 0, M = 0, D = 0, H = 0, Min = 0;
	ProjectList->push_back(prj_description);
	double Dt = StandardConverterUtility::GetCurrentDateTime();
	string datetime = StandardConverterUtility::GetDateTimeInString(Dt);
	//Common::DecodeDateTime(DT, &Y, &M, &D, &H, &Min);
	//string datest = D +" " + M  + Y + H + Min;
	string S("  Creation: " + datetime);

	string caption = GetCaptionFromAboutBox(); // AboutBox->Label2->Caption
	ProjectList->push_back("###### " + caption + S);


	bool Prj = false;
	if (filepath.find(".prj") != std::string::npos) { Prj = true; }

	if (Prj) {

		//need to modify
		//Main->Text = Main->Text.SubString(1, 49) + " - " + SaveDialogPrj->FileName;

		ProjectList->push_back("Dimensions:");
		ProjectList->push_back("######");
		ProjectList->push_back(string("nhru " + to_string(Global::maxhru)));
		ProjectList->push_back(string("nlay " + to_string(Global::nlay)));
		ProjectList->push_back(string("nobs " + to_string(Global::nobs)));
		ProjectList->push_back("######");

		ProjectList->push_back("Macros:");
		ProjectList->push_back("######");

		for (int ii = 0; ii < Global::MacroModulesList->size(); ++ii)
		{
			ProjectList->push_back("'" + Global::MacroModulesList->operator[](ii) + "'");
		}
			

		ProjectList->push_back("######");

		if (!Global::MapAKA.empty()) {
			Mapstr2::iterator it;

			ProjectList->push_back("AKAs:");
			ProjectList->push_back("######");

			for (it = Global::MapAKA.begin(); it != Global::MapAKA.end(); ++it) {
				string Var = (*it).first + ' ' + (*it).second;
				ProjectList->push_back(Var.c_str());
			}
			ProjectList->push_back("######");
		}

		ProjectList->push_back("Observations:");
		ProjectList->push_back("######");
		for (
			std::list<std::pair<std::string, ClassData*>>::iterator it = ObsFilesList->begin(); 
			it != ObsFilesList->end(); 
			it++
			) 
		{
			string S = it->first;
			ProjectList->push_back(S);
		}
		ProjectList->push_back("######");

		ProjectList->push_back("Dates:");
		ProjectList->push_back("######");
		string S;


		double date1 = GetStartDate();
		S = StandardConverterUtility::GetDateInString(date1);


		if (ObsFilesList->size() == 0)
		{
			S = S + " " + FloatToStrF(Global::Freq, TFloatFormat::ffGeneral, 0, 0);
		}
		ProjectList->push_back(S);


		double date2 = GetEndDate();
		S = StandardConverterUtility::GetDateInString(date2);


		ProjectList->push_back(S);
		ProjectList->push_back("######");

#ifdef CRHM_DLL
		if (OpenDLLs->Count > 0) {
			ProjectList->push_back("DLLs:");
			ProjectList->push_back("######");
			CompactDlls();
			for (int ii = 0; ii < OpenDLLs->Count; ii++) {
				String S = OpenDLLs->Strings[ii];
				ProjectList->push_back(S);
			}
			ProjectList->push_back("######");
		}
#endif

		ProjectList->push_back("Modules:");
		ProjectList->push_back("######");
		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
			modIt != Global::OurModulesList->end(); 
			modIt++
			) 
		{
			ClassModule* thisModule = modIt->second;
			string S = modIt->first;
			if (thisModule->variation > 0) 
			{
				string AA("#0 ");
				AA[1] += (char) (log(thisModule->variation) / log(2) + 1);
				S = S + AA.c_str();
			}
			else
			{
				S = S + " ";
			}
				
			S = S + thisModule->DLLName + " ";
			S = S + thisModule->Version;
			ProjectList->push_back(S);

			if (thisModule->isGroup || thisModule->isStruct) {
				list<ModulePtr> ::iterator iterM;
				iterM = ((ClassMacro *)thisModule)->Modules.begin();
				while (iterM != ((ClassMacro *)thisModule)->Modules.end()) {
					std::weak_ptr<ClassModule> MP((*iterM));
					string S = string(" +") + (*iterM)->NameRoot.c_str();
					if ((*iterM)->variation > 0) {
						string AA("#0 ");
						AA[1] += (char) (log((*iterM)->variation) / log(2) + 1);
						S = S + AA.c_str();
					}
					else
						S = S + " ";

					S = S + (*iterM)->DLLName + " ";
					S = S + (*iterM)->Version;
					ProjectList->push_back(S);
					++iterM;
				}
			}
		}
		ProjectList->push_back("######");

		ProjectList->push_back("Parameters:");
		ProjectList->push_back("###### 'basin' parameters always first");

		for (int bb = 0; bb < 2; ++bb) { // shared parameters first - initially over-write all others
			for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
				thisPar = (*itPar).second;

				if (thisPar->param == "HRU_group")
					continue;
				if (bb == 0 && thisPar->module != "shared")
					continue;
				if (bb == 1 && thisPar->module == "shared")
					continue;

				string S = string(thisPar->module.c_str()) + " " + string(thisPar->param.c_str());

				if (thisPar->varType != TVar::Txt)
					S += " <" + FloatToStrF(thisPar->minVal, TFloatFormat::ffGeneral, 4, 0) + " to " + FloatToStrF(thisPar->maxVal, TFloatFormat::ffGeneral, 4, 0) + ">";


				ProjectList->push_back(S);

				for (int jj = 0; jj<thisPar->lay; jj++) {
					S = "";
					for (int ii = 0; ii < thisPar->dim; ii++) {
						if (thisPar->varType == TVar::Float)
						{
							S = S + FloatToStrF(thisPar->layvalues[jj][ii], TFloatFormat::ffGeneral, 4, 0) + " ";
						}
						else if (thisPar->varType == TVar::Int)
						{
							S = S + FloatToStrF(thisPar->ilayvalues[jj][ii], TFloatFormat::ffFixed, 8, 0) + " ";
						}
						else if (thisPar->varType == TVar::Txt)
						{
							if (thisPar->Strings->Count > ii)
							{
								S = S + "'" + thisPar->Strings->Strings[ii] + "' ";
							}
							else
							{
								S = "''"; // handle null string
							}
						}

						if (ii % 16 == 15) {
							ProjectList->push_back(S);
							S = "";
						}
					}

					//if (!S.IsEmpty()) { ProjectList->Add(S); S = ""; }
					if (S.length() != 0) { ProjectList->push_back(S); S = ""; }
				}

				//if (!S.IsEmpty()) ProjectList->Add(S);
				if (S.length() != 0) ProjectList->push_back(S);
			} // output loop
		}  // basin module/other loop

		ProjectList->push_back("######");

		ProjectList->push_back("Initial_State");
		ProjectList->push_back("######");


		//need to modify
		//TMenuItem *StateItem;
		//StateItem = MainMenu1->Items->Items[5];

		//if (StateItem->Count > 5) { // State files open
		//	for (int ii = 5; ii < StateItem->Count; ++ii)
		//		ProjectList->Add(StateItem->Items[ii]->Caption);
		//}

		ProjectList->push_back("######");

		ProjectList->push_back("Final_State");
		ProjectList->push_back("######");
		if (SaveStateFlag) {
			ProjectList->push_back(SaveStateFileName);
		}
		ProjectList->push_back("######");
	}

	//ProjectList->Add("Summary_period");
	//ProjectList->Add("######");
	//need to modify
	//string T = TBases[TBase];
	//if (TBase == 1)
	//	T = T + " " + string(water_year_month);
	//ProjectList->Add(T);
	//ProjectList->Add("######");

	//ProjectList->Add("Log_Time_Format");
	//ProjectList->Add("######");

	//need to modify
	//T = TLogFormats[Global::TimeFormat];
	//ProjectList->Add(T);

	//ProjectList->Add("######");

	if (Global::LOGVARLOAD) {
		ProjectList->push_back("LOGVARLOAD");
		ProjectList->push_back("######");
	}

	ProjectList->push_back("Display_Variable:");
	ProjectList->push_back("######");

	for (int ii = 0; ii < SeriesCnt; ii++) { // transfer TeeChart data

											 //ClassVar *thisVar = (ClassVar *)cdSeries[ii]->Tag;

											 //need to modify
											 //thisVar->TchrtOpt = cdSeries[ii]->VertAxis == aRightAxis;
											 //thisVar->TchrtOpt = 0;
	}

	lastVar = NULL;
	Output = "";


	//need to modify
	//if (HruNames)
	//HruNameClick(Sender);


	for (
		std::list<std::pair<std::string, ClassVar*>>::iterator selectedVariablesIt = SelectedVariables->begin();
		selectedVariablesIt != SelectedVariables->end();
		selectedVariablesIt++
		) 
	{

		long lay, dim;

		ExtractHruLay(selectedVariablesIt->first, dim, lay);

		//need to modify possibly
		ClassVar *thisVar = selectedVariablesIt->second; 
		//previous code
		//ClassVar *thisVar = (ClassVar *)ii; //Manishankar's code
		//thisVar->TchrtOpt = 1; //added by Manishankar

		if (thisVar != NULL)
		{
			if (thisVar->TchrtOpt)
				dim = -dim;

			string SS = to_string(dim);
			if (thisVar->lay > 0) SS += "," + to_string(lay);

			string Mod = thisVar->module;

			if (lastVar == NULL)
				Output = (Mod + " " + thisVar->name + " ").c_str() + SS;
			else if (lastVar != thisVar) {
				ProjectList->push_back(Output);
				Output = (Mod + " " + thisVar->name + " ").c_str() + SS;
			}
			else
				Output += " " + SS;

			lastVar = thisVar;
		}
	}

	//if (!Output.IsEmpty()) ProjectList->Add(Output);
	if (Output.length() != 0) ProjectList->push_back(Output);

	ProjectList->push_back("######");

	ProjectList->push_back("Display_Observation:");
	ProjectList->push_back("######");

	lastVar = NULL;
	string kind, lastkind;
	Output = "";

	for (
		std::list<std::pair<std::string, TSeries*>>::iterator it = SelectedObservations->begin();
		it != SelectedObservations->end();
		it++) 
	{

		string S = it->first;
		string FullName;
		long dim = 0, lay = 0;
		kind = "_obs";


		//need to modify
		//string Name = ExtractHruLayFunct(SelectedObservations->Strings[ii], dim, lay, kind, FullName);
		string Name = GetObservationName(it->first);
		ExtractHruLay(it->first, dim, lay);
		//string Name = "";


		//need to modify
		//TLineSeries *cdSeries = (TLineSeries *)SelectedObservations->Objects[ii];
		TSeries *cdSeries =it->second;

		ClassVar *thisVar;
		thisVar = NULL;

		//need to modify
		thisVar = (ClassVar *)cdSeries->Tag; // always OK for observation

		//thisVar = it->second; //added by Manishankar for testing.
													 //Name = SelectedObservations->Strings[ii];


		if (!thisVar || !thisVar->FileData) {  // VarObsFunct
			if (!thisVar) {

				std::list<std::pair<std::string, ClassVar*>>::iterator pos;
				for (
					std::list<std::pair<std::string, ClassVar*>>::iterator it = SelectedVariables->begin();
					it != SelectedVariables->end() || it->first != FullName;
					it++
					)
				{
					pos = it;
				}

				if (pos != SelectedVariables->end())
				{
					thisVar = pos->second;
				}
				else
				{
					thisVar = VarFind(string(string("obs ") + Name.c_str()));
				}
			}
		}

		//need to modify
		//if (cdSeries->VertAxis == aRightAxis)
		//dim = -dim;

		string SS = to_string(dim);

		if (lay > 0)
			SS += "," + to_string(lay);

		if (Output != "" && (thisVar != lastVar || kind != lastkind)) {
			ProjectList->push_back(Output + " " + lastkind);
			if (thisVar)
				Output = (thisVar->module + " " + Name.c_str() + " " + SS.c_str()).c_str();
			else // fudge for obs _Avg thru _Tot being null for observations
				Output = (string("obs ") + Name.c_str() + " " + SS.c_str()).c_str();
		}
		else if (lastVar) // add to earlier output
			Output += " " + SS;
		else // first output
		{
			if (thisVar != NULL)
			{
				Output = (thisVar->module + " " + Name.c_str() + " " + SS.c_str()).c_str();
			}
		}

		lastVar = thisVar;
		lastkind = kind;



		//this is just like populating ListBox3.

		//long lay, dim;

		//ExtractHruLay(SelectedObservations->Strings[ii], dim, lay);

		////need to modify possibly
		//ClassVar *thisVar = (ClassVar *)SelectedObservations->Objects[ii]; //previous code
		//													   //ClassVar *thisVar = (ClassVar *)ii; //Manishankar's code
		//if (thisVar != NULL)
		//{
		//	if (thisVar->TchrtOpt)
		//		dim = -dim;

		//	string SS = to_string(dim);
		//	if (thisVar->lay > 0) SS += "," + to_string(lay);

		//	string Mod = thisVar->module;

		//	if (lastVar == NULL)
		//		Output = (Mod + " " + thisVar->name + " ").c_str() + SS;
		//	else if (lastVar != thisVar) {
		//		ProjectList->Add(Output);
		//		Output = (Mod + " " + thisVar->name + " ").c_str() + SS;
		//	}
		//	else
		//		Output += " " + SS;

		//	lastVar = thisVar;
		//}





	}


	if (Output.length() != 0) ProjectList->push_back(Output + " " + kind); // handle last output

	ProjectList->push_back("######");


	//need to check
	//if (PrjAutoRun->Checked) {
	//	ProjectList->Add("Auto_Run");
	//	ProjectList->Add("######");
	//}

	//if (SaveChartTemplate->Checked) {
	//	ProjectList->Add("SaveChartTemplate");
	//	ProjectList->Add("######");
	//	String FileName = ChangeFileExt(SaveDialogPrj->FileName, ".Tee");
	//	Chart->RemoveAllSeries();
	//	SaveChartToFile(Chart, FileName, false, true);
	//}
	//
	//if (PrjAutoExit->Checked) {
	//	ProjectList->Add("Auto_Exit");
	//	ProjectList->Add("######");
	//}
	//
	//if (Last1->Checked) {
	//	ProjectList->Add("Log_Last");
	//	ProjectList->Add("######");
	//}
	//
	//if (All1->Checked) {
	//	ProjectList->Add("Log_All");
	//	ProjectList->Add("######");
	//}
	//
	//if (DebugScreen1->Checked) {
	//	ProjectList->Add("Log_Screen");
	//	ProjectList->Add("######");
	//}
	//
	//if (SummaryScreen1->Checked) {
	//	ProjectList->Add("Summary_Screen");
	//	ProjectList->Add("######");
	//}

	ProjectList->push_back("TChart:");
	ProjectList->push_back("######");


	//need to check
	//for (int ii = 0; ii < Chart->Title->Text->Count; ++ii)
	//	ProjectList->Add(Chart->Title->Text->Strings[ii]);
	//ProjectList->Add(" ");
	//
	//for (int ii = 0; ii < Chart->SubTitle->Text->Count; ++ii)
	//	ProjectList->Add(Chart->SubTitle->Text->Strings[ii]);
	//ProjectList->Add(" ");
	//
	//ProjectList->Add(Chart->Axes->Items[2]->Title->Caption);
	//ProjectList->Add(" ");
	//
	//for (int ii = 0; ii < Chart->Foot->Text->Count; ++ii)
	//	ProjectList->Add(Chart->Foot->Text->Strings[ii]);
	//ProjectList->Add(" ");
	//
	//for (int ii = 0; ii < Chart->SubFoot->Text->Count; ++ii)
	//	ProjectList->Add(Chart->SubFoot->Text->Strings[ii]);
	//ProjectList->Add(" ");
	//
	//if (Chart->MaxPointsPerPage != 0) {
	//	string S = string(Chart->MaxPointsPerPage) + " " + string(Chart->Page);
	//	ProjectList->Add(S);
	//}
	ProjectList->push_back("######");


	//need to check
	//ProjectList->SaveToFile(SaveDialogPrj->FileName);

	ofstream file(filepath.c_str()) ;

	if (file)
	{
		for (
			std::list<std::string>::iterator it = ProjectList->begin();
			it != ProjectList->end();
			it++
			)
		{
			file << it->c_str() << endl;
		}

		file.close();
	}
	else
	{
		CRHMException e = CRHMException("Cannot open file at "+filepath+ " to save project file.", TExcept::ERR);
		CRHMLogger::instance()->log_run_error(e);
	}

	ProjectList->clear();


	//need to check
	//dirty = false;




}


string CRHMmain::GetObservationName(string vname)
{

	int pos = vname.find_first_of('(');

	std::string name = vname.substr(0,pos);

	std::map<std::string,ClassVar*>::iterator it = AllObservations->find(name);

	if (it != AllObservations->end())
	{
		return it->first;
	}
	else
	{
		return "";
	}
}

string  CRHMmain::ExtractHruLayFunct(string S, long &Hru, long &Lay, string &Funct, string &FullName) {

	long jj = S.rfind("(");
	long jj1 = S.find(",");
	long jj2 = S.rfind(")");
	long jj3 = S.rfind("_");
	long jj4 = S.rfind(")");

	Lay = 0;
	if (jj1 != 0)
		Lay = stoi(S.substr(jj1 + 1, jj2 - jj1 - 1));
	else
		jj1 = jj2;

	if (!HruNames) {
		Hru = stoi(S.substr(jj + 1, jj1 - jj - 1));
		if (jj3 > jj2) // if not '_' in variable name
			Funct = S.substr(jj4 + 1, S.length());
	}
	else {

		string sub = S.substr(jj + 1, jj1 - jj - 1);
		bool found = false;
		for (size_t i = 0; i < ListHruNames->size(); i++)
		{
			if (ListHruNames->operator[](i) == sub) 
			{
				Hru = i;
				found = true;
			}
		}

		if (found == false) 
		{
			Hru = -1;
		}
		
		if (Hru == -1) // detects observations - still numeric index value
		{
			Hru = stoi(S.substr(jj + 1, jj1 - jj - 1));
		}
		else
		{
			if (Hru == 0)
			{
				++Hru;
			}
		}
			
	}

	FullName = S.substr(1, jj2); // return name and bracket
	return S.substr(1, jj - 1); // return name
							//return S; //added by Manishankar temporarily
}



void CRHMmain::ClearModules(bool All) {

	ModVarRemove(Global::MapVars);

	Global::SharedMapPars.clear();

	if (All)
	{
		for (
			std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
			modIt != Global::OurModulesList->end();
			modIt++
			)
		{
			modIt->second->reset();
		}
	}
		

	Global::OurModulesList->clear();

	if (All) {
		AdminMacro.MacroClear();

		Global::MacroModulesList->clear();

		//OpenDialogPrj->FileName = "";
		//SaveDialogPrj->FileName = "";
	}

	AllVariables->clear();
	SelectedVariables->clear();

	if (cdSeries) {
		//for (int ii = 0; ii < SeriesCnt; ii++)
		//cdSeries[ii]->ParentChart = NULL;

		//delete cdSeries;           // remove TLineSeries
		//Do not fully delete cdSeries so that a null pointer exception does not occur - Matt
		cdSeries = NULL;
		SeriesCnt = 0; // ??? ListBox3->Items->Count;
	}
	//Chart->Refresh();

	Global::BuildFlag = TBuild::BUILD;

	Global::MapAKA.clear(); // remove all AKA
}


void CRHMmain::GetObservationNames(char* obsfilepath)
{
	FILE * obfile = fopen(obsfilepath, "r");

	char line[128];
	char obsname[128]{};
	//char * token; variable is unreferenced commenting out for now - jhs507
	char obsnames[50][128]{};
	int obsindex = 0;
	int j = 0;

	char* readErrorIndicator;

	readErrorIndicator = fgets(line, sizeof line, obfile); //reading the first line. discarding because first line is not an obsname

	if (readErrorIndicator == NULL) 
	{
		CRHMException e = CRHMException("Error reading and discarding the first line of an obsfile.", TExcept::TERMINATE);
		CRHMLogger::instance()->log_run_error(e);
	}

	while (fgets(line, sizeof line, obfile) != NULL) //read a line, end loop if end of file is reached
	{
		//Reset obsname variable
		obsname[0] = '\0';

		//Exit once we reach the division between observation names and data
		if (line[0] == '#')
		{
			break;
		}

		//copy the read line character by character into obsname until a space is reached 
		for (unsigned int i = 0; i < strlen(line); i++)
		{
			obsname[i] = line[i];
			if (line[i] == ' ')
			{
				obsname[i] = '\0'; //end the obsname with a null byte
				strcpy(obsnames[j], obsname); //copy the observation name into the array of observation names
				break;
			}
		}

		//loop over the previous observation names to see if the current obsname matches 
		//a previously recorded observation name with a '$' prepended to it indicating a derived observation 
		//If this is found decriment j which has the effect of discarding the current obsname 
		for (int i = 0; i < j; i++)
		{
			char test[128]{};
			test[0] = '$'; 
			test[1] = '\0';
			
			strcat(test, obsnames[i]);

			if (strcmp(obsname, test) == 0)
			{
				j--;
				break;
			}
		}

		j++;
	}
	fclose(obfile);


	//writing data to file.
	FILE * fp = fopen("datatransfer.txt", "w");
	for (int i = 0; i < j; i++)
	{
		fputs(strcat(obsnames[i], "\n"), fp);
	}
	fclose(fp);
}



void CRHMmain::GetObservationData(char * obsfilepath, char * observationname)
{
	int length = strlen(observationname);
	if (observationname[length - 1] == '\n') 
	{ 
		observationname[length - 1] = '\0'; 
	}

	FILE * obfile = fopen(obsfilepath, "r");

	char line[128];
	char obsname[128]{};
	char* token, obsnames[50][128]{};
	int obsindex = 0;
	int j = 0;

	char* readErrorIndicator;

	readErrorIndicator = fgets(line, sizeof line, obfile); //reading the first line which gets discarded as the first line in the obsfile is a description 

	if (readErrorIndicator == NULL)
	{
		CRHMException e = CRHMException("Error reading and discarding the first line of an obsfile.", TExcept::TERMINATE);
		CRHMLogger::instance()->log_run_error(e);
	}

	while (fgets(line, sizeof line, obfile) != NULL) //reading lines from the file until the end of file is reached
	{

		//Reset obsname variable
		obsname[0] = '\0';

		//End the loop if the line begins with '#' which indicates the break between obsnames and data
		if (line[0] == '#') 
		{ 
			break; 
		}

		//Loop along the line unntil a space character is reached 
		for (unsigned int i = 0; i < strlen(line); i++)
		{
			obsname[i] = line[i];
			if (line[i] == ' ')
			{
				obsname[i] = '\0'; //end the obsname with a null byte 
				strcpy(obsnames[j], obsname); //copy the new obsname into the obsname array. 
				break;
			}
		}

		//if the current obsname matches the requested observation name set obsindex
		if (strcmp(obsname, observationname) == 0) 
		{ 
			obsindex = j + 1; 
		}
		
		//loop over the previous observation names to see if the current obsname matches 
		//a previously recorded observation name with a '$' prepended to it indicating a derived observation 
		//If this is found decriment j which has the effect of discarding the current obsname 
		for (int i = 0; i < j; i++)
		{
			char test[128]{};
			test[0] = '$'; 
			test[1] = '\0';

			strcat(test, obsnames[i]);
			if (strcmp(obsname, test) == 0)
			{
				j--;
				break;
			}
		}

		j++;
	}

	observationseries = new TSeries(50000);
	observationseries->Title = observationname;

	int obscount = j;
	char tokens[50][50]{};
	int tokencount = 0;
	double obsvalue = 0.0;
	int dateelements = 0, year, month, day, hour;
	//int minute; variable is unreferenced commenting out for now - jhs507
	//int second; variable is unreferenced commenting out for now - jhs507
	double ddate;


	while (fgets(line, sizeof line, obfile) != NULL) //reading the data values.
	{
		tokencount = 0;
		token = strtok(line, " \t");
		while (token != NULL)
		{
			strcpy(tokens[tokencount], token);
			tokencount++;
			token = strtok(NULL, " \t");
		}

		if ((tokencount - obscount + obsindex - 1) > 0 )
		{
			obsvalue = atof(tokens[tokencount - obscount + obsindex - 1]);
		}
		else 
		{
			CRHMException Except("Reading an obs file attempted to read before the begining of an array", TExcept::TERMINATE);
		}

		

		dateelements = tokencount - obscount;
		if (dateelements == 1) { ddate = atof(tokens[0]); }
		else
		{
			year = atoi(tokens[0]); month = atoi(tokens[1]); day = atoi(tokens[2]); hour = atoi(tokens[3]);
			ddate = StandardConverterUtility::GetDateTimeInDouble(year, month, day, hour, 0, 0);
		}

		observationseries->AddXY(ddate, obsvalue);
	}

}

/*
* Returns passed in string with hru identifier appended
*
* hru identifer is numeric if CRHMmain::HruNames is false 
* if CRHMmain HruNames is true the identifier is looked up in
* CRHMmaim::ListHruNames
* 
* @param S string - string to append hru identifer to
* @param Hru long - numerical identifier of Hru
* @param dimen TDim - demension type of passed in variable
* @return string - S with identifier appended within ()
*/
string CRHMmain::BuildHru(string S, long Hru, TDim dimen) {

	if (!HruNames)
	{
		return S + "(" + to_string(Hru) + ")";
	}
	else 
	{


		string SS;
		if (dimen == TDim::BASIN)
		{
			SS = "(" + ListHruNames->front() + ")";
		}	
		else
		{
			SS = "(" + ListHruNames->operator[](Hru) + ")";
		}
		return S + SS;
	}
}
//---------------------------------------------------------------------------

string CRHMmain::BuildLay(string S, long Lay) {

	return S.substr(1, S.length() - 1) + "," + to_string(Lay) + ")";
}

void CRHMmain::SaveState()
{
	TStringList* StateList;
	MapVar::iterator itVar;
	ClassVar* thisVar;
	StateList = new TStringList;
	std::string S;

	StateList->Add("Description of State File - to be added");
	StateList->Add("######");

	StateList->Add("Time:");
	S = FormatString(Global::DTnow, "YMD");
	StateList->Add(S);
	StateList->Add("######");

	StateList->Add("Dimension:");
	StateList->Add(std::to_string(Global::nhru) + " " + std::to_string(Global::nlay));
	StateList->Add("######");

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		if (thisVar->varType < TVar::Read && thisVar->StatVar) {
			S = std::string(thisVar->module.c_str()) + " " +
				std::string(thisVar->name.c_str());
			StateList->Add(S);
			S = "";
			if (thisVar->lay == 0)
				for (int ii = 0; ii < thisVar->dim; ii++) {
					if (thisVar->values != NULL)
						S = S + FloatToStrF(thisVar->values[ii], TFloatFormat::ffGeneral, 4, 0) + " ";
					else if (thisVar->ivalues != NULL)
						S = S + FloatToStrF(thisVar->ivalues[ii], TFloatFormat::ffGeneral, 4, 0) + " ";
					else
						S = S + "-0 ";

					if (ii % 10 == 9) {
						StateList->Add(S);
						S = "";
					}
				}
			else
				for (int ll = 0; ll < thisVar->lay; ll++) {
					for (int ii = 0; ii < thisVar->dim; ii++) {
						if (thisVar->layvalues != NULL)
							S = S + FloatToStrF(thisVar->layvalues[ll][ii], TFloatFormat::ffGeneral, 4, 0) + " ";
						else if (thisVar->ivalues != NULL)
							S = S + FloatToStrF(thisVar->ilayvalues[ll][ii], TFloatFormat::ffGeneral, 4, 0) + " ";
						else
							S = S + "-0 ";

						if (ii % 10 == 9) {
							StateList->Add(S);
							S = "";
						}
					}
					if (!S.empty()) StateList->Add(S);
					S = "";
				}
			if (!S.empty()) StateList->Add(S);
			StateList->Add("######");
		}
	}
	StateList->SaveToFile(SaveStateFileName);
	delete StateList;

	SaveStateFileName = "";
	SaveStateFlag = false;
}

void CRHMmain::print_progress_start() 
{
	std::cout << "Running simulation...\n";
}

void CRHMmain::print_progress(long current_step, long last_step, int print_frequency)
{
	if (current_step % (Global::Freq * print_frequency) == 0)
	{
		std::cout << '\r' << setprecision(3) << setfill(' ') << setw(25) << (((float)current_step / (float)last_step) * 100.0f) << "% complete.";
		std::cout.flush();
	}
}

void CRHMmain::print_progress_end()
{
	std::cout.flush();
	std::cout << '\r' << setfill(' ') << setw(25) << 100.0f << "% Complete!";
	std::cout.flush();
	std::cout << "\n\n\n";
}