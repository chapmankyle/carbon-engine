// file      : carbon/display/window.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef DISPLAY_WINDOW_HPP
#define DISPLAY_WINDOW_HPP

#include "carbon/setup.hpp"
#include "carbon/common/utils.hpp"

#include <string>

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class Instance;
	class Surface;

	/**
	 * @brief Mode for the window to be presented.
	 */
	enum class WindowMode {
		Fullscreen,
		Windowed,
		BorderlessWindowed,

		NONE
	};

	/**
	 * @brief Names associated with the window modes.
	 */
	static const char* m_window_mode_names[] = {
		"Fullscreen",
		"Windowed",
		"Borderless Windowed",

		"NONE"
	};

	static_assert(ARRAY_SIZE(m_window_mode_names) == static_cast<u32>(WindowMode::NONE) + 1, "Number of window modes must match number of names for the window modes.");

	/**
	 * @brief Mode for when the cursor is inside the window.
	 */
	enum class CursorMode {
		Normal,
		Hidden,
		Disabled,

		NONE
	};

	/**
	 * @brief Class to allow on-screen rendering using GLFW.
	 */
	class Window {

		private:

		/**
		 * @brief Title of the window.
		 */
		std::string m_title{ "Game" };

		/**
		 * @brief Initial width of the window, upon creation.
		 */
		i32 m_initial_width{ 800 };

		/**
		 * @brief Initial height of the window, upon creation.
		 */
		i32 m_initial_height{ 600 };

		/**
		 * @brief Width of the window.
		 */
		i32 m_width{ m_initial_width };

		/**
		 * @brief Height of the window.
		 */
		i32 m_height{ m_initial_height };

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
		 * @brief Keep track of current window mode.
		 */
		WindowMode m_window_mode{ WindowMode::Windowed };

		/**
		 * @brief Keep track of the current cursor mode.
		 */
		CursorMode m_cursor_mode{ CursorMode::Normal };

		/**
		 * @brief Version number.
		 */
		utils::version m_version = { 1, 0, 0 };

		/**
		 * @brief Handle to the GLFW window object.
		 */
		GLFWwindow *m_window;

		/**
		 * @brief Monitor to use for fullscreen mode.
		 */
		GLFWmonitor *m_monitor;

		/**
		 * @brief Creates the GLFW window.
		 */
		void createWindow();

		/**
		 * @brief Callback for when GLFW detects that the framebuffer
		 * has been resized.
		 * @param window The GLFWwindow object to detect resize on.
		 * @param width The new width of the framebuffer.
		 * @param height The new height of the framebuffer.
		 */
		static void framebufferResizeCallback(GLFWwindow *window, i32 width, i32 height);

	public:

		/**
		 * @brief Initializes a GLFW window for on-screen rendering.
		 * @param title The title of the window.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 * @param version Optional. The version of the application.
		 */
		Window(const char *title, const i32 width, const i32 height, utils::version version = { 1, 0, 0 });

		/**
		 * @brief Initializes a GLFW window with default title, width
		 * and height.
		 */
		explicit Window();

		/**
		 * @brief Destructor for the GLFW window.
		 */
		~Window();

		/**
		 * @brief Destroys the window object.
		 */
		void destroy();

		/**
		 * @brief Checks if the window has not been closed.
		 * @return `true` if the window should be open, `false` otherwise.
		 */
		bool shouldClose();

		/**
		 * @brief Polls the event queue to find if anything happened.
		 */
		void update();

		/**
		 * @brief Waits until the window has is not minimized.
		 */
		void waitForFocus();

		/**
		 * @brief Sets the mode of the window.
		 * @param mode The new mode to set the window to.
		 */
		void setWindowMode(WindowMode mode);

		/**
		 * @brief Sets the cursor mode when inside the window.
		 * @param mode The new mode to set the cursor to.
		 */
		void setCursorMode(CursorMode mode);

		/**
		 * @brief Creates a surface for the window.
		 * @param instance The instance to create the surface from.
		 * @param surface The surface that is returned.
		 * @returns The created surface.
		 */
		class Surface createSurface(class Instance *instance);

		/**
		 * @returns The handle on the underlying GLFWwindow object.
		 */
		GLFWwindow* getHandle() const {
			return m_window;
		}

		/**
		 * @returns The title of the window.
		 */
		const std::string getTitle() const {
			return m_title;
		}

		/**
		 * @returns The width of the window.
		 */
		const i32 getWidth() const {
			return m_width;
		}

		/**
		 * @returns The height of the window.
		 */
		const i32 getHeight() const {
			return m_height;
		}

		/**
		 * @returns The aspect ratio of the window.
		 */
		const float getAspectRatio() const {
			return static_cast<float>(m_width) / static_cast<float>(m_height);
		}

		/**
		 * @returns `true` if the window is minimized, `false` otherwise.
		 */
		const bool isMinimized() const {
			return m_minimized;
		}

		/**
		 * @returns The current mode of the window.
		 */
		const WindowMode getWindowMode() const {
			return m_window_mode;
		}

		/**
		 * @brief Gets the name of the given window mode as a string.
		 * @param mode The window mode to get as a string.
		 * @returns The window mode string.
		 */
		const char* getWindowModeName(WindowMode mode) const {
			i32 idx = static_cast<i32>(mode);
			assert(idx < static_cast<i32>(WindowMode::NONE) + 1 && "[ERROR] Invalid window mode!");

			return m_window_mode_names[idx];
		}

		/**
		 * @returns The current mode of the cursor inside the window.
		 */
		const CursorMode getCursorMode() const {
			return m_cursor_mode;
		}

		/**
		 * @returns `true` if the mouse is visible, `false` otherwise.
		 */
		const bool isMouseVisible() const {
			return m_cursor_mode == CursorMode::Normal;
		}

		/**
		 * @returns The version of the application.
		 */
		const utils::version& getVersion() const {
			return m_version;
		}

	};

} // namespace carbon

#endif // DISPLAY_WINDOW_HPP
