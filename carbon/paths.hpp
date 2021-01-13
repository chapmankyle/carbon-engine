// file      : carbon/paths.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef PATHS_HPP
#define PATHS_HPP

#include "macros.hpp"
#include "platform.hpp"

#include <filesystem>
#include <string>

namespace carbon {

	namespace paths {

		/**
		 * @brief Absolute path of where the executable is being run from.
		 * Contains '\\' when in Windows and '/' otherwise.
		 */
		static inline const std::string CURRENT_PATH = std::filesystem::current_path().string();

		// Anonymous namespace since functions in here are not necessary
		namespace {

			/**
			 * @returns The root directory of the engine.
			 */
			static const std::string _getRoot() {
				// copy variable into editable string
				std::string curr = ::carbon::paths::CURRENT_PATH;
				size_t idx = curr.find(CARBON_ENGINE_DIR_NAME);

				// some error occurred if cannot find root directory
				if (idx == std::string::npos) {
					return ::carbon::paths::CURRENT_PATH;
				}

				// remove subdirectories from end of string
				curr = curr.substr(0, idx + CARBON_ENGINE_DIR_NAME_LEN);

				// append trailing slash depending on operating system
				if (CARBON_PLATFORM == CARBON_PLATFORM_WINDOWS) {
					curr.append("\\");
				} else {
					curr.append("/");
				}

				return curr;
			}

		}

		/**
		 * @brief Absolute path of the `NAME_ROOT_DIR` directory.
		 * Includes trailing slash, which is '\\' in Windows and '/' otherwise.
		 */
		static inline const std::string ROOT_DIR = _getRoot();

		/**
		 * @returns Path where the assets for the engine reside.
		 */
		static const std::string assetsPath() {
			return ROOT_DIR + "assets";
		}

		/**
		 * @returns Path where the log files for the engine reside.
		 */
		static const std::string logsPath() {
			return ROOT_DIR + "logs";
		}

		/**
		 * @returns Path where the generated binary files for the engine reside.
		 */
		static const std::string binaryPath() {
			return ROOT_DIR + "x64";
		}

		/**
		 * @returns `true` if the directory was made, `false` otherwise.
		 */
		static bool makeDir(const char *dir) {
			std::filesystem::path path{ dir };
			return std::filesystem::create_directory(path);
		}

		/**
		 * @returns `true` if the directory was made, `false` otherwise.
		 */
		static bool makeDir(const std::string &dir) {
			return makeDir(dir.c_str());
		}

		/**
		 * @returns `true` if the directory exists, `false` otherwise.
		 */
		static bool dirExists(const char *dir) {
			std::filesystem::path path{ dir };
			return std::filesystem::is_directory(path);
		}

		/**
		 * @returns `true` if the directory exists, `false` otherwise.
		 */
		static bool dirExists(const std::string &dir) {
			return dirExists(dir.c_str());
		}

	} // namespace paths

} // namespace carbon

#endif // PATHS_HPP
