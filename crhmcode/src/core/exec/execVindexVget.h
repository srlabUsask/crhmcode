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

#ifndef EXECVINDEXVGET
#define EXECVINDEXVGET

#include "execbase.h"

struct execVindexVget : public execbase {
	execVindexVget(stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) : execbase(eval_, oper_, "VindexVget"), LastVar(LastVar_), Indices(0), Idle(true) {}
	execVindexVget(const execVindexVget& Cl) : execbase(Cl), LastVar(Cl.LastVar), Indices(Cl.Indices), Idle(Cl.Idle) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const
	{
		if (Lvar != LastVar.top() || Idle) { // reset for new variable
			Indices = 0;
			Idle = false;
			Lvar = LastVar.top();
		}

		++Indices;

		if (e[0] != '[') {
			LastVar.pop();
			Idle = true;

			Execbase Sp(new execVindexVget(*this));
			oper.push_back(Sp);
		}
	}

	double operator()() const {
		switch (Indices) {
		case 2:
			Lvar->Ill = (int)eval.top() - 1;  // set by re-arrange in execbase
			if (Lvar->Ill < 0) Lvar->Ill = 0;
			eval.pop(); // remove element index
		case 1:
			Lvar->Ihh = (int)eval.top() - 1;  // set by re-arrange in execbase
			if (Lvar->Ihh < 0) Lvar->Ihh = 0;
			eval.pop(); // remove element index
		default: break;
		}

		eval.pop(); // remove variable not indexed

		double X = Lvar->get();
		eval.push(X); // push indexed variable to stack
		int Cnt = eval.size();
		return X;
	}

private:
	stack<VarCHRM*>& LastVar; // could be redundant
	mutable long Indices; // handles 1D & 2D
	mutable bool Idle; // Flags all variable dimensions handled. Required when variable has consecutive references
};

#endif // !EXECVINDEXVGET
