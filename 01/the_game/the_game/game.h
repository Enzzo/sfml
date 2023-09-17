#pragma once

#include "SFML/Graphics.hpp"


class Game {
public:
	Game();

	void run();	

private:
	void proccess_events();
	void handle_player_input(const sf::Keyboard::Key& key, bool is_pressed);
	void update(const sf::Time&);
	void render();

private:
	sf::RenderWindow _window;
	sf::Texture _texture;
	sf::Sprite _player;

	bool _is_moving_up, _is_moving_down, _is_moving_left, _is_moving_right;

	float _player_speed;
	const sf::Time _time_per_frame;
};