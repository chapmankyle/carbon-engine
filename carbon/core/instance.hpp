// file      : carbon/core/instance.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef CORE_INSTANCE_HPP
#define CORE_INSTANCE_HPP

#include "carbon/common/debug.hpp"
#include "carbon/common/utils.hpp"

#include <string>

namespace carbon {

	/**
	 * @brief A wrapper for the Vulkan instance that represents the base
	 * graphics object.
	 */
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
		 * @brief `true` if validation layers are enabled, `false` otherwise.
		 */
		bool m_validation_enabled;

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
		Instance(const std::string appName, const carbon::utils::version &version = { 1, 0, 0 });

		/**
		 * @brief Default constructor for initializing a Vulkan instance.
		 */
		explicit Instance();

		/**
		 * @brief Destructor for the Vulkan instance.
		 */
		~Instance();

		/**
		 * @brief Destroys the Vulkan instance.
		 */
		void destroy();

		/**
		 * @returns The underlying `VkInstance`.
		 */
		const VkInstance& getHandle() const {
			return m_handle;
		}

		/**
		 * @returns `true` if the validation layers are enabled, `false` otherwise.
		 */
		bool isValidationEnabled() const {
			return m_validation_enabled;
		}

		/**
		 * @returns The enabled validation layers that will be used if
		 * `CARBON_DISABLE_DEBUG` is not defined.
		 */
		const std::vector<const char *> getEnabledValidationLayers() const {
			return m_enabled_validation_layers;
		}

		/**
		 * @returns The currently enabled extensions on the instance.
		 */
		const std::vector<const char *> getEnabledExtensions() const {
			return m_enabled_extensions;
		}

	};

} // namespace carbon

#endif // CORE_INSTANCE_HPP
