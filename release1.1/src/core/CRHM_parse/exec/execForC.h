#pragma once

#ifndef EXECFORC
#define EXECFORC

#include "execbase.h"

class execForC : public execbase {
public:
	execForC(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterFOR_)
		: execbase(eval_, oper_, "ForC"), PCiter(PCiter_), PCiterFOR(PCiterFOR_),
		MyFor(NULL) {};

	execForC(const execForC& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterFOR(Cl.PCiterFOR),
		MyFor(Cl.MyFor) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		list<Execbase> ::iterator PCiterFORc = PCiterFOR.top();
		PCiter = PCiterFORc;

		MyFor = (PCiter)->get();

		Execbase Sp(new execForC(*this));
		oper.push_back(Sp);

		PCiter = oper.end();
		--PCiter;

		((execFor*)MyFor)->setCon_iter(PCiter);
	}

	double operator()() const { // execution

		if (!eval.top()) // false
			((execFor*)MyFor)->jmpEnd_iter();

		eval.pop();

		return -1;
	}

private:

	list<Execbase> ::iterator& PCiter;   // changes for each for
	stack<list<Execbase> ::iterator>& PCiterFOR; // changes for each for

	mutable execbase* MyFor;
};

#endif // !EXECFORC
