#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"

#include <animator.h>

int main4() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
	window.setFramerateLimit(60);

	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	sf::Sprite crystal1, crystal2, crystal3, crystal4;
	sf::Vector2f origin{ 16, 16 };

	crystal1.setOrigin(origin);
	crystal2.setOrigin(origin);
	crystal3.setOrigin(origin);
	crystal4.setOrigin(origin);

	crystal1.setPosition(80, 80);
	crystal2.setPosition(-80, -80);
	crystal3.setPosition(-80, 80);
	crystal4.setPosition(80, -80);

	sf::Vector2f p1 = crystal1.getPosition();
	sf::Vector2f p2 = crystal2.getPosition();
	sf::Vector2f dist = p1 - p2;
	sf::Vector2f center = p1 - sf::Vector2f{ dist.x / 2, dist.y / 2 };

	view.setCenter(center);

	animator cr1_anim(crystal1);
	animator cr2_anim(crystal2);
	animator cr3_anim(crystal3);
	animator cr4_anim(crystal4);

	sf::Vector2i sprite_size(32, 32);

	std::string path = "../../../src/png/";

	animator::animation& cr1_idle = cr1_anim.create_animation("idle", path + "gem_blue.png", sf::seconds(0.5f), true);
	animator::animation& cr2_idle = cr2_anim.create_animation("idle", path + "gem_blue.png", sf::seconds(0.5f), true);
	animator::animation& cr3_idle = cr3_anim.create_animation("idle", path + "gem_blue.png", sf::seconds(0.5f), true);
	animator::animation& cr4_idle = cr4_anim.create_animation("idle", path + "gem_blue.png", sf::seconds(0.5f), true);
	cr1_idle.add_frames(sf::Vector2i(0, 0), sprite_size, 8);
	cr2_idle.add_frames(sf::Vector2i(0, 0), sprite_size, 8);
	cr3_idle.add_frames(sf::Vector2i(0, 0), sprite_size, 8);
	cr4_idle.add_frames(sf::Vector2i(0, 0), sprite_size, 8);

	sf::Clock clock;

	while (window.isOpen()) {

		sf::Time delta_time = clock.restart();

		cr1_anim.update(delta_time);
		cr2_anim.update(delta_time);
		cr3_anim.update(delta_time);
		cr4_anim.update(delta_time);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.key.code == sf::Keyboard::Key::Escape) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f scene_coords = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				std::cout << scene_coords.x << " " << scene_coords.y << std::endl;
			}
		}

		view.rotate(1);

		window.setView(view);

		window.clear();
		window.draw(crystal1);
		window.draw(crystal2);
		window.draw(crystal3);
		window.draw(crystal4);
		window.display();
	}

	return 0;
}