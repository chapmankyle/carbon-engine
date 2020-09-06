#include "instance.hpp"

carbon::Instance::Instance(
	const char *appName,
	const carbon::utils::version &version,
	const std::vector<const char*> &requiredValidationLayers,
	const std::vector<const char*> &requiredExtensions
) {
	// check validation layers support
	if (CARBON_ENABLE_VALIDATION_LAYERS && !carbon::utils::hasValidationLayerSupport()) {
		throw std::runtime_error("No support for validation layers!");
	}

	// check for extensions support
	if (!carbon::utils::hasExtensionSupport()) {
		throw std::runtime_error("Failed to find required extensions.");
	}

	// get required extensions
	const auto required{ carbon::utils::getRequiredExtensions() };

	// inform driver of how best to optimize application
	VkApplicationInfo appInfo{};

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = appName;
	appInfo.applicationVersion = VK_MAKE_VERSION(version.major, version.minor, version.patch);

	appInfo.pEngineName = "Carbon Engine";
	appInfo.engineVersion = CARBON_VERSION;
	appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

	// tells driver which extensions and validation layers to use
	VkInstanceCreateInfo instanceInfo{};

	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;

	instanceInfo.enabledExtensionCount = static_cast<uint32_t>(required.size());
	instanceInfo.ppEnabledExtensionNames = required.data();

	// check for errors during messenger creation and deletion
	debugMessenger = carbon::DebugUtilsMessenger(handle, nullptr);
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{ debugMessenger.getCreateInfo() };

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
	if (vkCreateInstance(&instanceInfo, nullptr, &handle) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create instance!");
	}
}


carbon::Instance::~Instance() {
	vkDestroyInstance(handle, nullptr);
}


VkInstance carbon::Instance::getHandle() {
	return handle;
}


carbon::DebugUtilsMessenger carbon::Instance::getDebugMessenger() {
	return debugMessenger;
}

