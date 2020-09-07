#pragma once

#ifndef SETUP_HPP
#define SETUP_HPP

// ------------------
// -- DEPENDENCIES --
// ------------------

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <memory>

// ----------------------
// -- USEFUL CONSTANTS --
// ----------------------

#define CARBON_ENABLE 1
#define CARBON_DISABLE 0

#define CARBON_VERSION_MAJOR 1
#define CARBON_VERSION_MINOR 0
#define CARBON_VERSION_PATCH 0

#define CARBON_VERSION VK_MAKE_VERSION(CARBON_VERSION_MAJOR, CARBON_VERSION_MINOR, CARBON_VERSION_PATCH);
#define CARBON_VERSION_STRING "Carbon Engine v1.0.0"

#define CARBON_ENGINE_NAME "Carbon Engine"

// -----------
// -- DEBUG --
// -----------

#ifndef CARBON_DISABLE_DEBUG
#include <iostream>
#define CARBON_ENABLE_VALIDATION_LAYERS CARBON_ENABLE
#else
#define CARBON_ENABLE_VALIDATION_LAYERS CARBON_DISABLE
#endif // CARBON_DISABLE_DEBUG

// ----------------------
// -- USEFUL FUNCTIONS --
// ----------------------

namespace carbon {

	template<class T>
	static inline void initStruct(T &vulkanStruct, const VkStructureType &structType) {
		vulkanStruct.sType = structType;
		memset(((unsigned char*)&vulkanStruct) + sizeof(VkStructureType), 0, sizeof(T) - sizeof(VkStructureType));
	}

} // namespace carbon

#endif // SETUP_HPP

