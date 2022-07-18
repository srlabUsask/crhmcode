//#include "stdafx.h"
#include "core/CRHMArguments.h"

int main(int argc, char *argv[])
{
    //Declare the object for arguments.
    CRHMArguments * arguments = new CRHMArguments();

    arguments->readCommandLine(argc, argv);
    arguments->validate();

    int i = system("test -z $TZ && echo \"Enviroment variable TZ is not set this"
     " may negatively impact performance.\n Set TZ to :[Timezone]\n You can find"
     " the timezone to set TZ to in /etc/timezone on most systems.\n \" "
     "|| echo \"TZ is set to $TZ\n\"");

    //Create main object with the given arguments.
    CRHMmain* m = new CRHMmain(arguments);

    std::string projectArgument = arguments->get_project_name();
    m->OpenNamePrj = projectArgument;

    if (m->DoPrjOpen(projectArgument, ""))
    {
      m->RunClick();
    }
    else
    {
      std::cout << "Error encountered while loading the project. Check log file for more detail.\n";
    }

}
