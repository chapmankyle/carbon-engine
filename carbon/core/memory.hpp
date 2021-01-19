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
		 * @returns The handle on the allocator used for memory management.
		 */
		const VmaAllocator& getHandle() const {
			return m_allocator;
		}

	};

} // namespace carbon

#endif // CORE_MEMORY_HPP
