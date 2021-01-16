// file      : carbon/resources/command_pool.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "command_pool.hpp"

#include "carbon/common/logger.hpp"
#include "carbon/core/logical_device.hpp"

namespace carbon {

	void CommandPool::create() {
		// fill info struct
		VkCommandPoolCreateInfo poolInfo;
		initStruct(poolInfo, VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO);

		poolInfo.queueFamilyIndex = m_queue_family;
		poolInfo.flags = m_flags;
		poolInfo.pNext = nullptr;

		// attempt to create command pool
		if (vkCreateCommandPool(m_device->getHandle(), &poolInfo, nullptr, &m_pool) != VK_SUCCESS) {
			CARBON_LOG_FATAL(log::To::File, "Failed to create command pool.");
		}
	}


	CommandPool::CommandPool(const LogicalDevice *device, u32 queueFamily, const VkCommandPoolCreateFlags &flags)
		: m_device(device)
		, m_queue_family(queueFamily)
		, m_flags(flags)
	{
		assert(m_device && "Logical device cannot be null.");
		create();
	}


	CommandPool::CommandPool(const LogicalDevice *device, const VkCommandPoolCreateFlags &flags)
		: m_device(device)
		, m_queue_family(device->getGraphicsFamily())
		, m_flags(flags)
	{
		assert(m_device && "Logical device cannot be null.");
		create();
	}


	CommandPool::~CommandPool() {
		// ensure command pool has not already been destroyed
		if (m_pool != VK_NULL_HANDLE) {
			destroy();
		}
	}


	void CommandPool::destroy() {
		vkDestroyCommandPool(m_device->getHandle(), m_pool, nullptr);
		m_pool = VK_NULL_HANDLE;
	}

} // namespace carbon
