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
