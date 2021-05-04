#ifndef CRHM_ARGUMENTS
#define CRHM_ARGUMENTS

#include "../core/Common/Common.h"

const string USE_MESSAGE = "\nI am the usage message! I will be written later...\n";

struct crhm_arguments
{
	std::string project_name;
	TIMEFORMAT time_format;
	bool obs_out;
};

#endif // !CRHM_ARGUMENTS


