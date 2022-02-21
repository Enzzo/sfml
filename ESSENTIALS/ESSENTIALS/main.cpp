#include <iostream>
#include <chrono>
#include <vector>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"
#include "Animation.h"

int main() {

	AssetManager am;

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
	window.setFramerateLimit(60);

	const sf::Vector2u &w_size = window.getSize();
	sf::View view(sf::FloatRect(0, 0, w_size.x, w_size.y));
	view.setCenter(sf::Vector2f(0, 0));

	std::vector<sf::View> view_list(4, sf::View(sf::FloatRect(0, 0, w_size.x, w_size.y)));

	for (sf::View& v : view_list) {
		v.setCenter(sf::Vector2f(0, 0));
	}

	view_list[0].setViewport(sf::FloatRect(0, 0, 0.5f, 0.5f));
	view_list[1].setViewport(sf::FloatRect(0.5f, 0, 0.5f, 0.5f));
	view_list[2].setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f));
	view_list[3].setViewport(sf::FloatRect(0, 0.5f, 0.5f, 0.5f));

	view.setViewport(sf::FloatRect(0, 0, 0.5f, 0.5f));

	sf::Vector2f spriteSize(32, 32);
	auto texture = AssetManager::GetTexture("sprites\\gem_blue.png");
	
	sf::Sprite sprite1(texture);
	sprite1.setOrigin(spriteSize * 0.5f);
	sprite1.setPosition(sf::Vector2f(-80, -80));
	sprite1.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::Sprite sprite2(texture);
	sprite2.setOrigin(spriteSize * 0.5f);
	sprite2.setPosition(sf::Vector2f(80, -80));
	sprite2.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::Sprite sprite3(texture);
	sprite3.setOrigin(spriteSize * .5f);
	sprite3.setPosition(sf::Vector2f(80, 80));
	sprite3.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::Sprite sprite4(texture);
	sprite4.setOrigin(spriteSize * .5f);
	sprite4.setPosition(sf::Vector2f(-80, 80));
	sprite4.setTextureRect(sf::IntRect(0, 0, 32, 32));

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		}

		window.clear();		
		
		for (sf::View& v : view_list) {
			window.setView(v);
			window.draw(sprite1);
			window.draw(sprite2);
			window.draw(sprite3);
			window.draw(sprite4);
		}

		window.display();
	}
 
	return 0;
}