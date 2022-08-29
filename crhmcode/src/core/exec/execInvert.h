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

#ifndef EXECINVERT
#define EXECINVERT

#include "execbase.h"

class execInvert : public execbase {
public:
	execInvert(stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "invert") {};
	execInvert(const execInvert& Cl) : execbase(Cl) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {
		Execbase Sp(new execInvert(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double X = eval.top();
		eval.pop();

		if (X == 0.0)
			X = 1.0;
		else
			X = 0.0;

		eval.push(X);
		return X;
	}
};

#endif // !EXECINVERT
