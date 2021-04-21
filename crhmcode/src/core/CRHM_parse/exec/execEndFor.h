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
