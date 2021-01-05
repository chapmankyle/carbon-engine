#include "carbon/carbon.hpp"

#include <iostream>

int main() {

	// to disable debug messages and validation layers, add
	// #define CARBON_DISABLE_DEBUG
	// before the
	// #include "carbon/carbon.hpp"

	std::cout << "Root directory = |" << carbon::paths::ROOT_DIR << "|\n\n";

	// setup window properties
	carbon::window::Props properties;
	properties.title = "Work In Progress: Game";
	properties.version = carbon::utils::version{ 1, 1, 0 };
	properties.width = 1280;
	properties.height = 720;
	properties.resizable = true;

	// setup timer
	carbon::Timer t;

	// start timing
	t.reset();
	carbon::Engine engine(properties);
	std::cout << "\nEngine creation took " << t.elapsed() << " ms\n";

	std::cout << "Validation ?= " << std::boolalpha << engine.isValidationEnabled() << std::noboolalpha << '\n';

	std::cout << "\nInitial position = " << carbon::utils::showVector(engine.getWindow().getPosition()) << '\n';
	std::cout << "Initial size = " << carbon::utils::showVector(engine.getWindow().getSize()) << '\n';

	std::cout << "\nAspect ratio = " << engine.getWindow().getAspectRatio() << '\n';
	std::cout << "Aspect ratio => " << carbon::utils::getEstimatedAspectRatio(properties.width, properties.height) << '\n';

	std::cout << '\n' << engine.getPhysicalDevice().getPropertiesAsStr() << '\n';

	// main loop when window is open
	while (engine.isRunning()) {
		engine.update();
	}

	return 0;
}
