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
		m_initial_width = m_props.width;
		m_initial_height = m_props.height;
	}

	Window::Window() {}

	Window::~Window() {}


	const std::string Window::getTitle() const {
		return m_props.title;
	}


	const i32 Window::getWidth() const {
		return m_props.width;
	}


	const i32 Window::getHeight() const {
		return m_props.height;
	}


	const float Window::getAspectRatio() const {
		return static_cast<float>(m_props.height) / static_cast<float>(m_props.width);
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
