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

#ifndef EXECVASSIGN
#define EXECVASSIGN

#include "execbase.h"

class execVassign : public execbase {
public:
	execVassign(stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVas_)
		: execbase(eval_, oper_, "Vassign"), LastVas(LastVas_) {};
	execVassign(const execVassign& Cl) : execbase(Cl), LastVas(Cl.LastVas) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const {

		Lvar = LastVas.top();
		LastVas.pop();

		Execbase Sp(new execVassign(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double X = eval.top();
		Lvar->put(X);
		eval.pop();
		int Cnt = eval.size();
		return X;
	}
	stack<VarCHRM*>& LastVas;
};

#endif // !EXECVASSIGN
