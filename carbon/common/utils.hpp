#pragma once

#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <cstring>
#include <vector>

#include "carbon/setup.hpp"

namespace carbon {

	namespace utils {

		/*
		 * @brief Stores application version information.
		 */
		struct version {
			uint32_t major{ 1 };
			uint32_t minor{ 0 };
			uint32_t patch{ 0 };
		};

		/*
		 * @returns The validation layers that are required by the engine.
		 */
		static inline const std::vector<const char *> getRequiredValidationLayers() {
			return std::vector<const char *>{ "VK_LAYER_KHRONOS_validation" };
		}

		/*
		 * @returns The extensions that are required by the engine.
		 */
		inline const std::vector<const char *> getRequiredExtensions();

		/*
		 * @brief Requests the validation layers that are supported on the current machine.
		 * @returns The validation layer properties for each supported validation layer.
		 */
		inline const std::vector<VkLayerProperties> requestSupportedValidationLayers();

		/*
		 * @brief Requests the extensions that are supported on the current machine.
		 * @returns The extension properties for each supported extension.
		 */
		inline const std::vector<VkExtensionProperties> requestSupportedExtensions();

		/*
		 * @brief Checks if the required layers are available.
		 * @returns `true` if all required layers are available, `false` otherwise.
		 */
		bool containsRequired(const std::vector<const char *> &required, const std::vector<VkLayerProperties> &available);

		/*
		 * @brief Checks if the required extensions are available.
		 * @returns `true` if all required extensions are available, `false` otherwise.
		 */
		bool containsRequired(const std::vector<const char *> &required, const std::vector<VkExtensionProperties> &available);

		/*
		 * @brief Checks if all the required layers are available.
		 * @returns `true` if the required validation layers are supported, `false` otherwise.
		 */
		bool hasValidationLayerSupport();

		/*
		 * @brief Checks if all the required extensions are available.
		 * @returns `true` if the required extensions are supported, `false` otherwise.
		 */
		bool hasExtensionSupport();

	} // namespace utils

} // namespace carbon

#endif // !COMMON_UTILS_HPP

