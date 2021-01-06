// file      : carbon/common/logger.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "logger.hpp"

namespace carbon {

	// initial definitions

	std::shared_ptr<spdlog::logger> Logger::m_console = nullptr;
	std::shared_ptr<spdlog::logger> Logger::m_file = nullptr;


	void Logger::init() {
		// create directory if does not already exist
		if (!paths::dirExists(paths::logsPath())) {
			paths::makeDir(paths::logsPath());
		}

		// create console logger
		if (!m_console) {
			m_console = spdlog::stdout_color_mt("console");
		}

		// create async file logger
		if (!m_file) {
			std::string logPath;

			if (CARBON_PLATFORM == CARBON_PLATFORM_WINDOWS) {
				logPath = paths::logsPath() + "\\carbon.log";
			} else {
				logPath = paths::logsPath() + "/carbon.log";
			}

			// create logger
			m_file = spdlog::basic_logger_mt<spdlog::async_factory>(
				"file",
				logPath
			);
			spdlog::set_pattern("[%H:%M:%S] [%^%=5l%$] [thread %t] %v");
		}
	}

} // namespace carbon
