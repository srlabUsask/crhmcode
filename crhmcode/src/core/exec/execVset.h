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

#ifndef EXECVSET
#define EXECVSET

#include "execbase.h"

class execVset : public execbase {
public:
	execVset(symtab_t& vars_, stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVas_)
		: execbase(eval_, oper_, "Vset"), vars(vars_), LastVas(LastVas_) {};
	execVset(const execVset& Cl) : execbase(Cl), vars(Cl.vars), LastVas(Cl.LastVas) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const {

		string S(b, e);
		int ii = S.find_first_of("[ =\t");

		if (ii > 0)
			S.erase(ii);

		symtab_t::iterator FP = vars.find(S);
		if (FP == vars.end()) {
			string SS("macro code - writing to an undefined variable: \"" + S + "\".  Suggestion - declared observations always end with a # symbol");
			CRHMException Except(SS, TExcept::TERMINATE);
			throw CRHMException(Except);
		}

		Lvar = &FP->second;
		LastVas.push(&FP->second);

		Execbase Sp(new execVset(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		Lvar->Ihh = 0;
		return -888;
	}

private:
	symtab_t& vars;
	stack<VarCHRM*>& LastVas;
};

#endif // !EXECVSET
