#include <SFML/Graphics.hpp>
#include "AssetManager.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(400, 400), "Title");
	AssetManager manager;

	sf::Sprite sprite1(AssetManager::GetTexture("myTexture1.png", true));
	sf::Sprite sprite2(AssetManager::GetTexture("myTexture2.png", false));
	sf::Sprite sprite3(AssetManager::GetTexture("myTexture1.png", true));

	sprite1.setPosition(20, 20);
	sprite2.setPosition(80, 80);
	sprite3.setPosition(200, 200);

	sprite1.setTextureRect(sf::IntRect(15, 15, 64, 32));
	sprite3.setTextureRect(sf::IntRect(15, 15, 32, 32));

	sf::Time elapsedTime;
	sf::Time deltaTime;
	sf::Clock clock;

	while (window.isOpen()) {
		deltaTime = clock.restart();
		std::cout << deltaTime.asSeconds() << std::endl;

		elapsedTime += deltaTime;
		if (elapsedTime > sf::seconds(5))window.close();

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