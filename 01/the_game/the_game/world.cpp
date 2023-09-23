#include "world.h"

//--------------------------------------------------+
//					class World						|
//--------------------------------------------------+
//					World							|
//--------------------------------------------------+
World::World(sf::RenderWindow& window)
	: _window(window)
	, _world_view(window.getDefaultView())
	, _world_bounds(
		0.f,						// left X position
		0.f,						// top Y position
		_world_view.getSize().x,	// width
		2000.f)						// height
	, _spawn_position(
		_world_view.getSize().x / 2.f,						// X
		_world_bounds.height - _world_view.getSize().y)		// Y
	, _player_aircraft(nullptr)
{
	load_textures();
	build_scene();

	_world_view.setCenter(_spawn_position);
}

//--------------------------------------------------+
//					class World						|
//--------------------------------------------------+
//					void update						|
//--------------------------------------------------+
void World::update(sf::Time dt) {
	_world_view.move(0.f, _scroll_speed * dt.asSeconds());

	_player_aircraft->set_velocity(0.f, 0.f);

	//	forward commands to the scene graph
	while (!_command_queue.is_empty()) {
		_scene_graph.on_command(_command_queue.pop(), dt);
	}

	sf::Vector2f velocity = _player_aircraft->get_velocity();

	if (velocity.x != 0.f && velocity.y != 0.f) {
		_player_aircraft->set_velocity(velocity / std::sqrt(2.f));
	}

	_player_aircraft->accelerate({ 0.f, _scroll_speed });
	
	//	regular update step
	_scene_graph.update(dt);

	sf::FloatRect view_bounds(
		_world_view.getCenter() - _world_view.getSize() / 2.f,
		_world_view.getSize());
	
	const float border_distance = 40.f;

	sf::Vector2f position = _player_aircraft->getPosition();
	position.x = std::max(position.x, view_bounds.left + border_distance);
	position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
	position.y = std::max(position.y, view_bounds.top + border_distance);
	position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);

	_player_aircraft->setPosition(position);
}

//--------------------------------------------------+
//					class World						|
//--------------------------------------------------+
//					void draw						|
//--------------------------------------------------+
void World::draw() {
	_window.setView(_world_view);
	_window.draw(_scene_graph);
}

//--------------------------------------------------+
//					class World						|
//--------------------------------------------------+
//			CommandQueue& get_command_queue			|
//--------------------------------------------------+
CommandQueue& World::get_command_queue(){
	return _command_queue;
}

//--------------------------------------------------+
//					class World						|
//--------------------------------------------------+
//					load_textures					|
//--------------------------------------------------+
void World::load_textures() {
	_textures.load(Textures::ID::Eagle, "D:\\dev\\git\\sfml\\src\\png\\Eagle.png");
	_textures.load(Textures::ID::Raptor, "D:\\dev\\git\\sfml\\src\\png\\Raptor.png");
	_textures.load(Textures::ID::Desert, "D:\\dev\\git\\sfml\\src\\png\\Desert.png");
}

//--------------------------------------------------+
//					class World						|
//--------------------------------------------------+
//					build_scene 					|
//--------------------------------------------------+
void World::build_scene() {
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::ptr layer(new SceneNode());
		_scene_layers[i] = layer.get();
		_scene_graph.attach_child(std::move(layer));
	}

	sf::Texture& texture = _textures.get(Textures::ID::Desert);
	sf::IntRect texture_rect(_world_bounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> background_sprite(new SpriteNode(texture, texture_rect));
	background_sprite->setPosition(_world_bounds.left, _world_bounds.top);
	_scene_layers[Background]->attach_child(std::move(background_sprite));
	
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, _textures));
	_player_aircraft = leader.get();
	_player_aircraft->setPosition(_spawn_position);
	_player_aircraft->set_velocity(40.f, _scroll_speed);
	_scene_layers[Air]->attach_child(std::move(leader));

	std::unique_ptr<Aircraft> left_escort(new Aircraft(Aircraft::Raptor, _textures));
	left_escort->setPosition(-80.f, 50.f);
	_player_aircraft->attach_child(std::move(left_escort));

	std::unique_ptr<Aircraft> right_escort(new Aircraft(Aircraft::Raptor, _textures));
	right_escort->setPosition(80.f, 50.f);
	_player_aircraft->attach_child(std::move(right_escort));
}