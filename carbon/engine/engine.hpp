// file      : carbon/engine/engine.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "config.hpp"
#include "carbon/common/utils.hpp"
#include "carbon/display/window.hpp"

#include <string>

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class Instance;
	class PhysicalDevice;
	class LogicalDevice;
	class Surface;

	/**
	 * @brief Main engine that can be used to start creating a game.
	 * Performs all necessary Vulkan setup so that you can focus on
	 * creating the game!
	 */
	class Engine {

	private:

		/**
		 * @brief Base Vulkan instance needed for almost everything.
		 */
		class Instance *m_instance = nullptr;

		/**
		 * @brief Physical device to perform computation on (GPU).
		 */
		class PhysicalDevice *m_physical_device = nullptr;

		/**
		 * @brief Logical device used to send commands to physical device.
		 */
		class LogicalDevice *m_logical_device = nullptr;

		/**
		 * @brief Surface to render swapchain images to.
		 */
		class Surface *m_surface = nullptr;

		/**
		 * @brief Base window that handles user interaction.
		 */
		Window *m_window = nullptr;

		/**
		 * @brief Properties of the window.
		 */
		WindowProps m_props{};

		/**
		 * @brief Used to indicate if a resize operation is necessary.
		 */
		bool m_resized = false;

		/**
		 * @brief Keeps track of the current frame in flight.
		 */
		size_t m_current_frame = 0;

		/**
		 * @brief Creates the window for the Engine.
		 */
		void createWindow();

		/**
		 * @brief Creates all necessary Vulkan backend classes
		 * needed to start the Engine.
		 */
		void createVulkan();

	public:

		/**
		 * @brief Initializes the engine with a name. Version number is optional.
		 * @param properties The properties for the Engine window.
		 */
		Engine(const WindowProps &properties);

		/**
		 * @brief Initializes the engine with all default settings.
		 */
		explicit Engine();

		/**
		 * @brief Destructor for the Engine.
		 */
		~Engine();

		/**
		 * @returns `true` if the engine is running, `false` otherwise.
		 */
		bool isRunning() const;

		/**
		 * @brief Updates the engine.
		 */
		void update();

		/**
		 * @returns The instance associated with the engine.
		 */
		const class Instance& getInstance() const;

	};

} // namespace carbon

#endif // ENGINE_HPP
