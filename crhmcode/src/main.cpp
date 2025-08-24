/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
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
