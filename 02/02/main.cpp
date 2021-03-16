#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <chrono>

int main() {

	sf::RenderWindow window(sf::VideoMode(400, 400), "Title");
	AssetManager manager;

	sf::Sprite sprite1(AssetManager::GetTexture("myTexture1.png"));
	sf::Sprite sprite2(AssetManager::GetTexture("myTexture2.png"));
	sf::Sprite sprite3(AssetManager::GetTexture("myTexture1.png"));

	sf::Vector2i sprite_size(32, 32);

	sprite1.setPosition(20, 20);
	sprite2.setPosition(80, 80);
	sprite3.setPosition(200, 200);

	int time_duration = 1;//sec
	int frames = 8;

	while (window.isOpen()) {

		double elapsed_time = 0.0;

		int frame = static_cast<int>(((elapsed_time * time_duration) * frames) % frames);
		sf::Vector2i sprite_pos(frame * sprite_size.x, 0);
		sprite1.setTextureRect(sf::IntRect(sprite_pos, sprite_size));

		sf::Event ev;
		while (window.pollEvent(ev)){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || ev.type == sf::Event::EventType::Closed)
				window.close();
		}
		window.clear();
		window.draw(sprite1);
		window.draw(sprite2);
		window.draw(sprite3);
		window.display();
	}

	return 0;
}