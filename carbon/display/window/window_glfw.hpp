// file      : carbon/display/window/window_glfw.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef DISPLAY_WINDOW_GLFW_HPP
#define DISPLAY_WINDOW_GLFW_HPP

#include "carbon/display/window/window.hpp"

namespace carbon {

	/**
	 * @brief Class to allow on-screen rendering from base Window class using GLFW.
	 */
	class WindowGLFW : public Window {

	private:

		/**
		 * @brief Handle to the GLFW window object.
		 */
		GLFWwindow *m_window;

		/**
		 * @brief Monitor to use for fullscreen mode.
		 */
		GLFWmonitor *m_monitor;

		/**
		 * @brief Creates the window using GLFW.
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

		/**
		 * @brief Callback for when GLFW detects that the window
		 * position has changed.
		 * @param window The GLFWwindow object.
		 * @param xpos The new x co-ordinate of the window.
		 * @param ypos The new y co-ordinate of the window.
		 */
		static void windowPositionCallback(GLFWwindow *window, i32 xpos, i32 ypos);

	public:

		/**
		 * @brief Initializes a GLFW window for on-screen rendering.
		 * @param properties The window properties.
		 */
		WindowGLFW(const window::Props &properties);

		/**
		 * @brief Initializes a GLFW window with default title, width
		 * and height.
		 */
		explicit WindowGLFW();

		/**
		 * @brief Destructor for the GLFW window class.
		 */
		~WindowGLFW();

		/**
		 * @brief Destroys the GLFW window object.
		 */
		virtual void destroy() override;

		/**
		 * @brief Checks if the window has not been closed.
		 * @return `true` if the window should be open, `false` otherwise.
		 */
		virtual bool shouldClose() override;

		/**
		 * @brief Updates the window to check for any changes.
		 */
		virtual void update() override;

		/**
		 * @brief Waits until the window has is not minimized.
		 */
		virtual void waitForFocus() override;

		/**
		 * @brief Sets the mode of the window.
		 * @param mode The new mode to set the window to.
		 */
		virtual void setWindowMode(const window::Mode mode) override;

		/**
		 * @brief Sets the cursor mode when inside the window.
		 * @param mode The new mode to set the cursor to.
		 */
		virtual void setCursorMode(const cursor::Mode mode) override;

		/**
		 * @brief Sets the title for the window.
		 * @param title The new title for the window.
		 */
		virtual void setTitle(const std::string &title) override;

		/**
		 * @brief Creates a surface for the window.
		 * @param instance The instance to create the surface from.
		 * @param surface The surface that is returned.
		 * @returns The created surface.
		 */
		virtual class Surface createSurface(class Instance *instance) override;

		/**
		 * @returns The handle on the underlying GLFWwindow object.
		 */
		GLFWwindow* getHandle() const {
			return m_window;
		}

	};

} // namespace carbon

#endif // DISPLAY_WINDOW_GLFW_HPP
