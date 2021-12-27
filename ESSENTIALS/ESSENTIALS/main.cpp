#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"
#include "Animation.h"

int main() {

	AssetManager am;

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
	window.setFramerateLimit(60);

	sf::Texture t1(AssetManager::GetTexture("sprites\\gem_blue.png"));		
	sf::RectangleShape rectShape(sf::Vector2f(50, 50));

	rectShape.setTexture(&t1);
	rectShape.setOrigin(25, 25);
	rectShape.setTextureRect(sf::IntRect(0, 0, 32, 32));
	rectShape.setPosition(320, 240);

	int frames = 8;
	int animSpeed = 18; //sec

	std::chrono::time_point begin = std::chrono::steady_clock::now();

	while (window.isOpen()) {
		sf::Event event;
		std::chrono::time_point end = std::chrono::steady_clock::now();
		std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

		int frame = delta.count() / static_cast<int>(1000 / animSpeed) % frames * 32;
		std::cerr << frame << std::endl;
		rectShape.setTextureRect(sf::IntRect(frame, 0, 32, 32));
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed || event.key.code == sf::Keyboard::Key::Space)
				window.close();
		}

		window.clear();
		window.draw(rectShape);
		window.display();
	}

	return 0;
}