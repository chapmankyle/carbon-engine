// file      : carbon/resources/buffer.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "buffer.hpp"

#include "carbon/core/logical_device.hpp"

#include <cassert>

namespace carbon {

	Buffer::Buffer(const LogicalDevice *device, const VkDeviceSize &size, const VkBufferUsageFlags &usage, const VkMemoryPropertyFlags &properties, const void *data) 
		: m_device(device)
		, m_size(size)
		, m_usage(usage)
		, m_properties(properties)
		, m_buffer(VK_NULL_HANDLE)
		, m_memory(VK_NULL_HANDLE)
	{
		assert(m_device && "Logical device must not be null.");

		// create with given parameters
		create(m_size, m_usage, m_properties, data);

		// initialize descriptor
		m_descriptor = {};
		m_descriptor.buffer = m_buffer;
		m_descriptor.offset = m_offset;
		m_descriptor.range = m_size;
	}


	Buffer::Buffer(const LogicalDevice *device) 
		: m_device(device)
		, m_size(0)
		, m_usage(VK_NULL_HANDLE)
		, m_properties(VK_NULL_HANDLE)
		, m_mapped_memory(nullptr)
		, m_buffer(VK_NULL_HANDLE)
		, m_memory(VK_NULL_HANDLE)
		, m_descriptor{}
	{
		assert(m_device && "Logical device must not be null.");
	}


	Buffer::Buffer(const Buffer &other) {
		// do nothing if they are exactly the same
		if (*this == other) {
			return;
		}

		// copy contents of buffer to *this
		m_device = other.getLogicalDevice();
		m_size = other.getSize();
		m_usage = other.getUsage();
		m_properties = other.getMemoryProperties();
		m_mapped_memory = other.getMappedMemory();
		m_buffer = other.getHandle();
		m_memory = other.getDeviceMemory();
		m_descriptor = other.getDescriptor();
	}


	Buffer::~Buffer() {
		// ensure buffer has not already been destroyed
		if (m_buffer != VK_NULL_HANDLE) {
			destroy();
		}
	}


	void Buffer::destroy() {
		unmapMemory();

		// get logical device
		VkDevice dev = m_device->getHandle();

		// destroy buffer
		if (m_buffer != VK_NULL_HANDLE) {
			vkDestroyBuffer(dev, m_buffer, nullptr);
			m_buffer = VK_NULL_HANDLE;
		}

		// destroy device memory
		if (m_memory != VK_NULL_HANDLE) {
			vkFreeMemory(dev, m_memory, nullptr);
			m_memory = VK_NULL_HANDLE;
		}
	}


	bool Buffer::operator==(const Buffer &other) const {
		return m_size == other.getSize() && m_buffer == other.getHandle() && m_mapped_memory == other.getMappedMemory();
	}


	bool Buffer::operator!=(const Buffer &other) const {
		return !(*this == other);
	}


	void Buffer::create(const VkDeviceSize &size, const VkBufferUsageFlags &usage, const VkMemoryPropertyFlags &properties, const void *data) {
	}


	void Buffer::copyFrom(Buffer *src, const VkDeviceSize &size) {
	}


	bool Buffer::mapMemory(VkDeviceSize size, VkDeviceSize offset) {
		VkDevice dev = m_device->getHandle();
		return vkMapMemory(dev, m_memory, offset, size, 0, &m_mapped_memory) == VK_SUCCESS;
	}


	void Buffer::unmapMemory() {
		// do nothing if no memory has been mapped
		if (!m_mapped_memory) {
			return;
		}

		// unmap the memory
		VkDevice dev = m_device->getHandle();
		vkUnmapMemory(dev, m_memory);
		m_mapped_memory = nullptr;
	}


	bool Buffer::inUse() const {
		return m_memory != VK_NULL_HANDLE && m_buffer != VK_NULL_HANDLE && m_size;
	}


	bool Buffer::flush(const VkDeviceSize size, const VkDeviceSize offset) {
		VkDevice dev = m_device->getHandle();

		// flush memory mapped range
		VkMappedMemoryRange mappedRange;
		initStruct(mappedRange, VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE);

		mappedRange.size = size;
		mappedRange.offset = offset;
		mappedRange.memory = m_memory;
		mappedRange.pNext = nullptr;

		return vkFlushMappedMemoryRanges(dev, 1, &mappedRange) == VK_SUCCESS;
	}


	const LogicalDevice* Buffer::getLogicalDevice() const {
		return m_device;
	}


	namespace utils {

		void copyBuffer(Buffer *src, Buffer *dest, const VkDeviceSize &size) {
		}

	} // namespace utils

} // namespace carbon
