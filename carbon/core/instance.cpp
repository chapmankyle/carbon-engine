#include "instance.hpp"

void carbon::Instance::checkSupport() {
	// check validation layers support
	if (CARBON_ENABLE_VALIDATION_LAYERS && !carbon::utils::hasValidationLayerSupport()) {
		throw std::runtime_error("No support for validation layers!");
	}

	// check for extensions support
	if (!carbon::utils::hasExtensionSupport()) {
		throw std::runtime_error("Failed to find required extensions.");
	}
}


void carbon::Instance::fillApplicationInfo(
	VkApplicationInfo &appInfo,
	const char *appName,
	const carbon::utils::version &version
) {
	// zero-initialize struct
	initStruct(appInfo, VK_STRUCTURE_TYPE_APPLICATION_INFO);

	appInfo.pApplicationName = appName;
	appInfo.applicationVersion = VK_MAKE_VERSION(version.major, version.minor, version.patch);

	appInfo.pEngineName = CARBON_ENGINE_NAME;
	appInfo.engineVersion = CARBON_VERSION;
	appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
}


carbon::Instance::Instance(const char *appName, const carbon::utils::version &version) {
	checkSupport();

	// inform driver of how best to optimize application
	VkApplicationInfo appInfo;
	fillApplicationInfo(appInfo, appName, version);

	// get required extensions
	const auto required{ carbon::utils::getRequiredExtensions() };

	// tells driver which extensions and validation layers to use
	VkInstanceCreateInfo instanceInfo{};

	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;

	instanceInfo.enabledExtensionCount = static_cast<uint32_t>(required.size());
	instanceInfo.ppEnabledExtensionNames = required.data();

	// check for errors during messenger creation and deletion
	m_debug_messenger = carbon::DebugMessenger(m_handle, nullptr);
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{ m_debug_messenger.getCreateInfo() };

	// enable validation layers if flag set
	if (CARBON_ENABLE_VALIDATION_LAYERS) {
		const auto validationLayers{ carbon::utils::getRequiredValidationLayers() };

		instanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		instanceInfo.ppEnabledLayerNames = validationLayers.data();

		instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
	} else {
		instanceInfo.enabledLayerCount = 0;
		instanceInfo.pNext = nullptr;
	}

	// attempt to create instance
	if (vkCreateInstance(&instanceInfo, nullptr, &m_handle) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create instance!");
	}
}


carbon::Instance::~Instance() {
	destroy();
}


void carbon::Instance::destroy() {
	if (m_handle == nullptr || m_handle == VK_NULL_HANDLE) {
		return;
	}

	vkDestroyInstance(m_handle, nullptr);
}


VkInstance carbon::Instance::getHandle() {
	return m_handle;
}


carbon::DebugMessenger carbon::Instance::getDebugMessenger() {
	return m_debug_messenger;
}


std::vector<const char*> carbon::Instance::getExtensions() {
	return m_enabled_extensions;
}

