#pragma once

#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <cstring>
#include <cassert>
#include <vector>

#include "carbon/setup.hpp"
#include "template_types.hpp"

namespace carbon {

	namespace utils {

		/**
		 * @brief Stores application version information.
		 */
		struct version {
			uint32_t major{ 1 };
			uint32_t minor{ 0 };
			uint32_t patch{ 0 };
		};

		/*
		 * @returns The device extensions that are required by the engine.
		 */
		static const std::vector<const char *> getRequiredDeviceExtensions() {
			return std::vector<const char *>{
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};
		}

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
		int32_t compare(const char *str, const VkExtensionProperties &propStruct);

		/*
		 * @brief Compares a string to a Vulkan layer properties structure.
		 * @param str The string to compare.
		 * @param propStruct The Vulkan layer properties structure to compare.
		 * @returns 0 if equal, < 0 if `str` comes alphabetically before `propStruct` and > 0 otherwise.
		 */
		int32_t compare(const char *str, const VkLayerProperties &propStruct);

		/*
		 * @brief Checks if the required strings are available.
		 * @tparam T The type of the Vulkan properties structure (e.g. VkExtensionProperties).
		 * @returns `true` if all required strings are present in the available struct, `false` otherwise.
		 */
		template<class T>
		bool containsRequired(
			const std::vector<const char *> required,
			const std::vector<T> available
		) {
			// ensure type is correct
			assert(carbon::types::is_supported_properties_struct<T>::value);
			bool found;

			for (const auto &req : required) {
				found = false;

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

#endif // !COMMON_UTILS_HPP

