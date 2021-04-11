// file      : carbon/resources/buffer.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "buffer.hpp"

#include "carbon/common/logger.hpp"
#include "carbon/core/logical_device.hpp"
#include "carbon/core/physical_device.hpp"

#include "command_pool.hpp"
#include "command_buffer.hpp"

#include <cassert>

namespace carbon {

	Buffer::Buffer(
		LogicalDevice *device, 
		const VkDeviceSize &size, 
		const VkBufferUsageFlags &usage, 
		const VkMemoryPropertyFlags &properties, 
		const void *data
	) 
		: m_logi_device(device)
		, m_phys_device(device->getPhysicalDevice())
		, m_size(size)
		, m_usage(usage)
		, m_properties(properties)
		, m_buffer(VK_NULL_HANDLE)
		, m_memory(VK_NULL_HANDLE)
	{
		assert(m_logi_device && m_phys_device && "Logical and physical devices must not be null.");

		// create with given parameters
		create(m_size, m_usage, m_properties, data);

		// initialize descriptor
		m_descriptor = {};
		m_descriptor.buffer = m_buffer;
		m_descriptor.offset = m_offset;
		m_descriptor.range = m_size;

		// initialize command pool and command buffer
		m_pool = new CommandPool(m_logi_device);
		m_command_buffer = new CommandBuffer(m_logi_device, m_pool);
	}


	Buffer::Buffer(LogicalDevice *device) 
		: m_logi_device(device)
		, m_phys_device(device->getPhysicalDevice())
		, m_size(0)
		, m_usage(VK_NULL_HANDLE)
		, m_properties(VK_NULL_HANDLE)
		, m_mapped_memory(nullptr)
		, m_buffer(VK_NULL_HANDLE)
		, m_memory(VK_NULL_HANDLE)
	{
		assert(m_logi_device && m_phys_device && "Logical and physical devices must not be null.");
		m_descriptor = {};

		// initialize command pool and command buffer
		m_pool = new CommandPool(m_logi_device);
		m_command_buffer = new CommandBuffer(m_logi_device, m_pool);
	}


	Buffer::Buffer(const Buffer &other) {
		// do nothing if they are exactly the same
		if (*this == other) {
			return;
		}

		// copy contents of buffer to *this
		m_logi_device = other.getLogicalDevice();
		m_phys_device = other.getPhysicalDevice();
		m_pool = other.getCommandPool();
		m_command_buffer = other.getCommandBuffer();
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

		delete m_command_buffer;
		delete m_pool;
	}


	void Buffer::destroy() {
		unmapMemory();

		// get logical device
		VkDevice dev = m_logi_device->getHandle();

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


	void Buffer::create(
		const VkDeviceSize &size,
		const VkBufferUsageFlags &usage, 
		const VkMemoryPropertyFlags &properties,
		const void *data
	) {
		// get handle on logical device
		VkDevice dev = m_logi_device->getHandle();

		// specify use of buffer
		VkBufferCreateInfo bufferInfo;
		initStruct(bufferInfo, VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO);

		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		// attempt to create buffer
		if (vkCreateBuffer(dev, &bufferInfo, nullptr, &m_buffer) != VK_SUCCESS) {
			CARBON_LOG_FATAL(carbon::log::To::File, "Failed to create buffer.");
		}

		// get memory requirements
		VkMemoryRequirements memReqs;
		vkGetBufferMemoryRequirements(dev, m_buffer, &memReqs);

		// setup allocation of memory
		VkMemoryAllocateInfo allocInfo;
		initStruct(allocInfo, VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO);

		allocInfo.allocationSize = memReqs.size;
		allocInfo.memoryTypeIndex = m_phys_device->findMemoryType(memReqs.memoryTypeBits, properties);

		// attempt to allocate buffer memory
		if (vkAllocateMemory(dev, &allocInfo, nullptr, &m_memory) != VK_SUCCESS) {
			CARBON_LOG_FATAL(carbon::log::To::File, "Failed to allocate buffer memory.");
		}

		// bind memory
		m_logi_device->bindBuffer(m_buffer, nullptr, 0);
	}


	void Buffer::copyFrom(Buffer *src, const VkDeviceSize &size) {
		// begin copying
		m_command_buffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

		VkBufferCopy copy{};
		copy.srcOffset = 0;
		copy.dstOffset = 0;
		copy.size = size;
		vkCmdCopyBuffer(m_command_buffer->getHandle(), src->getHandle(), m_buffer, 1, &copy);

		// end copying
		m_command_buffer->end();
	}


	bool Buffer::mapMemory(VkDeviceSize size, VkDeviceSize offset) {
		VkDevice dev = m_logi_device->getHandle();
		return vkMapMemory(dev, m_memory, offset, size, 0, &m_mapped_memory) == VK_SUCCESS;
	}


	void Buffer::unmapMemory() {
		// do nothing if no memory has been mapped
		if (!m_mapped_memory) {
			return;
		}

		// unmap the memory
		VkDevice dev = m_logi_device->getHandle();
		vkUnmapMemory(dev, m_memory);
		m_mapped_memory = nullptr;
	}


	bool Buffer::inUse() const {
		return m_memory != VK_NULL_HANDLE && m_buffer != VK_NULL_HANDLE && m_size;
	}


	bool Buffer::flush(const VkDeviceSize &size, const VkDeviceSize &offset) {
		VkDevice dev = m_logi_device->getHandle();

		// flush memory mapped range
		VkMappedMemoryRange mappedRange;
		initStruct(mappedRange, VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE);

		mappedRange.size = size;
		mappedRange.offset = offset;
		mappedRange.memory = m_memory;
		mappedRange.pNext = nullptr;

		return vkFlushMappedMemoryRanges(dev, 1, &mappedRange) == VK_SUCCESS;
	}


	LogicalDevice* Buffer::getLogicalDevice() const {
		return m_logi_device;
	}


	const PhysicalDevice* Buffer::getPhysicalDevice() const {
		return m_phys_device;
	}


	CommandPool* Buffer::getCommandPool() const {
		return m_pool;
	}


	CommandBuffer* Buffer::getCommandBuffer() const {
		return m_command_buffer;
	}


	namespace utils {

		void copyBuffer(Buffer *src, Buffer *dest, const VkDeviceSize &size) {
		}

	} // namespace utils

} // namespace carbon
