#pragma once

#ifndef CORE_INSTANCE_HPP
#define CORE_INSTANCE_HPP

#include <vector>

#include "carbon/common/debug.hpp"
#include "carbon/common/utils.hpp"

namespace carbon {

	class Instance {

	private:

		/**
		 * @brief The required validation layers.
		 */
		const std::vector<const char *> m_req_validation_layers{
			"VK_LAYER_KHRONOS_validation"
		};

		/**
		 * @returns The extensions required by GLFW.
		 */
		const std::vector<const char *> getRequiredInstanceExtensions();

		/**
		 * @brief The required instance extensions.
		 */
		const std::vector<const char *> m_req_instance_extensions{
			getRequiredInstanceExtensions()
		};

		/**
		 * @brief Handle to underlying Vulkan instance.
		 */
		VkInstance m_handle{ VK_NULL_HANDLE };

		/**
		 * @brief The debug messenger to use if validation layers are enabled.
		 */
		VkDebugUtilsMessengerEXT m_debug_messenger{ VK_NULL_HANDLE };

		/**
		 * @brief The CreateInfo struct for the debug messenger.
		 */
		VkDebugUtilsMessengerCreateInfoEXT m_debug_create_info;

		/**
		 * @brief The enabled validation layers on the current instance.
		 */
		std::vector<const char *> m_enabled_validation_layers;

		/**
		 * @brief The enabled extensions on the current instance.
		 */
		std::vector<const char *> m_enabled_extensions;

		/**
		 * @returns `true` if validation layers are supported, `false` otherwise.
		 */
		bool hasValidationLayerSupport();

		/**
		 * @returns `true` if the extensions are supported, `false` otherwise.
		 */
		bool hasExtensionSupport();

		/**
		 * @brief Checks for default support of layers and extensions.
		 */
		void checkSupport();

		/**
		 * @brief Populates the application info struct.
		 */
		void fillApplicationInfo(
			VkApplicationInfo &appInfo,
			const char *appName,
			const carbon::utils::version &version
		);

		/**
		 * @brief Populates the instance info struct.
		 */
		void fillInstanceCreateInfo(
			VkInstanceCreateInfo &instInfo,
			const VkApplicationInfo &appInfo
		);

	public:

		/**
		 * @brief Initializes a Vulkan instance, using the default required
		 * extensions and validation layers.
		 * @param appName The name of the application.
		 * @param version Optional. The version of your application.
		 */
		Instance(const char *appName, const carbon::utils::version &version = { 1, 0, 0 });

		/**
		 * @brief Destructor for the Vulkan instance.
		 */
		~Instance();

		/**
		 * @brief Destroys the Vulkan instance.
		 */
		void destroy();

		/**
		 * @returns Underlying VkInstance object.
		 */
		const VkInstance getHandle() const;

		/**
		 * @returns The enabled validation layers that will be used if
		 * `CARBON_DISABLE_DEBUG` is not defined.
		 */
		const std::vector<const char *> getEnabledValidationLayers() const;

		/**
		 * @returns The currently enabled extensions on the instance.
		 */
		const std::vector<const char *> getEnabledExtensions() const;

	};

} // namespace carbon

#endif // CORE_INSTANCE_HPP
