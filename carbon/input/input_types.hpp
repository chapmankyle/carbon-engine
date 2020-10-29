// file      : carbon/input/input_types.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef INPUT_TYPES_HPP
#define INPUT_TYPES_HPP

#include "carbon/types.hpp"

namespace carbon {

	//    _  __
	//   | |/ /
	//   | ' / ___ _   _ ___
	//   |  < / _ \ | | / __|
	//   | . \  __/ |_| \__ \
	//   |_|\_\___|\__, |___/
	//              __/ |
	//             |___/

	namespace key {

		/**
		 * @brief The state of the key.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__input.html
		 */
		enum class State : u32 {
			Release = 0,
			Press,
			Repeat,

			NONE
		};

		/**
		 * @brief Modifiers for the keys.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__mods.html
		 */
		enum class Modifier : c8 {
			Shift = 0x0001,
			Control = 0x0002,
			Alt = 0x0004,
			Super = 0x0008,
			CapsLock = 0x0010,
			NumLock = 0x0020,

			NONE
		};

		/**
		 * @brief Codes for each key available.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__keys.html
		 */
		enum class Code : i32 {
			Unknown = -1,

			/* base keys */

			Space = 32,
			Apostrophe = 39, /* ' */
			Comma = 44,      /* , */
			Minus,           /* - */
			Period,          /* . */
			Slash,           /* / */

			_0 = 48,
			_1,
			_2,
			_3,
			_4,
			_5,
			_6,
			_7,
			_8,
			_9,

			Semicolon = 59, /* ; */
			Equal = 61,     /* = */

			A = 65,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,

			LeftBracket = 91, /* [ */
			Backslash,        /* \ */
			RightBracket,     /* ] */
			GraveAccent = 96, /* ` */

			World1 = 161, /* non-US #1 */
			World2 = 162, /* non-US #2 */

			/* surrounding keys */

			Escape = 256,
			Enter,
			Tab,
			Backspace,
			Insert,
			Delete,

			/* arrow keys */

			Right = 262,
			Left,
			Down,
			Up,

			PageUp,
			PageDown,
			Home,
			End,

			CapsLock = 280,
			ScrollLock,
			NumLock,
			PrintScreen,
			Pause,

			/* function keys */

			F1 = 290,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			F16,
			F17,
			F18,
			F19,
			F20,
			F21,
			F22,
			F23,
			F24,
			F25,

			Numpad_0 = 320,
			Numpad_1,
			Numpad_2,
			Numpad_3,
			Numpad_4,
			Numpad_5,
			Numpad_6,
			Numpad_7,
			Numpad_8,
			Numpad_9,

			NumpadDecimal = 330,
			NumpadDivide,
			NumpadMultiply,
			NumpadSubtract,
			NumpadAdd,
			NumpadEnter,
			NumpadEqual,

			LeftShift = 340,
			LeftControl,
			LeftAlt,
			LeftSuper,

			RightShift,
			RightControl,
			RightAlt,
			RightSuper,

			Menu,

			Last = Menu
		};

	} // namespace key

} // namespace carbon

#endif // INPUT_TYPES_HPP
