#include "aircraft.h"

Textures::ID to_texture_id(Aircraft::Type type) {
	switch (type) {
	case Aircraft::Eagle:
		return Textures::Eagle;

	case Aircraft::Raptor:
		return Textures::Raptor;
	}
	return Textures::Eagle;
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
	: _type(type)
	, _sprite(textures.get(to_texture_id(type))) {}

void Aircraft::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite, states);
}