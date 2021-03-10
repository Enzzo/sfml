#include <sfml/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");

	window.setFramerateLimit(60);

	sf::Texture leaf_tex;
	leaf_tex.loadFromFile("img/leaf.png");
	leaf_tex.setRepeated(true);

	sf::RectangleShape rect(sf::Vector2f(100, 200));
	rect.setTextureRect(sf::IntRect(20, 20, 10000, 20000));

	rect.setTexture(&leaf_tex); 
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(3);
	rect.setPosition(50, 50);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				window.close();
		}
		window.clear();
		window.draw(rect);
		window.display();
	}
	return 0;
}