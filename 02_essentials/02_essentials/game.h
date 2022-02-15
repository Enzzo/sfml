#pragma once

#include <SFML/Graphics.hpp>

#include "source_manager.h"
#include "aricraft.h"

enum class Layer {
	Background,
	Air,
	LayerCount //is not used to refer to a layer; instead it stores the total amount of layers
};

class Game {	
	sf::RenderWindow window_;
	//ResourceHolder<sf::Texture, Textures::ID> mTextures;
	TextureHolder mTextures;
	sf::Sprite mPlayer;

	sf::Time mTimePerFrame;
	int mPlayerSpeed;

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