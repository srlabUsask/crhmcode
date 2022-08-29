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
