// file      : carbon/core/logical_device.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef CORE_LOGICAL_DEVICE_HPP
#define CORE_LOGICAL_DEVICE_HPP

#include "carbon/backend.hpp"

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
			u32 graphicsFamily{ u32_max };
			u32 presentFamily{ u32_max };
			u32 computeFamily{ u32_max };
			u32 transferFamily{ u32_max };

			/**
			 * @returns `true` if all graphics families are present, `false` otherwise.
			 */
			bool hasFamilies() {
				return graphicsFamily != u32_max && presentFamily != u32_max && computeFamily != u32_max && transferFamily != u32_max;
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
		 * @brief Binds buffer memory to the logical device.
		 * @param buffer The buffer to bind.
		 * @param memory The buffer memory to use.
		 * @param offset The offset into the buffer memory.
		 */
		void bindBuffer(const VkBuffer &buffer, const VkDeviceMemory &memory, const VkDeviceSize &offset);

		/**
		 * @returns The handle of the underlying device.
		 */
		const VkDevice& getHandle() const {
			return m_device;
		}

		/**
		 * @returns The physical device associated with this logical device.
		 */
		const class PhysicalDevice* getPhysicalDevice() const;

		/**
		 * @returns The graphics queue.
		 */
		const VkQueue& getGraphicsQueue() const {
			return m_graphics_queue;
		}

		/**
		 * @returns The presentation queue.
		 */
		const VkQueue& getPresentQueue() const {
			return m_present_queue;
		}

		/**
		 * @returns The graphics family.
		 */
		const u32 getGraphicsFamily() const {
			return m_queue_family_indices.graphicsFamily;
		}

		/**
		 * @returns The presentation family.
		 */
		const u32 getPresentFamily() const {
			return m_queue_family_indices.presentFamily;
		}

		/**
		 * @returns The compute family.
		 */
		const u32 getComputeFamily() const {
			return m_queue_family_indices.computeFamily;
		}

		/**
		 * @returns The transfer family.
		 */
		const u32 getTransferFamily() const {
			return m_queue_family_indices.transferFamily;
		}

	};

} // namespace carbon

#endif // CORE_LOGICAL_DEVICE_HPP
