// file      : carbon/core/instance.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "instance.hpp"

namespace carbon {

	const std::vector<const char*> Instance::getRequiredInstanceExtensions() {
		u32 numExtensions{ 0 };

		// get required extensions and convert to std::vector<string>
		const char** reqExts = glfwGetRequiredInstanceExtensions(&numExtensions);
		std::vector<const char *> required(reqExts, reqExts + numExtensions);

		// additional extension if validation layers are included
		if (CARBON_USE_VALIDATION_LAYERS) {
			required.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return required;
	}


	bool Instance::hasValidationLayerSupport() {
		const std::vector<VkLayerProperties> supportedLayers = utils::getSupportedValidationLayers();

#ifndef CARBON_DISABLE_DEBUG
		std::cout << "[INFO] " << supportedLayers.size() << " supported layers.\n";
#endif // !CARBON_DISABLE_DEBUG

		return utils::containsRequired(m_req_validation_layers, supportedLayers);
	}


	bool Instance::hasExtensionSupport() {
		const std::vector<VkExtensionProperties> supportedExtensions = utils::getSupportedExtensions();

#ifndef CARBON_DISABLE_DEBUG
		std::cout << "[INFO] " << supportedExtensions.size() << " supported extensions.\n";
#endif // !CARBON_DISABLE_DEBUG

		return utils::containsRequired(m_req_instance_extensions, supportedExtensions);
	}


	void Instance::checkSupport() {
		// check validation layers support
		if (m_validation_enabled && !hasValidationLayerSupport()) {
			throw std::runtime_error("No support for validation layers!");
		}

		// set enabled validation layers
		m_enabled_validation_layers = m_req_validation_layers;

		// check for extensions support
		if (!hasExtensionSupport()) {
			throw std::runtime_error("Failed to find required extensions.");
		}
	}


	void Instance::fillApplicationInfo(
		VkApplicationInfo &appInfo,
		const char *appName,
		const utils::version &version
	) {
		// zero-initialize struct
		initStruct(appInfo, VK_STRUCTURE_TYPE_APPLICATION_INFO);

		appInfo.pApplicationName = appName;
		appInfo.applicationVersion = VK_MAKE_VERSION(version.major, version.minor, version.patch);

		appInfo.pEngineName = CARBON_ENGINE_NAME;
		appInfo.engineVersion = CARBON_VERSION;
		appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
	}


	void Instance::fillInstanceCreateInfo(
		VkInstanceCreateInfo &instInfo,
		const VkApplicationInfo &appInfo
	) {
		// zero-initialize struct
		initStruct(instInfo, VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO);

		instInfo.pApplicationInfo = &appInfo;

		instInfo.enabledExtensionCount = static_cast<u32>(m_req_instance_extensions.size());
		instInfo.ppEnabledExtensionNames = m_req_instance_extensions.data();

		// set enabled extensions
		m_enabled_extensions = m_req_instance_extensions;

		// enable validation layers if flag set
		if (m_validation_enabled) {
			instInfo.enabledLayerCount = static_cast<u32>(m_req_validation_layers.size());
			instInfo.ppEnabledLayerNames = m_req_validation_layers.data();

			debug::fillMessengerCreateInfo(m_debug_create_info);
			instInfo.pNext = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT *>(&m_debug_create_info);
		} else {
			instInfo.enabledLayerCount = 0;
			instInfo.pNext = nullptr;
		}
	}


	Instance::Instance(const std::string appName, const utils::version &version) {
		// set status of validation layers
		m_validation_enabled = static_cast<bool>(CARBON_USE_VALIDATION_LAYERS);

		checkSupport();

		// inform driver of how best to optimize application
		VkApplicationInfo appInfo;
		fillApplicationInfo(appInfo, appName.c_str(), version);

		// tells driver which extensions and validation layers to use
		VkInstanceCreateInfo instanceInfo;
		fillInstanceCreateInfo(instanceInfo, appInfo);

		// attempt to create instance
		if (vkCreateInstance(&instanceInfo, nullptr, &m_handle) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create instance!");
		}

		// do not create debug messenger if validation layers are off
		if (!m_validation_enabled) {
			return;
		}

		if (debug::createMessenger(m_handle, &m_debug_create_info, nullptr, &m_debug_messenger) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create debug messenger!");
		}
	}


	Instance::Instance()
		: Instance("Application")
	{}


	Instance::~Instance() {
		destroy();
	}


	void Instance::destroy() {
		// destroy debug messenger if applicable
		if (m_validation_enabled && m_debug_messenger != VK_NULL_HANDLE) {
			debug::destroyMessenger(m_handle, m_debug_messenger, nullptr);
			m_debug_messenger = VK_NULL_HANDLE;
		}

		if (m_handle == VK_NULL_HANDLE) {
			return;
		}

		// destroy instance
		vkDestroyInstance(m_handle, nullptr);
		m_handle = VK_NULL_HANDLE;
	}

} // namespace carbon
