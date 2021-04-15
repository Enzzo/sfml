#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed || event.key.code == sf::Keyboard::Key::Space)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}