#pragma once

#ifndef CORE_LOGICAL_DEVICE_HPP
#define CORE_LOGICAL_DEVICE_HPP

#include "carbon/setup.hpp"

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class PhysicalDevice;
	class Instance;

	/**
	 * @brief A wrapper for the Vulkan logical device that represents
	 * the view of the device, handling graphics and presentation.
	 */
	class LogicalDevice {

	private:

		/**
		 * @brief Used to check which queue families are supported by the
		 * logical device.
		 */
		struct QueueFamilyIndices {
			int32_t m_graphics_family{ -1 };
			int32_t m_present_family{ -1 };
			int32_t m_compute_family{ -1 };
			int32_t m_transfer_family{ -1 };
		};

		/**
		 * @brief Owning instance of the logical device.
		 */
		const class Instance *m_instance;

		/**
		 * @brief Owning physical device that facilitates logical device.
		 */
		const class PhysicalDevice *m_physical_device;

		/**
		 * @brief Handle on the underlying Vulkan logical device.
		 */
		VkDevice m_device{ VK_NULL_HANDLE };

		/**
		 * @brief Handle on the graphics queue.
		 */
		VkQueue m_graphics_queue{ VK_NULL_HANDLE };

		/**
		 * @brief Handle on the presentation queue.
		 */
		VkQueue m_present_queue{ VK_NULL_HANDLE };

	public:

		/**
		 * @brief Initialize and create a logical device.
		 * @param instance The owning instance.
		 * @param physicalDevice The physical device to use.
		 */
		explicit LogicalDevice(class Instance *instance, class PhysicalDevice *physicalDevice);

		/**
		 * @brief Destructor for the logical device.
		 */
		~LogicalDevice();

		/**
		 * @brief Waits for the device to stop being in use.
		 */
		void waitForIdle();

		/**
		 * @brief Destroys the logical device.
		 */
		void destroy();

		/**
		 * @returns The handle of the underlying device.
		 */
		const VkDevice& getHandle() const;

		/**
		 * @returns The graphics queue.
		 */
		const VkQueue& getGraphicsQueue() const;

		/**
		 * @returns The presentation queue.
		 */
		const VkQueue& getPresentQueue() const;

	};

} // namespace carbon

#endif // CORE_LOGICAL_DEVICE_HPP
