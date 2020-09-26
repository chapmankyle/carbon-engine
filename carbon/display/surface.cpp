#include "surface.hpp"

#include "carbon/core/instance.hpp"

carbon::Surface::Surface(carbon::Instance *instance, GLFWwindow *window)
	: m_instance(instance)
	, m_window(window)
{
	// check if surface creation was successful
	if (glfwCreateWindowSurface(m_instance->getHandle(), m_window, nullptr, &m_surface) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create window surface!");
	}
}


carbon::Surface::~Surface() {
	destroy();
}


void carbon::Surface::destroy() {
	if (m_surface == VK_NULL_HANDLE) {
		return;
	}

	// destroy and reset
	vkDestroySurfaceKHR(m_instance->getHandle(), m_surface, nullptr);
	m_surface = VK_NULL_HANDLE;
}


const VkSurfaceKHR& carbon::Surface::getHandle() const {
	return m_surface;
}
