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

#ifndef VANDP
#define VANDP

union VandP {

public:
	VandP(long Long) : both(Long) {}; // constructor
	VandP(void) : both(0) {}; // constructor

	unsigned long both;
	unsigned short int Module[2];

	unsigned short int GetV(void) { return Module[0]; };
	void PutV(unsigned short int V) { Module[0] = V; };
	unsigned short int GetP(void) { return Module[1]; };
	void PutP(unsigned short int P) { Module[1] = P; };
	void Set(long Long) { both = Long; };
};

#endif // !VANDP
