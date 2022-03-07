#include "CRHMArguments.h"
#include "InstrumentLogger.h"

CRHMArguments :: CRHMArguments ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::CRHMArguments()@@@CRHMArguments.cpp>");
    this -> project_name = "";
    this -> output_name = "";
    this -> obs_file_directory = "";
    this -> time_format = TIMEFORMAT :: ISO;
    this -> output_format = OUTPUT_FORMAT :: STD;
    this -> delimiter = '\t';
    this -> show_progress = false;
    this -> update_progress = 7;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::CRHMArguments()@@@CRHMArguments.cpp>");
}
void CRHMArguments :: readCommandLine (int argc, char * argv [])
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::readCommandLine(int argc, char * argv [])@@@CRHMArguments.cpp>");
    for (int i = 1; i < argc; i ++) {
        if (argv [i] [0] == '-')
        {
            this -> read_option (argv, & i);
        }

        else
        {
            this -> read_argument (argv [i]);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::readCommandLine(int argc, char * argv [])@@@CRHMArguments.cpp>");
}
void CRHMArguments :: read_option (char ** argv, int * i)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::read_option(char ** argv, int * i)@@@CRHMArguments.cpp>");
    std :: ofstream test_file;
    struct stat buff;
    int prog_frequency = 1;
    switch (argv [* i] [1]) {
    case 'h':
        std :: cout << USE_MESSAGE;
        exit (1);
    case 't':
        this -> time_format_set = true;
        * i = * i + 1;
        if (! strcmp (argv [* i], "MS"))
        {
            this -> time_format = TIMEFORMAT :: MS;
        }

        else
        if (! strcmp (argv [* i], "YYYYMMDD"))
        {
            this -> time_format = TIMEFORMAT :: YYYYMMDD;
        }

        else
        if (! strcmp (argv [* i], "ISO"))
        {
            this -> time_format = TIMEFORMAT :: ISO;
        }

        else
        {
            std :: cout << "\nUnable to read time format argument. " + std :: string (argv [* i]) + "\n";
            std :: cout << "-t must be followed directly by a valid time format.\n";
            std :: cout << "Valid formats are: \n\tMS \n\tISO \n\tYYYYMMDD\n";
            exit (1);
        }

        break;
    case 'f':
        * i = * i + 1;
        if (! strcmp (argv [* i], "STD"))
        {
            this -> output_format = OUTPUT_FORMAT :: STD;
        }

        else
        if (! strcmp (argv [* i], "OBS"))
        {
            this -> output_format = OUTPUT_FORMAT :: OBS;
        }

        else
        {
            std :: cout << "\nUnable to read output format argument. " + std :: string (argv [* i]) + "\n";
            std :: cout << "-f must be followed directly by a valid output format.\n";
            std :: cout << "Valid formats are: \n\tSTD - standard output.\n\tOBS - obsfile output.\n";
            exit (1);
        }

        break;
    case 'o':
        * i = * i + 1;
        this -> output_name = argv [* i];
        test_file.open (this -> output_name.c_str ());
        if (test_file.is_open ())
        {
            test_file.close ();
        }

        else
        {
            std :: cout << "\nArgument \"" + this -> output_name + "\" to -o could not be opened as a file to write to.\n";
            exit (1);
        }

        break;
    case 'd':
        * i = * i + 1;
        if (strlen (argv [* i]) == 1)
        {
            this -> delimiter = argv [* i] [0];
        }

        else
        {
            std :: cout << "\nInvalid argument \"" + std :: string (argv [* i]) + "\" to -d."
                "\nDelimiter must be a single character.\n";
            exit (1);
        }

        break;
    case 'p':
        * i = * i + 1;
        try {
            prog_frequency = std :: stoi (argv [* i]);
        }
        catch (std :: exception e) {
            std :: cout << "\nInvalid argument \"" + std :: string (argv [* i]) + "\" to -p."
                "\nFreqeuncy must be a positive integer.\n";
            exit (1);
        }
        if (prog_frequency > 0)
        {
            this -> show_progress = true;
            this -> update_progress = std :: stoi (argv [* i]);
        }

        else
        {
            std :: cout << "\nInvalid argument \"" + std :: string (argv [* i]) + "\" to -p."
                "\nFreqeuncy must be a positive integer.\n";
            exit (1);
        }

        break;
    case '-':
        switch (argv [* i] [2]) {
        case 'h':
            if (! strcmp (argv [* i], "--help"))
            {
                std :: cout << USE_MESSAGE;
                exit (1);
            }

        case 'o':
            * i = * i + 1;
            this -> obs_file_directory = argv [* i];
            if (stat (this -> obs_file_directory.c_str (), & buff) != 0)
            {
                std :: cout << "\nArgument to --obs_file_directory \"" + this -> obs_file_directory + "\" can't be resolved to a directory.\n";
                exit (1);
            }

            break;
        default:
            std :: cout << unrecongnized_option (argv [* i]);
            exit (1);
        }
        break;
    default:
        std :: cout << unrecongnized_option (argv [* i]);
        exit (1);
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::read_option(char ** argv, int * i)@@@CRHMArguments.cpp>");
}
void CRHMArguments :: read_argument (char * argument)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::read_argument(char * argument)@@@CRHMArguments.cpp>");
    this -> project_name = std :: string (argument);
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::read_argument(char * argument)@@@CRHMArguments.cpp>");
}
std :: string CRHMArguments :: unrecongnized_option (char * option)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::unrecongnized_option(char * option)@@@CRHMArguments.cpp>");
    std :: string message = "\nUnrecognized option \"" + std :: string (option) + "\" given. Use option --help for usage information.\n";

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::unrecongnized_option(char * option)@@@CRHMArguments.cpp>");
    return message;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::unrecongnized_option(char * option)@@@CRHMArguments.cpp>");
}
void CRHMArguments :: validate ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::validate()@@@CRHMArguments.cpp>");
    if (this -> output_format == OUTPUT_FORMAT :: OBS)
    {
        if (this -> time_format_set)
        {
            if (! (this -> time_format == TIMEFORMAT :: MS || this -> time_format == TIMEFORMAT :: YYYYMMDD))
            {
                std :: cout << "\nCannot use specified time format while requesting output format of OBS.\n"
                    "Only MS and YYYYMMDD formats are compatible with OBS output file.\n";
                exit (1);
            }

        }

        else
        {
            this -> time_format = TIMEFORMAT :: MS;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::validate()@@@CRHMArguments.cpp>");
}
std :: string CRHMArguments :: get_project_name ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::get_project_name()@@@CRHMArguments.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_project_name()@@@CRHMArguments.cpp>");
    return this -> project_name;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_project_name()@@@CRHMArguments.cpp>");
}
std :: string CRHMArguments :: get_output_name ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::get_output_name()@@@CRHMArguments.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_output_name()@@@CRHMArguments.cpp>");
    return this -> output_name;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_output_name()@@@CRHMArguments.cpp>");
}
std :: string CRHMArguments :: get_obs_file_directory ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::get_obs_file_directory()@@@CRHMArguments.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_obs_file_directory()@@@CRHMArguments.cpp>");
    return this -> obs_file_directory;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_obs_file_directory()@@@CRHMArguments.cpp>");
}
TIMEFORMAT CRHMArguments :: get_time_format ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::get_time_format()@@@CRHMArguments.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_time_format()@@@CRHMArguments.cpp>");
    return this -> time_format;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_time_format()@@@CRHMArguments.cpp>");
}
OUTPUT_FORMAT CRHMArguments :: get_output_format ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::get_output_format()@@@CRHMArguments.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_output_format()@@@CRHMArguments.cpp>");
    return this -> output_format;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_output_format()@@@CRHMArguments.cpp>");
}
char CRHMArguments :: get_delimiter ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::get_delimiter()@@@CRHMArguments.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_delimiter()@@@CRHMArguments.cpp>");
    return this -> delimiter;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_delimiter()@@@CRHMArguments.cpp>");
}
bool CRHMArguments :: get_show_progress ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::get_show_progress()@@@CRHMArguments.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_show_progress()@@@CRHMArguments.cpp>");
    return this -> show_progress;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_show_progress()@@@CRHMArguments.cpp>");
}
int CRHMArguments :: get_update_progress ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMArguments::get_update_progress()@@@CRHMArguments.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_update_progress()@@@CRHMArguments.cpp>");
    return this -> update_progress;
InstrumentLogger::instance()->log_instrument_log("</CRHMArguments::get_update_progress()@@@CRHMArguments.cpp>");
}