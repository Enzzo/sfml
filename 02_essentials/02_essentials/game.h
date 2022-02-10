#pragma once

#include <SFML/Graphics.hpp>

#include "source_manager.h"

class Game {	
	sf::RenderWindow window_;
	//ResourceHolder<sf::Texture, Textures::ID> textures_;
	TextureHolder textures_;
	sf::Sprite player_;
	sf::Time time_per_frame_;
	int player_speed_;

	bool is_moving_up = false
		,is_moving_down = false
		,is_moving_left = false
		,is_moving_right = false;

public:
	Game();
	void Run();

private:
	void ProcessEvents();
	void Update(const sf::Time);
	void Render();
	void HandlePlayerInterrupt(const sf::Keyboard::Key, const bool);
};