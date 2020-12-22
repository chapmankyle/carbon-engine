// file      : carbon/display/input.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef INPUT_TYPES_HPP
#define INPUT_TYPES_HPP

#include "carbon/types.hpp"

namespace carbon {

	/**
	 * @brief The state of the key or mouse.
	 * Adapted from : https://www.glfw.org/docs/3.3/group__input.html
	 */
	enum class InputState : u32 {
		Release = 0,
		Press,
		Repeat,

		NONE
	};

	namespace cursor {

		/**
		 * @brief The types of cursors available.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__shapes.html
		 */
		enum class Type : i32 {
			Arrow = 0x00036001,
			Ibeam = 0x00036002,
			Crosshair = 0x00036003,
			Hand = 0x00036004,
			HorizontalResize = 0x00036005,
			VerticalResize = 0x00036006,

			Normal = Arrow
		};

	} // namespace cursor

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

			Last = Menu,

			NONE
		};

		/**
		 * @brief Any event that occurs involving keys.
		 */
		struct event {

			/**
			 * @brief The state of the key.
			 */
			carbon::InputState state{ carbon::InputState::NONE };

			/**
			 * @brief The key that has been activated.
			 */
			carbon::key::Code key{ carbon::key::Code::NONE };

			/**
			 * @brief The modifier, if any, applied to the key.
			 */
			carbon::key::Modifier modifier{ carbon::key::Modifier::NONE };

			/**
			 * @returns `true` if any key is pressed, `false` otherwise.
			 */
			bool anyKeyPressed() const {
				return state == carbon::InputState::Press && key != carbon::key::Code::NONE;
			}

			/**
			 * @returns `true` if any key is released, `false` otherwise.
			 */
			bool anyKeyReleased() const {
				return state == carbon::InputState::Release && key != carbon::key::Code::NONE;
			}

			/**
			 * @returns `true` if any key is repeated, `false` otherwise.
			 */
			bool anyKeyRepeated() const {
				return state == carbon::InputState::Repeat && key != carbon::key::Code::NONE;
			}

			/**
			 * @brief Checks if a specific key was pressed.
			 * @param k The key to check.
			 * @returns `true` if the given key was pressed, `false` otherwise.
			 */
			bool isPressed(carbon::key::Code k) const {
				return anyKeyPressed() && key == k;
			}

			/**
			 * @brief Checks if a specific key was released.
			 * @param k The key to check.
			 * @returns `true` if the given key was released, `false` otherwise.
			 */
			bool isReleased(carbon::key::Code k) const {
				return anyKeyReleased() && key == k;
			}

			/**
			 * @brief Checks if a specific key was repeated.
			 * @param k The key to check.
			 * @returns `true` if the given key was repeated, `false` otherwise.
			 */
			bool isRepeated(carbon::key::Code k) const {
				return anyKeyRepeated() && key == k;
			}

			/**
			 * @brief Checks if a specific key and modifier combination was pressed.
			 * @param k The key to check.
			 * @param m The modifier to check.
			 * @returns `true` if the given key and modifier combination was pressed, `false` otherwise.
			 */
			bool isPressed(carbon::key::Code k, carbon::key::Modifier m) const {
				return isPressed(k) && modifier == m;
			}
		};

	} // namespace key

	//    __  __
	//   |  \/  |
	//   | \  / | ___  _   _ ___  ___
	//   | |\/| |/ _ \| | | / __|/ _ \
	//   | |  | | (_) | |_| \__ \  __/
	//   |_|  |_|\___/ \__,_|___/\___|
	//

	namespace mouse {

		/**
		 * @brief Stores the current position of the mouse.
		 */
		struct position {
			f64 x{ 0.0 };
			f64 y{ 0.0 };
		};

		/**
		 * @brief Codes for each button on the mouse.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__buttons.html
		 */
		enum class Button : u32 {
			_1 = 0,
			_2,
			_3,
			_4,
			_5,
			_6,
			_7,
			_8,

			Last = _8,

			Left = _1,
			Right = _2,
			Middle = _3,

			NONE = Last + 1
		};

		/**
		 * @brief Any event that occurs involving the mouse.
		 */
		struct button_event {

			/**
			 * @brief The state of the mouse.
			 */
			carbon::InputState state{ carbon::InputState::NONE };

			/**
			 * @brief The mouse button that has been clicked.
			 */
			carbon::mouse::Button button{ carbon::mouse::Button::NONE };

			/**
			 * @brief The modifier, if any, present when performing a mouse event.
			 */
			carbon::key::Modifier modifier{ carbon::key::Modifier::NONE };

			/**
			 * @returns `true` if any mouse button is pressed, `false` otherwise.
			 */
			bool anyButtonPressed() const {
				return state == carbon::InputState::Press && button != carbon::mouse::Button::NONE;
			}

			/**
			 * @returns `true` if any mouse button is released, `false` otherwise.
			 */
			bool anyButtonReleased() const {
				return state == carbon::InputState::Release && button != carbon::mouse::Button::NONE;
			}

			/**
			 * @brief Checks if a specific mouse button was pressed.
			 * @param b The mouse button to check.
			 * @returns `true` if the given mouse button was pressed, `false` otherwise.
			 */
			bool isPressed(carbon::mouse::Button b) const {
				return anyButtonPressed() && button == b;
			}

			/**
			 * @brief Checks if a specific mouse button was released.
			 * @param b The mouse button to check.
			 * @returns `true` if the given mouse button was released, `false` otherwise.
			 */
			bool isReleased(carbon::mouse::Button b) const {
				return anyButtonReleased() && button == b;
			}

		};

	} // namespace mouse

	//     _____                                      _
	//    / ____|                                    | |
	//   | |  __  __ _ _ __ ___   ___ _ __   __ _  __| |
	//   | | |_ |/ _` | '_ ` _ \ / _ \ '_ \ / _` |/ _` |
	//   | |__| | (_| | | | | | |  __/ |_) | (_| | (_| |
	//    \_____|\__,_|_| |_| |_|\___| .__/ \__,_|\__,_|
	//                               | |
	//                               |_|

	namespace gamepad {

		/**
		 * @brief Codes for the gamepad axes.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__gamepad__axes.html
		 */
		enum class Axis : u32 {
			LeftX = 0,
			LeftY,

			RightX,
			RightY,

			LeftTrigger,
			RightTrigger,

			Last = RightTrigger,

			NONE
		};

		/**
		 * @brief Codes for each button on the gamepad.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__gamepad__buttons.html
		 */
		enum class Button : u32 {
			A = 0,
			B,
			X,
			Y,

			LeftBumper,
			RightBumper,

			Back,
			Start,
			Guide,

			LeftThumb,
			RightThumb,

			DpadUp,
			DpadRight,
			DpadDown,
			DpadLeft,

			Last = DpadLeft,

			Cross = A,
			Circle = B,
			Square = X,
			Triangle = Y,

			NONE = Last + 1
		};

		/**
		 * @brief Any event that occurs involving the gamepad.
		 */
		struct event {

			/**
			 * @brief The current axis of the gamepad.
			 */
			carbon::gamepad::Axis axis{ carbon::gamepad::Axis::NONE };

			/**
			 * @brief The current button on the gamepad.
			 */
			carbon::gamepad::Button button{ carbon::gamepad::Button::NONE };

			/**
			 * @returns `true` if any button has been pressed, `false` otherwise.
			 */
			bool anyButtonPressed() const {
				return button != carbon::gamepad::Button::NONE;
			}

			/**
			 * @returns `true` if the given button was pressed, `false` otherwise.
			 */
			bool isPressed(carbon::gamepad::Button b) const {
				return button == b;
			}

		};

	} // namespace gamepad

	//         _                 _   _      _
	//        | |               | | (_)    | |
	//        | | ___  _   _ ___| |_ _  ___| | __
	//    _   | |/ _ \| | | / __| __| |/ __| |/ /
	//   | |__| | (_) | |_| \__ \ |_| | (__|   <
	//    \____/ \___/ \__, |___/\__|_|\___|_|\_\
	//                  __/ |
	//                 |___/

	namespace joystick {

		/**
		 * @brief Codes for each joystick state.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__joysticks.html
		 */
		enum class Code : u32 {
			_1 = 0,
			_2,
			_3,
			_4,
			_5,
			_6,
			_7,
			_8,
			_9,
			_10,
			_11,
			_12,
			_13,
			_14,
			_15,
			_16,

			Last = _16,

			NONE
		};

		/**
		 * @brief Codes for each joystick hat.
		 * Adapted from : https://www.glfw.org/docs/3.3/group__hat__state.html
		 */
		enum class Hat : u32 {
			Centered = 0,

			Up = 1,
			Right = 2,
			Down = 4,
			Left = 8,

			RightUp = (Right | Up),
			RightDown = (Right | Down),
			LeftUp = (Left | Up),
			LeftDown = (Left | Down),

			NONE = 20
		};

	} // namespace joystick

} // namespace carbon

#endif // INPUT_TYPES_HPP
