#include <iostream>

#include "carbon/carbon.hpp"

int main() {

	carbon::utils::version ver{ 1, 1, 0 };

	std::cout << "Version " << ver.major << '.' << ver.minor << '.' << ver.patch << '\n';

	std::string hi{};
	std::cin >> hi;

	return 0;
}