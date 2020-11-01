// file      : carbon/types.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

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

	using u8 = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using i8 = std::int8_t;
	using i16 = std::int16_t;
	using i32 = std::int32_t;
	using i64 = std::int64_t;

	using uc8 = std::uint_fast8_t;
	using c8 = std::int_fast8_t;

	using f32 = float;
	using f64 = double;

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

	//     _____                              _
	//    / ____|                            (_)
	//   | |     ___  _ ____   _____ _ __ ___ _  ___  _ __
	//   | |    / _ \| '_ \ \ / / _ \ '__/ __| |/ _ \| '_ \
	//   | |___| (_) | | | \ V /  __/ |  \__ \ | (_) | | | |
	//    \_____\___/|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
	//

	template<typename T>
	static inline u8 to_u8(T value) {
		return static_cast<u8>(value);
	}

	template<typename T>
	static inline u16 to_u16(T value) {
		return static_cast<u16>(value);
	}

	template<typename T>
	static inline u32 to_u32(T value) {
		return static_cast<u32>(value);
	}

	template<typename T>
	static inline u64 to_u64(T value) {
		return static_cast<u64>(value);
	}


	template<typename T>
	static inline i8 to_i8(T value) {
		return static_cast<i8>(value);
	}

	template<typename T>
	static inline i16 to_i16(T value) {
		return static_cast<i16>(value);
	}

	template<typename T>
	static inline i32 to_i32(T value) {
		return static_cast<i32>(value);
	}

	template<typename T>
	static inline i64 to_i64(T value) {
		return static_cast<i64>(value);
	}


	template<typename T>
	static inline uc8 to_uc8(T value) {
		return static_cast<uc8>(value);
	}

	template<typename T>
	static inline c8 to_c8(T value) {
		return static_cast<c8>(value);
	}


	template<typename T>
	static inline f32 to_f32(T value) {
		return static_cast<f32>(value);
	}

	template<typename T>
	static inline f64 to_f64(T value) {
		return static_cast<f64>(value);
	}

}

#endif // TYPES_HPP
