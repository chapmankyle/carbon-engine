// file      : carbon/common/logger.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "logger.hpp"

#include <spdlog/fmt/chrono.h>

namespace carbon {

	// initial definitions

	std::string Logger::m_date_time_format = "%Y-%m-%d";

	std::shared_ptr<spdlog::logger> Logger::m_console = nullptr;
	std::shared_ptr<spdlog::logger> Logger::m_file = nullptr;


	std::string Logger::getDateTime(const std::string &format) {
		std::time_t now = std::time(nullptr);
		std::string dateFormat = fmt::format("{}{}{}", "{:", format, "}");

		// format time using thread-safe fmt::localtime
		return fmt::format(dateFormat, fmt::localtime(now));
	}


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
			const std::string date = getDateTime(m_date_time_format);

			// construct full log file name
			std::string fileName = fmt::format("{}.{}.log", CARBON_ENGINE_LOG_PREFIX, date);

			// use separator based on operating system and construct full path
			char sep = (CARBON_PLATFORM == CARBON_PLATFORM_WINDOWS) ? '\\' : '/';
			std::string logPath = fmt::format("{}{}{}", paths::logsPath(), sep, fileName);

			// create logger
			m_file = spdlog::basic_logger_mt<spdlog::async_factory>(
				"file",
				logPath
			);

			// set global pattern
			spdlog::set_pattern("[%H:%M:%S] [%^%=7l%$] [thread %5t] %v");

			// output that logger has been initialized
			m_file->info("-------------------");
			m_file->info("Logger initialized.");
			m_file->info("-------------------");
		}
	}


	void Logger::log(const log::To &out, const log::State &state, const std::string &msg) {
		assert(m_console && m_file && "Logger has not been initialized. Call `init` method before anything else.");

		// check log output
		switch (out) {
			case log::To::Console:
				switch (state) {
					case log::State::Info:
						m_console->info(msg);
						break;
					case log::State::Warn:
						m_console->warn(msg);
						break;
					case log::State::Error:
						m_console->error(msg);
						break;
					case log::State::Fatal:
						m_console->error(msg);
						throw std::runtime_error(msg);
					default:
						throw std::runtime_error("Log state not recognized!");
				}
				break;
			case log::To::File:
				switch (state) {
					case log::State::Info:
						m_file->info(msg);
						break;
					case log::State::Warn:
						m_file->warn(msg);
						break;
					case log::State::Error:
						m_file->error(msg);
						break;
					case log::State::Fatal:
						m_file->error(msg);
						throw std::runtime_error(msg);
					default:
						throw std::runtime_error("Log state not recognized!");
				}
				break;
			default:
				throw std::runtime_error("Log output not recognized!");
		}
	}

} // namespace carbon
