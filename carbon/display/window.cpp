#include "window.hpp"

GLFWwindow* carbon::Window::createWindow() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW!");
	}

	if (!glfwVulkanSupported()) {
		throw std::runtime_error("Vulkan not supported!");
	}

	// specify not to use OpenGL context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// no resize support, yet!
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	return glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
}


carbon::Window::Window(const char *title, const int width, const int height, carbon::utils::version version)
	: m_title(title)
	, m_width(width)
	, m_height(height)
	, m_version(version)
	, m_window(createWindow())
	, m_instance(m_title, m_version)
{ }


carbon::Window::Window()
	: m_title(m_default_title)
	, m_width(m_default_width)
	, m_height(m_default_height)
	, m_version(carbon::utils::version{ 1, 0, 0 })
	, m_window(createWindow())
	, m_instance(m_title, m_version)
{ }


carbon::Window::~Window() {
	destroy();
}


void carbon::Window::destroy() {
	// destroy instance
	m_instance.destroy();

	// destroy and free window
	glfwDestroyWindow(m_window);

	// terminate GLFW
	glfwTerminate();
}


bool carbon::Window::isOpen() {
	return static_cast<bool>(!glfwWindowShouldClose(m_window));
}


void carbon::Window::pollEvents() {
	glfwPollEvents();
}
