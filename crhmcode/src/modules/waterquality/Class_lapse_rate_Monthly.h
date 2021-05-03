#pragma once

#ifndef CLASS_LAPSE_RATE_MONTHLY
#define CLASS_LAPSE_RATE_MONTHLY

#include "WQ_CRHM.h"

class Class_lapse_rate_Monthly : public ClassModule {
public:

	Class_lapse_rate_Monthly(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared variables
	double* lapse_rate{ NULL };
	double* lapse_rate_Mthly{ NULL };

	void decl(void);
	void init(void);
	void run(void);

	Class_lapse_rate_Monthly* klone(string name) const;
};

#endif // !CLASS_LAPSE_RATE_MONTHLY
