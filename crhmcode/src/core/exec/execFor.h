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

#ifndef EXECFOR
#define EXECFOR

#include "execbase.h"

class execFor : public execbase {
public:
	execFor(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterFOR_)
		: execbase(eval_, oper_, "For"), PCiter(PCiter_), PCiterFOR(PCiterFOR_), Begin_iter(),
		Con_iter(), Inc_iter(), End_iter() {};

	execFor(const execFor& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterFOR(Cl.PCiterFOR),
		Begin_iter(Cl.Begin_iter), Con_iter(Cl.Con_iter), Inc_iter(Cl.Inc_iter), End_iter(Cl.End_iter) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		setBegin_iter();

		Execbase Sp(new execFor(*this));
		oper.push_back(Sp);

		PCiterFOR.push(--oper.end()); // push self
	}

	double operator()() const { // execution - do nothing

		return -1;
	}

	void setBegin_iter(void) const { // used by self
		Begin_iter = oper.end();
		--Begin_iter; // save self. After execEndfor pushed - updated
	};

	void setEnd_iter(list<Execbase> ::iterator PCiter) { // used by execEndfor
		End_iter = PCiter;
		++Begin_iter; // done once after execEndfor pushed on stack

		list<Execbase> ::iterator Con1_iter = Con_iter;
		list<Execbase> ::iterator Inc1_iter = Inc_iter;

		/*    list<Execbase> ::iterator PCit = oper.begin();
		while(PCit != oper.end()) {
		execbase Op = (*(*PCit));
		++PCit;
		} */

		oper.splice(End_iter, oper, ++Con1_iter, ++Inc1_iter); // move increment code to after statement code
	};

	void setCon_iter(list<Execbase> ::iterator PCiter) { // used by execForI
		Con_iter = PCiter;
	};

	void setInc_iter(list<Execbase> ::iterator PCiter) { // used by execForI
		Inc_iter = PCiter;
	};

	void jmpBegin_iter(void) { // used by execFOR
		PCiter = Begin_iter;
	};

	void jmpEnd_iter(void) { // used by execFor
		PCiter = End_iter;
	};

private:
	mutable list<Execbase> ::iterator Begin_iter;
	list<Execbase> ::iterator Con_iter; // points to ForC (conditional) instruction
	list<Execbase> ::iterator Inc_iter; // points to last increment instruction
	list<Execbase> ::iterator End_iter; // points to EndFor (end) instruction

	list<Execbase> ::iterator& PCiter;   // changes for each for
	stack<list<Execbase> ::iterator>& PCiterFOR; // changes for each for
};

#endif // !EXECFOR
