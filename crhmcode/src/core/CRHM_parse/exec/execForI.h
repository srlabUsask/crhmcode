#pragma once

#ifndef EXECFORI
#define EXECFORI

#include "execbase.h"

class execForI : public execbase {
public:
	execForI(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterFOR_)
		: execbase(eval_, oper_, "ForI"), PCiter(PCiter_), PCiterFOR(PCiterFOR_),
		MyFor(NULL) {};

	execForI(const execForI& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterFOR(Cl.PCiterFOR),
		MyFor(Cl.MyFor) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		list<Execbase> ::iterator PCiterFORc = PCiterFOR.top();
		PCiter = PCiterFORc;

		MyFor = (PCiter)->get();

		//    Execbase Sp(new execForI(*this));
		//    oper.push_back(Sp);

		PCiter = oper.end();
		--PCiter;

		((execFor*)MyFor)->setInc_iter(PCiter);
	}

	double operator()() const { // execution

		return -1;
	}

private:

	list<Execbase> ::iterator& PCiter;   // changes for each for
	stack<list<Execbase> ::iterator>& PCiterFOR; // changes for each for

	mutable execbase* MyFor;
};

#endif // !EXECFORI
