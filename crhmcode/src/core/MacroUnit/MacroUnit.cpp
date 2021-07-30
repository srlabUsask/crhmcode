// 10/04/12
//---------------------------------------------------------------------------
//#include "stdafx.h"
#include <stdio.h>
//#include <tchar.h>

#include "MacroUnit.h"
#include <map>

//---------------------------------------------------------------------------

//#include "CRHM_parse.h"
#include <boost/spirit/include/classic_exceptions.hpp>
//#include "CRHMmain.h"

#if defined(__linux__) || defined(__APPLE__) //added for resolving the introspection issue. Manishankar
#include <cxxabi.h>
#endif

extern double xLimit;

std::vector<std::string> * DefCRHM::DefStringList = NULL;
