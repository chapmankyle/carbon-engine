// file      : carbon/core/physical_device.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef CORE_PHYSICAL_DEVICE_HPP
#define CORE_PHYSICAL_DEVICE_HPP

#include "carbon/backend.hpp"

#include <map>
#include <string>
#include <vector>

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class Instance;

	/**
	 * @brief A wrapper for the Vulkan physical device (GPU) that is used
	 * for rendering.
	 */
	class PhysicalDevice {

	private:

		/**
		 * @brief Owning instance for physical device.
		 */
		const class Instance *m_instance;

		/**
		 * @brief The required device extensions.
		 */
		const std::vector<const char *> m_device_extensions{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		/**
		 * @brief Handle on the underlying selected physical device.
		 */
		VkPhysicalDevice m_device{ VK_NULL_HANDLE };

		/**
		 * @brief Device properties for the selected device.
		 */
		VkPhysicalDeviceProperties m_device_props{};

		/**
		 * @brief Features of the selected device.
		 */
		VkPhysicalDeviceFeatures m_device_feats{};

		/**
		 * @brief Memory properties of the selected device.
		 */
		VkPhysicalDeviceMemoryProperties m_device_memory_props{};

		/**
		 * @brief Ordered map of possible candidate physical devices.
		 */
		std::multimap<i32, VkPhysicalDevice> m_candidates;

		/*
		 * @returns `true` if the device supports all the extensions, `false` otherwise.
		 */
		bool hasDeviceExtensionSupport(const VkPhysicalDevice &device);

		/**
		 * @returns The score for the given physical device.
		 */
		i32 getDeviceScore(const VkPhysicalDevice &device);

		/**
		 * @returns The best physical device.
		 */
		VkPhysicalDevice selectBestPhysicalDevice(const std::vector<VkPhysicalDevice> &devices);

	public:

		/**
		 * @brief Initialize a physical device that is owned by the instance.
		 * @param instance The owning instance for the physical device.
		 */
		explicit PhysicalDevice(class Instance *instance);

		/**
		 * @brief Physical device will be cleaned up automatically when
		 * Instance is destroyed.
		 */
		~PhysicalDevice() = default;

		/**
		 * @brief Finds the type of memory that is compatible with our application requirements.
		 * @param filter The bit field of memory types that are suitable.
		 * @param props The flags for the memory properties.
		 * @returns The index of the type of memory that is compatible.
		 */
		const u32 findMemoryType(u32 filter, const VkMemoryPropertyFlags &props) const;

		/**
		 * @returns The properties of the best physical device as a string.
		 */
		const std::string getPropertiesAsStr() const;

		/**
		 * @returns The type of the device, as a string.
		 */
		const char* getDeviceType() const;

		/**
		 * @returns The underlying `VkPhysicalDevice`.
		 */
		const VkPhysicalDevice& getHandle() const {
			return m_device;
		}

		/**
		 * @returns The device properties of the selected physical devices.
		 */
		const VkPhysicalDeviceProperties& getProperties() const {
			return m_device_props;
		}

		/**
		 * @returns The device features of the selected physical device.
		 */
		const VkPhysicalDeviceFeatures& getFeatures() const {
			return m_device_feats;
		}

		/**
		 * @returns The device memory properties of the selected physical device.
		 */
		const VkPhysicalDeviceMemoryProperties& getMemoryProperties() const {
			return m_device_memory_props;
		}

		/**
		 * @returns The found physical devices and their scores.
		 */
		const std::multimap<i32, VkPhysicalDevice> getCandidates() const {
			return m_candidates;
		}

		/**
		 * @returns The device extensions.
		 */
		const std::vector<const char*> getDeviceExtensions() const {
			return m_device_extensions;
		}

	};

} // namespace carbon

#endif // CORE_PHYSICAL_DEVICE_HPP
