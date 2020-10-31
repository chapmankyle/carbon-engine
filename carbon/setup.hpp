// file      : carbon/setup.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef SETUP_HPP
#define SETUP_HPP

// ------------------
// -- DEPENDENCIES --
// ------------------

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "platform.hpp"
#include "types.hpp"

// ----------------------
// -- USEFUL CONSTANTS --
// ----------------------

#define CARBON_ENABLE  1
#define CARBON_DISABLE 0

#define CARBON_TRUE  1
#define CARBON_FALSE 0

#define CARBON_VERSION_MAJOR 1
#define CARBON_VERSION_MINOR 0
#define CARBON_VERSION_PATCH 0

#define CARBON_VERSION VK_MAKE_VERSION(CARBON_VERSION_MAJOR, CARBON_VERSION_MINOR, CARBON_VERSION_PATCH);
#define CARBON_VERSION_MESSAGE "Carbon Engine v1.0.0"

#define CARBON_ENGINE_NAME "Carbon Engine"

// -----------
// -- DEBUG --
// -----------

#ifndef CARBON_DISABLE_DEBUG
#	include <iostream>
#	define CARBON_USE_VALIDATION_LAYERS CARBON_TRUE
#else
#	define CARBON_USE_VALIDATION_LAYERS CARBON_FALSE
#endif // CARBON_DISABLE_DEBUG

// ------------------
// -- C++ STANDARD --
// ------------------

#define CARBON_LANG_CXX0X_FLAG  (1 << 1)
#define CARBON_LANG_CXX11_FLAG  (1 << 2)
#define CARBON_LANG_CXX14_FLAG  (1 << 3)
#define CARBON_LANG_CXX17_FLAG  (1 << 4)
#define CARBON_LANG_CXX2A_FLAG  (1 << 5)

#define CARBON_LANG_CXX0X  CARBON_LANG_CXX0X_FLAG
#define CARBON_LANG_CXX11  (CARBON_LANG_CXX0X | CARBON_LANG_CXX11_FLAG)
#define CARBON_LANG_CXX14  (CARBON_LANG_CXX11 | CARBON_LANG_CXX14_FLAG)
#define CARBON_LANG_CXX17  (CARBON_LANG_CXX14 | CARBON_LANG_CXX17_FLAG)
#define CARBON_LANG_CXX2A  (CARBON_LANG_CXX17 | CARBON_LANG_CXX2A_FLAG)

// Controls language extensions
#define CARBON_LANG_EXT CARBON_DISABLE

// check if using Visual Studio compiler
#if CARBON_COMPILER & CARBON_COMPILER_VC && defined(_MSVC_LANG)
#	if CARBON_COMPILER >= CARBON_COMPILER_VC15_7
#		define CARBON_LANG_PLATFORM _MSVC_LANG
#	elif CARBON_COMPILER >= CARBON_COMPILER_VC15
#		if _MSVC_LANG > 201402L
#			define CARBON_LANG_PLATFORM 201402L
#		else
#			define CARBON_LANG_PLATFORM _MSVC_LANG
#		endif
#	else
#		define CARBON_LANG_PLATFORM 0
#	endif
#else
#	define CARBON_LANG_PLATFORM 0
#endif

// check C++ standard
#if __cplusplus > 201703L || CARBON_LANG_PLATFORM > 201703L
#	define CARBON_LANG (CARBON_LANG_CXX2A | CARBON_LANG_EXT)
#elif __cplusplus == 201703L || CARBON_LANG_PLATFORM == 201703L
#	define CARBON_LANG (CARBON_LANG_CXX17 | CARBON_LANG_EXT)
#elif __cplusplus == 201402L || __cplusplus == 201406L || __cplusplus == 201500L || CARBON_LANG_PLATFORM == 201402L
#	define CARBON_LANG (CARBON_LANG_CXX14 | CARBON_LANG_EXT)
#elif __cplusplus == 201103L || CARBON_LANG_PLATFORM == 201103L
#	define CARBON_LANG (CARBON_LANG_CXX11 | CARBON_LANG_EXT)
#else
#	define CARBON_LANG (0 | CARBON_LANG_EXT)
#endif

// ------------------
// -- C++ FEATURES --
// ------------------

// -- constexpr
// N2235 Generalized Constant Expressions http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2007/n2235.pdf
// N3652 Relaxing constraints on constexpr functions http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2013/n3652.html
#if (CARBON_COMPILER & CARBON_COMPILER_CLANG)
#	define CARBON_HAS_CONSTEXPR __has_feature(cxx_relaxed_constexpr)
#elif (CARBON_LANG & CARBON_LANG_CXX14_FLAG)
#	define CARBON_HAS_CONSTEXPR 1
#else
#	define CARBON_HAS_CONSTEXPR ((CARBON_LANG & CARBON_LANG_CXX0X_FLAG) && \
		((CARBON_COMPILER & CARBON_COMPILER_VC) && (CARBON_COMPILER >= CARBON_COMPILER_VC15)))
#endif

#if CARBON_HAS_CONSTEXPR
#	define CARBON_CONSTEXPR constexpr
#else
#	define CARBON_CONSTEXPR
#endif

// -- static_assert
// N1720 Proposal to Add Static Assertions to the Core Language http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2004/n1720.html
#if CARBON_COMPILER & CARBON_COMPILER_CLANG
#	define CARBON_HAS_STATIC_ASSERT __has_feature(cxx_static_assert)
#elif CARBON_LANG & CARBON_LANG_CXX11_FLAG
#	define CARBON_HAS_STATIC_ASSERT 1
#else
#	define CARBON_HAS_STATIC_ASSERT ((CARBON_LANG & CARBON_LANG_CXX0X_FLAG) && \
		((CARBON_COMPILER & CARBON_COMPILER_VC)))
#endif

#if CARBON_HAS_STATIC_ASSERT
#	define CARBON_STATIC_ASSERT(x, message) static_assert(x, message)
#elif CARBON_COMPILER & CARBON_COMPILER_VC
#	define CARBON_STATIC_ASSERT(x, message) typedef char __CASSERT__##__LINE__[(x) ? 1 : -1]
#else
#	define CARBON_STATIC_ASSERT(x, message) assert(x && message)
#endif

// -- inline

#define CARBON_INLINE inline

// ----------------------
// -- USEFUL FUNCTIONS --
// ----------------------

namespace carbon {

	/*
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

#endif // SETUP_HPP

