// file      : carbon/common/logger.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <sstream>

namespace carbon {

	// initial definitions

	std::string Logger::m_date_time_format = "%Y-%m-%d";

	std::shared_ptr<spdlog::logger> Logger::m_console = nullptr;
	std::shared_ptr<spdlog::logger> Logger::m_file = nullptr;


	std::string Logger::getDateTime(const std::string &format) {
		// get current time
		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm time{};
		
		// check platform
#if CARBON_PLATFORM == CARBON_PLATFORM_WINDOWS
		localtime_s(&time, &now);
#elif CARBON_PLATFORM == CARBON_PLATFORM_UNIX
		localtime_r(&now, &time);
#else 
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
		time = *std::localtime(&now);
#endif

		// convert to format
		std::ostringstream oss;
		oss << std::put_time(&time, format.c_str());

		return oss.str();
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
			spdlog::set_pattern("[%H:%M:%S] [%^%=7l%$] [thread %5t] %v");

			// output that logger has been initialized
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
