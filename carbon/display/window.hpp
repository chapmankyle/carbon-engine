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
		SIZE
	};

	/**
	 * @brief Class to allow on-screen rendering using GLFW.
	 */
	class Window {

	private:

		/**
		 * @brief Title of the window.
		 */
		std::string m_title = "Game";

		/**
		 * @brief Initial width of the window, upon creation.
		 */
		int m_initial_width = 800;

		/**
		 * @brief Initial height of the window, upon creation.
		 */
		int m_initial_height = 600;

		/**
		 * @brief Width of the window.
		 */
		int m_width = 800;

		/**
		 * @brief Height of the window.
		 */
		int m_height = 600;

		/**
		 * @brief Keep track of when the framebuffer has been
		 * resized (when resizing or minimizing window).
		 */
		bool m_resized = false;

		/**
		 * @brief Keep track of if the window is minimized or not.
		 */
		bool m_minimized = false;

		/**
		 * @brief Keep track of whether or not to show the mouse in
		 * the window.
		 */
		bool m_mouse_visible = true;

		/**
		 * @brief Keep track of current window mode.
		 */
		WindowMode m_mode = WindowMode::Windowed;

		/**
		 * @brief Version number.
		 */
		carbon::utils::version m_version = { 1, 0, 0 };

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
		static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

	public:

		/**
		 * @brief Initializes a GLFW window for on-screen rendering.
		 * @param title The title of the window.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 * @param version Optional. The version of the application.
		 */
		Window(const char *title, const int width, const int height, carbon::utils::version version = { 1, 0, 0 });

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
		 * @brief Sets the mouse to be visible or not.
		 * @param visible `true` if the mouse should be shown,
		 * otherwise `false` to hide mouse.
		 */
		void setMouseVisible(bool visible);

		/**
		 * @brief Sets the mode of the window.
		 * @param mode The new mode to set the window to.
		 */
		void setWindowMode(WindowMode mode);

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
		const int getWidth() const {
			return m_width;
		}

		/**
		 * @returns The height of the window.
		 */
		const int getHeight() const {
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
		 * @returns `true` if the mouse is visible, `false` otherwise.
		 */
		const bool isMouseVisible() const {
			return m_mouse_visible;
		}

		/**
		 * @returns The current mode of the window.
		 */
		const WindowMode getWindowMode() const {
			return m_mode;
		}

		/**
		 * @returns The version of the application.
		 */
		const carbon::utils::version& getVersion() const {
			return m_version;
		}

	};

} // namespace carbon

#endif // DISPLAY_WINDOW_HPP
