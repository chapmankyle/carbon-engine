// file      : carbon/core/logical_device.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "logical_device.hpp"

#include "instance.hpp"
#include "physical_device.hpp"

#include "carbon/common/logger.hpp"
#include "carbon/display/surface.hpp"

#include <set>

namespace carbon {

	void LogicalDevice::findQueueFamilyIndices() {
		u32 numQueueFamilies{ 0 };

		// get physical device queue family properties
		VkPhysicalDevice physDevice{ m_physical_device->getHandle() };
		vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &numQueueFamilies, nullptr);

		// store queue families
		std::vector<VkQueueFamilyProperties> queueFamilies(numQueueFamilies);
		vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &numQueueFamilies, queueFamilies.data());

		u32 i{ 0 };

		// find first index of queue family that supports commands
		for (const auto &queueFam : queueFamilies) {
			// check for graphics support
			if (queueFam.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				m_queue_family_indices.graphicsFamily = i;
			}

			// check for surface support
			VkBool32 presentSupport{ false };
			vkGetPhysicalDeviceSurfaceSupportKHR(m_physical_device->getHandle(), i, m_surface->getHandle(), &presentSupport);

			if (queueFam.queueCount > 0 && presentSupport) {
				m_queue_family_indices.presentFamily = i;
			}

			// check for compute support
			if (queueFam.queueFlags & VK_QUEUE_COMPUTE_BIT) {
				m_queue_family_indices.computeFamily = i;
			}

			// check for transfer support
			if (queueFam.queueFlags & VK_QUEUE_TRANSFER_BIT) {
				m_queue_family_indices.transferFamily = i;
			}

			// check if all families are supported
			if (m_queue_family_indices.hasFamilies()) {
				break;
			}

			i++;
		}

		if (m_queue_family_indices.graphicsFamily == u32_max) {
			CARBON_LOG_FATAL(carbon::log::To::File, "No graphics family support.");
		}
	}


	void LogicalDevice::createDevice() {
		// unique indices for queue families
		std::set<u32> uniqueQueueFamilies = {
			m_queue_family_indices.graphicsFamily,
			m_queue_family_indices.presentFamily
		};

		// createinfo for each queue family
		std::vector<VkDeviceQueueCreateInfo> createInfoQueues;

		// priority given to this queue
		float queuePriority{ 1.0f };

		for (const u32 queueFam : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo;
			initStruct(queueCreateInfo, VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO);

			queueCreateInfo.queueFamilyIndex = queueFam;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			createInfoQueues.push_back(queueCreateInfo);
		}

		// specify device features to use
		VkPhysicalDeviceFeatures deviceFeats{};
		deviceFeats.samplerAnisotropy = VK_TRUE;
		deviceFeats.sampleRateShading = VK_TRUE;

		std::vector<const char*> deviceExtensions{ m_physical_device->getDeviceExtensions() };
		std::vector<const char*> validationLayers{ m_instance->getEnabledValidationLayers() };

		// start creating device information
		VkDeviceCreateInfo createInfo;
		initStruct(createInfo, VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO);

		createInfo.queueCreateInfoCount = to_u32(createInfoQueues.size());
		createInfo.pQueueCreateInfos = createInfoQueues.data();

		createInfo.pEnabledFeatures = &deviceFeats;

		createInfo.enabledExtensionCount = to_u32(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (m_instance->isValidationEnabled()) {
			createInfo.enabledLayerCount = to_u32(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		} else {
			createInfo.enabledLayerCount = 0;
			createInfo.ppEnabledLayerNames = nullptr;
		}

		// attempt to create logical device
		if (vkCreateDevice(m_physical_device->getHandle(), &createInfo, nullptr, &m_device) != VK_SUCCESS) {
			CARBON_LOG_FATAL(carbon::log::To::File, "Failed to create logical device.");
		}

		// create single graphics queue from device
		vkGetDeviceQueue(m_device, m_queue_family_indices.graphicsFamily, 0, &m_graphics_queue);
		vkGetDeviceQueue(m_device, m_queue_family_indices.presentFamily, 0, &m_present_queue);
	}

	LogicalDevice::LogicalDevice(Instance *instance, PhysicalDevice *physicalDevice, Surface *surface)
		: m_instance(instance)
		, m_physical_device(physicalDevice)
		, m_surface(surface)
	{
		// find queue families and then create the logical device
		findQueueFamilyIndices();
		createDevice();
	}


	LogicalDevice::~LogicalDevice() {
		destroy();
	}


	void LogicalDevice::destroy() {
		if (m_device == VK_NULL_HANDLE) {
			return;
		}

		// wait for asynchronous drawing commands to complete
		vkDeviceWaitIdle(m_device);

		// destroy and reset
		vkDestroyDevice(m_device, nullptr);
		m_device = VK_NULL_HANDLE;

		// m_surface is member class and thus will be destroyed
		// after this class destructor
	}


	const PhysicalDevice* LogicalDevice::getPhysicalDevice() const {
		return m_physical_device;
	}

} // namespace carbon
