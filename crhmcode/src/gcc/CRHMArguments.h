#ifndef CRHM_ARGUMENTS
#define CRHM_ARGUMENTS

#include "../core/Common/Common.h"

enum class OUTPUT_FORMAT {STD, OBS};

const string USE_MESSAGE = "\ncrhm [options] PROJECT_FILE\n"
	"\n"
	"\t-h - Display this message.\n"
	"\n"
	"\t-t TIME_FORMAT - Select the format for date time outputs.\n"
	"\t\tValid formats are:\n"
	"\t\tMS - Microsoft Excel floating point.\n"
	"\t\tISO - ISO 8601 extended format YYYY-MM-DDThh:mm\n"
	"\t\tYYYYMMDD - YYYY MM DD hh mm\n"
	"\n"
	"\t-f OUTPUT_FORMAT - Select the file format for the output.\n"
	"\t\tValid formats are:\n"
	"\t\tSTD - Standard output format. Sutable for a spreadsheet.\n"
	"\t\tOBS - Observation file .obs format. Sutable for reading with CRHM GUI.\n"
	"\n"
	"\t-o PATH - Specify a location to place the output file generated.\n"
	"\n"
	"\t-d DELIMITER - Specify a single character delimiter to use when generating file output. \n\t\tTab character is the default.\n"
	"\n"
	"\t--obs_file_directory DIRECTORY_PATH - Specify a directory where the obs files" 
	"\n\t\t for this project are found. This directory will be prepended to the obsfile"
	"\n\t\t names specified in the project file."
	"\n\n"
	"\t-p UPDATE_FREQUENCY - Show percentage of progress towards completion during simulation run."
	"\n\t\t UPDATE_FREQUENCY specifies after how many days to update the percentage."
	"\n"
	;

struct crhm_arguments
{
	std::string project_name;
	std::string output_name;
	std::string obs_file_directory;
	TIMEFORMAT time_format{TIMEFORMAT::ISO};
	bool time_format_set{false};
	OUTPUT_FORMAT output_format{OUTPUT_FORMAT::STD};
	char delimiter{'\t'};
	bool show_progress;
	int update_progress;
};

#endif // !CRHM_ARGUMENTS


