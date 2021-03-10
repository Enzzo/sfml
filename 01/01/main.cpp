#include <sfml/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <assert.h>
#include "AssetManager.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
	window.setFramerateLimit(60);

	AssetManager manager;

	sf::Sprite sprite1 = sf::Sprite(AssetManager::GetTexture("myTexture1.png"));
	sf::Sprite sprite2 = sf::Sprite(AssetManager::GetTexture("myTexture2.png"));
	sf::Sprite sprite3(AssetManager::GetTexture("myTexture1.png"));

	float speed = 2;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				window.close();
		}
		window.clear();
		window.display();
	}
	return 0;
}