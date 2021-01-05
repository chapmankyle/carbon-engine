// file      : carbon/display/window/window.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef DISPLAY_WINDOW_HPP
#define DISPLAY_WINDOW_HPP

#include "carbon/macros.hpp"
#include "carbon/common/utils.hpp"
#include "carbon/display/input.hpp"

#include <glm/glm.hpp>

#include <array>
#include <string>

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class Instance;
	class Surface;

	namespace window {

		// window default constants

		static inline constexpr i32 DEFAULT_WIDTH = 800;
		static inline constexpr i32 DEFAULT_HEIGHT = 600;
		static inline constexpr i32 DEFAULT_X = 100;
		static inline constexpr i32 DEFAULT_Y = 100;

		/**
		 * @brief Mode for the window to be presented.
		 */
		enum class Mode {
			Fullscreen,
			Windowed,
			BorderlessWindowed,

			NONE
		};

		/**
		 * @brief Properties for the Window class.
		 */
		struct Props {
			/**
			 * @brief Title of the window.
			 */
			std::string title = "Application";

			/**
			 * @brief Width of the window.
			 */
			i32 width = DEFAULT_WIDTH;

			/**
			 * @brief Height of the window.
			 */
			i32 height = DEFAULT_HEIGHT;

			/**
			 * @brief The x position of the window.
			 */
			i32 x = DEFAULT_X;

			/**
			 * @brief The y position of the window.
			 */
			i32 y = DEFAULT_Y;

			/**
			 * @brief The version of the application using the window.
			 */
			utils::version version;
		};

	} // namespace window

	/**
	 * @brief Names associated with the window modes.
	 */
	static const char* m_window_mode_names[] = {
		"Fullscreen",
		"Windowed",
		"Borderless Windowed",

		"NONE"
	};

	static_assert(ARRAY_SIZE(m_window_mode_names) == static_cast<u32>(window::Mode::NONE) + 1, "Number of window modes must match number of names for the window modes.");

	/**
	 * @brief Virtual class to allow on-screen rendering.
	 * Used as a base class so that any library can be used for rendering
	 * a window, instead of being forced to use GLFW.
	 */
	class Window {

	protected:

		/**
		 * @brief Properties relating to the window.
		 */
		window::Props m_props;

		/**
		 * @brief Initial size of the window, as [width, height]
		 */
		glm::ivec2 m_initial_size{ window::DEFAULT_WIDTH, window::DEFAULT_HEIGHT };

		/**
		 * @brief Initial position of the window, as [x, y]
		 */
		glm::ivec2 m_initial_pos{ window::DEFAULT_X, window::DEFAULT_Y };

		/**
		 * @brief Current size of the window, as [width, height]
		 */
		glm::ivec2 m_size = m_initial_size;

		/**
		 * @brief Current position of the window, as [x, y]
		 */
		glm::ivec2 m_pos = m_initial_pos;

		/**
		 * @brief Keep track of when the framebuffer has been
		 * resized (when resizing or minimizing window).
		 */
		bool m_resized{ false };

		/**
		 * @brief Keep track of if the window is minimized or not.
		 */
		bool m_minimized{ false };

		/**
		 * @brief Keep track of if the window is currently in focus or not.
		 */
		bool m_focused{ false };

		/**
		 * @brief Keep track of current window mode.
		 */
		window::Mode m_window_mode{ window::Mode::Windowed };

		/**
		 * @brief Keep track of the current cursor mode.
		 */
		cursor::Mode m_cursor_mode{ cursor::Mode::Normal };

		/**
		 * @brief Keep track of any key events that occur.
		 */
		key::event m_key_event{};

		/**
		 * @brief Keep track of any button events that occur.
		 */
		mouse::button_event m_mouse_button_event{};

		/**
		 * @brief Keep track of the position of the mouse.
		 */
		mouse::position m_mouse_position{};

	private:

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	public:

		/**
		 * @brief Initializes a window for on-screen rendering.
		 * @param properties The window properties.
		 */
		Window(const window::Props &properties);

		/**
		 * @brief Initializes a window with the given title, width
		 * and height.
		 * @param title The title of the window.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 */
		Window(const std::string &title, i32 width, i32 height);

		/**
		 * @brief Initializes a window with the given width and
		 * height.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 */
		Window(i32 width, i32 height);

		/**
		 * @brief Initializes a window with default title, width
		 * and height.
		 */
		explicit Window();

		/**
		 * @brief Destructor for the window.
		 */
		~Window();

		/**
		 * @brief Pure virtual function to destroy the window object.
		 */
		virtual void destroy() = 0;

		/**
		 * @brief Pure virtual function to check if the window has not been closed.
		 * @return `true` if the window should be open, `false` otherwise.
		 */
		virtual bool shouldClose() = 0;

		/**
		 * @brief Pure virtual function to update the window.
		 */
		virtual void update() = 0;

		/**
		 * @brief Pure virtual function to wait until the window is in focus.
		 */
		virtual void waitForFocus() = 0;

		/**
		 * @brief Sets the mode of the window.
		 * @param mode The new mode to set the window to.
		 */
		virtual void setWindowMode(const window::Mode mode) = 0;

		/**
		 * @brief Sets the cursor mode when inside the window.
		 * @param mode The new mode to set the cursor to.
		 */
		virtual void setCursorMode(const cursor::Mode mode) = 0;

		/**
		 * @brief Sets the title for the window.
		 * @param title The new title for the window.
		 */
		virtual void setTitle(const std::string &title) = 0;

		/**
		 * @brief Creates a surface for the window.
		 * @param instance The instance to create the surface from.
		 * @param surface The surface that is returned.
		 * @returns The created surface.
		 */
		virtual class Surface createSurface(class Instance *instance) = 0;

		/**
		 * @returns The title of the window.
		 */
		const std::string getTitle() const;

		/**
		 * @returns The width of the window.
		 */
		const i32 getWidth() const;

		/**
		 * @returns The height of the window.
		 */
		const i32 getHeight() const;

		/*
		 * @returns The size of the window, as [width, height]
		 */
		const glm::ivec2 getSize() const;

		/**
		 * @returns The x co-ordinate of the window.
		 */
		const i32 getX() const;

		/**
		 * @returns The y co-ordinate of the window.
		 */
		const i32 getY() const;

		/*
		 * @returns The position of the window, as [x, y]
		 */
		const glm::ivec2 getPosition() const;

		/**
		 * @returns The aspect ratio of the window.
		 * The form is `width:height` and can be used as `1:<returned value>`.
		 */
		const float getAspectRatio() const;

		/**
		 * @returns `true` if the window is minimized, `false` otherwise.
		 */
		const bool isMinimized() const;

		/**
		 * @returns The current mode of the window.
		 */
		const window::Mode getWindowMode() const;

		/**
		 * @brief Gets the name of the given window mode as a string.
		 * @param mode The window mode to get as a string.
		 * @returns The window mode string.
		 */
		const char* getWindowModeName(window::Mode mode) const;

		/**
		 * @returns The current mode of the cursor inside the window.
		 */
		const cursor::Mode getCursorMode() const;

		/**
		 * @returns `true` if the mouse is visible, `false` otherwise.
		 */
		const bool isMouseVisible() const;

		/**
		 * @returns The version of the application.
		 */
		const utils::version& getVersion() const;

	};

} // namespace carbon

#endif // DISPLAY_WINDOW_HPP
