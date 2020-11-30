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
