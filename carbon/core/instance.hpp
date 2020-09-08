#pragma once

#ifndef CORE_INSTANCE_HPP
#define CORE_INSTANCE_HPP

#include <vector>

#include "carbon/common/utils.hpp"
#include "carbon/common/debug_messenger.hpp"

namespace carbon {

	class Instance {

	private:

		/*
		 * @brief Handle to underlying Vulkan instance.
		 */
		VkInstance m_handle;

		/*
		 * @brief Debug messenger for validation layers.
		 */
		DebugMessenger m_debug_messenger;

		/*
		 * @brief The enabled extensions on the current instance.
		 */
		std::vector<const char *> m_enabled_extensions;

		/*
		 * @brief Checks for default support of layers and extensions.
		 */
		void checkSupport();

		/*
		 * @brief Populates the application info struct.
		 */
		void fillApplicationInfo(
			VkApplicationInfo &appInfo,
			const char *appName,
			const carbon::utils::version &version
		);

		/*
		 * @brief Populates the instance info struct.
		 */
		void fillInstanceCreateInfo(
			VkInstanceCreateInfo &instInfo,
			const VkApplicationInfo &appInfo,
			const std::vector<const char *> &extensions,
			const std::vector<const char *> &validationLayers
		);

	public:

		/*
		 * @brief Initializes a Vulkan instance, using the default required
		 * extensions and validation layers.
		 * @param appName The name of the application.
		 * @param version The version of your application.
		 */
		Instance(const char *appName, const carbon::utils::version &version);

		/*
		 * @brief Destructor for the Vulkan instance.
		 */
		~Instance();

		/*
		 * @brief Destroys the Vulkan instance.
		 */
		void destroy();

		/*
		 * @returns Underlying VkInstance object.
		 */
		VkInstance getHandle();

		/*
		 * @returns The handle on the debug messenger used in this instance.
		 */
		DebugMessenger getDebugMessenger();

		/*
		 * @returns The currently enabled extensions on the instance.
		 */
		std::vector<const char *> getExtensions();

	};

} // namespace carbon

#endif // CORE_INSTANCE_HPP

