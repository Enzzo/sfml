#pragma once

#include "SFML/Graphics.hpp"

#include "world.h"
#include "player.h"
#include "scene_node.h"

//--------------------------------------------------+
//					class Game						|
//--------------------------------------------------+
class Game {
public:
	Game();

	void run();	

private:
	void proccess_events();
	void handle_player_input(const sf::Keyboard::Key& key, bool is_pressed);
	void update(const sf::Time);
	void render();
	void proccess_input();

private:	
	sf::RenderWindow _window;
	sf::Texture _texture;
	Player _player;
	World _world;

	bool _is_moving_up, _is_moving_down, _is_moving_left, _is_moving_right;
	bool _is_paused, _is_closed;

	float _player_speed;
	const sf::Time _time_per_frame;
};