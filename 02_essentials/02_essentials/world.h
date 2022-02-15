#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "source_manager.h"
#include "scene_node.h"
#include "aricraft.h"

class World : private sf::NonCopyable {
public:
	explicit World(sf::RenderWindow&);
	void update(sf::Time);
	void draw();

private:
	void loadTextures();
	void buildScene();

private:
	enum Layer {
		Background,
		Air,
		LayerCount
	};

private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;
	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
	float								mScrollSpeed;
	Aircraft*							mPlayerAircraft;
};