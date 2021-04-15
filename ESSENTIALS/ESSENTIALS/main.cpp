#include <iostream>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"

int main() {

	AssetManager am;

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
	window.setFramerateLimit(60);

	sf::RectangleShape s1;
	sf::Texture t1(AssetManager::GetTexture("sprites\\null.png"));
	sf::Sprite sp1(t1);
	s1.setPosition(sf::Vector2f(10, 10)); 
	s1.setTextureRect(sf::IntRect(0, 0, 32, 32));

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed || event.key.code == sf::Keyboard::Key::Space)
				window.close();
		}

		window.clear();
		window.draw(s1);
		window.display();
	}

	return 0;
}