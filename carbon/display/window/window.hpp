// file      : carbon/display/window/window.hpp
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
	 * @brief Properties for the Window class.
	 */
	struct WindowProps {
		/**
		 * @brief Title of the window.
		 */
		std::string title = "Application";

		/**
		 * @brief Width of the window.
		 */
		i32 width = 800;

		/**
		 * @brief Height of the window.
		 */
		i32 height = 600;

		/**
		 * @brief The x position of the window.
		 */
		i32 x = 100;

		/**
		 * @brief The y position of the window.
		 */
		i32 y = 100;

		/**
		 * @brief The version of the application using the window.
		 */
		utils::version version;
	};

	/**
	 * @brief Class to allow on-screen rendering.
	 */
	class Window {

	protected:

		/**
		 * @brief Properties relating to the window.
		 */
		WindowProps m_props;

		/**
		 * @brief Initial width of the window, upon creation.
		 */
		i32 m_initial_width{ 800 };

		/**
		 * @brief Initial height of the window, upon creation.
		 */
		i32 m_initial_height{ 600 };

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

	public:

		/**
		 * @brief Initializes a window for on-screen rendering.
		 * @param properties The window properties.
		 */
		Window(const WindowProps &properties);

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
		 * @brief Destroys the window object.
		 */
		virtual void destroy() = 0;

		/**
		 * @brief Checks if the window has not been closed.
		 * @return `true` if the window should be open, `false` otherwise.
		 */
		virtual bool shouldClose() = 0;

		/**
		 * @brief Updates the window.
		 */
		virtual void update() = 0;

		/**
		 * @brief Waits until the window has is not minimized.
		 */
		virtual void waitForFocus() = 0;

		/**
		 * @brief Sets the mode of the window.
		 * @param mode The new mode to set the window to.
		 */
		virtual void setWindowMode(const WindowMode mode) = 0;

		/**
		 * @brief Sets the cursor mode when inside the window.
		 * @param mode The new mode to set the cursor to.
		 */
		virtual void setCursorMode(const CursorMode mode) = 0;

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
		const WindowMode getWindowMode() const;

		/**
		 * @brief Gets the name of the given window mode as a string.
		 * @param mode The window mode to get as a string.
		 * @returns The window mode string.
		 */
		const char* getWindowModeName(WindowMode mode) const;

		/**
		 * @returns The current mode of the cursor inside the window.
		 */
		const CursorMode getCursorMode() const;

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
