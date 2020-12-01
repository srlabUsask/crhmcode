#pragma once

#ifndef EXECELSE
#define EXECELSE

#include "execbase.h"

class execElse : public execbase {
public:
	execElse(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterIF_)
		: execbase(eval_, oper_, "Else"), PCiter(PCiter_), PCiterIF(PCiterIF_),
		MyIf(NULL) {};

	execElse(const execElse& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterIF(Cl.PCiterIF),
		MyIf(Cl.MyIf) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		list<Execbase> ::iterator PCiterIFc = PCiterIF.top();
		PCiter = PCiterIFc;

		MyIf = (PCiter)->get(); // list of shared_ptrs to class execbase

		PCiter = oper.end();
		--PCiter; // value before else pushed on to stack.

		((execIf*)MyIf)->setFalse_iter(PCiter);

		Execbase Sp(new execElse(*this));
		oper.push_back(Sp);
	}

	double operator()() const { // execution
		((execIf*)MyIf)->jmpEnd_iter();

		return -1;
	}

private:
	list<Execbase> ::iterator& PCiter;   // changes for each if
	stack<list<Execbase> ::iterator>& PCiterIF; // changes for each if

	mutable execbase* MyIf;
};

#endif // !EXECELSE
