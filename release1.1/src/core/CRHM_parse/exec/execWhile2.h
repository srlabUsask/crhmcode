#pragma once

#ifndef EXECWHILE2
#define EXECWHILE2

#include "execbase.h"

class execWhile2 : public execbase { // Pushed on to stack!
public:
	execWhile2(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterWHILE_)
		: execbase(eval_, oper_, "While2"), PCiter(PCiter_), PCiterWHILE(PCiterWHILE_),
		MyWhile(NULL) {};

	execWhile2(const execWhile2& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterWHILE(Cl.PCiterWHILE),
		MyWhile(Cl.MyWhile) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		list<Execbase> ::iterator PCiterWHILEc = PCiterWHILE.top();
		PCiter = PCiterWHILEc;

		MyWhile = (PCiter)->get();

		Execbase Sp(new execWhile2(*this));
		oper.push_back(Sp);
	}

	double operator()() const { // execution

		if (!eval.top()) // false
			((execWhile*)MyWhile)->jmpEnd_iter();

		eval.pop();

		return -1;
	}

private:
	list<Execbase> ::iterator& PCiter;   // changes for each while
	stack<list<Execbase> ::iterator>& PCiterWHILE; // changes for each while

	mutable execbase* MyWhile;
};

#endif // !EXECWHILE2
