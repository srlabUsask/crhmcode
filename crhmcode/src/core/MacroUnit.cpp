#include <stdio.h>
#include "MacroUnit.h"
#include <map>
#include <boost/spirit/include/classic_exceptions.hpp>

#if defined (__linux__) || defined (__APPLE__)
    #include <cxxabi.h>
#endif

extern double xLimit;
std :: vector < std :: string > * DefCRHM :: DefStringList = NULL;
