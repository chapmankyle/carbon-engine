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


carbon::DebugMessenger::DebugMessenger(VkInstance &instance) {
	// set instance
	m_instance = instance;

	VkDebugUtilsMessengerCreateInfoEXT messengerInfo{};
	fillDebugMessengerCreateInfo(messengerInfo);

	// set create info
	m_create_info = messengerInfo;

	// get function since it is external (not loaded in Vulkan initially)
	auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT"));

	if (func == nullptr) {
		throw std::runtime_error("Failed to setup debug messenger!");
	}

	// attempt to create debug messenger
	if (func(m_instance, &m_create_info, nullptr, &m_debug_messenger) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create debug messenger!");
	}
}


carbon::DebugMessenger::DebugMessenger() {
	// set up only the create info struct
	VkDebugUtilsMessengerCreateInfoEXT msgInfo{};
	fillDebugMessengerCreateInfo(msgInfo);
	m_create_info = msgInfo;
}


carbon::DebugMessenger::~DebugMessenger() {
	destroy();
}


void carbon::DebugMessenger::destroy() {
	if (m_instance == VK_NULL_HANDLE) {
		return;
	}
	if (m_debug_messenger == VK_NULL_HANDLE) {
		return;
	}

	// get function to destroy debug messenger
	auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT"));

	if (func != nullptr) {
		func(m_instance, m_debug_messenger, nullptr);
		m_debug_messenger = VK_NULL_HANDLE;
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


void carbon::DebugMessenger::setCreateInfo(const VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
	m_create_info = createInfo;
}


void carbon::DebugMessenger::setDebugCallback(PFN_vkDebugUtilsMessengerCallbackEXT callback) {
	m_create_info.pfnUserCallback = callback;
}


carbon::DebugMessenger& carbon::DebugMessenger::operator=(const carbon::DebugMessenger &msg) {
	this->m_instance = msg.m_instance;
	this->m_debug_messenger = msg.m_debug_messenger;
	this->m_create_info = msg.m_create_info;
	return *this;
}

