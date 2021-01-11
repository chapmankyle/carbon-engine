// file      : carbon/common/logger.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef COMMON_LOGGER_HPP
#define COMMON_LOGGER_HPP

#include "carbon/paths.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace carbon {

	namespace log {

		/**
		 * @brief Enum indicating where to log to.
		 */
		enum class To {
			Console = 0,
			File
		};

		/**
		 * @brief Enum to show the type of log to produce.
		 */
		enum class State {
			Info = 0,
			Warn,
			Error,
			Fatal
		};

	} // namespace log

	/**
	 * @brief Class that allows logging to both console and file.
	 */
	class Logger {

	protected:

		/**
		 * @brief The format to use for date and time.
		 */
		static std::string m_date_time_format; 
		
		/**
		 * @brief Pointer to console used for logging.
		 */
		static std::shared_ptr<spdlog::logger> m_console;

		/**
		 * @brief Pointer to file used for logging.
		 */
		static std::shared_ptr<spdlog::logger> m_file;

		/**
		 * @brief Formats the current date and time as a single string 
		 * in the format specified.
		 * @param format The format of the date and time.
		 * @returns The date and time as a formatted string.
		 */
		std::string getDateTime(const std::string &format);

	public:

		Logger() = default;

		/**
		 * @brief Initializes the logger.
		 * Must be called before calling any logging methods.
		 */
		void init();

		/**
		 * @brief Logs a message of the given state to the output specified.
		 * @param out Where to log the message to.
		 * @param state The state of the log.
		 * @param msg The message to log.
		 */
		static void log(const log::To &out, const log::State &state, const std::string &msg);

		/**
		 * @returns Pointer to logger used for console logging.
		 */
		static std::shared_ptr<spdlog::logger>& getConsole() {
			return m_console;
		}

		/**
		 * @returns Pointer to logger used for file logging.
		 */
		static std::shared_ptr<spdlog::logger>& getFile() {
			return m_file;
		}

	};

} // namespace carbon

// debug messages are ON
#ifndef CARBON_DISABLE_DEBUG

#	define CARBON_LOG_INFO(to, ...) carbon::Logger::log(to, carbon::log::State::Info, ##__VA_ARGS__)
#	define CARBON_LOG_WARN(to, ...) carbon::Logger::log(to, carbon::log::State::Warn, ##__VA_ARGS__)
#	define CARBON_LOG_ERROR(to, ...) carbon::Logger::log(to, carbon::log::State::Error, ##__VA_ARGS__)
#	define CARBON_LOG_FATAL(to, ...) carbon::Logger::log(to, carbon::log::State::Fatal, ##__VA_ARGS__)

// debug messages are OFF
#else

#	define CARBON_LOG_INFO(to, ...) 
#	define CARBON_LOG_WARN(to, ...) 
#	define CARBON_LOG_ERROR(to, ...) 
#	define CARBON_LOG_FATAL(to, ...) carbon::Logger::log(to, carbon::log::State::Fatal, ##__VA_ARGS__)

#endif // CARBON_DISABLE_DEBUG

#endif // COMMON_LOGGER_HPP
