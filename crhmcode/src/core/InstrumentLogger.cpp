#include "InstrumentLogger.h"
#include <iostream>

InstrumentLogger* InstrumentLogger::s_instance = 0;

InstrumentLogger::InstrumentLogger()
{
    try
    {
        auto logger = spdlog::basic_logger_mt("instrumentLogger", "callLog.log");
        this->instrumentLogger = logger;
        this->instrumentLogger->set_pattern("%v");

    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed for instrument logger: " << ex.what() << std::endl;
        exit(1);
    }
}


InstrumentLogger* InstrumentLogger::instance()
{
    if (!s_instance)
        s_instance = new InstrumentLogger;
    return s_instance;
}

std::shared_ptr<spdlog::logger> InstrumentLogger::get_instrument_logger()
{
    return instrumentLogger;
}

void InstrumentLogger::log_instrument_log(std::string msg)
{
    this->instrumentLogger->info(msg);
}
