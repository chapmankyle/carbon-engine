#pragma once

#ifndef CORE_LOGICAL_DEVICE_HPP
#define CORE_LOGICAL_DEVICE_HPP

#include "carbon/setup.hpp"

#include <vector>
#include <set>

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class Instance;
	class PhysicalDevice;
	class Surface;

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
			uint32_t graphicsFamily{ UINT32_MAX };
			uint32_t presentFamily{ UINT32_MAX };
			uint32_t computeFamily{ UINT32_MAX };
			uint32_t transferFamily{ UINT32_MAX };

			/**
			 * @returns `true` if all graphics families are present, `false` otherwise.
			 */
			bool hasFamilies() {
				return graphicsFamily != UINT32_MAX && presentFamily != UINT32_MAX && computeFamily != UINT32_MAX && transferFamily != UINT32_MAX;
			}
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
		 * @brief Surface to use for displaying.
		 */
		const class Surface *m_surface;

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

		/**
		 * @brief Keep track of indices for different queue families (graphics,
		 * present, compute and transfer).
		 */
		QueueFamilyIndices m_queue_family_indices;

		/**
		 * @brief Finds the queue family indices.
		 */
		void findQueueFamilyIndices();

		/**
		 * @brief Creates the logical device.
		 */
		void createDevice();

	public:

		/**
		 * @brief Initialize and create a logical device.
		 * @param instance The owning instance.
		 * @param physicalDevice The physical device to use.
		 * @param surface The surface to use for rendering to the window.
		 */
		explicit LogicalDevice(
			class Instance *instance,
			class PhysicalDevice *physicalDevice,
			class Surface *surface
		);

		/**
		 * @brief Destructor for the logical device.
		 */
		~LogicalDevice();

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
