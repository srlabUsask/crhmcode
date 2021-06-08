//#include "stdafx.h"
#include <stdio.h>
#include "../core/Common/Common.h"
#include "../core/CRHMmain/CRHMmain.h"
#include "CRHMArguments.h"

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
    ofstream test_file;
    struct stat buff;
    int prog_frequency = 1;

    switch (argv[*i][1])
    {
    case 'h':
        std::cout << USE_MESSAGE;
        exit(1);
    case 't':
        arguments->time_format_set = true;
        *i = *i + 1;
        if (!strcmp(argv[*i], "MS"))
        {
            arguments->time_format = TIMEFORMAT::MS;
        }
        else if (!strcmp(argv[*i], "YYYYMMDD"))
        {
            arguments->time_format = TIMEFORMAT::YYYYMMDD;
        }
        else if (!strcmp(argv[*i], "ISO"))
        {
            arguments->time_format = TIMEFORMAT::ISO;
        }
        else
        {
            std::cout << "\nUnable to read time format argument. "+ std::string(argv[*i]) +"\n";
            std::cout << "-t must be followed directly by a valid time format.\n";
            std::cout << "Valid formats are: \n\tMS \n\tISO \n\tYYYYMMDD\n";
            exit(1);
        }
        break;
    case 'f':
        *i = *i + 1;
        if (!strcmp(argv[*i], "STD"))
        {
            arguments->output_format = OUTPUT_FORMAT::STD;
        }
        else if (!strcmp(argv[*i], "OBS"))
        {
            arguments->output_format = OUTPUT_FORMAT::OBS;
        }
        else
        {
            std::cout << "\nUnable to read output format argument. " + std::string(argv[*i]) + "\n";
            std::cout << "-f must be followed directly by a valid output format.\n";
            std::cout << "Valid formats are: \n\tSTD - standard output.\n\tOBS - obsfile output.\n";
            exit(1);
        }
        break;
    case 'o':
        *i = *i + 1;
        arguments->output_name = argv[*i];
        
        test_file.open(arguments->output_name.c_str());

        if (test_file.is_open()) 
        {
            test_file.close();
        }
        else
        {
            std::cout << "\nArgument \""
                + arguments->output_name 
                +"\" to -o could not be opened as a file to write to.\n";
            exit(1);
        }
        break;
    case 'd':
        *i = *i + 1;
        if (strlen(argv[*i]) == 1)
        {
            arguments->delimiter = argv[*i][0];
        }
        else
        {
            std::cout << "\nInvalid argument \"" + std::string(argv[*i]) + "\" to -d."
                "\nDelimiter must be a single character.\n";
            exit(1);
        }
        break;
    case 'p':
        *i = *i + 1;

        try 
        {
            prog_frequency = std::stoi(argv[*i]);
        }
        catch (exception e)
        {
            std::cout << "\nInvalid argument \"" + std::string(argv[*i]) + "\" to -p."
                "\nFreqeuncy must be a positive integer.\n";
            exit(1);
        }

        if ( prog_frequency > 0)
        {
            arguments->show_progress = true;
            arguments->update_progress = std::stoi(argv[*i]);
        }
        else
        {
            std::cout << "\nInvalid argument \"" + std::string(argv[*i]) + "\" to -p."
                "\nFreqeuncy must be a positive integer.\n";
            exit(1);
        }
        break;
    case '-':
        switch (argv[*i][2])
        {
        case 'h':
            if (!strcmp(argv[*i], "--help"))
            {
                std::cout << USE_MESSAGE;
                exit(1);
            }
        case 'o':
            *i = *i + 1;
            arguments->obs_file_directory = argv[*i];
            //Check if directory exists and exit if it can't be found. 
            if (stat(arguments->obs_file_directory.c_str(), &buff) != 0)
            {
                std::cout << "\nArgument to --obs_file_directory \"" +arguments->obs_file_directory+ "\" can't be resolved to a directory.\n";
                exit(1);
            }
            break;
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
    //Declare the structure for arguments.
    struct crhm_arguments arguments;

    // Set Default Argument Values
    arguments.project_name = "";
    arguments.output_name = "";
    arguments.obs_file_directory = "";
    arguments.time_format = TIMEFORMAT::ISO;
    arguments.output_format = OUTPUT_FORMAT::STD;
    arguments.delimiter = '\t';
    arguments.show_progress = false;
    arguments.update_progress = 7;
    

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

    //Perform logic check to make sure arguments are internaly consistant.
    if (arguments.output_format == OUTPUT_FORMAT::OBS)
    {
        if (arguments.time_format_set)
        {
            //Check that time format was set to MS or YYYYMMDD
            if (!(arguments.time_format == TIMEFORMAT::MS || arguments.time_format == TIMEFORMAT::YYYYMMDD))
            {
                std::cout << "\nCannot use specified time format while requesting output format of OBS.\n"
                    "Only MS and YYYYMMDD formats are compatible with OBS output file.\n";
                exit(1);
            }

        }
        else
        {
            //Default to MS time format.
            arguments.time_format = TIMEFORMAT::MS;
        }
    }

    //Run the program with the given arguments.
    CRHMmain* m = new CRHMmain(&arguments);

    std::string projectArgument = arguments.project_name;
    m->OpenNamePrj = projectArgument;
    m->DoPrjOpen(projectArgument, "");
    m->RunClick();

}
