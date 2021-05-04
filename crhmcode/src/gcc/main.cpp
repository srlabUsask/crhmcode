//#include "stdafx.h"
#include <stdio.h>

#include "../core/CRHMmain/CRHMmain.h"

const char * argp_program_version =
    "CRHMcode gcc Version 1.2";
const char * argp_program_bug_address =
    "<https://github.com/srlabUsask/crhmcode/issues>";

static char doc[] = "CRHM";

static char args_doc[] = "PROJECT_FILE [STRING...]";

std::string unrecongnized_option(char * option)
{
    std::string message = 
        "\nUnrecognized option \""
        + std::string(option) 
        + "\" given. Use option --help for usage information.\n";
    return message;
}


void read_option(char ** argv, struct crhm_arguments * arguments, int * i)
{


    switch (argv[*i][1])
    {
    case 't':
        *i = *i + 1;
        if (!strcmp(argv[*i], "MS"))
        {
            arguments->time_format = TIMEFORMAT::MS;
        }
        else if (!strcmp(argv[*i], "YYYYMMDD"))
        {
            arguments->time_format = TIMEFORMAT::YYYYMMDD;
        }
        else if (!strcmp(argv[*i], "MMDDYYYY"))
        {
            arguments->time_format = TIMEFORMAT::MMDDYYYY;
        }
        else
        {
            std::cout << "\nUnable to read time format argument. "+ std::string(argv[*i]) +"\n";
            std::cout << "-t must be followed directey by a valid time format.\n";
            std::cout << "Valid formats are: \n\t\tMS \n\t\tYYYYMMDD \n\t\tMMDDYYYY\n";
            exit(1);
        }
        break;
    case 'h':
        std::cout << USE_MESSAGE;
        exit(1);
    case '-':
        switch (argv[*i][2])
        {
        case 'h':
            if (!strcmp(argv[*i], "--help"))
            {
                std::cout << USE_MESSAGE;
                exit(1);
            }
        default:
            std::cout << unrecongnized_option(argv[*i]);
            exit(1);
        }
        break;
    default:
        std::cout << unrecongnized_option(argv[*i]);
        exit(1);
    }

}

void read_argument(char* argument, struct crhm_arguments* arguments)
{
    arguments->project_name = std::string(argument);
}


int main(int argc, char *argv[])
{

    struct crhm_arguments arguments;
    // Set Default Argument Values
    arguments.project_name = "";
    arguments.time_format = TIMEFORMAT::YYYYMMDD;
    arguments.obs_out = false;

    /*
    * Read the incoming argv[] vector
    */
    for (int i = 1; i < argc; i++) 
    {
        if (argv[i][0] == '-') 
        {
            read_option(argv, &arguments,  &i);
        }
        else
        {
            read_argument(argv[i], &arguments);
        }
    }

    CRHMmain * m = new CRHMmain(&arguments);

    std::string projectArgument = arguments.project_name;

    m->OpenNamePrj = projectArgument;
    m->DoPrjOpen(projectArgument, "");
    m->RunClick ();
}
