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
#include "../../src/core/ClassModule.h"

//#pragma once

class ClassEntry {
public:
	unsigned long OrigPos; // ListBox2 initial index
	long rank;             // rank bit: highest = 0
	bool used{false};
	string Name;           // module name
	ClassModule *module;   // pointer for module

	ClassEntry() : Name(""), OrigPos(0), rank(0), module(NULL) {};
	ClassEntry(string Name, ClassModule *module, int OrigPos_) : Name(Name), module(module), OrigPos(OrigPos_), rank(0) {};
	ClassEntry(const ClassEntry & Cl);
	ClassEntry & operator=(const ClassEntry & Cl);

	friend bool operator<(const ClassEntry &x, const ClassEntry &y);
};

bool operator<(const ClassEntry &x, const ClassEntry &y) {
	return x.rank < y.rank;
}

ClassEntry::ClassEntry(const ClassEntry & Cl) {
	OrigPos = Cl.OrigPos;
	rank = Cl.rank;
	used = Cl.used;
	Name = Cl.Name;
	module = Cl.module;
}

ClassEntry & ClassEntry::operator=(const ClassEntry & Cl) {
	if (this == &Cl) return *this;
	OrigPos = Cl.OrigPos;
	rank = Cl.rank;
	used = Cl.used;
	Name = Cl.Name;
	module = Cl.module;
	return *this;
}

void  MoveDown(vector<ClassEntry> &Entries, long to, long from) { // move 'from' downto 'to'
	ClassEntry Temp = Entries[from]; // save 'from'

	for (int jj = from; jj > to; --jj)
		Entries[jj] = Entries[jj - 1]; // move entries up to fill space

	Entries[to] = Temp; // save 'from' to 'to'
}

vector<ClassEntry> Entries;
