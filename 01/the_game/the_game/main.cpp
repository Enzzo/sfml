#include <iostream>

#include "game.h"

int main() {
	try {
		Game game;
		game.run();
	}
	catch (std::exception& e) {
		std::cerr << "\nbEXCEPTION: " << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}