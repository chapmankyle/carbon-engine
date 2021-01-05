// file      : carbon/core/physical_device.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "physical_device.hpp"

#include "instance.hpp"

#include <iostream>

namespace carbon {

	bool PhysicalDevice::hasDeviceExtensionSupport(const VkPhysicalDevice &device) {
		// query device extension properties
		u32 numExtensions{ 0 };
		vkEnumerateDeviceExtensionProperties(device, nullptr, &numExtensions, nullptr);

		// put into vector
		std::vector<VkExtensionProperties> available(numExtensions);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &numExtensions, available.data());

		return utils::containsRequired(m_device_extensions, available);
	}


	i32 PhysicalDevice::getDeviceScore(const VkPhysicalDevice &device) {
		// get device properties and features
		VkPhysicalDeviceProperties deviceProps;
		VkPhysicalDeviceFeatures deviceFeats;

		vkGetPhysicalDeviceProperties(device, &deviceProps);
		vkGetPhysicalDeviceFeatures(device, &deviceFeats);

		// cannot function without geometry shader
		if (!deviceFeats.geometryShader) {
			return 0;
		}

		// no support for device extensions
		if (!hasDeviceExtensionSupport(device)) {
			return 0;
		}

		i32 score{ 0 };

		// favour discrete GPU
		if (deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			score += 1000;
		}

		score += deviceProps.limits.maxImageDimension2D;
		return score;
	}


	VkPhysicalDevice PhysicalDevice::selectBestPhysicalDevice(const std::vector<VkPhysicalDevice> &devices) {
		i32 score{ 0 };

		// add all device scores to candidates
		for (const auto &d : devices) {
			score = getDeviceScore(d);
			m_candidates.insert(std::make_pair(score, d));
		}

		// check if best candidate is even suitable
		if (m_candidates.rbegin()->first > 0) {
			return m_candidates.rbegin()->second;
		}

		return VK_NULL_HANDLE;
	}


	PhysicalDevice::PhysicalDevice(Instance *instance)
		: m_instance(instance)
	{
		// get number of physical devices available
		u32 numDevices{ 0 };
		vkEnumeratePhysicalDevices(m_instance->getHandle(), &numDevices, nullptr);

		// no physical devices found
		if (numDevices == 0) {
			throw std::runtime_error("[ERROR] Failed to find any physical devices!");
		}

		// store all devices in vector
		std::vector<VkPhysicalDevice> devices(numDevices);
		vkEnumeratePhysicalDevices(m_instance->getHandle(), &numDevices, devices.data());

		// select best device
		m_device = selectBestPhysicalDevice(devices);

		if (m_device == VK_NULL_HANDLE) {
			throw std::runtime_error("[ERROR] Failed to choose suitable physical device!");
		}

		// get properties of device
		vkGetPhysicalDeviceProperties(m_device, &m_device_props);
		vkGetPhysicalDeviceFeatures(m_device, &m_device_feats);
		vkGetPhysicalDeviceMemoryProperties(m_device, &m_device_memory_props);
	}


	const std::string PhysicalDevice::getPropertiesAsStr() const {
		std::string props("Selected Physical Device -> ");
		props.append(m_device_props.deviceName);

		props.append("\n    Type:                        ");
		props.append(getDeviceType());
		props.append("\n    Vendor ID:                   ");
		props.append(std::to_string(m_device_props.vendorID));
		props.append("\n    Memory heap count:           ");
		props.append(std::to_string(m_device_memory_props.memoryHeapCount));
		props.append("\n    Maximum clip distances:      ");
		props.append(std::to_string(m_device_props.limits.maxClipDistances));
		props.append("\n    Maximum cull distances:      ");
		props.append(std::to_string(m_device_props.limits.maxCullDistances));
		props.append("\n    Maximum number of viewports: ");
		props.append(std::to_string(m_device_props.limits.maxViewports));
		props.append("\n    Maximum size of 2D textures: ");
		props.append(std::to_string(m_device_props.limits.maxImageDimension2D));
		props.append("\n    Maximum size of 3D textures: ");
		props.append(std::to_string(m_device_props.limits.maxImageDimension3D));
		props.append("\n");

		return props;
	}


	const char* PhysicalDevice::getDeviceType() const {
		switch (m_device_props.deviceType) {
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				return "Integrated GPU";
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				return "Discrete GPU";
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				return "Virtual GPU";
			case VK_PHYSICAL_DEVICE_TYPE_CPU:
				return "CPU";
			default:
				return "Other";
		}
	}

} // namespace carbon
