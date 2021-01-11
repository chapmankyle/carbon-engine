// file      : carbon/common/logger.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <mutex>

namespace carbon {

	// initial definitions

	std::string Logger::m_date_time_format = "%Y-%m-%d.%H:%M:%S";

	std::shared_ptr<spdlog::logger> Logger::m_console = nullptr;
	std::shared_ptr<spdlog::logger> Logger::m_file = nullptr;


	std::string Logger::getDateTime(const std::string &format) {
		// get current time
		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		// convert to date and time format
		std::string date(format.length() + 1, ' ');
		std::tm timeToFormat{};
		
		// check platform
#if CARBON_PLATFORM == CARBON_PLATFORM_WINDOWS
		localtime_s(&timeToFormat, &now);
#elif CARBON_PLATFORM == CARBON_PLATFORM_UNIX
		localtime_r(&now, &timeToFormat);
#else 
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
		timeToFormat = *std::localtime(&now);
#endif

		// format time
		std::strftime(&date[0], date.length(), format.c_str(), &timeToFormat);
		return date.substr(0, date.length() - 1);
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

			// construct path by detecting platform
			std::string logPath = (CARBON_PLATFORM == CARBON_PLATFORM_WINDOWS)
				? paths::logsPath() + "\\" + fileName
				: paths::logsPath() + "/" + fileName;

			// create logger
			m_file = spdlog::basic_logger_mt<spdlog::async_factory>(
				"file",
				logPath
			);

			// set global pattern
			spdlog::set_pattern("[%H:%M:%S] [%^%=5l%$] [thread %t] %v");
		}
	}


	void Logger::log(const log::To &out, const log::State &state, const std::string &msg) {
		// logger has not been initialized
		if (!m_console || !m_file) {
			init();
		}
	}

} // namespace carbon
