#include "carbon/carbon.hpp"

int main() {

	// setup window properties
	carbon::window::Props properties;
	properties.title = "Work In Progress: Game";
	properties.version = carbon::utils::version{ 1, 1, 0 };
	properties.width = 1280;
	properties.height = 720;
	properties.resizable = true;
	properties.showFPS = true;

	// setup timer
	carbon::Timer t;

	// start timing
	t.reset();
	carbon::Engine engine(properties);
	double elapsed = t.elapsed();

	// use logger to output stats
	carbon::Logger logger = engine.getLogger();

	logger.log(carbon::log::To::Console, carbon::log::State::Info, fmt::format("Root directory = |{}|", carbon::paths::ROOT_DIR));

	logger.log(carbon::log::To::File, carbon::log::State::Info, "Engine Statistics:");
	logger.log(carbon::log::To::File, carbon::log::State::Info, fmt::format("  Initialization -> {:.2f} ms", elapsed));
	logger.log(carbon::log::To::File, carbon::log::State::Info, fmt::format("  Validation     -> {}", engine.isValidationEnabled() ? "Enabled" : "Disabled"));

	logger.log(carbon::log::To::File, carbon::log::State::Info, "Window Statistics:");
	logger.log(carbon::log::To::File, carbon::log::State::Info, fmt::format("  Initial position -> {}", carbon::utils::showVector(engine.getWindow().getPosition())));
	logger.log(carbon::log::To::File, carbon::log::State::Info, fmt::format("  Initial size     -> {}", carbon::utils::showVector(engine.getWindow().getSize())));
	logger.log(carbon::log::To::File, carbon::log::State::Info, fmt::format("  Aspect ratio     -> {:.2f} (= {})", engine.getWindow().getAspectRatio(), carbon::utils::getEstimatedAspectRatio(properties.width, properties.height)));

	// main loop when window is open
	while (engine.isRunning()) {
		engine.update();
	}

	return 0;
}
