//#include "stdafx.h"
#include <stdio.h>
#include "../core/CRHMmain/CRHMmain.h"


int main(int argc, char *argv[])
{
    CRHMmain * m = new CRHMmain();
    //m->FormCreate(); Form create is run in the constructor so it doesn't need to be called here. 
    m->DoPrjOpen(argv[1], "");
    m->RunClick ();
}
