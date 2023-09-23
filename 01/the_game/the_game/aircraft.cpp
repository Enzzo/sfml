#include "aircraft.h"

Textures::ID to_texture_id(Aircraft::Type type) {
	switch (type) {
	case Aircraft::Type::Eagle:
		return Textures::ID::Eagle;

	case Aircraft::Type::Raptor:
		return Textures::ID::Raptor;
	}
	return Textures::ID::Eagle;
}

//--------------------------------------------------+
//					class Aircraft					|
//--------------------------------------------------+
//					Constructor						|
//--------------------------------------------------+
Aircraft::Aircraft(Type type, const TextureHolder& textures)
	: _type(type)
	, _sprite(textures.get(to_texture_id(type))) {}
//--------------------------------------------------+
//					class Aircraft					|
//--------------------------------------------------+
//					void accelerate					|
//--------------------------------------------------+
void Aircraft::accelerate(sf::Vector2f velocity) {
	// TODO: моя версия
	set_velocity(get_velocity() + velocity);
}

//--------------------------------------------------+
//					class Aircraft					|
//--------------------------------------------------+
//					get_category 					|
//--------------------------------------------------+
unsigned int Aircraft::get_category() const {
	switch (_type) {
	case Eagle:
		return Category::PlayerAircraft;
	default:
		return Category::EnemyAircraft;
	}
}

//--------------------------------------------------+
//					class Aircraft					|
//--------------------------------------------------+
//					void draw_current				|
//--------------------------------------------------+
void Aircraft::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite, states);
}