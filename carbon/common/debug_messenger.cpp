#include "debug_messenger.hpp"

VKAPI_ATTR VkBool32 VKAPI_CALL carbon::DebugMessenger::debugCallback(
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


void carbon::DebugMessenger::fillDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &cInfo) {
	carbon::initStruct(cInfo, VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT);

	cInfo.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	cInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	cInfo.pfnUserCallback = debugCallback;
	cInfo.pUserData = nullptr;
}


carbon::DebugMessenger::DebugMessenger(const VkInstance &instance, const VkAllocationCallbacks *allocator) {
	// set instance and allocator
	m_instance = instance;
	m_allocator = *allocator;

	VkDebugUtilsMessengerCreateInfoEXT messengerInfo{};
	fillDebugMessengerCreateInfo(messengerInfo);

	// set create info
	m_create_info = messengerInfo;

	// get function since it is external (not loaded in Vulkan initially)
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");

	if (func == nullptr) {
		throw std::runtime_error("Failed to setup debug messenger!");
	}

	// attempt to create debug messenger
	if (func(m_instance, &m_create_info, &m_allocator, &m_debug_messenger) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create debug messenger!");
	}
}


carbon::DebugMessenger::DebugMessenger()
	: DebugMessenger(nullptr, nullptr)
{}


carbon::DebugMessenger::~DebugMessenger() {
	// get function to destroy debug messenger
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func != nullptr) {
		func(m_instance, m_debug_messenger, &m_allocator);
	}
}


VkInstance carbon::DebugMessenger::getInstance() {
	return m_instance;
}


VkDebugUtilsMessengerEXT carbon::DebugMessenger::getHandle() {
	return m_debug_messenger;
}


VkDebugUtilsMessengerCreateInfoEXT carbon::DebugMessenger::getCreateInfo() {
	return m_create_info;
}


VkAllocationCallbacks carbon::DebugMessenger::getAllocationCallbacks() {
	return m_allocator;
}


void carbon::DebugMessenger::setCreateInfo(const VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
	m_create_info = createInfo;
}

