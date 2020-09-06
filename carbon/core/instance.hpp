#pragma once

#ifndef CORE_INSTANCE_HPP
#define CORE_INSTANCE_HPP

#include <vector>

#include "../common/utils.hpp"
#include "../common/debug_messenger.hpp"

namespace carbon {

	class Instance {

	private:

		/*
		 * @brief Handle to underlying Vulkan instance.
		 */
		VkInstance handle{ VK_NULL_HANDLE };

		/*
		 * @brief Debug messenger for validation layers.
		 */
		DebugUtilsMessenger debugMessenger;

		/*
		 * @brief The enabled extensions on the current instance.
		 */
		std::vector<const char *> enabledExtensions;

	public:

		/*
		 * @brief Initializes a Vulkan instance.
		 * @param appName The name of the application.
		 * @param version The version of the application.
		 * @param requiredValidationLayers The validation layers required by the application.
		 * @param requiredExtensions The extensions required by the application.
		 */
		Instance(
			const char* appName,
			const carbon::utils::version &version,
			const std::vector<const char *> &requiredValidationLayers,
			const std::vector<const char *> &requiredExtensions
		);

		/*
		 * @brief Destorys the Vulkan instance.
		 */
		~Instance();

		/*
		 * @returns Underlying VkInstance object.
		 */
		VkInstance getHandle();

		/*
		 * @returns The handle on the debug messenger used in this instance.
		 */
		DebugUtilsMessenger getDebugMessenger();

	};

} // namespace carbon

#endif // CORE_INSTANCE_HPP

