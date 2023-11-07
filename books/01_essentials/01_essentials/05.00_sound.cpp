#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "asset_manager.h"

int main_() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title", sf::Style::Default);

	sf::SoundBuffer buffer = asset_manager::instance()->get_sound_buffer("../../../src/snd/JJ_Level_3.wav");

	sf::Sound sound(buffer);

	sf::Sprite player;

	sound.play();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		sf::Listener::setPosition(player.getPosition().x, player.getPosition().y, 0);

		// window.draw(player);

		window.display();
	}

	return 0;
}