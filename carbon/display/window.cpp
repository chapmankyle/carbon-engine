#include "window.hpp"

#include "carbon/core/instance.hpp"
#include "carbon/display/surface.hpp"

void carbon::Window::createWindow() {
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


void carbon::Window::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
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


carbon::Window::Window(const char *title, const int width, const int height, carbon::utils::version version)
	: m_title(title)
	, m_initial_width(width)
	, m_initial_height(height)
	, m_width(width)
	, m_height(height)
	, m_version(version)
{
	createWindow();
}


carbon::Window::Window() {
	createWindow();
}


carbon::Window::~Window() {
	destroy();
}


void carbon::Window::destroy() {
	// destroy and free window
	glfwDestroyWindow(m_window);

	// terminate GLFW
	glfwTerminate();
}


bool carbon::Window::shouldClose() {
	return static_cast<bool>(glfwWindowShouldClose(m_window));
}


void carbon::Window::update() {
	glfwPollEvents();
}


void carbon::Window::waitForFocus() {
	int width{ 0 };
	int height{ 0 };

	while (width == 0 || height == 0 || m_minimized) {
		glfwGetFramebufferSize(m_window, &width, &height);
		glfwWaitEvents();
	}
}


void carbon::Window::setMouseVisible(bool visible) {
	// nothing has changed
	if (m_mouse_visible == visible) {
		return;
	}

	// change visibility
	m_mouse_visible = visible;

	if (visible) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}


void carbon::Window::setWindowMode(WindowMode mode) {
	// nothing has changed
	if (m_mode == mode) {
		return;
	}

	// change window mode
	m_mode = mode;

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


carbon::Surface carbon::Window::createSurface(Instance *instance) {
	return carbon::Surface(instance, m_window);
}
