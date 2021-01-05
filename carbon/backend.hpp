// file      : carbon/backend.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef BACKEND_HPP
#define BACKEND_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "types.hpp"

namespace carbon {

	/**
	 * @brief Zero-initializes a Vulkan structure.
	 * @tparam T The type of the Vulkan structure.
	 * @param vulkanStruct The Vulkan structure.
	 * @param structType The VkStructureType of the structure.
	 */
	template<class T>
	static inline void initStruct(T &vulkanStruct, const VkStructureType &structType) {
		// zero-initialize
		vulkanStruct = {};

		// set structure type
		vulkanStruct.sType = structType;
	}

} // namespace carbon

#endif // BACKEND_HPP
