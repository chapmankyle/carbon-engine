#include "utils.hpp"

const std::vector<VkLayerProperties> carbon::utils::getSupportedValidationLayers() {
	uint32_t numLayers{ 0 };

	// request number of layers
	vkEnumerateInstanceLayerProperties(&numLayers, nullptr);

	// put supported layers into std::vector
	std::vector<VkLayerProperties> supportedLayers(numLayers);
	vkEnumerateInstanceLayerProperties(&numLayers, supportedLayers.data());

	return supportedLayers;
}


const std::vector<VkExtensionProperties> carbon::utils::getSupportedExtensions() {
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
