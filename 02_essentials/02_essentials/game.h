#pragma once

#include <SFML/Graphics.hpp>

#include "source_manager.h"
#include "aricraft.h"
#include "world.h"

enum class Layer {
	Background,
	Air,
	LayerCount //is not used to refer to a layer; instead it stores the total amount of layers
};

class Game : private sf::NonCopyable {
	static const sf::Time TimePerFrame;
	sf::RenderWindow mWindow;	
	World mWorld;
	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;

public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time);
	void render();

	void updateStatistics(sf::Time);
	void handlePlayerInterrupt(const sf::Keyboard::Key, bool);
};