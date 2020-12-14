// file      : carbon/display/window/window_glfw.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "window_glfw.hpp"

#include "carbon/core/instance.hpp"
#include "carbon/display/surface.hpp"

namespace carbon {

	void WindowGLFW::createWindow() {
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW!");
		}

		if (!glfwVulkanSupported()) {
			throw std::runtime_error("Vulkan not supported!");
		}

		// specify not to use OpenGL context
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		// monitor to use for fullscreen
		m_monitor = glfwGetPrimaryMonitor();

		// create window
		m_window = glfwCreateWindow(m_props.width, m_props.height, m_props.title.c_str(), nullptr, nullptr);
		glfwSetWindowMonitor(m_window, nullptr, m_props.x, m_props.y, m_props.width, m_props.height, GLFW_DONT_CARE);

		// set callback for framebuffer resize
		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
	}


	void WindowGLFW::framebufferResizeCallback(GLFWwindow *window, i32 width, i32 height) {
		auto app = reinterpret_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		app->m_resized = true;

		// update width and height in application
		app->m_props.width = width;
		app->m_props.height = height;

		if (width == 0 || height == 0) {
			app->m_minimized = true;
		} else {
			app->m_minimized = false;
		}
	}


	WindowGLFW::WindowGLFW(const WindowProps &properties)
		: Window(properties)
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


	void WindowGLFW::setWindowMode(const WindowMode mode) {
		// nothing has changed
		if (m_window_mode == mode) {
			return;
		}

		// change window mode
		m_window_mode = mode;

		const GLFWvidmode *videoMode = glfwGetVideoMode(m_monitor);

		switch (mode) {
			case WindowMode::Fullscreen:
				glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
				glfwSetWindowMonitor(m_window, m_monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
				break;
			case WindowMode::Windowed:
				glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
				glfwSetWindowMonitor(m_window, nullptr, m_props.x, m_props.y, m_initial_width, m_initial_height, GLFW_DONT_CARE);
				break;
			case WindowMode::BorderlessWindowed:
				glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
				glfwSetWindowMonitor(m_window, nullptr, m_props.x, m_props.y, m_initial_width, m_initial_height, GLFW_DONT_CARE);
				break;
		}
	}


	void WindowGLFW::setCursorMode(const CursorMode mode) {
		// nothing has changed
		if (m_cursor_mode == mode) {
			return;
		}

		// change visibility
		m_cursor_mode = mode;

		switch (mode) {
			case CursorMode::Normal:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;
			case CursorMode::Hidden:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				break;
			case CursorMode::Disabled:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;
		}
	}


	Surface WindowGLFW::createSurface(Instance *instance) {
		return Surface(instance, m_window);
	}

} // namespace carbon