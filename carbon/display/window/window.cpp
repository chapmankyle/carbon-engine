// file      : carbon/display/window/window.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "window.hpp"

#include "carbon/core/instance.hpp"
#include "carbon/display/surface.hpp"

namespace carbon {

	Window::Window(const window::Props &properties)
		: m_props(properties)
	{
		// set initial size and position of window
		m_initial_size = glm::ivec2(m_props.width, m_props.height);
		m_initial_pos = glm::ivec2(m_props.x, m_props.y);

		// set current size and position to initial size and position
		m_size = m_initial_size;
		m_pos = m_initial_pos;
	}


	Window::Window(const std::string &title, i32 width, i32 height) {
		m_props = {};
		m_props.title = title;
		m_props.width = width;
		m_props.height = height;

		// set size of window
		m_initial_size = glm::ivec2(m_props.width, m_props.height);
		m_size = m_initial_size;
	}


	Window::Window(i32 width, i32 height) {
		m_props = {};
		m_props.width = width;
		m_props.height = height;

		// set size of window
		m_initial_size = glm::ivec2(m_props.width, m_props.height);
		m_size = m_initial_size;
	}


	Window::Window() {
		// initialize props to all default values
		m_props = {};
	}


	Window::~Window() {}


	const std::string Window::getTitle() const {
		return m_props.title;
	}


	const i32 Window::getWidth() const {
		return to_i32(m_size[0]);
	}


	const i32 Window::getHeight() const {
		return to_i32(m_size[1]);
	}


	const glm::ivec2 Window::getSize() const {
		return m_size;
	}


	const i32 Window::getX() const {
		return to_i32(m_pos[0]);
	}


	const i32 Window::getY() const {
		return to_i32(m_pos[1]);
	}


	const glm::ivec2 Window::getPosition() const {
		return m_pos;
	}


	const float Window::getAspectRatio() const {
		return static_cast<float>(m_size[1]) / static_cast<float>(m_size[0]); // 0 -> width, 1 -> height
	}


	const bool Window::isResizable() const {
		return m_resizable;
	}


	const bool Window::isMinimized() const {
		return m_minimized;
	}


	const window::Mode Window::getWindowMode() const {
		return m_window_mode;
	}


	const char* Window::getWindowModeName(window::Mode mode) const {
		i32 idx = static_cast<i32>(mode);
		assert(idx < static_cast<i32>(window::Mode::NONE) + 1 && "[ERROR] Invalid window mode!");

		return m_window_mode_names[idx];
	}


	const cursor::Mode Window::getCursorMode() const {
		return m_cursor_mode;
	}


	const bool Window::isMouseVisible() const {
		return m_cursor_mode == cursor::Mode::Normal;
	}


	const utils::version& Window::getVersion() const {
		return m_props.version;
	}

} // namespace carbon
