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
			// construct path by detecting platform
			std::string logPath = (CARBON_PLATFORM == CARBON_PLATFORM_WINDOWS)
				? paths::logsPath() + "\\" + CARBON_ENGINE_LOG_NAME
				: paths::logsPath() + "/" + CARBON_ENGINE_LOG_NAME;

			// create logger
			m_file = spdlog::basic_logger_mt<spdlog::async_factory>(
				"file",
				logPath
			);

			// set global pattern
			spdlog::set_pattern("[%H:%M:%S] [%^%=5l%$] [thread %t] %v");
		}
	}

} // namespace carbon
