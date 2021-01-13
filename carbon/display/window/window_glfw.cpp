// file      : carbon/display/window/window_glfw.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "window_glfw.hpp"

#include "carbon/common/logger.hpp"
#include "carbon/core/instance.hpp"
#include "carbon/display/surface.hpp"

namespace carbon {

	void WindowGLFW::createWindow() {
		if (!glfwInit()) {
			CARBON_LOG_FATAL(carbon::log::To::File, "Failed to initialize GLFW.");
		}

		if (!glfwVulkanSupported()) {
			CARBON_LOG_FATAL(carbon::log::To::File, "Vulkan not supported.");
		}

		// specify not to use OpenGL context
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		// set whether or not the window should be resizable
		glfwWindowHint(GLFW_RESIZABLE, (m_props.resizable ? GLFW_TRUE : GLFW_FALSE));

		// monitor to use for fullscreen
		m_monitor = glfwGetPrimaryMonitor();

		// create window
		m_window = glfwCreateWindow(m_props.width, m_props.height, m_props.title.c_str(), nullptr, nullptr);
		glfwSetWindowMonitor(m_window, nullptr, m_props.x, m_props.y, m_props.width, m_props.height, GLFW_DONT_CARE);

		// access local variables through the window
		glfwSetWindowUserPointer(m_window, this);

		// set callback functions
		glfwSetFramebufferSizeCallback(m_window, callbackFramebufferResizeGLFW);
		glfwSetWindowFocusCallback(m_window, callbackWindowFocusGLFW);
		glfwSetWindowPosCallback(m_window, callbackWindowPositionGLFW);
		glfwSetKeyCallback(m_window, callbackKeyGLFW);
		glfwSetMouseButtonCallback(m_window, callbackMouseButtonGLFW);
		glfwSetCursorPosCallback(m_window, callbackMousePositionGLFW);
	}


	void WindowGLFW::callbackFramebufferResizeGLFW(GLFWwindow *window, i32 width, i32 height) {
		auto app = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		app->m_resized = true;

		// update width and height in application
		app->m_size[0] = width;
		app->m_size[1] = height;

		if (width == 0 || height == 0) {
			app->m_minimized = true;
		} else {
			app->m_minimized = false;
		}
	}


	void WindowGLFW::callbackWindowFocusGLFW(GLFWwindow *window, i32 focused) {
		auto app = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

		// update focus for window
		app->m_focused = static_cast<bool>(focused);
	}


	void WindowGLFW::callbackWindowPositionGLFW(GLFWwindow *window, i32 xpos, i32 ypos) {
		auto app = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

		// update x and y co-ordinates in application
		app->m_pos[0] = xpos;
		app->m_pos[1] = ypos;
	}


	void WindowGLFW::callbackKeyGLFW(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mods) {
		auto app = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

		// update current key activated
		app->m_key_event.key = static_cast<key::Code>(key);
		app->m_key_event.modifier = static_cast<key::Modifier>(mods);
		app->m_key_event.state = static_cast<InputState>(action);
	}


	void WindowGLFW::callbackMouseButtonGLFW(GLFWwindow *window, i32 button, i32 action, i32 mods) {
		auto app = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

		// update mouse button
		app->m_mouse_button_event.button = static_cast<mouse::Button>(button);
		app->m_mouse_button_event.modifier = static_cast<key::Modifier>(mods);
		app->m_mouse_button_event.state = static_cast<InputState>(action);
	}


	void WindowGLFW::callbackMousePositionGLFW(GLFWwindow *window, f64 xpos, f64 ypos) {
		auto app = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

		// update current mouse position
		app->m_mouse_position.x = xpos;
		app->m_mouse_position.y = ypos;
	}


	WindowGLFW::WindowGLFW(const window::Props &properties)
		: Window(properties)
	{
		createWindow();
	}


	WindowGLFW::WindowGLFW(const std::string &title, i32 width, i32 height)
		: Window(title, width, height)
	{
		createWindow();
	}


	WindowGLFW::WindowGLFW(i32 width, i32 height)
		: Window(width, height)
	{
		createWindow();
	}


	WindowGLFW::WindowGLFW()
		: Window()
	{
		createWindow();
	}


	WindowGLFW::~WindowGLFW() {
		destroy();
	}


	void WindowGLFW::destroy() {
		// destroy and free window
		glfwDestroyWindow(m_window);

		// terminate GLFW
		glfwTerminate();
	}


	bool WindowGLFW::shouldClose() {
		return static_cast<bool>(glfwWindowShouldClose(m_window));
	}


	void WindowGLFW::update() {
		glfwPollEvents();
	}


	void WindowGLFW::waitForFocus() {
		int width{ 0 };
		int height{ 0 };

		while (width == 0 || height == 0 || m_minimized) {
			glfwGetFramebufferSize(m_window, &width, &height);
			glfwWaitEvents();
		}
	}


	void WindowGLFW::setWindowMode(const window::Mode mode) {
		// nothing has changed
		if (m_window_mode == mode) {
			return;
		}

		// change window mode
		m_window_mode = mode;

		const GLFWvidmode *videoMode = glfwGetVideoMode(m_monitor);

		switch (mode) {
			case window::Mode::Fullscreen:
				glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
				glfwSetWindowMonitor(m_window, m_monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
				break;
			case window::Mode::Windowed:
				glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
				glfwSetWindowMonitor(m_window, nullptr, m_initial_pos[0], m_initial_pos[1], m_initial_size[0], m_initial_size[1], GLFW_DONT_CARE);
				break;
			case window::Mode::BorderlessWindowed:
				glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
				glfwSetWindowMonitor(m_window, nullptr, m_initial_pos[0], m_initial_pos[1], m_initial_size[0], m_initial_size[1], GLFW_DONT_CARE);
				break;
		}
	}


	void WindowGLFW::setCursorMode(const cursor::Mode mode) {
		// nothing has changed
		if (m_cursor_mode == mode) {
			return;
		}

		// change visibility
		m_cursor_mode = mode;

		switch (mode) {
			case cursor::Mode::Normal:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;
			case cursor::Mode::Hidden:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				break;
			case cursor::Mode::Disabled:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;
		}
	}


	void WindowGLFW::setTitle(const std::string &title) {
		// title has not changed
		if (m_props.title == title) {
			return;
		}

		// change title and update in window
		m_props.title = title;
		glfwSetWindowTitle(m_window, title.c_str());
	}


	Surface WindowGLFW::createSurface(Instance *instance) {
		return Surface(instance, m_window);
	}

} // namespace carbon
