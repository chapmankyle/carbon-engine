#include "utils.hpp"

CARBON_INLINE const std::vector<const char*> carbon::utils::getRequiredExtensions() {
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


CARBON_INLINE const std::vector<VkLayerProperties> carbon::utils::requestSupportedValidationLayers() {
	uint32_t numLayers{ 0 };

	// request number of layers
	vkEnumerateInstanceLayerProperties(&numLayers, nullptr);

	// put supported layers into std::vector
	std::vector<VkLayerProperties> supportedLayers(numLayers);
	vkEnumerateInstanceLayerProperties(&numLayers, supportedLayers.data());

	return supportedLayers;
}


CARBON_INLINE const std::vector<VkExtensionProperties> carbon::utils::requestSupportedExtensions() {
	uint32_t numExtensions{ 0 };

	// request number of extensions available
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, nullptr);

	// pack available extensions into vector
	std::vector<VkExtensionProperties> supportedExtensions(numExtensions);
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, supportedExtensions.data());

	return supportedExtensions;
}


int32_t carbon::utils::compare(const char *str, const VkExtensionProperties &propStruct) {
	return strcmp(str, propStruct.extensionName);
}

int32_t carbon::utils::compare(const char *str, const VkLayerProperties &propStruct) {
	return strcmp(str, propStruct.layerName);
}


template<class T>
bool carbon::utils::containsRequired(
	const std::vector<const char *> &required,
	const std::vector<T> &available
) {
	assert(carbon::types::is_supported_properties_struct<T>::value);
	bool found;

	for (const auto &req : required) {
		found = false;

		for (const auto &a : available) {
			if (carbon::utils::compare(req, a) == 0) {
				found = true;
				break;
			}
		}

		if (!found) {
			return false;
		}
	}

	return true;
}


bool carbon::utils::hasValidationLayerSupport() {
	std::vector<const char *> requiredLayers{ getRequiredValidationLayers() };
	std::vector<VkLayerProperties> supportedLayers{ requestSupportedValidationLayers() };

#ifndef CARBON_DISABLE_DEBUG
	std::cout << "[INFO] " << supportedLayers.size() << " supported layers.\n";
#endif // !CARBON_DISABLE_DEBUG

	return utils::containsRequired(requiredLayers, supportedLayers);
}


bool carbon::utils::hasExtensionSupport() {
	std::vector<const char *> requiredExtensions{ getRequiredExtensions() };
	std::vector<VkExtensionProperties> supportedExtensions{ requestSupportedExtensions() };

#ifndef CARBON_DISABLE_DEBUG
	std::cout << "[INFO] " << supportedExtensions.size() << " supported layers.\n";
#endif // !CARBON_DISABLE_DEBUG

	return utils::containsRequired(requiredExtensions, supportedExtensions);
}

