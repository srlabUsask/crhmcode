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
#pragma once

#ifndef MYPARSER
#define MYPARSER

#include "ClassModule.h"

class Myparser {
	const char* exp_ptr;  // points to the expression
	char token[80]; // holds current token
	char tok_type{ '\0' };  // holds token's type

	int row{ 0 };
	int col{ 0 };
	int repeat{ 0 };
	int rowrepeat{ 0 };
	int Bang{ 0 };
	bool repeatset{ false };
	ClassPar* LocalPar{ NULL };

	void eval_exp2(double& result);
	void eval_exp3(double& result);
	void eval_exp4(double& result);
	void eval_exp5(double& result);
	void eval_exp6(double& result);
	void atom(double& result);
	void get_token();
	void serror(int error);
	int isdelim(char c);
public:
	Myparser();
	void eval_exp(ClassPar* Par);
};

#endif // !MYPARSER
