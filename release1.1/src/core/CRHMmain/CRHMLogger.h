#pragma once

#define SPDLOG_ACTIVE_LEVEL ACTIVE_LOG_LEVEL

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "../Common/CRHMException.h"

class CRHMLogger
{

	std::shared_ptr<spdlog::logger> runLogger;
	static CRHMLogger* s_instance;

	CRHMLogger();

public:

	static CRHMLogger* instance();

	std::shared_ptr<spdlog::logger> get_run_logger();

	void log_run_error(CRHMException exception);

};
