//#include "stdafx.h"
#include <stdio.h>
#include <argp.h>
#include "../core/CRHMmain/CRHMmain.h"

const char * argp_program_version =
    "CRHMcode gcc Version 1.2";
const char * argp_program_bug_address =
    "<https://github.com/srlabUsask/crhmcode/issues>";

static char doc[] = "CRHM";

static char args_doc[] = "PROJECT_FILE [STRING...]";

static struct argp_option options[] =
{
    {"time_format", 't', "TIME_FORMAT", 0, "Specify the desired time fromat in the output file."},
    {"obs_out", 1000, 0, 0, "Produces output as an .obs file."},
    {0}
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
    struct crhm_arguments *arguments = static_cast<struct crhm_arguments*>(state->input);
    char microsoftDates[] = "MS";

    switch (key)
    {
        case 't':
            if(!strcmp(arg, microsoftDates))
            {
                arguments->time_format = TIMEFORMAT::MS;
            }
            else
            {
                std::cout << std::string(arg) + " - Not a recognized time format." << '\n';
                return ARGP_ERR_UNKNOWN;
            }

            break;

        case 1000: //obs_out is selected
            arguments->obs_out = true;
            break;

        case ARGP_KEY_ARG:
            if (state->arg_num >= 1)
            {
                argp_usage(state);
            }
            arguments->args[state->arg_num] = arg;
            break;

        case ARGP_KEY_END:
            if (state->arg_num < 1)
            {
                argp_usage(state);
            }
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};


int main(int argc, char *argv[])
{

    struct crhm_arguments arguments;
    arguments.time_format = TIMEFORMAT::YYYYMMDD;
    arguments.obs_out = false;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    CRHMmain * m = new CRHMmain(&arguments);

    std::string projectArgument = arguments.args[0];

    m->OpenNamePrj = projectArgument;
    m->DoPrjOpen(projectArgument, "");
    m->RunClick ();
}
