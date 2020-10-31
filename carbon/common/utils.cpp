// file      : carbon/common/utils.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "utils.hpp"

namespace carbon {

	namespace utils {

		const std::vector<VkLayerProperties> getSupportedValidationLayers() {
			u32 numLayers{ 0 };

			// request number of layers
			vkEnumerateInstanceLayerProperties(&numLayers, nullptr);

			// put supported layers into std::vector
			std::vector<VkLayerProperties> supportedLayers(numLayers);
			vkEnumerateInstanceLayerProperties(&numLayers, supportedLayers.data());

			return supportedLayers;
		}


		const std::vector<VkExtensionProperties> getSupportedExtensions() {
			u32 numExtensions{ 0 };

			// request number of extensions available
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, nullptr);

			// pack available extensions into vector
			std::vector<VkExtensionProperties> supportedExtensions(numExtensions);
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, supportedExtensions.data());

			return supportedExtensions;
		}


		i32 compare(const char *str, const VkExtensionProperties &propStruct) {
			return strcmp(str, propStruct.extensionName);
		}


		i32 compare(const char *str, const VkLayerProperties &propStruct) {
			return strcmp(str, propStruct.layerName);
		}

	} // namespace utils

} // namespace carbon
