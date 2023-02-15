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

#ifndef EXECVGET
#define EXECVGET

#include "execbase.h"

class execVget : public execbase {
public:
	execVget(symtab_t& vars_, stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) :
		execbase(eval_, oper_, "Vget"), vars(vars_), LastVar(LastVar_) {};
	execVget(const execVget& Cl) : execbase(Cl), vars(Cl.vars), LastVar(Cl.LastVar) {}; // copy constructor
	execVget& operator=(const execVget& Cl); //  assigment operator

	void operator()(const string::iterator b, const string::iterator e) const {

		string S(b, e);
		symtab_t::iterator FP = vars.find(S);

		if (FP == vars.end()) {
			string SS("macro code - reading from an undefined variable: " + S);

			for (const auto& kv : vars) {
 				std::cout << kv.first << std::endl;
			}

			CRHMException Except(SS, TExcept::TERMINATE);
			throw CRHMException(Except);
		}

		Lvar = &FP->second;

		string SS(e, e + 1); // !!! wrong ???							 
		if (SS != " ")
		{
			string::size_type eq = SS.find_first_not_of(" \t\n");
			if (SS[eq] == '[')
				LastVar.push(&FP->second);
		}

		Execbase Sp(new execVget(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		Lvar->Ihh = 0;

		double X = Lvar->get(); // in case there is no array element [n]
		eval.push(X);
		return X;
	}

private:
	symtab_t& vars;
	stack<VarCHRM*>& LastVar;
};

#endif // !EXECVGET
