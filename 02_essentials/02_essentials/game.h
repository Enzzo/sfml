#pragma once

#include <SFML/Graphics.hpp>

class Game {
	sf::RenderWindow _window;
	sf::CircleShape _player;

public:
	Game();
	void run();

private:
	void ProcessEvents();
	void Update();
	void Render();
};