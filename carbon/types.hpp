#pragma once

#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <limits>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

namespace carbon {

	//    ____
	//   |  _ \
	//   | |_) | __ _ ___  ___
	//   |  _ < / _` / __|/ _ \
	//   | |_) | (_| \__ \  __/
	//   |____/ \__,_|___/\___|
	//

	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;

	//    _____
	//   |  __ \
	//   | |__) |__ _ _ __   __ _  ___  ___
	//   |  _  // _` | '_ \ / _` |/ _ \/ __|
	//   | | \ \ (_| | | | | (_| |  __/\__ \
	//   |_|  \_\__,_|_| |_|\__, |\___||___/
	//                       __/ |
	//                      |___/

	inline static constexpr auto u8_min = std::numeric_limits<u8>::min();
	inline static constexpr auto u8_max = std::numeric_limits<u8>::max();

	inline static constexpr auto u16_min = std::numeric_limits<u16>::min();
	inline static constexpr auto u16_max = std::numeric_limits<u16>::max();

	inline static constexpr auto u32_min = std::numeric_limits<u32>::min();
	inline static constexpr auto u32_max = std::numeric_limits<u32>::max();

	inline static constexpr auto u64_min = std::numeric_limits<u64>::min();
	inline static constexpr auto u64_max = std::numeric_limits<u64>::max();


	inline static constexpr auto i8_min = std::numeric_limits<i8>::min();
	inline static constexpr auto i8_max = std::numeric_limits<i8>::max();

	inline static constexpr auto i16_min = std::numeric_limits<i16>::min();
	inline static constexpr auto i16_max = std::numeric_limits<i16>::max();

	inline static constexpr auto i32_min = std::numeric_limits<i32>::min();
	inline static constexpr auto i32_max = std::numeric_limits<i32>::max();

	inline static constexpr auto i64_min = std::numeric_limits<i64>::min();
	inline static constexpr auto i64_max = std::numeric_limits<i64>::max();

}

#endif // TYPES_HPP
