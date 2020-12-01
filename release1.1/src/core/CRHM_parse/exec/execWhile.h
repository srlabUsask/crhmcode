#pragma once

#ifndef EXECWHILE
#define EXECWHILE

#include "execWhile.h"

class execWhile : public execbase { // Pushed onto stack!
public:
	execWhile(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterWHILE_)
		: execbase(eval_, oper_, "While"), PCiter(PCiter_), PCiterWHILE(PCiterWHILE_),
		Begin_iter(), End_iter() {};

	execWhile(const execWhile& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterWHILE(Cl.PCiterWHILE),
		Begin_iter(Cl.Begin_iter), End_iter(Cl.End_iter) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		setBegin_iter();

		Execbase Sp(new execWhile(*this));
		oper.push_back(Sp);

		PCiterWHILE.push(--oper.end()); // push self
	}

	double operator()() const { // no execution - does not alter stack

		return -1;
	}

	void setBegin_iter(void) const { // used by self
		Begin_iter = oper.end();
		--Begin_iter; // save self. After execEndwhile pushed - updated
	};

	void setEnd_iter(list<Execbase> ::iterator PCiter) { // used by execEndwhile
		End_iter = PCiter;
		++Begin_iter; // done once after execEndwhile pushed on stack
	};

	void jmpBegin_iter(void) { // used by execWhile2
		PCiter = Begin_iter;
	};

	void jmpEnd_iter(void) { // used by execWhile2
		PCiter = End_iter;
	};

private:
	mutable list<Execbase> ::iterator Begin_iter;
	list<Execbase> ::iterator End_iter;

	list<Execbase> ::iterator& PCiter;   // changes for each while
	stack<list<Execbase> ::iterator>& PCiterWHILE; // changes for each while
};

#endif // !EXECWHILE
