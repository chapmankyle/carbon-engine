#pragma once

#ifndef DISPLAY_WINDOW_HPP
#define DISPLAY_WINDOW_HPP

#include "carbon/setup.hpp"
#include "carbon/common/utils.hpp"
#include "carbon/core/instance.hpp"

namespace carbon {

	/*
	 * @brief Class to allow on-screen rendering using GLFW.
	 */
	class Window {

	private:

		/*
		 * @brief Title to use when no title is supplied.
		 */
		inline static constexpr char *m_default_title{ "Game" };

		/*
		 * @brief Width to use when no width is supplied.
		 */
		inline static constexpr int m_default_width{ 800 };

		/*
		 * @brief Height to use when no height is supplied.
		 */
		inline static constexpr int m_default_height{ 600 };

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
		 * @brief Version number.
		 */
		carbon::utils::version m_version;

		/*
		 * @brief Handle to the GLFW window object.
		 */
		GLFWwindow *m_window;

		/*
		 * @brief Handle to the instance from which to render.
		 */
		Instance m_instance;

		/*
		 * @brief Creates the GLFW window.
		 */
		GLFWwindow* createWindow();

	public:

		/*
		 * @brief Initializes a GLFW window for on-screen rendering.
		 * @param title The title of the window.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 * @param version Optional. The version of the application.
		 */
		Window(const char *title, const int width, const int height, carbon::utils::version version = { 1, 0, 0 });

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

		/*
		 * @returns The instance that is by the current window.
		 */
		const Instance& getInstance();

		/*
		 * @returns The version of the application.
		 */
		const carbon::utils::version& getVersion();

	};

} // namespace carbon

#endif // DISPLAY_WINDOW_HPP

