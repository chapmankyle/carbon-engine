// file      : carbon/resources/buffer.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef RES_BUFFER_HPP
#define RES_BUFFER_HPP

#include "carbon/setup.hpp"

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class LogicalDevice;

	/**
	 * @brief A wrapper for the Vulkan buffer object.
	 */
	class Buffer {

	private:

		/**
		 * @brief Handle on the underlying buffer object.
		 */
		VkBuffer m_buffer;

		/**
		 * @brief Size of the buffer (in bytes).
		 */
		VkDeviceSize m_size;

		/**
		 * @brief Offset of the buffer, if applicable.
		 */
		VkDeviceSize m_offset;

		/**
		 * @brief Physical device memory of this buffer.
		 */
		VkDeviceMemory m_memory;

		/**
		 * @brief Stores information about the offset, buffer and size.
		 */
		VkDescriptorBufferInfo m_descriptor;

		/**
		 * @brief Memory that has been mapped to the buffer.
		 */
		void *m_mapped_memory = nullptr;

		/**
		 * @brief Creates the buffer using the parameters from constructors.
		 */
		void create();

	public:

		/**
		 * @brief Initializes the buffer with the given parameters.
		 * @param size The size of the buffer.
		 * @param usage The bits representing how the buffer will be used.
		 * @param properties Properties of the buffer.
		 * @param data [Optional] Pointer to the data that the buffer should map to.
		 */
		Buffer(
			const VkDeviceSize& size, 
			const VkBufferUsageFlags& usage, 
			const VkMemoryPropertyFlags& properties, 
			const void *data = nullptr
		);

		/**
		 * @brief Initializes the buffer to 0.
		 */
		explicit Buffer();

		/**
		 * @brief Copy constructor to set current buffer to mirror another buffer.
		 * @param other Buffer object to copy from.
		 */
		Buffer(const Buffer &other);

		Buffer& operator=(const Buffer&) = delete;

		/**
		 * @brief Destructor for the buffer.
		 */
		~Buffer();

		/**
		 * @brief Destroys the buffer, freeing all allocated memory.
		 */
		void destroy();

		/**
		 * --------------------------
		 * -- Comparison operators --
		 * --------------------------
		 */

		bool operator==(const Buffer &other) const;

		bool operator!=(const Buffer &other) const;

		/**
		 * @brief Copies the contents from the `src` buffer into this buffer.
		 * @param src The buffer to copy the contents from.
		 * @param size The size of the buffer to copy.
		 */
		static void copyFrom(Buffer *src, VkDeviceSize size);

		/**
		 * @brief Attempts to map the buffer into CPU-accessible memory.
		 * @param size [Optional] The size of the buffer.
		 * @param offset [Optional] The offset of the buffer.
		 * @returns `true` if the buffer mapping was successful, `false` otherwise.
		 */
		bool mapMemory(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		/**
		 * @brief Unmaps the memory from the device.
		 */
		void unmapMemory();

		/**
		 * @returns `true` if the buffer is being used, `false` otherwise.
		 */
		bool inUse() const;

		/**
		 * @brief Flushes the memory of the device.
		 * @param size The size of the memory range to flush.
		 * @param offset The offset into the memory.
		 */
		void flush(VkDeviceSize size, VkDeviceSize offset);

		/**
		 * @returns The handle on the underlying buffer.
		 */
		const VkBuffer& getHandle() const {
			return m_buffer;
		}

		/**
		 * @returns The size of the buffer.
		 */
		const VkDeviceSize& getSize() const {
			return m_size;
		}

		/**
		 * @returns The offset of the buffer.
		 */
		const VkDeviceSize& getOffset() const {
			return m_offset;
		}

		/**
		 * @returns The device memory of the buffer.
		 */
		const VkDeviceMemory& getDeviceMemory() const {
			return m_memory;
		}

		/**
		 * @returns The descriptor buffer information.
		 */
		const VkDescriptorBufferInfo& getDescriptor() const {
			return m_descriptor;
		}

	};


	namespace utils {

		/**
		 * @brief Copies the contents of the `src` buffer into the `dest` buffer.
		 * @param src The buffer to copy the contents from.
		 * @param dest The buffer to copy the contents to.
		 * @param size The size of the buffer to copy.
		 */
		static void copyBuffer(Buffer *src, Buffer *dest, VkDeviceSize size);

	} // namespace utils

} // namespace carbon

#endif // RES_BUFFER_HPP
