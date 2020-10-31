// file      : carbon/common/utils.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <cassert>
#include <cstring>
#include <vector>

#include "carbon/setup.hpp"
#include "template_types.hpp"

namespace carbon {

	namespace utils {

		/**
		 * @brief Stores application version information.
		 */
		struct version {
			u32 major = 1;
			u32 minor = 0;
			u32 patch = 0;
		};

		/**
		 * @brief Requests the validation layers that are supported on the current machine.
		 * @returns The validation layer properties for each supported validation layer.
		 */
		const std::vector<VkLayerProperties> getSupportedValidationLayers();

		/**
		 * @brief Requests the extensions that are supported on the current machine.
		 * @returns The extension properties for each supported extension.
		 */
		const std::vector<VkExtensionProperties> getSupportedExtensions();

		/*
		 * @brief Compares a string to a Vulkan extension properties structure.
		 * @param str The string to compare.
		 * @param propStruct The Vulkan extension properties structure to compare.
		 * @returns 0 if equal, < 0 if `str` comes alphabetically before `propStruct` and > 0 otherwise.
		 */
		i32 compare(const char *str, const VkExtensionProperties &propStruct);

		/*
		 * @brief Compares a string to a Vulkan layer properties structure.
		 * @param str The string to compare.
		 * @param propStruct The Vulkan layer properties structure to compare.
		 * @returns 0 if equal, < 0 if `str` comes alphabetically before `propStruct` and > 0 otherwise.
		 */
		i32 compare(const char *str, const VkLayerProperties &propStruct);

		/*
		 * @brief Checks if the required strings are available.
		 * @tparam T The type of the Vulkan properties structure (e.g. VkExtensionProperties).
		 * @returns `true` if all required strings are present in the available struct, `false` otherwise.
		 */
		template<class T>
		bool containsRequired(const std::vector<const char *> required, const std::vector<T> available) {
			// ensure type is correct
			assert(carbon::types::is_supported_properties_struct<T>::value && "[ERROR] `containsRequired` template parameter not supported.");
			bool found;

			for (const auto &req : required) {
				found = false;

				// compare each available type
				for (const auto &a : available) {
					if (compare(req, a) == 0) {
						found = true;
						break;
					}
				}

				if (!found) {
					return false;
				}
			}

			return true;
		}

	} // namespace utils

} // namespace carbon

#endif // COMMON_UTILS_HPP
