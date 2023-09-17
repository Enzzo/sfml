#include "aircraft.h"

Textures::ID to_texture_id(Aircraft::Type type) {
	switch (type) {
	case Aircraft::Type::Eagle:
		return Textures::ID::Eagle;

	case Aircraft::Type::Raptor:
		return Textures::ID::Raptor;
	}
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
	: _type(type)
	, _sprite(textures.get(to_texture_id(type))) {}

void Aircraft::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite, states);
}