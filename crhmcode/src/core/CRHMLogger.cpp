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
#include "CRHMLogger.h"
#include <iostream>

CRHMLogger* CRHMLogger::s_instance = 0;

CRHMLogger::CRHMLogger()
{
    try
    {
        auto logger = spdlog::rotating_logger_st("run_log", "crhmRun.log", 1024 * 1024 * 10, 5);
        logger->set_level(spdlog::level::level_enum::trace);
        this->runLogger = logger;
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed for run logger: " << ex.what() << std::endl;
        exit(1);
    }

    try
    {
        auto console = spdlog::stdout_color_st("console");
        console->set_pattern("%v");
        this->consoleLogger = console;
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed for console logger: " << ex.what() << std::endl;
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

void CRHMLogger::log_to_console(std::string msg)
{
    this->consoleLogger->critical(msg);
    this->consoleLogger->flush();
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
