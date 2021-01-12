// file      : carbon/common/debug.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "debug.hpp"

#include "logger.hpp"

namespace carbon {

	namespace debug {

		static VKAPI_ATTR VkBool32 VKAPI_CALL messengerCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT msgSeverity,
			VkDebugUtilsMessageTypeFlagsEXT msgType,
			const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
			void *pUserData
		) {
			// ensure proper logging
			switch (msgSeverity) {
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
					if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
						CARBON_LOG_INFO(carbon::log::To::File, fmt::format("=General= {}", pCallbackData->pMessage));
						CARBON_LOG_INFO(carbon::log::To::Console, fmt::format("=General= {}", pCallbackData->pMessage));
					} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
						CARBON_LOG_INFO(carbon::log::To::File, fmt::format("=Validation= {}", pCallbackData->pMessage));
						CARBON_LOG_INFO(carbon::log::To::Console, fmt::format("=Validation= {}", pCallbackData->pMessage));
					} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
						CARBON_LOG_INFO(carbon::log::To::File, fmt::format("=Performance= {}", pCallbackData->pMessage));
						CARBON_LOG_INFO(carbon::log::To::Console, fmt::format("=Performance= {}", pCallbackData->pMessage));
					}
					break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
					if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
						CARBON_LOG_WARN(carbon::log::To::File, fmt::format("=General= {}", pCallbackData->pMessage));
						CARBON_LOG_WARN(carbon::log::To::Console, fmt::format("=General= {}", pCallbackData->pMessage));
					} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
						CARBON_LOG_WARN(carbon::log::To::File, fmt::format("=Validation= {}", pCallbackData->pMessage));
						CARBON_LOG_WARN(carbon::log::To::Console, fmt::format("=Validation= {}", pCallbackData->pMessage));
					} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
						CARBON_LOG_WARN(carbon::log::To::File, fmt::format("=Performance= {}", pCallbackData->pMessage));
						CARBON_LOG_WARN(carbon::log::To::Console, fmt::format("=Performance= {}", pCallbackData->pMessage));
					}
					break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
					if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
						CARBON_LOG_ERROR(carbon::log::To::File, fmt::format("=General= {}", pCallbackData->pMessage));
						CARBON_LOG_ERROR(carbon::log::To::Console, fmt::format("=General= {}", pCallbackData->pMessage));
					} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
						CARBON_LOG_ERROR(carbon::log::To::File, fmt::format("=Validation= {}", pCallbackData->pMessage));
						CARBON_LOG_ERROR(carbon::log::To::Console, fmt::format("=Validation= {}", pCallbackData->pMessage));
					} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
						CARBON_LOG_ERROR(carbon::log::To::File, fmt::format("=Performance= {}", pCallbackData->pMessage));
						CARBON_LOG_ERROR(carbon::log::To::Console, fmt::format("=Performance= {}", pCallbackData->pMessage));
					}
					break;
			}

			return VK_FALSE;
		}


		void fillMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT *createInfo) {
			initStruct(*createInfo, VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT);

			createInfo->messageSeverity =
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

			createInfo->messageType =
				VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

			createInfo->pfnUserCallback = messengerCallback;
			createInfo->pUserData = nullptr;
		}


		VkResult createMessenger(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
			const VkAllocationCallbacks *pAllocator,
			VkDebugUtilsMessengerEXT *pDebugMessenger
		) {
			// get function since it is external (not loaded in Vulkan initially)
			auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
				vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT")
			);

			// function has been loaded
			if (func != nullptr) {
				return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
			}

			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}


		void destroyMessenger(
			VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
			const VkAllocationCallbacks *pAllocator
		) {
			// get function to destroy debug messenger
			auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
				vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT")
			);

			// function has been loaded
			if (func != nullptr) {
				func(instance, debugMessenger, pAllocator);
			}
		}

	} // namespace debug

} // namespace carbon
