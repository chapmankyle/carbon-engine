// file      : carbon/paths.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef PATHS_HPP
#define PATHS_HPP

#include <string>

namespace carbon {

	/**
	 * @brief Struct containing useful paths for the engine.
	 */
	struct Paths {

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
		 * @returns 1 if directory was successfully created, 0 or > 1 otherwise.
		 */
		static int makeDir(const char *dir);

		/**
		 * @returns `true` if the directory exists, `false` otherwise.
		 */
		static bool dirExists(const char *dir);

	};

} // namespace carbon

#endif // PATHS_HPP
