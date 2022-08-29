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

#include "Myparser.h"

//---------------------------------------------------------------------------
Myparser::Myparser() // parser constructor
{
	exp_ptr = NULL;

	for (int i = 0; i < 80; i++) {
		token[i] = '\0';
	}

}

// Parser entry point.
void Myparser::eval_exp(ClassPar* Par)
{
	LocalPar = Par;
	double result, Last;
	int stop;
	bool OpenBrkt;

	//"points to the expression"
	exp_ptr = Par->valstr.c_str();

	row = 0; col = 0;
	rowrepeat = 1;
	Bang = 0;

next:
	repeat = 1;
	repeatset = false;
	OpenBrkt = false;

	//determine if the current token is a number, delimeter or variable
	get_token();

	if (*token == '[')
		result = 0.0;
	else if (*token) {
		eval_exp2(result);
		if (result > Par->maxVal) result = Par->maxVal;
		if (result < Par->minVal) result = Par->minVal;
		Last = result;
	}
	else
		result = 0.0;

	bool end = !*exp_ptr;

	switch (*token) {
	case '\0':
		if (col >= Par->dim) break;

		if (Par->varType == TVar::Float)
			Par->layvalues[row][col++] = result;
		else if (Par->varType == TVar::Int)
			Par->ilayvalues[row][col++] = (long)result;

		for (int ll = row; ll < Par->lay; ++ll) {
			if (Bang) { // N.B. loop start
				for (int ii = col - 1; ii < Par->dim; ++ii) {
					if (Par->varType == TVar::Float)
						Par->layvalues[ll][ii] = Last;
					else if (Par->varType == TVar::Int)
						Par->ilayvalues[ll][ii] = (long)Last;

					Last += 1;
				}
			}
			else {
				for (int ii = col; ii < Par->dim; ++ii)
					if (Par->varType == TVar::Float)
						Par->layvalues[ll][ii] = 0.0;
					else if (Par->varType == TVar::Int)
						Par->ilayvalues[ll][ii] = 0;
			}

			col = 0;;
		}
		break;
	case '[':
		rowrepeat = repeat;
		repeat = 1;
		repeatset = false;
		OpenBrkt = true;
		goto next;
	case ']':
		OpenBrkt = false;
		while (isspace(*exp_ptr)) ++exp_ptr; // skip over white space
		if (*exp_ptr == ',') ++exp_ptr; // skip over comma

		stop = col + repeat;
		if (stop > Par->dim) stop = Par->dim;
		for (int ii = col; ii < stop; ++ii)
			if (Par->varType == TVar::Float)
				Par->layvalues[row][col++] = result;
			else if (Par->varType == TVar::Int)
				Par->ilayvalues[row][col++] = (long)result;

		for (int ii = col; ii < Par->dim; ++ii) {
			Last += Bang;
			if (Par->varType == TVar::Float)
				Par->layvalues[row][ii] = Last;
			else if (Par->varType == TVar::Int)
				Par->ilayvalues[row][ii] = (long)Last;
		}

		Bang = 0;
		row++; col = 0;
		if (rowrepeat > 1 || end) {
			stop = row + rowrepeat - 1;
			if (stop > Par->lay || end) stop = Par->lay;

			for (int ll = row; ll < stop; ++ll) {
				for (int ii = col; ii < Par->dim; ++ii)
					if (Par->varType == TVar::Float)
						Par->layvalues[ll][ii] = Par->layvalues[ll - 1][ii];
					else if (Par->varType == TVar::Int)
						Par->ilayvalues[ll][ii] = Par->ilayvalues[ll - 1][ii];
			}
			row = stop;
			rowrepeat = 1;
		}
		if (row >= Par->lay) break;

		goto next;
	case ',':
		stop = col + repeat;
		if (stop > Par->dim) stop = Par->dim;
		for (int ii = col; ii < stop; ++ii)
			if (Par->varType == TVar::Float)
				Par->layvalues[row][col++] = result;
			else if (Par->varType == TVar::Int)
				Par->ilayvalues[row][col++] = (long)result;
		if (col >= Par->dim)
			if (!OpenBrkt && (row + 1 < Par->lay)) {
				col = 0;
				++row;
			}

		goto next;
	default:
		serror(0); // last token must be null
		break;
	} // switch
}

// Add or subtract two terms.
void Myparser::eval_exp2(double& result)
{
	char op; //removed register keyword to fix warning. Manishankar
	double temp;

	eval_exp3(result);
	while ((op = *token) == '+' || op == '-') {
		get_token();
		eval_exp3(temp);
		switch (op) {
		case '-':
			result = result - temp;
			break;
		case '+':
			result = result + temp;
			break;
		default:
			break;
		}
	}
}

