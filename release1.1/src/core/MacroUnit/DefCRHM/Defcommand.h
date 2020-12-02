#pragma once

#ifndef DEFCOMMAND
#define DEFCOMMAND

#include "DefCRHM.h"

class Defcommand : public DefCRHM {
public:
	Defcommand(ClassMacro* Macro_) : DefCRHM(Macro_) {}
};

#endif // !DEFCOMMAND
