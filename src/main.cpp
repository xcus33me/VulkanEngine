#include "first_app.hpp"
#include <iostream>
#include <exception>
#include <cstdlib>

int main() {

	lve::FirstApp app{};
	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
