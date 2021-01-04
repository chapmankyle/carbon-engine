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
		 * @returns Directory where `carbon-engine` resides.
		 */
		static const std::string& rootDir();

		/**
		 * @returns Directory where the assets for the engine reside.
		 */
		static const std::string& assetsDir();

		/**
		 * @returns Directory where the log files for the engine reside.
		 */
		static const std::string& logsDir();

		/**
		 * @returns Directory where the generated binary files for the engine reside.
		 */
		static const std::string& binaryDir();

		/**
		 * @returns `true` if the directory was made, `false` otherwise.
		 */
		static bool makeDir(const char* dir) {
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
