#include "CRHMLogger.h"
#include <iostream>

CRHMLogger* CRHMLogger::s_instance = 0;

CRHMLogger::CRHMLogger()
{
    try
    {
        auto logger = spdlog::rotating_logger_st("run_log", "crhmRun.log", 1024 * 1024 * 10, 5, true);
        logger->set_level(spdlog::level::level_enum::trace);
        runLogger = logger;
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed for base logger: " << ex.what() << std::endl;
        exit(1);
    }
}


CRHMLogger* CRHMLogger::instance()
{
    if (!s_instance)
        s_instance = new CRHMLogger;
    return s_instance;
}

std::shared_ptr<spdlog::logger> CRHMLogger::get_run_logger()
{
    return runLogger;
}

void CRHMLogger::log_run_error(CRHMException exception)
{

    switch (exception.Kind) 
    {
        case TExcept::TERMINATE:
            SPDLOG_LOGGER_CRITICAL(this->runLogger, exception.Message);
            break;
        case TExcept::ERR:
            SPDLOG_LOGGER_ERROR(this->runLogger, exception.Message);
            break;
        case TExcept::WARNING:
            SPDLOG_LOGGER_WARN(this->runLogger, exception.Message);
            break;
        default:
            SPDLOG_LOGGER_ERROR(this->runLogger, exception.Message);
            break;
    }

}

void CRHMLogger::log_run_message(std::string msg) 
{
    SPDLOG_LOGGER_INFO(this->runLogger, msg);
}

void CRHMLogger::log_run_debug_message(std::string msg)
{
    SPDLOG_LOGGER_DEBUG(this->runLogger, msg);
}
