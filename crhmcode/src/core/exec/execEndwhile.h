#pragma once

#ifndef EXECENDWHILE
#define EXECENDWHILE

#include "execbase.h"

class execEndwhile : public execbase { // Pushed on to stack!
public:
	execEndwhile(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterWHILE_)
		: execbase(eval_, oper_, "EndWhile"), PCiter(PCiter_), PCiterWHILE(PCiterWHILE_),
		MyWhile(NULL) {};

	execEndwhile(const execEndwhile& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterWHILE(Cl.PCiterWHILE),
		MyWhile(Cl.MyWhile) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		list<Execbase> ::iterator PCiterWHILEc = PCiterWHILE.top();
		PCiter = PCiterWHILEc;

		MyWhile = (PCiter)->get();

		PCiterWHILE.pop(); // all done

		Execbase Sp(new execEndwhile(*this));
		oper.push_back(Sp);

		PCiter = oper.end();
		--PCiter;

		((execWhile*)MyWhile)->setEnd_iter(PCiter);
	}

	double operator()() const { // execution
		((execWhile*)MyWhile)->jmpBegin_iter(); // goto start and retest
		return -1;
	}

private:
	list<Execbase> ::iterator& PCiter;   // changes for each while
	stack<list<Execbase> ::iterator>& PCiterWHILE; // changes for each while

	mutable execbase* MyWhile;
};

#endif // !EXECENDWHILE
