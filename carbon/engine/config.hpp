#pragma once

#ifndef ENGINE_CONFIG_HPP
#define ENGINE_CONFIG_HPP

namespace carbon {

	namespace config {

		static inline constexpr unsigned NUM_DESCRIPTOR_SETS = 4U;
		static inline constexpr unsigned NUM_BINDINGS = 16U;
		static inline constexpr unsigned NUM_ATTACHEMENTS = 8U;
		static inline constexpr unsigned NUM_VERTEX_BUFFERS = 4U;
		static inline constexpr unsigned MAX_UBO_SIZE = 16 * 1024;

		static inline constexpr int MAX_FRAMES_IN_FLIGHT = 2;

	} // namespace config

} // namespace carbon

#endif // ENGINE_CONFIG_HPP
