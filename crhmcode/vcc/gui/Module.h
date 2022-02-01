#pragma once

class Module
{
public:
	Module() : head(0), tail(0), avail(false), isGroup(false), isStruct(false) {};
	int head;
	int tail;
	bool avail;
	bool isGroup;
	bool isStruct;
	long GrpCnt{ 0 };
	long StructCnt{ 0 };
};