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

#ifndef EXECNEGATE
#define EXECNEGATE

#include "execbase.h"

class execNegate : public execbase {
public:
	execNegate(stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "negate") {};
	execNegate(const execNegate& Cl) : execbase(Cl) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {
		Execbase Sp(new execNegate(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double X = eval.top();
		eval.pop();
		eval.push(-X);
		return X;
	}
};

#endif // !EXECNEGATE
