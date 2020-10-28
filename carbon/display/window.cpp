#include "window.hpp"

#include "carbon/core/instance.hpp"
#include "carbon/display/surface.hpp"

namespace carbon {

	void Window::createWindow() {
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
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

		// set callback for framebuffer resize
		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
	}


	void Window::framebufferResizeCallback(GLFWwindow *window, i32 width, i32 height) {
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		app->m_resized = true;

		// update width and height in application
		app->m_width = width;
		app->m_height = height;

		if (width == 0 || height == 0) {
			app->m_minimized = true;
		} else {
			app->m_minimized = false;
		}
	}


	Window::Window(const char *title, const i32 width, const i32 height, utils::version version)
		: m_title(title)
		, m_initial_width(width)
		, m_initial_height(height)
		, m_width(width)
		, m_height(height)
		, m_version(version)
	{
		createWindow();
	}


	Window::Window() {
		createWindow();
	}


	Window::~Window() {
		destroy();
	}


	void Window::destroy() {
		// destroy and free window
		glfwDestroyWindow(m_window);

		// terminate GLFW
		glfwTerminate();
	}


	bool Window::shouldClose() {
		return static_cast<bool>(glfwWindowShouldClose(m_window));
	}


	void Window::update() {
		glfwPollEvents();
	}


	void Window::waitForFocus() {
		int width{ 0 };
		int height{ 0 };

		while (width == 0 || height == 0 || m_minimized) {
			glfwGetFramebufferSize(m_window, &width, &height);
			glfwWaitEvents();
		}
	}



	void Window::setWindowMode(WindowMode mode) {
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
				glfwSetWindowMonitor(m_window, m_monitor, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);
				break;
			case WindowMode::Windowed:
				glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
				glfwSetWindowMonitor(m_window, nullptr, 100, 100, m_initial_width, m_initial_height, GLFW_DONT_CARE);
				break;
			case WindowMode::BorderlessWindowed:
				glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
				glfwSetWindowMonitor(m_window, nullptr, 100, 100, m_initial_width, m_initial_height, GLFW_DONT_CARE);
				break;
		}
	}


	void Window::setCursorMode(CursorMode mode) {
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


	Surface Window::createSurface(Instance *instance) {
		return Surface(instance, m_window);
	}

} // namespace carbon
