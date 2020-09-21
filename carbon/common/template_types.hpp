#pragma once

#ifndef COMMON_TEMPLATE_TYPES_HPP
#define COMMON_TEMPLATE_TYPES_HPP

#include "carbon/setup.hpp"

namespace carbon {

	namespace types {

		template<class T>
		struct is_supported_properties_struct {
			static const bool value = false;
		};

		template<>
		struct is_supported_properties_struct<VkExtensionProperties> {
			static const bool value = true;
		};

		template<>
		struct is_supported_properties_struct<VkLayerProperties> {
			static const bool value = true;
		};

	} // namespace types

} // namespace carbon

#endif // !COMMON_TEMPLATE_TYPES_HPP

