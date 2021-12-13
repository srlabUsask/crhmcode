#include "CRHMArguments.h"

CRHMArguments::CRHMArguments()
{
    // Set Default Argument Values
    this->project_name = "";
    this->output_name = "";
    this->obs_file_directory = "";
    this->time_format = TIMEFORMAT::ISO;
    this->output_format = OUTPUT_FORMAT::STD;
    this->delimiter = '\t';
    this->show_progress = false;
    this->update_progress = 7;
}

void CRHMArguments::readCommandLine(int argc, char* argv[])
{
    /*
   * Read the incoming argv[] vector
   */
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            this->read_option(argv, &i);
        }
        else
        {
            this->read_argument(argv[i]);
        }
    }
}

void CRHMArguments::read_option(char** argv, int* i)
{
    std::ofstream test_file;
    struct stat buff;
    int prog_frequency = 1;

    switch (argv[*i][1])
    {
    case 'h':
        std::cout << USE_MESSAGE;
        exit(1);
    case 't':
        this->time_format_set = true;
        *i = *i + 1;
        if (!strcmp(argv[*i], "MS"))
        {
            this->time_format = TIMEFORMAT::MS;
        }
        else if (!strcmp(argv[*i], "YYYYMMDD"))
        {
            this->time_format = TIMEFORMAT::YYYYMMDD;
        }
        else if (!strcmp(argv[*i], "ISO"))
        {
            this->time_format = TIMEFORMAT::ISO;
        }
        else
        {
            std::cout << "\nUnable to read time format argument. " + std::string(argv[*i]) + "\n";
            std::cout << "-t must be followed directly by a valid time format.\n";
            std::cout << "Valid formats are: \n\tMS \n\tISO \n\tYYYYMMDD\n";
            exit(1);
        }
        break;
    case 'f':
        *i = *i + 1;
        if (!strcmp(argv[*i], "STD"))
        {
            this->output_format = OUTPUT_FORMAT::STD;
        }
        else if (!strcmp(argv[*i], "OBS"))
        {
            this->output_format = OUTPUT_FORMAT::OBS;
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
        this->output_name = argv[*i];

        test_file.open(this->output_name.c_str());

        if (test_file.is_open())
        {
            test_file.close();
        }
        else
        {
            std::cout << "\nArgument \""
                + this->output_name
                + "\" to -o could not be opened as a file to write to.\n";
            exit(1);
        }
        break;
    case 'd':
        *i = *i + 1;
        if (strlen(argv[*i]) == 1)
        {
            this->delimiter = argv[*i][0];
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
        catch (std::exception e)
        {
            std::cout << "\nInvalid argument \"" + std::string(argv[*i]) + "\" to -p."
                "\nFreqeuncy must be a positive integer.\n";
            exit(1);
        }

        if (prog_frequency > 0)
        {
            this->show_progress = true;
            this->update_progress = std::stoi(argv[*i]);
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
            this->obs_file_directory = argv[*i];
            //Check if directory exists and exit if it can't be found. 
            if (stat(this->obs_file_directory.c_str(), &buff) != 0)
            {
                std::cout << "\nArgument to --obs_file_directory \"" + this->obs_file_directory + "\" can't be resolved to a directory.\n";
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

void CRHMArguments::read_argument(char* argument)
{
    this->project_name = std::string(argument);    
}

std::string CRHMArguments::unrecongnized_option(char* option)
{
    std::string message =
        "\nUnrecognized option \""
        + std::string(option)
        + "\" given. Use option --help for usage information.\n";
    return message;
}

void CRHMArguments::validate()
{
    //Perform logic check to make sure arguments are internaly consistant.
    if (this->output_format == OUTPUT_FORMAT::OBS)
    {
        if (this->time_format_set)
        {
            //Check that time format was set to MS or YYYYMMDD
            if (!(this->time_format == TIMEFORMAT::MS || this->time_format == TIMEFORMAT::YYYYMMDD))
            {
                std::cout << "\nCannot use specified time format while requesting output format of OBS.\n"
                    "Only MS and YYYYMMDD formats are compatible with OBS output file.\n";
                exit(1);
            }

        }
        else
        {
            //Default to MS time format.
            this->time_format = TIMEFORMAT::MS;
        }
    }
}

std::string CRHMArguments::get_project_name()
{
    return this->project_name;
}

std::string CRHMArguments::get_output_name()
{
    return this->output_name;
}

std::string CRHMArguments::get_obs_file_directory()
{
    return this->obs_file_directory;
}

TIMEFORMAT CRHMArguments::get_time_format()
{
    return this->time_format;
}

OUTPUT_FORMAT CRHMArguments::get_output_format()
{
    return this->output_format;
}

char CRHMArguments::get_delimiter()
{
    return this->delimiter;
}

bool CRHMArguments::get_show_progress()
{
    return this->show_progress;
}

int CRHMArguments::get_update_progress()
{
    return this->update_progress;
}
