// file      : carbon/common/utils.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include "carbon/backend.hpp"
#include "template_types.hpp"

#include <cassert>
#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <spdlog/fmt/fmt.h>

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

		/**
		 * @brief Compares a string to a Vulkan extension properties structure.
		 * @param str The string to compare.
		 * @param propStruct The Vulkan extension properties structure to compare.
		 * @returns 0 if equal, < 0 if `str` comes alphabetically before `propStruct` and > 0 otherwise.
		 */
		i32 compare(const char *str, const VkExtensionProperties &propStruct);

		/**
		 * @brief Compares a string to a Vulkan layer properties structure.
		 * @param str The string to compare.
		 * @param propStruct The Vulkan layer properties structure to compare.
		 * @returns 0 if equal, < 0 if `str` comes alphabetically before `propStruct` and > 0 otherwise.
		 */
		i32 compare(const char *str, const VkLayerProperties &propStruct);

		/**
		 * @brief Performs the greatest common divisor algorithm on the two inputs.
		 * @returns The greatest common divisor between `x` and `y`.
		 */
		i32 gcd(i32 x, i32 y);

		/**
		 * @brief Calculates the estimated aspect ratio as a string in the form `width:height`.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 * @returns The estimated aspect ratio as a string in the form `width:height`.
		 */
		std::string getEstimatedAspectRatio(i32 width, i32 height);

		/**
		 * @brief Converts the given vector into a string representation of
		 * the vector.
		 * @param vector The vector of arbitrary length and type to convert
		 * to string.
		 * @returns The vector as (x, y[, ...]) in string form.
		 */
		template<glm::length_t L, typename T, enum glm::qualifier Q>
		const std::string showVector(const glm::vec<L, T, Q> &vector) {
			switch (L) {
				case 1:
					return fmt::format("({})", vector[0]);
				case 2:
					return fmt::format("({}, {})", vector[0], vector[1]);
				case 3:
					return fmt::format("({}, {}, {})", vector[0], vector[1], vector[2]);
				case 4:
					return fmt::format("({}, {}, {}, {})", vector[0], vector[1], vector[2], vector[3]);
				default:
					return "()";
			}
		}

		/**
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
