#include <iostream>

#include "carbon/carbon.hpp"

int main() {

	const char *title{ "Work In Progress: Game " };
	carbon::utils::version ver{ 1, 1, 0 };

	// off-screen rendering
	carbon::Instance inst{ title, ver };

	// create window
	carbon::Window win{ title, 1280, 720 };

	// main loop when window is open
	while (win.isOpen()) {
		win.pollEvents();
	}

	// destroy window
	win.destroy();

	return 0;
}
