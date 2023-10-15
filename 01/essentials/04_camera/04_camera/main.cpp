#include <string>

#include "SFML/Graphics.hpp"

#include <animator.h>

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
	window.setFramerateLimit(60);

	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	

	sf::Sprite crystal;
	crystal.setOrigin(16, 16);

	crystal.setPosition(80, 80);
	
	view.setCenter(crystal.getPosition());

	window.setView(view);

	animator animator(crystal);
	
	sf::Vector2i sprite_size(32, 32);

	std::string path = "../../../../src/png/";

	animator::animation &idle = animator.create_animation("idle", path + "gem_blue.png", sf::seconds(0.5f), true);
	idle.add_frames(sf::Vector2i(0, 0), sprite_size, 8);

	sf::Clock clock;
	
	while (window.isOpen()) {

		sf::Time delta_time = clock.restart();

		animator.update(delta_time);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			view.rotate(90);
		}
		window.clear();
		window.draw(crystal);
		window.display();
	}

	return 0;
}