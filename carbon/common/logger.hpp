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

	/**
	 * @brief Class that allows logging to both console and file.
	 */
	class Logger {

	protected:
		
		/**
		 * @brief Pointer to console used for logging.
		 */
		static std::shared_ptr<spdlog::logger> m_console;

		/**
		 * @brief Pointer to file used for logging.
		 */
		static std::shared_ptr<spdlog::logger> m_file;

	public:

		Logger() = default;

		/**
		 * @brief Initializes the logger.
		 * Must be called before calling any logging methods.
		 */
		static void init();

		/**
		 * @returns Pointer to logger used for console logging.
		 */
		static std::shared_ptr<spdlog::logger> getConsole() {
			return m_console;
		}

		/**
		 * @returns Pointer to logger used for file logging.
		 */
		static std::shared_ptr<spdlog::logger> getFile() {
			return m_file;
		}

	};

} // namespace carbon

#endif // COMMON_LOGGER_HPP
