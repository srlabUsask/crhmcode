#include "CRHMLogger.h"
#include <iostream>
#include "../InstrumentLogger.h"

CRHMLogger * CRHMLogger :: s_instance = 0;

CRHMLogger :: CRHMLogger ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMLogger::CRHMLogger()@@@CRHMLogger.cpp>");
    try {
        auto logger = spdlog :: rotating_logger_st ("run_log", "crhmRun.log", 1024 * 1024 * 10, 5, true);
        logger -> set_level (spdlog :: level :: level_enum :: trace);
        this -> runLogger = logger;
    }
    catch (const spdlog :: spdlog_ex & ex) {
        std :: cout << "Log initialization failed for run logger: " << ex.what () << std :: endl;
        exit (1);
    }
    try {
        auto console = spdlog :: stdout_color_st ("console");
        console -> set_pattern ("%v");
        this -> consoleLogger = console;
    }
    catch (const spdlog :: spdlog_ex & ex) {
        std :: cout << "Log initialization failed for console logger: " << ex.what () << std :: endl;
        exit (1);
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::CRHMLogger()@@@CRHMLogger.cpp>");
}
CRHMLogger * CRHMLogger :: instance ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMLogger::instance()@@@CRHMLogger.cpp>");
    if (! s_instance)
    {
        s_instance = new CRHMLogger;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::instance()@@@CRHMLogger.cpp>");
    return s_instance;
InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::instance()@@@CRHMLogger.cpp>");
}
std :: shared_ptr < spdlog :: logger > CRHMLogger :: get_run_logger ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMLogger::get_run_logger()@@@CRHMLogger.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::get_run_logger()@@@CRHMLogger.cpp>");
    return runLogger;
InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::get_run_logger()@@@CRHMLogger.cpp>");
}
void CRHMLogger :: log_to_console (std :: string msg)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMLogger::log_to_console(std :: string msg)@@@CRHMLogger.cpp>");
    this -> consoleLogger -> critical (msg);
    this -> consoleLogger -> flush ();
InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::log_to_console(std :: string msg)@@@CRHMLogger.cpp>");
}
void CRHMLogger :: log_run_error (CRHMException exception)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMLogger::log_run_error(CRHMException exception)@@@CRHMLogger.cpp>");
    switch (exception.Kind) {
    case TExcept :: TERMINATE:
        SPDLOG_LOGGER_CRITICAL (this -> runLogger, exception.Message);
        break;
    case TExcept :: ERR:
        SPDLOG_LOGGER_ERROR (this -> runLogger, exception.Message);
        break;
    case TExcept :: WARNING:
        SPDLOG_LOGGER_WARN (this -> runLogger, exception.Message);
        break;
    default:
        SPDLOG_LOGGER_ERROR (this -> runLogger, exception.Message);
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::log_run_error(CRHMException exception)@@@CRHMLogger.cpp>");
}
void CRHMLogger :: log_run_message (std :: string msg)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMLogger::log_run_message(std :: string msg)@@@CRHMLogger.cpp>");
    SPDLOG_LOGGER_INFO (this -> runLogger, msg);
InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::log_run_message(std :: string msg)@@@CRHMLogger.cpp>");
}
void CRHMLogger :: log_run_debug_message (std :: string msg)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMLogger::log_run_debug_message(std :: string msg)@@@CRHMLogger.cpp>");
    SPDLOG_LOGGER_DEBUG (this -> runLogger, msg);
InstrumentLogger::instance()->log_instrument_log("</CRHMLogger::log_run_debug_message(std :: string msg)@@@CRHMLogger.cpp>");
}