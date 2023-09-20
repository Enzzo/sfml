#pragma once
#include <array>

#include "SFML/Graphics.hpp"

#include "source_manager.h"
#include "scene_node.h"
#include "aircraft.h"

class World : private sf::NonCopyable {
public:
	explicit	World(sf::RenderWindow& window);
	void		update(sf::Time dt);
	void		draw();

private:
	void		load_textures();
	void		build_scene();

private:
	enum Layer {
		Background,
		Air,
		LayerCount
	};

private:
	sf::RenderWindow&	_window;
	sf::View			_world_view;
	TextureHolder		_textures;
	SceneNode			_scene_graph;
	std::array<SceneNode*, LayerCount> _scene_layers;

	sf::FloatRect		_world_bounds;
	sf::Vector2f		_spawn_position;
	float				_scroll_speed;
	Aircraft*			_player_aircraft;
};