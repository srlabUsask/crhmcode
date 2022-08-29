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

#ifndef EXECENDFOR
#define EXECENDFOR

#include "execEndFor.h"

class execEndFor : public execbase {
public:
	execEndFor(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterFOR_)
		: execbase(eval_, oper_, "EndFor"), PCiter(PCiter_), PCiterFOR(PCiterFOR_),
		MyFor(NULL) {};

	execEndFor(const execEndFor& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterFOR(Cl.PCiterFOR),
		MyFor(Cl.MyFor) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		list<Execbase> ::iterator PCiterFORc = PCiterFOR.top();
		PCiter = PCiterFORc;

		MyFor = (PCiter)->get();

		PCiterFOR.pop(); // all done

		Execbase Sp(new execEndFor(*this));
		oper.push_back(Sp);

		PCiter = oper.end();
		--PCiter;

		((execFor*)MyFor)->setEnd_iter(PCiter);
	}

	double operator()() const { // execution

		((execFor*)MyFor)->jmpBegin_iter(); // goto condition and retest
		return -1;
	}

private:

	list<Execbase> ::iterator& PCiter;   // changes for each for
	stack<list<Execbase> ::iterator>& PCiterFOR; // changes for each for

	mutable execbase* MyFor;
};

#endif // !EXECENDFOR
