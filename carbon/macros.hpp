// file      : carbon/macros.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef MACROS_HPP
#define MACROS_HPP

// ----------------------
// -- USEFUL CONSTANTS --
// ----------------------

#define CARBON_ENABLE  1
#define CARBON_DISABLE 0

#define CARBON_TRUE  1
#define CARBON_FALSE 0

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define CARBON_MAKE_VERSION(major, minor, patch) \
    ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

#define CARBON_VERSION_MAJOR 1
#define CARBON_VERSION_MINOR 1
#define CARBON_VERSION_PATCH 3

#define CARBON_VERSION          CARBON_MAKE_VERSION(CARBON_VERSION_MAJOR, CARBON_VERSION_MINOR, CARBON_VERSION_PATCH);
#define CARBON_VERSION_MESSAGE  "Carbon Engine v1.1.3"

#define CARBON_ENGINE_NAME "Carbon Engine"

#define CARBON_ENGINE_DIR_NAME      "carbon-engine"
#define CARBON_ENGINE_DIR_NAME_LEN  ARRAY_SIZE(CARBON_ENGINE_DIR_NAME) - 1

#define CARBON_ENGINE_LOG_PREFIX "carbon"

// -----------
// -- DEBUG --
// -----------

#ifdef CARBON_DISABLE_DEBUG
#	define CARBON_USE_VALIDATION_LAYERS CARBON_FALSE
#else
#	define CARBON_USE_VALIDATION_LAYERS CARBON_TRUE
#endif // CARBON_DISABLE_DEBUG

#endif // MACROS_HPP
