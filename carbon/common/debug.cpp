#include "debug.hpp"

static VKAPI_ATTR VkBool32 VKAPI_CALL carbon::debug::messengerCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT msgSeverity,
	VkDebugUtilsMessageTypeFlagsEXT msgType,
	const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
	void *pUserData
) {
	// ensure proper logging
	switch (msgSeverity) {
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
				std::cerr << "[INFO | General] " << pCallbackData->pMessage << '\n';
			} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
				std::cerr << "[INFO | Validation] " << pCallbackData->pMessage << '\n';
			} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
				std::cerr << "[INFO | Performance] " << pCallbackData->pMessage << '\n';
			}
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
				std::cerr << "[WARNING | General] " << pCallbackData->pMessage << '\n';
			} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
				std::cerr << "[WARNING | Validation] " << pCallbackData->pMessage << '\n';
			} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
				std::cerr << "[WARNING | Performance] " << pCallbackData->pMessage << '\n';
			}
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
				std::cerr << "[ERROR | General] " << pCallbackData->pMessage << '\n';
			} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
				std::cerr << "[ERROR | Validation] " << pCallbackData->pMessage << '\n';
			} else if (msgType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
				std::cerr << "[ERROR | Performance] " << pCallbackData->pMessage << '\n';
			}
			break;
	}

	return VK_FALSE;
}


void carbon::debug::fillMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
	carbon::initStruct(createInfo, VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT);

	createInfo.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	createInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	createInfo.pfnUserCallback = messengerCallback;
	createInfo.pUserData = nullptr;
}


VkResult carbon::debug::createMessenger(
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


void carbon::debug::destroyMessenger(
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
