#pragma once

#ifndef CLASSWQ_SUBSTITUTE_HYPE
#define CLASSWQ_SUBSTITUTE_HYPE

#include "WQ_CRHM.h"

class ClassWQ_Substitute_Hype : public ClassModule {
public:

	ClassWQ_Substitute_Hype(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared variables
	double* conc_soil_rechr{ NULL };   // concentration of inorganic nitrogen *** from soilstate
	double** conc_soil_rechr_lay{ NULL };
	double* conc_soil_lower{ NULL };   // concentration of organic nitrogen *** from soilstate
	double** conc_soil_lower_lay{ NULL };
	double* conc_soil_moist{ NULL };   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
	double** conc_soil_moist_lay{ NULL };

	// declared parameters

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	ClassWQ_Substitute_Hype* klone(string name) const;
};

#endif // !CLASSWQ_SUBSTITUTE_HYPE
