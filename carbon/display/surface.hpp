#pragma once

#ifndef DISPLAY_SURFACE_HPP
#define DISPLAY_SURFACE_HPP

#include "carbon/setup.hpp"

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class Instance;

	/**
	 * @brief A wrapper for the Vulkan surface extension that uses
	 * GLFW as the window surface creation technique.
	 */
	class Surface {

	private:

		/**
		 * @brief Handle on the instance to create the surface on.
		 */
		class Instance *m_instance;

		/**
		 * @brief Handle on the underlying Vulkan surface.
		 */
		VkSurfaceKHR m_surface{ VK_NULL_HANDLE };

		/**
		 * @brief Handle to the GLFW window object.
		 */
		GLFWwindow *m_window;

	public:

		/**
		 * @brief Initializes a surface for displaying to.
		 * @param instance The instance to create the surface on.
		 * @param window The GLFW window object.
		 */
		explicit Surface(class Instance *instance, GLFWwindow *window);

		/**
		 * @brief Destructor for a surface.
		 */
		~Surface();

		/**
		 * @brief Destroys a surface.
		 * Must be destroyed after logical device and before instance.
		 */
		void destroy();

		/**
		 * @returns The handle of the underlying surface.
		 */
		const VkSurfaceKHR& getHandle() const {
			return m_surface;
		}

	};

} // namespace carbon

#endif // DISPLAY_SURFACE_HPP
