#include <iostream>

#include "carbon/carbon.hpp"

int main() {

	carbon::utils::version ver{ 1, 1, 0 };

	carbon::Instance inst{ "Work In Progress: Game", ver };

	std::string hi{};
	std::cin >> hi;

	return 0;
}