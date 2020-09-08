#pragma once

#ifndef DISPLAY_WINDOW_HPP
#define DISPLAY_WINDOW_HPP

#include "carbon/setup.hpp"

namespace carbon {

	/*
	 * @brief Class to allow on-screen rendering using GLFW.
	 */
	class Window {

	private:

		/*
		 * @brief Handle to the GLFW window object.
		 */
		GLFWwindow *m_window;

		/*
		 * @brief Title of the window.
		 */
		const char *m_title;

		/*
		 * @brief Width of the window.
		 */
		int m_width;

		/*
		 * @brief Height of the window.
		 */
		int m_height;

		/*
		 * @brief Title to use when no title is supplied.
		 */
		const char *m_default_title = "Game";

		/*
		 * @brief Width to use when no width is supplied.
		 */
		const int m_default_width = 800;

		/*
		 * @brief Height to use when no height is supplied.
		 */
		const int m_default_height = 600;

		/*
		 * @brief Initializes the window.
		 */
		void init();

	public:

		/*
		 * @brief Initializes a GLFW window for on-screen rendering.
		 * @param title The title of the window.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 */
		Window(const char *title, const int width, const int height);

		/*
		 * @brief Initializes a GLFW window with default title, width
		 * and height.
		 */
		Window();

		/*
		 * @brief Destructor for the GLFW window.
		 */
		~Window();

		/*
		 * @brief Destroys the window object.
		 */
		void destroy();

		/*
		 * @brief Checks if the window has not been closed.
		 * @return `true` if the window should be open, `false` otherwise.
		 */
		bool isOpen();

		/*
		 * @brief Polls the event queue to find if anything happened.
		 */
		void pollEvents();

		/*
		 * @returns The title of the window.
		 */
		const char *getTitle();

		/*
		 * @returns The width of the window.
		 */
		const int getWidth();

		/*
		 * @returns The height of the window.
		 */
		const int getHeight();

	};

} // namespace carbon

#endif // DISPLAY_WINDOW_HPP

