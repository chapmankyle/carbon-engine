#include "debug_messenger.hpp"

VKAPI_ATTR VkBool32 VKAPI_CALL carbon::DebugUtilsMessenger::debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
	void *pUserData
) {
	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
		std::cerr << "[WARNING ID " << pCallbackData->messageIdNumber << "] Validation layer: " << pCallbackData->pMessage << '\n';
	} else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
		std::cerr << "[ERROR ID " << pCallbackData->messageIdNumber << "] Validation layer: " << pCallbackData->pMessage << '\n';
	} else {
		std::cerr << "Validation layer: " << pCallbackData->pMessage << '\n';
	}

	return VK_FALSE;
}

void carbon::DebugUtilsMessenger::fillDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

	createInfo.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	createInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData = nullptr;
}


carbon::DebugUtilsMessenger::DebugUtilsMessenger(const VkInstance &inst, const VkAllocationCallbacks &alloc) {
	// set instance and allocator
	this->instance = inst;
	this->allocator = alloc;

	VkDebugUtilsMessengerCreateInfoEXT messengerInfo{};
	fillDebugUtilsMessengerCreateInfo(messengerInfo);

	// set create info
	this->createInfo = messengerInfo;

	// get function since it is external (not loaded in Vulkan initially)
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if (func == nullptr) {
		throw std::runtime_error("Failed to setup debug messenger!");
	}

	// attempt to create debug messenger
	if (func(instance, &createInfo, &allocator, &debugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create debug messenger!");
	}
}


carbon::DebugUtilsMessenger::~DebugUtilsMessenger() {
	// get function to destroy debug messenger
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func != nullptr) {
		func(instance, debugMessenger, &allocator);
	}
}


VkInstance carbon::DebugUtilsMessenger::getInstance() {
	return instance;
}


VkDebugUtilsMessengerEXT carbon::DebugUtilsMessenger::getDebugMessengerHandle() {
	return debugMessenger;
}


VkDebugUtilsMessengerCreateInfoEXT carbon::DebugUtilsMessenger::getDebugMessengerCreateInfo() {
	return createInfo;
}


VkAllocationCallbacks carbon::DebugUtilsMessenger::getAllocationCallbacks() {
	return allocator;
}

