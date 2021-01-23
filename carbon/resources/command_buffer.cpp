// file      : carbon/resources/command_buffer.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "command_buffer.hpp"

#include "carbon/common/logger.hpp"
#include "carbon/core/logical_device.hpp"
#include "command_pool.hpp"

#include <cassert>

namespace carbon {

	CommandBuffer::CommandBuffer(const LogicalDevice* device, const CommandPool* pool) 
		: m_device(device)
		, m_pool(pool)
	{
		assert(m_device && m_pool && "Device and command pool must not be null.");

		// create allocation info
		VkCommandBufferAllocateInfo allocInfo;
		initStruct(allocInfo, VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO);

		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_pool->getHandle();
		allocInfo.commandBufferCount = 1;

		// attempt to create command buffer
		if (vkAllocateCommandBuffers(m_device->getHandle(), &allocInfo, &m_command_buffer) != VK_SUCCESS) {
			CARBON_LOG_FATAL(log::To::File, "Failed to allocate command buffers.");
		}

		// set state to ready
		m_state = buffer::State::Ready;
	}


	CommandBuffer::~CommandBuffer() {
		// check that command buffer has not already been freed
		if (m_command_buffer != VK_NULL_HANDLE) {
			vkFreeCommandBuffers(m_device->getHandle(), m_pool->getHandle(), 1, &m_command_buffer);
			m_command_buffer = VK_NULL_HANDLE;
		}
	}


	void CommandBuffer::begin(VkCommandBufferUsageFlagBits usage) {
		assert(!inUse() && "Command buffer is already in use.");
		m_state = buffer::State::Recording;

		// specify information about use of command buffer
		VkCommandBufferBeginInfo info;
		initStruct(info, VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO);

		info.flags = usage;
		info.pInheritanceInfo = nullptr;

		// attempt to begin command buffer recording
		if (vkBeginCommandBuffer(m_command_buffer, &info) != VK_SUCCESS) {
			CARBON_LOG_FATAL(log::To::File, "Failed to begin command buffer recording.");
		}
	}


	void CommandBuffer::end() {
		assert(inUse() && "Command buffer has not started recording.");

		// end recording and reset state
		if (vkEndCommandBuffer(m_command_buffer) != VK_SUCCESS) {
			CARBON_LOG_FATAL(log::To::File, "Failed to end command buffer recording.");
		}

		m_state = buffer::State::Ready;
	}


	const LogicalDevice* CommandBuffer::getDevice() const {
		return m_device;
	}


	const CommandPool* CommandBuffer::getPool() const {
		return m_pool;
	}

} // namespace carbon
