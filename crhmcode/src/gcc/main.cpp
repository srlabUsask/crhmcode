//#include "stdafx.h"
#include <stdio.h>
#include "../core/CRHMmain/CRHMmain.h"


int main(int argc, char *argv[])
{
    CRHMmain * m = new CRHMmain();

    std::string projectArgument = argv[1];

    m->OpenNamePrj = projectArgument;
    m->DoPrjOpen(projectArgument, "");
    m->RunClick ();
}
