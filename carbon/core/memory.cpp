// file      : carbon/core/memory.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "memory.hpp"

#include "carbon/common/logger.hpp"

#include "instance.hpp"
#include "physical_device.hpp"
#include "logical_device.hpp"

namespace carbon {

	Memory::Memory(const LogicalDevice *device) 
		: m_device(device)
	{
		// fill create info
		VmaAllocatorCreateInfo allocInfo{};

		allocInfo.vulkanApiVersion = VK_API_VERSION_1_2;
		allocInfo.physicalDevice = (m_device->getPhysicalDevice())->getHandle();
		allocInfo.device = m_device->getHandle();
		allocInfo.instance = (m_device->getInstance())->getHandle();

		// attempt to create allocator
		if (vmaCreateAllocator(&allocInfo, &m_allocator) != VK_SUCCESS) {
			CARBON_LOG_FATAL(log::To::File, "Failed to create allocator.");
		}
	}


	Memory::~Memory() {
		vmaDestroyAllocator(m_allocator);
	}

} // namespace carbon
