// file      : carbon/paths.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef PATHS_HPP
#define PATHS_HPP

#include <filesystem>
#include <string>

namespace carbon {

	namespace paths {

		/**
		 * @brief Absolute path of where the executable is being run from.
		 * Contains '\\' when in Windows and '/' otherwise.
		 */
		static inline const std::string CURRENT_PATH = std::filesystem::current_path().string();

		/**
		 * @returns Path where the `carbon-engine` directory resides.
		 */
		static const std::string& rootPath();

		/**
		 * @returns Path where the assets for the engine reside.
		 */
		static const std::string& assetsPath();

		/**
		 * @returns Path where the log files for the engine reside.
		 */
		static const std::string& logsPath();

		/**
		 * @returns Path where the generated binary files for the engine reside.
		 */
		static const std::string& binaryPath();

		/**
		 * @returns `true` if the directory was made, `false` otherwise.
		 */
		static bool makeDir(const char *dir) {
			std::filesystem::path path{ dir };
			return std::filesystem::create_directory(path);
		}

		/**
		 * @returns `true` if the directory exists, `false` otherwise.
		 */
		static bool dirExists(const char *dir) {
			std::filesystem::path path{ dir };
			return std::filesystem::is_directory(path);
		}

	} // namespace paths

} // namespace carbon

#endif // PATHS_HPP
