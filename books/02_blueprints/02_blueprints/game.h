#pragma once

#include <SFML/Graphics.hpp>

class game {
public:
	game() = default;

	void run(int frame_per_second);

private:
	void proccess_events();
	void update(const sf::Time time_per_frame);
	void render();

private:
	sf::RenderWindow _window;
};