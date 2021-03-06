// file      : carbon/engine/engine.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "engine.hpp"

#include "carbon/common/logger.hpp"
#include "carbon/core/instance.hpp"
#include "carbon/core/physical_device.hpp"
#include "carbon/core/logical_device.hpp"
#include "carbon/display/surface.hpp"
#include "carbon/display/swapchain.hpp"

namespace carbon {

	void Engine::createWindow() {
		m_window = new WindowGLFW(m_props);
	}


	void Engine::createVulkan() {
		// create instance
		m_instance = new Instance(m_props.title, m_props.version);

		// create surface for rendering to
		m_surface = new Surface(m_instance, m_window->getHandle());

		// create physical device used for computation
		m_physical_device = new PhysicalDevice(m_instance);

		// create logical device
		m_logical_device = new LogicalDevice(m_instance, m_physical_device, m_surface);

		// create swapchain
		m_swapchain = new Swapchain(m_window->getHandle(), m_logical_device, m_physical_device, m_surface);
	}


	Engine::Engine(const window::Props &properties)
		: m_props(properties)
	{
		m_logger->init();

		createWindow();
		createVulkan();
	}


	Engine::Engine() {
		m_logger->init();

		createWindow();
		createVulkan();
	}


	Engine::~Engine() {
		delete m_swapchain;
		delete m_logical_device;
		delete m_physical_device;
		delete m_surface;
		delete m_instance;
		delete m_window;
		delete m_logger;
	}


	bool Engine::isRunning() const {
		return !m_window->shouldClose();
	}


	void Engine::update() {
		m_window->update();
	}


	const bool Engine::isValidationEnabled() const {
		return m_instance->isValidationEnabled();
	}


	const Logger& Engine::getLogger() const {
		return *m_logger;
	}


	const Instance& Engine::getInstance() const {
		return *m_instance;
	}


	const PhysicalDevice& Engine::getPhysicalDevice() const {
		return *m_physical_device;
	}


	const LogicalDevice& Engine::getLogicalDevice() const {
		return *m_logical_device;
	}


	const Swapchain& Engine::getSwapchain() const {
		return *m_swapchain;
	}

} // namespace carbon
