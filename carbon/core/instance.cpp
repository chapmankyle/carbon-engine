#include "instance.hpp"

const std::vector<const char*> carbon::Instance::getRequiredInstanceExtensions() {
	uint32_t numExtensions{ 0 };

	// get required extensions and convert to std::vector<string>
	const char** reqExts{ glfwGetRequiredInstanceExtensions(&numExtensions) };
	std::vector<const char *> required(reqExts, reqExts + numExtensions);

	// additional extension if validation layers are included
	if (CARBON_USE_VALIDATION_LAYERS) {
		required.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return required;
}


bool carbon::Instance::hasValidationLayerSupport() {
	const std::vector<VkLayerProperties> supportedLayers{ carbon::utils::getSupportedValidationLayers() };

#ifndef CARBON_DISABLE_DEBUG
	std::cout << "[INFO] " << supportedLayers.size() << " supported layers.\n";
#endif // !CARBON_DISABLE_DEBUG

	return carbon::utils::containsRequired(m_req_validation_layers, supportedLayers);
}


bool carbon::Instance::hasExtensionSupport() {
	const std::vector<VkExtensionProperties> supportedExtensions{ carbon::utils::getSupportedExtensions() };

#ifndef CARBON_DISABLE_DEBUG
	std::cout << "[INFO] " << supportedExtensions.size() << " supported extensions.\n";
#endif // !CARBON_DISABLE_DEBUG

	return carbon::utils::containsRequired(m_req_instance_extensions, supportedExtensions);
}


void carbon::Instance::checkSupport() {
	// check validation layers support
	if (CARBON_USE_VALIDATION_LAYERS && !hasValidationLayerSupport()) {
		throw std::runtime_error("No support for validation layers!");
	}

	// set enabled validation layers
	m_enabled_validation_layers = m_req_validation_layers;

	// check for extensions support
	if (!hasExtensionSupport()) {
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


void carbon::Instance::fillInstanceCreateInfo(
	VkInstanceCreateInfo &instInfo,
	const VkApplicationInfo &appInfo
) {
	// zero-initialize struct
	initStruct(instInfo, VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO);

	instInfo.pApplicationInfo = &appInfo;

	instInfo.enabledExtensionCount = static_cast<uint32_t>(m_req_instance_extensions.size());
	instInfo.ppEnabledExtensionNames = m_req_instance_extensions.data();

	// set enabled extensions
	m_enabled_extensions = m_req_instance_extensions;

	// enable validation layers if flag set
	if (CARBON_USE_VALIDATION_LAYERS) {
		instInfo.enabledLayerCount = static_cast<uint32_t>(m_req_validation_layers.size());
		instInfo.ppEnabledLayerNames = m_req_validation_layers.data();
	} else {
		instInfo.enabledLayerCount = 0;
		instInfo.pNext = nullptr;
	}
}


carbon::Instance::Instance(const char *appName, const carbon::utils::version &version) {
	checkSupport();

	// inform driver of how best to optimize application
	VkApplicationInfo appInfo;
	fillApplicationInfo(appInfo, appName, version);

	// tells driver which extensions and validation layers to use
	VkInstanceCreateInfo instanceInfo;
	fillInstanceCreateInfo(instanceInfo, appInfo);

	// attempt to create instance
	if (vkCreateInstance(&instanceInfo, nullptr, &m_handle) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create instance!");
	}
}


carbon::Instance::~Instance() {
	destroy();
}


void carbon::Instance::destroy() {
	if (m_handle == VK_NULL_HANDLE) {
		return;
	}

	vkDestroyInstance(m_handle, nullptr);
	m_handle = VK_NULL_HANDLE;
}


const VkInstance carbon::Instance::getHandle() const {
	return m_handle;
}


const std::vector<const char *> carbon::Instance::getEnabledValidationLayers() const {
	return m_enabled_validation_layers;
}


const std::vector<const char*> carbon::Instance::getEnabledExtensions() const {
	return m_enabled_extensions;
}
