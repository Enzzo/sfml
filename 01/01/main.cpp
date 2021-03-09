#include <sfml/Graphics.hpp>
#include <iostream>

void initRect(sf::RectangleShape&, const sf::Vector2f&, const sf::Color&);

int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			
		}
		window.clear();
		window.display();
	}

	return 0;
}

void initRect(sf::RectangleShape& rect, const sf::Vector2f& pos, const sf::Color& color) {

}