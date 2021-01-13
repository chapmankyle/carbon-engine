// file      : carbon/core/time.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef CORE_TIME_HPP
#define CORE_TIME_HPP

#include <cassert>
#include <chrono>

namespace carbon {

	/**
	 * @brief Base clock type used to measure time.
	 */
	using clock_t = std::chrono::steady_clock;

	// type definitions for durations

	using seconds_t = std::chrono::duration<double, std::ratio<1>>;
	using milliseconds_t = std::chrono::duration<double, std::ratio<1, 1000>>;

	using time_point_t = std::chrono::time_point<clock_t>;

	namespace time {

		template<class T>
		struct is_supported_conversion {
			static const bool value = false;
		};

		template<>
		struct is_supported_conversion<seconds_t> {
			static const bool value = true;
		};

		template<>
		struct is_supported_conversion<milliseconds_t> {
			static const bool value = true;
		};

	} // namespace time

	/**
	 * @brief Class that provides methods to facilitate timing.
	 */
	class Timer {

	private:

		/**
		 * @brief Time when the class was constructed.
		 */
		time_point_t m_start;

	public:

		/**
		 * @brief Initializes the timer.
		 */
		Timer()
			: m_start(clock_t::now())
		{}

		/**
		 * @brief Resets the internal clock.
		 */
		void reset() {
			m_start = clock_t::now();
		}

		/**
		 * @brief Returns the elapsed time since the timer was initialized or reset (default is in milliseconds).
		 * @tparam T The return type (`seconds_t` or `milliseconds_t`).
		 * @returns The elapsed time (default is in milliseconds).
		 */
		template<typename T = milliseconds_t>
		double elapsed() const {
			assert(carbon::time::is_supported_conversion<T>::value && "[ERROR] Invalid time conversion parameter.");
			return std::chrono::duration_cast<T>(clock_t::now() - m_start).count();
		}

	};

} // namespace carbon

#endif // CORE_TIME_HPP
