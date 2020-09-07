#pragma once

#ifndef COMMON_DEBUG_MESSENGER_HPP
#define COMMON_DEBUG_MESSENGER_HPP

#include <iostream>
#include <vulkan/vulkan.h>

#include "carbon/setup.hpp"

namespace carbon {

	class DebugMessenger {

	private:

		/*
		 * @brief Handle on VkInstance associated with debug utils messenger.
		 */
		VkInstance m_instance{ VK_NULL_HANDLE };

		/*
		 * @brief Handle on debug messenger.
		 */
		VkDebugUtilsMessengerEXT m_debug_messenger{ VK_NULL_HANDLE };

		/*
		 * @brief Handle on create info struct.
		 */
		VkDebugUtilsMessengerCreateInfoEXT m_create_info;

		/*
		 * @brief Callback function to display debug messages when validation layers
		 * are turned on.
		 * @param messageSeverity Severity of the message (`VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT`,
		 * `VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT`, `VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT` or
		 * `VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT`)
		 * @param messageType Indicates what type of message has been generated (`VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT`,
		 * `VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT` or `VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT`)
		 * @param pCallbackData Refers to struct containing details of the message.
		 * @param pUserData Pointer to allow user to pass data into.
		 * @returns `true` if the Vulkan call that triggered validation layer message should be aborted
		 */
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
			const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
			void *pUserData
		);

		/*
		 * @brief Populates the debug messenger struct.
		 * @param createInfo The struct to fill with default data.
		 */
		void fillDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

	public:

		/*
		 * @brief Initializes a debug messenger.
		 * @param inst The instance to link to the debug messenger.
		 */
		DebugMessenger(const VkInstance &instance);

		/*
		 * @brief Default constructor for debug messenger.
		 */
		DebugMessenger();

		/*
		 * @brief Destructor for the debug messenger.
		 */
		~DebugMessenger();

		/*
		 * @brief Destroys the debug messenger.
		 */
		void destroy();

		/*
		 * @returns The underlying VkInstance.
		 */
		VkInstance getInstance();

		/*
		 * @returns A handle on the VkDebugUtilsMessengerEXT.
		 */
		VkDebugUtilsMessengerEXT getHandle();

		/*
		 * @returns A handle on the VkDebugUtilsMessengerCreateInfoEXT.
		 */
		VkDebugUtilsMessengerCreateInfoEXT getCreateInfo();

		/*
		 * @brief Sets the create info struct for the debug messenger.
		 * @param createInfo The new createInfo struct.
		 */
		void setCreateInfo(const VkDebugUtilsMessengerCreateInfoEXT &createInfo);

	};

} // namespace carbon

#endif // COMMON_DEBUG_MESSENGER_HPP
