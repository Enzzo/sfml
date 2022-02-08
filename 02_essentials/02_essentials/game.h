#pragma once

#include <SFML/Graphics.hpp>

class Game {
	sf::RenderWindow _window;
	sf::CircleShape _player;

	bool is_moving_up, is_moving_down, is_moving_left, is_moving_right;

public:
	Game();
	void run();

private:
	void ProcessEvents();
	void Update();
	void Render();
	void HandlePlayerInterrupt(const sf::Keyboard::Key, const bool);
};