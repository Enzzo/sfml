#include <iostream>

#include "SFML/Graphics.hpp"

#include "asset_manager.h"

int main5() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "sound", sf::Style::Default);

	// Listener at the center of the window
	sf::Listener::setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f, 0);

	// The listener is facing UP (-Y)
	sf::Listener::setDirection(0, -1, 0);

	// Shape for the listener (world representation)
	sf::CircleShape shape_listener(20);
	shape_listener.setFillColor(sf::Color::Red);

	sf::Sound sound(asset_manager::instance()->get_sound_buffer("../../../src/snd/JJ_Level_1.wav"));
	// Sound will start to fade away from the listener when it's
	// more than 160 pixels away from the listener (640 / 4 = 160)
	
	sound.setMinDistance(window.getSize().x / 4.f);

	// Sound will fade quite quickly, once it passes the 160 pixels boundary
	sound.setAttenuation(20.f);

	// Shape for the sound (world representation)
	sf::CircleShape shape_sound(10);
	shape_sound.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sound.play();
			}
		}

		// Get 2D listener position
		sf::Vector2f listener_pos(sf::Listener::getPosition().x, sf::Listener::getPosition().y);
		// Set listener position (constant for this example)
		shape_listener.setPosition(listener_pos);

		// Set sound position
		sf::Vector2f sound_pos(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		
		sound.setPosition(sound_pos.x, sound_pos.y, 0);
		shape_sound.setPosition(sound_pos);

		window.clear();

		window.draw(shape_listener);
		window.draw(shape_sound);

		window.display();
	}
	return 0;
}