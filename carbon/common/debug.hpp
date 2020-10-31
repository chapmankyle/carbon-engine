// file      : carbon/common/debug.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef COMMON_DEBUG_HPP
#define COMMON_DEBUG_HPP

#include "carbon/setup.hpp"

namespace carbon {

	namespace debug {

		/**
		 * @brief Callback function to display debug messages when validation
		 * layers are turned on.
		 *
		 * @param messageSeverity Severity of the message
		 * `VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT`,
		 * `VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT`,
		 * `VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT` or
		 * `VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT`
		 *
		 * @param messageType Which type of message has been generated
		 * `VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT`,
		 * `VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT` or
		 * `VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT`
		 *
		 * @param pCallbackData Refers to struct containing details of the message.
		 * @param pUserData Pointer to allow user to pass data into.
		 * @returns `true` if the Vulkan call that triggered validation layer
		 * message should be aborted, `false` otherwise.
		 */
		static VKAPI_ATTR VkBool32 VKAPI_CALL messengerCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT msgSeverity,
			VkDebugUtilsMessageTypeFlagsEXT msgType,
			const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
			void *pUserData
		);

		/**
		 * @brief Populates the debug messenger create info struct.
		 */
		void fillMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

		/**
		 * @brief Creates a debug messenger and attaches it to an instance.
		 * @returns `VK_SUCCESS` if successful.
		 */
		VkResult createMessenger(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
			const VkAllocationCallbacks *pAllocator,
			VkDebugUtilsMessengerEXT *pDebugMessenger
		);

		/**
		 * @brief Destroys the debug messenger.
		 */
		void destroyMessenger(
			VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
			const VkAllocationCallbacks *pAllocator
		);

	} // namespace debug

} // namespace carbon

#endif // COMMON_DEBUG_HPP
