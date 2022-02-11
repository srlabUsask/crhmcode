#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class InstrumentLogger
{

	std::shared_ptr<spdlog::logger> instrumentLogger;

	static InstrumentLogger* s_instance;

	InstrumentLogger();

public:

	static InstrumentLogger* instance();

	std::shared_ptr<spdlog::logger> get_instrument_logger();

	void log_instrument_log(std::string msg);

};
