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
#pragma once

#define SPDLOG_ACTIVE_LEVEL ACTIVE_LOG_LEVEL

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "CRHMException.h"

class CRHMLogger
{

	std::shared_ptr<spdlog::logger> runLogger;

	std::shared_ptr<spdlog::logger> consoleLogger;

	static CRHMLogger* s_instance;

	CRHMLogger();

public:

	static CRHMLogger* instance();

	std::shared_ptr<spdlog::logger> get_run_logger();

	void log_to_console(std::string msg);

	void log_run_error(CRHMException exception);

	void log_run_message(std::string msg);

	void log_run_debug_message(std::string msg);

};