// Multiply or divide two factors.
void Myparser::eval_exp3(double& result)
{
	char op; //removed register keyword to fix warning. Manishankar
	double temp;

	eval_exp4(result);
	while ((op = *token) == '*' || op == '/' || op == '%') {
		get_token();
		if (op == '*' && !repeatset) {
			repeat = (int)result; //added cast to int - jhs507
			repeatset = true;
			if (*token == '[') return;
			eval_exp4(result);
			return;
		}
		eval_exp4(temp);
		switch (op) {
		case '*':
			result = result * temp;
			break;
		case '/':
			result = result / temp;
			break;
		case '%':
			result = (int)result % (int)temp;
			break;
		default:
			break;
		}
	}
}

// Process an exponent
void Myparser::eval_exp4(double& result)
{
	double temp;
	//double ex; variable is unreferenced commenting out for now - jhs507
	//int t; //removed register keyword to fix warning. Manishankar variable is unreferenced commenting out for now - jhs507

	eval_exp5(result);
	if (*token == '^') {
		get_token();
		eval_exp4(temp);
		if (temp == 0.0) {
			result = 1.0;
			return;
		}
		result = pow(result, temp);
	}
}

// Evaluate a unary + or -.
void Myparser::eval_exp5(double& result)
{
	char  op; //removed register keyword to fix warning. Manishankar

	op = 0;
	if (((tok_type == DELIMITER) && *token == '+') || *token == '-') {  //warning resolved by Manishankar
		op = *token;
		get_token();
	}
	eval_exp6(result);
	if (op == '-') result = -result;
}

// Process a parenthesized expression.
void Myparser::eval_exp6(double& result)
{
	if (*token == '(') {  //warning resolved by Manishankar
		repeatset = true;
		get_token();
		eval_exp2(result);
		if (*token != ')')
			serror(1);
		get_token();
	}
	else atom(result);
}

// Get the value of a number.
void Myparser::atom(double& result)
{
	switch (tok_type) {
	case NUMBER:
		result = atof(token);
		get_token();
		return;
	default:
		serror(0);
	}
}

// Display a syntax error.
void Myparser::serror(int error)
{
	static string e[] = {
		"Syntax Error",
		"Unbalanced Parentheses",
		"No expression Present"
	};
	LogError(CRHMException(string(e[error]) + " in module '" +
		LocalPar->module + "' parameter '" + LocalPar->param + "'", TExcept::WARNING));

	for (int ll = row; ll < LocalPar->lay; ++ll) { // reset remainder of parameter values to 0
		for (int ii = col; ii < LocalPar->dim; ++ii)
			if (LocalPar->varType == TVar::Float)
				LocalPar->layvalues[ll][ii] = 0.0;
			else if (LocalPar->varType == TVar::Int)
				LocalPar->ilayvalues[ll][ii] = 0;
	}
}

// Obtain the next token.
void Myparser::get_token()
{
	char* temp;  //removed register keyword to fix warning. Manishankar

	tok_type = 0;
	temp = token;
	*temp = '\0';

	if (!*exp_ptr) return; // at end of expression

	while (isspace(*exp_ptr)) ++exp_ptr; // skip over white space

	if (*exp_ptr == '!') { // make series
		Bang = 1;
		++exp_ptr;
	}

	//check if exp_ptr is pointing to a valid character, that is, one of +-*/%^=(),[]!
	if ((*exp_ptr) && strchr("+-*/%^=(),[]!", *exp_ptr)) {  // added ','
		tok_type = DELIMITER;
		// advance to next char
		*temp++ = *exp_ptr++;
	}
	else if (isalpha(*exp_ptr)) {
		while (!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
		tok_type = CRHM::VARIABLE;
	}
	else if (iswdigit(*exp_ptr)) {
		while ((*exp_ptr) && strchr("0123456789.", *exp_ptr)) *temp++ = *exp_ptr++;
		if ((*exp_ptr) && strchr("eE", *exp_ptr)) {
			*temp++ = *exp_ptr++;
			while ((*exp_ptr) && strchr("+- ", *exp_ptr))  *temp++ = *exp_ptr++;
			while (!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
		}
		tok_type = NUMBER;
	}

	*temp = '\0';
}

// Return true if c is a delimiter.
int Myparser::isdelim(char c)
{
	if (((*exp_ptr) && strchr(" +-/*%^=(),[]", c)) || c == 9 || c == '\r' || c == 0)  // added ','  //warning resolved by Manishankar
		return 1;
	return 0;
}
