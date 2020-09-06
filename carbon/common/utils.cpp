#include "utils.hpp"

inline const std::vector<const char*> carbon::utils::getRequiredExtensions() {
	uint32_t numExtensions{ 0 };

	// get required extensions and convert to std::vector<string>
	const char** reqExts{ glfwGetRequiredInstanceExtensions(&numExtensions) };
	std::vector<const char *> required(reqExts, reqExts + numExtensions);

	// additional extension if validation layers are included
	if (CARBON_ENABLE_VALIDATION_LAYERS) {
		required.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return required;
}


inline const std::vector<VkLayerProperties> carbon::utils::requestSupportedValidationLayers() {
	uint32_t numLayers{ 0 };

	// request number of layers
	vkEnumerateInstanceLayerProperties(&numLayers, nullptr);

	// put supported layers into std::vector
	std::vector<VkLayerProperties> supportedLayers(numLayers);
	vkEnumerateInstanceLayerProperties(&numLayers, supportedLayers.data());

	return supportedLayers;
}


const std::vector<VkExtensionProperties> carbon::utils::requestSupportedExtensions() {
	uint32_t numExtensions{ 0 };

	// request number of extensions available
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, nullptr);

	// pack available extensions into vector
	std::vector<VkExtensionProperties> supportedExtensions(numExtensions);
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, supportedExtensions.data());

	return supportedExtensions;
}


bool carbon::utils::containsRequired(
	const std::vector<const char*> &required,
	const std::vector<VkLayerProperties> &available
) {
	// keep track of if an layer was found
	bool found;

	// check each layer in `required` to see if it is available
	for (const auto &req : required) {
		found = false;

		for (const auto &layer : available) {
			if (strcmp(req, layer.layerName) == 0) {
				found = true;
				break;
			}
		}

		// could not find required layer
		if (!found) {
			return false;
		}
	}

	return true;
}


bool carbon::utils::containsRequired(
	const std::vector<const char*> &required,
	const std::vector<VkExtensionProperties> &available
) {
	// keep track of if an extension was found
	bool found;

	// check each extension in `required` to see if it is available
	for (const auto &req : required) {
		found = false;

		for (const auto &ext : available) {
			if (strcmp(req, ext.extensionName) == 0) {
				found = true;
				break;
			}
		}

		// could not find required extension
		if (!found) {
			return false;
		}
	}

	return true;
}


bool carbon::utils::hasValidationLayerSupport() {
	std::vector<const char *> requiredLayers{ getRequiredValidationLayers() };
	std::vector<VkLayerProperties> supportedLayers{ requestSupportedValidationLayers() };

#ifndef NDEBUG
	std::cout << "[INFO] " << supportedLayers.size() << " supported layers.\n";
#endif // !NDEBUG

	return utils::containsRequired(requiredLayers, supportedLayers);
}


bool carbon::utils::hasExtensionSupport() {
	std::vector<const char *> requiredExtensions{ getRequiredExtensions() };
	std::vector<VkExtensionProperties> supportedExtensions{ requestSupportedExtensions() };

#ifndef NDEBUG
	std::cout << "[INFO] " << supportedExtensions.size() << " supported layers.\n";
#endif // !NDEBUG

	return utils::containsRequired(requiredExtensions, supportedExtensions);
}

