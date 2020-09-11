#include "window.hpp"

void carbon::Window::createInstance() {
	m_instance = carbon::Instance(m_title, m_version);
}


void carbon::Window::init() {
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

	// create window
	m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

	// create instance
	createInstance();
}


carbon::Window::Window(const char *title, const int width, const int height, carbon::utils::version version) {
	m_title = title;
	m_width = width;
	m_height = height;
	m_version = version;

	init();
}


carbon::Window::Window() {
	m_title = m_default_title;
	m_width = m_default_width;
	m_height = m_default_height;
	m_version = carbon::utils::version{ 1, 0, 0 };

	init();
}


carbon::Window::~Window() {
	destroy();
}


void carbon::Window::destroy() {
	// destroy instance
	if (m_instance.getHandle() != nullptr) {
		vkDestroyInstance(m_instance.getHandle(), nullptr);
	}

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


const char *carbon::Window::getTitle() {
	return m_title;
}


const int carbon::Window::getWidth() {
	return m_width;
}


const int carbon::Window::getHeight() {
	return m_height;
}


const carbon::Instance& carbon::Window::getInstance() {
	return m_instance;
}

