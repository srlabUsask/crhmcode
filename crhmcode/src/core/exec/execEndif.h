#pragma once

#ifndef EXECENDIF
#define EXECENDIF

#include "execbase.h"

class execEndif : public execbase { // NOT pushed on to stack!
public:
	execEndif(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterIF_)
		: execbase(eval_, oper_, "Endif"), PCiter(PCiter_), PCiterIF(PCiterIF_) {};

	execEndif(const execEndif& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterIF(Cl.PCiterIF) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		list<Execbase> ::iterator PCiterIFc = PCiterIF.top();
		PCiter = PCiterIFc;

		execbase* MyIf = (PCiter)->get();

		PCiter = oper.end();
		--PCiter;

		((execIf*)MyIf)->setEnd_iter(PCiter);

		PCiterIF.pop(); // all done
	}

	double operator()() const { // execution. Not used
		return -1;
	}

private:
	list<Execbase> ::iterator& PCiter;   // changes for each if
	stack<list<Execbase> ::iterator>& PCiterIF; // changes for each if
};

#endif // !EXECENDIF
