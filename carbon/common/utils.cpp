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


		i32 gcd(i32 x, i32 y) {
			assert(x >= 0 && y >= 0 && "[ERROR] Negative numbers not allowed.");

			while (y != 0) {
				x %= y;

				if (x == 0) {
					return y;
				}

				y %= x;
			}

			return x;
		}


		std::string getEstimatedAspectRatio(i32 width, i32 height) {
			// find greatest common divisor
			i32 factor = gcd(width, height);
			i32 x = width / factor;
			i32 y = height / factor;

			// specifically to return 16:10 as 16:10 instead of 8:5
			if (factor == 160) {
				x *= 2;
				y *= 2;
			}

			return std::to_string(x) + ":" + std::to_string(y);
		}

	} // namespace utils

} // namespace carbon
