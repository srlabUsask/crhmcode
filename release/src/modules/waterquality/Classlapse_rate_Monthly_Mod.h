#pragma once

#ifndef CLASSLAPSE_RATE_MONTHLY_MOD
#define CLASSLAPSE_RATE_MONTHLY_MOD

#include "WQ_CRHM.h"

class Classlapse_rate_Monthly_Mod : public ClassModule {
public:

	Classlapse_rate_Monthly_Mod(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared variables
	double* lapse_rate{ NULL };
	double* lapse_rate_Mthly{ NULL };

	void decl(void);
	void init(void);
	void run(void);

	Classlapse_rate_Monthly_Mod* klone(string name) const;
};

#endif // !CLASSLAPSE_RATE_MONTHLY_MOD
