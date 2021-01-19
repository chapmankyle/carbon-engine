// file      : carbon/core/memory.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef CORE_MEMORY_HPP
#define CORE_MEMORY_HPP

#ifndef VMA_IMPLEMENTATION
#	define VMA_IMPLEMENTATION
#	include "vk_mem_alloc.h"
#endif // VMA_IMPLEMENTATION

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class LogicalDevice;

	namespace memory {

		/**
		 * @brief Usage flags for memory allocation.
		 */
		enum class Usage {
			Unknown = 0,

			OnlyGPU = 1,
			OnlyCPU = 2,

			CPUtoGPU = 3,
			GPUtoCPU = 4,

			CopyCPU = 5,
			LazyGPU = 6,

			Max = 0x7FFFFFFF
		};

	} // namespace memory

	/**
	 * @brief Class to represent a memory manager in charge of handling 
	 * any memory allocation / deallocation.
	 */
	class Memory {

	private:

		/**
		 * @brief Handle on the logical device.
		 */
		const class LogicalDevice *m_device = nullptr;

		/**
		 * @brief Handle on the allocator of memory.
		 */
		VmaAllocator m_allocator;

	public:

		/**
		 * @brief Initializes the memory manager.
		 * @param device The device to use for memory management.
		 */
		explicit Memory(const class LogicalDevice *device);

		/**
		 * @brief Destructor for the memory manager.
		 */
		~Memory();

		/**
		 * @brief Creates a buffer, allocates the memory and binds it.
		 * @param info The information to create the buffer with.
		 * @param usage The usage of the 
		 */
		void createBuffer(const VkBufferCreateInfo &info, const memory::Usage &usage);

		/**
		 * @returns The handle on the allocator used for memory management.
		 */
		const VmaAllocator& getHandle() const {
			return m_allocator;
		}

	};

} // namespace carbon

#endif // CORE_MEMORY_HPP
